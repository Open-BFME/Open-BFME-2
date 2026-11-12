### PolygonTrigger writer and selected floorf (2026-10-28)

Status: partial repair; writer provider and census confirmation pending. Inspected
base `7dbe9f83c8`, index `41c28839bf`. Giving the unused math-header `floorf`
internal linkage removes the selected-copy failure from
`GameLogic/Map/PolygonTrigger.cpp`. Its 18 function rows and data row still
byte-verify, and strict preparation verifies it and the 14 rows of
`Common/AreaPolygonBase.cpp` together. The ordinary preview still reports
`?rva0030B2FE@Rva0030B2FE@@QAEXPAVDataChunkOutput@@@Z` unresolved; the ledger
owns that body in AreaPolygonBase, which is absent from the census preview.
The refreshed published index remains at `41c28839bf`. Verify that provider
and its consumer together in the next census; no linked-byte gain is claimed.

Reserve composition follow-up at `460c91f9d2`, index `d92e7e6635`: absorb
AreaPolygonBase_reserve.cpp into its approved AreaPolygonBase TU, preserving
15 matched rows and all external object facts. The destination previews LINKS
(694 authored bytes); the 21-byte attribution change moves existing coverage.
The writer consumer/census prerequisite above remains open. The full outgoing
audit is inconclusive on stale baseline/current receipts; carry the affected
cohort into the next census. [Composition, remaining donor blockers and
verification](../../reverse/attempt_support/area-polygon-consolidation-20261028-codexb4.md).

2026-11-04 allocated AreaPolygonBase dry-run hit a new LinkGuard refusal: its composition removes the Point constructor provider required by the currently linking Rva0030B7C2PointQuery unit; no donors accepted. Reconcile point-query provider bindings and the listed class views before retrying. [Evidence](../../reverse/attempt_support/area-polygonbase-linkguard-20261104-codex.md).

2026-11-04 follow-up: record views now agree; a fresh guarded dry-run accepts three donors (28 rows), but application stopped before writing on another worker's 0x0007FAB3 claim. Retry that accepted plan after the claim clears; parser bytes and point-copy COMDAT binding remain blocked. [Evidence](../../reverse/attempt_support/area-polygonbase-merge-screen-20261104-codexb4.md).

2026-11-12 parser-table prerequisite (base `e18ea1c5251`):
`PolygonTrigger.cpp` now defines the actual 18-byte registration cleanup for
`Rva002E3D7B` and `Rva002E3DE3`; their compiler-emitted lifetimes and the
28-byte deleting wrapper are individually verified ICF owners, with no new
pin. The constructor view in `Rva000AEFAA.cpp` declares the shared out-of-line
destructor, removing its incorrect five-byte local copy without changing any
of that source's 30 matched rows or retained COMDATs. All 29 code rows and the
data row of PolygonTrigger pass. The derived table at `0x00804C04`
still needs its existing 64-byte callback at `0x002E41EC` moved from the
placeholder class through the naming tool. Its dry run refuses the signature's
`PAX0` parameter back-reference, even though private compilation preserves the
64-byte callback and yields the correct eight-byte table (zero local bridges
or refusals). The exact unapplied source/header patch and false-reject record
are banked; safe back-reference handling needs a separate tooling fix. Full
table/queue clearance is not claimed for this prerequisite.
[Evidence and remaining slot](../../reverse/attempt_support/polygon-parser-table-20261112.md).
