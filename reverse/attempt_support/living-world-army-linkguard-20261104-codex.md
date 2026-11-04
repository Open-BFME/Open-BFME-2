# LivingWorldArmy consolidation LinkGuard refusal (2026-11-04)

Inspected revision: `3014df9a44`. The allocated TU check passed for `Code/GameEngine/Source/Common/System/LivingWorldArmy.cpp`. The planner ran under `Code/GameEngine/Source/Common/System/`; its snapshot check passed. `tu_skeleton.py --plan` reported 132 approved rows, 2 donor files, 8 mixed files, and 0 refused files. The dry-run accepted no donors.

LinkGuard reports the census seed currently links, but its merged-flag trial would leave this unresolved:

`?__uninitialized_fill_n@@YAPAVRva00318B5C@@PAV1@IABV1@ABU__false_type@_STL@@@Z`

The report identifies `Code/Libraries/Source/WWVegas/WWLib/stlport_vector_record_319bca_assign.cpp` in the census-linked set. No source, ledger, or map edits were made. No merge or census clearance is claimed.

Next check: resolve the seed's STLport provider/flag interaction and verify the current provider/consumer binding with supported scoped link checks before retrying this TU.
