### LINK-322: AODCrushCollide destructor view blocks TU merge
Status: Open. Updated: 2026-11-04; inspected revision: `7e66c0c0fb`.
The initial merge loses the destructor donor's synthetic CollideDtorB2 vtable; the family deleting-destructor donor also fails bytes. The destructor now adopts shared UpdateModule: both rows are exact, header acceptance retires its queue row, and its current-object preview retains 60/60 linked bytes. Retry the guarded merge; the family donor's byte mismatch remains. [Evidence and checks](../../reverse/attempt_support/aodcrushcollide-consolidation-20261104.md).
Census confirmation: awaiting; no linking gain claimed.
