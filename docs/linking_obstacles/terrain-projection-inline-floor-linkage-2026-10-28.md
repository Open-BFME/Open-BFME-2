### Terrain projection inline floor linkage (2026-10-28)

Status: consumer repair verified in ordinary preview; global selected-copy
repair and census confirmation pending. Inspected base: `483b6ac114`;
preview index: `54b83e4f69`.

BaseHeightMapRva000687EF.cpp now keeps its unused math-header `_floorf` copy
local. All four rows, the complete EH graph, ten retained external COMDAT
digests and all external dependencies are unchanged. Its ordinary preview
changes from blocked to LINKS for 1,369 authored bytes. The existing lightmap
owner's 18-byte wrapper is verified, but that unit still reports the global
selected-copy blocker. The indexed wrong copy in Render2DSentenceDrawBFME2.cpp
belongs to another worker's claimed scope and was not edited.

[Evidence and object comparison](../../reverse/attempt_support/terrain-projection-floor-link-20261028-codex.md).
The batch audit is INCONCLUSIVE: the index predates the base and affected
consumer Common/0CreateAHeroManager21FE49.cpp lacks a current receipt.
Carry this removed-copy scope into the next normal census. Full external
consumer selection and new census-linked bytes remain unclaimed.
