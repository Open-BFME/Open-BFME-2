# OathbreakerBody LinkGuard census-index refusal

Inspected source revision: `44e9b309d9`; allocated shard: `0/5`.

Commands:

- `python3 /opt/runner/consolidation_queue.py --check-tu Code/GameEngine/Source/GameLogic/Object/Body/OathbreakerBody.cpp` — passed.
- `python3 tools/name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Body/` — completed; 1 routed retail row, no missing inputs.
- `python3 tools/name_lane.py consolidate --check build/consolidation` — passed.
- `python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/Object/Body/OathbreakerBody.cpp` — 8 approved rows, 2 donor files, 2 mixed files, 0 refused.
- `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Body/OathbreakerBody.cpp --dry-run` — no accepted donors; LinkGuard blocked the trial because the census-linked `OathbreakerBody.cpp` is missing from its census index. The report lists both `OathbreakerBody.cpp` and `OathbreakerBodyAttemptDamage.cpp` as census-linked.

No merge was applied. The tool's LinkGuard reason is the blocker; no claim was taken and no source or ledger changed. Next check: retry only after the census index includes this TU or LinkGuard inputs otherwise change, then compare affected provider/consumer bindings.
