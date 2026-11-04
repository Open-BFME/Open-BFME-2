### LINK-290: PointGroupClass header adoption needs compatible static bindings
Status: Partly cleared; remaining adoptions blocked. Updated: 2026-11-04; inspected revision: `62b1ed9052`.
Completed: canonical private static bindings, renderer and transformed_loc teardown header adoption; both header-queue rows retired by accept.
Evidence: [byte/link checks and reverted pointgr.cpp trial](../../reverse/attempt_support/pointgroup-header-20261104-codexb4.md).
Remaining / next check: pointgr.cpp needs ShaderClass include/inlining reconciliation; destructor needs its nontrivial texture ownership represented in the shared header.
Clearance: changed two-unit preview preserves 12,023 linked bytes; restored pointgr.cpp also LINKS, all three preserve 23,997 bytes. Census confirmation pending.
