# WargBehavior consolidation trial (2026-11-04)

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Behavior/WargBehavior.cpp`; `consolidation_queue.py --check-tu` passed. A fresh Behavior-scoped planner and its `--check` passed. The plan had five approved rows, one pull donor and one mixed donor.

The merge dry run accepted no donors. `WargBehaviorCtor.cpp` failed because the `WargBehavior(Thing *, const ModuleData *)` constructor is absent from the class view; the tool recommends reconciling `WargBehavior`. `ConstIntGetters4.cpp` contains one approved row for this TU. Its split trial matched that row alone, but LinkGuard refused the split because the moved selected COMDAT `??_C@_0N@NPFADNKE@WargBehavior?$AA@` lacks matching private/weak-free context. No source or ledger changes were applied and no claims were made. The class-view and link-context prerequisites are outside this mechanical lane; no source reduction or identity/link progress is claimed.
