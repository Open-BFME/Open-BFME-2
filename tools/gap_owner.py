#!/usr/bin/env python3
"""Name the translation unit that owns an unclaimed region of .text.

`gaps` in the image are just addresses, which makes them useless as a work
queue: you cannot pick up "0x00273DCE, 33,685 bytes" the way you can pick up a
source file. But retail kept the assert and DEBUG_LOG file-name strings, and
they are absolute paths out of the original build tree --

    F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate.cpp

-- so a gap whose code pushes one of those addresses is that file's code, named
by the binary itself rather than by inference. That turns the gap list into a
per-file worklist.

Two things to know about the coverage it gives.

It is sparse: a release build keeps only the asserts that survived, so most
gaps reference no path at all and stay anonymous. Silence is not evidence that
a region is uninteresting.

And the biggest gaps are anonymous for a reason. Everything between roughly
0x9A0000 and 0xB00000 is statically linked Microsoft middleware, not game code:
0xAC8183 (216KB) is the DirectX error-string tables (`E_ABORT`, the `CO_E_*`
and `DIERR_*` families), and 0xA40673 (93KB) is the D3DX shader assembler
(`POSITION`, `BLENDWEIGHT`, `TESSFACTOR`, "internal error: unknown node").
Those are the top of every gap ranking and none of them is worth a cycle.

Usage:
  python3 tools/gap_owner.py                 # gaps over 8000 real bytes
  python3 tools/gap_owner.py --min 2000
  python3 tools/gap_owner.py --source AIUpdate.cpp    # only gaps naming this
"""
import argparse
import csv
import re
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

IMAGE_BASE = 0x400000
PADDING = 0xCC

# An absolute path ending in a source-file extension, as MSVC's __FILE__ emits.
SOURCE_PATH = re.compile(rb'[A-Za-z]:\\[^\x00]{4,150}?\.(?:cpp|c|h|inl)', re.IGNORECASE)


def unclaimed_gaps(text_lo, text_hi):
    """Ranges of .text that no ledger row covers, claimed rows merged first."""
    spans = []
    for row in build.load_all_function_rows():
        try:
            start = int(row["target_rva"], 16)
            size = int(row["target_size"])
        except (ValueError, TypeError):
            continue
        spans.append((start, start + size))
    spans.sort()

    merged = []
    for start, end in spans:
        if merged and start <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], end)
        else:
            merged.append([start, end])

    gaps = []
    cursor = text_lo
    for start, end in merged:
        if start > cursor:
            gaps.append((cursor, start))
        cursor = max(cursor, end)
    if cursor < text_hi:
        gaps.append((cursor, text_hi))
    return gaps


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--min", type=int, default=8000,
                        help="ignore gaps with fewer real (non-0xCC) bytes")
    parser.add_argument("--source", help="only report gaps naming this file")
    args = parser.parse_args()

    data = build.EXE.read_bytes()
    sections = build.pe_sections(data)
    text = next(s for s in sections if s["name"] == ".text")
    text_lo, text_hi = text["rva"], text["rva"] + text["size"]

    def string_at(rva):
        """The NUL-terminated string at an RVA, if it is a source path."""
        try:
            offset = build.rva_to_file_offset(sections, rva)
        except ValueError:
            return None
        match = SOURCE_PATH.match(data[offset:offset + 200])
        return match.group(0).decode("ascii", "replace") if match else None

    reports = []
    for lo, hi in unclaimed_gaps(text_lo, text_hi):
        blob = data[lo:hi]
        real = len(blob) - blob.count(PADDING)
        if real < args.min:
            continue
        owners = {}
        cursor = lo
        while cursor < hi - 5:
            opcode = data[cursor]
            # push imm32, and mov r32,imm32 -- the two ways a string address
            # reaches an assert call
            if opcode == 0x68 or 0xB8 <= opcode <= 0xBF:
                value = struct.unpack_from("<I", data, cursor + 1)[0]
                if IMAGE_BASE < value < IMAGE_BASE + 0x2000000:
                    path = string_at(value - IMAGE_BASE)
                    if path:
                        owners[path] = owners.get(path, 0) + 1
            cursor += 1
        reports.append((real, lo, hi, owners))

    reports.sort(reverse=True)
    if args.source:
        needle = args.source.lower()
        reports = [r for r in reports if any(needle in p.lower() for p in r[3])]

    total = sum(r[0] for r in reports)
    named = sum(r[0] for r in reports if r[3])
    print("gaps over %d real bytes: %d  (%s real bytes, %s in gaps with a named source)"
          % (args.min, len(reports), f"{total:,}", f"{named:,}"))
    print()
    for real, lo, hi, owners in reports:
        ranked = sorted(owners.items(), key=lambda kv: -kv[1])[:3]
        label = "  ".join("%s (%dx)" % (p.split("\\")[-1], n) for p, n in ranked)
        print("  real=%9s  0x%06X..0x%06X  %s"
              % (f"{real:,}", lo, hi, label or "-- anonymous --"))

    per_source = {}
    for real, lo, hi, owners in reports:
        if not owners:
            continue
        best = max(owners.items(), key=lambda kv: kv[1])[0]
        per_source[best] = per_source.get(best, 0) + real
    if per_source:
        print("\nunclaimed real bytes by owning source:")
        for path, count in sorted(per_source.items(), key=lambda kv: -kv[1]):
            print("  %9s  %s" % (f"{count:,}", path))


if __name__ == "__main__":
    main()
