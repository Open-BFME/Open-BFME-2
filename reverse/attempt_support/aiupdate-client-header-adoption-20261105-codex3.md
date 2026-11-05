# AIUpdateInterface consumer adoption, 2026-11-05

Inspected base: `f22acf5a96a0471cc64ece42689fb61c85d57eba`.
Claim owner: `yasinschroeder-codex3`. The default picker claimed the canonical
AIUpdateInterface header and a 25-file consumer cohort. The header is unchanged.

## Target facts and source adjustments

- PickAndPlayUnitVoiceResponse.cpp: replace the private AIUpdateInterface with
  AIUpdate.h. Its old 12-byte locomotor vector at +0x1D0 is the existing
  LocomotorVectorView over LocomotorSet::m_locomotors: AIUpdate's constructor
  places the set at +0x1CC and the set's primary vptr precedes this storage.
  The +0x3B1 flag is now read through the canonical isWaitingForPath accessor.
- ControlBarRappellerCount.cpp: replace the private 139-slot interface with
  AIUpdate.h. The old virtual method spelled isMoving occupied slot 138
  (+0x228), which the canonical header names rva00262BA9. Use that existing
  declaration, preserving the virtual dispatch. getDozerAIInterface remains
  slot 93; cast its canonical pointer to the unchanged local AIDozerView.
  AIUpdate.h introduces canonical BitFlags<11>; view its proven four-byte
  storage for the mask/test and call the existing Rva0028F528 count view.
  Keep a bool-returning commandDisabledTest helper: spelling its shift/test
  directly in the caller shortened the retail body by three bytes, whereas
  the helper preserves all 10 function/EH rows exactly.
- ResourceOwnedEntryList.cpp: the automatic adoption replaces only its
  private AIUpdateInterface declaration with the existing canonical header.

These are existing canonical names and measured layouts, not new donor-name
or TU-provenance claims. No shared header, provider name, ledger identity,
pin, alias, compiler flags or source path changed.

## Verification and scope

- `find_declared_unmatched.py` passed before trialing all 25 selected files;
  it passed again for the three retained source edits.
- Normal `./build.sh` checks: voice-response 81/81 function/EH rows exact,
  control-bar 10/10 exact, resource-owned entry 1/1 exact. Literal/data checks
  passed. No candidate body, ledger rename or alias was retained from the
  other 22 trials.
- `header_adopt_lane.py accept --class AIUpdateInterface` passed for each
  of the three client sources and retired their three header-queue rows.
  Acceptance includes byte/data verification and a per-unit link prediction.

These checks do not establish a real-link or census gain, ownership progress,
TU approval or a completed TU merge. No nightly or smoke run was started.

## Remaining AI cohort

The automatic adoption trial restored all 22 AI source files. Seven report
no private view and receive a separate acceptance check below. The other
15 have these prerequisites; preserve the existing header queue until its
normal acceptance succeeds:

- Code/GameEngine/Source/GameLogic/AI/AIAttackAimAtTargetStateOnExit.cpp: field renames: the header's layout: Code/GameEngine/Source/GameLogic/AI/AIAttackAimAtTargetStateOnExit.cpp: compile failed: C2371
- Code/GameEngine/Source/GameLogic/AI/AIAttackAimAtTargetStateOnExit_Update.cpp: Code\GameEngine\Source\GameLogic\AI\AIAttackAimAtTargetStateOnExit_Update.cpp(134) : error C2440: 'initializing' : cannot convert from 'Locomotor *' to 'Rva001E3F08 *'
- Code/GameEngine/Source/GameLogic/AI/AIAttackApproachComputePath.cpp: field renames: AIUpdateInterface::m_1a0 (+0x1A0) is int; the canonical AIUpdateInterface::m_field1A0 is float
- Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter.cpp: field renames: AIUpdateInterface::m_1a0 (+0x1A0) is int; the canonical AIUpdateInterface::m_field1A0 is float
- Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter_OnEnter.cpp: field renames: AIUpdateInterface::m_1a0 (+0x1A0) is int; the canonical AIUpdateInterface::m_field1A0 is float
- Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter_Unresolved.cpp: field renames: AIUpdateInterface::m_1a0 (+0x1A0) is int; the canonical AIUpdateInterface::m_field1A0 is float
- Code/GameEngine/Source/GameLogic/AI/AIAttackMeleeApproachStateOnEnter.cpp: field renames: m_3cc at line 231 is not proven a member of AIUpdateInterface; refusing rather than guessing
- Code/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetStateUpdate.cpp: Code\GameEngine\Source\GameLogic\AI\AIAttackPursueTargetStateUpdate.cpp(53) : error C2039: 'setBfme3C7' : is not a member of 'AIUpdateInterface' (fields: AIUpdateInterface::m_bfme3C7 -> m_field3C7)
- Code/GameEngine/Source/GameLogic/AI/AIDock.cpp: Data rows: FAIL 7 of 7
- Code/GameEngine/Source/GameLogic/AI/AIDockStateOnExit.cpp: Code\GameEngine\Source\GameLogic\AI\AIDockStateOnExit.cpp(109) : error C2259: 'AIDockMachine' : cannot instantiate abstract class (fields: AIUpdateInterface::m_canPathThroughUnits -> m_field3BA)
- Code/GameEngine/Source/GameLogic/AI/AIEnterStateOnEnter.cpp: field renames: AIUpdateInterface::m_locomotorSet (+0x1CC, 4 bytes) has no canonical field of that offset and size
- Code/GameEngine/Source/GameLogic/AI/AIFearState.cpp: field renames: ai occurs in a comma declaration or expression
- Code/GameEngine/Source/GameLogic/AI/AIFollowPathAndEvacuateStateUpdate.cpp: field renames: AIUpdateInterface::m_command (+0x20, 4 bytes) has no canonical field of that offset and size
- Code/GameEngine/Source/GameLogic/AI/AIFollowPathStateMethods.cpp: field renames: AIUpdateInterface::m_locomotorSet (+0x1CC) is uchar[36]; the canonical AIUpdateInterface::m_locomotorSet is LocomotorSet
- Code/GameEngine/Source/GameLogic/AI/AIFollowPathStateOnExit.cpp: Code\GameEngine\Source\GameLogic\AI\AIFollowPathStateOnExit.cpp(94) : error C2039: 'bfme_setCanPathThroughUnits_9c10a' : is not a member of 'AIUpdateInterface' (fields: AIUpdateInterface::m_canPathThroughUnits -> m_field3BA, AIUpdateInterface::m_currentGoalPathIndex -> m_field194)

The +0x1A0 integer/float conflict and embedded LocomotorSet storage need
whole-view reconciliation with the canonical layout. Missing inline setter
helpers and leaf view pointer types need local adaptation, then full byte,
data and link acceptance. AIDock must preserve all seven data rows; a
function-only pass would be insufficient. No shared-header change is claimed
as a solution by these failed, restored trials.

## Final acceptance receipts

The three edited client units preserve 12,939 preview-linked bytes against
the 2026-11-04 22:40 census at `3a95b274a2`: voice-response 8,150 -> 8,150;
control-bar 4,725 -> 4,725; resource-owned entry 64 -> 64.
`link_check.py` reports 3/3 clean. These are predictions, not a new census.

The seven unchanged AI files passed `header_adopt_lane.py accept --class
AIUpdateInterface` and retired seven stale rows through the register's normal
path. Together with the three client adoptions, ten header-queue rows retire:

```text
  PASS Code/GameEngine/Source/GameLogic/AI/AIAttackAimAtTargetStateUpdateInternal.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnExit.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIAttackPursueTargetStateUpdateInternal.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIAttackStateOnExit.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AICombineStateInternalUpdate.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIEnterStateOnExit.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIExitStateMethods.cpp
  retired 7 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

`tools/check_csv.py` and `git diff --check` pass. No source-path consumer
audit is needed: no source was moved or removed. The obstacle remains open
for the 15 restored trials listed above.
