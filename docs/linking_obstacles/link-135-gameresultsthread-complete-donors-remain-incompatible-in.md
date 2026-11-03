### LINK-135: GameResultsThread complete donors remain incompatible in composition

Status: Blocked on allocator/EH composition and startup include reconciliation.
Updated: 2026-10-28; inspected revision: `8416feb308`.
Evidence / affected units: GameResultsThread.cpp, its worker, queue startup,
NarrowStringRecord0041A5D2Dtor.cpp and NarrowStringRecord28DequeDestroy.cpp.
[Scoped cleanup and trials](../../reverse/attempt_support/gameresults-cleanup-20261028-codexb.md).
Completed: removed the seed's redundant local free declaration and refreshed
its Microsoft-header queue entry. All 14 seed rows remain exact; all 620
external providers and 11 undefined references are unchanged. Strict receipt
passes; ordinary preview retains LINKS for 902 bytes against `d92e7e6635`.
The verified private-view trial accepted zero additional donors and was reverted.
Remaining / next check: inspect worker/teardown allocator and EH differences;
reconcile startup's AsciiString include closure. An SDK-first include-order
trial still reaches nested sweep/windows.h and fails redefinitions; it was
reverted. Replace that closure coherently before retrying SDK migration.
Clearance: seed local declaration cleanup only. Batch audit is INCONCLUSIVE:
index predates the base and Common/0CreateAHeroManager21FE49.cpp lacks a
current receipt. Carry this provider/consumer scope into the next census.
Census confirmation: no linking, ownership or source-file reduction claimed.
