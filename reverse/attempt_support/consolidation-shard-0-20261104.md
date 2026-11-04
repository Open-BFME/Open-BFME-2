# Mechanical consolidation shard 0/5 — 2026-11-04

Continuation of the allocated BFME 2 consolidation shard. The full allocator
listing (`consolidation_queue.py --limit 100000`) showed unheld candidates.
No merge from this continuation landed; no net source files were removed and
no rows or debt were retired.

## Attempt outcomes

- `AITNGuard.cpp`: the merge tool accepted three unchanged constructor donors
  (12 approved rows) and its census LinkGuard passed. The ordinary commit hook
  rejected the result because the composed TU declares a private
  `AITNGuardInnerState` already covered by `AITNGuard.h`. The merge trial was
  restored and all seven file/RVA claims released. Details and TU verification
  are in [the focused evidence](aitnguard-partial-merge-20261104.md).
- `DelayedDeathBody.cpp`: dry run refused before composition because the
  census-linked destination and two donor units are missing from the census
  index. Exact report: `link guard: census-linked unit(s) missing from the
  census index: Code/GameEngine/Source/GameLogic/Object/Update/DelayedDeathBody.cpp`.
  No retry or source change.
- `DelayedUpgrade.cpp`: no donors accepted; its implementation donor fails
  because `DelayedUpgrade::upgradeImplementation` and the referenced member
  are absent from the destination view. The tool requests class-view
  reconciliation.
- `EvaAnnounceClientCreate.cpp`: no donors accepted; constructor, slot and xfer
  donors fail on missing member declarations in the destination class view.
- `GrantUpgradeCreate.cpp`: no donors accepted; donor trials report duplicate
  `SubsystemInterface`, `Player`, `Module`/`ObjectModule`, and `StringBase`
  declarations, plus a byte rejection. Class/view reconciliation is needed.
- `MemoryReadFile.cpp`: no donors accepted; its create donor conflicts on a
  duplicate `StringBase` template definition.
- `gamebrowserpinger.cpp`: no donors accepted; donors need `Rva00803080`
  members/layout and a consistent `Gen008030A0` vtable declaration.
- `BridgeTowerBehavior.cpp`: no donors accepted; donor trials conflict on
  duplicate `SubsystemInterface`, `Xfer`, and `GameLogic` views and missing
  behavior members. Class/view reconciliation is needed.

Each candidate passed its allocation check and had a fresh scoped name-lane
snapshot before planning. Dry-run refusals were left unchanged. The next
allocated listing still contains untried candidates; resume with the next
untried TU and keep within shard 0/5. Do not repeat these trials until their
named prerequisites or the census index change.
