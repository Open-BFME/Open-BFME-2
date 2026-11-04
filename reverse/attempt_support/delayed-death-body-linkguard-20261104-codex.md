# DelayedDeathBody LinkGuard census-index refusal

Inspected source revision: `5aa18aaf53`; allocated shard: `0/5`.

Commands and results:

- `python3 /opt/runner/consolidation_queue.py --check-tu Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp` — passed.
- `python3 tools/name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/` — completed; no missing inputs.
- `python3 tools/name_lane.py consolidate --check build/consolidation` — passed.
- `python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp` — 12 approved rows, 3 donor files, 5 mixed files, 0 refused.
- `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp --dry-run` — no accepted donors. LinkGuard blocked the trial because the census-linked destination `DelayedDeathBody.cpp` is missing from its census index; the report lists `DelayedDeathBodyApply.cpp`, `DelayedDeathBodyXfer.cpp` and the destination as census-linked.

No merge was applied. The refusal is the missing census-index entry; no source or ledger was changed and no claim was taken. Retry only after the index or LinkGuard inputs change, then compare the affected provider and consumer bindings.
