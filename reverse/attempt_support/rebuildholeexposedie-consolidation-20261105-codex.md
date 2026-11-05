# RebuildHoleExposeDie updated consolidation dry run

Rechecked after the approved header and row-routing changes since the 2026-10-25
trial. The fresh plan has 15 approved rows, three pull donors and one mixed
source. The guarded dry run accepted no donors; LinkGuard lists the destination
and the module-data destructor donor as census-linked.

`DieModuleDeletingDtors.cpp` fails with C2511 because
`RebuildHoleExposeDie(EmitVtableTag *)` is not declared in the selected view.
`RebuildHoleExposeDieModuleDataDtor.cpp` fails byte verification. The tool
recommends adopting the canonical `AI`, `DieModule` and `PlayerList` views and
reconciling the `RebuildHoleExposeDie` and module-data declarations. No source,
ledger or claim changes were made; these declaration and byte repairs belong to
other lanes.
