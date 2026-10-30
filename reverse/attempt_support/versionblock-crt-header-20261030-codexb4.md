# VersionBlockParser CRT header cleanup

Inspected base: `9c59d3c608`. Claimed scope:
`Code/GameEngine/Source/Common/VersionBlockParser.cpp`.

Replace four copied CRT declarations with the toolchain's `string.h` and
`stdio.h`. Retail's `sscanf` call uses the import, whereas the string
operations retain direct bindings. Scope `_CRTIMP` to the stdio inclusion
and qualify the parser call through `NativeScanCrt`. Including stdio globally
with this import setting conflicts with the direct `_iob` and `perror`
declarations already included by STLport; the namespace separates those
declarations without changing C linkage. No signatures, flags, names, pins,
ledger rows or shared headers change.

Verification:

- Baseline and final `./build.sh VersionBlockParser.cpp` pass 22/22 rows,
  both string references and the one named import.
- The frozen-source check passes before and after. Both EH graphs are EXACT;
  the four renumbered unwind labels verify through their parent graphs.
- All 52 non-debug COFF sections retain their names, sizes, bytes and
  relocation counts. All 69 external symbol records (name, storage, value,
  definition status), 44 external COMDAT byte-and-relocation fingerprints
  and weak bindings are identical.
- Strict current-provider preparation passes. Ordinary preview retains
  LINKS and 1,341 authored bytes against index `12b9e7a7c0` (2026-10-30
  10:11 UTC). Its unreferenced `distance<char*>` diagnostic is unchanged.
- The Microsoft-header scan and check are clean. Scoped `refresh_queue`
  removes exactly this source's four-declaration queue entry, preserving
  unrelated entries. CSV validation passes.

Publication audit scope includes all pending commits and this staged source.
The batch's only source-path move remains W3DBuffDrawModuleDataCtor.cpp into
W3DBuffDraw.cpp. A fresh combined old-path/basename search finds no active
tool, hook, workflow, include, build/configuration or registry consumer to
update. Remaining occurrences are historical link-status/census records,
provenance comments and handoff evidence. Earlier destination verification,
protected-owner transfer and header-queue checks remain applicable; this
cleanup adds no source-path move or changed path consumer.

The staged outgoing audit against `7ed98efdf86e` (tree
`908fa20ee35ab2d769fe70a24956bfe34ed9f5de`) is INCONCLUSIVE on the older
index and 33 objects without current receipts, first
`Code/GameEngine/Source/Common/Rva003A5DA0Write.cpp`. Carry this provider,
the batch's other changed providers and affected consumers into the next
scheduled census/current-receipt audit. Full consumer selection and loss
verification remains open. No census gain is claimed.
Object snapshots, comparison results and audit output are scratch under
`build/versionblock-crt-20261030-codexb4/`.
