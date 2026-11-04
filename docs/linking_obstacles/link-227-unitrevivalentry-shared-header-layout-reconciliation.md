### LINK-227: UnitRevivalEntry shared-header layout reconciliation
Status: Open. Updated: 2026-11-04; inspected revision: ac936f239c62.
Evidence / affected units: the ten queued UnitRevivalEntry header consumers; [trial and verification evidence](../../reverse/attempt_support/unitrevivalentry-header-20261104-codex5.md).
Completed: UnitRevivalTrackerRva0037F2C0Finish.cpp and ArmySummaryRevivalSpawn.cpp now include the shared header; five rows byte-match and owning-lane acceptance retires two header-queue entries.
Remaining / next check: eight consumers remain; reconcile +0x14/+0xB0 helper identities and lifetimes, inspect provider C2011 diagnostics, and map opaque views/member uses before retrying adoption.
Clearance: the two changed consumers pass ordinary combined link preview, preserving 423 -> 423 linked bytes against index a62ac1c10b; remaining consumers are not cleared.
Census confirmation: no new census; no linked-byte gain claimed.
