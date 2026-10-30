# FXShaderRenderer consolidation, 2026-10-30

Prerequisite commit: `214b97f299`, based on `92d06029b8`. The runner has
handed both commits to its fleet publisher; their history is immutable.

## Scope and placement

The supported planner was run for `Code/Libraries/Source/WWVegas/`, and its
`--check build/consolidation` snapshot check passed before composition.
The packet's lowercase destination is a spelling hint, not rename approval.
`tu_skeleton.py` rebuilt the stale TU map in memory and approved the existing
`WW3D2/FXShaderRenderer.cpp` destination for the 51-byte range erase at
RVA `0x00173FB6`. The committed map change only repoints that row's source;
it does not regenerate assignments or claim a recovered retail filename.

`tu_skeleton.py --merge` absorbs
`WWLib/stlport_vector_bfmeassignrecord32_erase.cpp` into that TU. Eight rows
remain matched, and one source file is removed. Current progress reports
20,302 source files and 47,974 approved rows; unrelated upstream work also
contributes to those absolute totals. This batch's source-file delta is -1.

## Prerequisite and retained bindings

The erase donor used private copies of vector, allocator and dispatch tags.
STLport 4.5.3's real vector header produces the exact 51-byte body when its
stock const-reference copy dispatch is used. The seed now includes that
stock algorithm header before the allocation shim, following the existing
`StlRangeEraseRva00173DF8.cpp` arrangement. Explicit specialization
declarations retain the existing copy and destroy providers instead of
emitting additional helper bodies.

Both prerequisite objects preserve every COMDAT digest and their strong,
undefined and weak external sets. The merged object contains exactly the
union of their 26 COMDATs: no added, removed or changed body. Strong and weak
external sets agree with the union. Undefined dependencies agree after
removing symbols supplied inside the merged object. Data identity therefore
has no changed binding to explain; no new storage, name or pin is introduced.

The ordinary current-object preview uses index `12b9e7a7c0` (10:11 UTC).
Before: seed LINKS, 925 authored bytes; donor LINKS, 51 bytes. After: merged
seed LINKS, 976 bytes. This is retained coverage, not a census gain.
The merge's current-object link guard also accepts the composition.

## Debt, queues and consumers

Neither absorbed donor nor destination has a code-identity or data-check
baseline key, header-adoption queue entry, data-ledger definition,
body-owner entry or flag override to transfer. The three existing seed
alternatename entries remain counted. The merge's supported hatch-counter
rewrite keeps all counts; it also removes the stale `allow=` stamp from the
unchanged pin-count entry at `0x004D9A8B`. The emitted Verifier-Change trailer
covers the generated register rewrite. No hatch is admitted.

The merge refreshes the Microsoft-header queue. The seed's existing sprintf
ABI conflict and mbstring declarations remain queued, with a refreshed
include-line reference. Header-adoption debt is unchanged.

The complete outgoing path audit covers the reference-refresh commit,
prerequisite and this merge. The erase donor is the only removed Code path.
A repository search for its full path/basename finds no active tool, hook,
workflow, include or build/config consumer. Remaining old-path mentions are
the merged source's provenance comment, the historical link census
`reverse/link_status.csv`, and the 2026-10-21 vector-helper proof. These are
retained as historical evidence. Active ledger and TU-map source columns
point to the destination. No fold proof or canonical class contract names
the removed path. The reference-refresh commit has its own dependency and
two-full-gate receipts in its evidence directory.

## Checks and remaining work

`./build.sh FXShaderRenderer.cpp`: 8/8 exact, four renumbered funclet pins
verified against parent EH data, seven string references and one import
verified. Frozen-file scan passes. `check_csv.py` and staged TU ownership
pass; EH verification reports two exact EH rows. Data checks report no
findings, and converged-data enforcement passes. Normal commit and outgoing
push hooks remain required; no runtime or image-ownership result is claimed.

The other whole donors were attempted by the merge and remain separate:

- `FXShaderRendererAddRenderingTask.cpp`: declaration ordering fails with
  RefCountClass undefined; its MeshClass inheritance also conflicts with
  the seed's private view. Reconcile actual layout and virtual slots first.
- `stlport_vector_rva001741eb_overflow.cpp` and
  `StlSweepW4Rva0017422D.cpp`: compiled composition loses byte matches.
  Their allocation/copy dispatch and template context need reconciliation.

A local unsigned-max overload alone preserves the seed but unlocks no donor.
Adding `_STLP_NO_EXCEPTIONS` with the original `_CRTIMP=` changes sprintf
from an imported call to a direct call and loses one seed byte match.
Removing `_CRTIMP=` in that trial restores all seven seed matches, but does
not establish compatibility for the other donors. These trials were reverted;
no nonmatching source remains in Code. Mixed files and the vendored-source
refusal were not split or moved.
