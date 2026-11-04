### LINK-189: AerialPathfinder merge moves profiler Id constructor copy
Status: Blocked. Updated: 2026-11-03; inspected revision: d8af1ec58a.
Completed: AI/AerialPathfinder.cpp now uses the shared Object header; its five function rows and global byte-match, and both original units still preview LINKS. Consolidation passes compilation/bytes but is refused for moving `??0Id@ProfileHighLevel@@QAE@XZ` earlier in link order.
Remaining / next check: reconcile the profiler constructor emission or investigate its unreferenced-copy treatment in the guard before retrying the merge. No source move or census gain is claimed.
Evidence / clearance: [current index, exact helper bytes, build and preview receipts](../../reverse/attempt_support/aerialpathfinder-object-view-20261103.md); merge clearance pending, census confirmation not claimed.
