### Castle/shroud canonical Module storage views (2026-10-30)

DrawableShroud includes the canonical eight-byte Module base and retains the
observed `+18` castle ID in an address-named partial view. Its separate module
lookup reads only base ModuleData at `+4`, then data `+4C`; the results need not
share one concrete derived class. All five rows and EH remain exact, and all
17 external code definitions and actual relocation destinations are unchanged.
No new definition/provider is emitted. Literal/strict/frozen and owning header
acceptance pass, retiring one Module queue row. The changed-pair preview against
`ccafe54d1d` retains 2/2 LINKS and 1,268 authored bytes. No shared header, ledger,
pin, alias, hatch or path changes. Full consumer/census confirmation remains
pending. [Shroud evidence](../../reverse/attempt_support/castle-module-headers-20261030/shroud.md).

The shroud shadow data check retains its pre-existing compiler-guard name
finding at `009FEC4C`: original and changed objects have the identical guard
name, storage and data, while the data ledger retains the former clearer owner.
No data-ownership or debt retirement is claimed for it; enforced converged-data
checks pass.

The separate castle helper adoption retains its observed four-byte storage at
`+14` over the canonical base. Native `398064` tests that storage and `398069`
passes the unchanged module pointer to the existing checkValid owner; the
original type/name is not recovered. All four rows, EH and four external code
definitions/relocations remain identical. The owning acceptance tool retires
its one Module queue row. The pair conserves 1,268 authored LINKS bytes and
retires two header rows, with no new body/provider or shared-header change.
[Castle helper evidence](../../reverse/attempt_support/castle-module-headers-20261030/pending.md).

Outgoing audit: INCONCLUSIVE on older `ccafe54d1d` versus base `6d6ae2f4d5`
and the missing current CreateAHeroManager receipt. Carry the changed pair and
affected consumers into the next scheduled census; the bounded preview and
header acceptances do not clear the full consumer selection/loss scope.
