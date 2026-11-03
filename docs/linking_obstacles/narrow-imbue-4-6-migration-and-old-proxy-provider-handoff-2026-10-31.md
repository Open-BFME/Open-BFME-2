### Narrow imbue 4.6 migration and old proxy-provider handoff (2026-10-31, LINK-140)

The complete narrow imbue unit moves to STLport 4.6; its two deallocate
specializations adopt the vendor's non-const two-argument signature. All six
rows remain exact. The separately claimed wide imbue unit keeps 4.5.3 and
emits the old proxy allocator after removal of its imported force-inline
override; a bodyless malloc-allocate declaration preserves the existing owner.
All five removed narrow external code providers remain byte-and-relocation
identical in the wide object, including the 25-byte proxy allocate. Wide's
one changed unrowed append copy equals the previous narrow copy. The pair
passes 7/7 rows, two EXACT EH graphs, frozen checks and strict preparation.
With the newly fetched published index `3c7a254a38` (2026-10-31 13:43), the
bounded preview retains 2/2 LINKS and 513 authored bytes. No source-path move,
new matched bytes, census gain or full-image runtime result is claimed.

The two new non-const allocator copies have only debug incoming references
in this pair. Broader selected-provider/consumer loss checks and scheduled
census confirmation remain separate; retain the outgoing audit's scope and
currency qualifications. Do not retire the LINK-140 family on this preview.
[Actual-object comparison, controls and scope](../../reverse/attempt_support/imbue-stlport46-provider-handoff-20261031.md).

Publication audit for `b4d0c4f5547f5fb9fa26dfca3ab6d6ea4fe0273d`:
INCONCLUSIVE. The index `3c7a254a38` predates outgoing base `d8afc35512fc`;
two affected source objects lack current receipts, first
`stlport_basic_ios_init.cpp`. No full consumer-loss clearance follows from
the successful 7-row hook. Keep these cases for the next scheduled census.
