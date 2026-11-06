### WorldHeightMap size/header boundary (qc-11, 2026-10-31)

The generator reports a decided contract but selects size 16 by majority despite its own retail allocation 0x120F0 and ctor-write lower bound 73940. Native W3DTerrainVisual::load pushes 0x120F0 at 0x00092193 before the constructor call at 0x000921AB. Generation adopted 0/59 units (41 field-renaming failures, 13 C2535); no header or source was retained. The word following the two known vtable entries is parseBlendTileData; its role/boundary remains unproven. Ghidra import timed out after 330 seconds and yielded no xref result. Full header recovery needs this table boundary and the allocation-backed member surface; no layout was guessed. Evidence: reverse/attempt_support/world-height-map-qc11.md.

2026-11-04: The existing canonical header now documents the allocation and third-slot proof; two lookup consumers adopted it with byte/runtime equality and passing link predictions, retiring two header-queue rows. Remaining consumer/seed views and incompatible TU compiler flags still block consolidation; see [current scope and next checks](../../reverse/attempt_support/worldheightmap-header-adoption-20261104-codex4.md).

2026-11-04: Three BaseHeightMap terrain-query consumers adopted the existing header; nine rows byte-match, three header-debt rows retired, and the combined preview preserves 2,446 linked bytes. Remaining family/flag prerequisites are unchanged; see [verification and accessor-copy details](../../reverse/attempt_support/worldheightmap-baseheightmap-queries-20261104-codex4.md).

2026-11-04 audit follow-up: strict receipts now pass for the three edited providers; the broader consumer audit remains inconclusive on the old index and missing current receipt for `0CreateAHeroManager21FE49.cpp`. Carry the scope into the next official census; see the [outgoing audit handoff](../../reverse/attempt_support/worldheightmap-baseheightmap-queries-20261104-codex4.md#outgoing-consumer-audit-handoff).

2026-11-04: Three terrain query consumers now adopt the canonical map header; local RefCountClass guard and const-accessor selection preserve complete runtime objects, nine matched rows and 2,446 census-linked bytes in prediction. Three header-debt rows retired; remaining family prerequisites unchanged. [Evidence](../../reverse/attempt_support/worldheightmap-terrain-query-header-20261104-codex5.md).


2026-11-06 stopped-fleet recovery: FlatHeightMapDoPartialUpdate and W3DSnowManagerRender now adopt the existing WorldHeightMap header; 2/2 rows remain exact, strict providers pass and owning acceptance passed; two queue rows await separate retirement. Constructor/parser and remaining cohort/TU prerequisites stay open. [Current five-consumer verification and remaining audit limits](../../reverse/attempt_support/fleet-recovery-header-adoptions-20261106.md).


Recovery commit-gate follow-up: the shadow Set_Material identity finding is not retired. Read-only comparison preserves its 52-byte provider digest c0b7cdf7e449 from index d707d2f53b to the current Snow object. This is bounded provider preservation, not a retail-identity repair or full consumer verdict. [Gate result and comparison scope](../../reverse/attempt_support/fleet-recovery-header-adoptions-20261106.md#commit-gate-shadow-finding).
