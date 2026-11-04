# AptObject consolidation trial (2026-11-04)

Allocated destination: `Code/GameEngine/Source/Common/AptObject.cpp`; `consolidation_queue.py --check-tu` passed. A fresh Common-scoped planner and its `--check` passed. The plan had three approved rows: two pull donors and one mixed donor.

The merge dry run accepted no donors. `AptObject_DestroyGCPointers.cpp` failed because `AptObject::DestroyGCPointers` is absent from the class view (the generated trial also reports an illegal qualified call); the tool recommends reconciling `AptObject`. `VslotSmallBodiesAJ.cpp` has no approved row for this destination, so it was not split. No changes or claims were made. A class-view contributor can address the prerequisite; this trial made no source reduction or identity/link progress.
