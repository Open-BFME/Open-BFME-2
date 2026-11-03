# WorkerAIUpdateCtor canonical StateConditionInfo adoption

Replaced the private `StateConditionInfo` definition in
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateCtor.cpp`
with the existing canonical `Common/StateConditionInfo.h` include.

The former definition uses `Bool` (`bool`) for the callback result and
`StateID` (`unsigned int`) for the destination. Its field names, order and
callback arguments agree with the canonical declaration: `test`, `toStateID`,
`userData`. No header, symbol, alias, ledger row or source path changed.
This adopts an existing declaration; it makes no new donor provenance claim.

Verification completed before committing:

- `./build.sh Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/WorkerAIUpdateCtor.cpp`:
  30/30 matched, 17 literals and seven empty strings checked, ten float
  constants checked; seven renumbered funclets verified through parent EH data.
- `find_declared_unmatched.py` for that source: all defined functions already
  matched.
- `header_adopt_lane.py accept --class StateConditionInfo` for that source:
  PASS; its structural, byte and link-preservation preview checks accepted
  the adoption and retired one row from `reverse/header_queue.tsv`.
- `check_csv.py`: OK, 99,431 function rows, 9,343 symbol rows, 2,269 data rows.

The broader WorkerAIUpdate consolidation remains blocked by the previously
recorded declaration conflicts. This removes one canonical-header prerequisite;
it does not establish a merged TU or a new census result.
