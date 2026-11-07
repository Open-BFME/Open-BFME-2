### LINK-514: kept `??_7` copies differ from retail's vftables (runtime vtable survey)
Status: Open (partly repaired). Updated: 2026-11-07 (lk56 pass at 2f3e43c2c1; lk53 pass at 26715f1e00); inspected revision: e5e17e246f, getter and installer passes at be366d041e, dummy-vptr ctor pass at e44e2c5ef6c, ObjectHelper family at e1e03be955 (census index c95fcfcfcd; f44cbcf5b0 for the ctor pass; 94d8ffa1ad for the family).
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
- CLEARED 2026-11-07 (seat halilkkaya-lk50, base cdb102e40d): ObjectWeaponStatusHelper `update`, 0x0028F976
  (+0x10 slot 0, was `__purecall`). It was rowed `?update@Rva0028F976@@UAEHXZ` with a guessed int return,
  and C++ forbids an int override of UpdateModuleInterface::update. The tooling fix f4fe1d2f893 lets
  `--to-class` take a registered header's enum return (UpdateModule.h declares `virtual UpdateSleepTime
  update()`). It also passes over the destructor scaffold Rva004DF7C2Derived.cpp, whose one-slot stand-in
  tables (`6BRva004DF8A9_B2`, `6BMiBase1`, `6BObjectHelper`) resolve nothing. The row is now
  `?update@ObjectWeaponStatusHelper@@UAE?AW4UpdateSleepTime@@XZ` (VslotSmallBodiesAM.cpp; the class
  declares it in ObjectWeaponStatusHelperCtor.cpp). Evidence: 134/134 exact; the only `??_7` change is
  ObjectWeaponStatusHelperCtor.obj's `??_7ObjectWeaponStatusHelper@@6B@` slot 0 `__purecall` -> update (now
  3/3 with retail 0x00BFBE3C); scoped DIR32 OK; link_check over ObjectWeaponStatusHelperCtor.cpp,
  VslotSmallBodiesAM.cpp, Rva004DF7C2Derived.cpp, Object.cpp and VslotSmallBodiesAC.cpp: 5/5 LINK, 7,729 B
  unchanged. Census confirmation: not claimed.
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
- Walled in the same family: HijackerUpdate (getModuleNameKey 0x004A4010 is rowed as a static member).
  OCLUpdate keeps its dtor identity conflict (above).
- AutoFindHealingUpdate 0x00495139 (2026-11-07, seat halilkkaya-lk50; was walled by the int-return false
  reject on its update 0x0049520B, cleared by the tooling fix f4fe1d2f893). The same recipe in three
  commits: fe5e228b2fe declares the class over UpdateModule.h in its ctor unit; a3516e6ebcc folds
  `Rva0049506E` (dtor 0x0049506E, `??_G` 0x00495167, xfer 0x0049508D); the update move respells
  `?update@Rva0049520B@@QAEHXZ` as `?update@AutoFindHealingUpdate@@UAE?AW4UpdateSleepTime@@XZ`. Its body
  (Rva0049520BGate.cpp) now reads getObject(), getModuleData() and the +0x20 counter from the complete
  object. Tables against retail by address: 0x00C4EC04 3/3; 0x00BEFF90 45/47 + 2 inline; 0x00C4EC10 9/13
  (slot 1 the jmp-equivalent base body, slot 5 the inline `ret`, slot 0 the unit's own `??_E`). Slot 2 is
  still UpdateModule's getter: 0x00495087 (`Rva00495087Named`) sits in ModuleNameGetters3.cpp, which
  Burachi-3D held (class:ArrowStormUpdate claim). Evidence: 62/62 exact; scoped DIR32 OK; link_check over
  the ctor unit, Rva0024A797Derived.cpp, Rva0049508DXfer.cpp, Rva0049520BGate.cpp,
  AutoFindHealingUpdateFriendNew.cpp, AutoFindHealingUpdate.cpp and ModuleFactory.cpp: 7/7 LINK, 4,532 B
  unchanged. Census confirmation: not claimed.
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


**ActiveBody's 36 unrowed slots, and the collide family's base header (2026-11-07, seat halilkkaya-lk47,
base `fd6d5a2132`).**

ActiveBody inventory. Compiled against retail by address, ActiveBody.h names 36 slots that no row spells
under ActiveBody (lk43 counted 34). By kind:

| kind | slots (primary 0x00C5B038 / body interface 0x00C5B5B0) | path |
|---|---|---|
| placeholder member in ActiveBody's own range | p1 0x004BF40F, p14 0x004BF8AC, p16 0x004BF8ED; b3 0x004BDB25, b5 0x004BDC25, b10 0x004BDCE2, b23 0x004BDB37, b24 0x004BF8BE, b25 0x004BF8CB, b29 0x004BDC48, b30 0x004BDC4F, b34 0x004BF8D8, b35 0x004BDC41, b36 0x004BDC03, b41 0x004BF893 | `--to-class ActiveBody`, walled (below) |
| non-virtual spelling | p17 validateArmorAndDamageFX 0x004BE1AE, p21 setCorrectDamageState 0x004BE8BD | `function --virtual` (dry run passes); only the ctor calls them directly (devirtualized) |
| ICF fold with unrelated bodies | b4 0x004F5F92, b6 0x005D870D, b7 0x00094A94, b8 0x0030D377, b15 0x00314046, b16 0x0023CAD2, b17 0x005BE1A7, b19 0x0052BAAB, b42 0x00101CBE | inline bodies or `--icf-owner` twins |
| BodyModule's own slot, redeclared by ActiveBody.h | b26 0x004BD77C, b27 0x00452D82, b37/b39 0x0047A69C, b38 0x005CB9FA, b40 0x0050B238 (BodyModule's table 0x00C5AC18 holds the same words) | declare in BodyModuleClass.h, drop from ActiveBody.h |
| wall | p2 `?name@ActiveBody@@QBEPBDXZ` (readable class, Wall 1); p15 0x004BF8DF (int-return placeholder, false reject); p20 0x004BE3EF rowed `W3DModelDraw::stopClientParticleSystems`; b28 0x004BE67E rowed `DetachableRiderBody::Rva004BE67E` | naming lane / tooling |

Why the `--to-class` moves cannot start (re_attempts 0x004BDB25):
- The slot check needs an ActiveBody installer that compiles ActiveBody.h. Both installers use private views:
  ActiveBodyConstructor.cpp (ctor 0x004BF6A1, its kept 12-slot primary and 43-slot body table) and
  BodyModuleDeletingDtors.cpp (dtor 0x004BF951, one-slot tables). ActiveBody.h cannot compile the ctor yet:
  +0xE0 is `void *` x3 where the ctor builds a vector (0x00211E58, assigned through 0x004BF4CE, 12-byte
  elements), and +0xF0 is a plain uint where the ctor runs BitFlags<11>'s ctor (0x003B31AD). Ten of the
  twelve ActiveBody.h includers build without STLport.
- The body is also judged folded: DelayedDeathBody (0x00C5BB38), FreeLifeBody (0x00C5BD88) and
  DetachableRiderBody (0x00C5BF48) tables hold it, and their installers' views do not derive from ActiveBody.
- The four walls would leave any ActiveBody.h table unresolved even after every other move.
  re_attempts: 0x004BF8DF and 0x0049520B (int vs enum return: false reject, the 0x0028F976 wall; the
  tool part is cleared by f4fe1d2f893, and 0x0049520B moved; 0x004BF8DF's dry run now stops on the folded-body
  wall above, its DelayedDeathBody/FreeLifeBody/DetachableRiderBody tables),
  0x004BE3EF and 0x004BE67E (readable wrong class: retail references both only from Body-family tables).
StructureBody (and every ActiveBody subclass ctor) stays on its dummy vptrs until those clear.

CollideModule.h (new, `Code/GameEngine/Include/GameLogic/Module/CollideModule.h`): CollideModuleInterface's six
slots and CollideModule's defaults, written from retail (ctor 0x004BB702: 0x00C5A130/+0, 0x00C5A040/+0x0C,
0x00C5A00C/+0x10). getCollide returns this (0x002533D3's 13 bytes), the five predicates return false
(0x005CB9FF / 0x0047A699 shapes). Slot 5 is named isSalvageCrateCollide (SalvageCrateCollide's 0x00C5A9A8
overrides it with `mov al,1; ret`); slots 2-4 stay neutral, because BFME2 has six slots to Zero Hour's seven.
CollideModule's loadPostProcess (0x0058B03E) and xfer (0x004CE56D) are rowed as ICF twins in the new
CollideModule.cpp (Zero Hour's file for exactly those two); its GetSnapshotName 0x004BB733 is a free-function
scaffold, so it is not declared.

SquishCollide 0x004BB9CF (infantry crush collide), the first ctor on it:

| table | retail | after | before |
|---|---|---|---|
| primary | 0x00C5A204 | 9/12 equal + slots 0/5 inline + slot 1 one jmp (CollideModule's 0x0058B03E for retail's 0x00497805) | zero int |
| BehaviorModuleInterface | 0x00C5A040 | 44/47 equal + 3 inline (getCollide byte-equal to 0x002533D3) | zero int |
| CollideModuleInterface | 0x00C5A1EC | onCollide equal + 5 inline, byte-equal to 0x005CB9FF/0x0047A699 | zero int |

- `?xfer@SquishCollide@@MAEXPAVXfer@@@Z`: ICF twin at 0x0045CE8C (BoneFXDamage::xfer's body; owner
  `?xfer@Rva0045CE8C`). Getter: `--to-class` 0x004BB962. Destructor: `class --fold Rva004BB949`; the scaffold
  Rva004BB68EDerived.cpp keeps its placeholder bases, so its one-slot tables take names no ctor table uses.
- link_check: Rva004BB68EDerived.cpp 212 B, SquishCollide.cpp 1,247 B, ModuleNameGetters3.cpp 605 B,
  ModuleFactory.cpp 2,404 B, FireWeaponCollide.cpp, Rva0049B47CThreeVptrDerived.cpp, Rva0045CE8CXfer.cpp,
  Rva004CE56DXfer.cpp, DamageModule.cpp, BoneFXDamage.cpp and UpdateModuleLoadPostProcess.cpp all LINK.
  SquishCollideCtor.cpp (42 B before) lists only `?loadPostProcess@CollideModule@@MAEXXZ` and
  `?xfer@CollideModule@@MAEXPAVXfer@@@Z` unresolved: CollideModule.cpp defines both, but link_check previews
  only census units, so the next census confirms it.

Still walled in the collide family:
- HordeMemberCollide 0x004BC389: its onCollide row spells `class Coord3D` (`PBVCoord3D`), CollideModule.h
  the canonical `struct Coord3D`: LINK-018.
- CivilianSpawnCollide 0x004BD694: onCollide 0x004BD6DA is rowed `?bfmeGo1026F@BfmeF1026@@QAEXHHH@Z` (three
  ints), which `--to-class` cannot respell.
- The five crates: CrateCollide.cpp's private CollideModule (one-slot interface) has to go first.
  CrateCollide's collide slot 1 0x004BC51B (`add ecx,-0x10; mov eax,[ecx]; jmp [eax+0x34]`, the forward to
  isValidToExecute) is rowed `?forward@Rva004BC51B@@UAEXXZ` (no argument), and each crate's name getter is a
  free-function scaffold.
- FireWeaponCollide.cpp, CollideModule's approved TU, compiles a capitalized Snapshot (BuffManager.h first),
  so it cannot adopt CollideModule.h without reordering that TU.

**Walled rows re-tried with the extended rename.py, and a Drawable.h slot regression (2026-11-07, seat
halilkkaya-lk53, base `26715f1e00`).**

Regression repaired (our account's): 902bae9dc22 (Include Drawable.h in 48 units retail built with its flash
constant) put the include after each unit's first include. Drawable.h defines `BFME_SNAPSHOT_NAME_SLOT` and
`BFME_SNAPSHOT_CAPITALIZED_SLOTS` before reading Snapshot.h, so in eight module units Snapshot was read with
`LoadPostProcess`/`DoXfer` and the module headers' `loadPostProcess`/`xfer` became two appended virtuals: each
primary table held `__purecall` in slots 1 and 3 and was two slots longer than retail. Every function stayed
exact, so no gate saw it. Found by scanning the current objects of all 386 Drawable.h includers for a `??_7`
with `__purecall` at slots 1 and 3 beside a GetSnapshotName in slot 2 (exactly these eight, all from that
commit). a21ad04d46d moves the include below the unit's module header (three units also define
`BFME_SNAPSHOT_NAME_SLOT` first, as the module headers do); only the named table changes in each object:

| unit | table | slots before -> after | retail |
|---|---|---|---|
| FireWeaponWhenDamagedBehavior.cpp | `??_7FireWeaponWhenDamagedBehavior@@6BObjectModule@@@` | 15 -> 13 | 0x00C4965C |
| SpawnUnitBehavior.cpp | `??_7SpawnUnitBehavior@@6BObjectModule@@@` | 15 -> 13 | 0x00C591EC |
| ProneUpdate.cpp | `??_7ProneUpdate@@6BObjectModule@@@` | 15 -> 13 | 0x00C5191C |
| CommandSetUpgrade.cpp | `??_7CommandSetUpgrade@@6BObjectModule@@@` | 14 -> 12 | 0x00C57290 |
| ExperienceScalarUpgrade.cpp | `??_7ExperienceScalarUpgrade@@6BObjectModule@@@` | 14 -> 12 | 0x00C584E8 |
| MaxHealthUpgrade.cpp | `??_7MaxHealthUpgrade@@6BObjectModule@@@` | 14 -> 12 | 0x00C58590 |
| ModelConditionUpgrade.cpp | `??_7ModelConditionUpgrade@@6BObjectModule@@@` | 14 -> 12 | 0x00C58658 |
| ProductionQueueHordeContain.cpp | `??_7ProductionQueueHordeContainModuleData@@6B@` | 33 -> 31 | 0x00C490F8 |

Slots 1 and 3 now hold the base bodies (slot 1 is retail's jmp-equivalent; slots 2/3 of the upgrades still
wait for their placeholder rows). link_check over the 49 units naming these classes: 49 LINK at census bytes;
ProductionQueueHordeContainModuleDataDtor.cpp (a one-slot scaffold copy) and AIUpdate.cpp (STLport bodies)
did not link before either. Check any future include of Drawable.h in a module unit the same way: the other
Drawable.h includers whose module tables hold `__purecall` in slots 1-3 (DestroyDie, RadarUpgrade,
StealthUpgrade, WeaponSetUpgrade, ...) have it in all three slots at retail length, the Wall 2 pattern
above, not this flip.

Moves the new tool made possible (each byte-exact, scoped DIR32 OK, the only `??_7` change the named slots,
link_check unchanged with the post-census providers included):
- adc92bb2c53: AutoFindHealingUpdate's getter 0x00495087 (ModuleNameGetters3.cpp, no longer held); its
  primary table is now 10/13 against 0x00C4EC10 by address (slot 0 `??_E`, slot 1 the jmp-equivalent body,
  slot 5 the inline `ret`). The TSV row is now `fixed`.
- def3bdd8e9d: ObjectWeaponStatusHelper's getter 0x0028CBDB (SubsystemNameGetters2.cpp, no longer held):
  0x00BFBE48 11/13 plus slots 0 and 5 inline.
- 59a90d26d09 + ad87f95280d: BuildingBehavior (Wall 2): xfer 0x004562C0 and the getter 0x004561BB in one
  `--also` plan, then `class --fold Rva004561A2`; 0x00C406D4 10/13 plus the same three. BuildingBehavior.cpp
  does not link between the two commits only.
- SpawnUnitBehavior: b70d566b3bf moves update 0x004B886F (the int-return placeholder Rva004B886F, now the
  UpdateSleepTime override) into slot 0 of 0x00C59124, where the constructor unit's table held `__purecall`
  (3/3 now); 9df93b0e363 moves xfer 0x004B87A3 and the getter 0x004B8797 (`--also`).

- 6ebb40818aa: ReplaceSelfUpgrade (TSV needs-view), the WeaponBonusUpgrade recipe over UpgradeModule.h plus a
  four-slot +0x1C interface (placeholder Rva004B70F0Iface1C). Its constructor now stores real tables where it
  stored six zero ints: 0x00C58B10 8/12, 0x00C58AC8 17/18, 0x00C58110 41/47, 0x00C58AB8 1/4 by address, every
  other slot an inline body of retail's shape, and the interface's own 0x00C4EF80 4/4. The deleting-destructor
  scaffold FamilyDeletingDtors_muse-b1dd.cpp declares the class the same way, so its copies are digest-identical
  (its one-slot `??_7ReplaceSelfUpgrade@@6B@` otherwise collided with the constructor unit's +0x1C table and
  stopped linking). Left: slot 3 of 0x00C58110 returns 0 here, but retail 0x004B4A8C returns the +0x1C
  subobject (`lea eax,[ecx-0xC]; add ecx,0x10; neg; sbb; and`), so the interface is CreateModuleInterface (target
  fact; CreateModuleClass.h's four slots match the table's shapes). Adopting it needs `rva004B70F0` under that
  interface's slot-1 name first. SpellRechargeModifierUpgrade has the same shape (+0x1C table 0x00C58358) but its
  destructor fold and xfer touch SpellRechargeModifierUpgrade.cpp, held by lk51 this pass.

- Two of the 21 dummy-secondary units beyond the TSV, the HeightDieUpdate recipe (canonical UpdateModule.h in
  the unit that holds both ctor and dtor; every slot they declare was already rowed under the class):
  37d61ba3773 StealthDetectorUpdate (ctor 0x004A2CB9, dtor 0x004A2BD1; 0x00C51FB4 2/3, 0x00C51FC0 9/13,
  0x00BEFF90 45/47) and 55b6011a2e5 BoredUpdate (ctor 0x00496791, dtor 0x0049669A; 0x00C4F550 3/3,
  0x00C4F55C 8/13, 0x00BEFF90 45/47). Before, both stored zero ints at +0x0C/+0x10, so each module's update
  call reached a zero word. Their name getters are non-virtual readable rows (Wall 1); BoredUpdate's xfer
  0x004ACAAA is one body with PartTheHeavensUpdate::xfer, StealthDetectorUpdate's +0x10 slot 1 0x004A2D67 a
  folded free-function placeholder; those slots stay UpdateModule's.

Still walled:
- SpawnUnitBehavior's +0x20 interface slot 0x004B8851 (`?rva004B8851@Rva004B8732`, table 0x00C59120, today
  `__purecall` in the kept copy): the move builds exact and the rebuilt table names it, but rename.py's
  post-build check refuses a one-slot table, which has no other slot to agree with (false reject,
  re_attempts 0x004B8851). Its destructor `Rva004B8732` (Rva0024A797Grandchildren.cpp) is not folded: that
  scaffold derives from canonical UpdateModule, so a token fold would emit `??_7SpawnUnitBehavior@@6BObjectModule@@@`
  and `6BBehaviorModuleInterface` copies that differ from the constructor unit's; it needs the WeaponBonusUpgrade
  recipe (a shared class header both units include) first.
- RampageBehavior and EnragedBehavior (dummy secondaries): the same recipe builds exact for RampageBehavior.cpp
  (0x00C40D9C 3/3, 0x00C40DA8 8/13), but the pins `??_7RampageBehavior@@6B@` -> 0x00840DA8 and
  `??_7EnragedBehavior@@6B@` -> 0x00840FBC (symbols.csv) name the primary tables, which a canonical view names
  `6BObjectModule` (its `6B@` is the +0x10 table), so link_check takes the unit from LINKS 338 B to not linking.
  Retire or retarget those pins in the same change (re_attempts 0x00458B60); reverted.
- The UpgradeModule family's private views: RadarUpgrade, StealthUpgrade, WeaponSetUpgrade, TooltipUpgrade,
  DoCommandUpgrade (12 slots) and CostModifierUpgrade (10) compile primaries with `__purecall` in slots 1-3, and
  RadarUpgrade, StealthUpgrade and RemoveUpgradeUpgrade an 11-slot UpgradeMux table where retail has 18, so an
  upgrade that reaches getUpgradeActivationMasks or performUpgradeFX reads past it (current objects, this pass).
  Each needs the ReplaceSelfUpgrade/WeaponBonusUpgrade recipe, after its placeholder-rowed slots (for example
  RadarUpgrade's `?rva004B47DB@Rva004B46F9`, UpgradeMux slot 8) move into the class.
- HijackerUpdate (static `getModuleNameKey` spelling) and CivilianSpawnCollide (three-int `onCollide`): re-tried,
  still refused (re_attempts 0x004A4010, 0x004BD6DA).
- SpecialEnemySenseUpdate (Wall 2): every rename of Rva00499F45 respells a comment in
  Rva003AF22EXfer.cpp under the FXParticleSystem tree, which this seat may not touch.
- CivilianSpawnUpdate (Wall 2): its xfer 0x0047F94C is one body in CivilianSpawnUpdate's and BannerCarrierUpdate's
  tables, so `--to-class` refuses it as folded; it needs an ICF twin row first.
- The SpecialAbilityUpdate family (nine TSV rows: FellBeastSwoopPower, FlingPassenger, GiveUpgradeUpdate,
  ReplaceObjectUpdate, SpecialDisguiseUpdate, ToggleDeploy, ToggleHidden, ToggleMounted, WoundArrowUpdate, plus
  about a dozen more units with dummy secondaries): every derived constructor calls the base through
  `??0Rva0044EF5E`. SpecialAbilityUpdate is registered, so `class --fold Rva0044EF5E --into SpecialAbilityUpdate`
  needs every one of the 40 units that spell the placeholder prepared on SpecialAbilityUpdate.h in one change;
  no constructor can adopt the header before that.
- OCLUpdate: `??1OCLUpdate@@UAE@XZ` 0x004CD3DB and `??_GOCLUpdate` 0x004CD440 are TeleportToCasterSpecialPower's
  (target facts: the destructor's first +0 store 0x00C5FB40 is the table whose slot 4 is
  `?getModuleNameKey@TeleportToCasterSpecialPower` 0x004CD3FB and which TeleportToCasterSpecialPower's
  constructor 0x004CD3A4 installs). Readable names never fold, so this is a naming-lane identity correction
  before OCLUpdate's constructor can store its table.

**The Upgrade family's private views, part 1 (2026-11-07, seat halilkkaya-lk56, base `2f3e43c2c1`, census
index `0aff0e89c0`).** Eleven upgrade classes now let the compiler store their real tables over the canonical
UpgradeModule.h. Before, each emitted a primary table with `__purecall` in slots 1-3 (only two slots long for
RemoveUpgradeUpgrade), an UpgradeMux (+0x10) table of ONE anchor slot (Delayed, Base, Castle, DoCommand,
Tooltip, AllowBannerSpawn, LocomotorSet) or of
11 slots with 9-10 `__purecall` (Stealth, Radar, RemoveUpgrade) where retail has 18, a one-slot +0x18 table,
and a BehaviorModuleInterface table whose getDamage/getUpgrade returned 0. CommandSetUpgrade (already on the
header) had `__purecall` in UpgradeMux slot 10, so applying any command-set upgrade aborted.

Recipe (one class at a time; three commits when the destructor and the getter are placeholders):
1. Ctor unit on the header: drop the private UpgradeMux/ModuleInterface/UpgradeModule, define
   `BFME_SNAPSHOT_NAME_SLOT` before the first Snapshot.h (three units read Snapshot.h in crc mode first:
   BaseUpgrade's `Common/Snapshot.h`, CastleUpgrade through CastleUpgradeModuleData.h, RemoveUpgradeUpgrade
   through its view) and read UpgradeModule.h before Drawable.h. Declare only overrides rowed under the class;
   an UpgradeMux slot 8 that is retail's shared empty 0x000B3FD0 becomes an inline empty override. Slot 3
   0x004B8710 (Version1, then UpgradeModule::xfer) is added per class as an ICF twin of
   `?xfer@ArmorUpgrade@@MAEXPAVXfer@@@Z` (add_match `--icf-owner`, fold-proof ArmorUpgradeXfer.cpp). When the
   unit has its own `AsciiString` (BaseUpgrade's StringBase typedef, ascii_string.h), include BfmeXfer.h at
   the end of the unit with only the other operand forward declarations.
2. `rename.py function --to-class X --new ?GetSnapshotName@X@@MBEPBDXZ` for the `RvaXXXXXXXXNamed` getter,
   with ModuleNameGetters3.cpp prepared in its `BFME_SNAPSHOT_NAME_GETTER` form. Rebuild the ctor unit with
   the declaration first: the dry run judges the current object.
3. A shared `Code/GameEngine/Include/GameLogic/Module/X.h` (the WeaponBonusUpgrade.h recipe) with the public
   virtual destructor, then `rename.py class --fold <dtor placeholder> --into X`. In the same commit the
   scaffold FireWeaponWhenDeadBehaviorDerived.cpp includes X.h instead of the token fold's dtor-only view,
   whose ObjectModule/UpgradeMux tables differ under the same names. Every COMDAT the two units share was
   digest-identical (62-63 per class).

| class (ctor; primary / UpgradeMux table) | commits | primary vs retail by address | UpgradeMux | left |
|---|---|---|---|---|
| StealthUpgrade 0x004B5378 (0x00C57E30 / 0x00C57DE8) | 1d10fe35dfd | 6/12 -> 8/12 + 3 equiv | 2/11 -> 18/18 | slot 2: readable non-virtual `?name@StealthUpgrade` (Wall 1) |
| RadarUpgrade 0x004B478E (0x00C57890 / 0x00C57848) | ddfb43d0d95, 0e6e0be8088, dead0784778 | 5/12 -> 9/12 + 3 equiv | 1/11 -> 18/18 | none: slot 8 `onDelete` (was `?rva004B47DB@Rva004B46F9`) moved with the getter (`--also`); UpgradeMux slot 8 0x004B471F is a five-table fold, rowed as a twin of `?rva004B471F@Rva004523E9`; `Rva004B46F9` folded with RadarUpgrade.h |
| DoCommandUpgrade 0x004B4C2E (0x00C57B58 / 0x00C57B10) | 1903b9d4b9d | 6/12 -> 8/12 + 3 equiv | 1 slot -> 18/18 | slot 2 Wall 1 (`?name@DoCommandUpgrade`); the ctor, dtor and slots units share DoCommandUpgrade.h, and the ctor's extern `__identifier` stores are gone |
| RemoveUpgradeUpgrade 0x004B7FA4 (0x00C58E20 / 0x00C58DD8) | f1699b78f69 | 2 slots -> 8/12 + 3 equiv | 2/11 -> 18/18 | slot 2 Wall 1; RemoveUpgradeUpgradeView.h now derives the class from UpgradeModule.h |
| DelayedUpgrade 0x004B3C75 (0x00C573E4 / 0x00C572E0) | ca86272f99b, 8f23a7ff6a5, e8e156de5ec | 6/12 -> 9/12 + 3 equiv | 1 slot -> 17/18 + inline slot 8 | none |
| BaseUpgrade 0x004B371C (0x00C57120 / 0x00C570D8) | 66129a1ccd2, 35695d8351b, e14181773d9 | 6/12 -> 9/12 + 3 equiv | 1 slot -> 17/18 + inline slot 8 | none |
| CastleUpgrade 0x004B6869 (0x00C58880 / 0x00C58838) | 9e828df3c3f, 5dead9e635f, d9291776684 | 6/12 -> 9/12 + 3 equiv | 1 slot -> 17/18 + inline slot 8 | none |
| CommandSetUpgrade 0x004B3AB2 (0x00C57290 / 0x00C57248) | five commits, "CommandSetUpgrade: declare postUpgradeCheck ..." to "Fold class Rva004B39FC ..." | 6/12 -> 9/12 + 3 equiv | 16/18 (slot 10 `__purecall`) -> 18/18 | none |
| TooltipUpgrade 0x004B7A50 (0x00C58C08 / 0x00C58BC0) | fa93e328ee1, f61e65810cb, 0882584e5bc, 1bff0526d02 | 6/12 -> 9/12 + 3 equiv | 1 slot -> 18/18 | none: slot 6 is the postUpgradeCheck twin (an offset cast reads the registered Player's mask), slot 10 moved from `Rva004B7A9D`, `Rva004B79AD` folded |
| AllowBannerSpawnUpgrade 0x004B8587 (0x00C59030 / 0x00C58FE8) | 0739a85b88b, 2129172c717 | 6/12 -> 9/12 + 3 equiv | 1 slot -> 18/18 | none; the destructor and `??_G` were already rowed under the class (UpgradeModuleTailDtors.cpp), so no fold; the ctor's extern `__identifier` stores are gone |
| LocomotorSetUpgrade 0x004B3F0B (0x00C57530 / 0x00C574E8) | 0739a85b88b | 6/12 -> 8/12 + 3 equiv | 1 slot -> 18/18 | slot 2 Wall 1 (`?name@LocomotorSetUpgrade`); LocomotorSetUpgradeConstructor.cpp, which compiled a third private view and did not link, now LINKS 75 B |

"3 equiv" is slot 0 (the unit's `??_E` for the rowed `??_G`), slot 1 (UpgradeModule's 0x0058B03E for retail's
`jmp` 0x00497805) and slot 5 (the inline `ret`). Every class's BehaviorModuleInterface table is now 42/47 plus
5 inline bodies of retail's shapes, and its +0x18 table 3 inline bodies (`ret 4`, `ret 4`, `ret 0xC`).
CommandSetUpgrade's slot 6 postUpgradeCheck 0x004B3B42 is one body with TooltipUpgrade's slot 6, so
`--to-class` refuses it; it is rowed as an ICF twin of `?rva004B3B42@Rva004B3B42` (the owner's own unit),
which let the slot-10 move (`?upgradeImplementation@Rva004B3AFF` -> CommandSetUpgrade) prove itself.

link_check: every commit keeps its ctor, scaffold, factory, pool-key, implementation and getter units
linking at census bytes or more (Stealth 226 -> 252, Radar 416 -> 450, DoCommand 145 -> 171, RemoveUpgrade
295 -> 321, Delayed 49 -> 75, Base 270 -> 296, Castle 271 -> 297, CommandSet 443 -> 469, Tooltip 206 -> 302,
AllowBannerSpawnUpgradeCtor 49 -> 75, LocomotorSetUpgradeConstructor 0 -> 75 B). Check these units
with the current objects of FireWeaponWhenDeadBehaviorDerived.cpp and ModuleNameGetters3.cpp in the list: the
census copies predate the folds and getter moves, and fake `??1X` duplicates and unresolved
`GetSnapshotName`s (the getter commit 5dead9e635f's "6/6" holds only with the scaffold included: 7/7).
Census confirmation: not claimed.

Still walled in the family:
- Wall 1 getters (readable non-virtual `?name@X@@QBEPBDXZ`: StealthUpgrade, DoCommandUpgrade,
  RemoveUpgradeUpgrade, LocomotorSetUpgrade): an identifier rename to GetSnapshotName needs a canonical basis; vtable slot order is
  only a hint.
- WeaponSetUpgrade: UpgradeMux slots 8/10 (0x004B5783, 0x004B5765) are rowed non-virtual under the readable
  class WeaponSetUpgradeSecondary; `--to-class` takes only placeholder classes (re_attempts 0x004B5765).
- Not attempted this pass: LevelUpUpgrade (UpgradeMux slot 2 is
  `?rva004CE2B0@LevelUpUpgrade@@UAE_NPAVRva00406F9C@@@Z`, a wouldUpgrade override with a placeholder
  parameter type), CostModifierUpgrade and SpellRechargeModifierUpgrade (the ReplaceSelfUpgrade +0x1C
  interface shape), GeometryUpgrade, StatusBitsUpgrade and SubObjectsUpgrade.

Items 2 and 3 of the lk53 handoff, re-checked this pass and still walled:
- SpecialAbilityUpdate (`class --fold Rva0044EF5E --into SpecialAbilityUpdate`) is refused before planning by
  frozen keys. reverse/dup_defs_baseline.tsv holds `divergent ??_GRva0044EF5E@@UAEPAXI@Z` and
  `duplicate ??1Rva0044EF5E@@UAE@XZ`. Both are stale (dup_defs.py at this tree reports neither), but
  `dup_defs.py --write-baseline` refuses because 298 current shadow keys are not in the baseline, so no tool
  shrinks only these two. reverse/hatch_baseline.tsv holds the `/alternatename:??1Rva0044EF5E@@UAE@XZ=
  ??1SpecialAbilityUpdate@@UAE@XZ` of SpecialAbilityUpdateDtor.cpp, through which about 30 derived
  destructors resolve until the fold. After both, the fold still needs all 40 units that spell the
  placeholder prepared on SpecialAbilityUpdate.h in one change (re_attempts 0x0044EF5E). It needs a
  maintainer decision on the two registers.
- RampageBehavior/EnragedBehavior: no supported tool retires or retargets the data pins
  `??_7RampageBehavior@@6B@` -> 0x00840DA8 and `??_7EnragedBehavior@@6B@` -> 0x00840FBC. pin_admission.py
  only adds (and refuses data addresses, so a retarget to 0x00840D9C is refused too), and
  pin_consistency.py --symbol reports both consistent. The only precedent is a hand deletion plus a
  hatch_counters shrink under Verifier-Change (baa896fe561), which needs maintainer approval (re_attempts
  0x00458B60).
