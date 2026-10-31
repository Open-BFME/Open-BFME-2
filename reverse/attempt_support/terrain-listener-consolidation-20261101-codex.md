# Terrain resource listener composition

Base: `3261895e6c`. Scope: `TerrainResourceManager.cpp` and its notifier,
clear and destructor donors. The listener name remains an address-derived
private view; this change does not recover its original class identity.

## Reconciliation

The four units declared different prefixes of `Rva00359E04Listener`'s five
virtual slots. `tools/tu_views.py --class Rva00359E04Listener` makes their
declarations identical, preserving the existing slot order and signatures.
The clear unit already had the complete declaration; only the seed, notifier
and destructor sources change. No function body, layout field, pin, flag,
ledger row or register changes in this prerequisite.

The owning tool verifies layouts, external symbol identity, byte matching
and declared-unmatched status before retaining the change. The supported
merge dry run goes from no accepted composition to the seed plus
`Common/Rva00359E04Notifier.cpp`. The four-source ordinary link preview
retains 4/4 LINKS and 4,055 authored bytes.

## Index currency

The published index still attributed `?name@Rva00359E8DNamed@@QBEPBDXZ` to
`SubsystemNameGetters4.cpp`, although `c1db761559` moved its only definition
to the seed. The unchanged seed verified 34/34 but its ordinary preview
reported that stale duplicate. The documented local `link_check.py
--update-index` refreshes current objects and clears it without changing
source or census history. Local index base: `3261895e6c`; underlying census:
`85e8af1a53`, 2026-10-31 16:54. No census-linked gain is claimed.

## Remaining prerequisites

The other six donors remain refused: `_List_base` redefinition in Clear,
declaration ordering in the destructor, incompatible `ResourceCell` views,
the constructor's explicit Snapshot vftable declaration, the claim unit's
argument declaration, and the Xfer unit's incompatible manager view.
The existing CRT/provider and affected-consumer census prerequisites remain
open. Reconcile each donor separately before another supported merge trial.
