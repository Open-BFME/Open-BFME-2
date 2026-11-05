### LINK-513: AIInternalMoveToState adoption lacks two canonical virtual providers
Status: Blocked. Updated: 2026-11-05; inspected revision: 57d08ff823.
Evidence / scope: [current-object trial](../../reverse/attempt_support/aiinternalmovetostate-header-adoption-20261105-codexb.md); AIAttackMoveStateMachine.cpp and AIGuardRetaliate.cpp byte-match the adoption but lose linking through GetSnapshotName and _bfme_state_slot7.
Completed: rejected source edits restored; AIHarvest.cpp adopted independently and four passing header-queue rows retired through accept.
Remaining / next check: reconcile existing placeholder owners at 0x0033F2F7 and 0x0033F2D7 with the canonical virtual declarations, then repeat the two adoptions and their consumer checks.
Clearance: pending for the two blocked adoptions.
Census confirmation: none claimed.

2026-11-05: four serializer-only consumers adopted the canonical movement-state header and retired four queue rows; no external providers removed ([573-byte verification and scope](../../reverse/attempt_support/aiinternalmovetostate-xfer-adoption-20261105-codexb4.md)). The two missing virtual providers remain blocked.
