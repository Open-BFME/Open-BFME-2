### LINK-514: kept `??_7` copies differ from retail's vftables (runtime vtable survey)
Status: Open (partly repaired). Updated: 2026-11-08 (lk67 shape survey and twins at 49e50f8ba4; lk64 pass at d171e84869; lk56 pass at 2f3e43c2c1; lk53 pass at 26715f1e00); inspected revision: e5e17e246f, getter and installer passes at be366d041e, dummy-vptr ctor pass at e44e2c5ef6c, ObjectHelper family at e1e03be955 (census index c95fcfcfcd; f44cbcf5b0 for the ctor pass; 94d8ffa1ad for the family).
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
  StrafeAreaUpdate constructor prerequisite verified 2026-11-08: canonical
  UpdateModule replaces its private base, retaining the correct 13-slot manual
  table and all three explicit stores. Both rows, the 52-byte data row and
  parent EH graph remain exact; header acceptance retires one debt row.
  The split StrafeAreaUpdate/Rva003A4CAE identities and short mixed-destructor
  table still block replacement of the manual table; strong-definition is
  still open. [Evidence](../../reverse/attempt_support/strafe-base-adoption-20261108/README.md).
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
index `0aff0e89c0`).** Twelve upgrade classes now let the compiler store their real tables over the canonical
UpgradeModule.h. Before, each emitted a primary table with `__purecall` in slots 1-3 (only two slots long for
RemoveUpgradeUpgrade and StatusBitsUpgrade), an UpgradeMux (+0x10) table of ONE anchor slot (Delayed, Base, Castle, DoCommand,
Tooltip, AllowBannerSpawn, LocomotorSet) or of
11 slots with 9-10 `__purecall` (Stealth, Radar, RemoveUpgrade, StatusBits) where retail has 18, a one-slot +0x18 table,
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
| StatusBitsUpgrade 0x004B4960 (0x00C57938 / 0x00C578F0) | e03a6dfb630, 1fd1c6fe66e | 2 slots -> 9/12 + 3 equiv | 2/11 -> 18/18 | none; the fold went with the header move (on the header the ctor unit's implicit inline `??1StatusBitsUpgrade` was judged against the pinned retail body, so the unit linked only with the real destructor); it retired the pin `??1StatusBitsUpgrade@@UAE@XZ` -> 0x004B48D3 and the scaffold's `/alternatename` to the placeholder (register ceilings left for the next `hatch_counters --update`) |
| LocomotorSetUpgrade 0x004B3F0B (0x00C57530 / 0x00C574E8) | 0739a85b88b | 6/12 -> 8/12 + 3 equiv | 1 slot -> 18/18 | slot 2 Wall 1 (`?name@LocomotorSetUpgrade`); LocomotorSetUpgradeConstructor.cpp, which compiled a third private view and did not link, now LINKS 75 B |
| ModelConditionUpgrade 0x004B64E5 (0x00C58658 / 0x00C58610) | "ModelConditionUpgrade: declare the class in ModelConditionUpgrade.h ...", "Move 2 members into ModelConditionUpgrade ..." (halilkkaya-lk62, finishing lk61) | 8/12 -> 9/12 by address (slot 3 the ArmorUpgrade::xfer ICF twin; slots 0 and 1 equivalent) | 16/18 (slots 8 and 10 `__purecall`) -> 18/18 | slot 2: the getter 0x004B63DD is `?name@Rva004B63DDNamed` in ModuleNameGetters3.cpp, which ancalgonn-swarm-defects held (class claims), so it stays UpgradeModule's; slot 8 moved from `?upgradeRemovalImplementation@Rva004B65A5` (its body stays in VslotSmallBodiesY.cpp, now on the canonical class, until a merge brings it to its approved TU); the destructor 0x004B63BD and `??_G` 0x004B6516 remain under the placeholder Rva004B63BD in FireWeaponWhenDeadBehaviorDerived.cpp (`class --fold` not done; no pin names `??1ModelConditionUpgrade`) |

"3 equiv" is slot 0 (the unit's `??_E` for the rowed `??_G`), slot 1 (UpgradeModule's 0x0058B03E for retail's
`jmp` 0x00497805) and slot 5 (the inline `ret`). Every class's BehaviorModuleInterface table is now 42/47 plus
5 inline bodies of retail's shapes, and its +0x18 table 3 inline bodies (`ret 4`, `ret 4`, `ret 0xC`).
CommandSetUpgrade's slot 6 postUpgradeCheck 0x004B3B42 is one body with TooltipUpgrade's slot 6, so
`--to-class` refuses it; it is rowed as an ICF twin of `?rva004B3B42@Rva004B3B42` (the owner's own unit),
which let the slot-10 move (`?upgradeImplementation@Rva004B3AFF` -> CommandSetUpgrade) prove itself.

link_check: every commit keeps its ctor, scaffold, factory, pool-key, implementation and getter units
linking at census bytes or more (Stealth 226 -> 252, Radar 416 -> 450, DoCommand 145 -> 171, RemoveUpgrade
295 -> 321, Delayed 49 -> 75, Base 270 -> 296, Castle 271 -> 297, CommandSet 443 -> 469, Tooltip 206 -> 302,
AllowBannerSpawnUpgradeCtor 49 -> 75, LocomotorSetUpgradeConstructor 0 -> 75, StatusBits 224 -> 250 B). Check these units
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
  interface shape), GeometryUpgrade and SubObjectsUpgrade.

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

Item 4 of the lk53 handoff, CLEARED (2026-11-07, seat halilkkaya-lk56): SpawnUnitBehavior's one-slot +0x20
table. e0cd82258e8 teaches `rename.py --to-class` that a retail table of exactly one slot proves its move
when an installer's compiled copy is exactly one slot long and names the moved symbol (Verifier-Change,
five regression tests in tools/tests/test_rename_to_class.py; test_gate_exploits.py still passes). Then
4fc54046a98 moves `?rva004B8851@Rva004B8732` into SpawnUnitBehavior (identifier kept): the kept
`??_7SpawnUnitBehavior@@6BSpawnUnitBehaviorIface3@@@` slot 0 goes from `__purecall` to 0x004B8851, 1/1
against retail 0x00C59120; 51/51 exact, link_check 6/6 LINK at unchanged bytes (re_attempts 0x004B8851).
The destructor `Rva004B8732` (Rva0024A797Grandchildren.cpp) is still unfolded: that scaffold derives from
canonical UpdateModule, so it needs a shared SpawnUnitBehavior header first.

**2026-11-07, crash-prevention lane (seat ancalgonn-swarm-seat4): ActiveBody's readable-class slots, classified by the
retail tables that hold them.** StructureBody (ctor 0x004C0951, 268 Object INI uses) is the most-used zero vptr left on
the shell-map path; it waits on ActiveBody.h's slots. `rename.py function --to-class ActiveBody` proves slot 1 (0x004BF40F,
`Rva004BF40F` -> `loadPostProcess`, table 0x00C5B038 installed by ActiveBody's ctor; dry run clean, four units) but refuses
p20 as a readable class. Which tables hold each wall (every retail .rdata reference, with the ctor that installs the
table):
- p20 0x004BE3EF, rowed `W3DModelDraw::stopClientParticleSystems`: slot 20 of ActiveBody's 0x00C5B038 and the ten Body
  subclass primaries (Highlander, Immortal, Structure, SymbioticStructures, Respawn, DelayedDeath, FreeLife,
  DetachableRider, Oathbreaker, PorcupineFormation); no W3DModelDraw table holds it. Not an ICF fold: ActiveBody's own
  body filed under another readable class. **Naming decision.**
- b28 0x004BE67E, rowed `DetachableRiderBody::Rva004BE67E`: slot 28 of ActiveBody's body interface 0x00C5B5B0 and every
  Body subclass's. Not a fold: ActiveBody's own (DetachableRiderBody inherits it). **Naming decision.**
- p15 0x004BF8DF, rowed under the placeholder `Rva004BF8DF`: slot 15 of the same eleven primaries. A `--to-class` move
  (the int vs enum return may need `--respell`), not a naming decision.
- p2 0x004BF88D, rowed `ActiveBody::name` (QBE, non-virtual): slot 2 of 0x00C5B038 only. ActiveBody's own GetSnapshotName
  slot under a non-virtual spelling; a same-class respell, not a naming decision.
For the names workflow: p20 and b28 only. The other categories in the inventory above (placeholder members, non-virtual
spellings, BodyModule-owned slots, ICF folds) are tool moves.

**2026-11-07, crash-prevention lane (seat ancalgonn-swarm-seat4): two tool gaps found while repairing StructureBody and
W3DTreeDraw, routed to a tooling lane.**

1. *Class ownership between readable classes (false reject, re_attempts 0x004BE3EF and 0x004BE67E).* ActiveBody p20
   0x004BE3EF is rowed `?stopClientParticleSystems@W3DModelDraw@@IAEXXZ` and b28 0x004BE67E
   `?Rva004BE67E@DetachableRiderBody@@UBE?AVAsciiString@@XZ`. The retail .rdata references prove whose they are: p20 is
   slot 20 of ActiveBody's 0x00C5B038 and of the ten Body subclass primaries (Highlander, Immortal, Structure,
   SymbioticStructures, Respawn, DelayedDeath, FreeLife, DetachableRider, Oathbreaker, PorcupineFormation), and no
   W3DModelDraw table holds it. b28 is slot 28 of ActiveBody's body interface 0x00C5B5B0 and of every Body subclass's.
   `rename.py function --to-class ActiveBody` refuses both because the current class is readable ("a naming decision").
   `name_lane` has no key for it: `next --files` serves no key for `stopClientParticleSystems`, which has no
   name_basis.csv record (a donor spelling), so `dispute` cannot revert it. b28 is served only as the placeholder
   identifier under `DetachableRiderBody`, and a vote there would land under the wrong class. Proposed rule: a
   readable-class member may move when every retail table holding its address belongs to CLASS or to classes that
   derive from it, and no table of the current class holds it.
   Related: p15 0x004BF8DF is refused as a folded body because our DelayedDeathBody/FreeLifeBody/DetachableRiderBody
   views do not derive from ActiveBody, although retail's tables do. The derivation the proof checks comes from our
   views, not from retail.
   W3DTreeDraw shows the same order problem. `--to-class W3DTreeDraw` for slot 2 (0x000CEB69) dry-runs clean but fails
   verification because W3DTreeDraw.cpp compiles no `??_7W3DTreeDraw`: its ctor still stores `g_00BCCCF8`. The ctor
   cannot install the real table until slots 0/2/3 resolve, and slot 2 cannot move until the ctor installs the table.

2. *The `?name@X@@QBEPBDXZ` getters: proposal, nothing renamed.* 297 rows have this non-virtual `name` spelling, and all
   297 bodies are `mov eax, offset <class-name literal>; ret`. Retail .rdata references, against the tables the vptr
   stores install (crash-prevention store scan):

   | where retail holds the address | rows | class part |
   |---|---:|---|
   | slot 2 of a table installed only by X's own ctor/dtor | 85 | readable (WaterRenderObjClass, EventParameter, ScriptEngine, ActiveBody p2 0x004BF88D, ...) |
   | slot 2 of other classes' tables only | 174 | all `Rva…Named` placeholders: 78 with one owning class, 91 with two, 5 with three |
   | referenced, but not at slot 2 of an installed table | 34 | placeholders |
   | no table | 4 | placeholders (plain getters) |

   Slot 2 is Snapshot's `GetSnapshotName` in the BFME_SNAPSHOT_NAME_SLOT spelling (canonical
   reference/shims/moduledata/Common/Snapshot.h). An override must be spelled `GetSnapshotName` to occupy it, so a
   non-virtual `name` cannot be what retail compiled. Evidence that proves a row is X's GetSnapshotName override: (a) the
   address is slot 2 of a retail table T; (b) T is installed by a ctor or dtor row of X (a dtor's first +0 store, or
   every +0 store of a ctor); (c) every table holding the address belongs to X or to classes deriving from X; (d) the
   body returns a string literal (the name). (a)-(c) are what `--to-class` already proves, and (d) is a byte check.
   Feasibility: the 85 own-class rows are a mechanical respell `?name@X@@QBEPBDXZ` -> `?GetSnapshotName@X@@UBEPBDXZ`
   (identifier and virtual together; `--virtual` alone keeps `name`, and `--respell` cannot combine with `--to-class`
   or `--virtual`), batchable with a tool-verified proof per row. The 78 single-owner placeholders are `--to-class X
   --new GetSnapshotName` moves, but they face the same order problem as W3DTreeDraw: the proof needs X's unit to
   compile X's vftable, and many of those classes' ctors still store placeholder vptrs. The 96 multi-owner rows are
   folds (ICF alias rows) or inherited overrides, and need the derivation the tables imply. Batches must also update
   the BFME_LITERAL_NAME_GETTER units (W3DDrawNameGetters.cpp, SubsystemNameGetters.cpp, ModuleNameGetters*.cpp).

3. *Why p15 stays refused, and why the Body views cannot simply take an ActiveBody base.* The tables `--to-class`
   judges "unrelated" are owned twice: by the real class (its ctor) and by the placeholder its destructor is rowed under.
   DelayedDeathBody 0x00C5BBE8 is owned by `??0DelayedDeathBody` and `??1Rva004C1604`, FreeLifeBody 0x00C5BE38 by
   `??0FreeLifeBody` and `??1Rva004C1866` (both placeholders in Rva004C131BDerived.cpp, over the placeholder base
   Rva004C131B), and DetachableRiderBody 0x00C5C0B8 by `??0DetachableRiderBody` and `??1Rva004C1BAB`
   (Rva004BF951Derived_Unresolved.cpp). DetachableRiderBodyCtor.cpp's view already derives from ActiveBody;
   DelayedDeathBody.cpp's and FreeLifeBody.cpp's derive from a flat local RespawnBody with three explicit dummy-vptr
   stores. The honest repair is `rename.py class --fold Rva004C1604 --into DelayedDeathBody` (and likewise for the
   other two; none is registered). It is refused while the ctor installs no `??_7DelayedDeathBody@@6B@`, and the ctor can
   install its real three tables only through ActiveBody.h, whose primary and body-interface slots name the 34-36
   members still rowed under placeholder or field-getter classes (the StructureBody wall above): bytes stay exact, but
   the unit would go from linking to unresolved. Order: ActiveBody's slot rows (gaps 1-2), then each Body ctor on
   ActiveBody.h, then the three destructor folds, then p15.
4. *Five shell-map modules scoped (read-only).* Every primary table still has slots under placeholder identities. None
   is source-only:
   - RunOffMapBehavior (ctor 0x0046217B): 12/47/1-slot tables. Slot 0 is `??_GRva00462151` (destructor placeholder:
     class fold) and slot 2 is the free function `?Rva004621ACGet@@YAHXZ` (a getter needing a class); the 47-slot
     BehaviorModuleInterface table is all shared rowed bodies.
   - ModelConditionSoundSelectorClientBehavior (0x00254B82): 19/3. Slot 0 is `??_GRva00252B68` (fold); slots 13/14 are
     the shared field getter `Rva000CA841MovLeaNegSbbField` (ICF alias rows, an existing tool).
   - HorseHordeContain (0x004765E5): 13 tables up to 155 slots with 65 placeholder slots; a large identity job.
   - DominateEnemySpecialPower (0x004CC988) and ActivateModuleSpecialPower (0x004CDD02): 23/47/3/9 tables with dtor and
     getter placeholders (`??_GRva004CC9BF`, `Rva004CC9B9Get`, `Rva004CDD33Get`) and a shared `xfer@Rva004CE0BE`.
   The closest are RunOffMapBehavior and ModelConditionSoundSelector: both need one destructor class fold, which is
   refused for the same reason until the ctor installs the real table, plus a getter move or ICF aliases.

   *Review outcome (2026-11-07):* the proposed rule in gap 1 is rejected. A missing name_basis record does not prove a
   readable name wrong, and a body's occupancy of inherited slots does not prove which class overrides it. So
   `--to-class` stays refused for readable classes, and the two false-reject rows for 0x004BE3EF and 0x004BE67E are
   voided. ActiveBody p20/b28 need a class-ownership naming route, which is not designed yet. StructureBody and the
   ActiveBody.h-based Body ctors stay parked behind it.


**2026-11-07 ActiveBody p20/b28 need a naming route for class ownership (swarm Link lane).**
0x004BE3EF (rowed `W3DModelDraw::stopClientParticleSystems`, a Zero Hour donor spelling) and 0x004BE67E
(`DetachableRiderBody::Rva004BE67E`) sit only in ActiveBody's and its subclasses' retail tables
(0x004BE3EF in slot 20 of eleven 23/25-slot tables from 0x00C5B038; 0x004BE67E in slot 28 of the
43-slot tables from 0x00C5B390). A `rename.py function --to-class` mode that moved a readable member
out of its class on that evidence (no name_basis.csv record, the address in no table of the current
class, every table installed by the target or a subclass) was reviewed and dropped: a missing record
is no evidence that a readable name is wrong (docs/naming.md records historical hand renames without
basis rows), and inherited occupancy does not prove which class declares the override. So the move is
a naming decision and needs a naming route: a name_lane key type that votes on which class owns a
method. To design later, not now.

Two facts for that design, read through rename.py's table helpers at 27ad28896c: every subclass table
holding either address is installed by exactly two rows, the readable subclass's constructor and a
destructor rowed under a placeholder class (e.g. 0x00C5BBE8: `??0DelayedDeathBody` and
`??1Rva004C1604`, a class with only `??1`/`??_G` rows). The `--to-class` "unrelated class" refusal on
the DelayedDeathBody, FreeLifeBody and DetachableRiderBody tables comes from their own constructor
units' views, not from the placeholders: DelayedDeathBody.cpp and FreeLifeBody.cpp declare their class
on `RespawnBody` with no base for RespawnBody, and DetachableRiderBodyCtor.cpp declares no base for its
class, so neither chain reaches ActiveBody. ImmortalBody, StructureBody and RespawnBody's tables have
the same constructor-plus-placeholder-destructor shape and pass.

**The Upgrade family's private views, part 2, and why no table leaves the bridge yet (2026-11-08, seat
halilkkaya-lk64, base `d171e84869`, census index `eaefe561ff`, real link rl7 at `cdcfc30b16`).** Six more
upgrade classes now declare their class in a shared `Code/GameEngine/Include/GameLogic/Module/X.h`, and
their destructor placeholders in FireWeaponWhenDeadBehaviorDerived.cpp are folded into them (lk56's recipe,
steps 1 and 3 in one commit per class; the getter step stays walled, see below). Each fold deletes the
placeholder's four `??_7RvaXXXXXXXX@@6B...@@@` tables, which rl7 bridged at the class's own retail
addresses: 24 bridged tables go, none are added. In every commit the scaffold and the ctor unit share 62
COMDATs, all digest-identical, the scaffold's other COMDATs are unchanged, and only the ctor unit's
primary table changes (toward retail); no initializer or non-COMDAT data section changes.

| class (placeholder; primary / UpgradeMux table) | commit | primary vs retail by address | UpgradeMux |
|---|---|---|---|
| ModelConditionUpgrade (Rva004B63BD; 0x00C58658 / 0x00C58610) | bab46819bad | scaffold copy 7/12 -> 10/12 | 16/18 -> 18/18 (the scaffold's copy) |
| GarrisonUpgrade (Rva004B57CE; 0x00C58088 / 0x00C58040) | cbb73e66363 | 7/12 (slot 4 `__purecall`) -> 10/12 | 18/18 |
| ExperienceScalarUpgrade (Rva004B611C; 0x00C584E8 / 0x00C584A0) | 6f58e03652e | 9/12 -> 10/12 | 18/18 |
| AttributeModifierUpgrade (Rva004B66B3; 0x00C587E8 / 0x00C587A0) | b86c526fa8c | 7/12 (slot 4 `__purecall`) -> 10/12 | 18/18 |
| MaxHealthUpgrade (Rva004B6259; 0x00C58590 / 0x00C58548) | 67f30ae7752 | 9/12 -> 10/12 | 18/18 |
| UnpauseSpecialPowerUpgrade (Rva004B53DF; 0x00C57EA8 / 0x00C57E60) | e784fa681e2 | 8/13 -> 9/13 | 18/18 |

Counts include slot 0 (`??_E` for the rowed `??_G`). Slot 3 is each class's ICF twin of
`?xfer@ArmorUpgrade` (0x004B8710; BfmeXfer.h read at the end of the unit after the operand forward
declarations); slot 4 is getModuleNameKey, already rowed (for Garrison and AttributeModifier in
`Code/GameEngine/Source/Common/System/X.cpp`), so two `__purecall`s are gone. Left in every primary table:
slot 1 (UpgradeModule's 0x0058B03E where retail has the `jmp` 0x00497805) and slot 2 (the getter, a
`?name@RvaXXXXXXXXNamed` row in ModuleNameGetters3.cpp, which ancalgonn-swarm-defects holds). Unpause also
keeps slot 5: retail's 0x004B54D9 sits in Module's onObjectCreated slot, but the row is named
`?onCreate@UnpauseSpecialPowerUpgrade`, a new virtual that lands at slot 12; the rename needs a naming
basis. Pitfall confirmed: link_check the scaffold with the current objects of every ctor unit the branch
changed, or the census copies fake `??1X` duplicates and unresolved `?xfer@X`. The scaffold's own two
unresolved names (`?xfer@CastleUpgrade`, `?upgradeImplementation@CastleUpgrade`) predate this pass:
4771339e0a2 merged their providers into CastleUpgrade.cpp after the census index.

Why none of these tables leaves the bridge yet (rl7's `vtable_bridge.json`):
- `tools/vtable_bridge.py` `matches()` and `source_slot_mismatches()` compare a slot's relocation symbol
  name with ledger row names. A vftable's slot 0 relocates to `??_EX@@UAEPAXI@Z`, a weak external
  (`IMAGE_SYM_CLASS_WEAK_EXTERNAL`) whose default is `??_GX`; no ledger row is named `??_EX`, so every
  table with a virtual destructor is bridged even when the linker resolves the slot to the rowed `??_G` at
  retail's address. In rl7, 465 bridged tables differ from retail only in such slots (their `??_G` row is
  at the retail target); the primary tables above join them once slots 1 and 2 are fixed. Lead for a
  tooling seat (Verifier-Change, with tests): resolve a weak external slot to its default when no kept
  object or archive defines the weak name. `comdat_body` already reads weak defaults (lk40).
- Shared inline bodies without a ledger row: 32 bridged `??_7XUpgrade@@6BBehaviorModuleInterface@@@`
  copies (0x00C57328) differ from retail only in slots 4, 9 and 10 (`?getDamage@UpgradeModule` 0x0045875F,
  `?getUpdate@BehaviorModule` 0x000D43D0, `?getUpgrade@UpgradeModule` 0x002533D3), and 35
  `??_7XUpgrade@@6BUpgradeModuleInterface18@@@` copies (0x00C58790) only in slots 0-2 (`vslot18_00/01`
  0x0047A69C, `vslot18_02` 0x000D1407). Six ICF twin rows in one ctor unit (the SupplyTruckAIUpdateCtor.cpp
  precedent for BehaviorModule's slots) would clear 67 tables. Not done: `class:UpgradeModule` was held by
  ancalgonn-swarm-defects all pass and 0x000D43D0 by yasinschroeder-codexb2 (class:Keyboard). The +0x18
  table's three slots have DamageModuleInterface's shape in Zero Hour (onDamage/onHealing `ret 4`,
  onBodyDamageStateChange `ret 0xC`), and slot 4 returns that +0x18 interface; a donor lead, not proof.
- The five UpgradeMux tables with one inline empty slot 8 (Base, Delayed, WeaponBonus, Castle,
  ReplaceSelf; retail 0x000B3FD0) need the same twin rows; 0x000B3FD0 is held through class:Keyboard.

Still walled in the scaffold: BuildableHeroListUpgrade (Rva004B82A5; its unit reads Snapshot.h without the
name slot before UpgradeModule.h, so its primary table has 13 slots with `__purecall` in 2 and 4),
CostModifierUpgrade and SpellRechargeModifierUpgrade (Rva004B5982, Rva004B5D0B; the +0x1C interface),
LevelUpUpgrade (Rva004B3D3B; placeholder parameter type), SubObjectsUpgrade (Rva004B4CDF; spelled in three
units), WeaponSetUpgrade (Rva004B568B; slots 8/10 under WeaponSetUpgradeSecondary). Other GameLogic/Object
scaffolds with placeholder tables in rl7: DieModuleDerived.cpp (30 tables, 10 classes) and
ModuleUpdateDtors.cpp (9) are DieModule/UpdateModule units this seat may not touch; HealContain.cpp's
Rva00220240FlatDtor (9 tables) and Rva00082EF5Ctor.cpp (8) are multi-base Contain shapes.

**The slot-0 weak `??_E` lead, verified and measured (2026-11-08, seat halilkkaya-lk65, base `4904abd4bd`,
census index `eaefe561ff`).** Verified on compiled objects: in the five spot-checked units, slot 0 of
`??_7X@@6B@` relocates (DIR32) to `??_EX@@UAEPAXI@Z`, an undefined symbol of class 105
(IMAGE_SYM_CLASS_WEAK_EXTERNAL). Its IMAGE_WEAK_EXTERN aux record names `??_GX@@UAEPAXI@Z` with
characteristics 2 (search libraries), and the ledger rows `??_GX` at retail's slot-0 address. With no
definition of `??_EX` in any input, link.exe binds the slot to `??_GX`, so the table already matches retail
and the bridge copy is not needed.
Rule tested (tools-only, Verifier-Change): a slot whose relocation names an undefined weak external matches
only when no input (kept object or runtime archive, COMDAT or not) defines the weak name, every kept
object's weak record for it gives the same default and characteristics (the slot's own record among them),
and the default's ledger address is exactly retail's target. Otherwise the existing name comparison
applies. Five tests cover it: the weak slot matches; a strong or COMDAT `??_EX` stops it; disagreeing
defaults or characteristics stop it; a default rowed at another address stops it. `test_vtable_bridge.py`
(104), `test_gate_exploits.py`, `test_exit_link.py`, `test_link_batch_audit.py` and `test_repair_queue.py`
pass. Without the fix, the first test fails.
Offline A/B over exit_link's own inputs (17,956 objects, no link): bridged tables 5,075 -> 4,581 (-494;
retail tables 3,485 -> 3,056; slots 66,093 -> 64,758), already-correct 604 -> 1,098. Refusals are
identical, no table becomes bridged and no correct table is lost. All 494 move to already-correct. Five
random multi-slot tables (Rva004E1B72, BuffInstance, StrategicHUD::ArmyUnitSwapperMovieClip, Rva002E0A0A,
TeamInQueue) match retail by ledger address in every slot, with slot 0 through the default.
Not landed: `file:tools/vtable_bridge.py` was claimed by yasinschroeder-claudeb2 during this pass. The
patch waits for that claim to clear.
Still bridged, with the slot-0 `??_E` as their only mismatch (325 tables; leads, not tooling artefacts):
- 214: the default `??_GX` has no ledger row. Retail's slot-0 address is rowed under another name, an ICF
  fold or placeholder (`??_7CImage@ATL@@6B@` -> 0x00002926 `??_GRva00002926Element`). This needs a name or
  twin route, not a bridge rule.
- 103: `??_EX` is a plain external, and a real vector deleting destructor is linked. Retail's body there
  needs its `??_E` row (for example `??_7AudioManager@@6BSnapshot@@@` slot 0 -> 0x00051C9A).
- 8: the default is rowed at another address. `??_GImage@Gdiplus` sits at 0x2111 and `??_GBitmap@Gdiplus`
  at 0x1E43, but the Image (0x007BB524) and Bitmap (0x007BB548) tables point the other way. Either the two
  `??_G` rows or the two table names look swapped. This is a naming lead.

**Slot-0 `??_G`/`??_E` names rowed as ICF twins (2026-11-08, seat halilkkaya-lk66, base `c2ca5f6f36`).**
Follows lk65's weak-slot lead (the `tools/vtable_bridge.py` fix itself lands separately). Of the 325 tables
whose only mismatch was slot 0, the 214 "default-unrowed" ones were checked against compiled objects with a
scratch planner: the `??_GX` (or this-adjusting `??_EX` thunk) the table's providing unit emits must have a
matched same-size row already at retail's slot-0 address, equal bytes with relocation fields masked, and
every relocation naming a symbol rowed (code ledger or data-ledger table names) at exactly retail's target,
or itself passing the same test (depth 3; weak externals through their default). Passing symbols were rowed
callee-first with `tools/add_match.py --icf-owner` and `fold-proof=<owner source>`; no source changed.
- Done: 140 twin rows (three commits) for 112 tables. 46 join the `0x00395A19` partition-filter fold
  (four with their `~X` twins at `0x0049C38A`); others include
  CImage@ATL (`0x00002926`), `__Named_exception`, CameraShakerClass, the FXShaderParameterSourceNamespace
  family (`0x001F45C3` via `~` at `0x000E14BD`), the 16-class `0x0007E5EE` empty-base family (base table
  `0x007C6F20`), the iterator, SimpleVec and List/Node templates, ObjectTracker and the
  TerrainTracksRenderObjClass secondary thunk.
- Offline A/B (lk65_ab.py over exit_link's inputs, no link; old = HEAD's rule, new = lk65's weak rule):
  bridged tables with the weak rule 4,557 -> 4,445, slot-0-only mismatches 325 -> 213, already-correct
  1,098 -> 1,210; with HEAD's rule 5,051 -> 5,050. Refusals identical; no table newly bridged or lost.
  The gain needs lk65's fix to land.
- Blocked by claims (planner passed, rows not added): Drawable and Object (`??_GDrawable` 0x00279FFC,
  `??_GObject@@MAE` 0x0029A10F and their `@@WGA`/`@@OGA` thunks; Object held by Burachi-3D, class:Drawable
  reported held), AABox/OBBox/Null3DObjClass (boxrobj.cpp and 0x001811A0-D0, a codex seat),
  fxshadernamespacesas.cpp (ancalgonn-swarm-defects), SpawnArmy.cpp (ancalgonn-swarm-harness),
  TeamUpdateState.cpp (dave-cons4-merge2), AptMapPreview.cpp and Rva0056AC26Constructor.cpp.
- `??_GTerrainTracksRenderObjClass` (0x0008E533) is recorded blocked: with that row added, build.py verifies
  a different W3DTerrainTracks.obj variant (`$L` labels shift by 7) in which Get_Obj_Space_Bounding_Box and
  _Sphere differ; without it the file is 8/8 exact. Its thunk row landed alone.
- Gdiplus (the 8 "default-rowed-elsewhere"): retail proves the two `??_G` rows swapped, not the tables.
  Bitmap's constructors (0x00001368, 0x000013A2) store 0x00BBB548; ~Image (0x000012A3), Clone@Image
  (0x00002639) and the 9-byte Image() (0x00001199, still the placeholder `??0Rva00001199`) store
  0x00BBB524. So 0x007BB524 is Image's table (slot 0 0x00001E43: 36 bytes, ~Image inlined) and 0x007BB548
  is Bitmap's (slot 0 0x00002111: 27 bytes, a call to ~Image). The split sources produce the swapped pair
  (gdiplusbitmap.cpp makes ~Image `__declspec(noinline)`, gdiplusbitmap_dtor.cpp defines it in the class),
  and link order keeps gdiplusbitmap.obj's 27-byte `??_GImage`. Retail's single TU matches MSVC's pattern
  seen at Vector3Randomizer (0x007235D0): `??_GX` inlines ~X, but a derived class's implicit destructor
  calls the base destructor out of line. Not changed: class:Image and gdiplusbitmap_dtor.cpp are held by
  yasinschroeder-claudeb2.
- Other rowed-elsewhere leads: Vector3Randomizer's own table 0x007D5E38 has slot 0 0x00191120 (31 bytes,
  inline empty dtor), rowed as the placeholder `??_GRva00191120` whose `??0Rva00191120` (0x007230E0) is
  Vector3Randomizer's default constructor; the `??_GVector3Randomizer` row at 0x007235D0 is the four derived
  classes' fold. That needs a class fold plus v3_rnd.cpp work. The other four are placeholder shapes, not
  names: 0x008615D4 slot 0 is a float getter (0x00094A94), 0x00862888 has `__purecall` at slot 0 and its
  `??_G` at slot 2, 0x007E6BA4 slot 0 is 0x005D124D, and DebugCmdInterface's 0x007BE7EC carries the
  placeholder alias `??_7Rva006C5930Dtor`.
- Still open in the slot-0 set: 213 tables. Most need a real destructor body at the callee address (no
  same-size row there, e.g. `??1AudioManager` 0x0005109D, `??1W3DStatusCircle` 0x0008E4EC,
  `??1Line3DClass` 0x00166DE0) or are FXParticleSystem module templates (owned by others); 36 not-weak
  FXParticleSystem tables point slot 0 at `__purecall`.

**Shape survey of the still-bridged tables, and 50 cleared by whole-table ICF twins (2026-11-08, seat
halilkkaya-lk67, base `49e50f8ba4`).** Method: lk65's offline A/B (exit_link's own inputs, 17,954
objects, no link; old = HEAD's `tools/vtable_bridge.py`, new = lk65's weak-slot rule), then every
`source_slot_mismatches` entry of the 4,529 tables the new rule still bridges (lk66's 109 tables were then
pending landing) classified by shape. Counts: tables touching the shape / tables where it is the only
shape / slots.
- **Our first copy is shorter than retail's** (missing source slots): 2,666 / 865 / 35,607. In 2,100 of
  them the kept copy has one slot: a destructor-only private view (RvaSmallVtableCtors.cpp 128 tables,
  Rva0024A797Derived.cpp 90, Rva00493DEFDerived.cpp 60, Rva0026E836Derived.cpp 24, Rva00451F45Derived.cpp
  24, AIStateRva0034005DCtor.cpp 23; FXParticleSystem units about 90). By area: GameEngine/Common 1,425,
  GameLogic 659, GameClient 315. Route: the class-header lane (a shared header so the view emits the real
  table); per class, not bulk.
- **Slot name unrowed, retail's target rowed under another name**: plain functions 1,416 tables / 4,383
  slots to a real-named row and 545 / 958 to a placeholder row; `??_E` 654 + 697; adjustor thunks 182.
  The scratch planner (lk66's recursive twin test, run over every slot: the table's providing object
  defines the symbol, its section equals retail's body with relocations masked, a matched same-size row
  owns the address, every relocation is rowed at retail's target or itself twins, depth 3) passes 3,554
  slots, and 402 tables pass in every slot. Of those, 109 were lk66's pending rows, 97 are in excluded
  scopes (FXParticleSystem, Drawable/Object, Null3DObjClass/BoxRenderObj, Rva00577FE2, module units),
  117 need an address others hold (Burachi-3D's 0x0047A699/0x0050B238/0x005CB9FF/0x000D1407 folds;
  class:Keyboard covers 0x000B3FD0 and 0x000D43D0) and 26 a held file; 53 were rowed here.
  Planner failures per slot: symbol not defined in the table's provider 1,511, no matched same-size row at
  the target 1,123 (plus 329 for a callee), a relocation not proven 490, bytes differ 70.
- **`__purecall` in ours**: 777 / 241 / 2,976. Retail's targets are folded trivial defaults (0x000D43D0
  349 slots, 0x000B3FD0 236, 0x0047A69C 152, 0x0047A699 40, 0x0050B238 50): our base views declare pure
  what retail's bases define inline. Route: real default bodies in the shared headers (class-header lane).
- **Name rowed at another address**: 529 / 128 / 997 (placeholder names 122 / 34 / 177). Slot order or
  identity differs between view and retail, or a row is misnamed; per-slot work.
- **No copy at all**: 88 tables, address-named data rows (`_vtbl_00BBB58C` ...) that no object defines.
Survey and planner output: lk67_shapes_head.txt / lk67_plan_head.json in the seat's scratch (not
committed; reproduce with lk65_ab.py plus the classifier described above).

Done: 144 ICF twin rows (`tools/add_match.py --icf-owner`, `fold-proof=<owner source>`, each byte-verified)
from 21 table-providing units, the whole slot set of 50 tables (53 planned): the VectorClass/DynamicVectorClass/
SimpleVecClass template families of MeshLoadContextCtor.cpp, agg_def.cpp, collect.cpp, HAnimComboBFME1.cpp,
FontCharsClassConstructorBFME.cpp, hlod.cpp, DX8MeshRendererClassDtor.cpp, MaterialCollectorDestructor.cpp,
pointgr.cpp, hanim.cpp, Rva007B7280Siblings.cpp; STLport num_get/time_get and basic_streambuf<unsigned short>
(stlport_classic_locale.cpp, FstreamDefaultProtectionNameCtors.cpp); the translator family of
Rva00576C4BDtor.cpp and GameClientDrawableTOC.cpp; RAMFile, RawFileClass, ProcessAnimateWindow and the
Narrow/WideStrLenSource getLength pair (whose two `present-unmatched` markers add_match removed).
Offline A/B with the weak rule: 4,529 -> 4,479 bridged (all 50 tables whose rows landed), already-correct
1,145 -> 1,195; HEAD's rule 5,025 -> 5,022; refusals identical, no table newly bridged or lost. link_check:
all 21 sources LINK with more linked bytes; full gate green. The weak-rule gain needs lk65's fix to land.
- Blocked: `??_GBFME2Encoding1/2MotionChannel` (0x001A47BC): add_match's scoped verification of
  BFME2MotionChannelFactory.cpp refuses `$L573` (scoped funclet lacks a same-source parent EH location);
  `setRenderingMode@TerrainFXShaderParameterSourceNamespace` (0x002E6A93): the only owner is the gen-alias
  `?dup_002e6a93@@YAXXZ`, which check_csv requires retracting first (naming lane). Both are in re_attempts.
- Next leads, cheapest first: (1) plan each slot symbol in its first provider in exit_link's input order
  rather than the table's provider (1,511 slot failures are "not defined in the provider"; lk67_plan2.py
  in scratch does this); (2) the 117 held-address tables once Burachi-3D's fold pass and class:Keyboard
  release; (3) the 594 tables that twins clear only partly, ranked by what blocks the rest (usually one
  short-copy or `__purecall` slot); (4) the destructor-only private views of the six scaffold units above,
  through shared class headers.

**Kept-copy twin pass: 51 tables off the bridge (2026-11-08, seat halilkkaya-lk68, base `195accef7e`).**
lk67's lead (1): lk67_plan2.py plans each slot symbol in its first external provider in exit_link's input
order (`vtable_bridge.first_providers`, the copy the linker keeps) instead of the table's own unit. Run
as is, it had no check that callees also hold in their kept copy, so a second pass re-checks every planned
row there (same size, bytes equal to retail with relocation fields masked, same relocation symbols); all
1,129 planned rows held. Of the 2,225 "not defined in this unit" slots it recovers, the hits were checked
by hand on samples (Clear@VectorClass<ResolutionDescClass> 0x00154A30, ??_GRva004D5795 and its ??1 callee,
??_GDrawable 0x00279FFC, the AABox dtor family 0x001811A0-D0): owner bytes and relocation targets equal.
- Done, three commits, rows only (`tools/add_match.py --icf-owner`, `fold-proof=<owner source>`):
  89 rows clearing 47 tables (dx8wrapper.cpp, MaterialCollector and render2dsentence VectorClass families,
  the FXShaderParameterSourceNamespaceSAS SourceNamespace_* destructors, numpunct/messages<unsigned short>,
  the LivingWorld observer no-op events at 0x0050B238, ??_GObject@@MAE with its OGA thunk); 11 rows clearing
  Drawable's Snapshot table and the AABox/OBBox/Null3DObjClass secondary tables (claims now free); 74 rows
  that leave 57 more tables one slot short. add_match removed two present-unmatched markers
  (DX8Rigid/DX8SkinFVFCategoryContainer::Log in dx8renderer.cpp).
- Offline A/B (lk65_ab.py, old = new = HEAD's `tools/vtable_bridge.py` with the weak rule): bridged
  4,353 -> 4,302, already correct 1,312 -> 1,363, mismatching source slots 46,101 -> 46,030 after the
  partial batch; refusals identical (211); no table newly bridged or lost. link_check: all touched units
  LINK with equal or more bytes, except LivingWorldCampaign.cpp and SpawnArmy.cpp, which already fail at
  plain `195accef7e` (unresolved `??1?$vector@VEnableRegionRecord...` and `?rva00566527@Rva00566527...`,
  duplicate `??0Rva0056616B`, after the 4bae086dd55/8303e0c1b71 split and respell).
- Still clearable but not rowed: 157 tables need addresses or files Burachi-3D holds (0x000B3FD0 and
  0x000D43D0 alone block 139 and 160 of them; also 0x000D1407, 0x004543A9, 0x0047A699, 0x00497805,
  0x004D5B30, 0x005C4AD5, 0x005CB9FF, Rva0056AC26Constructor.cpp, NetCommandMsgCtor.cpp); 98 sit in
  excluded scopes (BehaviorModule/DieModule units 52, FXParticleSystem 29, SpecialAbilityUpdate 9, Coord3D,
  LivingWorldManager, Rva00577FE2). Re-run the planner and lk67_select.py when those release.
- Next leads: (1) 641 slot names that no input defines (private-view phantoms such as `?slot01@State`,
  AIInternalMoveToState and AptValue virtuals); the bridge masks them, the class-header lane fixes them;
  (2) 1,386 slots whose retail target has no matched same-size row (needs the real body, e.g. the
  `??1LaserFXNugget` behind `??_E` at 0x001E1152); (3) placeholders a twin now proves, for the naming lane:
  `??_GRva002793F0` at 0x00279FFC is `??_GDrawable` (its callee is `??1Drawable`), and 0x004CEE78
  `?apply@Rva004CEE78DwordImmSetter` is a fold of `??1NetCommandMsg`. No `tools/vtable_bridge.py` change
  is needed for this lane.

**Lead (3) follow-up (2026-11-08, seat halilkkaya-lk69).**
- `??_GRva002793F0` at 0x00279FFC: done in `dc088913621`. `rename.py class --fold Rva002793F0 --into
  Drawable` refuses because both names row the -0x60 thunk at 0x0027966F, an ICF alias pair the fold does
  not merge. So OpaqueScalarDeletingDtorsB05.cpp's copy was retracted instead: the two rows are
  tombstoned, and the class, its tag constructor, its `/alternatename` and both pins
  (`??1Rva002793F0`, `??_ERva002793F0@@UAEPAXI@Z`) are gone. The Drawable twins in
  DrawableConstructor.cpp now own both addresses. The next real link should take `??_7Drawable@@6BSnapshot@@@`'s
  slot 0 from `??_EDrawable@@WGA@AEPAXI@Z` rather than the placeholder. All four Drawable/B05 units still
  link (link_check).
- 0x004CEE78 `?apply@Rva004CEE78DwordImmSetter@@QAEXXZ`: not done. `class:NetCommandMsg` is held by
  Burachi-3D. The same retraction applies when it releases. Disp0DwordImmSetters.cpp's `apply` stores
  `??_7NetCommandMsg@@6B@` and nothing calls it. `??1NetCommandMsg@@MAE@XZ` (NetGameCommandMsgDtor.cpp,
  fold-proof) already rows the address.

**Lead (1): slot names no input defines (2026-11-08, seat halilkkaya-lk70, base `23b25439bf`).**
Method: lk65_ab.py (old = new = HEAD's `tools/vtable_bridge.py`) over exit_link's inputs, then every
`source_slot_mismatches` name checked with `vtable_bridge.first_providers` over the kept objects and the
runtime archives. 3,262 mismatching names, 1,789 defined nowhere: 1,152 slots are weak `??_E` names
(their default exists; a separate shape) and 1,101 slots / 641 names in 453 tables are plain phantoms
(lk68's 641). Count tables by (address, name): several table names share one retail address.
- Done, four commits: `e08827b2fbd` (Q3MakeBaseB and Rva007F1DE0BaseB define their payload getter
  inline; 2 ICF twin rows at 0x007244B0; 15 tables at 0x008E0FB4), `9870659d694` (the interface slot of
  FakePathfindPortalBehaviour, ShareExperienceBehavior (2 tables), FireWeaponWhenDeadBehavior and
  HordeWorkerAIUpdate declared with the rowed override), `3b3aaba23e7` (`rename.py class --fold
  Rva004BC4FC --into CrateCollide`; CrateCollide.cpp and SalvageCrateCollide.cpp declare
  `~CrateCollide` out of line, or the fold duplicates it), `81b9d9e8a78` (the crate +0x10 tables name
  CrateCollide::onCollide). 19 /alternatename pragmas gone (2,739 -> 2,720).
- Offline A/B before -> after: bridged 4,298 -> 4,278, already correct 1,371 -> 1,391, mismatching
  source slots 46,021 -> 45,993; refusals identical (158); no table newly bridged or lost (the fold
  renames three CrateCollide tables in place). link_check: every touched unit, its consumers and the
  65 CrateCollide sources keep their verdict and bytes.
- Left: 1,074 phantom slots in 575 tables, 120 of them phantom-only. Next leads:
  (1) held: the Contain family's die/payload slots (onDie@OpenContain, createPayloadMember@TransportContain,
  CaveContain, TunnelContain, HordeSiegeEngineContain; 12 tables, class:OpenContain/TransportContain/
  GarrisonContain held by ancalgonn-swarm-defects) and WorkerAIUpdate's DBaseM3 slot;
  (2) class folds before the slot can be spelled: DieModuleDerived.cpp's ten Rva*_B2 tables and
  CreateObjectDie.cpp (excluded DieModule scope), Rva0045D39E -> SlowDeathBehavior (4 tables;
  SlowDeathBehavior.cpp held), the Rva0024A797Grandchildren.cpp E1/E2 tables whose slot names
  OneRingPenaltyUpdate, StructureCollapseUpdate, RubbleRiseUpdate, WallUpgradeUpdate, SpawnUnitBehavior
  (LINK-584 holds those files), the partition filters (Rva00260FD0Filter = PartitionFilterPossibleToAttack,
  Rva0026137EFilter = PartitionFilterPlayer), PropagandaTowerBehavior (0x00481837 rowed under placeholder
  Rva00481837 in GapBodiesS3B.cpp; Rva0048180C's table holds it too);
  (3) retail 0x007CA08C (5 table names: W3DTankDraw, W3DTruckDraw, Rva000CA119, Rva000CAEC6,
  Rva0078B83): slot 0 is 0x000BFB76, rowed `?rva000BFB76@Rva000BFB76Interface@@...`, most likely
  W3DModelDraw's own interface method; name it first;
  (4) AIInternalMoveToState (65 slots, 27 tables): `header_adopt_lane.py adopt` byte-passes
  Rva00342826/3429B9/342B87/342EACCtor.cpp, but adoption alone points their derived tables at
  AIInternalMoveToState's methods where retail (and today's /alternatename) has the derived overrides
  (Rva00342826 is AIMoveOutOfTheWayState by its onEnter row). Name the derived classes first.
  AIStateRva0034005DCtor.cpp refuses on a field-name collision (m_30 vs m_goalLayer);
  AIStateMoveTightenCtors.cpp is held by Burachi-3D;
  (5) the CrateCollide +0x10 tables now match in slot 0 but our copies are one slot long; retail's
  interface has six (0x004BC51B, then 0x0047A699 four times, held by Burachi-3D);
  (6) STLport moneypunct/codecvt/_Locale_impl/_Messages: our STLport units never compile those members
  (retail ICF-folds them); STLport lane.

**Weak `??_E` slots whose default is rowed under another name (2026-11-09, seat halilkkaya-lk71, base
`f445bd6480`).** lk70's separate shape: a slot (0, sometimes 1, 3 or 14) relocates to a weak `??_EX`
whose default `??_GX` exists, but the ledger rows retail's target under another name, so HEAD's weak rule
cannot accept it. Method: lk65_ab.py (old = new = HEAD's `tools/vtable_bridge.py`), then each of the
1,151 such bridged slots classified by the rows at retail's target; the default tested with lk67's
recursive twin test plus lk68's kept-copy check; and every placeholder pair dry-run through
`rename.py class --fold OLD --into X` (332 pairs).
- Target-row shapes (slots): one placeholder `??_GRva*` 357; several placeholders (an ICF fold) 94; a
  real class's `??_G` (an ICF fold, e.g. 0x004A10FD, 0x00184150, 0x004D8507) 293; placeholder and real
  mixed 79; `??_G` plus other names 16; a non-destructor body 312 (e.g. 0x00656C30
  `?bfmeDelTVA@BfmeThingTVA`, 0x00131C40 `?bfmeGo1035G@BfmeG1035`). The default twins retail's body for
  242 slots; 29 tables pass in every slot.
- Done, rows only (`tools/add_match.py --icf-owner`, `fold-proof=<owner source>`, callee first), three
  commits: `2691447a4bd` (6 rows: `??_GRva00261513Filter` at 0x00395A19; ProcessAnimateWindowSpiral and
  SlideFromRight `??1`/`??_G` at 0x005C6317/0x005C5990 and `setMaxDuration` at 0x0047A69C; three tables
  off the bridge); `db850117852` (93 rows: the AI state family at 0x004D8507/0x004D7B93 and the
  TextureMapperClass family at 0x00184150/0x00724510, slot 0 of 49 tables); `9bc256c29c7` (49 rows in 36
  units: the 0x004A10FD `??_GObjectModule` fold, 0x0008FFC4/0x000A43C8, 0x00406B1D, 0x003F7BCC,
  0x00254418/0x004905B0, 0x00508F8C/0x0050B8D6, 0x005B2558 and two more AI states). Only addresses that
  three or more classes' slots reach were taken (genuine folds). The tables of the last two commits stay
  bridged on other shapes: phantom State slots, one-slot private views, and slots at 0x000B3FD0/0x000D43D0.
- Offline A/B before -> after: bridged 4,257 -> 4,254, already correct 1,392 -> 1,395, mismatching
  source slots 45,996 -> 45,899; refusals identical (147); no table newly bridged or lost. link_check:
  every touched unit and the owners' units LINK with equal or more bytes.
- Twin-clean except for held addresses (22 tables): 0x000B3FD0/0x000D43D0 (Burachi-3D) block
  GameClient@SubsystemInterface, WeaponSetUpgradeModuleData, UpgradeCenter, GhostObjectManager,
  Rva00318B5C, Rva004885DE, Animal/Horde/WanderAIUpdateModuleData, ObjectHelperModuleData,
  W3DDebrisDrawModuleData, Darkness/FreezingRainSpecialPowerModuleData, PerTurnStats@LivingWorldScoreKeeper,
  Rva004F599E and AITNGuardInnerState; 0x004D5B30 and NetCommandMsgCtor.cpp block Rva004D5795/57AE/59D1/
  5A30; Rva0056AC26Constructor.cpp blocks Rva0056AC26Base1; 0x0047A699 blocks Rva000A217F. Most of
  their other rows landed in `9bc256c29c7`, so they need only those addresses (plus ElvenWoodSpecialPower.cpp
  and GameClientDrawableTOC.cpp, held). Excluded scopes: Rva00577FE2Base and FXParticleSystem's Rva005641BB.
- Blocked: `??_GBFME2Encoding1/2MotionChannel` (0x001A47BC) still refused by add_match: the `$L573`-`$L575`
  funclet rows name labels the object no longer emits (it emits `$L914`-`$L916`), and standalone
  `tools/eh_verify.py` on BFME2MotionChannelFactory.cpp fails `?Load_BFME2MotionChannel` (0x001A46B4) as
  "unmapped -- never reached from the function", so the next edit of that file meets the EH gate.
- Folds: 107 of 332 pairs pass the dry run, but only 8 would complete a table, and none landed.
  Refusals: a third class names the table 51, OLD installs another table 25, a registered NEW needs
  `--prepared` 22, OLD installs no own table 19, OLD keys a frozen register 30 (hatch 18, dup_defs 11,
  code identity 1), secondary vftable 16, both names have a destructor or constructor row 17.
  - `Rva003E3C39 -> Rva003E3C22` (TransportStatus, 0x00C35B34): verifies 224/224, then link_check fails
    three units. ScriptConditions_evaluateTeamStateIs.cpp's inline constructor COMDAT (byte-equal to
    retail's 0x003E3C22) duplicates RvaSmallVtableCtors.cpp's strong `??0Rva003E3C22`, and that view's
    inline empty destructor makes the kept `??_G` not retail's. Declaring the constructor out of line
    breaks evaluateUnitHasEmptied (retail inlines it). Needs the 0x003E3C22 row in its TU
    (ScriptConditions.cpp, proposed) and the RvaSmallVtableCtors view retired. Reverted; in re_attempts.
  - `Rva001505CD -> FXShaderParameterSourceNamespaceSAS` (0x00BD3A34): verifies 68/68, and
    fxshadernamespacesas.cpp then needs its destructor declared out of line (its implicit 119-byte one
    duplicates retail's 140), which stays exact (105/105). Rva001505CDDtor.cpp's view still emits a
    different class table ([`s0`, `??_E`] against [`??_E`, ResolveBindings]); giving it the real interface
    base fixes the table but breaks the 140-byte destructor (retail reuses one register for the base and
    member vptr stores, so both must name one table). Needs the TU merge into
    FXShaderParameterSourceNamespaceSAS.cpp (approved TU of 0x001505CD and 0x00150A5B). Reverted; in
    re_attempts.
  - `Rva0055133F -> BuddyThreadClass`: BuddyThread.cpp declares both classes; the 170-byte destructor has
    to move into the real class (whose implicit one is 140 bytes).
  - `Rva0041F94A -> Rva0022BD25Subsystem` and `Rva00488D3B -> Rva004885DE`: the tables' other slots need
    0x000B3FD0/0x000D43D0.
  - `Rva004C6CC1` and `Rva00535776`: the placeholder's `??_G` is slot 0 of several classes' tables (an
    ICF of distinct classes), so folding it into one of them would be a naming claim. Tooling lead:
    `rename.py class --fold` accepts one OLD into two to four different NEWs (Rva004318D8, Rva00535776,
    Rva005C47A3, Rva005E57C9, Rva005EA2AB); its third-class check looks only at the one table T.
- Next leads: (1) before any fold, list the objects defining OLD's and NEW's `??0`/`??1`/`??_G` with their
  COMDAT selection: a strong (selection 1) body against an inline (selection 2) one in a view unit is the
  duplicate that stopped both folds above; fix the inline view first. (2) The 22 held tables above when
  their claims clear. (3) The 99 passing folds that leave the table bridged (WallHubBehavior,
  DeletionUpdate, FireSpreadUpdate, the Die/Body/Create/SpecialPower families, AI*State classes) are
  naming progress, one class at a time; their twin rows (58) would only put a second name on one class's
  body, so fold instead. (4) The 312 non-destructor targets are deleting destructors rowed as plain
  methods (naming lane). (5) The rest of the planner's genuine-fold twin rows: AIStateHashCtors0033F2FD.cpp
  50 (held by Burachi-3D), ElvenWoodSpecialPower.cpp 4 (held), BfmeDirtyBaseDerived.cpp 6, and folds
  that only one or two classes reach.

**lk71's EH and fold-check leftovers (2026-11-09, seat halilkkaya-lk72, base `93e2f70268`).**
- EH at 0x001A46B4/0x001A47BC: no regression on master. After a clean `./build.sh`, standalone
  `tools/eh_verify.py` on BFME2MotionChannelFactory.cpp is EXACT for `?Load_BFME2MotionChannel`, so nothing
  needs a baseline. lk71's failure came from a stale object, and add_match refused the twins for another
  reason than the labels. flag_defaults compiles a TU under the flag region that holds most of its matched
  row bytes (`8ed9b443761`, Jonathan; `12559cc15ef` then dropped the file's inert `/O1 /G7`). This file has
  310 B in the /O2 region 0x0018D2A0-0x001B20E4 and 319 B in /O1, so it builds /O1. The two 28 B twins at
  0x001A47BC sit in the /O2 region and raise it to 366 B, which flips the TU to /O2 (checked with
  `flag_defaults._load_source_regions` over the file's rows plus the twins). Under /O2,
  `Load_BFME2MotionChannel` becomes a 319 B inline `fs:[0]` frame; retail's 264 B body is
  `mov eax,handler; call __EH_prolog`. Its EH is then no longer EXACT, so build.py cannot place the funclet
  rows. add_match reverted the rows but left that object in build/match. The renumbered labels are routine:
  `56d13052df7` (StarkillerHDX, ChunkLoadClass.h) moved `$L573`-`$L575` to `$L914`-`$L916`, and a full build
  verifies 20,983 rows past renumbered labels. The twins first need a `reverse/flag_overrides.csv`
  `/O1 /G7` entry. `flag_defaults.py propose` records one only when the rows are present and the `// cl:`
  line carries the flags. The verdict is in re_attempts.
- Fold check: reproduced. With `--dry-run`, HEAD's `rename.py class --fold` passed `Rva00535776` into the
  Profile, StrategicStats and RealTimeStats preferences, `Rva005EA2AB` into AABTreeLinkClass and
  Rva005EA026, `Rva004318D8` into Rva004318FC and Rva0043190E, `Rva005C47A3` into Rva004FA623 and
  Rva005C43CFRegistration, and `Rva005E57C9` into Rva005E569A and Rva005E56C8. Cause: when only destructors
  tie OLD to the table T (the destructor-only route, the inlined-base route, or a destructor's first +0
  store, which an inlined base destructor can supply), no check asked whether OLD's deleting destructor also
  sits in other tables. Retail ICF-folds identical deleting destructors, so 0x00537E60 is slot 0 of
  0x00C68DD8, 0x00C6913C and 0x00C69188. Fix: refuse when a deleting destructor of OLD is a slot of a
  retail table other than T and T's subobject tables, unless a constructor of OLD installs T as its own.
  With the fix all 11 pairs above refuse; the fix's commit adds regression tests to test_rename_fold.py. The
  "would declare class NEW twice" check also missed a class head with `__declspec(novtable)`, so
  `Rva0055133F -> BuddyThreadClass` passed although BuddyThread.cpp defines both classes (the build would
  have refused it later). The fix accepts `__declspec(...)` in the head, and that dry run now refuses.
  Of lk71's 107 passing pairs, 20 refuse under the fix (19 on a shared deleting destructor, 1 on the
  `__declspec` view) and 87 still pass.
  - Unchanged by design: `Rva004C6CC1 -> EvacuateGarrisonSpecialPowerModuleData` still passes. Its `??_G`
    0x004AD538 sits only in 0x00C5F778, which ten classes' constructors install as their own (one ICF
    table). The documented co-owner exception allows that; whether it should refuse too is a maintainer
    call.
  - Held: ancalgonn-swarm-seat6 holds `file:tools/rename.py` (retype route), so the fix waits as a local
    commit on wt_x's branch `lk72-fold-check` until that claim clears.
- lk71's eight table-completing folds: none landed. With the fix, the three preferences folds refuse.
  `Rva0041F94A` and `Rva00488D3B` still need 0x000B3FD0/0x000D43D0 (Burachi-3D). `Rva001505CD` and
  `Rva003E3C39` need the TU merges lk71 described. `Rva004C6CC1` is the co-owner case above.
  `Rva0055133F` first needs BuddyThreadClass's own 170 B destructor (its implicit one is 140 B), and it
  refuses under the fix until then.
