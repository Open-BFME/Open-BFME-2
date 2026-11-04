# AreaPolygonBase consolidation LinkGuard refusal (2026-11-04)

Inspected revision: `3014df9a44` (`origin/master` current at screening). The allocated TU check passed for `Code/GameEngine/Source/Common/AreaPolygonBase.cpp`. The consolidation planner ran under `Code/GameEngine/Source/Common/` and `--check build/consolidation` passed. `tu_skeleton.py --plan` reported 39 approved rows, 6 donors, 4 mixed files, and 0 refused files. `--merge ... --dry-run` accepted no donors; compile prerequisites remain for the mixed donors.

LinkGuard refused the donor composition because `Code/GameEngine/Source/GameLogic/Map/Rva0030B7C2PointQuery.cpp` currently links, while the merged object would fail to provide `??0Rva0030D111Point@@QAE@ABU0@@Z` for the other unit's copy. The report lists AreaPolygonBase and the affected point-query provider/consumer cohort as census-linked. No source, ledger, or map edits were made. No merge or census clearance is claimed.

Next check: reconcile the AreaPolygonBounds/BfmeE12/BfmePod8 class views and review the point-query constructor provider binding; then rerun the allocated TU dry-run and supported scoped link verification before applying any accepted donors.
