# GrabPassengerSpecialPower consolidation dry-run handoff

The allocated destination passed its allocation check and the scoped SpecialPower
planner freshness check. The current plan has 17 approved rows, three pull
donors and two mixed sources. The guarded dry run accepted no donors; LinkGuard
lists the destination and all three pull donors as census-linked.

Compilation reports an undefined `SpecialPowerModule` base (C2504) in
`GrabPassengerSpecialPowerDoAtObject.cpp` and a missing
`GrabPassengerSpecialPower(Thing *, const ModuleData *)` declaration (C2511)
in `GrabPassengerSpecialPower_doSpecialPower.cpp`. The tool recommends
adopting `SpecialPowerModuleData`, `SpecialPowerModuleInterface` and
`Rva00045411BitSet`, then reconciling views of
`GrabPassengerSpecialPower`, `GrabPassengerSpecialPowerModuleData` and
`SpecialPowerModule`. No source, ledger or claim changes were made; these
declaration repairs belong to another lane.
