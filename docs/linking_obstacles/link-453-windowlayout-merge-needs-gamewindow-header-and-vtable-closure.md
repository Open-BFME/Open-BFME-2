### LINK-453: WindowLayout merge needs GameWindow header and vtable closure
Status: Blocked. Updated: 2026-11-05; inspected revision: `006a74b68c`.
Evidence / next check: [Current dry-run and claim prerequisites](../../reverse/attempt_support/windowlayout-consolidation-20261105.md). `window_layout.cpp` conflicts with the seed's canonical GameWindow include; `BfmeQuickMatchScreenBaseDefaultCtor.cpp` loses linkability through slot7 and its emitted vtable. Acquire the held GameWindow consumer scope for header reconciliation, preserve chain-call bindings, and prove vtable providers before repeating the merge. No source edit or clearance; census confirmation pending.

2026-11-13, inspected `bc1ac42b01d`: the Apt constructor's seven-slot view
still falls short of both native nine-slot tables. Its first cleanup is proven
by the parent FuncInfo to call base destructor `538C5F`, not operator delete.
Both native lifetime folds need duplicate-view reconciliation; a base-only
virtual-destructor change would synthesize an incomplete Apt destructor and is
unsafe to bank. The WindowLayout installer tie remains unproved. Untouched
three-source baseline passes 15/15 rows; no source, queue or table retirement.
[Native slots, cleanup proof and coupled repair prerequisites](../../reverse/attempt_support/aptwindowlayout-interface-prerequisites-20261113-root20.md).
