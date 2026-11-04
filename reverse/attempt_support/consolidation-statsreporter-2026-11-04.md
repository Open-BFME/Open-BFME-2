# StatsReporter consolidation trial (2026-11-04)

Allocated destination: `Code/GameEngine/Source/Common/StatsReporter.cpp`; `consolidation_queue.py --check-tu` passed. A fresh Common-scoped planner and its `--check` passed. The plan had 28 approved rows, two pull donors and no mixed or refused files.

The merge dry run accepted no donors. `StatsReporterStrategicResults.cpp` failed because its `LivingWorldLogic::getFrame` and `rva004EE037` members are absent from the merged view; the tool recommends class-view reconciliation for `StatsReporter` and related types. No changes or claims were made. The declaration prerequisite is outside this mechanical lane; no source reduction or identity/link progress is claimed.
