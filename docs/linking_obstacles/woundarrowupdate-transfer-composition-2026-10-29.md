### WoundArrowUpdate transfer composition (2026-10-29)

The supported merge absorbs WoundArrowUpdateXfer.cpp into its approved
WoundArrowUpdate.cpp unit after reconciling the seed's transfer view. At base
`435a06a2f7`, the merge guard accepts both census-linked inputs; all six
function rows and two data rows remain exact, and the merged unit previews
LINKS for 200 bytes against index `85f6b7f40c`. This moves existing coverage;
no census gain is claimed. Strict current preparation passes. The Microsoft
header audit reports the destination clean, and neither source has a header,
data identity, code identity, or hatch register entry. The path audit found no
active tooling or include reference to the removed donor; its remaining
mentions are a source provenance comment and historical census status.

The constructor, slot 8, update, and slot 17 donors remain separate: their
private class and base views do not compose with the seed. Two mixed files also
remain. Reconcile those views and check their vtable and provider bindings before
retrying. Carry the merged provider and its consumers into the next census.

2026-11-05 mechanical consolidation recheck: no donor was accepted. The ctor
and slot-17 donors still need the `SpecialAbilityUpdate`/seed view reconciled;
`ConstIntGetters4.cpp` and `Rva00451F45Derived.cpp` split trials are blocked by a
missing `Object::m_conditionBits` view and selected-COMDAT LinkGuard evidence,
respectively. [Exact trial and next prerequisites](../../reverse/attempt_support/woundarrowupdate-consolidation-trial-20261105.md).
