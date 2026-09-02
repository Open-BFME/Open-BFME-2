"""List vtable slots that hold a body the ledger has never seen.

Virtuals are invisible to caller-based discovery: every call goes through a
slot, so callers_of.py finds nothing and they never enter the candidate pool
- not even as gen placeholders. But a vtable whose other slots are already
named tells you both that the address is a function and which class it
belongs to, and that is usually enough to name it from the worker it calls.

This walks the image for runs of consecutive words that all look like .text
addresses, keeps the runs where at least one slot is already named, and
prints the slots in them that have no ledger row. Long runs of small
addresses are also how jump tables and relocation blocks look, so treat the
output as candidates to read, not as conclusions.

Usage: python3 tools/vtable_gaps.py [--min-run 3]
"""
import argparse, csv, pathlib, struct, sys

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import build

BASE = 0x400000


def ledger():
    known = {}
    for path in ("reverse/functions.csv", "reverse/symbols.csv"):
        for row in csv.DictReader(open(path, newline="", encoding="utf-8-sig")):
            text = row.get("target_rva") or row.get("address")
            try:
                known.setdefault(int(text, 16), row["name"])
            except (TypeError, ValueError):
                continue
    return known


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--min-run", type=int, default=3)
    parser.add_argument("--max-run", type=int, default=40)
    parser.add_argument("--min-named", type=float, default=0.5,
                        help="fraction of the run that must already be named")
    args = parser.parse_args()

    known = ledger()
    data, sections = build.exe_image()
    text_lo, text_hi = 0x1000, 0x760000

    def is_text(word):
        rva = word - BASE
        return text_lo <= rva < text_hi

    runs, run = [], []
    for off in range(0, len(data) - 4, 4):
        word = struct.unpack("<I", data[off : off + 4])[0]
        if is_text(word):
            run.append(word - BASE)
        else:
            if len(run) >= args.min_run:
                runs.append(run)
            run = []
    if len(run) >= args.min_run:
        runs.append(run)

    total = 0
    for run in runs:
        named = [r for r in run if r in known]
        gaps = [r for r in run if r not in known]
        if not named or not gaps:
            continue
        if len(run) > args.max_run:
            continue
        if len(named) / len(run) < args.min_named:
            continue
        total += len(gaps)
        print(f"run of {len(run)} slots, {len(named)} named, {len(gaps)} unknown")
        for rva in run:
            mark = "    " if rva in known else "  ??"
            print(f"  {mark} {rva:#010x} {known.get(rva, '')[:72]}")
    print(f"{total} unnamed slot(s) in vtable-shaped runs that carry a named slot")


if __name__ == "__main__":
    main()
