# GarrisonContain consolidation recheck (2026-11-04)

Shard 2/5 allocation and `consolidation_queue.py --check-tu` passed for
`Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContain.cpp`. A fresh
Contain-scoped `name_lane.py consolidate` report and its `--check` passed. The
plan contained 56 approved rows, six pull donors, three mixed files and no
refused files. The merge dry-run accepted no donors and reported no verified
merge of two or more donors.

Rejected pull donors and blockers:

- `GarrisonContainOnObjectCreated.cpp`: `m_filter40` undeclared; access to
  `rva00362192` consequently fails.
- `GarrisonContainOnRemoving.cpp`: `m_conditionBits` is absent from `Object`.
- `GarrisonContainLoadGarrisonPoints.cpp`: `GARRISON_POINT_PRISTINE`
  redefinition.
- `GarrisonContainUpdate.cpp`: duplicate `_STL::_List_iterator::operator!=`.
- `GarrisonContainExit.cpp`: `exitObjectViaDoor` absent from the
  `GarrisonContain` view.

LinkGuard reports the seed and all five donor files as census-linked. The
report requests class/view reconciliation for `GarrisonContain`, `Object`,
`OpenContain`, `ConditionBits`, `ContainSlots`, `Flags128`,
`Rva00263895Member`, `Rva0046247D`, `GameLogicFrameView`, and listed base views.
No claims or source edits were made. Retry after those view and declaration
prerequisites change.
