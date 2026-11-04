### LINK-333: ObjectSMCHelper header and destructor merge prerequisites
Status: Open for consolidation. Updated: 2026-11-04; inspected revision: `aca9a34025`.
Affected units: ObjectSMCHelper.cpp and ObjectSMCHelperDtor.cpp; no current link failure demonstrated.
Completed: canonical Drawable and Thing adoption accepted; two header-queue debts retired, five byte matches retained, current-input link preview unchanged at 622 bytes.
Remaining / next check: reconcile the destructor's base/container declarations and compiler settings separately before retrying its rejected TU merge; ModelConditionFlags adoption remains open.
Evidence: [header acceptance and object comparison](../../reverse/attempt_support/objectsmchelper-header-debt-20261104-codexb.md), [merge prerequisite](../../reverse/attempt_support/objectsmchelper-consolidation-20261104-codexb.md).
Clearance: Drawable/Thing header subset only; unchanged runtime object contents and current-input link preview against the 2026-11-04 20:47 census index at `f12552d0a7`.
Census confirmation: no new measurement or gain claimed.
