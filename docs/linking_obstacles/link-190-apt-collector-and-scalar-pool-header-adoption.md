### LINK-190: Apt collector and scalar-pool header adoption
Status: Cleared for AptGC.cpp and AptScalarClearPoolsBFME2.cpp. Updated: 2026-11-03; inspected revision: 950ca57fb939b7f224e8384ec528e17eec23d38c.
Completed: adopted existing AptValue/AptBoolean/AptInteger declarations, reconciled collector slot calls and scalar free-list fields, and retired five header-queue rows through accept.
Evidence / clearance: [byte checks, individual acceptance and current-object link previews](../../reverse/attempt_support/apt-scalar-header-adoption-20261103.md); both units LINKS, 510 -> 510 bytes against census 8661f15284.
Remaining / next check: the other eight AptBoolean cohort units remain queued; reconcile their separate base-layout and declaration obstacles before retrying adoption.
Census confirmation: awaiting a later scheduled census; no linking headline increase claimed.

2026-11-04: Cleared the AptInteger/AptValue/BfmeAptValue006DCD20 adoption blocker in AptAnimation.cpp by placing its unchanged loader after the pool methods; three queue rows retired, 8/8 byte matches and 4,274 linked bytes preserved ([evidence](../../reverse/attempt_support/aptanimation-scalar-header-adoption-20261104.md)).
