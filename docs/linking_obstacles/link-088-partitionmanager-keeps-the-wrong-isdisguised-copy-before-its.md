### LINK-088: PartitionManager keeps the wrong isDisguised copy before its exact owner
Status: selected-provider repair verified in the bounded cohort; other unit blockers and census confirmation remain. Updated: 2026-10-30; earlier inspected revision: 2a45addda1806342ac5c52757f63be902dcd428e.
Evidence / affected units: `PartitionManager.cpp`, `StealthUpdate.cpp` and `WeaponSet.cpp` select `?isDisguised@StealthUpdate@@QBE_NXZ` from PartitionManager. The rowed owner at 0x0004D65B in StealthUpdate.cpp emits retail's nine-byte body; the first copy uses the older UpdateModule layout and a different instruction shape. All six sources spelling the member were checked together.
Completed: a trial of the existing `/Ireference/shims/dockupdate` include directory keeps all four verified PartitionManager rows exact and corrects the field placement, but leaves the selected-copy blocker. The unit's existing optimization context still emits a different body. The trial was reversed by removing only that include-directory edit; the restored byte gate and six-source preview reproduce the baseline. All three already-linking consumers stay LINKS throughout. Raw logs: `build/c136-logic/stealth-before.log`, `stealth-after-trial.log`, `partition-build-trial.log`, `stealth-restored.log` and `partition-restored-build.log`.
Remaining / next check: reconcile the shared StealthUpdate declaration so this early emitter can bind the existing exact owner without emitting its stale copy, while preserving other inline uses and every caller row. A shared-header edit, an optimization-flag change and a renamed helper were outside this seat. Do not repeat the include-directory-only trial.
2026-10-30 follow-up: a Partition-only dllimport/forceinline selection in the
existing owned StealthUpdate link header suppresses its wrong eleven-byte
outlined copy without changing the inline body. Its only incoming relocation
was .debug$F; the existing nine-byte native owner at 0x0004D65B is now selected
before WeaponSet's later copy. Four Partition rows, two owner rows, all 564
retained external code definitions/relocations and all other loadable sections
are unchanged (section records compared as a multiset). No getStealthLevel
definition/reference existed in the control, so none is additionally removed.
The four-source preview clears this selected-name blocker from three units;
all unrelated blockers remain identical and StealthUpdateLogic retains
LINKS/5,722 authored bytes against ccafe54d1d. Shared-header dependent checks
remain mandatory. Clearance is only for this selected name, not complete
Partition/StealthUpdate/WeaponSet linking or the donor's full inline layout.
Census confirmation: pending; no gain claimed.
[Native and provider evidence](../../reverse/attempt_support/partition-stealth-selected-provider-20261030/README.md).

PartitionManager consolidation follow-up (2026-10-27): the current-map dry run
accepts no donors, preserving all already-linking donor units. Three CRT
declaration conflicts are separately repaired through `math.h` and `/MD`:
3/3 rows (129 bytes), all three target import identities, clean header scans
and unchanged 3/3 LINKS previews. This does not clear LINK-088 or the seed's
selected `updateCellsTouched` conflict. The unresolved seed providers and
private-class/flag prerequisites are recorded in the
[PartitionManager handoff](../../reverse/attempt_support/partition-crt-consolidation-20261027-codex5.md).
No merge or census gain is claimed.
