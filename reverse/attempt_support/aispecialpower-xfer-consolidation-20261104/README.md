# AISpecialPowerUpdate save/load consolidation, 2026-11-04

Base: `b2e6d2bb8e`. The default picker claimed the approved Update TU and
five donors. The original-path planner retains Object/AISpecialPower as a
WorldBuilder hint only; the current in-memory map approves the provisional
Object/Update TU. No original retail path or new TU approval is asserted.

The supported class-view reconciliation found differing base clauses and
incompatible module-data views. Its unused BehaviorModuleBase change was
restored. The bounded repair instead makes the existing TU and xfer donor
share their AISpecialPowerUpdate declaration: existing getter/update/xfer
methods, bytes +0x20/+0x21, padding, and the existing +0x24 pointer spelling.
The xfer body uses its existing slot-1 transfer view through that pointer.
This retains the seed's names; no new semantic name or pointer-product identity
is inferred. No header, flags, pin, alias, data owner or ledger identity changes.

Declaration prerequisite checks:

- Normal build: 7/7 rows exact, one string and one float reference verified.
- find_declared_unmatched: both sources pass; EH parent EXACT.
- Both sources' complete external COMDAT digests, strong definitions and
  undefined/weak/common bindings are unchanged (declarations.json).
- Ordinary link preview: both LINKS, 410 -> 410 and 153 -> 153 authored bytes,
  census/index measured at a62ac1c10b, 2026-11-04 07:28 UTC. This is a preview,
  not a new census measurement.
- tu_skeleton --merge --dry-run accepts the TU and xfer donor (7 rows).
  Other donors still fail: ctor lacks the shared constructor declaration;
  dtor needs its pointee view reconciled; post-init needs module-data fields;
  map-load needs its secondary interface reconciled. Two mixed sources remain.

The affected pair has no data/identity debt key or header-queue row on the
removed donor. Existing seed data-ledger owners remain. Remaining header debt
belongs to the surviving TU and four other donors and is not retired here.
