# UnpauseSpecialPowerUpgrade canonical bases

Inspected revision: `b00541981f`, 2026-11-04.
Scope: `Code/GameEngine/Source/GameLogic/Object/Upgrade/UnpauseSpecialPowerUpgrade.cpp`.

Behavior-side change: use the existing UpgradeModule header instead of the
private ObjectModuleBase, interface and mux scaffolds. Module data and object
remain at +4/+8, and the UpgradeMux receiver remains at +0x10. The removal
implementation now calls the canonical isAlreadyUpgraded method at mux slot 0.
No constructor/destructor behavior scaffold is changed.

Module-data change: include the registered Rva00253487Base header and remove
the private 0x118-byte layout and explicit WeaponSetUpgradeModuleData table
reference. The existing UnpauseSpecialPowerUpgradeModuleData constructor
receives its vptr store from ordinary C++ initialization and retains its
fields at +0x118/+0x11C. Its emitted table is 124 bytes with 31 relocations;
slots 1/2/3 use ModuleData loadPostProcess/GetSnapshotName/xfer, slot 10 uses
Rva00253487Base::slot10, and slot 30 uses ModuleData::slot30. These are compiled
shape observations, not a new original class-name or source-path claim.

Verification:

- Frozen-file checks before and after: all defined functions already matched.
- Normal build after each base change: 8/8 rows matched, including compiler
  funclet $L1222, whose parent EH data places its renumbered label at
  0x0078ECFD. One string literal verified; float/import reference checks passed.
- The owning header lane accepted UpgradeModule and Rva00253487Base and
  retired both queue rows; no queue row for this unit remains.
- Link preview after both changes: LINKS, LINKED 334 -> 334 bytes against
  census 2026-11-04 02:25 at `5a13f2cd61`.
- Data identity shadow check: zero findings, zero outside the baseline.

These are per-unit previews. No new census, real link or smoke result is claimed.
The separately queued behavior constructor and shared derived-destructor file
are outside this unit and retain their existing prerequisites.
