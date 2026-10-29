#!/usr/bin/env python3
"""Evidence script (not a tool): tools/link_check.py with the census index's objects permuted into
retail-truth-5 link order computed from the CURRENT ledger (link_check.link_rank). link_check itself
judges keep_rule and selection by census index position (min(definers)), i.e. by the census's
retail-truth-4 order, until the next census; this previews the next census's order instead.
Providers repaired since the census count only when passed too (their current objects replace the
census's); the referenced-name set stays the census's.

    python3 reverse/attempt_support/rt5-order-losses-20261029/rt5_lc.py <link_check args...>
"""
import sys
sys.path.insert(0, "tools")
import build, link_check
_orig = link_check.load_index
def permuted():
    idx = _orig()
    rank = link_check.link_rank(build.load_function_rows())
    objs = idx["objects"]
    order = sorted(range(len(objs)), key=lambda i: (rank.get(objs[i], 10**9), i))
    new = {old: n for n, old in enumerate(order)}
    idx["objects"] = [objs[i] for i in order]
    idx["strong"] = {k: [new[p] for p in v] for k, v in idx["strong"].items()}
    idx["comdat"] = {k: [(new[p], d, s) for p, d, s in v] for k, v in idx["comdat"].items()}
    idx["common"] = {k: [(new[p], z) for p, z in v] for k, v in idx["common"].items()}
    idx["alternates"] = {k: [(new[p], t) for p, t in v] for k, v in idx["alternates"].items()}
    ex = idx["selection"]["exceptions"]
    idx["selection"]["exceptions"] = {k: (None if v is None else new[v]) for k, v in ex.items()}
    print(f"rt5_lc: index permuted into current-ledger retail-truth-5 order ({len(rank)} ranked objects)",
          file=sys.stderr)
    return idx
link_check.load_index = permuted
sys.exit(link_check.main(sys.argv[1:]))
