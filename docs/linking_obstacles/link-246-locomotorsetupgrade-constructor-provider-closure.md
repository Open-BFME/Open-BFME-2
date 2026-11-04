### LINK-246: LocomotorSetUpgrade constructor provider closure
Status: Blocked. Updated: 2026-11-04; inspected revision: `4ee23edebd`.
Evidence / affected units: `LocomotorSetUpgradeConstructor.cpp`, `ExperienceScalarUpgradeConstructor.cpp` and `CastleUpgrade_upgradeImplementation.cpp`; allocated unchanged merge dry runs in [shared provider evidence](../../reverse/attempt_support/locomotorsetupgrade-linkguard-blocker-20261104-codexb2.md) and [ExperienceScalarUpgrade evidence](../../reverse/attempt_support/experiencescalarupgrade-linkguard-blocker-20261104-codexb2.md).
Completed: none; LinkGuard confirms both census units link separately.
Remaining / next check: reconcile providers for `UpgradeModule::GetSnapshotName`, `UpgradeMux::isSubObjectsUpgrade` and `UpgradeModule::loadPostProcess`, then rerun the merge guard.
Clearance: no donor accepted; composition remains blocked.
Census confirmation: awaiting; no new census claimed.
