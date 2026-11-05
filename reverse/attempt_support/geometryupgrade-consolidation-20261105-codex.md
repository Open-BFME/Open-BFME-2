# GeometryUpgrade consolidation dry-run handoff

The allocated `GeometryUpgrade.cpp` passed its TU allocation check; the scoped
Upgrade consolidation report passed its freshness check. The plan has 31
approved rows, three donors and one mixed file. The guarded dry run accepted
no donors and LinkGuard lists the destination and both pull donors as
census-linked.

`GeometryUpgradeDtor.cpp` fails combined-TU compilation on duplicate
`BehaviorModuleInterface` and `BehaviorModule` definitions (C2011).
`GeometryUpgradeModuleDataCtor.cpp` fails on duplicate `Rva001EAE6FHelper`
(C2011) and a special-member declaration mismatch (C2600). The tool identifies
`WallUpgradeUpdate` adoption and class-view reconciliation as prerequisites.
No source, ledger or claim changes were made; these declaration repairs belong
to another lane.
