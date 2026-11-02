# LINK-177 item 1: the State class-key change (banked, blocked)

Seat halilkkaya-lk16, 2026-11-02. Base `bb0c2735b9` (origin/master at the time).

## Why the change is needed

`Rva004D759CDerived.cpp` holds 13 derived StateMachine destructors and is first in
link order. Since `936b658f65` it includes canonical `StateMachineClass.h`, so it emits
16-slot `??_7<X>StateMachine@@6B@` tables. The 13 constructor units still emit
one-slot copies from private StateMachine views and lose (12,033 B on current
objects). StateMachine is registered canonical, so the constructor units have to
adopt `StateMachineClass.h`. That header brings canonical `class State`, and their
`defineState` calls then mangle `PAVState@@`. Every row and caller spells
`PAUState@@` today, so the State class key has to flip in one commit across the
whole connected group.

Class-key evidence: retail has no RTTI or string that proves the key. Zero Hour
declares `class State`, and BFME 1's ledger spells `PAVState@@` for defineState. The
`U` spelling came from BFME 2's private views, not from retail.

MSVC 7.1 mangling rule, measured here with a scratch compile: the key of the
definition wins when the class is defined; otherwise the first declaration's key
wins. So respelling a unit's own `struct State` body is enough even where a shim
declares `struct State;` earlier (DozerAIUpdateCtor.cpp, WorkerAIUpdateCtor.cpp via
`StateMachineView.h`). No shim edit is needed.

## What `state-classkey.patch` does

Apply it on the base above with `git apply`.

- **Sources (32 units).** Every unit whose object touches a `UState@@` name
  (census index `touches`) respells `struct State` as `class State` (adding
  `public:` to bodies). It covers all defineState, internalGetState and
  condition-function units **except** SupplyTruckAIUpdate.cpp.
- **functions.csv.** 13 rows are renamed `UState@@` -> `VState@@`: defineState, its
  `_M_insert`, internalGetState, the Dozer, Worker and AIDock conditions,
  rva005430E7, rva00545F10, rva0034373F and rva0047A699.
- **symbols.csv.** The three `UState@@` pins are dropped. Their respells
  (`state-pins-before.csv` holds the originals) behave differently:
  - `_M_create_node` (0x00534743) was re-admitted through
    `pin_admission.py --add` with `fold-proof=StateMachineDefineState.cpp`. It is in
    the patch. On commit, `hatch_counters.py --update` must rerun; the admission
    rewrote `hatch_baseline.tsv` without the 0x004D795B pin.
  - The other two are refused. See the blockers below.

Measured with the patch applied: `./build.sh` over the 32 units gives 458/463 rows.
The 5 failures are only the unresolved callees of the two refused pins and the
not-yet-admitted `_M_create_node` (the latter clears once admitted).

## The step-B proof: `step-b-attackfirewhilecharging.patch`

The proof applies on top of the class-key patch. AttackFireWhileChargingMachine.cpp
replaces its private StateMachine view with `StateMachineClass.h`.

- `./build.sh` gives 4/4 rows.
- `link_check` over the unit, Rva004D759CDerived.cpp and StateMachineDefineState.cpp:
  AttackFireWhileChargingMachine 114 B LINKS again, the holder's 584 B is unchanged,
  and the `??_7AttackFireWhileChargingMachine@@6B@` conflict is gone.

The other 12 constructor units need the same swap. Units that `new` State-derived
classes also need their pads rebased from 4 to 0x20 (canonical State is 0x20 bytes)
and the pure `update`, `GetSnapshotName` and `xfer` declared in each derived view
(canonical State is abstract). Alternatively they can keep opaque non-State views
with an explicit cast, as this unit already does. AIStateMachineCtor.cpp also needs
canonical `AIStateMachineClass.h` together with AIStateMachine.cpp (the
`??_7AIStateMachine@@6B@` pair).

## Blockers, with prerequisites

1. **SupplyTruckAIUpdate.cpp** is a defineState caller with 7 `UState@@` rows (its
   SupplyTruckStateMachine conditions). It was held by
   `codex-01a1071d-root-recovery-oct11` for the whole session (rows 0x004A69BF and
   0x004A6A58, link-cycle repair), so it is not in the patch. It needs the same
   respell and its 7 row renames.
2. **The `_M_find` pin at 0x00357180** (callers hasState, internalGetState and
   rva004D7627 in StateMachineGoal.cpp). The int-key
   `??$_M_find@H@...HPAVState...` is refused: 0x00357180 is named, and the fold-proof
   fails because StateMachineGoal's body differs from retail at +0x16 (signed
   compare). code_identity_baseline already records the current U pin as `wrong`.
   - An unsigned map key makes the body fold: the pin
     `??$_M_find@I@...IPAVState...` was admitted with
     `fold-proof=StateMachineGoal.cpp` in a trial.
   - But retail passes `&param` straight to the unsigned-key find. That means
     BFME 2's `StateID` parameters are unsigned (Zero Hour: `typedef UnsignedInt
     StateID`). With an `int` parameter, cl adds a frame and a temporary.
   - `typedef unsigned int StateID` in StateMachineGoal.cpp byte-matches the bodies
     but respells the signatures: internalGetState, internalSetState, hasState,
     rva004D7627 and the **virtual** setState go from `H` to `I`. That is a
     signature decision across StateMachine, its overrides (AIStateMachine,
     TurretStateMachine, ...) and their callers. It is not taken here.
3. **The `insert_unique` pin at 0x004D795B** (defineState's call at 0x004D7B31) is
   refused. 0x004D795B is named (`map<unsigned,int>::insert_unique`), and
   StateMachineDefineState.cpp compiles the V body to 132 bytes against the
   ledger's 134. The current U pin is the code_identity_baseline `wrong` key at
   line 86. The STLport/allocator profile of that unit has to reproduce retail's
   134-byte body first, then the V pin is admitted with `fold-proof=`.

Tooling note: `pin_admission` treats a pure class-key respell of a grandfathered
pin as a new pin (an edited line counts as added). Both refused pins already hold
wrong bindings, so the refusal is not a false reject. The prerequisite is fixing
the bindings, not the check.

## Registers this touches when it lands

- code_identity_baseline.tsv lines 86-89 (shadow mode) are keyed on the U names.
  They must not be respelled by hand (the register never grows by hand). They
  become stale and are retired through `repair_queue.py retire identity` once the
  bindings are fixed.
- header_queue.tsv diagnostics and name_basis.csv mention the U names in free text
  only.

## Refresh after the prerequisites (lk17, 2026-11-02): `state-classkey-v2.patch`

Seat halilkkaya-lk17 cleared blockers (2) and (3), and the change is rebuilt on top of them:
- 52f216e4e1 makes StateID unsigned and proves the `_M_find` pin;
- the identity-key retirement follows it;
- 41a2dcfb49 moves the State tree helpers to retail's 0x004D9C49 and 0x00382B7F and re-homes
  0x0053479F.

`state-classkey-v2.patch` applies on `41a2dcfb49` with `git apply`. It holds:
- the same 32 source respells, applied with a three-way merge;
- the 13 non-SupplyTruck `UState@@` rows respelled to `VState@@`;
- all three State pins re-admitted through `pin_admission.py --add` with fold-proofs, so none is
  refused any more:
  - `??$_M_find@I@...IPAVState@@...` at 0x00357180, `fold-proof=StateMachineGoal.cpp`;
  - `_M_create_node` at 0x00382B7F, `fold-proof=StateMachineDefineState.cpp`;
  - `insert_unique` at 0x004D795B, `fold-proof=StateMachineDefineState.cpp`.

The hatch_baseline.tsv hunk is the tool's own admission output.

Measured on the trial:
- `./build.sh` passes **463/463** rows over the 32 units, against v1's 458/463.
- `link_check` over the 263 family units shows the same non-linking set as before the change. The
  class key alone moves no bytes; the step-B header adoption in the 13 constructor units does.

Still blocked: SupplyTruckAIUpdate.cpp (7 `UState@@` rows and a defineState call) is held by
codex-01a1071d-root-recovery-oct11. Landing v2 without it would leave that unit's defineState
reference unresolved. The unit already loses its `??_7SupplyTruckStateMachine@@6B@` on current
objects, but the lead asked to bank, not land. Once the file is claimable:
- respell its `struct State`;
- rename its 7 rows (tombstones);
- apply v2;
- do step B (see `step-b-attackfirewhilecharging.patch`).

## Step B for nine constructor units (lk17, 2026-11-02): `step-b-v2-nine-ctors.patch`

This applies after `state-classkey-v2.patch`. It covers the following units, with their census
bytes:
- AttackFireWhileChargingMachine 114 (lk16's proof, carried over);
- AIGuardMachineCtor 451;
- AIGuardRetaliateMachineCtor 199;
- Rva00544C51MachineCtor 214;
- AttackStateMachine 654;
- AttackMeleeStateMachine 479;
- AITNGuardMachineCtor 417;
- Rva00343756Ctor 198;
- Rva0033FC0ACtor 213.

The recipe, mechanical in each unit:
- Delete the private `class State` and `class StateMachine` and include `StateMachineClass.h`.
  Each machine class keeps declaring only its constructor, destructor and members, so its
  `??_7` table equals Rva004D759CDerived.cpp's 16-slot copy.
- Where the unit's private `StateConditionInfo` used `(void *)` test pointers that canonical
  `StateConditionInfo.h` accepts, it includes that header. AttackStateMachine keeps its own copy,
  because its condition functions have mixed signatures.
- State views no longer derive from State. Canonical State is abstract and 0x20 bytes, while these
  units only `new` the states and call their rowed constructors. Each view keeps its allocation
  size: either a full pad (`m_pad00[size]`) or a leading `m_stateBytes[0x20]` where the old view
  relied on a 0x20-byte State base. Each `new` is cast to `State *` at its defineState call.

Measured on v2 plus this patch:
- `./build.sh` passes 463/463 rows over the 32 units.
- `link_check` over the 263 family units plus StateMachineDefineState: 252/264 link, and LINKED
  rises from 221,890 to 225,062 bytes. The nine units (2,939 B) and StateMachineDefineState
  (233 B) link.
- Still losing: AIStateMachineCtor 3,825, AIDock 2,608, SupplyTruckAIUpdate 1,658,
  AIAttackMoveStateMachine 654 and TurretStateMachineCtor 562. Each needs real view work:
  - AIStateMachineCtor constructs a `vector<Gen_p12pod>` goal path, but canonical
    AIStateMachineClass.h keeps that field opaque (`field3C[0x0C]`), so the header has to carry
    the vector first.
  - AIAttackMoveStateMachine and AIDock define constructors of State subclasses that emit their
    own tables and use `getMachineOwner`.
  - TurretStateMachineCtor needs TurretStateMachine.h and its multi-level state views.
  - SupplyTruckAIUpdate.cpp stays held.

## SupplyTruckAIUpdate.cpp to-do (read-only survey, lk17, 2026-11-02)

The file is still held by codex-01a1071d-root-recovery-oct11 for a link-cycle repair, so nothing
here was edited. When it frees, the class-key part is small:
- Line 114 `struct State;` and line 133 `struct State { public: ... }` become `class State`. The
  view already has `public:`.
- Its 7 rows are respelled `PAUState@@` -> `PAVState@@`, each with a deleted_rows.csv tombstone:
  ownerIdle, ownerDocking, ownerRva004A6D15, ownerAvailableForSupplying, ownerNotDockingOrIdle,
  isForcedIntoWantingState and isForcedIntoBusyState. These are the SupplyTruckStateMachine
  statics at 0x004A6D38, 0x004A6CF2, 0x004A6D15, 0x004A6D5D, 0x004A6DA1, 0x004A6C92 and
  0x004A6CC2.
- The comment at line ~703 ("State is a struct in this view because the rowed defineState is
  spelled with one") must be updated.

Apply those together with `state-classkey-v2.patch`; then `./build.sh` the 33 units.

SupplyTruck's step B is separate work, with the AIAttackMoveStateMachine shape. Its State views
use `getMachineOwner()` through the private `m_machine` at +0x18, and
SupplyTruckWantsToPickUpOrDeliverBoxesState defines `update`. So adopting `StateMachineClass.h`
needs those views rebased on canonical State (pure update/GetSnapshotName/xfer declared), not the
opaque-view recipe of the nine-unit patch.

### Step B for AIStateMachineCtor (lk17): `step-b-v2-aistatemachinector.patch`

This applies after v2 and the nine-unit patch. AIStateMachine.cpp's `??_7AIStateMachine@@6B@` is the
plain 16-slot base table; it declares only the destructor. So AIStateMachineCtor.cpp needs neither
canonical AIStateMachineClass.h nor a header change. It keeps its private AIStateMachine view,
with the real `vector<Gen_p12pod>` goal path its constructor builds, and gets the same recipe:
`StateMachineClass.h` plus 62 opaque, size-preserving state views. This corrects the earlier note
that the header has to carry the vector first.

Trial on v2 plus both step-B patches:
- `./build.sh` passes 81/81 rows in the unit and 463/463 over the 32.
- `link_check` over the 263 family units plus StateMachineDefineState: LINKED 221,890 -> 228,887 B
  (+6,997). AIStateMachineCtor's 3,825 B links.

Left after this: AIDock 2,608, AIAttackMoveStateMachine 654 and TurretStateMachineCtor 562 B.
These units define State-subclass constructors and emit their own tables, so their views need
rebasing on canonical State. Also left: SupplyTruckAIUpdate 1,658 B, which is held.

## State's slots and step B for AIDock, AIAttackMove and Turret (lk18, 2026-11-02): `step-b-v2-dock-attackmove-turret.patch`

Seat halilkkaya-lk18, base `9e271b3526`.

### The State header change (landed, not in a patch)

The landed commit that adds this section also edits canonical `StateMachine.h` and
`StateMachineClass.h`. Retail's base State table 0x00C605D8 (installed by 0x004D73FC) gives each
slot's base body:
- slots 1, 7 and 16: the bare RET 0x000B3FD0;
- slot 4: `xor eax,eax; ret` 0x000D43D0 (STATE_CONTINUE);
- slot 5: RET 4 0x0047A69C, pinned as `?onExit@State@@UAEXW4StateExitType@@@Z`;
- slots 2, 3 and 6: `__purecall`;
- slots 8-15: `xor al,al; ret` 0x0047A699 (false).

None of slots 7-16 is `__purecall`, so none can be declared pure. Each base body is a shared ICF
fold rowed under other classes' names (`??1Region2D`, `Xfer::IsCRC`, ...), so no State name can
point at it. The header now defines the base bodies inline, as Zero Hour's StateMachine.h does:
`loadPostProcess() {}`, `onEnter() { return STATE_CONTINUE; }`, `_bfme_state_slot7() {}`,
`isAttack() const { return false; }`, `_bfme_state_slot9..15() const { return false; }` and
`_bfme_state_slot16() {}`. A unit that emits a State-derived table then defines every base slot it
does not override as a COMDAT. Before, the table referenced names that no unit defines.
- Slot 8 is named `isAttack`. The rowed overrides `?isAttack@AIAttackAreaState/AIGuardState/
  AIAttackState@@UBE_NXZ` (0x003422EF, 0x00341D81, 0x0034141F) sit in slot 8 of their tables, and
  `StateMachine::isInAttackState` 0x002621B8 calls `[eax+20h]`.
- The other slots keep their placeholder names: their overrides are rowed only under address
  names, and the private views disagree (slot 10 vs 14 for `isBusy`).
- WorkerAIUpdate.cpp's private view already emits `?isAttack@State@@UBE_NXZ` and
  `?onEnter@State@@...` as COMDATs. Their census digests (bbc58e31feea, 2c49700537) are the same
  bytes these inline bodies compile to.
- The canonical State also gains Zero Hour's `getMachine()`, `getMachineOwner() const` and
  `getMachineGoalObject() const`. The last two are defined after StateMachine in
  `StateMachineClass.h`. Eleven units' private views already emit these three COMDATs under the
  same names, and their digests agree. Retail inlines them: findMyDrone 0x00544B5B reads +0x18,
  then +0x14.

Verified on current objects: all 120 units that include `StateMachine.h` rebuild, 907/907 rows
pass, and **0 objects change** (external symbols and COMDAT digests compared before and after).
No current object emits a canonical-State-derived table, so the change moves no bytes by itself.

### The banked step B

`step-b-v2-dock-attackmove-turret.patch` applies after `state-classkey-v2.patch`. It touches none
of the files the nine-unit and AIStateMachineCtor patches touch.
- **AIAttackMoveStateMachine.cpp**: includes `StateMachineClass.h`. Its three `new`-only states
  become opaque, size-keeping views. The private AIInternalMoveToState view now derives from
  canonical State, so the three state tables it emits (AIAttackMoveToState,
  AIAttackFollowWaypointPathState, AIFollowPathAsTeamState; this unit alone emits them) use the
  canonical slots. `initDefaultState` is called through canonical StateMachine's slot 7. This part
  needs the landed slot bodies.
- **AIDock.cpp**: includes `StateMachineClass.h`, defining `BFME_SNAPSHOT_NAME_SLOT` first because
  Player.h requires it. The private StateMachine and State views go:
  - the canonical accessors replace the State helpers;
  - a file-static `bfme_unlock(StateMachine *)` keeps the TU-local unlock (the previous LINK note);
  - the instantiated `Rva005445D4` and the private AIInternalMoveToState view declare
    `GetSnapshotName`/`xfer` (and `update`) so they are not abstract. Their tables are never
    emitted, because the vptrs come from the address-named data rows;
  - `Rva00544095` (`new` only) becomes opaque.
  This part needs the landed accessors.
- **TurretStateMachineCtor.cpp**: includes `StateMachineClass.h`. TurretStateMachine keeps a
  ctor/dtor/member view, so its 16-slot table equals Rva004D759CDerived.cpp's. The turret-state
  base `Rva004D7B70` and the fire state `Rva0033F483` become opaque, layout-keeping views, because
  the five states are `new`ed here and canonical State is abstract. Each `new` is cast to `State *`.

Trial (v2 + nine + AIStateMachineCtor + this patch, on the landed header):
- `./build.sh`: 463/463 rows over the 32 v2 units. AIDock is 41/41 rows plus 7 data rows,
  AIAttackMove 15/15 and Turret 15/15. Funclet `$L` rows verify through the parent EH data after
  renumbering.
- `link_check` over 473 units that touch State/StateMachine names (census index touches):
  - master: 442/473 link, 566,226 B;
  - trial: 455/473 link, 576,814 B (**+10,588 B**, 13 units, none lost);
  - this patch's share: AIDock 2,608 + AIAttackMoveStateMachine 654 + TurretStateMachineCtor 562 =
    3,824 B.

Still blocked: everything above waits on `state-classkey-v2.patch`, which waits on
SupplyTruckAIUpdate.cpp. That file is still held by codex-01a1071d-root-recovery-oct11 at 22:40.
Apply order once it frees: v2 (with SupplyTruck's respell), then `step-b-v2-nine-ctors.patch`,
`step-b-v2-aistatemachinector.patch` and this patch.

## Landed (lk18, 2026-11-02)

SupplyTruckAIUpdate.cpp was freed at 22:38. All the patches above are now applied on master, in
four commits:
- the class key: the 32 v2 units plus SupplyTruck, 20 rows respelled with tombstones, and the 3
  pins renamed in place;
- step B for the ten constructor units (the nine-unit patch plus AIStateMachineCtor);
- step B for AIDock, AIAttackMove and Turret (`step-b-v2-dock-attackmove-turret.patch`);
- SupplyTruck's own step B.

`link_check` over 527 State-family units: 482 -> 496 link, 584,501 -> 596,747 B. The patches here
are kept as history only.

