# ProcessAnimateWindow consolidation trial

Base: `e93d5b4890`. The allocated destination passed `consolidation_queue.py
--check-tu`; the GUI-scoped planner passed its freshness check. The plan has
37 approved rows, four donor files and one mixed donor. The split plan routes
14 rows to this TU and leaves five without an approved TU; its guarded dry run
refuses all 14 because a copied helper or datum would grow a hatch count.

The guarded merge dry run accepts no donors. `SlideLeftUpdate.cpp` and
`SlideTopUpdate.cpp` fail on `ICoord2D` redefinition and missing `finished`
members. The `ProcessAnimateWindowSpiralCtor.cpp` donor is rejected by
LinkGuard: the merged object no longer defines `??_EProcessAnimateWindow@@UAEPAXI@Z`
required by the census. No claims or source edits were made. The destination
needs manual class/header and provider reconciliation before another trial.
