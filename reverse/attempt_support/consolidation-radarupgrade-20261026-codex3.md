# Mechanical consolidation blocker: RadarUpgrade

Date: 2026-10-26
Destination: `Code/GameEngine/Source/GameLogic/Object/Upgrade/RadarUpgrade.cpp`

The approved plan has seven rows, three donors and one mixed donor. The dry run
accepted no donors:

- `RadarUpgradePoolKey.cpp`: `C2039`, `getModuleNameKey` is not a member of
  `RadarUpgrade`; the composed member definition also reports `C2270`.
- `RadarUpgradeUpgradeImplementation.cpp`: `C2143` missing `;` before `*` and
  `C2501` missing type for `Rva004B46F9::Object`.

Result: `blocked: no verified merge of two or more donors`. No files or claims
were changed. Sol owns the declaration prerequisites.

## Resolved 2026-10-28

`RadarUpgradePoolKey.cpp` had already been absorbed. The seed and
`RadarUpgradeUpgradeImplementation.cpp` were given one class view (the
`CommandSetUpgrade.cpp` UpgradeMux view; commit "RadarUpgrade: one class view
for the seed and its upgradeImplementation donor"); the dry run then accepted
both and `tu_skeleton.py --merge` absorbed the donor (8 rows, all matched).
`FireWeaponWhenDeadBehaviorDerived.cpp` stays mixed and still holds 0x004B47BF
(`??_G` of the placeholder `Rva004B46F9`, whose slot-8 body 0x004B47DB, now in the TU, has the shape of
Zero Hour's `RadarUpgrade::onDelete`; a naming inference, not yet renamed).
