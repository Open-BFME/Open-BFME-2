#!/usr/bin/env python3
"""Decompile WorldBuilder functions with Ghidra, named from our evidence.

worldbuilder.exe is an unoptimised internal build of the source game.dat was
compiled from, so Ghidra's pseudo-C of a WB function is a far better starting
point for C++ than retail's optimised body. This driver runs Ghidra headless
in two steps:

  import   once: import worldbuilder.exe into build/wb/ghidra/proj with the
           expensive analyzers off and every tools/pe_features.py boundary
           seeded as a function (tools/ghidra/wb_prepare.java). Takes tens of
           minutes; run it in the background.

  run      any number of times: write the naming table, then decompile the
           chosen WB functions (tools/ghidra/wb_decompile.java) to
           build/wb/decomp/<wb_va>.c, or <wb_va>.err when Ghidra fails.
           Functions already decompiled are skipped, so a run is resumable.

Naming, applied in the Ghidra project before decompiling (callees included,
so call sites read as names):
  * the WB name the matcher gave the function, else a WB name only this
    function pushes (an assert's "Class::method"; a header's name counts only
    when it is the function's sole name, since inlined helpers push theirs)
  * else, if the function is paired with a game.dat function, that ledger
    row's demangled name when it is a real or partial identity, otherwise
    gd_<rva>_<ledger name> (or gd_<rva> when unrowed)
  * "Class::method" goes into a Ghidra class namespace, and a function whose
    prologue saves ecx into its frame becomes __thiscall, so `this` is typed
  * WB's debug object global and its out-of-line wrappers (tools/wb_show.py's
    detection) are labelled TheDebugObject / DebugObject_*, which
    tools/wb_draft.py strips
  * callees without a signature get one undefined4 parameter per 4 bytes of
    their `ret N` (or of the caller's `add esp, N`), so calls show arguments

Targets default to every wb_va in build/wb/matches_full.jsonl: functions
behind reverse/wb_name_leads.csv first, then the rest, largest first within
each group. --vas picks explicit WB VAs (or game.dat RVAs with --gd).

    python3 tools/wb_decompile.py import
    python3 tools/wb_decompile.py run [--limit N] [--vas 0x... ...] [--gd]
                                      [--timeout S] [--force]

Needs Ghidra 11.x or later and JDK 21. Ghidra is found at $GHIDRA_HOME, else
as tools/ghidra_refdb.py finds it ($GHIDRA_INSTALL_DIR, build/toolchains/ or
inputs/toolchains/). Most seats need neither: tools/wb_data.py unpacks the
committed decompilation (reverse/wb/wb_decomp.jsonl.xz). Outputs are
unverified decompiler text: identity evidence and a draft source, never proof
of a byte match.
"""
import argparse
import csv
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

import wb_show

ROOT = wb_show.ROOT
GHIDRA_DIR = ROOT / "build" / "wb" / "ghidra"
PROJECT_DIR = GHIDRA_DIR / "proj"
PROJECT_NAME = "wb"
PROGRAM = wb_show.WB_EXE.name
SEEDS = GHIDRA_DIR / "seeds.txt"
NAMES = GHIDRA_DIR / "names.tsv"
TARGETS = GHIDRA_DIR / "targets.txt"
OUT_DIR = ROOT / "build" / "wb" / "decomp"
LEADS = ROOT / "reverse" / "wb_name_leads.csv"
SCRIPTS = ROOT / "tools" / "ghidra"
IMAGE_BASE = wb_show.IMAGE_BASE
MAX_MEM = "10G"
PROLOGUE_BYTES = 96
HEADER_SUFFIXES = (".h", ".hpp", ".inl")
DEBUG_GLOBAL_NAME = "TheDebugObject"
REAL_KINDS = ("REAL", "PARTIAL")


# ----------------------------------------------------------------- ghidra

def ghidra_home():
    """The Ghidra install directory: $GHIDRA_HOME, else where tools/ghidra_refdb.py
    looks ($GHIDRA_INSTALL_DIR, then build/toolchains/ghidra_* or
    inputs/toolchains/ghidra_*)."""
    home = os.environ.get("GHIDRA_HOME")
    if home:
        return Path(home)
    import ghidra_refdb
    return ghidra_refdb.ghidra_home()


def ghidra_env():
    """The caller's environment, with JAVA_HOME set from tools/ghidra_refdb.py's
    lookup (build/toolchains/jdk-*, inputs/toolchains/jdk-*) when it is unset and
    one is found; otherwise launch.sh finds java on PATH."""
    env = dict(os.environ)
    if not env.get("JAVA_HOME"):
        import ghidra_refdb
        try:
            env["JAVA_HOME"] = str(ghidra_refdb.java_home())
        except SystemExit:
            pass
    return env


def headless(args, log):
    """Run AnalyzeHeadless with a large heap; its output goes to log and is returned."""
    launch = ghidra_home() / "support" / "launch.sh"
    vmargs = "-XX:ParallelGCThreads=2 -XX:CICompilerCount=2 -Djava.awt.headless=true"
    command = [str(launch), "fg", "jdk", "Ghidra-Headless", MAX_MEM, vmargs,
               "ghidra.app.util.headless.AnalyzeHeadless", str(PROJECT_DIR), PROJECT_NAME, *args]
    with open(log, "w") as fh:
        result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                                env=ghidra_env())
        fh.write(result.stdout)
    if result.returncode:
        sys.exit(f"Ghidra failed (exit {result.returncode}); see {log}")
    return result.stdout


def import_program():
    """Create the project: seeded import with the reduced analyzer set."""
    PROJECT_DIR.mkdir(parents=True, exist_ok=True)
    with open(wb_show.WB_JSONL) as fh, open(SEEDS, "w") as out:
        for record in map(json.loads, fh):
            out.write(f"{record['va']:#x}\n")
    started = time.time()
    headless(["-import", str(wb_show.WB_EXE), "-overwrite", "-analysisTimeoutPerFile", "14400",
              "-scriptPath", str(SCRIPTS), "-preScript", "wb_prepare.java", str(SEEDS)],
             GHIDRA_DIR / "import.log")
    print(f"imported and analysed in {time.time() - started:.0f}s")


# ----------------------------------------------------------------- naming

def split_qualified(name):
    """("A::B", "method") for "A::B::method", splitting only outside <...> and (...)."""
    depth, cut = 0, -1
    for i, ch in enumerate(name):
        if ch in "<(":
            depth += 1
        elif ch in ">)":
            depth -= 1
        elif depth == 0 and name.startswith("::", i):
            cut = i
    return (name[:cut], name[cut + 2:]) if cut > 0 else ("", name)


def ghidra_safe(text):
    """Ghidra symbol names may not contain whitespace."""
    return re.sub(r"\s+", "", text)


def identifier(text):
    return re.sub(r"[^0-9A-Za-z_]+", "_", text).strip("_")


def own_names(path=wb_show.WB_JSONL):
    """{wb_va: name} for WB functions whose most-pushed name is unique to them.

    A name pushed beside a header path is an inlined helper's, so it counts
    only when it is the function's sole name.
    """
    with open(path) as fh:
        records = [(r["va"], r["names"], dict(map(tuple, r["name_files"])))
                   for r in map(json.loads, fh) if r["names"]]
    spread = {}
    for _, names, _ in records:
        for name in set(names):
            spread[name] = spread.get(name, 0) + 1
    chosen = {}
    for va, names, files in records:
        name = names[0]
        from_header = files.get(name, "").lower().endswith(HEADER_SUFFIXES)
        if spread[name] == 1 and (len(names) == 1 or not from_header):
            chosen[va] = name
    return chosen


def ledger_name(namer, gd_va):
    """Name for a WB function from its game.dat pairing's ledger row."""
    rows = namer.ledger(gd_va)
    rva = gd_va - IMAGE_BASE
    if not rows:
        return f"gd_{rva:08X}"
    _, display, kind = rows[0]
    return display if kind in REAL_KINDS else f"gd_{rva:08X}_{identifier(display)}"


def best_gd(index, wb_va):
    """The game.dat VA paired with wb_va at the highest score, or None."""
    matches = [m for gd_va in index["by_wb"].get(wb_va, ())
               for m in index["by_gd"].get(gd_va, ()) if m["wb_va"] == wb_va]
    return max(matches, key=lambda m: m["score"])["gd_va"] if matches else None


def matched_names(index):
    """{wb_va: name} from the matcher's wb_name for each pairing."""
    names = {}
    for matches in index["by_gd"].values():
        for match in matches:
            if match.get("wb_name"):
                names.setdefault(match["wb_va"], match["wb_name"])
    return names


def function_names(index):
    """{wb_va: qualified name} for every WB function we can name."""
    namer = wb_show.Namer(index)
    names = {va: ledger_name(namer, gd_va) for va in index["by_wb"]
             if (gd_va := best_gd(index, va)) is not None}
    names.update(own_names())
    names.update(matched_names(index))
    for va, slot in index["debug_wrappers"].items():
        names[va] = f"DebugObject_slot_{slot:#x}"
    for va in index["debug_flags"]:
        names[va] = "DebugObject_flag"
    return names


def saves_this(image, md, va):
    """Does the function's prologue store ecx into its frame (a member function)?"""
    insns = list(wb_show.disassemble(md, image, va, PROLOGUE_BYTES))
    return bool(insns) and wb_show.Frame(insns).this_slot is not None


def write_names(index, targets):
    """Write names.tsv (kind, va, namespace, name, thiscall) for the Ghidra script:
    every named WB function, every target, and every member function (by its
    prologue) so unnamed callees are __thiscall too."""
    image = wb_show.pf.Image(wb_show.WB_EXE)
    md = wb_show.pf.Context(image, {}, False).md
    names = function_names(index)
    rows = []
    if index["debug_global"] is not None:
        rows.append(("D", f"{index['debug_global']:#x}", "", DEBUG_GLOBAL_NAME, "0"))
    for va in sorted(set(names) | set(targets) | set(index["wb"])):
        namespace, base = split_qualified(names.get(va, ""))
        thiscall = saves_this(image, md, va)
        if base or thiscall or va in targets:
            rows.append(("F", f"{va:#x}", ghidra_safe(namespace), ghidra_safe(base), "1" if thiscall else "0"))
    with open(NAMES, "w") as fh:
        fh.writelines("\t".join(row) + "\n" for row in rows)
    return len(rows)


# ---------------------------------------------------------------- targets

def lead_wb_vas(index):
    """WB VAs paired with the game.dat functions in reverse/wb_name_leads.csv."""
    found = set()
    with open(LEADS, newline="") as fh:
        for row in csv.DictReader(fh):
            gd_va = int(row["target_rva"], 16) + IMAGE_BASE
            wb_va = wb_show.wb_for_gd(index, gd_va)
            if wb_va is not None:
                found.add(wb_va)
    return found


def default_targets(index):
    """Every matched WB VA: name leads first, then the rest; largest first in each."""
    def size(va):
        return index["wb"].get(va, (0,))[0]
    leads = lead_wb_vas(index)
    rest = set(index["by_wb"]) - leads
    return sorted(leads, key=size, reverse=True) + sorted(rest, key=size, reverse=True)


def explicit_targets(index, values, gd):
    """WB VAs for --vas values; with --gd they are game.dat targets in any form
    tools/wb_show.py accepts (rva, va, rva:/va: prefixed, ledger or WB name)."""
    if not gd:
        return [int(text, 16) for text in values]
    targets = []
    for text in values:
        try:
            _, wb_va, _ = wb_show.resolve_target(index, text)
        except SystemExit as error:
            wb_va, reason = None, error.code
        else:
            reason = "no WB pairing"
        if wb_va is None:
            print(f"skip {text}: {reason}", file=sys.stderr)
        else:
            targets.append(wb_va)
    return targets


def pending(targets, force):
    """Targets without an output yet (all of them with force)."""
    if force:
        return list(targets)
    return [va for va in targets
            if not (OUT_DIR / f"{va:#x}.c").exists() and not (OUT_DIR / f"{va:#x}.err").exists()]


# -------------------------------------------------------------------- run

def run(args):
    """Name, then decompile the pending targets in one headless session."""
    if not (PROJECT_DIR / f"{PROJECT_NAME}.gpr").exists():
        sys.exit("no Ghidra project yet: run `tools/wb_decompile.py import` first")
    index = wb_show.load_index()
    targets = explicit_targets(index, args.vas, args.gd) if args.vas else default_targets(index)
    todo = pending(targets, args.force)[:args.limit or None]
    if not todo:
        print(f"nothing to do: all {len(targets)} targets decompiled")
        return
    for va in todo:                     # --force: drop stale outputs first
        for suffix in (".c", ".err"):
            (OUT_DIR / f"{va:#x}{suffix}").unlink(missing_ok=True)
    print(f"naming: {write_names(index, set(todo))} rows; decompiling {len(todo)} of {len(targets)}")
    TARGETS.write_text("".join(f"{va:#x}\n" for va in todo))
    started = time.time()
    output = headless(["-process", PROGRAM, "-noanalysis", "-scriptPath", str(SCRIPTS),
                       "-postScript", "wb_decompile.java", str(NAMES), str(TARGETS), str(OUT_DIR),
                       str(args.timeout)], GHIDRA_DIR / "decompile.log")
    summary = re.findall(r"wb_decompile: .*", output)
    print("\n".join(summary) if summary else "no summary line; see build/wb/ghidra/decompile.log")
    report(todo, time.time() - started)


def report(todo, seconds):
    """Success rate and wall time per function for this run."""
    ok = sum((OUT_DIR / f"{va:#x}.c").exists() for va in todo)
    print(f"{ok}/{len(todo)} decompiled ({100 * ok / len(todo):.1f}%), "
          f"{seconds:.0f}s wall incl. Ghidra startup, {seconds / len(todo):.2f}s/function")


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)
    sub.add_parser("import", help="import and analyse worldbuilder.exe (once)")
    runner = sub.add_parser("run", help="name and decompile WB functions")
    runner.add_argument("--vas", nargs="+", help="WB VAs to decompile (default: all matched)")
    runner.add_argument("--gd", action="store_true", help="--vas are game.dat targets (as tools/wb_show.py)")
    runner.add_argument("--limit", type=int, help="decompile at most N pending targets")
    runner.add_argument("--timeout", type=int, default=60, help="seconds per function (default 60)")
    runner.add_argument("--force", action="store_true", help="redo targets already decompiled")
    args = parser.parse_args(argv)
    if args.command == "import":
        import_program()
    else:
        run(args)


if __name__ == "__main__":
    main()
