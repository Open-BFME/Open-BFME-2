### LINK-311: Apt pool receiver canonical header adoption
Status: Cleared for the two header adoptions. Updated: 2026-11-04; inspected revision: 293fbba275.
Scope: Rva006DB270 in AptActionInterpreter.cpp and DogmaAllocator.cpp.
Completed: both units use the existing canonical header; owning acceptance retires two header-queue rows, with 107/107 code rows and two data rows byte-matched.
Clearance / evidence: [scoped adoption checks](../../reverse/attempt_support/apt-pool-header-20261104-codexb4.md); acceptance preserves census-linked bytes in both units.
Remaining / next check: no remaining Rva006DB270 header-queue rows; unrelated AptValue root-view reconciliation remains in LINK-197.
Census confirmation: no new census or real-link gain claimed.
