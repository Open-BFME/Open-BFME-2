# LINK-464: Made002CCC90 consolidation needs its constructor declared

**Blocked** (2026-11-05): allocated TU `Code/GameEngine/Source/GameLogic/Object/Made002CCC90.cpp` has no safe donor merge. The guarded dry run rejects `Rva0050BD45Finish.cpp` with C2600 because `Made002CCC90` does not declare the constructor. The tool's link guard lists both census-linked units and blocks the merge. See [trial evidence](../../reverse/attempt_support/made002ccc90-consolidation-20261105.md). Next: reconcile the class declaration in a source-repair seat, then rerun the guarded merge.
