# StateMachine header cohort, 2026-11-05

Inspected revision: `16cb195a24`. Scope claimed as `class:StateMachine`;
25 queued units tried through `header_adopt_lane.py adopt`.

Five units now include the existing canonical
`Code/GameEngine/Include/Common/StateMachineClass.h` instead of private copies.
No shared header, symbol, pin, alias, source path or function-ledger changes.

| Source (under Code/GameEngine/Source/GameLogic/) | Preview linked bytes before / after |
| --- | ---: |
| AI/BackAwayAndCowerStateMachine.cpp | 223 / 223 |
| AI/Rva003435FBStates.cpp | 296 / 296 |
| Object/ObjectDoXfer.cpp | 3,418 / 3,418 |
| Object/Update/AIUpdateInterfaceLocomotorDistanceToGoal.cpp | 506 / 506 |
| Object/Update/AIUpdateInterfacePrivateGuardObject.cpp | 115 / 115 |

The first two survive the supported automatic adoption. ObjectDoXfer and
LocomotorDistanceToGoal read the canonical goal-position field at +0x24 directly,
replacing their private inline accessor. This preserves the retail accesses and
avoids emitting a conflicting older +0x28 getter. PrivateGuardObject keeps its
0x10 guard constant in an anonymous enum, letting the canonical StateID typedef
supply the argument type; its clear/setState calls retain slots 5/8.

Verification on the complete retained cohort:

- `./build.sh` on all five: 23/23 rows exact, including 14 renumbered funclet
  labels verified against parent EH data; three string and three float literals
  verified. No import-reference failures.
- `find_declared_unmatched.py` before and after: all defined functions matched.
- `header_adopt_lane.py accept --class StateMachine`: five PASS results; only
  this tool removed the five header-queue rows.
- Combined `link_check.py` with current dependency-cache objects: 5/5 LINKS,
  4,558 -> 4,558 bytes. Published census index: 2026-11-05 05:17 at
  `c95fcfcfcd`. This is a preview preservation result, not a new census gain.

Rejected scope / next steps:

AttackPositionHordeStateMachine.cpp byte-passed automatic adoption, but acceptance
reported a loss of census-linked bytes. Its source was restored and its queue
row retained. Before retrying, compare its canonical-derived vtable and provider
bindings against the current census; byte equality alone did not establish link
safety. The other 19 trial files were restored by the adoption tool after
compile/layout/field-rename refusals. Their debt remains. In particular,
StateMachineDefineState needs a canonical typed map contract, and Rva00368344's
s14(Coord3D*) must not be guessed to mean canonical setGoalObject(Object*).
The remaining family-wide reconciliation in LINK-144 is not claimed cleared.
