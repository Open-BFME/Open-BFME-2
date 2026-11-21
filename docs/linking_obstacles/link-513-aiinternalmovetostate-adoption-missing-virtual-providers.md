### LINK-513: AIInternalMoveToState adoption lacks two canonical virtual providers
Status: Blocked. Updated: 2026-11-05; inspected revision: 57d08ff823.
Evidence / scope: [current-object trial](../../reverse/attempt_support/aiinternalmovetostate-header-adoption-20261105-codexb.md); AIAttackMoveStateMachine.cpp and AIGuardRetaliate.cpp byte-match the adoption but lose linking through GetSnapshotName and _bfme_state_slot7.
Completed: rejected source edits restored; AIHarvest.cpp adopted independently and four passing header-queue rows retired through accept.
2026-11-05: four additional consumers adopt the canonical base after adjusting derived padding; nine distinct byte rows, unchanged external definition/reference sets, four LINKS preserving 1,701 bytes and four owning-tool queue retirements. The two virtual-provider prerequisites remain open. [Evidence](../../reverse/attempt_support/aiinternalmovetostate-padding-adoption-20261105-codex5.md).
Remaining / next check: reconcile existing placeholder owners at 0x0033F2F7 and 0x0033F2D7 with the canonical virtual declarations, then repeat the two adoptions and their consumer checks.
Clearance: pending for the two blocked adoptions.
Census confirmation: none claimed.

2026-11-05: four serializer-only consumers adopted the canonical movement-state header and retired four queue rows; no external providers removed ([573-byte verification and scope](../../reverse/attempt_support/aiinternalmovetostate-xfer-adoption-20261105-codexb4.md)). The two missing virtual providers remain blocked.

2026-11-09 (hdr-a, base 06c0b727c0): 17 more AI units adopted the canonical header, 39 queue rows with State and StateMachine, all link_check clean (18 of 18 units with MeshClassLifetime; LINKED 23,780 -> 23,780 on the rebased tree); a further 9 attack-state units (State/StateMachine only) 9 of 9, 3,059 -> 3,059. Those units' classes do not emit the table. Seven adoptions that do emit it byte-match or nearly so and still lose linking through the same two symbols: Rva00367518Ctor 33, AIAttackMoveStateMachine 654, AIGuardRetaliate 214, AIInternalMoveToStateOnExit_AIInternalMoveToState 94, AIStateRva0034005DCtor 1,131, AIStatesSmallUpdates 619, AIStates 4,714 bytes (AIStates also keeps one byte difference, AIAttackFireWeaponState::onEnter). Attempts reverted; verdicts in reverse/re_attempts.log.
Next check: `tools/rename.py function --rva 0x0033F2D7 --to-class AIInternalMoveToState --new _bfme_state_slot7 --also 0x0033F2F7=GetSnapshotName --prepared ...` is the planned route (docs/naming.md); not yet run. On 2026-11-09 the claim on 0x0033F2F7 and SubsystemNameGetters2.cpp was refused because class:Drawable's scope covers that file. Consumers that spell the placeholders: AIDock, AITNGuard, Rva00346CDDCtor, Rva00544EB1Ctor, and the /alternatename line in the constructor unit.
2026-11-09 (hdr-a, later): correction to the entry above: the 39 rows include MeshClassLifetime's one MeshModelClass row, so 38 are this class family's. Six more units adopted (AIStatesDerivedOnExit and its splits, AIInternalMoveToStateUpdate, AIStatesMoreExits), 18 rows, 6 of 6, 6,455 -> 6,455. AIGuardStates joins the units held back: adoption byte-matches, 4,315 -> 0 bytes on the same two symbols. The claim on 0x0033F2F7 was still refused at 09:06 UTC, same scope.

2026-11-12: The three Giant Bird guard tables emitted by `AIGuardStates.cpp`
now bind their retail entry, exit and update bodies in slots 4 through 6.
The inner entry owns its 315-byte body and unwind graph. The exit and
aggressor update folds match their existing bodies and relocation targets.
The installer and update provider verify 54 code rows and six EH graphs,
with 4,610 scoped linked bytes on index `9ca25659d0`. Completing the tables
still requires the shared State layout and the remaining virtual providers.

2026-11-15 (slotnames, approval revision 7ff1670043d): independent votes approve slot2 GetSnapshotName. Supported protected getter move with prepared getter/caller/constructor verifies 84/84 code rows on Boat, then the table check rejects the constructor (15 slots agree, one differs); tool restores all files. No provider bound; slot7 and constructor reconciliation remain prerequisites. Full evidence and limits: [own-provider trials](../../reverse/attempt_support/slotnames-own-provider-trials-20261115.md). No adoption or real-link clearance.


### Confirmed slot7 behaviour defect, 2026-11-15 (slotnames)

The constructor unit `AIInternalMoveToStateOnExit_AIInternalMoveToState.cpp` does not declare the class's native slot7 override. Its emitted `??_7AIInternalMoveToState@@6B@` slot7 therefore names `?_bfme_state_slot7@State@@EAEXXZ`, the inherited empty State default at RVA **0x000B3FD0**, while retail's **VA0x00C10DE8 slot7/+0x1C** calls RVA **0x0033F2D7**. That existing 5-byte matched row, `?disable@Rva0033F2D7ByteSetter@@QAEXXZ` in `Common/Disp8ByteSetters.cpp`, clears receiver byte **+0x49** (the canonical movement state's waiting-for-path flag). This is wrong behaviour, not merely an undefined name.

A single authorized diagnostic rerun at local d921a21df82 saved the actual failed constructor COFF and all18 table entries. Baseline and attempted sources byte-verify84/84; the table check has15 agreeing resolved entries, the one slot7 clash and two unresolved entries (generated destructor0 and proposed getter2). Supported rename rolls back; tracked diff is empty. Captured object SHA and native/current targets are retained at `~/bfme2-ops/swarm/sweeps/slotnames/ai-diagnostic-20261115/`. No provider, adoption, real link or runtime clearance is claimed.

Native call RVA **0x00350332** in AIStateMachine::updateStateMachine resumes the active State through slot7 after temporary-state exit and saved goal restoration. Two independent name_lane votes agree to **onResume** at the State slot key, record **nl-ac8209bc374c** (inferred readable name; original EA spelling unproved). Zero Hour's Boolean isIdle at ordinal7 and BFME1's absence of this callback are not canonical naming proof. The current structural spelling cannot receive a slot vote by design.

A shared State-hook rename must preserve the virtual position and update the derived override and explicit bindings together. Read-only plan: `~/bfme2-ops/swarm/sweeps/slotnames/packets/state-slot7-plan.md`; hook654 dependents, conservative whole-repair verification union659. Owner decision required before a512+ full-gate batch. No gate/header/full-gate change started. This defect note and pending votes must ride with the first substantive landing, never as a standalone records push.

### 2026-11-20: State-family vtable census and the view-declaration recipe (seat halilkkaya-st)

Base `68ba4a0f55e` (branch seat-vt-1120); measured with the local bridge snapshot (tools/vtable_bridge.py plan over
build/match, no link). Family: 50 retail tables whose slot-0 deleting destructor reaches 0x0033FF2B (`imt`) and 84
other State-shaped tables (17-24 slots, slot 1 0x000B3FD0, slots 9-15 mostly 0x0047A699; `state`). 100 of them are
bridged under 105 names (41 imt, 59 state), 3 are correct, with 862 mismatching slots, emitted by 32 units.

Mismatching slots by the documented route that would fix them:
- **identity, 228 slots in 68 tables (no tool route).** The table's class is a placeholder (`Rva0033F5B9`, its
  constructor's row) while retail's slot bodies are rowed as methods of a real class (`?xfer@AIHordeExitState`,
  ...), which the slot-2 getter's own string names ("AIHordeExitState" at 0x0033F5DD). `rename.py class --fold`
  refuses (NEW is not named on the table), `class --name` refuses (NEW already spelled in code) and
  `--merge-existing` refuses (NEW owns rows). The largest single blocker; it needs a fold mode tied by the slot
  bodies, a verifier change.
- **State default, 287 slots.** Missing slots 7-16 where a unit's State view is a private 7-slot copy or a stand-in
  base (TurretStateMachineCtor.cpp's `Rva004D7B70`). The canonical header fixes them, see below.
- **getter-to-class, 70 slots (approval needed).** Free getters `?RvaNNNNNNNNGet@@YAHXZ` in slot 2. `rename.py
  function --to-class C --new ?GetSnapshotName@C@@MBEPBDXZ` now reads a name_lane slot approval for the getter
  move too (`to_class_name_problem`); for an unregistered C it refuses "register it first". The lk106 moves predate
  that.
- **placeholder-body, 68**: overrides rowed under placeholder classes or functions; their to-class moves need slot
  approvals.
- **shared default body, 66** (0x0050B5C6, 0x0047A69C and similar ICF bodies) and **slot-0 ICF deleting destructor,
  39** (`??_GX` at 0x00346CFB, shared by 49 tables, with `??1X` at 0x00368793): twin rows, not started.
- **declare-override, 85**: retail's body already rowed under the table's own class with the canonical spelling.
  Only the unit's view lacks the declaration. Done below.

Canonical AIInternalMoveToState.h, `header_adopt_lane.py adopt` trial over the 14 imt emitting units: 8 byte-match
(AIInternalMoveToStateOnExit_AIInternalMoveToState, Rva00342826Ctor, AIStateMoveTightenCtors, Rva003429B9Ctor,
Rva00342B87Ctor, AIStateEvacLeafCtors, Rva00342EACCtor, AIGuardRetaliate). AIStateRva0034005DCtor and
Rva00367518Ctor fail on the field rename `m_30 -> m_goalLayer` colliding with the view's own `m_goalLayer` (+0x40).
AIStatesSmallUpdates and AIGuardStates fail with C2011 (own StateReturnType/StateExitType enums), Rva0036804FCtor
with C2555 (int onEnter), and Rva0033FF2BDtor has no private view. Measured blast radius of the 8 trial objects
left in build/match: mismatching slots -110, but two new names undefined anywhere,
`?GetSnapshotName@AIInternalMoveToState@@MBEPBDXZ` and `?_bfme_state_slot7@AIInternalMoveToState@@EAEXXZ`, so the
judge rejects it. Slot 2 has an agreed approval (nl-fd1a7bdbd840); slot 7 does not (the State key's `onResume`,
above, is unapplied). Trap: `adopt` without `--apply` leaves its trial objects in build/match. Rebuild the units
with `./build.sh` before any snapshot.

Landed (commits by subject):
- "Declare AIInternalMoveToState's computePath slot in two State views": AIStateRva0034005DCtor.cpp's private view
  gains slot 17 and the protected xfer, and the eight overriding classes declare their rowed computePath.
  Rva00340BDCDtor.cpp's view follows, so the two `??_7Rva00340BDC@@6B@` copies stay identical. Mismatching slots
  32,895 -> 32,872; bridged, correct and refusals unchanged; both units LINK.
- "Declare rowed State overrides in ten State-family units": 21 overrides in 12 tables (AIAttackSquadState,
  AIHarvestState, AIGuardRetaliateState, AITunnelNetworkGuardState, AIHuntState, AIAttackAreaState,
  AIGoingIdleState, AIAttackFollowWaypointPathState, AIAttackMoveToState, AIFollowPathAsTeamState,
  GiantBirdAttackMoveToState, AIAttackMeleeHordeWaitState). AIStateHashCtors0033F2FD.cpp emits seven of those
  tables too and declares the same overrides.
- "Complete three private AIInternalMoveToState views with its rowed virtuals": AIAttackMoveStateMachine.cpp,
  AIGuardRetaliate.cpp and Rva00367518Ctor.cpp. AIGuardRetaliate.cpp builds State with the capitalized Snapshot
  slots (slot 3 DoXfer), so xfer is not declared there; check slot positions in the compiled table.
- "Re-base two AIInternalMoveToState ctor units on the canonical State header" and "Re-base three more ...":
  AIStateEvacLeafCtors, Rva003429B9Ctor, AIStateMoveTightenCtors, Rva00342843Ctor and Rva00342EACCtor. Each
  drops its private 7-slot State view for Common/StateMachine.h and keeps an AIInternalMoveToState view of only
  the rowed virtuals with providers (no slot 2 or 7 override), so ten tables go from 7 to 18 slots. Rva00342843Ctor's
  and Rva00342EACCtor's eight `/alternatename` directives now alias spellings their objects no longer reference
  (the xfer one no unit references); removing them needs a Verifier-Change commit (hatch_baseline.tsv).
- "Re-base Rva00342826Ctor and Rva00342B87Ctor on the canonical State header": the same, two tables.

Measure over the six commits: mismatching source slots 32,895 -> 32,737 (family 862 -> 704), bridged 3,020 ->
3,020, correct 2,496 -> 2,496, refusals identical, undefined-without-definer 2,806 -> 2,804, every judge ACCEPT,
every touched unit LINK in link_check. No table turned fully correct: every imt table still waits on slot 0 (the
`??_GX` twin at 0x00346CFB), slot 2 (GetSnapshotName) and slot 7, and most also on identity.

Slot 0 (39 imt tables): `add_match.py --icf-owner` refuses the first step, `??1X` as the twin of 0x00368793:
`unresolved call(s): ??1AIInternalMoveToState@@UAE@XZ (add to reverse/symbols.csv)`. Retail's 0x00368793 jumps to
0x0033FF2B, rowed `??1Rva0033FF2B@@UAE@XZ`, and no row or pin binds the class's own destructor name there. It waits
on the Rva0033FF2B -> AIInternalMoveToState fold (LINK-618) or an admitted pin. 0x00368793 was also claimed by
another worker that day.

Not taken:
- overrides whose rows carry a non-canonical spelling (`?onEnter@AIHuntState@@UAEHXZ`,
  `?onExit@AIHarvestState@@UAEXH@Z`, `?update@AIGoingIdleState@@QAEHXZ`, ...): `--respell` refuses a return type
  or an enum parameter.
- the Turret tables: TurretStateMachineCtor.cpp's stand-in base would need re-basing on State. Its states are
  created with `new`, so every pure slot must be declared, slot 2 is a getter move (approval) and
  TurretAIIdleState's xfer is the ICF body 0x00544AB3.
- Rva0033FC42Dtor.cpp: re-basing on State turns its non-virtual `int update()` (`?update@Rva0033FC42@@QAEHXZ`)
  into a C2555 override.
- AIStatesSmallUpdates, AIGuardStates, AIStates, Rva0036804FCtor: private StateMachine views or their own enums.

Scratch: build/st/census.py (census), overrides.py and declare.py (declarations), imt_complete.py and
state_rebase.py (the view recipes), getter_move.py (the refused getter batch).
