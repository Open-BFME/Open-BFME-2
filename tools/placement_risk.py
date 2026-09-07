#!/usr/bin/env python3
"""Rank masked-search placements by how little corroborates them.

A masked whole-.text search proves that a body's fixed bytes occur exactly once.
That is not the same as proving the NAME on those bytes.  Five rows were found
wrong this way in one session, and every one of them shared a shape:

  * the address is not 16-byte aligned -- real function starts nearly always are;
  * the byte after the body is not 0xCC -- a real body is usually followed by
    the padding that aligns the next one;
  * nothing else in the ledger is claimed anywhere near it -- a real body sits
    among the siblings its translation unit emitted beside it.

Each of those alone is weak: mid-block bodies abut their neighbours legitimately,
and a unit's first landing has no neighbours yet.  Together they mean the bytes
were found inside something else.  `?Get_Width@SegmentedLineClass` had been
placed at 0x00133D90, which is the third slot in CameraClass's getter row.

This reports the rows carrying that shape, worst first.  It PROVES NOTHING --
every row here byte-verifies, which is exactly the problem, since seven bytes of
load-and-return byte-verify anywhere those seven bytes occur.  Treat it as a
list to re-check when a header or layout change gives you a reason to, and note
that the check that actually settles one is a rebuild under a corrected layout:
a real placement follows its class, a coincidence does not.

  python3 tools/placement_risk.py [--limit N] [--all-notes]
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

PLACED = ("placed by masked", "unique masked placement", "masked byte-scan")
NEIGHBOURHOOD = 0x200


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--limit", type=int, default=40)
    parser.add_argument("--all-notes", action="store_true",
                        help="include rows whose notes do not mention a masked search")
    args = parser.parse_args()

    rows = build.load_all_function_rows()
    starts = sorted(int(r["target_rva"], 16) for r in rows)

    def neighbours(rva, size):
        lo, hi = rva - NEIGHBOURHOOD, rva + size + NEIGHBOURHOOD
        return sum(1 for s in starts if lo <= s <= hi and s != rva)

    scored = []
    for row in rows:
        note = row["notes"].lower()
        if not args.all_notes and not any(p in note for p in PLACED):
            continue
        rva = int(row["target_rva"], 16)
        size = int(row["target_size"])
        try:
            padded = build.read_target_bytes(rva + size, 1)[0] == 0xCC
        except Exception:
            padded = True
        near = neighbours(rva, size)
        risk = (0 if rva % 16 == 0 else 2) + (0 if padded else 1) + (0 if near else 2)
        if risk >= 3:
            scored.append((risk, -1 if size > 32 else size, rva, size, near,
                           padded, row["name"], row["source"]))

    scored.sort(key=lambda s: (-s[0], s[1]))
    print(f"{'risk':>4} {'size':>6}  address     near  pad  source")
    for risk, _, rva, size, near, padded, name, src in scored[:args.limit]:
        print(f"{risk:4d} {size:6d}  0x{rva:08X}  {near:4d}  "
              f"{'y' if padded else 'n'}    {src}")
        print(f"                {name[:104]}")
    print(f"\n{len(scored)} row(s) of {len(rows)} carry the shape "
          f"(showing {min(args.limit, len(scored))})")
    print("Nothing here is a defect on its own; re-check when a layout change "
          "gives you a reason to.")


if __name__ == "__main__":
    main()
