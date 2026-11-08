# Marked definitions that are the only provider of a referenced symbol, 2026-11-08

A `present-unmatched` definition with no row or pin that another object references is what links in that symbol's
place. Nothing compares its body with retail, and the callee scan can't see it when the row points elsewhere.

`scan.py` reads the build's objects. Run it from a checkout with `build/match/` and `build/scratch_defects/callee.tsv`.

| Step | Count |
|---|---:|
| Markers in `.cpp`/`.c` comments | 2,081 |
| Map to a definition in their object | 897 |
| Name nothing their object defines (not emitted, or a shape the parser misses) | 1,150 |
| Name an identifier in their object under another spelling, counted loosely | 34 |
| Definitions with no row or pin | 667 |
| Referenced by another object, and the only provider | 64 |

Of the 64, compared with retail at the address a rowed caller or table uses: 34 differ, 12 are the same, 17 have no rowed
consumer so have no retail address here, and 1 has consumers that disagree.

`ranking.tsv` orders them by the boot walk: the first order at which `scan3.tsv` installs the consumer's table or reaches its
row. **A blank order clears nothing**: it means this walk does not reach it, and the walk is a static one.

"Differs" means bytes, outside relocations. Some are a compile near-miss rather than a behaviour change, so read the body
before fixing it.
