# AIUpdateInterface header adoption (25 queued units): blocked

Lane: `header_adopt_lane.py adopt --class AIUpdateInterface --header
Code/GameEngine/Include/GameLogic/Module/AIUpdate.h --apply <25 units>` failed
every unit (no source changed). Verdicts by shared cause:

## 1. `Rva00352F9D` is the +0x20 `AICommandInterface` subobject (inference)
Target facts: AIUpdate.h's header notes place the one-slot interface table
0x00C47B88 at +0x20, its first slot calling aiDoCommand 0x002673F6.
`Code/GameEngine/Source/Common/Rva00352F9DAICommand.cpp` rows seven helpers
(0x00352F9D, 0x0035300B, 0x00353080, 0x003530F3, 0x00353168, 0x003531DB,
0x0035325A) on class `Rva00352F9D`, whose only virtual (slot 0) takes
`AICommandParms *` -- the aiDoCommand shape. Views reach it at `ai+0x20`
(AIStatesShipEvacuate.cpp `m_commands` +0x20; AIStatesRva003543BF.cpp base
after a 0x20 prefix; MoveToGroupOrderXfer.cpp `m_commands` +0x20).
Inference: `Rva00352F9D` == `AICommandInterface`. Unifying needs the seven rows
respelled to `AICommandInterface` (canonical, 89 rows). `rename.py class
--merge-existing` refuses (NEW owns rows); `--fold` needs a vftable proof that
names the placeholder. A tooling seat or a fold path for "placeholder whose only
virtual is a known canonical interface" would unblock AIStatesRva003543BF,
AIStatesShipEvacuate and MoveToGroupOrderXfer.

## 2. Slot-template views with pad prefixes
AIInternalMoveToStateUpdate, AIStatesBfmeOnExit, AIStatesDerivedOnExit,
AIStatesDerivedOnExit_ComputeGoal_ComputeGoal (`m_pad004` +0x4, 28 bytes),
AIStates (`m_pad008` 40), Rva00343FB0 (`m_pad008` 488), AIGroupRva00372571
(`m_pad08` 24), AIGuardStateOnEnter (`m_pad004` 969),
AIGuardInnerTargetRva00369FDF (`m_pad00`): the lane finds no canonical field
for the pad spans; hand adoption needs every slot name the view uses
(slot131..slot150 placeholders) mapped to the header's primary-slot names.

## 3. Fields the header keeps opaque or names differently
AIGroupMoveFormation `m_surfaces` +0x1DC (header: inside m_locomotorSet
+0x1CC); AIGuard `m_locomotorSet` +0x1CC 108 bytes (size disagreement with
header's LocomotorSet); AIHarvest `m_locoSet` +0x50; GiantBirdStateSlots
`m_id4C0` +0x4C0 (beyond the 0x3E4 object -- a derived class field);
PathfinderProcessPathfindQueue `slot234` virtual; GiantBirdSlowDeathBehavior
`getCrashData` (derived-class API).

## 4. Other
- AIPlayerQueueSupplyTruck, AIPlayerTeamBuild, GateOpenAndCloseBehavior,
  GettingBuiltBehaviorCompletion: macOS false reject (vendor/stlport/pthread.h
  `/usr/include/pthread.h` include walk; see re_attempts 0x002B466E).
- AISkirmishPlayer: C1001 ICE under adoption.
- SidesList: Rva00493009.h(24) C2955 with the header included.
- AIUpdateInterface_onCollide: lane reported no candidate.
