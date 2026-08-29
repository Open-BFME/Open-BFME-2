#!/usr/bin/env python3
"""Land the drift report's `exact-ambiguous` functions: byte-identical template copies
locate.py refuses (unique-placement rule), disambiguated here by their string anchor.

Safety: only rows whose function carries a ??_C@ string DIR32 are emitted — the build's
verify_string_refs gate then PROVES the copy assignment (a wrong copy references the
wrong string content and fails the build loudly). Copies with no string reference stay
unassigned: byte-identical + anchorless means no evidence says which address is whose.

Usage: python3 tools/land_ambiguous.py [--report reverse/zh_sweep/drift_report.csv]
"""
import argparse
import csv
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build
import ledger_io
from locate import object_functions
from portable_lock import lock, unlock

ROOT = build.ROOT
LOCK_FILE = ROOT / "reverse" / ".add_match.lock"


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--report", default="reverse/zh_sweep/drift_report.csv")
    ap.add_argument("--src-dir", default="Code")
    args = ap.parse_args()

    # The Ghidra inventory is gitignored, so a fresh clone does not have it and
    # this tool is the first rung of the work ladder. Say which file is missing
    # and how to make it instead of dying on an unhandled FileNotFoundError.
    inventory = ROOT / "reverse" / "ghidra_functions.csv"
    if not inventory.exists():
        raise SystemExit(
            f"{inventory.relative_to(ROOT).as_posix()} not found — this tool needs the Ghidra\n"
            "inventory to size the candidate copies. It is a generated, gitignored file;\n"
            "regenerate it per tools/ghidra/README.md, or pick another rung of the ladder\n"
            "(python3 tools/next_work.py)."
        )

    ghidra = {}
    with inventory.open(newline="") as fh:
        for row in csv.DictReader(fh):
            ghidra[int(row["rva"], 16)] = int(row["size"])
    matched = {r["name"] for r in build.load_all_function_rows()}

    todo = []
    with (ROOT / args.report).open(newline="") as fh:
        for row in csv.DictReader(fh):
            if row["class"] == "exact-ambiguous" or (
                row["aligned_pct"] == "100" and row["first_diff"] == "-1" and row["candidate_rva"]
            ):
                todo.append(row)

    by_source = {}
    for row in todo:
        by_source.setdefault(row["source"], []).append(row)

    emitted_total = 0
    for cpp_name, rows in sorted(by_source.items()):
        # drift report stores bare basenames (often lowercased); resolve under Code/
        src = ROOT / args.src_dir / cpp_name
        if not src.exists():
            want = Path(cpp_name).name.lower()
            hits = [h for h in (ROOT / args.src_dir).rglob("*.cpp") if h.name.lower() == want]
            src = hits[0] if hits else src
        if not src.exists():
            print(f"{cpp_name}: missing source — skipped")
            continue
        # ensure object exists via compile
        try:
            obj = build.obj_path(src)
            build.compile_source(src, obj)
        except (SystemExit, Exception) as e:
            # compile_source raises SystemExit (not Exception) on a bad compile;
            # catch both so one broken sweep source doesn't abort the whole batch.
            print(f"{cpp_name}: compile failed — skipped ({e})")
            continue
        if not obj.exists():
            print(f"{cpp_name}: missing obj — skipped")
            continue
        rel_src = str(src.relative_to(ROOT)).replace("\\", "/")
        has_string = {}
        sizes = {}
        for name, span, relocs in object_functions(obj):
            has_string[name] = any(rt == 0x0006 and sym.startswith("??_C@")
                                   for _, rt, sym in relocs)
            sizes[name] = len(span.rstrip(b"\xcc"))
        new_rows = []
        for row in rows:
            name = row["function"]
            if name in matched:
                continue
            if not has_string.get(name):
                print(f"  SKIP {name[:60]}: no string anchor — copy assignment unprovable")
                continue
            rva = int(row["candidate_rva"], 16)
            size = ghidra.get(rva, sizes.get(name, 0))
            new_rows.append(f"{name},,0x{rva:08X},{size},{rel_src},matched,"
                            f"exact-ambiguous copy; assignment proven by verify_string_refs")
        if not new_rows:
            continue
        lock_handle = LOCK_FILE.open("a")
        lock(lock_handle, exclusive=True,
             wait_notice="land_ambiguous: waiting for the ledger lock...")
        functions_raw = build.FUNCTIONS.read_bytes()
        try:
            eol = ledger_io.lf_terminator(functions_raw, "functions.csv")
            with build.FUNCTIONS.open("ab") as fh:
                fh.write(b"".join(line.encode("utf-8") + eol for line in new_rows))
            verify = subprocess.run(
                [sys.executable, str(ROOT / "tools" / "build.py"), rel_src],
                cwd=ROOT, capture_output=True, text=True, timeout=420)
            if verify.returncode != 0:
                build.FUNCTIONS.write_bytes(functions_raw)
                print(f"{cpp_name}: byte-verify REJECTED the assignment — reverted "
                      f"({(verify.stdout.strip().splitlines() or ['?'])[-1]})")
                continue
        except BaseException:
            build.FUNCTIONS.write_bytes(functions_raw)
            raise
        finally:
            unlock(lock_handle)
            lock_handle.close()
        emitted_total += len(new_rows)
        print(f"{cpp_name}: +{len(new_rows)} exact-ambiguous landed "
              f"({(verify.stdout.strip().splitlines() or [''])[-1]})")
    print(f"\ntotal landed: {emitted_total}")


if __name__ == "__main__":
    main()
