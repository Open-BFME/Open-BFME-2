# LevelGrantSpecialPower consolidation dry-run handoff

The allocated destination passed its allocation check and the scoped
SpecialPower report freshness check. The plan has 26 approved rows, three pull
donors and six mixed sources. The guarded dry run accepted no donors; LinkGuard
lists the destination and both rejected donors as census-linked.

`LevelGrantSpecialPowerCtorThunk.cpp` fails with C2511 because the
`LevelGrantSpecialPower(Thing *, const ModuleData *)` constructor has no
matching declaration. The module-data destructor trial reports `compile:` with
no diagnostic text, so its source-level cause is inconclusive. The tool
recommends adopting `ContainModuleInterface`, `SpecialAbilityUpdate` and
`BehaviorModule`, then reconciling the behavior and module-data views. No
source, ledger or claim changes were made.
