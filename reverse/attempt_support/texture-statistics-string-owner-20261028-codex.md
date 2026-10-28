# Texture report string storage ownership

2026-10-28, base `ec06839de0`, seat `yasinschroeder-codex`.
Preview index: `41c28839bf`, 2026-10-28 11:08. BFME 1 freshness receipt
remains within 72 hours; no donor implementation was needed for this repair.

The default picker served the report string's duplicate-definition debt in
`DebugStatisticsRecordTextureEnd.cpp`. Its real StringClass object owns the
matched 50-byte dynamic initializer at `0x007ACCE0`. The getters and cleanup
instead referenced `texture_statistics_string` in `statistics.cpp`, where an
empty private StringClass view supplied a separate one-byte object.

Keep the reporting unit's real four-byte object and initializer, exposing that
object under the existing ledger symbol `?texture_statistics_string@@3VStringClass@@A`.
The getter/cleanup unit now uses a forward declaration and extern reference.
No new global identity is inferred, and no initializer, function row, source
path or pin moves. The initializer's historical ledger label and `object-symbol`
selector remain valid and byte-verified. This corrects storage sharing rather
than claiming an independently proven source name.

## Evidence and checks

- Normal paired builds pass 41/41 rows and one data row. Including the recording
  provider and `Common/Rva007B6880Thunks.cpp` passes 960/960 rows and 18 data rows.
  All four sources also pass `link_check.py --prepare-current` with strict
  reusable receipts. Four EH graphs are EXACT.
- Both edited sources pass `find_declared_unmatched.py`. Converged-data checking
  reports no second names or unjudged rows. String and import checks pass.
- Full emitted-code comparison retains all 12 reporting executable sections
  (1,386 bytes) and all 39 getter/cleanup executable sections (1,149 bytes).
  Raw bytes and relocation sites/kinds are identical. Targets are identical
  after substituting only the intended string binding and normalizing local
  compiler labels by section/value. No executable helper was added or removed.
- Before/after reporting object SHA-256:
  `d6e08a52a3ab2a4ea49e3fc2dd5fb289b445d8b495ae6b2fc0c17675ea13050b` /
  `c3d14de63a3a8013b28cd4c548d42ad623475d05fac2c4262d4995d79daed5e6`.
  Before/after statistics object SHA-256:
  `1440a3cad88a2bdbb479bee08bc3bc62af582e189232a4a4746bd3c7266b535a` /
  `5291d3ffa7f3ba34b3a9df06e52d719afd30fc6bb140a575b0617d80b6133f36`.
- `data_ledger.py --out build/texture-statistics-owner-codex/data-ledger-final.csv`
  generates the replacement row for `0x009EE91C`: four bytes, one definition,
  26 references, owned by the reporting file. Only this exact generated row is
  copied into the committed index. The full scan reports 68 sources without
  objects; this is a scoped repair, not an assertion of complete-tree coverage.
- `repair_queue.py retire data` retires exactly two string keys. Its two mode
  keys remain; no baseline key is removed manually.
- Fixed-index ordinary previews overlay the saved original objects and final
  objects with the same two current providers. Every finding is unchanged.
  Reporting, statistics and recording remain LINKS (1,006 + 986 + 784 authored
  bytes). The unchanged thunk unit still reports
  `?rva001EAF7B@Rva001EAF7B@@QAE_NXZ` unresolved. The recording unit retains its
  unreferenced RefCountPtr constructor diagnostic. Neither is a new regression.

## Remaining prerequisites

The same file's mode debt was tested with its definition retained locally but
given external linkage, and the old statistics definition replaced by an extern.
This still moves the mode compare after the StringClass byte store and fails the
948-byte parent. The trial is reverted and logged; the string-only change passes.

The fresh naming planner and in-memory TU plan classify the reporting file as
mixed: the report and its EH rows are approved for statistics.cpp, but initializer
`0x007ACCE0` is not placed. No merge or map edit was attempted. Whole-file recovery
also needs compatible StringClass, enum/namespace and vector views, plus compiler
settings. Revisit mode storage with that ownership/codegen work; do not repeat a
plain extern substitution.

This retires two data keys. It claims no census-linked gain, image-ownership
receipt, runtime result or source-file reduction.

The outgoing batch audit is INCONCLUSIVE: index `41c28839bf` predates the base,
and affected consumer `Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. The four explicitly checked objects have strict receipts. Carry the
changed string provider and external consumers into the next scheduled census;
bounded byte/ownership verification does not establish complete link closure.

## Post-commit identity warning

The normal commit hook passes in shadow mode but reports one new binding:
initializer `??__EtextureStatisticsString@@YAXXZ` references local `_$E2`
at cleanup RVA `0x007B7050`, classified `wrong / static-unknown`. This is
not a disproven byte or relocation: `Identity.certify` returns `unknown`.
The cleanup is still the same ten-byte `mov ecx, string; jmp Free_String`.
Its DIR32 now names `?texture_statistics_string@@3VStringClass@@A`; that
name has no entry in either `RetailTruth.ledger` or `RetailTruth.pinned`.
The data-ownership index updated by this repair is not one of those inputs.
Previously the checker inferred the file-local object's address from other
matched callers; that local-data proof does not apply to external names.

A scratch-only diagnostic supplies the independently evidenced string RVA
`0x009EE91C` in a copied RetailTruth mapping. With no other changes,
`Identity.certify(object, "_$E2", 0x007B7050)` returns `retail`.
No gate, register, pin or production truth mapping was changed to obtain this
result. The outstanding task is to carry the string's independently verified
data identity into the census/identity inputs through their supported admission
path. Preserve this warning in the scheduled census handoff; the passing shadow
hook is not a claim of a clean identity scan.
