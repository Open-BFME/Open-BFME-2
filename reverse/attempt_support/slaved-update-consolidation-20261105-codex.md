# SlavedUpdate consolidation dry-run handoff

Inspected source revision: `463674729a`; allocator shard: `0/5`.

Commands and results:

- `python3 /opt/runner/consolidation_queue.py --check-tu Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate.cpp` — passed.
- `python3 tools/name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/` and `python3 tools/name_lane.py consolidate --check build/consolidation` — completed with no missing inputs; snapshot check passed.
- `python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate.cpp` — 28 approved rows, 5 pull donors, 5 mixed files, 0 refused.
- `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/SlavedUpdate.cpp --dry-run` — 0 accepted donors. `SlavedUpdateCtor.cpp` failed with C2065 for undeclared `m_secondary20` and `m_24`; `SlavedUpdateRva004A1950.cpp` failed with C2039 because `Object` lacks `m_modelConditionWords` and `m_modelCondition...`; `Rva004A1855Xfer.cpp` failed with C2011 duplicate `Xfer` and C2039 missing `Version`; `SlavedUpdateMoveToNewRepairSpot.cpp` failed with C2011 duplicate `Coord3D` and further view diagnostics. The report recommends `UpdateModule` adoption for the ctor and `AIUpdateInterface` adoption for MoveToNewRepairSpot, and identifies private `SlavedUpdate` views. LinkGuard lists the destination and four donor units as census-linked; no merged composition passed it.

No source, ledger or claim changed. Declaration, class-view and header prerequisites require another owner; do not retry these unchanged donors until those prerequisites or the guarded inputs change.
