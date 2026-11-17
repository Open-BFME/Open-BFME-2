# BridgeTowerBehavior base declaration preflight

The served cohort starts with BehaviorModule's primary table at RVA 007EEA7C.
BridgeTowerBehavior.cpp already includes the canonical module headers. Its
inline BehaviorModule destructor emits a 48-byte base table whose slots 2 and
3 are purecall, while retail uses GetSnapshotName at 0024A791 and xfer at
004C9C7D. Both implementations already have ledger rows in their original units.

BehaviorModule.h has no GetSnapshotName declaration. Its xfer declaration is
conditional, with a documented restriction against emitting derived tables in
that mode. Fixing the base contract therefore needs coordination with the
canonical class owner, not an extra private class or an unreviewed flag change.
Both class:BehaviorModule and class:BridgeTowerBehavior conflict with another
contributor's current claims. No source, header or ledger edit is retained.

The unchanged whole-file build passes 16/16 functions, its string reference,
and its tracked destructor funclet. The real-link bridge pass test remains
open. Table and file claims are released before selecting other work.
