# Thing header adoption, 2026-11-04

Base: `7a21975fe8` (rebased onto `f12552d0a7`). Scope: the default picker's
25-file Thing adoption cohort, held by `yasinschroeder-codexb`.

Twenty-one queue keys retire through `header_adopt_lane.py accept --class Thing`.
Nineteen sources change: eleven private Thing definitions become canonical
includes, with derived padding reduced to retain the same member offsets;
eight existing indirect consumers gain direct includes. WaypointIsValidUnitType
and GettingBuiltBehaviorCompletion already include the header and need only
owning acceptance. The canonical header itself is unchanged.

Target layout: Thing occupies 0x60 bytes; template +4, transform +8, position
+0x38 and angle +0x44 come from the canonical constructor-backed definition.
Old partial or empty private bases incorrectly represented its full extent.
Template loads remain inline through the existing canonical m_template member;
its getTemplate declaration has no inline definition. Bridge position accesses
use the canonical m_cachedPos member. No donor fact or recovered name is inferred
from these equivalent loads.

All 97 ledger rows in the accepted files pass byte verification, including
compiler literals/imports and EH funclets. The first three accepted units
(Waypoint, burning death, computePath) cover 7 rows. The next thirteen cover
63 rows; the final five cover 27. Post-edit find_declared_unmatched checks pass.
All 21 owning accepts pass structural, byte and link-preservation prediction
checks against the fetched census index (2026-11-04 17:56, 8c757ea0db).
These predictions establish no new measured linking coverage; no census or
smoke runner was started. No source paths, pins or aliases change.

## Accepted files

| Source | Matched rows |
| --- | ---: |
| `Code/GameEngine/Source/GameClient/System/ParticleSystemUpdate.cpp` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/AIAttackApproachComputePath.cpp` | 3 |
| `Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnExit.cpp` | 5 |
| `Code/GameEngine/Source/GameLogic/AI/AIAttackFireDuringApproachStateUpdateInternal.cpp` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/AIAttackMeleeApproachStateOnEnter.cpp` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/AIBurningDeathStateUpdate.cpp` | 3 |
| `Code/GameEngine/Source/GameLogic/AI/AIGroupAdd.cpp` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateStartMoveSound.cpp` | 13 |
| `Code/GameEngine/Source/GameLogic/AI/AIStatesBfmeOnExit.cpp` | 27 |
| `Code/GameEngine/Source/GameLogic/AI/Rva00343FB0.cpp` | 1 |
| `Code/GameEngine/Source/GameLogic/AI/Rva00438D58Update.cpp` | 5 |
| `Code/GameEngine/Source/GameLogic/Map/BridgeObjectCtor.cpp` | 7 |
| `Code/GameEngine/Source/GameLogic/Map/WaypointIsValidUnitType.cpp` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/AutoHealBehaviorPlayerScan.cpp` | 12 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehaviorHandleObjectsOnBridgeOnDie.cpp` | 4 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/CastleBehaviorConditionFlags.cpp` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehaviorOnDie.cpp` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorCompletion.cpp` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorResume.cpp` | 1 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorRva00453905.cpp` | 3 |
| `Code/GameEngine/Source/GameLogic/Object/Behavior/RampageBehavior_update.cpp` | 1 |

## Scanner handoff

The four remaining selected sources are unchanged, with their queue keys kept:
AIAttackApproachTargetStateOnEnter.cpp,
AIAttackApproachTargetStateOnEnter_OnEnter.cpp,
AIAttackApproachTargetStateOnEnter_Unresolved.cpp, and AIStates.cpp.
Their automatic trials stop before compilation in field_renames at unchanged
vendor/stlport/config/stl_dec_vms.h:50: "trigraph or continued line comment in
include input". This is the existing guarded-include verifier obstacle, not a
new byte mismatch. Representatives 0033F9FE, 00351951, 0034AAC8 and 00346FA5
have blocked false-reject re_log verdicts. No checker or vendor workaround was
applied. Next: a separate verifier fix for conditional STLport include traversal,
then rerun adoption and reconcile their actual base layouts.

The other automatic trial failures in trials.log were resolved manually by
adopting the full base and correcting the corresponding derived padding, or
by explicitly including an already-used canonical header. No failed trial
source remains in Code/.

[Trial log](thing-header-adoption-20261104/trials.log),
[thirteen-file build](thing-header-adoption-20261104/build-first-thirteen.log),
[thirteen owning accepts](thing-header-adoption-20261104/accept-first-thirteen.log),
[five-file build](thing-header-adoption-20261104/build-final-five.log), and
[five owning accepts](thing-header-adoption-20261104/accept-final-five.log).
