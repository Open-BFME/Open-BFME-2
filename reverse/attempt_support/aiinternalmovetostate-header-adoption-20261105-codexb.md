# AIInternalMoveToState header adoption, 2026-11-05

Inspected revision: `57d08ff823`. Census/index: `c95fcfcfcd`, 2026-11-05 05:17.
Worker: yasinschroeder-codexb; model: gpt-6.1-sol.

## Landable scope

`header_adopt_lane.py adopt --class AIInternalMoveToState --header
Code/GameEngine/Include/GameLogic/AIInternalMoveToState.h --apply` replaced
AIHarvest.cpp's private base projection with the canonical header. All other
source edits from the trial were restored when byte or link checks failed.

The owning `accept` command retired four AIInternalMoveToState queue rows:

- Code/GameEngine/Source/GameLogic/AI/AIHarvest.cpp (new adoption).
- Code/GameEngine/Source/GameLogic/AI/AIAttackMeleeApproachStateUpdateInternal.cpp
  (already included the canonical header).
- Code/GameEngine/Source/GameLogic/AI/AIFollowPathStateOnExit.cpp
  (already included the canonical header).
- Code/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateOnExit.cpp
  (already included the canonical header).

`./build.sh` on these four sources: 10/10 rows exact, eight literals and five
floating-point literals verified. AIHarvest's frozen-file check passes.
Acceptance checks current objects and preserves each unit's census-linked bytes.
Final combined preview after restoring the rejected edits: all six units link,
2,570 -> 2,570 authored bytes. Restored units also pass 21/21 byte rows.
These are preview/queue results, not a census or real-link measurement.

## LINK-513: canonical virtual providers remain under placeholders

Two other proposed adoptions byte-matched, then failed acceptance:

- AIAttackMoveStateMachine.cpp: link preview 654 -> 0 authored bytes.
- AIGuardRetaliate.cpp: link preview 214 -> 0 authored bytes.

Both introduced unresolved references to
`?GetSnapshotName@AIInternalMoveToState@@MBEPBDXZ` and
`?_bfme_state_slot7@AIInternalMoveToState@@EAEXXZ`. Both source edits were
reverted; their AIInternalMoveToState queue rows remain.

Target facts: the canonical header documents retail table 0x00C10DE8's slot 2
as 0x0033F2F7 and slot 7 as 0x0033F2D7. The ledger currently owns those bodies as
`?name@Rva0033F2F7Named@@QBEPBDXZ` in
Code/GameEngine/Source/Common/SubsystemNameGetters2.cpp (6 bytes), and
`?disable@Rva0033F2D7ByteSetter@@QAEXXZ` in
Code/GameEngine/Source/Common/Disp8ByteSetters.cpp (5 bytes).

Inference/next step: reconcile these existing placeholder owners with the
canonical virtual declarations through the naming lane, checking every consumer
and virtual calling convention, then retry the two adoptions together. Do not
add duplicate rows or alias hatches. The header's slot7 spelling is a neutral
slot label, not a recovered donor method name.

## Other trial boundaries

The 25-source trial also found missing setAdjustsDestination declarations,
private State/StateMachine enum/class collisions, unproven member ownership,
and incompatible field types (uint versus canonical float at +0x2C).
Those units were restored and their queue entries were retained. No shared
header or provider was edited. An attempted State acceptance for the restored
AIAttackMoveStateMachine.cpp correctly refused its missing canonical include;
that State queue row remains too.
