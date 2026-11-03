### AIGuard.cpp: the machine constructor donor's one-slot vtable (2026-10-29)

Status: blocked; three of four donors merged (xfer 0x00542FC5, ReturnState
onEnter 0x00543CC4, the hasAttackedMe condition 0x005430E7; `AIGuard.cpp`
11/11, link_check LINKS 2,050 B). `AIGuardMachineCtor.cpp` (0x00543163) stays
apart. Reconciled in probe (not committed) against the shared
`reference/shims/bfme2_statemachine/StateMachineView.h`, the seed's xfer field
names and the seed's state class sizes (Outer state 0x44), both units
byte-match and `tu_skeleton --merge --dry-run` composes and verifies the
bytes, but LinkGuard refuses: `comdat ??_7AIGuardMachine@@6B@ (first)`.
`Rva004D759CDerived.cpp` (the rowed ~AIGuardMachine 0x00542C19) and the
constructor unit both emit the vtable from a destructor-only view (one slot),
and the census keeps the first copy. The TU cannot use that view: the rowed
`?xfer@AIGuardMachine@@MAEXPAVXfer@@@Z` and its qualified
`StateMachine::xfer` call are protected virtuals, so the merged vtable has at
least four slots. Prerequisite: one full 16-slot `AIGuardMachine` table
(retail 0x00869680) in every emitter, with rowed providers for slot 1
(0x000B3FD0), slot 2 (`?name@AIGuardMachine@@QBEPBDXZ` 0x00542C24 is rowed
non-virtual) and slots 9-10 (0x000D43D0), or the destructor moving into the
TU with the constructor. No linking gain claimed for this donor.

The mixed `AIGuardStates.cpp` (35 rows, 18 of them `AIGuard.cpp`'s) also
stays apart. With the seed reconciled to a superset of its views and
`?xfer@AIGuardAttackAggressorState@@MAEXPAVXfer@@@Z` rowed as the fold at
0x00542DBD, `tu_skeleton --split ... --for AIGuard.cpp` carves all 18 rows
(22/22 beside the TU, compose "first" exact), but the split link guard refuses:
`moved selected COMDAT ??0AIGuard{AttackAggressor,Inner,Outer,...}State@@QAE@PAVStateMachine@@@Z
lacks matching private/weak-free context`. Each inline constructor stores its
state's vtable, a COMDAT both changed objects define, and the vtables cannot be
proven retail while slots 1-3 bind the `?slot0N@State@@UAEXXZ` placeholders that
three TUs alternatename to different targets (AIStatesSmallUpdates.cpp,
AITNGuardAttackAggressorStateCtor.cpp, GiantBirdGuardMachine.cpp). Retail tables:
AttackAggressor 0x00C69890, Inner 0x00C69780, Outer 0x00C697D8, Return 0x00C69830,
Idle 0x00C696D0; slot 2 of each is a `ConstIntGetters4.cpp` getter row
(0x00542F3D, 0x00542E5C, 0x00542EAB, 0x00542ED2, 0x00542D58). Prerequisite:
real per-class overrides for slots 1-2 (and a real name for slot 1's
0x00368129 / 0x000B3FD0) in both units so the vtable copies prove retail, then
re-run the split. No linking gain claimed.
