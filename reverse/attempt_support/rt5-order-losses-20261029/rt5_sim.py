#!/usr/bin/env python3
"""Evidence script (not a tool): re-rank the census index's objects by
retail-truth-5's link_census.code_places, computed from the census commit's own
functions.csv, and list the COMDAT names whose kept (first-in-link-order) copy
changes verdict, with the census-linked units that touch each lost name.

Run from the repo root after `python3 tools/link_check.py --fetch-index`:
    git show <census commit>:reverse/functions.csv > build/functions_census.csv
    python3 reverse/attempt_support/rt5-order-losses-20261029/rt5_sim.py build/functions_census.csv

Sanity check printed first: the retail-truth-4 rule (lowest RVA of all rows) on
the same ledger must reproduce the index's object order exactly.
Upper bounds: other new conflicts are not re-judged, /MAP exceptions ignored.
"""
import collections
import csv
import pickle
import sys

sys.path.insert(0, "tools")
import build  # noqa: E402
import link_census  # noqa: E402

idx = pickle.load(open("build/link_census/link_index.pkl", "rb"))
objs = idx["objects"]
cur = {o: i for i, o in enumerate(objs)}
with open(sys.argv[1], newline="", encoding="utf-8") as handle:
    rows = [r for r in csv.DictReader(handle) if r.get("status") == "matched"
            and (r.get("target_rva") or "").startswith("0x")]
old = {}
for r in rows:
    o, v = build.row_object(r).name, int(r["target_rva"], 16)
    old[o] = min(old.get(o, v), v)
placed = [o for o in objs if o in old]
print(f"index {idx['meta']['date']} at {idx['meta']['commit']}; retail-truth-4 order reproduced: "
      f"{sorted(placed, key=lambda o: (old[o], o)) == placed}")
places = {p.name: rva for p, rva in link_census.code_places(rows).items()}
rank = {o: i for i, o in enumerate(sorted(objs, key=lambda o: (0, places[o], o) if o in places else (1, cur[o], o)))}
bl = idx["blockers"]
obj2src = {e["object"]: s for s, e in bl.items()}
gain, loss = {}, {}
for name, copies in idx["comdat"].items():
    b = min(copies, key=lambda c: c[0])
    a = min(copies, key=lambda c: rank[objs[c[0]]])
    if b[1] == a[1]:
        continue
    if b[2] == "wrong" and a[2] != "wrong":
        gain[name] = (b, a)
    elif a[2] == "wrong" and b[2] != "wrong":
        loss[name] = (b, a)
print(f"names whose kept copy turns non-wrong: {len(gain)}; turns wrong: {len(loss)}")
hurt = collections.defaultdict(set)
for name, (b, a) in sorted(loss.items()):
    users = [obj2src[o] for o, names in idx["touches"].items()
             if name in names and o in obj2src and bl[obj2src[o]].get("linked")]
    print(f"  - {name}\n      kept was {obj2src.get(objs[b[0]])} ({b[2]}), becomes {obj2src.get(objs[a[0]])} "
          f"({a[2]}); census-linked users {len(users)}, {sum(idx['bytes'].get(u, 0) for u in users):,} B")
    for u in users:
        hurt[u].add(name)
print(f"census-linked units touching a lost name: {len(hurt)}, {sum(idx['bytes'].get(u, 0) for u in hurt):,} B")
for u in sorted(hurt, key=lambda u: -idx["bytes"].get(u, 0)):
    print(f"  {idx['bytes'].get(u, 0):>8,} {u}")
freed = [(s, idx["bytes"].get(s, 0)) for s, e in bl.items()
         if not e.get("linked") and e["wrong_selected"] and set(e["wrong_selected"]) <= set(gain)
         and not (e["unresolved"] or e["duplicates"] or e["losers"] or e["addresses"])]
print(f"census-unlinked units blocked only by wrong_selected on gained names: {len(freed)}, "
      f"{sum(b for _, b in freed):,} B")
