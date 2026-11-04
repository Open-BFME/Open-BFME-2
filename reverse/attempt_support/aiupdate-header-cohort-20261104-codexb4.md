# AIUpdateInterface header cohort, 2026-11-04

Inspected base: `0e393373af6364566a42b972fcf06681c3757bcc`.
Claim owner: `yasinschroeder-codexb4`; picker selected class AIUpdateInterface
and its 25-file AI cohort. The canonical header is unchanged.

## Recovery and target evidence

- AIStateMachineResetToDefaultState.cpp: replace the private 154-slot interface
  with AIUpdate.h; call canonical `vslot153` for both notifications. The old
  view and native call use primary slot 153 (+0x264), which AIUpdate.h places
  at the same offset. Remove the now-unused recursive slot template.
- AIStatesMeleeApproachGoal.cpp: replace the private interface with AIUpdate.h;
  replace `*ai->locomotorSet()` with `ai->getLocomotorSet()`. Both access +0x1CC;
  the header's target constructor/destructor evidence places LocomotorSet there.
  This uses existing names and layout evidence; it adds no donor-name claim.
- Eight other cohort consumers already used this header. Acceptance, rather
  than an edited queue or a trailer, retires their stale queue entries.

## Verification

`find_declared_unmatched.py` passed before the cohort trial and after both
source edits. `./build.sh` verified 6/6 function/EH rows in the two changed
sources, plus the literal-reference checks. The final header acceptance also
rechecked the edited source after removing the unused template.
`check_csv.py` and `git diff --check` pass. No ledger identity, provider name,
shared header, pin, alias, or source path changed.

The initial 25-file automatic adoption retained no changes. Its shared causes
and remaining prerequisites (15 units remain queued after the two repairs):

- AISkirmishPlayer: header-layout compilation C1083; identify its missing include.
- AIStates: +0x1A0 private int versus canonical float; reconcile accesses first.
- AIStatesBfmeComputePath: one-byte LocomotorSet view at +0x1CC versus canonical
  storage; replace the incomplete view and reconcile its virtual call spellings.
- AIStatesBfmeMoveOnEnters: TU-specific bfme_get_path helper was introduced to
  avoid COMDAT selection conflicts. Replacing it requires checking selection,
  not simply renaming calls to getPath.
- AIStatesBfmeOnExit, AIStatesDerivedOnExit and its two ComputeGoal satellites,
  AIStatesShipEvacuate: flattened command-interface fields at +0x20 need the
  canonical AICommandInterface base subobject and call forms.
- AIStatesCowerVoice: field-rewrite scanner stops on STLport stl_dec_vms.h's
  trigraph/continued-comment diagnostic; no scanner change attempted.
- AIStatesRva003543BF: rva0035325A belongs to the +0x20 secondary view; reconcile
  its canonical command-interface call before adoption.
- AIStatesSmallUpdates: slot136 placeholder must use setLocomotorGoalNone and
  its other inline helper declarations must be reconciled with the header.
- AITNGuard: code trial reaches data verification but its single data row fails;
  inspect that emitted table's provider names before retrying.
- AttackStateMachine: ObjectID typedef conflicts with the canonical enum.
- GiantBirdStateSlots: +0x4C0 field exceeds AIUpdateInterface; establish the
  actual derived-class owner instead of putting it in the base header.

These diagnostics are bounded automatic trials, not retained reconstructions.
All failed candidates were restored by the tool. No source remains nonmatching.

## Owning-tool receipts

Initial acceptance passes (the other 17 fail structural adoption):

```text
  PASS Code/GameEngine/Source/GameLogic/AI/AIStateMachineUpdate.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIStatesDerivedOnExit_ComputeGoal_ComputeGoal_Update.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIStatesMoreExits.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AITunnelNetworkGuardStateOnEnter.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIWanderInPlaceStateUpdate.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIWanderStateMethods.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIWanderStateOnExit.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/GarrisonObjectGroupOrder.cpp
  retired 8 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

Acceptance of the two source changes:

```text
  PASS Code/GameEngine/Source/GameLogic/AI/AIStateMachineResetToDefaultState.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIStatesMeleeApproachGoal.cpp
  retired 2 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

Combined ordinary preview (not a new census or ownership measurement):

```text
Code/GameEngine/Source/GameLogic/AI/AIStateMachineUpdate.cpp: LINKS  LINKED 330 -> 330 bytes (census 2026-11-04 12:23 at 40fe1783d7; file's own bytes 330)
Code/GameEngine/Source/GameLogic/AI/AIStatesDerivedOnExit_ComputeGoal_ComputeGoal_Update.cpp: LINKS  LINKED 119 -> 119 bytes (census 2026-11-04 12:23 at 40fe1783d7; file's own bytes 119)
Code/GameEngine/Source/GameLogic/AI/AIStatesMoreExits.cpp: LINKS  LINKED 679 -> 679 bytes (census 2026-11-04 12:23 at 40fe1783d7; file's own bytes 679)
Code/GameEngine/Source/GameLogic/AI/AITunnelNetworkGuardStateOnEnter.cpp: LINKS  LINKED 154 -> 154 bytes (census 2026-11-04 12:23 at 40fe1783d7; file's own bytes 154)
Code/GameEngine/Source/GameLogic/AI/AIWanderInPlaceStateUpdate.cpp: LINKS  LINKED 524 -> 524 bytes (census 2026-11-04 12:23 at 40fe1783d7; file's own bytes 524)
Code/GameEngine/Source/GameLogic/AI/AIWanderStateMethods.cpp: LINKS  LINKED 1,440 -> 1,440 bytes (census 2026-11-04 12:23 at 40fe1783d7; file's own bytes 1,440)
Code/GameEngine/Source/GameLogic/AI/AIWanderStateOnExit.cpp: LINKS  LINKED 65 -> 65 bytes (census 2026-11-04 12:23 at 40fe1783d7; file's own bytes 65)
Code/GameEngine/Source/GameLogic/AI/GarrisonObjectGroupOrder.cpp: LINKS  LINKED 248 -> 248 bytes (census 2026-11-04 12:23 at 40fe1783d7; file's own bytes 248)
Code/GameEngine/Source/GameLogic/AI/AIStateMachineResetToDefaultState.cpp: LINKS  LINKED 155 -> 155 bytes (census 2026-11-04 12:23 at 40fe1783d7; file's own bytes 155)
Code/GameEngine/Source/GameLogic/AI/AIStatesMeleeApproachGoal.cpp: LINKS  LINKED 1,555 -> 1,555 bytes (census 2026-11-04 12:23 at 40fe1783d7; file's own bytes 1,555)
link_check: 10 of 10 link cleanly; LINKED 5,269 -> 5,269 bytes (5.5s)
```

The ten queue rows were removed only by `header_adopt_lane.py accept`.
