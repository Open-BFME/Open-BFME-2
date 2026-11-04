# AreaPolygonBase consolidation follow-up (2026-11-04)

Inspected base: `36452d8291`; declaration repair: `394494bc7b`.
The current census preview reports 2026-11-04 20:47 at `f12552d0a7`.
No new census or linked-byte gain is claimed.

## Completed prerequisite

Aligned the swap-only BfmeE12 view in AreaPolygonBase_parse.cpp and the
assignment-only BfmePod8 view in Rva0030B92COpAssign.cpp with the destination
TU's existing float-field views. Their sizes remain 12 and 8 bytes. This
reconciles declarations; it does not establish original type names.
`./build.sh` verified all four rows across the two files, including the
parser's parent-derived funclet. Declared-unmatched passed, and both units
predict LINKS (143 and 63 authored bytes). The view dry-run now reports both
types already shared. This repair was committed separately and handed to the
fleet publisher.

## Merge trial and boundary

`tu_skeleton.py --merge Code/GameEngine/Source/Common/AreaPolygonBase.cpp --dry-run`
accepted the existing destination plus AreaPolygonUpdateBounds.cpp,
Rva0030B92COpAssign.cpp and Rva0030B980Constructors.cpp: 28 matched rows and
three source files removable. The ordinary merge byte and link guards passed
for that composition. The saved plan remains under ignored build/tu_skeleton/plans.

The parser still fails merged bytes. Rva0030B7C2PointQuery.cpp is refused
because moving its copy constructor `??0Rva0030D111Point@@QAE@ABU0@@Z`
would break another unit's copy. The index has copies in both the point-query
and Rva0030D111ContainsPoint objects; no alias or provider was removed.
Mixed-source donors remain outside this merge.

Applying the accepted plan stopped before writing: the destructor fold RVA
`0x0007FAB3` is held by `yasinschroeder-claudeb`. The merge released its acquired
scope, and the working tree stayed clean. No source reduction was landed.
Do not bypass that claim or the link guard.

## Next check

When the fold claim is free, reacquire the TU scope and rerun the supported
merge; it rechecks saved-plan inputs and link safety. Verify the resulting
28-row TU and audit all removed-path consumers before publication. The parser
byte mismatch and point-copy constructor conflict remain separate follow-ups.
The PolygonTrigger writer/census prerequisite in the obstacle entry remains open.
