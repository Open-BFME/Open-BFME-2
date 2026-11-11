#!/usr/bin/env python3
"""Second pass over the 439 "open" false rejects: how many name a DATA address?

fr_open.py answers "does the name the record wanted now own that RVA?" against
reverse/functions.csv alone. Every false reject whose subject is a vtable,
vbtable, string or other static lives in reverse/data_ledger.csv or
reverse/data_rows.csv instead, so it can never resolve and is scored open
whatever the truth. The vtable_bridge cluster is the proof: all 8 were repaired
on 2026-11-08 (0e11bbf733d, b9aeebea15a) and all 8 still read as open.
"""
import collections, csv, json, os, re
SC = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(os.path.dirname(SC))
os.chdir(ROOT)
OPEN_JSON = os.path.join(SC, "fr_open.json")      # written by fr_open.py; run it first

def addr(text):
    try:
        return int(text, 16)
    except (ValueError, TypeError):
        return None

data_at = collections.defaultdict(set)
for path, acol, ncol, extra in (
        ("reverse/data_ledger.csv", "address", "name", "names"),
        ("reverse/data_rows.csv", "address", "name", None)):
    with open(path, newline="", encoding="utf-8") as fh:
        for r in csv.DictReader(fh):
            a = addr(r[acol])
            if a is None:
                continue
            names = {r[ncol]}
            if extra:
                names |= set((r.get(extra) or "").split(";"))
            data_at[a] |= names - {""}

recs = json.load(open(OPEN_JSON))
print(f"{len(recs)} records fr_open.py called open")

by = collections.Counter()
closed_by_data = collections.defaultdict(list)
for r in recs:
    a = addr(r.get("rva") or "")
    if a is None or a not in data_at:
        by["not a data address"] += 1
        continue
    sym = r.get("sym", "")
    if sym in data_at[a]:
        by["CLOSED by the data ledger: the wanted name owns it"] += 1
        closed_by_data[r.get("check", "?")].append(r)
    else:
        by["data address, but a different name owns it"] += 1

for k, v in by.most_common():
    print(f"  {v:4d}  {k}")
print()
print("  closed by check:")
for check, rows in sorted(closed_by_data.items(), key=lambda kv: -len(kv[1])):
    print(f"   {len(rows):4d}  {check}")
json.dump({k: [r["line"] for r in v] for k, v in closed_by_data.items()},
          open(os.path.join(SC, "fr_data_closed.json"), "w"), indent=1)
