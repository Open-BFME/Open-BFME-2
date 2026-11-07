### LINK-514: kept `??_7` copies differ from retail's vftables (runtime vtable survey)
Status: Open (partly repaired). Updated: 2026-11-07; inspected revision: e5e17e246f, getter and installer passes at be366d041e, dummy-vptr ctor pass at e44e2c5ef6c, ObjectHelper family at e1e03be955 (census index c95fcfcfcd; f44cbcf5b0 for the ctor pass; 94d8ffa1ad for the family).
Evidence / scope: [survey, method and reproduction](../../reverse/attempt_support/runtime-vtable-survey-20261105.md); [ranked table](../../reverse/attempt_support/runtime-vtable-survey-20261105.tsv); every `??_7` the census link order keeps (6,416 tables).

**Problem.** A byte-exact unit can still emit a vftable unlike retail's: a placeholder or Zero Hour-shaped
private view gives a short table, a wrong slot, or `__purecall` where retail has a body. link.exe keeps
the first COMDAT copy in link order without a word, and the census judges vftables only where a matched
`data_rows.csv` row or a pin gives the symbol an address (127 of 6,421 index names have a verdict). So
"links" does not mean "runs": calls through those slots crash or misbehave at runtime.

**Method (reusable).**
- Take each `??_7`'s first definer in `link_census.objects(ledger())` order.
- Locate retail's table from the matched rows' DIR32 vptr stores (`name_globals.load_index()`), not
  from ledger labels.
- Bound its extent by every retail `C7 /0` immediate, ledger row and code-proven table start.
- Resolve each slot's relocation the way `RetailTruth` does.

**Results (6,416 tables).**
- 1,330 equal retail.
- 3,442 can crash (any `__purecall` slot, or shorter than retail):
  - T1, boot/menu/save-load paths: 852;
  - T2, skirmish classes: 707;
  - the rest are placeholder classes.
- 136 have a wrong slot.
- 750 are unproven; 748 have no retail address.
- In referenced tables: 3,241 `__purecall` slots where retail has a body, 908 wrong slots, and
  40,230 retail slots the kept copy lacks.
- Only 10 tables have a better copy that link order discards, so the class views, not link
  order, are the cause.

**Top risks.**
- `W3DDisplay` (1/101 slots, kept from W3DDisplayDtor.cpp).
- `AudioManager`'s SubsystemInterface table (14/105).
- `InGameUI` (7/120).
- `XferSave` (1/39) and `XferMD5CRC` (2/39), on the save/load and game-logic CRC path.
- The AIUpdate family's ObjectModule tables (12-16/154).
- About 25 `*ModuleData` tables (4/31, Snapshot slots 1-3 pure).
- `HordeContain`'s interface table (151 of 155 slots pure).
- Every `BehaviorModuleInterface` table of CallHelpOnDamage, ObjectSMCHelper and four other
  classes (47/47 pure).
- The ActiveBody/RespawnBody/OathbreakerBody `BodyModuleInterface` tables (43/43 pure).
- The Apt menu screens (1/14-23 slots).

lk28's 56 slot-1 `loadPostProcess` tables (`behaviormodule-snapshot-slots-20261105-lk28.md`) are a
subset: 372 kept tables have `__purecall` at slot 1.

**Completed (2026-11-05, seat halilkkaya-rt-o1, base e5e17e246f).** 267 slots in 149 kept tables now
equal retail. Each fix declares, in the kept unit's class view, an override that retail's slot word
already names through a matched row of the table's own class. The row is bound by its exact mangled
name; no new names or rows were added.
- da28ffb0a68: DynamicPortalBehaviour slot 1.
- d9e8d212bbd: slots 1/3/4 (`loadPostProcess`/`xfer`/`getModuleNameKey`), 64 tables. This covers
  the five Body tables, AIUpdateInterface, Siege/Transport/GiantBird and the Upgrades.
- 35d01b993d7: any rowed virtual slot of a single-copy table, 79 tables / 156 slots.
- a8a794b1de6: 25 multi-copy classes, edited in every defining unit at once (27 tables / 41 slots).

Totals:
- Referenced `__purecall` slots 3,241 -> 3,098.
- Wrong slots 908 -> 784.
- Equal slots 23,714 -> 23,981.
- T1 tables 852 -> 813.

Every batch:
- byte-matched;
- was accepted only where each changed table gained `eq` slots and nothing else moved (survey A/B);
- kept link_check unchanged over the edited units and every other definer of a changed table.

Lesson: a ctor/dtor pair holds two copies of one table. Changing one copy charges the other under
the census "first" rule (13 siblings, 4,082 B, in the first trial), so both copies change together.

**GetSnapshotName getter slots (2026-11-05, seat halilkkaya-rt-o2, base 8e80cf400b).** Retail
slot 2 of a Snapshot-family table is a 6-byte class-name getter (`mov eax, "Class"; ret`). In 223
kept-table slots (222 in referenced tables; 113 `__purecall`, 93 wrong, 17 unknown) that getter
is rowed under a non-virtual `?name@X@@QBEPBDXZ`. There are 204 getter rows: 159 slots hang off a
placeholder class (`RvaXXXXXXXXNamed`), 64 off a readable class (`?name@DockUpdate@@QBEPBDXZ`).
- Done: 28576b66b9a moves 0x00427603 into CaveSystem (`rename.py function --to-class`). The kept
  `??_7CaveSystem@@6BSnapshot@@@` goes from 3/4 to 4/4 equal retail; its slot 2 was a Zero Hour
  `crc` stand-in. (0x00252B84 DrawableModule had already landed in dcf5bd0a777.)
- Wall 1, readable class (64 slots): `--to-class` moves only a placeholder class's member, and
  `--virtual` keeps the identifier `name`. These rows need an identifier rename to GetSnapshotName
  with a basis first. Examples: TurretAI, AIGuardMachine, Upgrade, MilesAudioManager.
- Wall 2, other slots clash: `--to-class` refuses unless every other resolvable slot of the
  installers' table equals retail. 106 getter tables also hold `__purecall` in slot 1 or 3, so
  those slots (rowed under placeholders or folds) must be fixed in the same move.
- Wall 3, a false reject (re_attempts 0x004B0876): about 66 UpdateModule-family tables name
  `?loadPostProcess@UpdateModule@@MAEXXZ` (0x0058B03E) in slot 1. Retail slot 1 is 0x00497805,
  `jmp 0x0058B03E` (which itself jumps to the `ret` at 0x000B3FD0). That is the same body, but
  the slot check compares addresses without following E9 chains. Reproduced on AIGateUpdate:
  13/13 rows exact, slot 2 named, refused, restored. Fixing it unblocks AIGateUpdate,
  BattlePlanUpdate, BloodthirstyUpdate, CritterEmitterUpdate, FireWeaponUpdate, PoisonedBehavior
  and others.
- Wall 4, an installer without a table: PartTheHeavensUpdate (0x004AC93C; the kept copy is
  otherwise 12/13 equal) is refused because PartTheHeavensUpdateCtor.cpp stores dummies, not a
  `??_7` (see the next item).
- Held at the time (skipped): SubsystemNameGetters.cpp (class claims of yasinschroeder-claude),
  and SubsystemNameGetters2/4.cpp and ModuleNameGetters3.cpp (lk28).

**Walls 3 and 4 repaired (2026-11-05/06, seat halilkkaya-rt-o3).** Two `rename.py --to-class`
slot-check fixes (Verifier-Change, regression tests in `tools/tests/test_rename_to_class.py`):
- Wall 3: another slot no longer clashes when its ledger address and retail's word reach one body
  through a single `jmp rel32` on either side (`same_slot_body`); a chain or a jump to another
  body still refuses (rename.py c7666dba81c).
- An installer unit that only references the class's `??_7` (an extern store, as
  BloodthirstyUpdateCtor.cpp) is passed over; one installer must still compile a matching table
  after ./build.sh (re_attempts 0x0044E000).
- Wall 4 for PartTheHeavensUpdate: its ctor now stores the real tables (below).

Moves landed through it: AIGateUpdate, PoisonedBehavior, FireWeaponUpdate, CritterEmitterUpdate,
RadiateFearUpdate, DetachableRiderUpdate, BloodthirstyUpdate and PartTheHeavensUpdate. Each
`??_7X@@6BObjectModule@@@` gains slot 2 (wrong -> eq). PartTheHeavensUpdate is now 13/13 OK;
the others keep slot 1 `unknown`, because 0x00497805 is a shared fold the survey cannot judge.
Survey: eq 24,195 -> 24,201 over the first six at the old base, with no other table changing.
Linked bytes unchanged in every unit (CritterEmitterUpdate.cpp already did not link before:
`??_7CritterEmitterUpdateModuleData@@6B@` first-copy mismatch).

Still walled (scan of the 77 UpdateModule-family getter tables, `0x00497805` in slot 1):
- ClickReactionBehavior (0x00459573): unblocked, but its class is held by yasinschroeder-codexb5.
- SpecialAbilityUpdate (0x0044F099): slots 3/4 are rowed real overrides too, but it is a canonical
  class (`SpecialAbilityUpdate.h`): define the getter through that header, not a private copy.
- Slot 3 `xfer` under a placeholder (Wall 2): LifetimeUpdate, BuildingBehavior,
  CivilianSpawnUpdate, ShareExperienceBehavior, DelayedWeaponSetUpgradeUpdate,
  SpecialEnemySenseUpdate, SpawnUnitBehavior and WeaponModeSpecialPowerUpdateBase. Declare both
  overrides in the view, then move the xfer and getter rows in one commit.
- About 30 Die/Upgrade/Collide/Body tables still hold `__purecall` in slots 1 and 3 (Wall 2).
- About 33 classes whose only installer is a dummy-vptr ctor or emits no table (Wall 4), e.g.
  StrafeAreaUpdate, HeightDieUpdate, OCLUpdate, RadarUpdate, ToppleUpdate.
- BattlePlanUpdate: slot 8 is `onDelete@Module` where retail names 0x004984CC (rowed as
  `?cleanUp@SpectreGunshipUpdate@@QAEXXZ`, an identity question). DemoTrapUpdate and
  EntEnragedUpdate: Rva0024A797Derived.cpp emits one-slot copies of their tables.

**New obstacle: constructors that install a TU-local dummy as the vptr (found by rt-o2).** 71
matched constructor rows in 71 units, listed in
[dummy-vptr-ctors-20261105.tsv](../../reverse/attempt_support/dummy-vptr-ctors-20261105.tsv)
(`rg -l '&s_vtable\b' Code`, constructor bodies only), store `&s_vtable`, and often
`&s_secondary0C`/`&s_secondary10`, where retail stores the class's `??_7` tables. These are
`static int`s in the unit. DIR32 is masked, so the bytes match; the static resolves locally, so
the unit links. But the built object's vptr points at a zero int.
- Leaf classes crash at their first virtual call. Examples: ObjectDefectionHelper,
  ObjectRecoveryHelper, ObjectRepulsorHelper and ObjectWeaponStatusHelper (in Zero Hour, a donor
  fact, every Object creates its helpers), StructureBody, the crate collides, and many update,
  upgrade and special-power modules.
- In a base constructor (ObjectHelper, DamageModule) the dummy is live only until the derived
  constructor's own store.
- The table survey cannot see this, because it judges `??_7` copies, not installers.
- Fix: write the constructor against the class view that emits the real table (often the class's
  TU seed), then re-run the survey and link_check.
- DamageModule (lk33, 2026-11-05; trial reverted, not landed):
  - DamageModuleCtor.cpp on canonical DamageModuleClass.h is byte-exact (1/1). It emits the real
    tables:
    - 0x00C598E4: 10/12 retail-equal;
    - 0x00C597F8: 43/47;
    - 0x00BE2B78: 3/3.

    No slot is wrong. The rest are unrowed inline bodies and the canonical header's `??_E` in slot 0.
    Before, the unit emitted none, and the survey at f0f6176eead keeps no `??_7DamageModule` table
    anywhere.
  - Refused by link_check: LINKS 49 B -> does not link. The `??_E` calls `??1DamageModule@@UAE@XZ`,
    whose only definer is the wrong COMDAT in EvacuateDamageCtorModuleFactoryBody.cpp.
  - It lands only with the `~DamageModule` identity fold. See the GameLogic real-link entry and
    [damagemodule-dtor-identity-20261105-lk33.md](../../reverse/attempt_support/damagemodule-dtor-identity-20261105-lk33.md).
- Done (seat halilkkaya-rt-o3): PartTheHeavensUpdate, AISpecialPowerUpdate,
  GiveOrRestoreUpgradeSpecialPower, DoCommandUpgrade and AllowBannerSpawnUpgrade. Where one unit
  (the class's dtor unit) defines every table the ctor installs, the ctor stores them by exact
  mangled name (extern `__identifier`, the BloodthirstyUpdateCtor.cpp pattern). Codegen is
  unchanged; each DIR32 now targets the real table. Map each displacement to its table through
  the retail store immediate and the kept copy at that VA, never by member name alone.
  Verified: bytes exact, scoped DIR32 OK, link_check LINKS on the ctor and the definer.
- Done (seat halilkkaya-rt-o4, base e44e2c5ef6c), the same pattern: RadarMarkerClientUpdate,
  TerrainResourceClientBehavior, ShipSlowDeathBehavior, FakePathfindPortalBehaviour,
  RebuildHoleBehavior, Horse/ProductionQueue/SlaughterHordeContain, DeployStyleAIUpdate,
  MonsterDockUpdate, CommandPointsUpgrade, ObjectCreationUpgrade and SiegeDeployHordeSpecialPower.
  Then five ctors that store a slot twice (an inlined base ctor writes a folded interface table
  first, the derived ctor overwrites it): DynamicPortalBehaviour, ModelConditionAudioLoopClientBehavior,
  CaveContain, DamageFilteredCreateObjectDie and AnimalAIUpdate. Their final stores now name the
  class's tables; the transient first store stays a TU-local dummy. That is safe at run time: the
  decoded store (base register, displacement) is overwritten with only plain stores in between, and
  naming one of the many classes folded at 0x00BE2B78/0x00C1C780/0x00C4EF80/0x00C6FFFC would be a
  guess. WargBehavior and BuildableHeroListUpgrade had already been fixed by their TU merges.
  Verified per batch: bytes exact; each new DIR32 target's retail imm32 equals the planned table VA;
  scoped DIR32 OK over the ctors and definers; link_check current A/B over every unit naming the
  class unchanged; survey unchanged (0 tables differ). Most of these kept tables are still 1-slot
  placeholder views, so the class family's header is the next step for them; the vptrs no longer
  need touching then.
- Mapping script (reusable): for each `_s_*` DIR32 site in the ctor's current object, read the
  retail imm32 at the site's offset, take the one `??_7<Class>@@...` the survey keeps at that VA, and
  count its definers over the current objects of every unit naming the class (the census index is
  stale for merged units). Read the ctor's source path from `reverse/functions.csv`, not the TSV:
  a stale object of a deleted unit still answers.
- Status of all 71 is in the TSV's `status` column: 25 fixed, 1 blocked, 7 need a class view, 38
  need an identity first.
  - Blocked: CastleMemberBehavior. Its ctor unit's view of the class is polymorphic (novtable,
    virtual `xfer`), so the compiler owns `??_7CastleMemberBehavior@@6B@` there and the extern
    declaration fails with C2373. It needs CastleMemberBehavior.cpp's view (re_attempts 0x00395B66).
  - Needs a class view (no kept table at the stored VA): AnnounceBirthAndDeathBehavior,
    CitadelSlaughterHordeContain, RiderChangeContain, EvaAnnounceClientCreate, DamageModule and
    ReplaceSelfUpgrade. FXListDieModuleData's 0x00C4ED70 is a ModuleData table folded across 12
    classes and kept under their names.
  - Needs an identity first (38): the class's retail table is kept only under a placeholder
    class's name, emitted by a scaffold unit (`Rva...Derived.cpp`). The highest risk is the
    ObjectHelper family, which every Object builds: `??1Rva004DF7C2@@UAE@XZ` (0x004DF7C2),
    `??1Rva004DF52E`, `??1Rva004DF836`, `??1Rva004DF863` and `??1Rva004DF8A9` install
    0x00BFBCF0/0x00BFBD40/0x00BFBD98/0x00BFBDF0/0x00BFBE48. Those are the very tables the
    ObjectHelper, ObjectDefectionHelper, ObjectRecoveryHelper, ObjectRepulsorHelper and
    ObjectWeaponStatusHelper ctors install last. That is a target fact (the same vptr store at +0,
    five distinct addresses); that they are those classes' destructors is the inference. Rename the
    placeholder classes through the naming lane (`docs/naming.md`), then the ctors can store the
    tables by name. The other placeholder owners (StructureBody -> Rva004C0988, the five
    CrateCollides -> Rva004BC83F/96F/CB0D/CC43/CE62, SquishCollide -> Rva004BB949,
    HordeMemberCollide -> Rva004BC325, and so on) are listed per row in the TSV.
- Identity conflict found on the way (target facts, both rows matched): OCLUpdate's ctor
  (0x0049B381, proven by its pool key and factory) installs 0x00C50B40 at +0, the table that
  `??1Rva0049B2A2@@UAE@XZ` (0x0049B2A2) installs, and `?xfer@Rva0049B2A2` sits in OCLUpdate.cpp.
  But `??1OCLUpdate@@UAE@XZ` is rowed at 0x004CD3DB (ModuleUpdateDtors.cpp, named from factory
  stub order), which installs 0x00C5FB40, so the kept `??_7OCLUpdate@@6B@` carries the other
  table's address. One of the two dtor names is wrong; settle it in the naming lane before OCLUpdate's
  ctor stores a table.
- Beyond the TSV, 21 more units store `static` dummies as vptrs (any `s_dummy*`/`s_secondary*`/
  `s_vt*` name, not just `&s_vtable`). Constructors with dummy secondary vptrs (+0x0C/+0x10/+0x20,
  the BehaviorModuleInterface and module-interface subobjects that Object code calls through):
  BoredUpdate, StealthDetectorUpdate, RampageBehavior, EnragedBehavior, AssistedTargetingUpdate,
  Rva004DF418, and the special powers TeleportToCaster, Curse, EvacuateGarrison, ActivateModule,
  Unleash, HordeDispatch and DominateEnemy, plus Rva00490D3F/Rva00492179/Rva00492402/Rva00492C59/
  Rva00494DCA, and ToggleMountedSpecialAbilityUpdateModuleData's primary vptr. Destructors
  with dummies: 14 in ModuleUpdateDtors.cpp, and those of RampageBehavior,
  BoredUpdate and StealthDetectorUpdate. None has a class-owned kept table at its stored VAs (most
  are the folded 0x00BEFF90/0x00C4D640/0x00C4DEE8 tables or have no kept copy), so all need class
  views. The FXParticleSystem module creators in Rva003AC9AFCreate.cpp also store dummies (left to
  the FXParticleSystem seat).
- Separately, 154 retail table addresses are reached from matched code through a non-`??_7`
  symbol: address-named globals such as `?g_00C50868@@3QBQBXB` and `?vftable_0112B89C@@3HA`
  (`name_globals.load_index()` against retail-installed tables). Whether each is aliased to the
  real table at link time is not checked here.

Rejected and left for header work:
- Declarations that append a slot because the view's base lacks it: the Apt screens, group
  orders, mice, GameSpyInfo, TaintManager, SpecialPowerModule's multi-copy group, StateMachine,
  Weapon, the siege-engine contains, ObjectSMCHelper and others. They need the family's canonical
  base header first.
- Slots whose retail body is rowed under a non-virtual name (`?name@C@@QBEPBDXZ`, the BFME2
  GetSnapshotName getters), or under another class's or a placeholder's name. Both need
  naming-lane renames before a declaration can bind them (getter walls: the rt-o2 pass above).
- Short tables (40,230 missing slots), which need full class views.
- Deleting-destructor scaffolds. 60 units use the `EmitVtableTag` pattern: a dummy constructor
  makes a view with only a virtual destructor emit its table, so the unit emits the `??_G`
  wrapper. These units sit early in link order, so their one-slot tables become the kept copy.
  The kept tables they hold (at e5e17e246f plus the passes above):
  - 228 at risk (T1 28, T2 47, T4 152);
  - 196 of them one slot long;
  - 137 with a longer copy elsewhere.
  Example: SpecialPowerModuleDeletingDtors.cpp keeps the 1-slot
  `??_7{Devastate,OCL,PlayerUpgrade,Invisibility,ProductionSpeedBonus}...ModuleData@@6B@`. The
  family units' 31-slot copies (built on SpecialPowerModuleData.h/ModuleData.h) are discarded.
  The fix is to give the scaffold class the same base view as its family unit, so every copy is
  identical. The scaffold's ModuleData inline-virtual COMDATs then join every copy of that header,
  so check all their definers with link_check.
  Done in 4d44fb30c14 and 273e5d13f1f: six tables, the five SpecialPower ModuleData classes and
  GeometryUpgradeModuleData, went from 1 to 31 slots (30 equal retail). Each scaffold copy is
  digest-identical to its family copy, and link_check A/B over every co-definer is unchanged.
  Only five kept short tables had a full-length copy elsewhere. The other scaffold tables' family
  units are short too (e.g. every ContainModuleData copy is one slot), so those need the family
  header first.

**Remaining / next check.** A table moves to retail only through its class family's own view:
adopt the canonical class header (`header_adopt_lane.py`), or declare the family's override where
its body is already rowed. A placeholder table kept from a destructor-only unit needs the same view
as the class's constructor unit. Re-run the survey script on the affected units before and after
each change: every changed table must move toward retail slot by slot, with `link_check` showing no
LINKS→not-linking.

Clearance: none claimed; measurement only, no census rule changed.
Census confirmation: none claimed.

2026-11-06 AssistedTargetingUpdate scoped follow-up: constructor dummy arrays
are replaced by compiler-owned native13/47/3 tables (63/63 slots checked).
Canonical0x20 UpdateModule view removes the old CRC table dependency; ctor is
merged into the approved TU,10/10 rows and2 EXACT EH graphs retained. Lifetime
source still awaits a guard-approved split; no actual image/runtime clearance
claimed. [Proof and remaining prerequisites](../../reverse/attempt_support/assisted-native-profile-20261106/README.md).

**ObjectHelper family: shared header and the first helper (2026-11-07, seat halilkkaya-lk41, base
`4b2bb61eb1d`).** `Code/GameEngine/Include/GameLogic/Module/ObjectHelper.h` is the canonical
ObjectHelper over canonical `UpdateModule.h`, written from retail's tables: ObjectHelper installs
UpdateModule's two interface tables unchanged (0x00BEFF90/+0x0C, 0x00BFBCE4/+0x10) and overrides
slots 0-3 of its primary 0x00BFBCF0. It declares the constructor, the virtual destructor and
`loadPostProcess`; `GetSnapshotName` and `xfer` wait for their placeholder rows (below).
- ObjectDefectionHelperCtor.cpp adopts it. Its constructor (0x0028C955, still 61/61 exact) now lets the
  compiler store `??_7ObjectDefectionHelper@@6BObjectModule@@@`, `...6BBehaviorModuleInterface@@@` and
  `...6B@` where it stored three TU-local zero ints. Survey on the current objects: 13/13, 47/47 and 2/3
  slots equal retail (0x00BFBD40, 0x00BEFF90, 0x00BFBD34).
- Names given on the way (each byte-verified): ICF twins `?loadPostProcess@ObjectHelper@@MAEXXZ` at
  0x00497805 (in Rva004DF81BXfer.cpp, ObjectHelper's xfer unit) and
  `?loadPostProcess@ObjectDefectionHelper@@MAEXXZ` at 0x00483CEF (`jmp 0x00497805`); the two must sit in
  different units or MSVC inlines the base. `--to-class` moved 0x0028C9D7 to
  `?GetSnapshotName@ObjectDefectionHelper@@MBEPBDXZ`; `class --fold Rva004DF52E --into
  ObjectDefectionHelper` named the destructor 0x004DF52E and deleting destructor 0x0028C9DD.
- link_check: ObjectDefectionHelperCtor.cpp LINKS 61 -> 66 B, Rva004DF81BXfer.cpp 27 -> 32 B; the
  dtor, getter, xfer/update, pool-key units and the fold owners are unchanged (AssistedTargetingUpdate.cpp,
  another 0x00497805 twin, needs its post-census providers rebuilt to show LINKS).
- Left wrong: slot 1 of 0x00BFBD34 is UpdateModule's `getDisabledTypesToProcess` (DISABLEDMASK_NONE);
  retail's 0x004DF396 returns DISABLEDMASK_ALL and is an ICF fold of 8 tables
  (`Rva004DF396`, UpdateModuleSetWakeFrame.cpp). It needs an ICF twin under this class with a BitFlags<11>
  view. The defection helper then does not update while its Object is disabled.

- ObjectRepulsorHelper (0x0028CAB4) followed the same recipe the same day: ctor unit on ObjectHelper.h,
  ICF twins `?loadPostProcess@ObjectRepulsorHelper@@MAEXXZ` (0x00483CEF) and
  `?xfer@ObjectRepulsorHelper@@MAEXPAVXfer@@@Z` (0x004DF87C, calling ObjectHelper's xfer through its
  placeholder spelling `Rva004DF81B`), `--to-class` for the getter 0x0028CB23 (Object.cpp) and `update`
  0x004DF897 (VslotSmallBodiesU.cpp), and the fold of `Rva004DF863`. Its three tables are 11/13, 3/3 and
  45/47 by address; every other slot is an inline body of the same shape (`??_E`, `ret`,
  `xor eax,eax; ret`). link_check: 13 of 13 checked units LINK, the ctor unit 42 -> 74 B.

Next, in this order (each a wall found this pass):
1. ObjectRecoveryHelper and ObjectWeaponStatusHelper: their constructors (0x0028C9F9, 0x0028CB45) have EH
   frames whose unwind calls `~ObjectHelper`, so they adopt the header only together with step 3.
2. ObjectHelper's own names: `GetSnapshotName` 0x0028C933 is the scaffold `?Rva0028C933Get@@YAHXZ`
   (ConstIntGetters4.cpp, no approved TU); `xfer` 0x004DF81B is `Rva004DF81B` but also carries the ICF twin
   `?xfer@AssistedTargetingUpdate@@MAEXPAVXfer@@@Z`, so `--to-class` refuses it as a shared body.
3. `~ObjectHelper` (0x004DF7C2, `Rva004DF7C2`): the fold needs ObjectHelper's own table named, i.e.
   Object.cpp's ctor (0x0028C8DF) on the header, and Object.cpp's private `UpdateModule` view goes. Three
   units declare both `Rva004DF7C2` and a private `ObjectHelper` (ObjectRecoveryHelperCtor.cpp,
   ObjectWeaponStatusHelperCtor.cpp, ObjectSMCHelper_Rva002927f8.cpp), so the token fold refuses them;
   either register ObjectHelper (then fold with those units `--prepared` on the header) or reconcile them
   first. Recovery's and WeaponStatus's constructors have EH frames whose unwind calls `~ObjectHelper`,
   so they adopt the header only together with this fold.

**ObjectHelper family finished (2026-11-07, seat halilkkaya-lk43, base `e1e03be955`).** Steps 1-3 above are
done; every helper constructor now lets the compiler store its class's real tables over ObjectHelper.h.
Slot counts are against retail by address, "+ inline" meaning bodies of retail's shape with no address of
their own (`??_E` resolving to the rowed `??_G`, slot 5's `ret`, `xor eax,eax; ret`):

| ctor (unit) | primary | BehaviorModuleInterface | UpdateModuleInterface | before |
|---|---|---|---|---|
| ObjectHelper 0x0028C8DF (Object.cpp) | 10/13 + 2 inline | 45/47 + 2 inline | 3/3 | three zero ints, no `??_7ObjectHelper` anywhere |
| ObjectRecoveryHelper 0x0028C9F9 | 11/13 + 2 inline | 45/47 + 2 inline | 3/3 | three zero ints |
| ObjectWeaponStatusHelper 0x0028CB45 | 10/13 + 2 inline | 45/47 + 2 inline | 2/3 | three zero ints |
| ObjectSMCHelper 0x002927F8 | 10/13 + 2 inline | 45/47 + 2 inline | 2/3 | stand-in tables: 4-slot primary, 47/47 and 3/3 `__purecall` |

- Object.cpp drops its private UpdateModule/ObjectHelper view, includes ObjectHelper.h after BehaviorModule.h
  and defines `BFME_SNAPSHOT_NAME_SLOT` first, so UpdateModule's slot 2 is GetSnapshotName (rowed), not Zero
  Hour's `crc` (no definer). An object diff shows no other change; the unwind now names `??1UpdateModule@@UAE@XZ`.
- Folds: `Rva004DF7C2` -> ObjectHelper (once Object.cpp named 0x00BFBCF0 and the three dual-declaring units
  used the header), `Rva004DF836` -> ObjectRecoveryHelper, `Rva004DF8A9` -> ObjectWeaponStatusHelper. Every
  pair of `??_G` copies (ctor unit vs scaffold) is byte- and relocation-identical.
- ICF twins (add_match `--icf-owner`): `loadPostProcess` 0x00483CEF for Recovery, WeaponStatus and SMC;
  `xfer` 0x004DF87C for Recovery and WeaponStatus; ObjectWeaponStatusHelper's `getUpdatePhase` 0x0044827C
  (`push 3; pop eax; ret`, slot 12, folded by retail with ATL's `_AtlGetThreadACPReal`); and ObjectHelper's
  `xfer` 0x004DF81B (fold-proof Rva004DF81BXfer.cpp), now declared in ObjectHelper.h.
- `--to-class`: 0x0028CA92 -> `?GetSnapshotName@ObjectRecoveryHelper@@MBEPBDXZ` (Object.cpp) and 0x004DF8C2 ->
  `?getDisabledTypesToProcess@ObjectWeaponStatusHelper@@...` (VslotSmallBodiesAC.cpp).
- link_check over 33 family, scaffold, provider and twin-owner units: 33 of 33 LINK; Recovery ctor 94 -> 126 B,
  WeaponStatus ctor 81 -> 117 B, SMC ctor 81 -> 86 B, Object.cpp 7,026 B unchanged. Include the post-census
  `ObjectSMCHelper_Rva002927f8.cpp` object whenever `Rva0024A797Derived.cpp` is checked: the census copy still
  defines the old inline `~ObjectHelper` and fakes a `??1ObjectHelper@@UAE@XZ` duplicate.

Still open in the family:
- ObjectHelper slot 2, 0x0028C933: rowed as the free-function scaffold `?Rva0028C933Get@@YAHXZ`
  (ConstIntGetters4.cpp, no approved TU). `--to-class` moves only a placeholder class's member and
  `--replace-rva` only gen scaffolding, so no supported move exists (re_attempts 0x0028C933).
- ObjectWeaponStatusHelper `update`, 0x0028F976 (+0x10 slot 0, now `__purecall`): rowed
  `?update@Rva0028F976@@UAEHXZ` with a guessed int return; `--to-class` keeps the return type, and C++ forbids
  an int override of UpdateModuleInterface::update. False reject recorded (re_attempts 0x0028F976). The
  prepared VslotSmallBodiesAM.cpp view is the existing class body with `UpdateSleepTime` for `Int`.
- Getters in SubsystemNameGetters2.cpp (WeaponStatus 0x0028CBDB, SMC 0x0029288E, the latter spelled as the
  non-virtual `?name@ObjectSMCHelper@@QBEPBDXZ`) and the DISABLEDMASK_ALL fold 0x004DF396 (Defection and SMC
  slot 1 of +0x10, owner UpdateModuleSetWakeFrame.cpp): their units sit under another seat's
  `class:UpdateModule` claim.
- The seventh helper, ObjectGuardingHelper (Object's `ModuleTag_GuardingHelper`, its pool-key getter
  0x004DF351 is already `?getModuleNameKey@ObjectGuardingHelper@@...`): ctor 0x004DF418 is rowed
  `??0Rva004DF418` (Rva004DF418Finish.cpp) and dtor 0x004DF324 `??1Rva004DF324`, two different placeholders.
  The ctor stores the dtor unit's one-slot `??_7Rva004DF324@@6B@` at +0, a zero int at +0x0C and a three-entry
  `extern "C"` array at +0x10. No tool path names it yet: `class --fold` needs T (0x00C61588) already named by
  NEW and refuses a placeholder NEW, and a plain class rename collides with the rowed getModuleNameKey.
  Its unwind spelled `~ObjectHelper` non-virtual (`??1ObjectHelper@@QAE@XZ`), which linked only through the
  old Recovery/WeaponStatus units' inline copies; Rva004DF418Finish.cpp now declares the views' destructors
  virtual and keeps today's three stores (novtable class), so it still LINKS 122 B. That is containment, not
  the fix: the class's own tables wait for the identity above.

**Dummy-vptr ctors over UpdateModule.h (2026-11-07, seat halilkkaya-lk43).** The same recipe works for a
module that derives from UpdateModule directly, with no helper header: declare the class over the
canonical UpdateModule.h in its ctor unit, move the name getter with `--to-class` (the
ModuleNameGetters3.cpp line becomes its `BFME_SNAPSHOT_NAME_GETTER` form), fold the destructor placeholder
from Rva0024A797Derived.cpp, and leave `loadPostProcess` to UpdateModule when retail's slot 1 is 0x00497805
(`jmp 0x0058B03E`, the same body).
- HeightDieUpdate 0x0048FCB2: `Rva0048FBBA` folded; tables 11/13 + 2 equivalent, 45/47 + 2 inline, 3/3.
- AutoDepositUpdate 0x0049A20F: `Rva0049A1AB` folded; slot 3 0x004A0CC3 is a retail fold with
  RadarUpdate::xfer (same +0x20 uint and +0x24/+0x25 bools), rowed as a twin; tables as HeightDieUpdate's.
- link_check: HeightDieUpdateCtor.cpp 77 B and AutoDepositUpdateCtor.cpp 68 -> 144 B LINK, with their
  update, getter, factory and scaffold units unchanged.
- Walled in the same family: AutoFindHealingUpdate (its update 0x0049520B is rowed non-virtual with an
  int return, the 0x0028F976 false reject) and HijackerUpdate (getModuleNameKey 0x004A4010 is rowed as a
  static member). OCLUpdate keeps its dtor identity conflict (above).
- WeaponBonusUpgrade 0x004B5633 (UpgradeModule family, its approved TU WeaponBonusUpgrade.cpp): the
  novtable WeaponBonusUpgradeView.h is gone; a shared `Code/GameEngine/Include/GameLogic/Module/WeaponBonusUpgrade.h`
  declares the class over UpgradeModule.h (UpgradeMux slot 8 is retail's shared empty body, an inline empty
  override). Slot 3 0x004B8710 is a twin of ArmorUpgrade::xfer. Folding `Rva004B55C8` needed one more step:
  its scaffold (FireWeaponWhenDeadBehaviorDerived.cpp) derives from canonical UpgradeModule, so the token fold
  made it emit dtor-only `??_7WeaponBonusUpgrade@@6BObjectModule@@@`-named tables (slots 2-4 and UpgradeMux
  8/10 base or `__purecall`) earlier in link order than the real ones. In the fold commit the scaffold
  includes the shared header instead; every copy is now byte-identical. Check any fold whose scaffold
  derives from a canonical base the same way (`rename.py` takes `--prepared` only for a registered NEW).
- InheritUpgradeCreate 0x004B9428 (CreateModule family, approved TU InheritUpgradeCreate.cpp): the class was
  `__declspec(novtable)` over canonical CreateModuleClass.h with explicit dummy stores. Dropping novtable
  needed `BFME_SNAPSHOT_NAME_SLOT` first: in crc mode CreateModuleClass.h's GetSnapshotName became a 13th slot
  behind a pure `crc` in slot 2 (check any unit that includes Snapshot.h before a canonical module header).
  onCreate is retail's shared empty body (inline override); slot02 0x004B96C4 moved by `--to-class` into a
  two-base view in GapBodiesS9B.cpp; `Rva004B9458` folded. Its getter 0x004B9452 is, like ObjectHelper's, a
  free-function scaffold (`?Rva004B9452Get@@YAHXZ`), so slot 2 stays CreateModule's.
- Walled (tried and reverted): StructureBody 0x004C0951 on ActiveBody.h compiles exact and emits real-length
  tables, but ActiveBody.h's body-interface and primary slots name 34 members (getHealth, getMaxHealth,
  getDamageState, vslot14/17/21, ...) whose bodies are rowed under placeholder or field-getter classes; the
  unit would go from LINKS 49 B to unresolved on all 34. Every ActiveBody subclass ctor (SymbioticStructuresBody,
  the RespawnBody family) waits for those rows to move into ActiveBody (`--to-class`, one slot each).
- Not attempted, same reason class: the SpecialPowerModule family (PlayerHeal, UntamedAllegiance: a 24-slot
  interface table with ten placeholder rows and a free-function getter scaffold), the SpecialAbilityUpdate
  family (its ctor is still `??0Rva0044EF5E`), and the CrateCollide/CollideModule and DockUpdate families
  (no shared header yet).

