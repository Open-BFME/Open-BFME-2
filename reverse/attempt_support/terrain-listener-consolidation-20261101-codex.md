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

## Applied notifier merge

After the listener prerequisite, the supported merger absorbs the notifier
and repoints its 15-byte row at `0x00359E04` into the approved TU. One source
file is removed; no matched row is added or lost. The TU verifies 35/35 rows,
its literal/import checks and frozen declarations. Ordinary previews retain
LINKS for all three surviving affected units, totaling the same 4,055
authored bytes as the four input units.

Actual-object comparison against the verified pre-merge seed and notifier
retains all 83 unique COMDAT fingerprints. There are no changed, removed or
new copies, no lost or new external definitions and no new undefined names.
The protected hatch update has no net register diff; data and identity debt
keys do not move or retire, and the other header-queue prerequisites remain.

The shadow identity finding on `?rva0035A2DC@Rva0035A2DC@@QAEXPAURegion3D@@M@Z`
binding `??_9@$BA@AE` at `0x005CC208` predates this change. A controlled
official build and identity scan of the prerequisite's parent and current
source produce the same single wrong-binding key. The merged TU retains
that key. It is unresolved debt, not newly introduced or retired here.
[Object and identity controls](terrain-listener-controls-20261101-codex.json).

## Outgoing path audit

Audited both outgoing commits after rebase onto `0d2cdb9d27`. The removed
notifier path has no active references in tools, hooks, workflows, source
includes, shims, root build/configuration files or path-keyed registers.
Its remaining mentions are this historical handoff and the merged TU's
source-provenance comment. Function/TU ledger ownership is repointed by the
merger; no regenerated TU map is committed. Header queues and surviving
data/identity keys are retained. The post-rebase 43-row build and the
83-COMDAT union comparison pass again. Broader affected-consumer/census
confirmation remains separate from these scoped checks.
