### LINK-207: FrameDataManager lifetime adoption adds base EH state
Status: Blocked on the MemoryPoolObject lifetime/exception contract. Updated: 2026-11-04; inspected revision: `372e613e52`.
Scope: `Common/FrameDataManagerDtor.cpp`; the canonical base adds non-retail EH code to constructor 0x0058B567 and destructor 0x0058B623. Original source restored; its queue row remains.
Completed: `GameNetwork/ConnectionManager_reset.cpp` adopts FrameDataManager, NetCommandList and ConnectionManager; all five rows pass, three queue rows retire, ordinary preview retains LINKS/438 bytes. Provider control retains LINKS/282 bytes.
Next: settle the base cleanup contract with the shared MemoryPoolObject work (LINK-188), then verify both lifetime bodies and their EH companions together. Census confirmation: no new measurement claimed.
Evidence: [byte trials, accepted consumer and remaining prerequisite](../../reverse/attempt_support/framedatamanager-adoption-20261104/README.md).
