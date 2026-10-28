#!/usr/bin/env python3
"""Evidence script (not a tool): census-linked units whose own COMDAT copy would newly
lose link_census.keep_rule when the census index's objects are re-ranked by
retail-truth-5's code_places (census commit's functions.csv), with the census's
referenced-name set. On the census order the same computation reproduces the
census's multi-copy losers exactly (0 extra), so only the order changes here.

    git show <census commit>:reverse/functions.csv > build/scratch_lk6/functions_census.csv
    python3 reverse/attempt_support/rt5-order-losses-20261029/rt5_losers.py
"""
import collections, csv, pickle, sys
sys.path.insert(0, "tools")
import link_census
idx = pickle.load(open("build/link_census/link_index.pkl", "rb"))
objs = idx["objects"]; cur = {o: i for i, o in enumerate(objs)}; REF = idx["references"]["referenced"]
with open("build/scratch_lk6/functions_census.csv", newline="", encoding="utf-8") as h:
    rows = [r for r in csv.DictReader(h) if r.get("status") == "matched" and (r.get("target_rva") or "").startswith("0x")]
pl = {p.name: rva for p, rva in link_census.code_places(rows).items()}
rank = {o: i for i, o in enumerate(sorted(objs, key=lambda o: (0, pl[o], o) if o in pl else (1, cur[o], o)))}
bl = idx["blockers"]; obj2src = {e["object"]: s for s, e in bl.items()}
linked = {e["object"] for e in bl.values() if e.get("linked")}
hurt = collections.defaultdict(list)
for name, cs in idx["comdat"].items():
    if len({d for _, d, _ in cs}) < 2:
        continue
    old = sorted(cs, key=lambda c: c[0]); new = sorted(cs, key=lambda c: rank[objs[c[0]]])
    if old[0][0] == new[0][0]:
        continue
    lo, _ = link_census.keep_rule([(objs[c[0]], c[1], c[2]) for c in old], name in REF)
    ln, rule = link_census.keep_rule([(objs[c[0]], c[1], c[2]) for c in new], name in REF)
    for o, lose in ln.items():
        if lose and not lo.get(o) and o in linked:
            hurt[obj2src[o]].append((name, rule, objs[new[0][0]]))
print(f"census-linked units whose own copy newly loses under rt5: {len(hurt)}, {sum(idx['bytes'].get(u,0) for u in hurt):,} B")
for u in sorted(hurt, key=lambda u: -idx['bytes'].get(u, 0)):
    print(f"{idx['bytes'].get(u,0):>8,} {u}")
    for n, rule, first in hurt[u][:3]:
        print(f"           {rule}: {n[:120]}  first={obj2src.get(first, first)[-60:]}")
