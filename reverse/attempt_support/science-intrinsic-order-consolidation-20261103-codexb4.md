# Science intrinsic declaration order (2026-11-03)

Inspected base: `adc5ccdeec`. Scope: the approved Science.cpp consolidation
group, claimed through the default picker. The scoped supported naming planner
was regenerated after the source change. The merger rebuilds the stale TU map
in memory; no placement approval or regenerated map is committed.

The initial supported dry run rejected even the seed with `bytes`. Isolated
seed composition retained 35 of 38 distinct addresses (40 ledger rows):
`getPurchasableSciences` at `001FFB64` and `playerHasPrereqsForScience` at
`001FF47D` gained unresolved `__ReadWriteBarrier` calls, and their dependent
funclet at `0076C27D` consequently failed. Composition hoisted the intrinsic
pragma above the extern declaration, which followed the last include.

Moving the declaration before the includes preserves declaration-before-pragma
order in both the standalone source and composed seed. No body, flags, alias,
pin or hatch changes. `./build.sh Code/GameEngine/Source/Common/RTS/Science.cpp`
passes all 40 rows, including four renumbered funclet pins and the existing
STLport constructor fold. The frozen-file check passes. Isolated composition
now verifies all 38 addresses. The before/after standalone objects have
identical 113 normalized COMDAT bodies/sizes, 148 external symbol facts (113
definitions and 35 unresolved names), COMDAT selection policies, no weak
aliases, 47 reference roots and 91 reference-graph owners. Their complete
reference sets and edges are identical.

The repeated supported merge trial still accepts no donor. Its census-linked
guard now reaches `Rva001FF909Dtor.cpp`, whose composed vtable
`??_7Rva001FF909@@6B@` would break another unit's selected copy. The seed's
NameKeyGenerator/ScienceStore includes enable fourteen SubsystemInterface slots;
the standalone destructor donor includes the short base. Retail VA `00BE25B4`
has fourteen slots, as already documented in ScienceStore.h. Reconcile this
owner's complete virtual contract and selected providers before retrying that
merge; do not remove or bypass the guard. This pass changes neither class.

The parser now reaches its conflicting private ScienceStore view (`m_sciences`
is absent from the canonical view); `Rva001FFA5A` and `Rva001FFEE9` also need
reconciliation. Both STL donors still lose bytes under the composed flags.
Nine mixed donors remain outside the clean merge. No source file reduction,
debt retirement, census-link gain or image-ownership gain is claimed.

Local diagnostics: `build/science-compose-diagnose.log` (before),
`build/science-compose-order.log` (after), `build/science-order-facts.log`,
`build/science-intrinsic-order.log` and `build/science-dryrun-order.log`.
