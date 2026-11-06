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
