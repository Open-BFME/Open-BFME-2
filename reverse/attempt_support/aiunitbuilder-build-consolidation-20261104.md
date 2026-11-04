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

Applied the merge after prerequisite commit `d9f71f777e`. The tool absorbed only
the approved build donor, removed one source file and repointed its function
row, TU-map source column and both list fold proofs. It did not regenerate the
TU map or change approval evidence. Final `./build.sh` passes 25/25 rows;
renumbered EH labels are verified through parent data. Frozen-file and CSV
checks pass. Final `link_check.py` reports LINKS with 895 own bytes against the
same census: the former units owned 829 + 66 bytes, so this is preservation,
not a measured linking gain.

Consolidation audit covers the pending range from `origin/master` through the
prerequisite and this merge. No other source paths move in that range. A combined
old-basename search finds no active tool, hook, workflow, include or configuration
consumer. Remaining old-path mentions are the census's historical link-status
row, the merged source's provenance comment and this evidence. Header and
Microsoft-header queues were refreshed by the merge tool; neither changed.
The donor has no identity, data, gate or hatch debt keys to transfer. The
destination's existing data-name finding is retained, with no debt retired.
The prerequisite hook also reported shadow identity findings for renumbered EH
labels and the Xfer temporary destructor, plus the existing global's shadow
duplicate definition; byte/EH checks remain authoritative for this merge.
The merge link guard verifies selected COMDATs and provider bindings; no alias
was removed. Boundary approvals, mixed donors and Rva00506B1B header adoption
remain separate work.

The post-merge scoped naming packet for the complete inspected
`AIUnitBuilder::build` body inventoried one local and no parameters or coverage
warnings. Native-child proposal and parent review retained `item` as clear;
scoped preview/apply completed with zero source changes. The flag's purpose and
concrete item type remain unsupported and were not renamed.
