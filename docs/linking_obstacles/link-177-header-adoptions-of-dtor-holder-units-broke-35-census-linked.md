### LINK-177: header adoptions of dtor-holder units broke 35 census-linked units (2026-11-02, seat halilkkaya-lk15)

Status: Open (analysis; regression). Item 1 (StateMachine family, 13 units plus Rva0033FC0ACtor) was repaired by lk18 on 2026-11-02: the class key, step B and the SupplyTruck step B landed, +12,246 B on current objects. Items 2 and 3 are as recorded below. Base `ae61e35305`, index 2026-11-02 08:35 (`984a4cdc4d`).
A current-object `link_check` over all 18,470 present sources the 06:54 census (`357ce2a88f`)
records as linked: 18,435 link, 7,725,216 -> 7,696,163 B (-29,053 B). Excluding the known
`__imp_`/`___ImageBase` modelling gaps and a sweep artifact (OpaqueScalarDeletingDtorsB11.cpp's
`??1LivingWorldBuilding@@UAE@XZ` is defined by Rva004E0D67Dtor.cpp, which the census-linked path
list omits; checked together they link), the losses share one mechanism: a bulk canonical-header
adoption (StarkillerHDX, landed after the 06:54 census) moved a unit that holds a family of
derived destructors onto the canonical base, so it now emits full canonical tables, while each
class's constructor unit keeps its grandfathered one-slot private base view and emits a one-slot
copy of the same `??_7` name. The holder sits first in link order (its rows are the lowest), so
every constructor unit loses (`differs from the first copy`, no retail address).

1. StateMachine family, 12,033 B, cause `936b658f65` (Adopt canonical StateMachine in 34 more
   units): `Rva004D759CDerived.cpp` (13 derived machine destructors) and `AIStateMachine.cpp` now
   include `StateMachineClass.h` (16 slots). Losers: AIStateMachineCtor 3,825, AIDock 2,608,
   SupplyTruckAIUpdate 1,658, AttackStateMachine 654, AIAttackMoveStateMachine 654,
   TurretStateMachineCtor 562, AttackMeleeStateMachine 479, AIGuardMachineCtor 451,
   AITNGuardMachineCtor 417, Rva00544C51MachineCtor 214, AIGuardRetaliateMachineCtor 199,
   Rva00343756Ctor 198, AttackFireWhileChargingMachine 114. Retail (e.g. SupplyTruck 0x008532A8,
   Turret 0x008609C8, AIGuard 0x00869680, AIDock 0x008699A0) has 16 slots with per-class overrides:
   slot 2 the class name getter, slot 3 an xfer override, Turret also 5/6/8, AIDock 15. Neither copy
   is retail's. A private StateMachine copy cannot return to the holder (class registered), so the
   constructor units must adopt `StateMachineClass.h`. Blockers found: (a) it pulls canonical
   `class State` (0x20 bytes, abstract: update/GetSnapshotName/xfer pure) over the units' private
   4-byte `struct State` views, so their derived-state pads and pure overrides need rework;
   (b) every one of the 25 `defineState` callers and the row 0x004D7B0F spell
   `?defineState@StateMachine@@QAEXIPAUState@@IIPBUStateConditionInfo@@@Z` (struct State), while the
   canonical declaration mangles `PAVState@@`: nothing defines that name. The State class-key
   (struct/class) has to be decided at the class level first (header lane: predicted row-name
   changes and consumers), then the constructor units adopt both headers with the per-class
   overrides declared in the holder and in each constructor unit.
   Class-key evidence (searched 2026-11-02 for the follow-up seat): the retail image holds 81 RTTI
   type descriptors, all exception types and STLport stream/locale classes (`.?AVINIException@@`,
   `.?AVXferException@@`, `.?AU_Refcount_Base@_STL@@`, ...); neither `.?AVState@@`/`.?AUState@@`,
   `.?A?StateMachine@@` nor `.?A?GameWindow@@` occurs, and the image has no `defineState` string. The
   WorldBuilder data (`reverse/wb/*.jsonl.xz`: 286 functions with RTTI, again only exceptions and
   STLport) carries no mangled State signature either; WB names `StateMachine::defineState`
   (StateMachine.cpp) only as a demangled string. So the target proves no class key. Donor and
   reference evidence point to `class`: Zero Hour's StateMachine.h declares `class State : public
   MemoryPoolObject, public Snapshot` and `class GameWindow : public MemoryPoolObject`, and BFME 1's
   matched ledger spells `?defineState@StateMachine@@IAEXIPAVState@@IIPBUStateConditionInfo@@@Z`
   (class State, protected) at its 0x000A2030. BFME 2's `PAUState@@` spelling came from the private
   `struct State` views, not from retail; treat any key choice as inferred and verify it with the
   header lane's predicted row-name changes.
2. Apt GameWindow family, 4,985 B, cause `636533e29f` (Adopt canonical GameWindow in 37 more
   units): `OpaqueScalarDeletingDtorsB12.cpp` emits 11-slot `6BGameWindow` tables; losers
   AptMainMenu 3,621, Rva005173F8Dtor 1,121, _bfme_AptGameWindow 243. Their header-queue rows show
   adoption failures in other classes of the same units (AptCommandMapAdder field renames,
   BfmeAptWindowManager data row, GlobalData include cycle).
3. Others of the same shape: AptScriptFunction 3,535 (`??_7Rva006FBC90Owner@@6B@`, 17 vs 15
   slots, AptValue adoption `1d9e653c6e`), AptMyHero_Unresolved 1,067 (`??_7AptMyHero@@6B@` slot 3
   `xfer` vs `DoXfer(Xfer&)`: the unit reads a capitalized Snapshot first), MeshLoadContextCtor 2,043
   and matinfo 644 (`VectorClass<ShaderClass>` copies), MapCacheAddMap 1,191 and
   MapCacheLoadUserMapsBFME2 1,198 (duplicate and non-retail `MapCache::addMap`),
   W3DScriptedModelDrawDestructor 506 (`6BDrawModule`), Rva001041BDASlot1 418, Rva0033FC0ACtor 213,
   FloodUpdateDtor 180, SpawnBehaviorDtor 174, XferSaveOpen 169, AttributeModifierAuraUpdateCtor 128.

Repaired (2026-11-02, lk15): FloodUpdateDtor (180 B), cause `0769434026` (Adopt canonical
UpdateModuleInterface in 21 more units; it moved FloodUpdateCtor.cpp onto the canonical chain) while
the Dtor (first in link order) kept a private UpdateModule with a one-slot interface. Same recipe:
the Dtor includes canonical UpdateModule.h. `./build.sh` 5/5 rows; scoped DIR32 OK; only the two units
touch the FloodUpdate tables, now one digest each; `link_check` FloodUpdateDtor 180 B links again,
FloodUpdateCtor 95 B unchanged.

Repaired (2026-11-02, lk15): SpawnBehaviorDtor (174 B). SpawnBehaviorCtor.cpp moved onto canonical
UpdateModule.h (`a9be158d99`, landed after the 06:54 census) while the Dtor (first in link order) kept a
private UpdateModule with a one-slot interface (primary slots 1-3 `__purecall`, 12 slots). The Dtor now
includes the canonical header (the GettingBuiltBehavior recipe). `./build.sh` 4/4 rows; scoped DIR32 OK
(14 symbols); only the two units touch the SpawnBehavior tables, now one digest each; `link_check`
SpawnBehaviorDtor 174 B links again, SpawnBehaviorCtor 263 B unchanged.

Repaired (2026-11-02, lk15): AttributeModifierAuraUpdateCtor (128 B), cause `0769434026` (Adopt
canonical UpdateModuleInterface in 21 more units): the Dtor unit now emits the +0x10 and +0x20 tables
(0x00C50D20, 0x00C50CD8) as `??_7AttributeModifierAuraUpdate@@6BUpdateModule@@@` and
`6BUpgradeMux@@@`, while the ctor still bound `6BUpdateModuleInterface@@@` and `6B@` by explicit
identifier (LINK-168 mechanism 1). The ctor binds the emitted names. `./build.sh` 2/2 rows; scoped DIR32
OK (6 symbols, with the Dtor: both names sit on the same retail tables); `link_check` ctor 128 B links
again, Dtor 143 B unchanged.

Repaired (2026-11-02, lk15): MeshLoadContextCtor (2,043 B) and matinfo (644 B), cause `ccfd564709`
(Adopt canonical ShaderClass in 38 more units). Canonical `ShaderClass.h` declared `operator==`/`!=`
out of line, so MaterialCollectorDestructor.cpp (first in link order) emitted
`VectorClass<ShaderClass>::operator==`, `::ID` and `DynamicVectorClass<ShaderClass>::ID` calling
`??8ShaderClass` (73 B) where the two units inline the compare (45 B). Retail inlines it: the
VectorClass<ShaderClass> table 0x00BD4670 (installed by ctor 0x0016FB40) points slot 1 at 0x00196920
and the ID slot at 0x001964F0, the four-byte-element bodies shared with
VectorClass<FontCharsBuffer*> (no call), and the rowed 0x00143240/0x001541B0 are COMDAT copies (four
units emit `??8ShaderClass` as identical `retail` COMDATs from in-class definitions). The header now
defines both operators in the class. Only MaterialCollectorDestructor referenced them out of line
(index touches); its three template copies now equal the other units' and its new `??8ShaderClass`
COMDAT equals the retail-proven copies. `./build.sh` 74/74 rows over the three units; scoped DIR32 OK;
`link_check` MeshLoadContextCtor 2,043 and matinfo 644 B link again, MaterialCollectorDestructor
1,588 B unchanged. Full gate on the header commit.

Repaired (2026-11-02, lk15): the Apt GameWindow family (item 2, 4,985 B). AptMainMenu.cpp,
Rva005173F8Dtor.cpp and _bfme_AptGameWindow.cpp replace their one-slot private GameWindow
views with canonical `Bfme2GameWindow.h`, as OpaqueScalarDeletingDtorsB12.cpp reads it (its
default constructor declaration covers the two units' call-only `GameWindow()`); no other view
change. `./build.sh` 56/56 and 32/32 rows (data row OK); scoped DIR32 OK (61 symbols, with B12);
each unit's only changed definition is its `6BGameWindow` table, now B12's digest; `link_check`
AptMainMenu 3,621, Rva005173F8Dtor 1,121, _bfme_AptGameWindow 243 B LINK again;
OpaqueScalarDeletingDtorsB12 727 and BfmeAptGameWindowConstructor 104 B unchanged. Both copies keep
GameWindow's slot 7 `__purecall`, the canonical contract (no retail override is declared).

Repaired (2026-11-02, lk15): AptMyHero_Unresolved.cpp (1,067 B), cause `b056878e3e` (Adopt
canonical CreateAHeroData in 30 more units): AptMyHeroCtor.cpp (first) now spells CreateAHeroData's
slot 3 `xfer(Xfer *)` while the unit's private view kept `DoXfer(Xfer &)`; both names already
reach retail 0x00408C11 through existing alternatenames (`?xfer@CreateAHeroData` in
CreateAHeroDataCopy.cpp, `?DoXfer@CreateAHeroData` in both AptMyHero units, now unused here). The
view now spells the slot as the canonical header does. `./build.sh` 16/16 rows; scoped DIR32 OK
(20 symbols); only the two units touch `??_7AptMyHero@@6B@`, which now has one digest; `link_check`
AptMyHero_Unresolved 1,067 B (census-linked, lost on current objects) LINKS again, AptMyHeroCtor
1,152 B unchanged.

Checked and left (2026-11-02, lk15), with causes and prerequisites:
- AptScriptFunction (3,535 B), cause `1d9e653c6e`: Rva006FBC90OwnerDtor.cpp (first) now reads
  canonical AptValue, whose pure slots 12/13 carry the neutral names `vslot12`/`vslot13`, so its
  AptValueGC::IsGarbageCollected and AptValueWithHash::RegisterReferences override nothing and are
  appended (17 slots, `__purecall` at 12/13); AptScriptFunction emits 15. Retail 0x00CED880 has 15
  (slot 11 0x006FBC10 and slot 13 0x006FBC30 are Rva006FBC90Owner overrides, slot 12 the 0x001826C0
  fold). Naming the canonical slots IsGarbageCollected/RegisterReferences (the existing row
  `?RegisterReferences@AptValueWithHash@@UBEXXZ` 0x006DCC00 is `inferred`) would restore the overrides;
  it is a naming decision on a registered header, not taken here. No unit overrides `vslot12/13`.
- MapCacheAddMap (1,191 B) and MapCacheLoadUserMapsBFME2 (1,198 B), cause `16060f2bc4`: MapUtil.cpp's
  unrowed Zero Hour `MapCache::addMap` (present-unmatched) mangled `AAE` under its private view and now
  `QAE` under canonical MapCache.h, a strong duplicate of the rowed 0x00304E64 (MapCacheAddMap.cpp).
  Dropping the body fails 6 of MapUtil's 19 rows (the `_M_insert_overflow<ICoord2D>`, `getExtent` and
  `_Rb_tree<AsciiString, Coord3D>` instantiations it alone emits); those rows need another emitter first.
- XferSaveOpen (169 B), cause `c9fe5b31cd`: ArmorHashMapErase.cpp (first, canonical ArmorTemplate with
  its AsciiString member, destructor 0x001D8FA5) emits a 32-byte node deleter calling the pair
  destructor and `deallocate`; XferSaveOpen's private 152-byte ArmorTemplate is trivial (20 bytes,
  `free`). Do not adopt Armor.h there blindly: XferSaveOpen is the sole definer of a retail-proven
  `hashtable<NameKeyType,ArmorTemplate>::clear` (digest e5f4c01a) that 16 other units use, and the
  adoption changed that copy's bytes (trial reverted). The allocator profiles differ too
  (bfmealloc vs `_STLP_USE_MALLOC`).
- W3DScriptedModelDrawDestructor (506 B), cause `0448c68cb5` (canonical DrawModule in the ctor): the
  destructor's view inlines an empty `~DrawModule`; canonical DrawModule.h declares it out of line, so
  adopting it changes the destructor's bytes (the BehaviorModule situation; the family-wide DrawModule
  table 0x00BC9690 work applies).
- Rva001041BDASlot1 (418 B), cause `18befef11f` (canonical SimpleSceneClass in Rva001040D5Ctor.cpp,
  28-slot `??_7Rva001040D5@@6B@`) against its one-slot private view.
- Rva0033FC0ACtor (213 B) belongs to item 1 (Rva004D759CDerived.cpp holds its destructor).

Banked (2026-11-02, lk16), item 1: the State struct->class key change, base `bb0c2735b9`. Re-verified
on current objects: the 13 constructor units still lose 12,033 B on their `??_7` tables. The change is
banked in `reverse/attempt_support/link177-state-classkey-20261102/` (README, `state-classkey.patch`,
`step-b-attackfirewhilecharging.patch`).
- What the patch does: 32 units respell `struct State` as `class State`. The set is every object
  whose census `touches` holds a `UState@@` name. 13 `UState@@` rows become `VState@@`, and the three
  `UState@@` pins are dropped.
- MSVC 7.1 rule, measured: the definition's class key wins, else the first declaration's. A unit's own
  body respell is enough even after a shim's `struct State;`, so no shim edit is needed.
- Result: `./build.sh` 458/463. The only failures are unresolved callees of the respelled pins.
- Step-B proof: on top of the patch, AttackFireWhileChargingMachine.cpp swaps its private view for
  `StateMachineClass.h`. `./build.sh` 4/4, and `link_check` shows 114 B LINKS again with the holder's
  584 B unchanged.

Three blockers remain:
- (1) SupplyTruckAIUpdate.cpp, a defineState caller with 7 `UState@@` rows, was held by
  codex-01a1071d-root-recovery-oct11 all session.
- (2) The respelled `_M_find` pin at 0x00357180 (hasState, internalGetState, rva004D7627) is refused.
  StateMachineGoal's int-key body differs from retail at +0x16 (a signed compare).
  - An unsigned key folds (fold-proof admitted in a trial). But retail passes `&param` straight to the
    unsigned find, so BFME 2's StateID parameters are unsigned (Zero Hour `UnsignedInt StateID`).
  - Respelling internalGetState/internalSetState/hasState/rva004D7627 and the virtual setState from
    `H` to `I` is a family-wide signature decision.
- (3) The respelled `insert_unique` pin at 0x004D795B is refused. StateMachineDefineState compiles 132
  bytes against the ledger body's 134.

Both refused pins are grandfathered wrong bindings (code_identity_baseline lines 86-89), so these are
real prerequisites, not false rejects. `_M_create_node` (0x00534743) re-admits with
`fold-proof=StateMachineDefineState.cpp`.

Repaired (2026-11-02, lk17), blocker (2): StateID is unsigned, and the `_M_find` pin is proven.
- Target fact: hasState 0x004D76F2, internalGetState 0x004D764C and rva004D7627 0x004D7627 each push
  `lea eax,[esp+8]` (the parameter's own slot) to the find at 0x00357180, whose key compares are
  `jb`/`jae`. The key type is unsigned and the parameter has that same type (an `int` parameter
  would need a converted temporary). Donor fact: Zero Hour GeneralsMD StateMachine.h:61
  `typedef UnsignedInt StateID`. The ledger already spelled defineState and setTemporaryState with
  `I` for their state IDs.
- Change: StateMachineGoal.cpp keys its map by `unsigned int` (with the matching `less<unsigned>`
  forceinline), and seven rows are respelled from `H` to `I` by hand (rename.py cannot change a
  signature), each tombstoned in deleted_rows.csv: internalGetState, internalSetState, hasState,
  rva004D7627, the virtual StateMachine::setState and its AIStateMachine and TurretStateMachine
  overrides. The canonical StateMachineClass.h, AIStateMachineClass.h and TurretStateMachine.h, the
  StateMachineView.h shim, and the private views of the 13 objects that reference these names now
  declare the parameters unsigned. Every body uses the ID only in equality tests or passes it on, so
  no byte changes.
- Pin: `??$_M_find@I@...IPAUState@@...` was admitted at 0x00357180 through `pin_admission.py --add`
  with `fold-proof=StateMachineGoal.cpp`, replacing the refused `H` spelling. allowed_symbols now
  reports the three StateMachineGoal references as `fold` and 0 wrong bindings. The
  code_identity_baseline keys 87-89 hold the old names. `retire identity` refuses them while HEAD
  still lists the old rows, so they are retired in the next commit.
- Verified: `./build.sh` 220/220 rows over the 13 objects and 648/648 over the 51 includers of the
  four edited headers; scoped DIR32 OK; find_declared_unmatched clean. In current objects only three
  stale objects whose sources are deleted still spell `H`. `link_check` over the 263 units that touch
  the family's tables or State names: 242 link. The 21 that do not are the known item-1 losers
  (12,033 B plus Rva0033FC0ACtor 213 B, all "differs from the first copy" on their own `??_7`), the
  B11 sweep artifact, and units that the census already records as unlinked. ReplenishUnitsBehavior
  (1,050 B) links on current objects.
- Blockers (1) SupplyTruckAIUpdate.cpp (still held by the foreign fleet) and (3) remain. The class-key
  patch must respell the new `_M_find` pin to `PAVState@@` and re-admit it with the same fold-proof.

Analysed (2026-11-02, lk17), blocker (3): the 2-byte difference is the begin() fast path, but two of
the State map's tree identities are wrong. Handoff:
`reverse/attempt_support/link177-state-tree-helpers-20261102/`.
- The 2 bytes: retail insert_unique 0x004D795B calls `_M_insert(__y, __y, __v)` on the begin() path.
  `/D_BFME_RETAIL_TREE_INSERT_LAYOUT` reproduces it (134 B). With `/Ireference/shims/bfmealloc`
  added, the unit's create_node is retail 0x00382B7F byte for byte. defineState still passes 2/2
  (trial patch banked).
- The identities: retail 0x004D795B calls `_M_insert` 0x004D9C49, which calls create_node 0x00382B7F.
  The ledger rows `_M_insert<unsigned, State*>` at 0x0053479F and pins create_node at 0x00534743.
  Those two belong to another unsigned-keyed tree: 0x00534743 allocates 0x20-byte nodes and copies a
  12-byte map value through 0x005346D9. Its insert_unique bodies 0x00534827 and 0x005348E7 are
  rowed as the `map<unsigned, void*>` stand-ins. The State row byte-matches only because the wrong
  create_node pin resolves its one differing relocation.
- Prerequisite: give 0x0053479F an honest owner first. That is the `_M_insert` of the
  Rva00534743Record tree in StlSweepR3Rva00534743.cpp, whose key must become unsigned: 0x0053479F
  compares `jb`. Then, in one change:
  - apply the flags;
  - pin the State create_node to 0x00382B7F with fold-proof;
  - turn the State `_M_insert` row into an ICF row at 0x004D9C49 (PathDoXfer.cpp's
    `map<unsigned,int>` precedent).
  StateMachineDefineState.cpp (233 B, losers: insert_unique and create_node) should then link, and
  the class-key patch can re-admit all three with fold-proofs.

Repaired (2026-11-02, lk17), blocker (3): the State map's tree helpers now bind retail's bodies.
- StlSweepR3Rva00534743.cpp keys its Rva00534743Record tree by `unsigned int`. Its creator row at
  0x00534743 is respelled `H` -> `I` and tombstoned. It also emits that tree's `_M_insert`, which
  is now rowed at 0x0053479F (136 B, add_match verified). Retail 0x0053479F compares keys with `jb`
  and calls 0x00534743 at 0x005347C7 and 0x005347E0.
- StateMachineDefineState.cpp builds with `/D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc`
  and drops its now-unused `__node_alloc` override.
- Its `_M_insert<unsigned, State*>` row moved from 0x0053479F to an ICF row at 0x004D9C49
  (tombstoned).
- Its create_node pin moved from 0x00534743 to 0x00382B7F (`pin_admission.py --add`,
  `fold-proof=StateMachineDefineState.cpp`). The existing insert_unique pin at 0x004D795B now
  reproduces retail.
- allowed_symbols: 0 wrong bindings in either unit. code_identity_baseline key 86 (defineState ->
  insert_unique) retired through `repair_queue.py retire identity` (PASS).
- `./build.sh` 20/20 rows over the two units and the three Image/void* map providers; scoped DIR32 OK;
  pin_consistency OK; find_declared_unmatched clean.
- `link_check` over the 53 units that touch the State, Rva00534743Record, `void*`, Image and
  `map<unsigned,int>` tree names, plus Gen009D6DD0.cpp: 54/54 link. StateMachineDefineState.cpp
  0 -> 233 B and StlSweepR3Rva00534743.cpp 34 -> 170 B; no unit lost. CreateAHeroHero and
  MilesAudioManager report an unresolved `?Close@Gen009D6DD0@@QAEXXZ` only when checked without
  their renamed provider.
- The class-key patch must respell three State pins to `PAVState@@` and re-admit them with the
  same fold-proofs: `_M_find`, create_node at 0x00382B7F and insert_unique at 0x004D795B. The
  State `_M_insert` ICF row needs the same respell. Blocker (1), SupplyTruckAIUpdate.cpp, is still
  held by the foreign fleet.

Banked (2026-11-02, lk17): `state-classkey-v2.patch` in
`reverse/attempt_support/link177-state-classkey-20261102/` applies on the commits above and needs
no refused pin.
- It contains the 32 source respells, the 13 `UState@@` -> `VState@@` rows, and the three State pins
  re-admitted with fold-proofs (`_M_find`, create_node 0x00382B7F, insert_unique 0x004D795B).
- Trial: `./build.sh` 463/463 rows. `link_check` over the 263 family units shows the same
  non-linking set; the class key moves no bytes by itself.
- What remains: SupplyTruckAIUpdate.cpp's respell and its 7 rows once it is claimable, then step B
  (`StateMachineClass.h` in the 13 constructor units).
- Not landed, at the lead's request.
- Step B is banked too: `step-b-v2-nine-ctors.patch` applies after v2. Nine constructor units
  include `StateMachineClass.h` and keep opaque, size-preserving state views. Trial: 463/463 rows;
  `link_check` LINKED 221,890 -> 225,062 B over the family, with the nine units (2,939 B) and
  StateMachineDefineState (233 B) linking.
- Left after step B:
  - AIStateMachineCtor (3,825 B): solved later in the trial. It needs no header change, because
    the holder's table is the base one. `step-b-v2-aistatemachinector.patch` makes it link, and
    the family total becomes 221,890 -> 228,887 B (+6,997).
  - AIDock (2,608 B) and AIAttackMoveStateMachine (654 B): they emit State-subclass tables.
    Trial (lk17): rebasing AIAttackMoveStateMachine's state views on canonical State builds
    15/15, but its three state tables then reference canonical State's placeholder slots
    `?_bfme_state_slot10..12@State@@EAEXXZ`, which nothing defines. Those units first need
    State's slots 7-16 named and provided (the State family table work), or overrides for every
    slot in each view.
  - TurretStateMachineCtor (562 B): needs TurretStateMachine.h.
  - SupplyTruckAIUpdate (1,658 B): held.
- SupplyTruckAIUpdate.cpp to-do, read-only survey (still held at 21:30 UTC by
  codex-01a1071d-root-recovery-oct11):
  - change its two `struct State` lines to `class State`;
  - respell its 7 condition rows to `PAVState@@` with tombstones;
  - apply v2 with them.
  The README lists the rows and addresses. Its own step B needs State views rebased on canonical
  State.

Repaired (2026-11-02, lk18), the State-slot blocker: canonical State's slots 7-16, plus slots 1 and
4, now have base bodies, so a unit that emits a State-derived table no longer references names no
unit defines. Base `9e271b3526`.
- Target facts: base table 0x00C605D8 (ctor 0x004D73FC) holds:
  - slots 1, 7 and 16: the bare RET 0x000B3FD0;
  - slot 4: `xor eax,eax; ret` 0x000D43D0;
  - slot 5: RET 4 0x0047A69C (pinned);
  - slots 2, 3 and 6: `__purecall`;
  - slots 8-15: `xor al,al; ret` 0x0047A699.
  No slot from 7 to 16 is pure. Every base body is a shared ICF fold rowed under other classes'
  names, so `StateMachine.h` defines them inline, as Zero Hour does.
- Names: slot 8 is `isAttack`. The rowed overrides (0x003422EF, 0x00341D81, 0x0034141F) sit in
  slot 8, and `isInAttackState` 0x002621B8 calls `[eax+20h]`. The other slots keep placeholders,
  because the private views conflict (slot 10 vs 14 for `isBusy`).
- State also gains Zero Hour's `getMachine`, `getMachineOwner` and `getMachineGoalObject` (const).
  The last two are defined in `StateMachineClass.h`. Eleven private views already emit identical
  COMDATs under these names.
- Verified: the 120 includers rebuild 907/907, and 0 objects change (symbols and COMDAT digests).
  No current object emits a canonical-State-derived table.
- Step B for the last three units is banked:
  `reverse/attempt_support/link177-state-classkey-20261102/step-b-v2-dock-attackmove-turret.patch`,
  after v2. The units are AIAttackMoveStateMachine (State-derived views on the new slots), AIDock
  (canonical accessors; opaque `new`-only states) and TurretStateMachineCtor (opaque turret-state
  views).
- Trial over 473 State-family units (v2 + nine + AIStateMachineCtor + this): 442 -> 455 link,
  566,226 -> 576,814 B (+10,588), none lost. AIDock 2,608, AIAttackMove 654 and Turret 562 B are
  this patch's share.
- Every step-B patch still waits on v2, and v2 waits on SupplyTruckAIUpdate.cpp. That file was
  still held by codex-01a1071d-root-recovery-oct11 at 22:40.

Landed (2026-11-02, lk18), item 1 step A, the State class key. SupplyTruckAIUpdate.cpp was freed by
codex-01a1071d at 22:38, and lk18 claimed it.
- Applied: lk17's `state-classkey-v2.patch` sources (32 units) plus SupplyTruck's two `struct State`
  lines and its comment.
- 20 rows respelled `PAUState@@` -> `PAVState@@`, each with a tombstone and a re_log `solved` verdict.
  These are the 13 rows from v2 and SupplyTruck's 7 conditions.
- The three State tree pins (`_M_find` 0x00357180, `_M_create_node` 0x00382B7F, `insert_unique`
  0x004D795B) are renamed in place with their fold-proof notes. The hatch_baseline hunk in v2 is
  obsolete: master had already dropped that allow token.
- Verified:
  - `./build.sh` passes 500/500 rows over the 33 units;
  - no live source's object still spells `UState@@`;
  - check_csv and pin_consistency pass;
  - `link_check` over 527 State-family units gives 482/527 and 584,501 B both before and after. The
    class key moves no bytes by itself.

Landed (2026-11-02, lk18), item 1 step B for ten units. These are lk17's banked
`step-b-v2-nine-ctors.patch` and `step-b-v2-aistatemachinector.patch`, applied unchanged on the class
key: AttackFireWhileChargingMachine, AIGuardMachineCtor, AIGuardRetaliateMachineCtor,
Rva00544C51MachineCtor, AttackStateMachine, AttackMeleeStateMachine, AITNGuardMachineCtor,
Rva00343756Ctor, Rva0033FC0ACtor and AIStateMachineCtor.
- Each unit includes `StateMachineClass.h`, so its `??_7` machine table equals
  Rva004D759CDerived.cpp's 16-slot copy. Its `new`-only states keep opaque, size-preserving views.
- Verified: `./build.sh` passes 141/141 rows; find_declared_unmatched and class_gate are clean.
- `link_check` over 527 State-family units: 482 -> 492 link, 584,501 -> 591,265 B (+6,764). All ten
  link again, and none is lost.

Landed (2026-11-02, lk18), item 1 step B for AIAttackMoveStateMachine, AIDock and
TurretStateMachineCtor. This is lk18's `step-b-v2-dock-attackmove-turret.patch`, unchanged; it needs
the State slot bodies and accessors landed above.
- Verified: `./build.sh` passes 71/71 rows plus AIDock's 7 data rows; find_declared_unmatched and
  class_gate are clean.
- `link_check` over 527 State-family units: 492 -> 495 link, 591,265 -> 595,089 B (+3,824). All three
  link again, and none is lost.
- Left in item 1: SupplyTruckAIUpdate.cpp (1,658 B; `??_7SupplyTruckStateMachine@@6B@` still loses).

Landed (2026-11-02, lk18), item 1 step B for SupplyTruckAIUpdate.cpp, the last of the 13 losers.
- The unit includes `StateMachineClass.h`, so SupplyTruckStateMachine, with its ctor, dtor and
  condition statics, emits the holder's 16-slot table.
- The private StateMachine and State views and the duplicate StateReturnType enum go. The
  conditions and Rva004A6979::onEnter use canonical `getMachineOwner()`.
- The six machine states are created here with plain operator new, while their ctors are rowed
  elsewhere. They stay State-derived and declare the update/GetSnapshotName/xfer overrides, so they
  are not abstract. No table is emitted here.
- Verified: `./build.sh` passes 37/37 rows; find_declared_unmatched and class_gate are clean.
- `link_check` over 527 State-family units: 495 -> 496 link, 595,089 -> 596,747 B (+1,658), none
  lost.
- Item 1 total, base `36e2341322` -> this commit: 482 -> 496 link, 584,501 -> 596,747 B (+12,246).
  All 13 LINK-177 item-1 losers link again, and Rva0033FC0ACtor does too.

New obstacle (2026-11-02, lk17), BridgeBehaviorCtor.cpp (196 B): unresolved
`??_7BridgeBehavior@@6BMiBase1@@@`. BridgeBehaviorDtor.cpp stores retail 0x00C40920 at +0x0C
under the name `??_7BridgeBehavior@@6BBehaviorModuleInterface@@@`. Rebinding the ctor's
`__identifier` extern to that name fails with C2373: the ctor's BridgeBehavior derives from
canonical UpdateModule, so cl owns that vftable name itself. The ctor has to install its tables
through a real class view (BridgeBehaviorInterface, DamageModuleInterface and DieModuleInterface
bases, as the dtor declares) instead of hand-written stores. Trial reverted; the verdict is in
re_attempts.log.
- W3DScriptedModelDrawDestructor (lk16): canonical DrawModule.h makes the dtor call
  `??1DrawModule@@MAE@XZ`. Retail inlines it: the body ends with the 0x00BC9690 store and a call to
  0x0049B47C.
  - An in-TU `inline DrawModule::~DrawModule() {}` restores 3/3 rows and the `6BDrawModule` table.
  - It then emits the canonical 62-slot `??_7DrawModule@@6B@` against the 4fe3271e copy that all 8
    private-view emitters share (DrawModule.cpp first).
  - Needs the family-wide DrawModule inline-destructor/table decision. Reverted (re_attempts.log).
- Rva001041BDASlot1 (418 B) LINKS again on current objects (link_check, base `bb0c2735b9`). No work
  needed.

Process note: the adoption batches' own link guard predicts only the adopted units; the losers are
untouched siblings that bind the same COMDAT names. Before adopting a header in a unit that defines
a class family's destructors, run `link_check` over every unit touching the family's `??_7` names
(index `touches`), as LINK-168 recommends. Census confirmation: pending (the next census will
record these losses).

- **2026-11-04 LaserDraw consolidation:** typed storage and inline teardown now preserve all 23 combined bodies, but LinkGuard refuses `??_7DrawModule@@6B@` and the constructor's `??_7W3DLaserDraw@@6BDrawModule@@@` copy; standalone units still preview as linking. The shared table contract remains prerequisite. [Evidence](../../reverse/attempt_support/laserdraw-tu-contracts-20261104-codexb4.md).

- **2026-11-05 StateMachine follow-up:** AttackPositionHorde constructor/destructor now adopt together with the canonical header first; all five adopted units preserve their scoped 1,044 B in the preview and retire five header entries. Other items remain open. [Evidence](../../reverse/attempt_support/statemachine-header-adoptions-20261105-codexb2.md).

- **2026-11-10 `Rva001041BDASlot1.cpp` cleared:** Census `05cba3c7ab` (`2026-11-10 10:49 UTC`) still showed `Rva001041BDASlot1.cpp` failing on `??_7Rva001040D5@@6B@` against `Rva001040D5Ctor.cpp`'s canonical 28-slot copy. `Rva001041BDASlot1.cpp` now adopts canonical `SimpleSceneClass.h` and `Vector3Data.h` (dropping the private `SimpleSceneClass`, `Vector3`, and `Rva001040D5Dispatch` views), retiring both `header_queue.tsv` entries. Verified: 5/5 rows and EH EXACT, `find_declared_unmatched.py --fail` clean, `hatch_counters.py --report` zero drift, `link_check` 2/2 cleanly (`LINKED 18 -> 436 bytes`; `Rva001041BDASlot1.cpp` 0 -> 418 B, `Rva001040D5Ctor.cpp` 18 B unchanged); census confirmation pending.
- **2026-11-10 `UpgradeSoundSelectorClientBehavior.cpp` repaired via `UpgradeSoundSelectorDataFindName.cpp` (+1,123 B):** Adopting canonical `Rva002390CB.h` (`5e397155d22088`, out-of-line `~Rva002390CB()`) in `UpgradeSoundSelectorDataFindName.cpp` caused `struct Rva002C99FB`'s implicit dtor COMDAT (`??1Rva002C99FB@@QAE@XZ`) to emit a 5-byte `jmp` thunk conflicting with `UpgradeSoundSelectorClientBehavior.cpp`'s retail 13-byte `0x004C9F38` COMDAT. Declaring `~Rva002C99FB();` out of line in `UpgradeSoundSelectorDataFindName.cpp` suppresses the 5-byte COMDAT (and COFF inspection confirms no remaining `undefs` for `??1Rva002C99FB@@QAE@XZ`), while keeping `header_queue.tsv:4127` open until `Rva002C99FB`/`Rva002390CB` can unify cleanly without losing `0x004CB167`/`0x004CB2FB`'s `[ebp-4]` wrapper layout. Verified: 2/2 rows, `eh_verify.py`, `find_declared_unmatched.py --fail`, `class_gate.py`, and `hatch_counters.py --report` clean; `link_check` over 5 `Rva002C99FB` units gives 5/5 cleanly (`LINKED 744 -> 1,867 bytes`; `UpgradeSoundSelectorClientBehavior.cpp` 0 -> 1,123 B); census confirmation pending.
- **2026-11-10 `XferSaveOpen.cpp` repaired via `ArmorHashMapErase.cpp` (+169 B):** Census `682a5d2110` (`2026-11-10 12:07 UTC`) still showed `XferSaveOpen.cpp` losing `?_M_delete_node@?$hashtable<NameKeyType, ArmorTemplate, ...>` (`bd3e39f02146`) to `ArmorHashMapErase.obj`'s non-retail 32-byte COMDAT (`78ce13e46ca6`), instantiated by its `?erase@?$hashtable` copy (also needed by `Rva002AD13F.cpp` and `Rva002AD19EArmor.cpp`). Declaring `ArmorTable::_M_delete_node` out of line in `ArmorHashMapErase.cpp` suppresses its conflicting COMDAT so `erase` binds `XferSaveOpen.obj`'s `bd3e39f02146` copy while keeping canonical `Armor.h` and `?erase@?$hashtable`. Verified: 1/1 row (`0x001E2861`), `eh_verify.py`, `find_declared_unmatched.py --fail`, `class_gate.py`, and `hatch_counters.py --report` clean; `link_check` across 11 `ArmorTemplate`/`FXList` callers/siblings + 9 additional `Armor` units gives 11/11 and 9/9 cleanly (`XferSaveOpen.cpp` `0 -> 169 B`, `ArmorHashMapErase.cpp` `30 -> 30 B` with its `?deallocate@_STLP_alloc_proxy` diagnostic cleared); census confirmation pending.

**2026-11-10, restore the Armor node deletion provider.** Real link d5d330359e (run 42854058132) reported 13 unresolved, including LNK2019 from ArmorHashMapErase. After 72e0f84542 both its object and XferSaveOpen.obj had the same undefined Armor node-deletion symbol. Removing only the new specialization declaration restores the STLport instantiation in XferSaveOpen. Its complete 20 bytes match retail RVA 0x004D96BA after resolving its sole REL32 operand at +12 to free (RVA 0x00030830). The two scoped rows match. Against index 60189f9ced, the same paired preview went from 0/2 to 2/2 (199 bytes); the unreferenced one-byte Destroy copy remains a diagnostic. Confirmation for this symbol awaits the next real link containing the repair.
