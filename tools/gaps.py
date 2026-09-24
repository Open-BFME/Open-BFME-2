"""Unclaimed .text regions, with the 0xCC padding counted separately.

The headline coverage number is measured against the whole section, but a large
part of what it calls unmatched is inter-function padding rather than code.
This separates the two. tools/gap_owner.py then names the translation unit that
owns each remaining gap.

Run from the repo root: python3 tools/gaps.py
"""
import csv

import build


def padding_split(chunk):
    """Return (0xCC padding bytes, real bytes) for a slice of .text.

    Padding is 0xCC and nothing else. Zero bytes look like filler in a hex dump
    but are ordinary operands and jump-table entries inside real code, so
    discounting them too would shrink the denominator by another megabyte and
    silently inflate every coverage percentage measured against it.
    """
    pad = chunk.count(0xCC)
    return pad, len(chunk) - pad


def main():
    # Bounds and bytes come from the build gate's PE parser: ledger rows are
    # RVAs, and .text's file offset is not its RVA.
    data, sections = build.exe_image()
    text = next(s for s in sections if s['name'] == '.text')
    TEXT_START = text['rva']
    TEXT_END = TEXT_START + text['size']

    iv = []
    for r in csv.DictReader(open('reverse/functions.csv', newline='')):
        if r['status'] != 'matched':
            continue
        s = int(r['target_rva'], 16)
        iv.append((s, s + int(r['target_size'])))
    iv.sort()
    merged = []
    for s, e in iv:
        if merged and s <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], e)
        else:
            merged.append([s, e])

    gaps = []
    prev = TEXT_START
    for s, e in merged:
        if s > prev:
            gaps.append((prev, s))
        prev = max(prev, e)
    if prev < TEXT_END:
        gaps.append((prev, TEXT_END))

    scored = []
    total_pad = 0
    for s, e in gaps:
        chunk = build.read_pe_bytes(data, sections, s, e - s)
        pad, real = padding_split(chunk)
        total_pad += pad
        if real > 0:
            scored.append((real, s, e, len(chunk)))
    scored.sort(reverse=True)

    print(f"gaps: {len(gaps)}   0xCC bytes inside gaps: {total_pad:,}")
    print(f"real unclaimed code bytes: {sum(x[0] for x in scored):,}")
    print("\nlargest gaps by REAL (non-0xCC) bytes:")
    for real, s, e, span in scored[:20]:
        print(f"  real={real:>8,}  span={span:>8,}  0x{s:06X} .. 0x{e:06X}")


if __name__ == '__main__':
    main()
