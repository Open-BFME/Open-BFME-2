# CallHelpOnDamage updated consolidation dry run

Rechecked after source changes through `ec026a8db3` (sharing a class view).
The fresh 23-row plan has six whole-file donors and two mixed sources. The
guarded dry run accepts no donors; LinkGuard lists the destination and all
five remaining whole-file donors as census-linked.

Remaining compile failures include undeclared `getModuleNameKey` and the
`CallHelpOnDamage(Thing *, const ModuleData *)` constructor (C2509/C2511), plus
missing `xfer` on `CallHelpOnDamage` (C2039). `DamageModuleDeletingDtors.cpp`
and `CallHelpOnDamageModuleDataDtor.cpp` fail byte checks. The tool recommends
reconciling views of `CallHelpOnDamage`, `CallHelpOnDamageModuleData` and
`Rva003623E5Filter`; the onDamage donor also recommends adopting `DamageInfo`.
No claims or source changes were made. The remaining declaration and byte
repairs belong to other lanes.
