# Additional shard 0/5 dry-run blockers (2026-11-05, root seat)

Each TU passed its allocation check, parent-scoped consolidation planner and snapshot check. The guarded merge dry run accepted no donors; no split or source change was applied. LinkGuard confirmed tested seed/donor objects remained census-linked.

- `GameLogic/Object/Update/ProductionExitUpdate/SpawnPointProductionExitUpdate.cpp`: `SpawnPointInitializeBonePositions.cpp` fails C2440 converting `Object *` to `Thing *`; tool requests reconciling `SpawnPointProductionExitUpdate` views.
- `Common/QuadStrip2D.cpp`: its `W3DAnimationInfoVectorInsert.cpp` donor fails byte verification.
- `GameLogic/Map/FireLogicSystem.cpp`: two WWLib donors fail byte verification (`StlSweepR3Rva0028681A.cpp`, `stlport_map_int_ptr_tree_dtor.cpp`).
- `GameClient/GUI/GUICallbacks/Apt/AptCampaignReview.cpp`: the donor under `GameClient/GUI/Apt/` has ambiguous `__ctor` access (C2385).

Related `CallHelpOnDamage` and `GeometryUpgrade` obstacles already contain the current failed-dry-run prerequisites; no new evidence was added for those unchanged blockers. No mixed-file split can cure the blockers above, so none was attempted. No claims, builds, composed-object checks, or census runs were performed.
