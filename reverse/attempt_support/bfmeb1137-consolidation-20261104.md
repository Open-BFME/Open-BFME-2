# BfmeB1137 consolidation prerequisites (2026-11-04)

Inspected source revision: 1c7119a3e7. Scope: the approved provisional TU
`Code/GameEngine/Source/Common/BfmeB1137.cpp` and its destructor donor
`BfmeConv1137Dtor.cpp`. The provisional name is retained; no real source name
is asserted. The consolidation planner classifies the destination as unresolved
for original-path recovery. The live TU map rebuilt by tu_skeleton approves the
moved destructor and its EH rows for this unit.

The initial merge trial accepted no donors: both donor candidates replaced the
seed's partial BfmeB1137 view and lost m_guard54/m_clear68. Retail constructor
0x00094EBF, destructor 0x00094F38, and the existing canonical MaterialPassClass
header establish the 0x38-byte base and texture holders at +0x58..+0x64.
UnInstall_Materials witnesses byte accesses at +0x54/+0x68. Reconciled the seed
and destructor to that layout and the seed's existing field spellings. No claim
is made about the unknown intervening fields or original class name.

The destructor now calls the existing TextureClass::Release_Ref provider rather
than the TextureBaseClass spelling: both ledger bodies own identical retail
RVA 0x0061ED10. No linker alias or pin was removed or added.

Verification before the merge:

- ./build.sh on both changed sources: 25/25 rows exact, including the EH rows.
- find_declared_unmatched on both: all definitions matched.
- link_check on both current objects: 2/2 LINKS, 824 + 154 authored bytes
  unchanged against the 2026-11-04 20:47 census index (f12552d0a7).
- tu_skeleton --merge --dry-run: accepts the seed and destructor; its current
  link guard passes. Gen006E2310Ctor.cpp still fails on the incompatible
  BfmeB1137 field names. tu_views also reports Rva009519B virtual-slot disagreement
  between that constructor donor and the seed. Reconcile that donor separately;
  do not weaken its merge checks.
- No identity/data baseline keys or header-queue rows belong to the destructor
  donor. Existing DX8Wrapper/StringClass header work stays attached to the TU.
  No baseline debt is retired by this prerequisite repair.

Application after prerequisite commit cdc1ac1995 wrote nothing: tu_skeleton
refused the live claim on shared ICF RVA 0x0017098D, held by
`yasinschroeder-claudeb` for fxshadersetup.cpp (about 2.2 hours remaining).
The seed owns the folded StageTextureRef destructor at that address. Respect
that claim and retry the approved merge after it is released; do not remove the
alias row or narrow the merge claim set. No source-file reduction is claimed.
No paths moved, so no outgoing path-consumer audit was necessary in this pass.
