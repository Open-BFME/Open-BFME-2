# Coord2D animation header debt retirement, 2026-11-04

Inspected revision: `d2dba86837`. Follow-up to
[the source adoption](coord2d-animation-header-20261104-codexb.md) and LINK-098.
No source, header, ledger identity, pin or compiler flags change here.

The current published index is dated 2026-11-04 07:28 at `a62ac1c10b`.
`python3 tools/link_check.py --fetch-index` confirms the local index is the
same published census. This resolves the earlier stale-provider preview
prerequisite for the two animation header queue rows; no verifier edit is
needed.

`header_adopt_lane.py accept --class Coord2D` on AnimateWindowGetVel.cpp
and ProcessAnimateWindowRightFastInitReverse.cpp passes both units and
retires their two rows from `reverse/header_queue.tsv`. The staged
`repair_queue.py verify-removed` exits zero. The existing canonical
Coord2DCtorView.h companion is accepted by the owning tool in both units.

An explicit `./build.sh` of both units passes all 20 function rows, four
compiler float literals and 14 named import references. Ordinary link
preview against the index above reports:

| Unit | Census-linked bytes before -> preview after |
| --- | ---: |
| AnimateWindowGetVel.cpp | 18 -> 18 |
| ProcessAnimateWindowRightFastInitReverse.cpp | 2,816 -> 2,816 |

Both previews say LINKS. This is debt retirement and preservation of
2,834 previously census-linked bytes, not a new linking headline or a
real-game-link measurement. The stale Rva00062B17Init.cpp Coord2D queue
row remains unchanged; its historical-identity acceptance boundary is
still open. Other LINK-098 prerequisites are outside this verification.

Local logs: `build/codex4-coord2d-{accept,build,debt,link}.log`.
