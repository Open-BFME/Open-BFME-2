### LINK-495: Rva0052413E owner lifetime and constructor contract
Status: Blocked for the remaining two header adoptions. Updated: 2026-11-05; inspected revision: `e633f06883be`.
Completed: five consumers accepted the canonical header and retired five header-queue rows; scoped build passes 89/89 rows including the restored constructor source, and all five changed units preview LINKS with 2,246 linked bytes preserved.
Remaining / next check: reconcile the canonical constructor's `throw()` with `StrategicHUD::CommandUIImpl`'s native EH state at 0x005D2BD4, and represent the implicit vector member destruction required by `Rva0052413EDtor.cpp`; both queue rows remain.
Evidence: [accepted scope, reverted trial and verification](../../reverse/attempt_support/rva0052413e-header-consumers-20261105-codex3.md).
Clearance: five consumer adoptions only; owner/header reconciliation pending.
Census confirmation: no new census claimed; preview index `c95fcfcfcd` (2026-11-05 05:17).
