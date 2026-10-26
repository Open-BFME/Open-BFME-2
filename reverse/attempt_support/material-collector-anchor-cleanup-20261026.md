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

## Standard allocation-header follow-up

The same source also had one Microsoft-header queue item: a local declaration
of `operator delete[](void *) throw()`. Replace it with the VS 2003 `<new>`
header, whose global declaration has the same calling convention, parameter
and nonthrowing specification. A first include-only trial exposed duplicate
array-placement bodies in the donor `always.h`. The final source selects the
toolchain declarations first and sets the existing `_OPERATOR_NEW_DEFINED_`
guard to suppress that donor block for this translation unit. This pattern
already exists in `bfme2_mesh_material_pass.cpp`; no shared header is changed.

The normal gate again preserves eight rows (1,506 bytes), both cleanup
funclets and one EXACT EH graph. Frozen-file checks pass. The Microsoft-header
audit reports zero local definitions/declarations and zero failed scans.
The same paired link control preserves the consumer's 1,489 authored bytes,
three diagnostics and the provider's seven blockers. This removes one local
Microsoft declaration, separately from the two prior hatch retirements;
it changes no register, compiler flag, pin or ledger row.

## Publication audit qualification

The publication of `0edae3a354` over prior branch head `a5cb102c02` passed
47/47 functions across nine changed/dependent sources, one data row and nine
EXACT EH graphs. Upstream had meanwhile added `link_batch_audit.py` to the
pre-push hook; this was its one automatic run for the outgoing batch.

It reported an INCONCLUSIVE baseline (`f995f30157` versus `a5cb102c02`) and
INCONCLUSIVE input freshness: nine source objects lacked current strict
receipts, first `AnimatedParticleSysBoneClientUpdate.cpp`. It stopped before
a selected-provider/lost-byte verdict. No no-regression or loss claim follows.

Read-only receipt witnesses for both that upstream unit and the changed
material collector report `normal_current=True`, `strict_current=False`;
their sidecars contain only `cmd`, `deps`, `object`, `path` and `source`.
The new audit requires the full include-search inventory or a census-owned
compile witness through `link_census.object_current`. Thus the normal gate
does not satisfy its stricter freshness requirement. No check or receipt was
relaxed or fabricated, and no extra census/measurement runner was started.
Carry this batch into the next census with current input proof and a suitable
comparison baseline; the ordinary paired preview above remains its bounded
local linking evidence. LINK-008 tracks this open qualification.
