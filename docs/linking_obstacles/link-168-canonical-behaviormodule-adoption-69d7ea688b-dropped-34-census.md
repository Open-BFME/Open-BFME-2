### LINK-168: canonical BehaviorModule adoption (69d7ea688b) dropped 34 census-linked module units (2026-11-01, seat halilkkaya-lk10)

Status: Open (partly repaired). Updated: 2026-11-01; inspected revision `39dfbbdb50`, index `0d24c60eef` (09:19).
Census 03:00 (`ee981931dc`) -> 07:56 (`00f3a8f97b`): LINKING 7,466,117 -> 7,457,427 B,
unresolved 2,993 -> 3,020. 34 surviving units went from linked to not linked
(`reverse/link_status.csv` at `74e616b469` vs `a02a086db1`; the other 59 that left
the list are deleted TU-merge donors). All 34 trace to `69d7ea688b` ("Adopt canonical
BehaviorModule chain in 214 units"), which replaced private `BehaviorModule` views
(bases spelled `BehaviorModuleBase`/`BehaviorModuleOther`/`BehaviorModuleInterface`
with a one-slot anchor) by `GameLogic/Module/BehaviorModule.h`. Four mechanisms:

1. **Renamed vftables bound by explicit identifier** (LINK-157 pattern). A unit whose
   compiled class view defined `??_7X@@6BBehaviorModuleOther@@@` (or `6BBehaviorModuleBase`)
   now emits `??_7X@@6BBehaviorModuleInterface@@@` (`6BObjectModule`); sibling ctor units
   that store those tables through `extern "C" __identifier(...)` lost their definer.
   Fix: bind the name the definer now emits; scoped DIR32 proves both names sit on the
   same retail table. `c3e8f0752f` (canonical UpdateModule, after the census) renamed
   `6BRva0024A797_Root`/`_B2` the same way in `Rva0024A797Grandchildren.cpp`.
2. **Canonical vs Zero Hour BehaviorModule tables.** The canonical header defines
   `virtual ~BehaviorModule() { }` inline; a unit that defines the constructor of a class
   derived from BehaviorModule odr-uses the base destructor (MSVC emits it even with
   `-EHsc-`; scratch compile of DamageModuleCtor.cpp: with the ctor body the object defines
   `??1BehaviorModule@@UAE@XZ` and both `??_7BehaviorModule@@6B...` tables, without it none,
   and declaring `~DamageModule()` out of line does not help). Its 47-slot tables (188 B,
   retail size of 0x00BEE9C0) then collide with the 34-slot Zero Hour copies that ten
   ZH-header units emit (DumbProjectileBehavior.cpp is first in link order, place 67;
   CreateModule, CreateObjectDie, BridgeTowerBehavior, SpecialPowerCompletionDie and
   FXListDie link with it). No retail address for the name -> `first` rule -> every
   canonical copy loses. Units: UpdateModuleCtor, RunOffMapBehaviorCtor, DamageModuleCtor,
   SpecialPowerModuleCtor, BodyModuleCtor, FireWeaponCollide (the rows themselves stay
   exact). A per-unit fix is impossible without a private BehaviorModule copy (refused:
   the class is registered canonical); the remedy is in the header (owner
   StarkillerHDX holds `class:BehaviorModule`): e.g. declare the destructor
   `protected: virtual ~BehaviorModule();` out of line, the spelling the ZH copies
   (`??1BehaviorModule@@MAE@XZ`, 10 identical COMDATs) provide and the pre-adoption
   views used, or move the ZH-header units onto the canonical layout.
3. **Implicit destructors now virtual.** Private UpdateModule/derived views without a
   declared destructor inherit the canonical virtual one, so their ctor units emit inline
   `??1UpdateModule@@UAE@XZ`, `??1AIGateUpdate@@UAE@XZ`, `??1DestroyEnvironmentUpdate@@UAE@XZ`
   (retail-proven wrong, and duplicates of the rowed strong definitions), which also drags
   in mechanism 2. Losers: AIGateUpdateCtor/Dtor, DestroyEnvironmentUpdate(+Ctor),
   Rva0024A797DeletingDtor (duplicate of its own row `??1UpdateModule@@UAE@XZ`). Fix: the
   ctor unit declares the rowed destructors (`virtual ~UpdateModule();`, `virtual ~X();`)
   so it references them instead of emitting copies.
4. **Same-name class tables with different slots.** Pairs of units for one class now both
   spell `??_7X@@6BBehaviorModuleInterface@@@`/`6BObjectModule@@@` but one emits the
   canonical BehaviorModule-shaped table (digest `d0dadb66`, no getUpdate override) and the
   other a private all-`__purecall`, one-slot-anchor or ZH 34-slot table. Losers:
   ReplenishUnitsBehavior.cpp, SiegeDockingBehaviorDtor, SpecialPowerModuleDtor_Unresolved,
   MonitorConditionUpdate.cpp, StructureToppleUpdateCtor, AutoPickUpUpdate.cpp. Neither copy
   is retail's (retail +0x0C tables override slot 9 with 0x002533D3 for UpdateModule
   classes; compare the qc-11/hb1 notes above). Prerequisite: give both views the class's
   native overrides (canonical UpdateModule.h where it applies) so the copies agree.

| Unit | B | Mechanism | Status |
|---|---:|---|---|
| OathbreakersFadeAwayBehaviorCtor | 59 | 1 | links again: `9c6a1c1279` adopted canonical UpdateModule (compiler vptr stores) |
| StancesBehaviorCtor, AttachUpdateCtor, BannerCarrierUpdateCtor, DamageFieldUpdateBehaviorCtor/Dtor, FadeAndDieOrnamentUpdateCtor, HordeNotify.../NotifyTargetsOfImminentProbableCrushingUpdateCtor, RespawnUpdateCtor, StrafeAreaUpdateCtor | 967 | 1 | repaired (this entry, first commit): bind `??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@` |
| SupplyWarehouseCripplingBehaviorCtor, WallUpgradeUpdate | 1,143 | 1 | repaired (second commit): `??_7PoisonedBehavior@@6BBehaviorModuleInterface@@@` (0x00C49800) and the `c3e8f0752f` renames `??_7Rva004839D3@@6BRva004839D3_E1/UpdateModule/ObjectModule@@@`, `??_7Rva004AB246@@6BUpdateModule/ObjectModule@@@` |
| BloodthirstyUpdateCtor, RainOfFireUpdateCtor | 250 | 1 | repaired (second commit): `6BObjectModule`/`6BBehaviorModuleInterface` tables their Dtor units emit |
| BridgeBehaviorCtor, QueueProductionExitUpdateCtor | 302 | 1 | QueueProductionExitUpdateCtor links again (2026-11-01, lk12, below). BridgeBehaviorCtor still blocked: `6BMiBase1` (0x00C40920) is now BridgeBehaviorDtor.cpp's `6BBehaviorModuleInterface` (retail DIR32 pair), but the unit's own view derives from BehaviorModuleInterface, so rebinding is C2373. Moving the ctor to canonical UpdateModule with compiler vptr stores is not enough either: BridgeBehaviorDtor.cpp (first in link order, held by StarkillerHDX) emits a primary `6BObjectModule` table whose slots 1-4 are UpdateModule's defaults, while retail 0x00C409DC (the ctor's byte-verified `_vtbl_00C409DC` data row) holds 0x00497805, BridgeBehavior::GetSnapshotName, ::xfer and ::getModuleNameKey; the Dtor's view needs those overrides first |
| UpdateModuleCtor, RunOffMapBehaviorCtor, DamageModuleCtor, SpecialPowerModuleCtor, BodyModuleCtor, FireWeaponCollide | 1,167 | 2 | repaired (2026-11-02, lk15): the canonical header declares `protected: virtual ~BehaviorModule();` out of line; all six predict LINKS (below) |
| AIGateUpdateCtor, DestroyEnvironmentUpdateCtor | 132 | 3 (+2) | Both corrected by explicit existing destructor declarations (2026-11-01, Cortys). Historical held-scope blocker retained below. |
| AIGateUpdateDtor, DestroyEnvironmentUpdate, Rva0024A797DeletingDtor | 413 | 3 (victims) | All three now predict LINKS after the three constructor units reference their existing destructors |
| ReplenishUnitsBehavior, SiegeDockingBehaviorDtor, SpecialPowerModuleDtor_Unresolved, MonitorConditionUpdate, StructureToppleUpdateCtor, AutoPickUpUpdate | 3,940 | 4 | AutoPickUpUpdate and StructureToppleUpdateCtor repaired by other seats (2026-11-02); ReplenishUnitsBehavior, MonitorConditionUpdate and SiegeDockingBehaviorDtor repaired (lk15, below); SpecialPowerModuleDtor_Unresolved open |

**AIGate scoped repair (2026-11-01, Cortys):** the constructor now declares the
existing UpdateModule and AIGateUpdate destructors out of line. All five strict
rows pass, all 56 retained complete code definitions/relocations are identical
to the original-source control, and four implicit destructor definitions
disappear. Against index86db074988, the constructor improves 0 -> 62 linking
bytes and its destructor unit 0 -> 154. The common UpdateModule destructor
unit still has another duplicate; no census or shared-header closure is claimed.
Evidence: `reverse/attempt_support/aigate-destructor-declarations-20261101/`.
Earlier file reservations prevented this repair; its constructor scope is now
available and claimed. No claim is taken over from another worker.

**DestroyEnvironment follow-up (2026-11-01, Cortys):** its constructor now has
the same two out-of-line destructor declarations. Nine strict rows pass; all
58 retained complete code definitions/relocations are unchanged and four
implicit definitions disappear. The current five-source preview adds 277
linking bytes (70 constructor, 207 destructor unit) and retains AIGate's 62.
The common base unit still has UpdateModuleCtor's copy. The prior AIGate push
audit remains inconclusive on the older index and an AICowerState_onEnter.cpp
receipt; carry that broader scope into the next census. Evidence:
`reverse/attempt_support/destroy-environment-declarations-20261101/`.

**Remaining base-copy repair (2026-11-01, Cortys):** UpdateModuleCtor now declares
its existing destructor out of line. Three strict rows pass and all 59 retained
complete definitions/relocations are unchanged; only its implicit destructor
copy disappears. The current six-source cohort predicts 545 linking bytes over
five units, including the common base unit's new 52 bytes. UpdateModuleCtor
itself still has the two BehaviorModule vtable COMDAT obstacles, requiring the
separate canonical destructor-contract repair. No census gain is claimed.
Evidence: `reverse/attempt_support/update-module-destructor-declaration-20261101/`.

Completed: group 1 rebinding of the AttributeModifierPoolUpdate folded table
(0x00BEFF90) in ten ctor units. `./build.sh` 17/17 rows over the ten files; scoped
DIR32 OK (65 rows, 31 symbols, including AttributeModifierPoolUpdate.cpp's own rows);
`link_check` 0 -> 967 B for the ten units, AttributeModifierPoolUpdate.cpp 3,869 ->
3,869 B (LINKS).
Update (2026-11-01, behavior-module-other-bind): all ten group-1 units
(`AttachUpdateCtor.cpp`, `StancesBehaviorCtor.cpp`, `BannerCarrierUpdateCtor.cpp`,
`DamageFieldUpdateBehaviorDtor.cpp`, `DamageFieldUpdateBehaviorCtor.cpp`,
`FadeAndDieOrnamentUpdateCtor.cpp`, `HordeNotifyTargetsOfImminentProbableCrushingUpdateCtor.cpp`,
`NotifyTargetsOfImminentProbableCrushingUpdateCtor.cpp`, `RespawnUpdateCtor.cpp` and
`StrafeAreaUpdateCtor.cpp`) re-bound `??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@`
to `??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@` (0x00BEFF90), matching
the converged data ledger symbol and the actual table emitted by `AttributeModifierPoolUpdate.cpp`.
All ten units now LINK cleanly (0 -> 967 bytes, `link_check.py`).
Correction (2026-11-01, seat halilkkaya-lk11): that rebind (`f363137e8e`, `aaea1a560e`)
undid the repair. No object defines `??_7AttributeModifierPoolUpdate@@6BBehaviorModuleOther@@@`
(index `86db074988`: no comdat or strong entry; the spelling survives only in the generated
`reverse/data_ledger.csv` names column), while AttributeModifierPoolUpdate.cpp's current object
emits `??_7AttributeModifierPoolUpdate@@6BBehaviorModuleInterface@@@` (canonical chain since
`69d7ea688b`). With current objects all ten units were unresolved again (0 B). They bind the
`6BBehaviorModuleInterface` name once more, and their comments now say the ledger spelling
has no definer. `./build.sh` 17/17 rows and 9 data rows; scoped DIR32 OK (65 rows, 31 symbols,
definer included); `link_check` 0 -> 967 B for the ten units, AttributeModifierPoolUpdate.cpp
3,869 B unchanged. Pattern: bind an explicit vftable identifier only to a name the definer's
current object emits (dump its COFF symbols or query the index), never to a data-ledger name.
Second commit: the four group-1 units above bind the names PoisonedBehavior.cpp,
Rva0024A797Grandchildren.cpp, BloodthirstyUpdateDtor.cpp and RainOfFireUpdateDtor.cpp
emit for the same retail tables (0x00C49800, 0x00C49AAC/AB8/AC8, 0x00C54774/780,
0x00C3EFF8/F0B4, 0x00C54BB8/C74). `./build.sh` 25/25 rows; scoped DIR32 OK (90 rows,
119 symbols, definers included); `link_check` 0 -> 1,393 B for the four units, definers
PoisonedBehavior 746, BloodthirstyUpdateDtor 60, RainOfFireUpdateDtor 129 unchanged.
New regression seen on the way (not from this entry's commits): with current objects
Rva0024A797Grandchildren.cpp (1,280 B, linked in the 07:56 census) now loses the
`??_7StructureToppleUpdate@@6BUpdateModule/BehaviorModuleInterface/ObjectModule@@@`
copies to StructureToppleUpdate.cpp's Zero Hour tables (first in link order), after
`c3e8f0752f` moved it onto canonical UpdateModule (mechanism 4).
Mechanism 4, ReplenishUnitsBehavior (2026-11-02, lk15): the two `??_7ReplenishUnitsBehavior@@6BObjectModule@@@`
copies differed in primary slots 2-4. Retail 0x00C4A034: slot 1 0x004B7BAA (rowed as the
AudioLoopUpgrade loadPostProcess fold), 2 0x00484181 (`Rva00484181Named::name` placeholder, the name
getter), 3 0x00484365 `ReplenishUnitsBehavior::xfer`, 4 0x00484187 `ReplenishUnitsBehavior::getModuleNameKey`.
ReplenishUnitsBehavior.cpp read Snapshot without the name slot (slot 2 `crc@UpdateModule`) and
ReplenishUnitsBehaviorDtor.cpp (first) lacked both overrides (slot 3 `xfer@UpdateModule`, slot 4
`__purecall`). The .cpp now defines `BFME_SNAPSHOT_NAME_SLOT` before ObjectModule.h (as AutoPickUpUpdate)
and the Dtor declares the two rowed overrides; both emit the same table (slots 3-4 now retail, slots
1-2 still the UpdateModule defaults: the folds need identity work). `./build.sh` 25/25 rows; scoped
DIR32 OK (20 symbols); only the two units touch the table; object definitions otherwise unchanged
against the index; `link_check` ReplenishUnitsBehavior.cpp 0 -> 1,050 B, Dtor 60 B unchanged.
Mechanism 4, MonitorConditionUpdate (2026-11-02, lk15): the same pattern. Retail 0x0084DAD8 (VA
0x00C4DAD8) slots 3/4 are the rowed `MonitorConditionUpdate::xfer` 0x004915C6 and `::getModuleNameKey`
0x00491667; MonitorConditionUpdate.cpp spelled slot 2 `crc` and FamilyDeletingDtors_muse-2c79.cpp
(first) had slot 3 `UpdateModule::xfer` and slot 4 `__purecall`. The .cpp defines
`BFME_SNAPSHOT_NAME_SLOT` before ObjectModule.h and the family view declares the two overrides.
`./build.sh` 14/14 rows; scoped DIR32 OK (8 symbols); only the two units touch the tables and only
the primary table changed (now one digest); `link_check` MonitorConditionUpdate.cpp 0 -> 334 B,
FamilyDeletingDtors_muse-2c79 56 B unchanged.
Mechanism 4, SiegeDockingBehavior (2026-11-02, lk15): SiegeDockingBehavior.cpp (first) read
SiegeDockingBehaviorView.h, whose private BehaviorModule/UpdateModule copies (one-slot interfaces)
gave a 10-slot primary table with `__purecall` in slots 1-3 and a one-slot BehaviorModuleInterface
table, against the Dtor's canonical copies. The view now includes canonical UpdateModule.h (with
`BFME_SNAPSHOT_NAME_SLOT`) and both views declare the rowed overrides retail 0x00C414DC holds in
slots 1, 3 and 4 (`loadPostProcess` 0x0045A16D, `xfer` 0x0045A02F, `getModuleNameKey` 0x004599E5);
slot 2 (0x004599DF, the placeholder `Rva4599DFGet`) stays UpdateModule's getter. All four
SiegeDockingBehavior tables now have one digest across both units; the .cpp additionally emits the
canonical inline getters, identical to the 125 existing copies. `./build.sh` 11/11 rows; scoped
DIR32 OK (9 symbols); only the two units touch the tables; `link_check` SiegeDockingBehaviorDtor
0 -> 129 B, SiegeDockingBehavior.cpp 204 B unchanged.
Checked and left (2026-11-02, lk15): BridgeBehaviorCtor (196 B) is on canonical UpdateModule now,
but binding `extern __identifier("??_7BridgeBehavior@@6BBehaviorModuleInterface@@@")` (the Dtor's name
for 0x00C40920) fails C3861: the compiler resolves that identifier as its own vftable. The remaining
route is compiler vptr stores through real BridgeBehaviorInterface/DamageModuleInterface/
DieModuleInterface bases, which first needs the +0x20/+0x28 folded tables (0x00C40818, 0x00C1C780,
today bound through other classes' ledger names) and the Dtor's primary overrides (retail 0x00C409DC
slots 1-4) reconciled; re_attempts verdict on 0x00457472. SpecialPowerModuleDtor_Unresolved (222 B):
~SpecialPowerModule (0x00493DEF) inlines ~BehaviorModule (stores 0x00BEEA7C/0x00BEE9C0), so a canonical
view must define the empty destructor inline in that unit and then emits the 47-slot
`??_7BehaviorModule@@6B...` tables, which lose to the nine Zero Hour units' 34-slot copies exactly as
mechanism 2 did. Prerequisite (family-wide): those ZH copies go (their units move onto BFME views)
or the two retail tables get proven names so the canonical copies win.
Mechanism 4, ThreatFinderUpdate (2026-11-02, lk15): ThreatFinderUpdate.cpp (first) reads Snapshot
through PlayerList.h, which selects the capitalized slot names, so canonical UpdateModule's
`loadPostProcess`/`xfer` overrode nothing and were appended (15 slots, `__purecall` in 1 and 3, the
rowed `xfer` at 12). Retail 0x00C360CC has 13 slots (0x00C36100 starts the next table) with
`ThreatFinderUpdate::xfer` 0x003ECED5 in slot 3 and `::getModuleNameKey` 0x003ECCD6 in slot 4. The
.cpp now includes the moduledata Snapshot with `BFME_SNAPSHOT_NAME_SLOT` before PlayerList.h and the
Dtor declares both overrides; the one table digest is shared. `./build.sh` 24/24 rows; scoped DIR32
OK (19 symbols); only the two units touch the tables; `link_check` ThreatFinderUpdateDtor 0 -> 125 B,
ThreatFinderUpdate.cpp 1,167, MapLoadPostProcess 172 and FriendNew 56 B unchanged.
Mechanism 2 repair (2026-11-02, seat halilkkaya-lk15, base `1765dc430d`, index 08:35
`984a4cdc4d`): `BehaviorModule.h` now declares `protected: virtual ~BehaviorModule();` with no
body, the proposal below. Scope proof before the edit: in the census index exactly six objects
define `??1BehaviorModule@@UAE@XZ` and the canonical 47-slot `??_7BehaviorModule@@6B...` tables
(the six units above, digests `80eaa6db`/`d0dadb66`), and no other object touches those names, so
no other canonical unit inlined the empty destructor (an inlined copy would reference the tables).
After the edit the six objects define none of them; only SpecialPowerModuleCtor gains an external
reference, `??1BehaviorModule@@MAE@XZ`, from its constructor's state-0 unwind action, which the
nine Zero Hour units already provide as identical COMDATs (`d8d55189`, no retail address, the
same provider WeaponModeSpecialPowerUpdateCtorThunk.cpp already links against). `./build.sh`
22/22 rows over the six sources (three funclet labels renumbered, parent EH data verified);
`link_check`: all six 0 -> LINKS, 1,167 B (UpdateModuleCtor 61, RunOffMapBehaviorCtor 49,
DamageModuleCtor 49, SpecialPowerModuleCtor 340, BodyModuleCtor 109, FireWeaponCollide 559).
Identity lead found on the way (not acted on): retail's out-of-line ~BehaviorModule exists.
SpecialPowerModule's ctor 0x00493C5A has FuncInfo 0x00D3CA18 (two unwind states); state 0's action
0x0078CDDB (`mov ecx,[ebp-14h]; jmp`) jumps to 0x004607E1, an 18-byte body storing 0x00BEEA7C at
+0 and 0x00BEE9C0 at +0x0C and tail-jumping the Snapshot fold 0x0049B47C, i.e. BehaviorModule's
destructor. It is rowed as the placeholder `??1Rva004607E1@@UAE@XZ` (Rva0049B47CDerived.cpp;
`CreateModule.cpp` and `UpgradeModuleCtor.cpp` also spell it). Folding `Rva004607E1` into
`BehaviorModule` (`rename.py class --fold`, a placeholder-into-existing-class decision) would give
`??1BehaviorModule@@MAE@XZ` a retail address; check first that the Zero Hour copies then lose
nothing (they would be proven wrong unless the retail-shaped copy is supplied). Census
confirmation: pending.
Mechanism 2 tested proposal (third commit, no header change landed): with the header
temporarily patched to `protected: virtual ~BehaviorModule();` (declaration only) and the
eight affected ctor units compiled into `build/lk10_scratch` (never `build/match`; header
restored byte-identical), all 24 rows of those units keep identical COMDAT bodies and
relocation names, none of them defines `??1BehaviorModule@@UAE@XZ`,
`??_GBehaviorModule@@UAEPAXI@Z` or either `??_7BehaviorModule@@6B...` table, and the only new
external is `??1BehaviorModule@@MAE@XZ`, which the ten ZH units already provide as identical
COMDATs (census `first` rule: no loser). That would clear RunOffMapBehaviorCtor,
DamageModuleCtor, BodyModuleCtor, FireWeaponCollide and SpecialPowerModuleCtor (1,106 B,
pending a real current-object `link_check`), and UpdateModuleCtor (61 B) once its private
UpdateModule view also declares `virtual ~UpdateModule();` (rowed in
Rva0024A797DeletingDtor.cpp). The protected spelling is the one retail and Zero Hour use for
module destructors (`??1DieModule@@MAE@XZ`, MEMORY_POOL_GLUE_ABC). Cost: a canonical unit that
must inline the empty base destructor (a future canonical ~DieModule) then needs the inline
body back, so the header owner should decide; a shared-header edit takes the full gate.
Mechanism 3 for the held ctor files: canonical UpdateModule.h already declares
`virtual ~UpdateModule();`, which removes the inline ~UpdateModule/~BehaviorModule copies, but
`AIGateUpdate`/`DestroyEnvironmentUpdate` must also declare their rowed
`virtual ~AIGateUpdate();`/`virtual ~DestroyEnvironmentUpdate();`, or the vftable's `??_G`
still emits an implicit copy that duplicates the Dtor rows (scratch test above: both still
define it).
Mechanism 4 retail slots (table VAs, slot targets as RVAs, read from the image, diff against BehaviorModule's
0x00BEE9C0): SiegeDockingBehavior 0x00C41420 slots 9 (0x002533D3) and 34 (0x004543A9);
AutoPickUpUpdate 0x00C4EFB0 slots 9 and 27 (0x004543A9); ReplenishUnitsBehavior 0x00C49F78
slots 9 and 10 (0x004543A9); SpecialPowerModule 0x00BEFCF8 slots 8 (0x002533D3), 43
(0x00251C11), 44 (0x00251C24). The canonical copies (digest `d0dadb66`) override none of
them, so making the private copies equal them would only hide the defect; both views need
the native overrides (canonical UpdateModule.h supplies slot 9 for update modules).
Post-census losses from the same adoptions (current-object `link_check` over the 881
sources changed since `00f3a8f97b`, 2026-11-01 13:55; 873 link): mechanism 1 in files
held by other seats, recipes ready, names and addresses from DIR32 pairs of the definers'
rows: BridgeScaffoldBehavior.cpp (1,021 B; its rows are claimed) binds
`??_7Rva00458402@@6B@`/`6BRva0024A797_B2`/`_Mid`/`_Root@@@`, now emitted by
Rva0024A797Grandchildren.cpp as `6BRva00458402_E1@@@` (0x00C40B70, +0x20),
`6BUpdateModule@@@` (0x00C40B88, +0x10), `6BBehaviorModuleInterface@@@` (0x00C40B98, +0x0C),
`6BObjectModule@@@` (0x00C40C54, +0); OneRingPenaltyUpdate.cpp (482 B; StarkillerHDX TU merge)
binds `??_7Rva00499934@@6B@`/`_B2`/`_Root` -> `6BRva00499934_E1@@@` (0x00C50250),
`6BUpdateModule@@@` (0x00C50254), `6BObjectModule@@@` (0x00C50260), and
`??_7PropagandaTowerBehavior@@6BPB_Iface1@@@` -> `??_7Rva00499934@@6BBehaviorModuleInterface@@@`
(same folded 0x00C49188 as PropagandaTowerBehaviorConstructor.cpp's
`6BBehaviorModuleInterface`). Mechanism 4: Rva0024A797Grandchildren.cpp (1,280 B;
StructureToppleUpdate tables vs StructureToppleUpdate.cpp's ZH copies), ThreatFinderUpdateDtor
(125 B), AudioLoopUpgradeCtorModuleFactory (133 B). AudioLoopUpgradeCtorModuleFactory's
primary table differs from AudioLoopUpgradeDtor.cpp's only in slot 0
(`??_EAudioLoopUpgrade@@UAEPAXI@Z` vs `MAE`): its view leaves the destructor implicit (public);
declaring the rowed `protected: virtual ~AudioLoopUpgrade();` (`??1AudioLoopUpgrade@@MAE@XZ`,
0x004B7B20) should make the copies equal (file held by StarkillerHDX's AudioLoopUpgrade.cpp TU
merge; not tried). ThreatFinderUpdateDtor (canonical UpdateModule) and ThreatFinderUpdate.cpp
(private views, first in link order, held) differ in primary slots 1-4 and 12 and the
update-interface slots 1-2: both views need the class's native overrides.
2026-11-04: AudioLoopUpgrade's canonical sound-handle storage preserves 17/17 rows and a 680-byte link preview; [declaration prerequisites](../../reverse/attempt_support/audioloop-consolidation-prerequisites-20261104.md) remain; the include-checker fix landed and [normal UpdateModule acceptance retired both stale queue rows](../../reverse/attempt_support/audioloop-header-retirement-20261104.md), with byte and link-preservation checks passing for this source only.
2026-11-04: [AudioLoopUpgrade xfer adopts the canonical UpgradeMux base](../../reverse/attempt_support/audioloop-xfer-upgrademux-adoption-20261104.md), retiring its header-queue row with 1/1 byte match and 72 -> 72 link-preview bytes; seed adoption and the other declaration prerequisites remain.
2026-11-04: [AudioLoopUpgradeUpdate adopts canonical UpdateModule](../../reverse/attempt_support/audioloop-update-updatemodule-adoption-20261104-codexb.md), retiring its queue row with 2/2 byte matches and 81 -> 81 link-preview bytes; other declaration prerequisites remain.
Repair (2026-11-01, lk10, after `1f5e399716`): Rva0024A797Grandchildren.cpp's 1,280 B
loss was not the Grandchildren view's fault. StructureToppleUpdate.cpp (a Zero Hour port
whose only rows are two STLport helpers, link place 3720) still defined the Zero Hour
`StructureToppleUpdate::~StructureToppleUpdate() { }` under a `present-unmatched` marker.
That body is not retail's (retail's `??1StructureToppleUpdate@@UAE@XZ` 0x004A54A8 is rowed
in Grandchildren), and nothing touches its `??1`/`??_G...MAE` names, but defining it made
the unit emit the 34-slot Zero Hour `??_7StructureToppleUpdate@@6B...` tables ahead of every
other copy. Dropping the body (and its marker) removes all four tables from that object;
Grandchildren's retail-shaped copies (slot 9 = UpdateModule::getUpdate) become first.
`./build.sh` 2/2; scoped DIR32 OK (44 rows, with Grandchildren); `link_check` over all ten
units touching `StructureToppleUpdate@@` names: Grandchildren 0 -> 1,280 B (current objects),
the other eight linked units unchanged (25,246 B total), StructureToppleUpdateCtor still loses
its BehaviorModule-shaped copies (file locked by StarkillerHDX's class:BehaviorModule claim;
it needs canonical UpdateModule like Grandchildren). The other six "native overrides" units
and ThreatFinderUpdateDtor, AudioLoopUpgradeCtorModuleFactory, MonitorConditionUpdate,
and SiegeDockingBehavior(Dtor) were all locked by
StarkillerHDX claims (tu seat w2, header_adopt_lane, class:BehaviorModule) at 14:40.
Pattern: when a seed or Zero Hour port keeps an unrowed constructor or destructor body of a
module class, its tables can sit first in link order and beat retail-shaped copies; drop the
body when the row lives elsewhere.
Full sweep (2026-11-01 15:00, lk10): `link_check` over all 18,530 sources the 07:56 census
records as linked, on current objects: 18,509 link. Eleven more mechanism-1 ctor units had
lost their explicit vftable bindings to `c3e8f0752f`'s Rva0024A797Grandchildren.cpp renames
(`6BRva0024A797_Root/_Mid/_B2@@@` -> `6BObjectModule/BehaviorModuleInterface/UpdateModule@@@`,
the class's own `6B@` -> `6B<Class>_E1@@@`) and to the canonical spellings of
SpawnPointProductionExitUpdate (`6BSpawnB2/B3` -> `6BBehaviorModuleInterface/UpdateModule`),
LargeGroupAudioUpdate (`6BMiBase1/Rva0049B47C` -> `6BBehaviorModuleInterface/ObjectModule`)
and PropagandaTowerBehavior (`6BPB_Iface1` -> `6BBehaviorModuleInterface`, folded 0x00C49188).
Repaired by binding the names now emitted, each mapped by a DIR32 pair dump of the consumer
row and of the definer rows onto the same retail table: SlowDeathBehaviorCtor 276,
AutoHealBehaviorCtor 199, DefaultProductionExitUpdateCtor 130, FoundationAIUpdateCtor 117,
LargeGroupAudioUpdateCtor 120, LargeGroupBonusUpdateCtor 153, RubbleRiseUpdateCtor 150,
SlavedUpdateCtor 97, StructureCollapseUpdateCtor 149, SupplyCenterProductionExitUpdateBehaviorCtor
130, ToppleUpdateCtor 167 (1,688 B). `./build.sh` 20/20 rows; scoped DIR32 OK (156 rows, 128
symbols, definers included); `link_check` 11/11 LINKS, definers GapForwardersSeat8 691,
PropagandaTowerBehaviorConstructor 115, LargeGroupAudioUpdateDtor 74,
SpawnPointProductionExitUpdate 717 B unchanged (Rva0024A797Grandchildren links when checked
together with the current StructureToppleUpdate.cpp object). Still failing in that sweep and
not from this cause: BfmeStringTailRecord180Ctor (41), Rva00236285Ctor (47),
DisplayRegisterVideoBuffer (19) and BaseHeightMap_Rva00069F4F (62) on unprovided STLport
`__imp_` node-allocator / range-error imports, and atlbasemodule.cpp (197) on `___ImageBase`;
BattlePlanUpdateConstructor (263) loses its class tables (mechanism 4, file claimed).
Remaining / next check: the open rows above. Pattern: after a base-header adoption,
grep `__identifier("??_7<Class>@@6B<old base>@@@")` in sibling units, and check whether
any adopting unit defines a constructor (it then emits the base's inline destructor and
tables).
Repair (2026-11-01, seat halilkkaya-lk12, base `6b1a8fb85c`): a current-object
`link_check --refresh` over all 18,636 sources of the 12:39 census (`39dfbbdb50`) finds 14
census-linked units that no longer link. Two are this entry's mechanism 1, after the
held-file renames since the census: QueueProductionExitUpdateCtor.cpp (106 B) bound
`??_7QueueProductionExitUpdate@@6BBehaviorModuleBase@@@` (0x00C519C8) and
`??_7SpawnPointProductionExitUpdate@@6BSpawnB2@@@` (0x00C4B1F0); QueueProductionExitUpdateDtor.cpp
now emits the first as `6BObjectModule@@@` and SpawnPointProductionExitUpdate.cpp the second as
`6BBehaviorModuleInterface@@@` (the name lk10 bound for DefaultProductionExitUpdateCtor).
TerrainResourceBehaviorCtor.cpp (135 B) bound `??_7FakePathfindPortalBehaviour@@6BMiBase1@@@`
(0x00C42B60), which FakePathfindPortalBehaviourDtor.cpp now emits as `6BBehaviorModuleInterface@@@`.
Both bind the emitted names. `./build.sh` 1/1 and 2/2 rows (+1 data row); scoped DIR32 OK
(16 rows/18 symbols with QueueProductionExitUpdateDtor and SpawnPointProductionExitUpdate;
18 rows/17 symbols with FakePathfindPortalBehaviourDtor); `link_check --refresh`
QueueProductionExitUpdateCtor 0 -> 106 B, TerrainResourceBehaviorCtor 0 -> 135 B (current
objects), definers QueueProductionExitUpdateDtor 60, SpawnPointProductionExitUpdate 717,
FakePathfindPortalBehaviourDtor 624 B unchanged LINKS.
Same sweep, mechanism 4 (parity): FiringTrackerCtor.cpp (149 B) lost `??_7FiringTracker@@6B@`,
`6BObjectModule@@@` and `6BBehaviorModuleInterface@@@` to FiringTrackerDtor.cpp (first in link order),
which `c861eabfff` moved onto canonical UpdateModule.h while the ctor kept a private UpdateModule
(one-slot `updateModuleInterface` interface, no getUpdate). The ctor now includes the canonical
header as the Dtor reads it (no other view change; `setWakeFrame`/`m_object` come from the header).
Both copies are equal again; neither carries FiringTracker's native update/xfer overrides yet (the
Dtor is held by StarkillerHDX), so this restores the census-linked parity, not native table
correctness. `./build.sh` 1/1; scoped DIR32 OK (5 symbols, with the Dtor); `link_check --refresh`
FiringTrackerCtor 0 -> 149 B, FiringTrackerDtor 124 B unchanged LINKS.
Same sweep, held files (not edited; recipes): GettingBuiltBehaviorDtor.cpp (142 B, census-linked)
is the mirror case: `c5692cd910` moved GettingBuiltBehaviorCtor.cpp (first in link order) onto
canonical UpdateModule.h while the Dtor keeps a private UpdateModule, so the Dtor's 12-slot primary
table (slots 1-4 `__purecall`) and 1-slot `6BUpdateModule` table differ from the Ctor's 13-slot and
3-slot copies and lose. Including the canonical header in the Dtor, as above, should make them
equal (file held by StarkillerHDX at 21:50 UTC+3). Applied 2026-11-02 (lk15, base `1765dc430d`): the
Dtor drops its private UpdateModuleInterface/UpdateModule and includes canonical UpdateModule.h; no
other view change. `./build.sh` 2/2 rows; scoped DIR32 OK (8 symbols, with the Ctor); only the two
units touch `??_7GettingBuiltBehavior@@` names (index); `link_check` GettingBuiltBehaviorDtor 0 -> 142 B,
GettingBuiltBehaviorCtor 188 B unchanged LINKS. Both copies still lack GettingBuiltBehavior's native
primary overrides (parity, not native table correctness). HordeMeleeSwarm.cpp (1,947 B) reports a duplicate
`?erase@?$vector@UBfmePod28@@...`: a `link_check` artifact, since the 14:31 index still holds the
object of Rva005842F7Finish.cpp, which `ab58bb88df` merged into HordeMeleeSwarm.cpp at 17:49 (after
the index); the next census will not see that object.
lk10's held-file recipes above, applied once the files became claimable (lk12, base `c871f897be`):
BridgeScaffoldBehavior.cpp (1,021 B) binds `??_7Rva00458402@@6BObjectModule/BehaviorModuleInterface/UpdateModule@@@`
and `6BRva00458402_E1@@@` for its old `6BRva0024A797_Root/_Mid/_B2@@@` and `6B@` (+0/+0x0C/+0x10/+0x20);
OneRingPenaltyUpdate.cpp (765 B) binds `??_7Rva00499934@@6BObjectModule/UpdateModule/Rva00499934_E1@@@`
for `_Root/_B2/6B@`, and its class's own `??_7Rva00499934@@6BBehaviorModuleInterface@@@` for the folded
0x00C49188 it spelled `??_7PropagandaTowerBehavior@@6BPB_Iface1@@@`. All names are what
Rva0024A797Grandchildren.cpp's current object defines. `./build.sh` 23/23 rows; scoped DIR32 OK
(106 symbols, with Grandchildren and PropagandaTowerBehaviorConstructor); `link_check --refresh`
BridgeScaffoldBehavior 0 -> 1,021 B, OneRingPenaltyUpdate 0 -> 765 B, Grandchildren 1,280 B and
PropagandaTowerBehaviorConstructor 115 B LINKS.
Second sweep (lk12, base `dd39597a0f` with the above, census 18:30 `dae306bc9d`, its index): all
18,635 census sources with current objects, 18,472 link. Of the census-linked units, eight fail,
none from the Zero Hour body drops landed after that census (their lost definitions' outside users
are all census-unlinked: JetAIUpdate, FlightDeckBehavior, DeliverPayloadAIUpdate, PhysicsUpdate,
W3DTankTruckDraw): RelationMapXfer (LINK-170) and GettingBuiltBehaviorDtor (recipe above), both held;
HordeMeleeSwarm (index artifact above; `ab58bb88df` landed after `dae306bc9d` too);
BfmeStringTailRecord180Ctor, Rva00236285Ctor, DisplayRegisterVideoBuffer and BaseHeightMap_Rva00069F4F
(`__imp_` STLport node-allocator/range-error imports) and atlbasemodule (`___ImageBase`), the
known `link_check` modelling gaps. Other blockers checked and left: BridgeBehaviorCtor (row above),
DebugDestructorThunk (`??_7Debug@@6B@`, 1-slot view vs the 35-slot shim; retail 46 slots with a
virtual destructor, see the Debug entry; class:Debug held), W3DPropDraw (32-slot Zero Hour
`??_7DrawModule@@6B@` vs the 1-slot copies of eight other units).
Census confirmation: awaiting.
2026-11-05: AIGateUpdate seed now selects BFME2's Snapshot name slot before ObjectModule; seed/ctor/dtor retain 522 preview bytes and owning acceptance retires three stale UpdateModule queue rows. Destructor merge still needs primary-vtable parity; constructor/trigger views still differ. [Checks and next prerequisite](../../reverse/attempt_support/aigate-update-snapshot-20261105-codexb5/README.md).

2026-11-05: AIGateUpdate constructor/destructor now declare the retail slot-4 name key and share the seed field view; 5/5 rows and 522 preview bytes preserved. Dry run accepts the three-source merge; trigger remains separate. [Prerequisite evidence](../../reverse/attempt_support/aigate-update-views-20261105-codexb5/README.md).

2026-11-05: AIGateUpdate seed/ctor/dtor merged into the approved TU: two fewer files, 13/13 rows and both EH graphs exact, aliases transferred intact. Trigger layout remains the next prerequisite; broad batch audit awaits a current consumer receipt and next-census confirmation. [Merge/audit evidence](../../reverse/attempt_support/aigate-update-merge-20261105-codexb5/README.md).

2026-11-05 codex4: OneRing roaming-helper canonical headers adopted; seed adoption still needs four canonical virtual providers before merging; byte/link evidence and next steps: [handoff](../../reverse/attempt_support/onering_headers_20261105_codex4.md).

2026-11-06 real-link unresolved ?crc@BehaviorModule@@MAEXPAVXfer@@@Z (exit_link_blockers at e185a327a7, 8 units), seat leosmare:
- Target fact: retail BFME2 has no crc slot. BehaviorModule's slot 2 is GetSnapshotName (row 0x0024A791,
  BehaviorModule.cpp), so nothing defines the Zero Hour ?crc@BehaviorModule.
- SpecialPowerModule.cpp: repaired (327177475d). Its unrowed SpecialPowerModule::crc dropped the base call
  (the 1a7053eb7c pattern); the object no longer references the name. 4/4 exact, LINKS 36 -> 36 B.
- BridgeTowerBehavior.cpp: base call dropped too (f982dc9e95), but the blocker stays. The unit emits the Zero
  Hour ??_7BehaviorModule@@6BObjectModule@@@ table (from the ZH BehaviorModule.h it compiles against), and slot
  2 of that table is ?crc@BehaviorModule. FXListDie.cpp and AssistedTargetingUpdate.cpp reference the name the
  same way (table relocation, no explicit call). CreateObjectDie.cpp and SpecialPowerCompletionDie.cpp reach it
  through DieModule::crc.
- DieModule.cpp and SpawnBehavior.cpp hold the same explicit base call but were claimed by
  codex-01a1071d-root-recovery-oct11, so they were left alone.
- Remaining prerequisite: move each table-emitting unit off the Zero Hour BehaviorModule.h onto the canonical
  Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h (slot 2 = GetSnapshotName), as 1a7053eb7c did for
  CreateModule.cpp. Dropping the explicit calls alone does not clear the table reference.

2026-11-06 AssistedTargetingUpdate scoped follow-up: constructor dummy arrays
are replaced by compiler-owned native13/47/3 tables (63/63 slots checked).
Canonical0x20 UpdateModule view removes the old CRC table dependency; ctor is
merged into the approved TU,10/10 rows and2 EXACT EH graphs retained. Lifetime
source still awaits a guard-approved split; no actual image/runtime clearance
claimed. [Proof and remaining prerequisites](../../reverse/attempt_support/assisted-native-profile-20261106/README.md).
