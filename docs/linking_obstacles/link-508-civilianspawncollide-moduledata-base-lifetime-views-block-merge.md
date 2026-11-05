### LINK-508: CivilianSpawnCollide ModuleData base lifetime views block merge
Status: Blocked. Updated: 2026-11-05; inspected revision: `20fa09df4e`.
Evidence / completed: [canonical handle cleanup and byte/link verification](../../reverse/attempt_support/civilian-spawn-canonical-handle-20261105.md); the 48-byte destructor now shares the constructor's canonical handle, and both units remain preview LINKS (202 bytes).
Remaining / next check: reconcile the constructor's nonvirtual ModuleDataBase cleanup and explicit vptr with the destructor's novtable Snapshot inheritance, preserving constructor EH ownership; removing novtable adds a non-retail store. Current merge dry-run still accepts no donor.
Clearance: pending for consolidation; existing unit links preserved. Census confirmation: no new measurement claimed.
