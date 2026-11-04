# ThingTemplate AI header adoption, 2026-11-04

Source revision: `2b49153c61`. Published preview index: `5a13f2cd61`,
2026-11-04 02:25 UTC, fetched with `tools/link_check.py --fetch-index`.
Claim: `class:ThingTemplate`, owner `yasinschroeder-codex3`.

## Target facts and change

The canonical `ThingTemplate.h` documents the native seven-word kind mask at
+0x108..+0x124 from constructor/assignment bytes and the kind-name lookup.
Two attack-state consumers instead declared 20 bytes; the attack-exit and
follow-path consumers declared four. These private subsets prevented automatic
field-to-field adoption because their extents differ from the real field.

Four sources now include the existing canonical header. Byte tests use unsigned
character access to `m_kindof`; the attack helper's word-3 test reads
`m_kindof[3]`. Mask values, byte offsets and evaluation order are unchanged.
The private class declarations and their unused fields/methods are removed.
No shared header, row identity, pin, alias or source path changed. This is header
cleanup, not recovery of a missing retail body or a new donor identification.

## Verification

`find_declared_unmatched.py` passed before and after each source change.
The ordinary scoped builder passed all 24 rows in the four edited sources:

- `AIAttackApproachTargetStateOnEnter_OnEnter.cpp`: 2/2 rows.
- `AIAttackApproachTargetStateOnEnter_Unresolved.cpp`: 14/14 rows, including
  the nine funclet pins verified through parent EH data after label renumbering.
- `AIAttackApproachTargetStateOnExit.cpp` and `AIFollowPathStateMethods.cpp`:
  8/8 rows together.

String, float and named-import verification passed. An intermediate compile
identified the remaining `kindOfWord(3)` calls; replacing them with the canonical
word access produced the final exact result. No failed reconstruction remains.

`header_adopt_lane.py accept --class ThingTemplate` passed all 18 sources below
and retired exactly their 18 queue rows through the owning tool. Four sources
were adopted here; fourteen already included the canonical header at the source
revision and had stale queue entries. Acceptance checked each source's structure,
byte matching and explicit preview verdict without loss of census-linked bytes.

A separate ordinary preview of the four edited sources reported:

| Source basename | Census linked bytes | Current preview | Result |
| --- | ---: | ---: | --- |
| AIAttackApproachTargetStateOnEnter_OnEnter.cpp | 626 | 626 | LINKS |
| AIAttackApproachTargetStateOnEnter_Unresolved.cpp | 1,981 | 1,981 | LINKS |
| AIAttackApproachTargetStateOnExit.cpp | 756 | 756 | LINKS |
| AIFollowPathStateMethods.cpp | 1,046 | 1,046 | LINKS |

Total: 4,409 -> 4,409 bytes. These are preview/retirement checks, not a new
census, real game link, ownership receipt or runtime smoke result. No maintainer
measurement runner was invoked. Other ThingTemplate consumers remain queued.

## Accepted sources

- `Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter_OnEnter.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnEnter_Unresolved.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIAttackApproachTargetStateOnExit.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIAttackStateOnExit.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIDeadStateOnExit.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIEnterStateOnEnter.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIFollowPathStateMethods.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIFollowPathStateOnExit.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIGroupGetCenter.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIGroupRva00372571.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIGroupScatter.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIGuard.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIGuardInnerTargetRva00369FDF.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIGuardStates.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIHordeCowerStateSlots.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIHuntStateUpdate.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIInternalMoveToStateUpdate.cpp`
- `Code/GameEngine/Source/GameLogic/AI/AIMoveToStateOnEnter.cpp`
