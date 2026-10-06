#!/usr/bin/env python3
"""Region default code-generation flags, and the tool-owned overrides list.

The game was built per project, not per file: research/25 fingerprinted the
retail image and found 48 flag regions in BFME2 (GameEngine + GameEngineDevice
are /O1 /arch:SSE /G7, WW3D2 is /O2 /arch:SSE /G7, WWLib/WWDebug and the
third-party block /O2 blend, DirtySock /O2 /G7). The `// cl:` lines in Code/
were instead fitted file by file: 14,768 of them disagree with their region,
and almost all of those disagreements are inert. /G7 in particular is nearly
invisible in /O1 function bodies, so nobody fitted it, and the static-guard
funclets (`and al,0FEh` in retail, `and eax,-2` without /G7) were wrong
everywhere the gate does not look.

So the build now takes the code-generation flags of a Code/ translation unit
from its region:

  reverse/retail_inventory/flag_regions.csv
                              written by tools/retail_inventory.py from the
                              image. Retail RVA ranges -> opt/arch/tune; a `?`
                              dimension is resolved by region_flags() below.
  reverse/flag_overrides.csv  tool-owned. Sources whose `// cl:` codegen flags
                              still count, because the region default loses a
                              row that their own flags match.

A TU's region is the voting region holding most of its matched rows' bytes.
"Codegen flags" means exactly MANAGED below (/O*, /arch:*, /G5-7/GB). Every
other `// cl:` token -- /D, /I, /MD, /EH*, /GX, /Ob*, /Oy- -- is passed through
unchanged; /EH variants cannot be fingerprinted from code (research/25 s.4).

An override is never typed by hand. `propose SOURCE` compiles the source under
its region default and under its own flags and records an override only when
the default loses a row its own flags match; `generate` + `overrides` do the
same for the whole tree. `check` (pre-commit) fails when an overridden file's
`// cl:` codegen flags drift from the recorded ones.

FLAG_DEFAULTS=off restores the old behaviour (every `// cl:` line counts).
"""
import argparse
import bisect
import contextlib
import csv
import json
import os
import re
import sys
import threading
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REGIONS = ROOT / "reverse" / "retail_inventory" / "flag_regions.csv"
OVERRIDES = ROOT / "reverse" / "flag_overrides.csv"
FUNCTIONS = ROOT / "reverse" / "functions.csv"
SCAN_DIR = ROOT / "build" / "flagscan"

MANAGED = re.compile(r"[-/](?:O[12xstdg]|arch:SSE2?|G[567B])$")
MANAGED_IN_LINE = re.compile(r"(?<!\S)[-/](?:O[12xstdg]|arch:SSE2?|G[567B])(?!\S)")
SOURCE_SUFFIXES = (".c", ".cpp")
OVERRIDE_FIELDS = ["source", "flags", "rows", "default_lost", "reason"]
CL_PLACEHOLDER = "// flags: region default (reverse/retail_inventory/flag_regions.csv)"

# The mode a compile runs in, per thread: build.py's pool compiles in threads
# and `generate` runs one pass at a time, so a thread-local is enough.
#   normal  -- region default unless the source is in flag_overrides.csv
#   current -- the `// cl:` line as written (the pre-region behaviour)
#   default -- region default, ignoring overrides (what `generate` tests)
#   g7      -- the `// cl:` line plus /G7 where the region is /G7 (the pilot)
_mode = threading.local()


@contextlib.contextmanager
def forced_mode(mode):
    previous = getattr(_mode, "value", None)
    _mode.value = mode
    try:
        yield
    finally:
        _mode.value = previous


def current_mode():
    value = getattr(_mode, "value", None)
    if value:
        return value
    return "current" if os.environ.get("FLAG_DEFAULTS", "on") == "off" else "normal"


def region_tokens(region):
    tokens = ["-" + region["opt"]]
    if region["arch"] in ("SSE", "SSE2"):
        tokens.append("-arch:" + region["arch"])
    if region["tune"] == "G7":
        tokens.append("-G7")
    return tokens


def managed_tokens(flags):
    return [flag for flag in flags if MANAGED.match(flag)]


def _norm(flags):
    return " ".join(f.replace("/", "-", 1) if f.startswith("/") else f for f in flags)


def _rel(source):
    try:
        return Path(os.path.abspath(source)).relative_to(ROOT).as_posix()
    except ValueError:
        return None


def managed_source(rel):
    return rel.startswith("Code/") and rel.lower().endswith(SOURCE_SUFFIXES)


_cache = {}
_cache_lock = threading.RLock()


def _cached(key, loader):
    with _cache_lock:
        if key not in _cache:
            _cache[key] = loader()
        return _cache[key]


def resolve_region(row):
    """A flag_regions.csv row with every dimension decided, plus `vote`.

    An unknown dimension inherits the project default for its opt level
    (research/25 s.3): /O1 code is the GameEngine set (/arch:SSE /G7), /O2
    code the library blend (x87, no /G7). `.text$x` funclets and byte-dump
    islands carry almost no opt evidence, so a region votes on which region
    a TU sits in only with 3+ opt votes over at least 5% of its functions."""
    row = dict(row)
    if row["arch"] == "?":
        row["arch"] = "SSE" if row["opt"] == "O1" else "x87"
    if row["tune"] == "?":
        row["tune"] = "G7" if row["opt"] == "O1" else "G6"
    evidence, funcs = int(row["n_opt_evidence"]), int(row["n_funcs"])
    row["vote"] = "1" if evidence >= 3 and evidence >= 0.05 * funcs else "0"
    return row


def _load_regions():
    rows = []
    if REGIONS.exists():
        with REGIONS.open(newline="", encoding="utf-8") as handle:
            for raw in csv.DictReader(handle):
                row = resolve_region(raw)
                rows.append((int(row["rva_start"], 16), int(row["rva_end"], 16), row))
    rows.sort(key=lambda item: item[0])
    return rows


def regions():
    return _cached("regions", _load_regions)


def region_at(rva):
    table = regions()
    starts = _cached("starts", lambda: [start for start, _end, _row in table])
    index = bisect.bisect_right(starts, rva) - 1
    if index >= 0 and rva <= table[index][1]:
        return table[index][2]
    return None


def _flag_set(region):
    return (region["opt"], region["arch"], region["tune"])


def _load_source_regions():
    """{source: region row}: the voting flag set holding most matched bytes."""
    weights = {}
    with FUNCTIONS.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            source = row["source"]
            if row["status"] != "matched" or not managed_source(source):
                continue
            try:
                rva, size = int(row["target_rva"], 16), int(row["target_size"])
            except ValueError:
                continue
            region = region_at(rva)
            if region is None or region["vote"] != "1":
                continue
            per_set = weights.setdefault(source, {})
            key = _flag_set(region)
            if key not in per_set:
                per_set[key] = [0, region]
            per_set[key][0] += size
    return {source: max(sorted(per_set.items()), key=lambda item: item[1][0])[1][1]
            for source, per_set in weights.items()}


def source_region(rel):
    if not REGIONS.exists():
        return None
    return _cached("sources", _load_source_regions).get(rel)


def _load_overrides():
    if not OVERRIDES.exists():
        return {}
    with OVERRIDES.open(newline="", encoding="utf-8") as handle:
        return {row["source"]: row for row in csv.DictReader(handle)}


def overrides():
    return _cached("overrides", _load_overrides)


def apply(source, flags):
    """The `// cl:` flags (already '-' style) a compile of `source` really uses."""
    mode = current_mode()
    if mode == "current":
        return flags
    rel = _rel(source)
    if rel is None or not managed_source(rel):
        return flags
    region = source_region(rel)
    if region is None:
        return flags
    if mode == "normal" and rel in overrides():
        return flags
    if mode == "g7":
        return flags if region["tune"] != "G7" or "-G7" in flags else flags + ["-G7"]
    return region_tokens(region) + [flag for flag in flags if not MANAGED.match(flag)]


# ---------------------------------------------------------------- the `// cl:` line

def read_cl_line(path):
    """The first `// cl:` line build.py reads, or None."""
    text = path.read_text(encoding="utf-8-sig", errors="replace")
    for line in text.splitlines():
        if line.startswith("// cl:"):
            return line
    return None


def cl_managed(path):
    line = read_cl_line(path)
    if line is None:
        return ""
    return _norm(tok for tok in line[len("// cl:"):].split() if MANAGED.match(tok))


def strip_line(line):
    """`line` without its codegen tokens; the placeholder if nothing is left.
    The line itself stays, so __LINE__ in every body below keeps its value."""
    rest = " ".join(MANAGED_IN_LINE.sub("", line[len("// cl:"):]).split())
    return f"// cl: {rest}" if rest else CL_PLACEHOLDER


# ---------------------------------------------------------------- scanning

def _matched_rows_by_source():
    by_source = {}
    with FUNCTIONS.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row["status"] == "matched" and managed_source(row["source"]):
                by_source.setdefault(row["source"], []).append(row)
    return by_source


def row_key(row):
    return f"{row['name']}@{row['target_rva']}"


def scan_source(build, rel, rows, symbol_map, pass_dir, mode):
    """Compile `rel` in `mode` into `pass_dir` and byte-compare its rows."""
    source = ROOT / rel
    output = pass_dir / build.obj_path(source).name
    started = time.time()
    # build imports its own copy of this module; a `python3 tools/flag_defaults.py`
    # run is __main__, so the mode must be set on build's copy.
    with build.flag_defaults.forced_mode(mode):
        command, _env = build.compiler_command(source, output)
        ok, text, _code = build.try_compile_source(source, output)
    flags = command[command.index("-EHsc-") + 1:-2] if "-EHsc-" in command else []
    record = {"source": rel, "mode": mode, "flags": _norm(managed_tokens(flags)),
              "compiled": ok, "rows": len(rows), "fail": []}
    if not ok:
        record["error"] = text[-300:]
    else:
        for row in rows:
            try:
                patch = build.compile_function(row, symbol_map, output)
                thin = patch["masked"] and patch["concrete"] < build.MIN_LIB_CONCRETE
                good = patch["bytes"] == patch["target"] and not thin
            except (ValueError, SystemExit):
                good = False
            if not good:
                record["fail"].append(row_key(row))
    record["secs"] = round(time.time() - started, 2)
    return record


def load_scan(name):
    path = SCAN_DIR / f"{name}.jsonl"
    records = {}
    if path.exists():
        with path.open(encoding="utf-8") as handle:
            for line in handle:
                if line.strip():
                    record = json.loads(line)
                    records[record["source"]] = record
    return records


def run_scan(name, mode, sources=None, pool=8):
    import concurrent.futures
    os.environ["BFME_OBJSTORE"] = "off"  # never put experiment objects in the shared store
    sys.path.insert(0, str(ROOT / "tools"))
    import build
    by_source = _matched_rows_by_source()
    wanted = [rel for rel in sorted(by_source) if source_region(rel) is not None]
    if mode == "g7":
        wanted = [rel for rel in wanted if source_region(rel)["tune"] == "G7"]
    if sources is not None:
        wanted = [rel for rel in wanted if rel in sources]
    done = load_scan(name)
    todo = [rel for rel in wanted if rel not in done]
    print(f"{name}: {len(wanted)} source(s), {len(done)} already scanned, {len(todo)} to go",
          flush=True)
    symbol_map = build.load_symbol_map()
    pass_dir = SCAN_DIR / name
    pass_dir.mkdir(parents=True, exist_ok=True)
    started = time.time()
    with (SCAN_DIR / f"{name}.jsonl").open("a", encoding="utf-8") as out, \
            concurrent.futures.ThreadPoolExecutor(pool) as executor:
        futures = [executor.submit(scan_source, build, rel, by_source[rel], symbol_map,
                                   pass_dir, mode) for rel in todo]
        for count, future in enumerate(concurrent.futures.as_completed(futures), 1):
            out.write(json.dumps(future.result()) + "\n")
            out.flush()
            if count % 500 == 0:
                print(f"  {count}/{len(todo)} in {time.time() - started:.0f}s", flush=True)
    print(f"{name}: done in {time.time() - started:.0f}s", flush=True)
    return load_scan(name)


def decide(current, default):
    """None when the region default keeps every row `current` matches, else
    (rows_lost, reason): the source needs an override."""
    if not current["compiled"]:
        return None
    if not default["compiled"]:
        return current["rows"] - len(current["fail"]), "region default does not compile"
    lost = set(default["fail"]) - set(current["fail"])
    return (len(lost), "region default loses rows") if lost else None


def write_overrides(entries):
    with OVERRIDES.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=OVERRIDE_FIELDS, lineterminator="\n")
        writer.writeheader()
        for source in sorted(entries):
            writer.writerow(entries[source])
    _cache.pop("overrides", None)


def override_entry(current, verdict):
    lost, reason = verdict
    return {"source": current["source"], "flags": current["flags"], "rows": current["rows"],
            "default_lost": lost, "reason": reason}


# ---------------------------------------------------------------- commands

def cmd_generate(args):
    sources = None
    if args.sources:
        with open(args.sources, encoding="utf-8") as handle:
            sources = {line.strip() for line in handle if line.strip()}
    run_scan(args.name, args.mode, sources, args.pool)


def cmd_overrides(args):
    current, default = load_scan(args.current), load_scan(args.default)
    entries, redundant, undecided = {}, 0, []
    for source, record in default.items():
        if record["compiled"] and not record["fail"]:
            redundant += 1
            continue
        if source not in current:
            undecided.append(source)
            continue
        verdict = decide(current[source], record)
        if verdict is None:
            redundant += 1
        else:
            entries[source] = override_entry(current[source], verdict)
    write_overrides(entries)
    print(f"region default reproduces every row of {redundant} source(s); "
          f"{len(entries)} override(s) written; {len(undecided)} undecided")
    for source in undecided[:20]:
        print(f"  undecided (no current-flag scan): {source}")
    return 1 if undecided else 0


def cmd_propose(args):
    os.environ["BFME_OBJSTORE"] = "off"
    sys.path.insert(0, str(ROOT / "tools"))
    import build
    by_source = _matched_rows_by_source()
    symbol_map = build.load_symbol_map()
    entries = dict(overrides())
    pass_dir = SCAN_DIR / "propose"
    pass_dir.mkdir(parents=True, exist_ok=True)
    for rel in args.sources:
        rel = _rel(ROOT / rel) or rel
        if rel not in by_source or source_region(rel) is None:
            print(f"{rel}: no matched rows in a flag region; its `// cl:` line counts as written")
            continue
        default = scan_source(build, rel, by_source[rel], symbol_map, pass_dir, "default")
        current = scan_source(build, rel, by_source[rel], symbol_map, pass_dir, "current")
        verdict = decide(current, default)
        if verdict is None:
            entries.pop(rel, None)
            print(f"{rel}: region default ({default['flags']}) keeps every row; no override")
        else:
            entries[rel] = override_entry(current, verdict)
            print(f"{rel}: override '{current['flags']}' -- {verdict[1]} ({verdict[0]})")
    write_overrides(entries)


def cmd_prune(_args):
    """Drop overrides whose source is gone or no longer sits in a region."""
    entries = dict(overrides())
    gone = [s for s in entries if not (ROOT / s).exists() or source_region(s) is None]
    for source in gone:
        del entries[source]
        print(f"  dropped {source}")
    write_overrides(entries)
    print(f"pruned {len(gone)} stale override(s); {len(entries)} remain")


def cmd_check(_args):
    """Every override's `// cl:` codegen flags still equal the recorded ones."""
    bad = 0
    for source, entry in sorted(overrides().items()):
        path = ROOT / source
        if not path.exists():
            print(f"  {source}: listed in reverse/flag_overrides.csv but missing")
            bad += 1
            continue
        flags = cl_managed(path)
        if flags != entry["flags"]:
            print(f"  {source}: `// cl:` codegen flags are '{flags}' but "
                  f"reverse/flag_overrides.csv records '{entry['flags']}'. Run "
                  f"`python3 tools/flag_defaults.py propose {source}`; never edit either by hand.")
            bad += 1
    if bad:
        print(f"Flag overrides: FAIL {bad}")
        return 1
    print(f"Flag overrides: OK {len(overrides())}")
    return 0


def cmd_strip(args):
    """Drop codegen tokens from `// cl:` lines the region default reproduces."""
    verified = None
    if args.scan:
        verified = {s for s, r in load_scan(args.scan).items() if r["compiled"] and not r["fail"]}
    changed = 0
    for rel in sorted(_matched_rows_by_source()):
        if not rel.startswith(args.dir) or source_region(rel) is None or rel in overrides():
            continue
        if verified is not None and rel not in verified:
            continue
        path = ROOT / rel
        lines = path.read_bytes().split(b"\n")
        for index, raw in enumerate(lines):
            body = raw[3:] if index == 0 and raw.startswith(b"\xef\xbb\xbf") else raw
            if not body.startswith(b"// cl:"):
                continue
            cr = body.endswith(b"\r")
            text = body.rstrip(b"\r").decode("utf-8", "surrogateescape")
            new = strip_line(text)
            if new != text:
                lines[index] = (raw[:len(raw) - len(body)] + new.encode("utf-8", "surrogateescape")
                                + (b"\r" if cr else b""))
                path.write_bytes(b"\n".join(lines))
                changed += 1
            break
    print(f"stripped codegen flags from {changed} `// cl:` line(s)")


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = parser.add_subparsers(dest="command", required=True)
    p = sub.add_parser("generate", help="compile and compare every region source in one mode")
    p.add_argument("name")
    p.add_argument("--mode", choices=["current", "default", "g7", "normal"], required=True)
    p.add_argument("--pool", type=int, default=8)
    p.add_argument("--sources", help="file listing the sources to scan")
    p = sub.add_parser("overrides", help="write reverse/flag_overrides.csv from two scans")
    p.add_argument("--current", required=True)
    p.add_argument("--default", required=True)
    p = sub.add_parser("propose", help="decide the override for named sources")
    p.add_argument("sources", nargs="+")
    sub.add_parser("check", help="override flags still equal their `// cl:` lines")
    sub.add_parser("prune", help="drop overrides for sources that are gone")
    p = sub.add_parser("strip", help="drop redundant codegen tokens from `// cl:` lines")
    p.add_argument("--dir", default="Code/")
    p.add_argument("--scan", help="only sources this default-mode scan proved green")
    args = parser.parse_args(argv)
    handler = {"generate": cmd_generate, "overrides": cmd_overrides,
               "propose": cmd_propose, "check": cmd_check, "prune": cmd_prune, "strip": cmd_strip}[args.command]
    return handler(args) or 0


if __name__ == "__main__":
    sys.exit(main())
