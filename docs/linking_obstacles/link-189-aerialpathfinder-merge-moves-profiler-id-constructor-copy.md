### LINK-189: AerialPathfinder merge moves profiler Id constructor copy
Status: Cleared for merge guard and merged-unit preview; batch/census confirmation pending. Updated: 2026-11-05; inspected revision: 01539a0c2e.
Completed: AI/AerialPathfinder.cpp now uses the shared Object header; its five function rows and global byte-match, and both original units still preview LINKS. Consolidation passes compilation/bytes but is refused for moving `??0Id@ProfileHighLevel@@QAE@XZ` earlier in link order.
Remaining / next check: merge applied, all 12 rows and the global byte-verified, merged unit previews LINKS with the same combined 3,278 bytes. Carry the scope into the next scheduled census: batch audit is inconclusive on its older baseline and missing census-grade receipts. No census gain is claimed.
Evidence / clearance: [current index, exact helper bytes, build and preview receipts](../../reverse/attempt_support/aerialpathfinder-object-view-20261103.md); merge clearance pending, census confirmation not claimed.
Guard repair: [regression controls, verifier tests and accepted dry run](../../reverse/attempt_support/aerialpathfinder-unreferenced-guard-20261105.md).
Merge clearance: [byte/EH/preview checks, register/path audit and inconclusive batch-audit scope](../../reverse/attempt_support/aerialpathfinder-merge-20261105.md).
