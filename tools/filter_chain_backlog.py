"""List the retail functions that build a BFME2 partition filter chain.

A chain is built by REL32 calls to `PartitionFilter::link` (0x00625790, the
`Rva000421C8` view in AIStructureCreepTactic.cpp), so every function holding
such a call is a candidate for the shared filter-chain view. The containing
function is the nearest Ghidra or ledger start at or before the call site whose
extent covers it.

Each line gives the function RVA, its size, the number of link calls, its
ledger state (CPP for a clean source row, GEN for a gen-* / gen_asm placeholder,
- for no row), the latest reverse/re_attempts.log verdict (partial with its
score, blocked, ...), the source path when one exists, and the __FILE__
basename any assert in the body pushes (retail keeps them, so it names the
unit).

Usage:
    python3 tools/filter_chain_backlog.py            # unmatched, cheapest first
    python3 tools/filter_chain_backlog.py --all      # matched too
    python3 tools/filter_chain_backlog.py --csv      # machine-readable
"""
import bisect
import csv
import re
import struct
import sys

from callers_of import load_image, make_off, file_literal

LINK = 0x00625790


def load_starts():
    """RVA -> size over Ghidra's inventory, overridden by ledger rows."""
    sizes = {}
    for r in csv.DictReader(open('reverse/ghidra_functions.csv', newline='')):
        try:
            sizes[int(r['rva'], 16)] = int(r['size'])
        except ValueError:
            continue
    rows = {}
    for r in csv.DictReader(open('reverse/functions.csv', newline='')):
        try:
            rva = int(r['target_rva'], 16)
            size = int(r['target_size'] or 0)
        except (ValueError, KeyError):
            continue
        sizes[rva] = size
        rows.setdefault(rva, r)
    return sizes, rows


def load_verdicts():
    """RVA -> latest re_attempts.log verdict, with the score for partials."""
    out = {}
    for line in open('reverse/re_attempts.log', encoding='utf-8', errors='replace'):
        f = line.rstrip('\n').split('\t')
        if len(f) < 4 or not f[1].startswith('0x'):
            continue
        try:
            rva = int(f[1], 16)
        except ValueError:
            continue
        verdict = f[3]
        if verdict == 'partial':
            m = re.search(r'score=([0-9.]+)', line)
            if m:
                verdict += '=' + m.group(1)
        out[rva] = verdict
    return out


def state_of(row):
    if row is None:
        return '-'
    src = row['source']
    if row['name'].startswith('gen-') or '/gen_asm/' in src or '/gen_small/' in src:
        return 'GEN'
    return 'CPP'


def main():
    args = sys.argv[1:]
    data, secs = load_image()
    off = make_off(secs)
    text = next(s for s in secs if s[0] <= LINK < s[0] + s[1])
    va, vsz, raw = text
    body = data[raw:raw + vsz]
    sizes, rows = load_starts()
    order = sorted(sizes)

    funcs = {}
    i = 0
    while True:
        i = body.find(b'\xe8', i, len(body) - 4)
        if i < 0:
            break
        site = va + i
        if site + 5 + struct.unpack_from('<i', body, i + 1)[0] == LINK:
            k = bisect.bisect_right(order, site) - 1
            if k >= 0 and site < order[k] + sizes[order[k]]:
                funcs[order[k]] = funcs.get(order[k], 0) + 1
            else:
                print('call at 0x%08X lies in no known function' % site, file=sys.stderr)
        i += 1

    verdicts = load_verdicts()
    out = []
    for rva, n in funcs.items():
        row = rows.get(rva)
        state = state_of(row)
        if state == 'CPP' and '--all' not in args:
            continue
        out.append((sizes[rva], rva, n, state, verdicts.get(rva, ''),
                    row['source'] if row else '',
                    file_literal(data, off, rva, sizes[rva]) or ''))
    out.sort()
    total = len(funcs)
    done = sum(1 for r in funcs if state_of(rows.get(r)) == 'CPP')
    if '--csv' in args:
        w = csv.writer(sys.stdout)
        w.writerow(['rva', 'size', 'links', 'state', 'verdict', 'source', 'file_literal'])
        for size, rva, n, state, verdict, src, lit in out:
            w.writerow(['0x%08X' % rva, size, n, state, verdict, src, lit])
        return
    for size, rva, n, state, verdict, src, lit in out:
        print('0x%08X %6d  links=%-2d %-3s %-12s %s %s' % (rva, size, n, state, verdict, src, lit))
    print('%d functions build a filter chain; %d have clean source, %d bytes outstanding'
          % (total, done, sum(r[0] for r in out if r[3] != 'CPP')), file=sys.stderr)


if __name__ == '__main__':
    main()
