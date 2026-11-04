# AIUnitBuilder build consolidation

Inspected starting revision: `3c645a66ac`. Scope: `AIUnitBuilder.cpp` and
`AIUnitBuilderBuild.cpp` under
`Code/GameEngine/Source/GameLogic/SkirmishAI/AIUnitBuilder/`.

The default picker selected approval of four proposed boundary rows. Current
`tu_skeleton.py --plan` still leaves 0x00598DA2, 0x00598E66, 0x00598E85 and
0x00598F08 without approved independent brackets. The WorldBuilder pairing at
0x00598DA2 does not establish the original owner/method name. No names or TU
approvals were invented; these remain prerequisites for the constructor donor.

A directly approved donor, `AIUnitBuilderBuild.cpp`, failed the first merge
link guard because the destination's bfmelist shim force-inlined node creation,
changing the retail list::insert COMDAT. Declaration-only insert removed the
needed provider; declaration-only push_back also changed build's codegen. Those
trials were discarded. Removing the unnecessary bfmelist include search path
keeps the ordinary STLport list implementation and its matching folded insert
and push_back definitions. No pins, aliases or shared shims were changed.

The build-selection expression now assigns item on each actual selection path,
avoiding a dead initializer store under the destination's compiler context.
Standalone build remains exactly 66 bytes. All 24 destination rows, including
its associative EH rows, remain exact. `find_declared_unmatched.py` passes for
both files. Both individual units pass `link_check.py` against census
2026-11-04 13:15, revision f6d845ecd4: 829 and 66 own bytes respectively.

The final `tu_skeleton.py --merge .../AIUnitBuilder.cpp --dry-run` accepts both
files, preserves all 25 rows, and passes its census link guard. Only the approved
build donor is absorbed; mixed sources and the unapproved constructor remain.
This preview does not change the census headline.
