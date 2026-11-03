### GameLogic canonical module chain (2026-10-30)

Cleared for the merged GameLogic TU: adopt canonical Module, ObjectModule and
BehaviorModule/Interface, removing four private copies. Remove the displaced
UpdateModule unknown primary slot; canonical BehaviorModule already supplies
primary slots10/11. Native post-load calls at 0x00242DE0 and 0x00242E25 retain
interface slot9 and primary phase slot12. All 88 rows, 13 parent EH graphs,
289 external code bodies/relocations and all non-debug runtime contents are
identical. Owning acceptance retires Module and ObjectModule keys, plus the
stale GameLogic key whose progress API is already canonical (three total).
Ordinary preview retains LINKS/6,378 current authored bytes; the old index's
smaller source extent predates other merges, so no linking gain is attributed
to this adoption. Team and complete UpdateModule recovery remain separate.
[Native hierarchy and full-file invariants](../../reverse/attempt_support/game-logic-canonical-module-chain-20261030/README.md).
