# WaterTracks unused cleanup view, 2026-11-04

Inspected revision: `1d3cf22691`. The default picker claimed W3DWaterTracks.cpp
and its two clean donors. The Water/ consolidation planner's original-path
evidence, alternatives and blockers were reviewed; the merge tool rebuilt the
stale TU map in memory. No regenerated map or source-path move is published.

The supported `tu_views.py` pass applied only BfmeThingSH reconciliation.
Rva000FE9E3PointBounds reconciliation was restored after its donor failed to
compile with incomplete BoundsValue fields. WaterTracksObj has a padding/vfptr
conflict. WaterTracksRenderSystem belongs to the canonical-header lane.
The ordinary merge dry runs before and after accepted zero donors: render
still collides with RealRange from BaseType.h, and flush still fails header/type
composition (including TextureClass). These are existing consolidation
prerequisites, not lost rows or newly broken link consumers.

The retained change instead deletes the unused BfmeThingSH declaration and
inline destructor from WaterTracksRenderSystemFlush_Flush.cpp. That file had
no use of the class outside its definition; its destructor marker covered an
unemitted helper. The live definition in W3DWaterTracks.cpp stays unchanged.
The redundant seed comment changes and unsuccessful reconciliation trials were
restored. The matching hatch_baseline.tsv key is removed: present_unmatched
debt decreases by one. No alias, pin, global, function row or provider is removed.

Final verification:

- `./build.sh` on the flush donor: 1/1 exact; both compiler floats verified.
- `find_declared_unmatched.py`: all defined functions already matched.
- `link_check.py`: LINKS, 391 -> 391 authored bytes against the published
  2026-11-03 20:03 census at `8661f15284`; current object inputs checked.
- A COFF comparison using allowed_symbols.Obj preserves all 11 external
  code/data providers: complete owning-section bytes, flags and relocation
  bindings. Static referents are compared by section content and offset,
  external referents by symbol name and offset. All nine external code
  providers and all 14 undefined references are unchanged.

The original-source object was recovered read-only from the object store using
the current compiler fingerprint, original source hash and source path.
Original object SHA256:
`951ec29439c3202df500015164994965366c9552b12b3c66078cc29f27b113bc`.
Final object SHA256:
`c49a59858e47ffc04bd34a66d96f10695058631052a2d35c99f2bf12ad60ed07`.
Whole-object hashes include compiler metadata; the provider comparison above
checks emitted code/data and bindings rather than treating metadata as code.

Local receipts: build/codex-watertracks-final-build.log and
build/codex-watertracks-final-link.log. Before narrowing the change, the
seed and flush also passed 25/25 function rows and their data row, including
parent-bound funclets, and both linked in preview (4,074 bytes retained).

There are no applied consolidations, destination/residual queue transfers or
path consumers to repoint. Data/identity registers and header queues keep their
current owners. No census, real-link, smoke, recovered-byte or file-reduction
gain is claimed. Further merging requires the existing header-world and layout
prerequisites; no obstacle-register entry's next step changed in this pass.
