### LINK-200: statistics-core owner requires its implicit destructor contract
Status: Blocked. Updated: 2026-11-04; inspected revision: `6b19bc334f`.
Completed: canonical `Rva00553E47StatsCore` adopted in `PeerDefs.cpp` and `Thread/PeerThreadPushStatsBfme.cpp`; acceptance retired two header-queue rows, 144/144 rows match, both ordinary previews retain LINKS (7,921 bytes).
Remaining / next check: `Thread/PersistentStorageThread.cpp` emits the native implicit nonvirtual destructor at `0x00383D71`; the shared header's declaration suppresses it, and an explicit empty definition adds a non-retail vptr store. Reconcile that lifetime contract and verify all consumers before retrying the remaining queue row; owner trial restored and verified.
Evidence: [scoped adoption, destructor bytes and checks](../../reverse/attempt_support/statscore-header-adoption-20261104-codex3.md).
Clearance: accepted consumers only; owner prerequisite remains blocked. Census confirmation: no new measurement or linked-byte gain claimed.
