# ScriptConditions consolidation recheck (2026-11-05)

Shard 2/5 allocation and `consolidation_queue.py --check-tu` passed for
`Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptConditions.cpp`. A fresh
ScriptEngine-scoped `name_lane.py consolidate` report and its `--check` passed.
The plan contained 266 approved rows, five pull donors, six mixed files and
one refused donor (`ScriptConditions_ctor.cpp`, one row not approved for this
TU). The merge dry-run accepted no donors and reported no verified merge of
two or more donors.

Rejected pull donors:

- `ScriptConditionsPlayerUnitCounts.cpp` and
  `ScriptConditionsRva003E8E23.cpp`: `Overridable` base and
  `friend_getFinalOverride` declarations are missing.
- `ScriptConditions_evaluateSkirmishSpecialPowerIsReady.cpp`:
  `TeamPrototype::m_1D8` and `m_entries` are missing.
- `ScriptConditions_evaluateIsNumOfUnitsBelongingToPlayerNearEvaEventLastPlayedLocationComparisonInt.cpp`:
  `BfmeWideResult::size` is missing.

LinkGuard reports the seed and all four pull donors as census-linked. The
report requests reconciliation for `BfmeObjectDlinkBase`,
`BfmeObjectThingPad`, `BfmeObjectVbptrCarrier`, `BfmeObjectVirtualTail`,
`BfmeObjectVtbl`, `Object`, `ObjectTypesTemp`, and `SpecialPowerStore`. The
recent AI-header adoption does not clear these prerequisites. No claims or
source edits were made; retry after the listed view/declaration fixes.
