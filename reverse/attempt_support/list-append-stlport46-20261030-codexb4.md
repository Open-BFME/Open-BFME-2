# List append wrapper: STLport 4.6 header migration

Base: `497fe9e0f0`, after rebasing the runner's pending batch onto
`origin/master` at `33564ef244`. Scope: RVA `0x001B4D0E`, eight bytes, in
`Code/Libraries/Source/WWVegas/WW3D2/Rva001B4D0EAppend.cpp`.

## Target facts and change

The selected census blocker predates `d98221c12c`, which already bound the
wrapper to the existing native list push-back provider. Before this change,
the current and census-only previews already reported LINKS for the wrapper.
This change selects the supported STLport 4.6 headers via `// stlport46`,
retains the provider specialization declaration and records the migration in
the row through `tools/add_match.py --replace-existing`. Its original
STLport 4.5.3 recovery reference remains identified in the source comment.

Retail establishes the receiver adjustment of 12 bytes and the callee ABI;
the enclosing type and 72-byte element still have no recovered semantic
identity. This migration supplies no new naming or layout evidence.

## Verification

- Before and after, `tools/find_declared_unmatched.py` finds all definitions
  matched, and `./build.sh` verifies the wrapper's one row.
- Comparing objects built through `./build.sh`, the single external COMDAT
  fingerprint remains `a926590d5602`, size 8. Both external symbol records,
  the empty weak-symbol set and the empty alias map are unchanged. This
  comparison does not claim identical debug sections.
- Strict `link_check.py --prepare-current` verifies 29/29 rows across the
  wrapper and `Code/Libraries/Source/WWVegas/WWLib/StlportListInsertFootprints.cpp`.
  The provider's renumbered funclet is verified through its parent EH graph.
- Joint ordinary preview against the published 2026-10-30 10:11 index at
  `12b9e7a7c0` reports 2/2 LINKS: 8 wrapper bytes and 837 provider bytes.
  These are previews; no census gain is attributed to the migration.

## Outgoing audit and remaining scope

`tools/link_batch_audit.py --base origin/master --tip
9b6367f8b10bab821dc5ccbdc9fd07880f7b1f57 --sources-from
build/append46-codexb4/verified-sources.nul` audits the complete staged outgoing
batch, including the ten previously queued commits. It exits 2,
INCONCLUSIVE: the index predates the outgoing base, and 15 source objects
lack current receipts, first `Code/GameEngine/Source/Common/BfmeConv1456.cpp`.
Full consumer selection/loss verification remains open. Carry the wrapper,
native push-back provider and affected consumers into the next scheduled
census/current-receipt audit; no direct census or smoke run was started.

The entire outgoing batch has one source-path removal: the previously
verified W3DBuffDrawModuleDataCtor.cpp merge. Immediately before publication,
the path-consumer audit across active tools, hooks, workflows, sources,
shims, reverse records and docs finds only the destination provenance
comment and historical attempt-support evidence. No active path consumer
requires an update. Its debt, header, data, EH and provider checks remain
recorded in `w3dbuffdraw-consolidation-20261030-codexb4.md`; this migration
adds no path move or hatch.
