### LINK-219: AptValue constructor adoption needs canonical virtual providers
Status: Blocked. Updated: 2026-11-04; inspected revision: `4fad46fa2d`.
Evidence: [predicate adoption and reverted constructor trial](../../reverse/attempt_support/aptvalue-header-predicates-20261104.md).
Completed: three predicate units adopt BfmeAptValue006DCD20.h and retain 641 predicted linked bytes; three header debts retired through accept.
Remaining / next check: reconcile the twelve canonical virtual slot providers before adopting AptValueConstructorBFME2.cpp; its nonretail placement-new anchor also instantiates an abstract base. Removing that anchor and directly emitting the constructor matches bytes but predicts 127 -> 0 linked bytes, so the complete trial was reverted.
Clearance: pending for the constructor; predicate cohort passes byte and link checks.
Census confirmation: awaiting; no new census claimed.
