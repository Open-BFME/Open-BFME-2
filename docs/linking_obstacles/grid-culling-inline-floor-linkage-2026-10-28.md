### Grid culling inline floor linkage (2026-10-28)

Status: scoped preview repaired; external consumer and census confirmation pending.
Inspected base `9dc3b3d773`, preview/census index `d92e7e6635`.
Giving gridcull.cpp's unused inline `floorf` internal linkage preserves all
48 rows, its exact EH graph and all 89 retained external COMDAT fingerprints.
Strict preparation and scoped data checks pass. Ordinary preview changes
from blocked to LINKS for 11,117 authored bytes; LINK-132/LINK-133 remain
open globally. Carry the removed-copy scope into the next normal census.
[Evidence and checks](../../reverse/attempt_support/gridcull-floor-link-20261028-codexb.md).
The outgoing batch audit is INCONCLUSIVE: the index predates the base and
Common/0CreateAHeroManager21FE49.cpp lacks a current affected-consumer
receipt. Carry that consumer into the next census. No census-linked gain is claimed.
