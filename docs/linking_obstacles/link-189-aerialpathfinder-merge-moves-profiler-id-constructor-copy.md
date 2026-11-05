### LINK-189: AerialPathfinder merge moves profiler Id constructor copy
Status: Merge application pending. Updated: 2026-11-05; inspected revision: 9f8815d896.
Completed: AI/AerialPathfinder.cpp now uses the shared Object header; its five function rows and global byte-match, and both original units still preview LINKS. Consolidation passes compilation/bytes but is refused for moving `??0Id@ProfileHighLevel@@QAE@XZ` earlier in link order.
Remaining / next check: the guard now passes the census reference status to both copy comparisons; the supported dry run accepts all 12 approved rows. Apply and verify the merge, register transfers and path consumers. No source move or census gain is claimed.
Evidence / clearance: [current index, exact helper bytes, build and preview receipts](../../reverse/attempt_support/aerialpathfinder-object-view-20261103.md); merge clearance pending, census confirmation not claimed.
Guard repair: [regression controls, verifier tests and accepted dry run](../../reverse/attempt_support/aerialpathfinder-unreferenced-guard-20261105.md).
