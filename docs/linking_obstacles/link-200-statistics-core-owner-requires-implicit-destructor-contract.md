### LINK-200: statistics-core owner requires its implicit destructor contract
Status: Blocked. Updated: 2026-11-04; inspected revision: `6b19bc334f`.
Completed: canonical `Rva00553E47StatsCore` adopted in `PeerDefs.cpp` and `Thread/PeerThreadPushStatsBfme.cpp`; acceptance retired two header-queue rows, 144/144 rows match, both ordinary previews retain LINKS (7,921 bytes).
Remaining / next check: `Thread/PersistentStorageThread.cpp` emits the native implicit nonvirtual destructor at `0x00383D71`; the shared header's declaration suppresses it, and an explicit empty definition adds a non-retail vptr store. Reconcile that lifetime contract and verify all consumers before retrying the remaining queue row; owner trial restored and verified.
Evidence: [scoped adoption, destructor bytes and checks](../../reverse/attempt_support/statscore-header-adoption-20261104-codex3.md).
Clearance: accepted consumers only; owner prerequisite remains blocked. Census confirmation: no new measurement or linked-byte gain claimed.

Status: Blocked for `PersistentStorageThread.cpp`; updated 2026-11-04 at `b0cc08ec59`.
`Rva00553E47StatsCore` header adoption passes PeerDefs and PeerThreadPushStatsBfme (two queue rows retired; 7,921 census-linked bytes preserved). The provider's implicit destructor at 0x00383D71 gains a non-retail vptr store with an empty explicit definition; its trial was restored and its queue row remains. Next: reconcile the shared destructor declaration/emission contract before adopting the provider. No census gain claimed. [Scoped verification and trial evidence](../../reverse/attempt_support/statscore-header-adoption-20261104.md).
