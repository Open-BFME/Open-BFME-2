# Locomotor consolidation dry-run handoff

The allocated `Locomotor.cpp` destination passed `consolidation_queue.py
--check-tu`; the GameLogic/Object-scoped consolidation report passed its
freshness check. The plan contains 154 approved rows, 38 donor files and 14
mixed files. The guarded dry run accepted no donors and ended with `blocked:
no verified merge of two or more donors`; LinkGuard listed the affected objects
as census-linked.

Manual source prerequisites remain. Combined-TU trials report missing
`Locomotor::getLegalSurfaces`/`rva001E4194` and `Object::component` /
`clearModelConditionState` declarations, absent `LocomotorTemplate` special
member declarations (C2600), and a `GlobalData.h` include-order error (C1189).
Several independent donors fail byte verification, including
`LocomotorTemplateValidate.cpp`, `SmallIniParseCallbacks_CanMoveBackwards.cpp`,
`LocomotorTerrainHeight.cpp`, and `Rva001E4DB0Ctor.cpp`. The tool recommends
reconciling the listed private class views before another merge trial. This
mechanical seat made no source, ledger or claim changes; the declaration,
include and byte repairs belong to other lanes.
