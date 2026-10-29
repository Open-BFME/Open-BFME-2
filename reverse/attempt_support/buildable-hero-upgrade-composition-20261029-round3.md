# BuildableHeroListUpgrade: base-view prerequisite

Inspected 29c5ceda1fb5b10685912e113655ccbcc9640b2f, 2026-10-29.
The normal picker claimed the destination and both complete donor files.
No game source, ledger row or protected register is changed by this attempt.

## Supported composition and actual refusal

The freshly rebuilt in-memory TU map approves the constructor at 0x004B8332
(49 bytes) and three implementation rows at 0x004B837F, 0x004B83D2 and
0x004B8484 (83, 178 and 102 bytes). The 28-byte deleting destructor at
0x004B8363 is in the mixed FireWeaponWhenDeadBehaviorDerived.cpp and stays
there. The proposed destination does not yet exist.

The required naming/consolidation planner reports no static-clear group
under the selected Upgrade scope. Both complete donor files pass
find_declared_unmatched. tu_views --dry-run finds a concrete UpgradeModule
conflict: the constructor's explicit m_vtable at +0 lies under the
implementation view's bases, whose own-data extent starts at +0x14.
Its proposed leaf superset does not resolve that base conflict.

The supported tu_skeleton --merge --dry-run accepts only the implementation
file's three rows. The constructor is rejected with C2504, UpgradeModule
base class undefined, followed by member-access errors in the composition.
Accepting only that one donor into a new destination would remove no net
source file. No applying merge, manual source move, class rename, alias,
vtable admission or baseline change is made.

## Next prerequisite

Reconcile the constructor's opaque base and explicit table stores with the
implementation's ObjectModuleBase/UpgradeModuleInterface/UpgradeMuxIface
inheritance using independently evidenced native layout and the canonical
module-chain workflow. The existing module-base obstacle already records
the missing base headers and the inherited-field issue. Do not flatten or
discard the conflicting fields just to satisfy the composition planner.
Verify each reconciled donor in its own prerequisite commit, then rerun the
normal merge and its provider/consumer guard. Keep the mixed destructor
source outside the merge until its separate ownership prerequisites pass.

The dry run establishes no source-file reduction, new matched bytes,
linking gain or image-ownership clearance. The saved view and merge logs are
build/continuation-20261029-round3/hero-views-plan.txt and
build/continuation-20261029-round3/hero-merge-dry-run.log.
