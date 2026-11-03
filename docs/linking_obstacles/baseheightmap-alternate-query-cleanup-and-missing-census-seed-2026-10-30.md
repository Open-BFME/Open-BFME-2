### BaseHeightMap alternate query cleanup and missing census seed (2026-10-30)

At base b657c77a8b81, the seed's unreferenced 242-byte alternate height query
is removed; native 0x000670B8 remains the existing matched 250-byte
getMaxCellHeight in BaseHeightMapCellQueries.cpp. The owner counter tool retires
one unmatched exemption (3660 -> 3659). All 30 paired rows, 64 bindings,
retained external object facts and three EH graphs remain exact/unchanged.
Strict preparation passes; the existing query owner retains LINKS for 939 bytes.
The supported merge remains blocked before composition: the current published
index (6fe1089c24; embedded census diagnostic 8716fcf38f) lacks the seed's
census object. No source moves; the class-view and 13 mixed-file prerequisites
remain. The correctly based outgoing audit is INCONCLUSIVE on the older index
and missing current receipt for Common/0CreateAHeroManager21FE49.cpp. Carry
the removed provider/literals and affected consumers into the next scheduled
census. No census gain or seed linking clearance is claimed.
[Verification, counter retirement and merge blocker](../../reverse/attempt_support/baseheightmap-query-cleanup-20261030-bce2/README.md).
