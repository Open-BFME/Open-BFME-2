# InheritUpgradeCreate consolidation dry-run handoff

Inspected source revision: `463674729a`; allocator shard: `0/5`.

Commands and results:

- `python3 /opt/runner/consolidation_queue.py --check-tu Code/GameEngine/Source/GameLogic/Object/Create/InheritUpgradeCreate.cpp` — passed.
- `python3 tools/name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Create/` — completed with no missing inputs; `tools/name_lane.py consolidate --check build/consolidation` passed.
- `python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/Object/Create/InheritUpgradeCreate.cpp` — 18 approved rows, 5 pull donors, 3 mixed files, 0 refused.
- `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Create/InheritUpgradeCreate.cpp --dry-run` — 0 accepted donors. The ctor donor failed C2511 for the missing class constructor declaration; Xfer failed C2039 because `xfer` is not a member and C2248 on a private member; the module-data ctor failed C2600 because its special member is not declared in the class; OnBuildComplete failed C2039 because `onBuildComplete` is not a class member. The tool recommends `CreateModule` adoption for the ctor and `Rva003623E5Member` for the module-data ctor, and flags private `InheritUpgradeCreate` / `InheritUpgradeCreateModuleData` views. LinkGuard lists the destination and all four donor objects as census-linked; no merged composition passed it.

No source, ledger or claim changed. Class declarations, module-data view and base-header prerequisites need owner-side reconciliation before another merge trial.
