### LINK-536: AI TU header environments and insert COMDAT block consolidation
Status: Open. Updated: 2026-11-05; inspected revision: `ffb486dac9`.
Evidence / affected units: `Code/GameEngine/Source/GameLogic/AI/ai.cpp` and its 26 donor candidates; [trial and cleanup evidence](../../reverse/attempt_support/ai-tu-cleanup-20261105.md).
Completed: merge dry-run accepted no donors; removed redundant seed macro blocks and three empty optimization directives, preserving all runtime object contents and the 519-byte clean link preview.
Remaining / next check: reconcile StringBase/header environments and canonical-header prerequisites before retrying the merge; preserve other consumers of the `StlSweepR3Rva002FED53.cpp` insert COMDAT, which the current link guard rejects after composition.
Clearance: pending; no donor moved and no merge/link improvement claimed.
Census confirmation: not claimed; local preview used the 2026-11-05 15:52 index at `112a456a2c`.
