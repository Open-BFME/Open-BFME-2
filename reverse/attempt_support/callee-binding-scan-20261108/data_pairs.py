"""Read-only: retail data addresses whose ledger names are defined as separate objects in one image: P55's shape. Sizes are the gap to the next symbol in the map.
usage: data_pairs.py IMAGE_DIR LEDGER_DIR OUT_TSV"""
import bisect
import collections
import csv
import re
import sys

image_dir, ledger, out = sys.argv[1:4]
csv.field_size_limit(10**8)
syms = collections.defaultdict(list)
objs = {}
MAP = re.compile(r"\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(f\s+)?(?:i\s+)?(\S*)")
sections = {}
addrs = set()
for line in open(image_dir + "/image/exit.map", errors="replace"):
    m = MAP.match(line)
    if m and not m.group(3):
        va = int(m.group(2), 16)
        syms[m.group(1)].append((va, m.group(4)))
        addrs.add(va)
    elif m:
        addrs.add(int(m.group(2), 16))
starts = sorted(addrs)


def gap(va):
    i = bisect.bisect_right(starts, va)
    return (starts[i] if i < len(starts) else va) - va


rows = list(csv.DictReader(open(ledger + "/data_ledger.csv", newline="", encoding="utf-8", errors="replace")))
multi = pairs = differ = 0
listed = []
for r in rows:
    names = {r["name"], *(r.get("names") or "").split(";")} - {""}
    if len(names) < 2:
        continue
    multi += 1
    found = {n: syms[n] for n in names if n in syms}
    vas = {v for e in found.values() for v, _o in e}
    if len(vas) < 2:
        continue
    pairs += 1
    sizes = {va: gap(va) for va in vas}
    big = max(sizes.values())
    small = min(sizes.values())
    if big != small:
        differ += 1
    listed.append((r["address"], r["size"], r["kind"], len(vas), small, big,
                   " | ".join(f"{n[:46]}@{e[0][0]:#x}/{gap(e[0][0])}" for n, e in sorted(found.items())), r["source"][-48:]))
print("ledger rows", len(rows), "with 2+ names", multi, "defined apart in the image", pairs, "of those with different sizes", differ)
kinds = collections.Counter(x[2] for x in listed)
print("by kind", dict(kinds))
with open(out, "w", encoding="utf-8") as f:
    print("address\tledger_size\tkind\tdefinitions\tsmallest\tlargest\tnames\tsource", file=f)
    for x in sorted(listed, key=lambda x: -(x[5] - x[4])):
        print(*x, sep="\t", file=f)
for x in sorted(listed, key=lambda x: -(x[5] - x[4]))[:14]:
    print(x[0], "ledger", x[1], x[2], "sizes", x[4], x[5], x[6][:150])
