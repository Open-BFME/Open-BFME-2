# HordeMeleeAmoeba header cohort probe, 2026-11-05

Source revision `7ac44ac9c4`; worker `yasinschroeder-codexb5`.
The header picker claimed class:HordeMeleeAmoeba and selected the three
remaining private-view consumers. Declared-unmatched checks passed.

`header_adopt_lane.py adopt --class HordeMeleeAmoeba --header
Code/GameEngine/Include/GameLogic/HordeMeleeAmoeba.h --apply` on
FamilyDeletingDtors_Rva00587F69.cpp, WWLib/HordeMeleeAmoeba.cpp and
Rva00587F69Dtor.cpp retained no edits:

- Deleting-destructor emitter: C2653, `_STL` is not a namespace. This consumer
  lacks the STLport selection required by the header's vector member.
- Seed: field reconciliation refuses vector<BfmeE16> versus vector<BfmePod60>.
- Native destructor: header layout compilation fails (C2653/C2143/C2501), also
  before member-lifetime reconciliation.

The existing LINK-201 seed lifetime and emitted-vtable closure prerequisites
remain unchanged. Fixing configuration alone would not establish provider
closure; the earlier canonical-header handoff already records unresolved opaque
slots from complete table emission. No repeated complete-table trial, provider
invention, header edit, debt retirement or new link measurement was attempted.
The class claim was released; the blocked verdict was recorded through re_log.py.
