### Obsolete module CRC callers after native BehaviorModule cleanup

Status: Open; SpawnBehavior repaired, seven measured CRC units remain. Updated:
2026-11-06, base b4e415d620; real-link artifact e185a327a7.

SpawnBehavior's unrowed donor CRC body is unused by tables or outside consumers.
Removing it preserves3/3 rows, the data row, all579 retained code definitions and
their relocations, the initializer ordinal and normal/private provider equality.
The owning counter retires one hatch. Its current preview now LINKS93B; a later
real link/census must confirm the removed blocker. No runtime clearance claimed.

BridgeTowerBehavior, CreateObjectDie, DieModule, FXListDie,
SpecialPowerCompletionDie, SpecialPowerModule and AssistedTargetingUpdate still
need native class/table profiles. Their current table references keep the CRC
symbols live, even where no explicit donor CRC body remains. SpecialPowerModule
also has two leaf CRC callers whose own tables retain those methods. Delete no
provider before reconciling those emitters together.

[Body-specific prerequisites and verification](../../reverse/attempt_support/spawn-obsolete-crc-20261106/README.md).

2026-11-06 AssistedTargetingUpdate prerequisite: native updateC4B1E0/slot0 and primary post-loadC4AF64/slot1 now have verified real member bodies (6B FOREVER /5B UpdateModule forwarding). Both genuine ICF rows retain old owners/proofs, normal7/7 and pool-key EXACT EH pass, two markers retire. The unit remains CRC-unlinked; no table/lifetime clearance claimed. A canonical0x20 ctor+xfer private probe is3/3 with EXACT ctor EH, but its lifetime/table bindings are not applied. [Proof and coupled repair boundary](../../reverse/attempt_support/assisted-native-callbacks-20261106/README.md).

Publication audit for SpawnBehavior repairbe723e22e6: INCONCLUSIVE against indexe9f0686bd3/basee4e031a8d0fa72766b87d4324884fd9dcc6406b8, one missing current receipt (SpawnBehavior.cpp). Scoped3/3, data, DIR32 and provider checks pass; a later current-consumer/census pass must confirm the real-link result.
