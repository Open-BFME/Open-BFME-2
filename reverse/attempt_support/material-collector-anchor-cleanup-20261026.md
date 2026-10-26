# Material collector: current provider control and obsolete anchor removal

The default link queue served `MaterialCollectorCollectMaterials.cpp` on
upstream `a91e877b4d`, naming its existing `Get_Single_Texture` row. The whole
source and prior texture-copy/buff-math attempts were read; the file and
`0x0015A180` were claimed before work. Frozen-file checks pass before/after.

Against published index `f995f30157` (2026-10-25 21:36), the consumer alone
still reports a wrong selected `DynamicVectorClass<VertexMaterialClass*>::Add`.
The current shattersystem source already has the declaration-only repair
recorded in LINK-012. Its own normal gate passes. Checking both current
objects together clears the consumer **before** any edit: its ordinary
preview is 0 -> 1,489 authored bytes. This confirms inherited repair and
does not credit new linking bytes to this cleanup.

Remove the unused `BfmeVciAnchorElem`/`bfmeVciAnchor` construction scaffold and
its two optimization pragmas. The whole source still passes all **eight rows
(1,506 bytes)**, including the complete 1,238-byte collection loop and 42-byte
texture getter. The parent's EH graph remains EXACT, with both renumbered
cleanup labels verified by the normal gate. No row, extent, pin, class layout,
compiler flag, shared header or source path changes.

The paired ordinary preview after removal is identical: the consumer links
for 1,489 authored bytes, with its same three unreferenced diagnostics.
Shattersystem retains three unresolved, two COMDAT and two selected-copy
findings; the combined command correctly exits nonzero. No family, strict,
runtime or census clearance is claimed.

`hatch_counters.py --update` removes exactly this file's two pragma entries,
each with count one, and makes no unrelated register change. Those two retired
hatch occurrences are the new result; matched and C++ exact bytes are retained.
