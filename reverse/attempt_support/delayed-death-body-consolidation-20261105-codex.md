# DelayedDeathBody consolidation dry-run handoff

Inspected source revision: `463674729a`; allocator shard: `0/5`.

Commands and results:

- `python3 /opt/runner/consolidation_queue.py --check-tu Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp` — passed.
- `python3 tools/name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/` — completed with no missing inputs; `tools/name_lane.py consolidate --check build/consolidation` passed.
- `python3 tools/tu_skeleton.py --plan Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp` — 12 approved rows, 3 pull donors, 5 mixed files, 0 refused.
- `python3 tools/tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp --dry-run` — 0 accepted donors. `DelayedDeathBodyApply.cpp` was rejected at generated line 167 with C2511: `DelayedDeathBody::DelayedDeathBody(Thing *,const ModuleData *)` not found in `DelayedDeathBody`. `DelayedDeathBodyXfer.cpp` was rejected at generated line 217 with C2039: `xfer` is not a member of `DelayedDeathBody`; the diagnostic continues with C2065 for `m_b100`. The report's `link_guard` lists census-linked `DelayedDeathBodyApply.cpp`, `DelayedDeathBodyXfer.cpp` and the destination; no successful merge was verified.

No source, ledger or claim changed. A source/header owner must reconcile the `DelayedDeathBody` declaration/member mismatch in both donors before another merge trial. The previous LINK-211 evidence documented a missing census-index entry; this run did not independently reproduce that specific diagnostic, so rerun LinkGuard after the compile prerequisite is repaired.
