### LINK-205: LivingWorldArmy merged flags drop the STLport fill provider
Status: Open. Updated: 2026-11-04; inspected revision: 3014df9a44.
Evidence / affected units: allocated TU `Common/System/LivingWorldArmy.cpp`; LinkGuard reports the census seed links, but its merged-flag trial leaves `?__uninitialized_fill_n@@YAPAVRva00318B5C@@PAV1@IABV1@ABU__false_type@_STL@@@Z` unresolved; `stlport_vector_record_319bca_assign.cpp` is in the reported census-linked set. [Dry-run evidence](../../reverse/attempt_support/living-world-army-linkguard-20261104-codex.md).
Completed: planner snapshot and check passed; plan reported 132 approved rows, 2 donor files, 8 mixed files, 0 refused files; dry-run accepted no donors. No edits applied.
Remaining / next check: resolve the STLport provider/flag interaction, then rerun the allocated TU dry-run and supported scoped link verification.
Clearance: none; no merge or source reduction claimed.
Census confirmation: no new census claimed.
