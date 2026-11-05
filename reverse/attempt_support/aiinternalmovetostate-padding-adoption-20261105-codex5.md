# AIInternalMoveToState: four consumer layouts adopt the canonical base

Base: `551e63c52ae49de7c0cf0140430de7ea40bcabda`. Worker:
`yasinschroeder-codex5`; model: gpt-6. Census preview index:
`f44cbcf5b0`, 2026-11-05 15:19 UTC.

The canonical header describes a State prefix of 0x20 bytes and an
AIInternalMoveToState extent of 0x4C. Four queued consumers used shorter
private base views and supplied the missing bytes in their derived classes.
Replacing only the base declaration moved the derived fields and failed the
byte gate. The retained adoption removes that redundant padding or starts it
at 0x4C, preserving every accessed field's previous offset.

| Source under Code/GameEngine/Source/ | Layout adjustment | Rows | Ordinary preview bytes |
| --- | --- | ---: | ---: |
| Common/Rva00340D70Xfer.cpp | Remove derived 0x44..0x4C padding; first member remains +0x4C | 1 | 201 -> 201 |
| GameLogic/AI/AIAttackApproachTargetStateOnExit.cpp | Start derived padding at 0x4C; flags remain +0x6C and +0x60 in the two views | 5 | 756 -> 756 |
| GameLogic/AI/AIAttackPursueTargetStateUpdateInternal.cpp | Start derived padding at 0x4C; first flag remains +0x5E | 1 | 515 -> 515 |
| GameLogic/AI/AIEnterStateOnExit.cpp | Remove derived 0x20..0x4C padding; object ID remains +0x4C | 2 | 229 -> 229 |

The combined builder reports 9 rows, all exact. Before/after builds also verify two string literals,
five compiler floating-point literals and all named import references.
`find_declared_unmatched.py` passes before and after; the existing force-inlined
AIEnterState helper remains marked absent from retail.

Provider preservation: original objects were rebuilt through `./build.sh` and
copied to scratch before editing. Comparing their COFF external definitions
and undefined/weak symbol sets with the verified final objects finds no added
or removed names in any of the four units. Their respective external-definition
counts remain 2, 17, 5 and 12. Removed private declarations contain no bodies;
no alias, body, data definition or inline provider is removed.

One combined `header_adopt_lane.py accept --class AIInternalMoveToState` over
all four sources passes and retires four queue rows. The ordinary combined
`link_check.py` preview reports four LINKS and preserves 1,701 -> 1,701 authored
bytes. This establishes the bounded adoption and debt retirement, not a new
census, real link or runtime result.

The initial automated cohort trial restored every failed candidate. Other
consumers still need coordinate-transfer type reconciliation, missing accessor
declarations, State enum/class reconciliation or distinct derived-layout work.
AIAttackMoveStateMachine.cpp was excluded from the trial because LINK-513
already records its missing virtual-provider prerequisite; that prerequisite
and AIGuardRetaliate.cpp remain open. No other queue row is retired here.
