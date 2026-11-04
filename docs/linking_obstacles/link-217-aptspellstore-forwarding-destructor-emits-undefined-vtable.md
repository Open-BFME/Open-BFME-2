### LINK-217: AptSpellStore forwarding destructor emits an undefined vtable
Status: Cleared in scoped link prediction. Updated: 2026-11-04; inspected revision: `320fac87ed7`.
Affected unit: `Code/GameEngine/Source/GameClient/GUI/AptSpellStore.cpp`; missing `Rva0043D16F::v00(ScienceType)` and `v04()` after `48d25c26438` removed the forwarding view's `novtable`.
Completed: restored `novtable` on that view; 16/16 byte checks and parent EH EXACT; unit links cleanly in the current-object prediction (1,137 authored bytes).
Evidence: [before/after verification and ownership](../../reverse/attempt_support/aptspellstore-novtable-link-20261104.md).
Remaining / next check: confirm both names disappear from the next real-link blockers; constructor/destructor identity reconciliation for consolidation remains separate work.
Census confirmation: awaiting; no headline gain claimed.
