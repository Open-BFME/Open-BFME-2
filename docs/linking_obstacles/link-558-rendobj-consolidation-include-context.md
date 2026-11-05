### LINK-558: rendobj constructor consolidation needs retail RefCount include context
Status: Open. Updated: 2026-11-05; inspected revision: `85b46a09f3`.
Evidence / completed: [Scoped byte checks and before/after merge guards](../../reverse/attempt_support/rendobj-consolidation-20261105-codex3/report.md); moving the existing size-optimization include block before rendobj.h preserves all 25 seed rows and lets RenderObjCtor.cpp merge with its retail RefCount deleting destructor.
Remaining / next check: apply and verify the accepted constructor merge; copy and filename donors fail bytes, and Intersect introduces a duplicate RayCollisionTestClass constructor.
Clearance: constructor prerequisite passes the scoped dry-run guard; the remaining donors stay separate. No census or real-link gain claimed.
