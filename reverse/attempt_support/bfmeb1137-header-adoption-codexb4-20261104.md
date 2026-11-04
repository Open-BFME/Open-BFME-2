# BfmeB1137 header adoption and TU-approval boundary

Inspected revision: `d9a128b6d0` (2026-11-04). Claim owner:
`yasinschroeder-codexb4`; scope
`file:Code/GameEngine/Source/Common/BfmeB1137.cpp`.

## Completed repair

The TU carried private `StringClass` and `DX8Wrapper` definitions even though
both classes have canonical declaration headers. Include `StringClassData.h`
and `DX8WrapperClass.h`, keeping the existing StringClass constructor/destructor
and DX8 texture-stage setter as inline definitions in this TU. Preserve the
constructor's existing compiler options. The shared headers are unchanged.
The source's link-wide ScreenTextureStageStateChanges alternate name remains.

The constructor and cleanup bodies are necessary to reproduce the inlined
retail code. This follows LINK-192's existing per-TU approach. No names, pins,
ledger extents, source paths, or counted hatches were added or removed.

## Verification

`find_declared_unmatched.py` passed before and after the edit. `./build.sh`
verified all 17 rows before and after adoption, including the compiler-generated
EH rows with parent-graph resolution of renumbered labels. String, float and
import reference checks passed. `git diff --check` passed.

Both `header_adopt_lane.py accept --class StringClass` and `--class DX8Wrapper`
passed for this source and retired their respective queue entries. The combined
`link_check.py` preview reports LINKS and preserves 824/824 linked bytes against
the index dated 2026-11-04 22:40 at `3a95b274a2`. This is preview preservation,
not a new census measurement or a headline linked-byte gain.

## TU approval remains separate

The default picker selected TU approval: 16 proposed rows in 10 files,
9 with only naming hints and 7 bracket-dependent rows. The current-input
`tu_skeleton.py --plan` rebuilt the stale committed map in memory; it reported
109 approved rows, 3 donor files, 2 mixed files and 2 refused files. This does
not approve the remaining rows or establish the original retail TU name.

`name_lane.py consolidate --under Code/GameEngine/Source/Common/` produced
current source/layout packets. BfmeB1137's local packet leaves all 17 row
placements unresolved and supplies no original-path evidence. Inspected BFME1
CloudEffect and shader sources give no independent name proof for these
placeholder owners; a donor file or a similar rendering role cannot establish
BFME2 identity. Existing work also records merge layout conflicts in
`reverse/re_attempts.log` under `tu-merge:.../BfmeB1137.cpp`.

Next useful approval step: obtain an independent retail file/assert string or
a nontrivial, unique same-body donor placement with proven names for the
Rva009519B/BfmeB1137/Gen006E2310 family. Do not rename it from adjacency or
rendering-role guesses. No TU map was regenerated on disk and no merge was
attempted; this commit claims header-debt reduction only.
