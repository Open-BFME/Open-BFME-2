# PlayerPosition TU approval prerequisite

Inspected `07d1520d8e` on 2026-11-04. No source, pin or TU-map edits.

The picker selected 23 proposed rows in nine files for
`Code/GameEngine/Source/GameClient/PlayerPosition.cpp`. Its ordinary rows have
N/U/C hints, not an independent retail source-path or donor-definition anchor.
The PlayerPosition naming cluster covers `0x003023B8..0x003039E8` and
interleaves Z-anchored MapUtil rows at `0x003024BC`, `0x00302B7D` and
`0x00303409`. MapUtil's hard-anchor span is
`0x003004A5..0x00305749` (0x52A4), exceeding `tu_map.UNION_SPAN` (0x2000).
The U merge therefore cannot absorb the smaller naming cluster. This explains
the noncontiguous proposals without asserting that PlayerPosition.cpp was a
retail translation unit.

The current-input `tu_skeleton.py --plan` rebuilds the stale committed map in
memory. It reports 28 approved P funclet rows, zero donor files, two mixed files
and two refused files. It does not approve the ordinary PlayerPosition bodies.
The WorldBuilder lead at `0x003023B8` is PARTIAL, score 2, callgraph-only;
it supplies no independently corroborated source path. No source path was
inferred from the generated file stem.

Verification: `find_declared_unmatched.py` reports all definitions matched in
`PlayerPositionRva003023B8.cpp`; `./build.sh` verifies 3/3 rows, its funclet,
one string literal and import/float checks. No matching regression was found.

Next step: obtain an independent target placement anchor, or separately measure
and validate a mapper rule for this larger anchored span before changing routing.
The existing MapUtil split-dimension/debt attempts remain prerequisites of their
own repairs; this investigation neither retires those keys nor authorizes moves.
