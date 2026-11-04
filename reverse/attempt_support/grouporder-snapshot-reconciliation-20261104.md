# GroupOrder Snapshot reconciliation, 2026-11-04

Inspected base: `6f7fb4d6f7`; local preceding commits `8418b6b626`, `b66aa12da3`.
Scope: GroupOrder.cpp and its default, copy and holder constructor shards.

The seed already derives from the shared Snapshot ABI. Its destructor documents
retail stores of GroupOrder table 0x00C6A520 followed by Snapshot 0x00BBB554.
The constructor shards instead used a plain explicit vptr or an invented
EmptyBase lifetime. Replace those surfaces with the seed's Snapshot inheritance,
virtual destructor and slot-3 xfer declaration, letting the compiler install the
vptr. All four now declare the same constructor overloads and 0x18-byte view.
The default constructor's vector<AsciiString> was only an empty-constructor fold;
use the existing copy/holder ScienceType vector identity consistently. Member
spellings follow the seed's offsets; the two trailing words are unsigned IDs,
not pointers. No new name, pin, alias, hatch or code row is introduced.

Verification before composition:

- find_declared_unmatched.py passes separately for all four sources.
- ./build.sh on the four sources: 16/16 rows exact, including the holder cleanup
  funclet and EH handler, and one data row. No literal/import findings.
- Current-object link_check.py: four LINKS before and after, 939 -> 939 authored
  bytes against index f12552d0a7 (2026-11-04 20:47). This is a preview, not a new
  census or real-link measurement.
- git diff --check passes.

The original dry run accepted no donor: explicit vtable declarations collided
with the seed's compiler vfptr, and constructor declarations were absent from
that seed. Those class prerequisites are now removed. Composition remains a
separate tu_skeleton operation and must pass its own byte/link guard. The
source-layout planner has no original-path evidence for these shards; its
routing warnings are not TU approval. Only the current in-memory TU map can
approve the move. Allocator specializations and compiler options remain to be
judged by the composition trial.
