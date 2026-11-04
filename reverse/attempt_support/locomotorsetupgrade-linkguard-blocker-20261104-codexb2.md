# LocomotorSetUpgrade constructor merge blocker (2026-11-04)

Allocated `Code/GameEngine/Source/GameLogic/Object/Upgrade/LocomotorSetUpgrade.cpp`;
the unchanged merge dry run accepted no donors. LinkGuard found the constructor
donor's merged object would leave these symbols unresolved, although both
current census units link separately:

- `?GetSnapshotName@UpgradeModule@@MBEPBDXZ`
- `?isSubObjectsUpgrade@UpgradeMux@@UAE_NXZ`
- `?loadPostProcess@UpgradeModule@@MAEXXZ`

The identical unresolved set also blocked the allocated constructor merges for
`ExperienceScalarUpgrade` and `CastleUpgrade`. This needs provider/header
reconciliation by another lane before retrying any of the three. No source edits
or claims were made.
