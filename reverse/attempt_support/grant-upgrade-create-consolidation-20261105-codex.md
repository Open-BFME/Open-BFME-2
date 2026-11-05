# GrantUpgradeCreate consolidation dry-run handoff

Inspected source revision: `463674729a`; allocator shard: `0/5`.

Commands and results:

- `python3 /opt/runner/consolidation_queue.py --check-tu Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate.cpp` — passed.
- `python3 tools/name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Create/` — completed with no missing inputs; `tools/name_lane.py consolidate --check build/consolidation` passed.
- `python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate.cpp` — 17 approved rows, 5 pull donors, 2 mixed files, 0 refused.
- `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Create/GrantUpgradeCreate.cpp --dry-run` — 0 accepted donors. `GrantUpgradeCreate_onCreate.cpp` and `GrantUpgradeCreate_onBuildComplete.cpp` hit C2011 redefinitions of `Module` and `ObjectModule`; `GrantUpgradeCreateModuleDataCtor.cpp` hit C2953 duplicate `StringBase` and C2614 for `GrantUpgradeCreateModuleData`; `GrantUpgradeCreateModuleDataDtor.cpp` failed byte verification. LinkGuard lists the destination and four donors as census-linked; no merged composition passed it.

No source, ledger or claim changed. The class/module declarations and module-data constructor/destructor bytes need an owning source repair before another merge trial.
