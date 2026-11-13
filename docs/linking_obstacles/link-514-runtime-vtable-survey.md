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
  otherwise 12/13 equal) is refused because PartTheHeavensUpdateCtor.cpp (merged into
  PartTheHeavensUpdate.cpp on 2026-11-09) stores dummies, not a
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

2026-11-09, root seat, table 007F91B0: removed Rva00149E60Set.cpp's strong
g_010956C4 duplicate and rebound the unchanged 36-byte body's store to the
existing PartitionFilterPossibleToAttack compiler table. The current real
deleting destructor, allow and base getPlayerMask providers pass with the
source (59/59 code rows, seven exact EH graphs). Bounded replay removes one
strong refusal with no bridge and the same already-correct table; four-source
LINKS 8,124 is conserved at index c885072a48. This does not clear the broader
partition-filter family or establish an image/runtime result. A byte-exact
real-constructor trial is banked but its naming transition is not landed.
[Detailed scope](../../reverse/attempt_support/possible-attack-filter-table-20261108/README.md).

Published as 264d46e4ff; scoped proof passes after publication. The broad
audit is still INCONCLUSIVE (c885072a48 versus 008c434387), with one old-array
loss candidate through an unread object and zero proven newly unresolved
names. The index's sole user was the repaired source and current Code text
has no uses; unread/directive coverage and next-image confirmation remain.

**Tables freed by Burachi-3D's released claims (2026-11-09, seat halilkkaya-lk73, base `7617427900`).**
Method: lk65_ab.py (old = new = HEAD's `tools/vtable_bridge.py`), lk67_shapes.py, lk68's kept-copy twin
planner, restricted to tables that need 0x000B3FD0, 0x000D43D0, 0x000D1407, 0x004543A9, 0x0047A699,
0x00497805, 0x004D5B30, 0x005C4AD5, 0x005CB9FF or the five files lk68/lk71 listed. 262 tables plan
clean; 143 need a freed key.
- Done, three commits:
  - The lk69 retraction: `?apply@Rva004CEE78DwordImmSetter` (Disp0DwordImmSetters.cpp) is tombstoned and
    its class removed; `??1NetCommandMsg@@MAE@XZ` alone rows 0x004CEE78. No hatch named it.
  - 52 rows (`add_match.py --icf-owner`, `fold-proof=<owner source>`, callees first) take 38 tables off
    the bridge: FileClass, W3DPropBuffer, W3DShadowTexture@HashableClass, SequentialScript,
    GameClient@Snapshot, FireLogicSystem, Rva002A8F24, WeaponSet, Anim2D, TAiData, AI, GhostObjectManager,
    Rva00318B5C, DisplayString, AIGroup, Rva0039AE75, Script, VictorySystem, ArmySummary, CaveSystem,
    RebuildHoleBehavior@BehaviorModuleInterface, five UpgradeMux tables (Base, Delayed, WeaponBonus,
    Castle, ReplaceSelf), AODCrushCollide, Rva004D5795/57AE/59D1/5A30, Rva0056AC26Base1, PerTurnStats,
    Rva004F599E, LivingWorldCampaign, Rva005CF872/5CFA43, DownloadManager. Two FXParticleSystem owners
    were swapped for other matched rows at the same address (0x0030F45F `GameWindow::winGetStatus`,
    0x0047A69C `SubsystemInterfaceList::addSubsystem`). add_match removed three present-unmatched markers
    (present_unmatched 2190 -> 2180 with keys master had already shrunk).
  - 54 genuine-fold rows held since lk71: the AIStateHashCtors0033F2FD.cpp AI states (0x004D7B93 ??1,
    0x004D8507 ??_G; 28 classes reach it) and Darkness/FreezingRainSpecialPowerModuleData (0x004C8AB0,
    0x004C2A84; 5 classes). Slot 0 only; those 27 tables stay bridged on other slots.
- Offline A/B, base -> after: bridged 4,272 -> 4,234, already correct 1,399 -> 1,437, mismatching source
  slots 45,941 -> 45,861; refusals identical (113); no table newly bridged or lost. link_check: every
  touched, owner and sibling unit LINKs before and after with equal or more bytes, except the 7 B
  Disp0DwordImmSetters.cpp double-counted with `??1NetCommandMsg`.
- Slot-position names left (not rowed): 103 of the 143 freed-key tables need 70 rows whose names are
  positional placeholders. `SubsystemInterface` `vslot06/08/12` blocks 40 tables and `ModuleData`
  `slot01/14/16-29` blocks 38; both canonical headers (SubsystemInterface.h, ModuleData.h) carry these
  names themselves, and neither the Zero Hour nor the BFME 1 reference names those slots, so no
  `rename.py function --to-class` move is provable yet. Smaller sets: LivingWorld observers
  `event2_0/2_1/5_1/5_2`, StateMachine `slot09/10`, State `_bfme_state_slot7/16`, DockUpdate
  `slot22/dockSlot16`, CreateModule `slot02`, ActiveBodyModuleData `slot07`, CollideModule `slot02-04`,
  DozerActionState `slot07-16`, HordeContainInterface `slot76/112/136`, ReplaceSelfUpgrade `i1C_N`,
  Rva0086E350Listener `v00/v08`, and placeholder classes Rva0056B126B2, Rva0078D310Host, Rva0056AC26,
  Rva0059EB41. The weak-slot tables lk71 held (GameClient@SubsystemInterface, UpgradeCenter,
  Rva004885DE, Darkness/FreezingRainSpecialPowerModuleData) are in this set.
- Next leads: (1) `?getUpdate@BehaviorModule@@UAEPAVUpdateModuleInterface@@XZ` at 0x000D43D0, kept copy in
  FamilyDeletingDtors_muse-b1dd.cpp, is the only unproven slot of 48 tables (three more also need
  `getDamage`/`getCollide` twins). One row would take them off the bridge, but BehaviorModule units
  were outside this seat's scope; it needs the lead's go-ahead. (2) GameFileClass (`?Delete@GameFileClass`
  at 0x000910FB) and Weapon (`?GetSnapshotName@Weapon` at 0x002CC2F6) plan clean but
  ancalgonn-swarm-defects holds those addresses. (3) Naming the SubsystemInterface and ModuleData slots
  (header lane) would free about 78 tables. (4) About eight clean tables with real names outside the
  freed set (SimpleVecClass<float>, SimpleDynVecClass<float>, DynamicVectorClass<BfmeHandleCX>,
  RebuildHoleBehavior's interface table, BoneFXDamage, DamageModule@ObjectModule,
  LivingWorldBattleListener); read re_attempts first (`setRenderingMode` was withdrawn on a gen-alias
  owner). (5) The single-class ElvenWood destructors (0x004C3905, 0x004C4028, 0x004C4508, ...) are
  folds into their Rva placeholders, not twins.

**The getUpdate default and six named tables (2026-11-09, seat halilkkaya-lk74, base `0dabbd0a8a`).**
Method: a one-pass snapshot of HEAD's `tools/vtable_bridge.py` plan over exit_link's inputs (lk65_ab.py's
plan call without the duplicate old/new run), lk67_shapes.py, lk68's kept-copy twin planner.
- Done, rows only (`tools/add_match.py --icf-owner`, `fold-proof=<owner source>`), two commits:
  - 3 rows, 51 tables: `?getUpdate@BehaviorModule` at 0x000D43D0, kept in FamilyDeletingDtors_muse-b1dd.cpp
    (owner `?ControlBarInput`), plus `getDamage@DamageModule` (BoneFXDamage.cpp) and `getCollide@CollideModule`
    (SquishCollideCtor.cpp) at 0x002533D3 (owner `getDie@DieModule`). The tables are the
    BehaviorModuleInterface tables of BehaviorModule, BodyModule, DieModule, CreateModule, DamageModule,
    BoneFXDamage, SquishCollide, WargBehavior, nine Die classes, 26 Upgrade classes and eight Create classes.
  - 13 rows, 6 tables: SimpleVecClass<float> and SimpleDynVecClass<float> (StreakVectorConstructorsBFME2.cpp),
    DynamicVectorClass<BfmeHandleCX> (4 rows), LivingWorldBattleListener, RebuildHoleBehavior's
    RebuildHoleBehaviorInterface table (4 rows) and BoneFXDamage's primary table (2 rows). Three
    FXParticleSystem owners were swapped for other matched rows at the same address: 0x0047A69C
    `SubsystemInterfaceList::addSubsystem`, 0x0030F45F `GameWindow::winGetStatus`, and 0x001DB0A8
    `FrameDataManager::getQuitFrame`.
- Offline plan, base -> after: bridged 4,234 -> 4,177, already correct 1,437 -> 1,494, mismatching source
  slots 45,858 -> 45,749; refusals identical (110); no table newly bridged or lost. link_check (31 and 24
  units: changed, owner and table-emitting units): every unit that linked still links, with more bytes
  (10,088 -> 10,117 and 23,114 -> 23,306). Three units fail identically before and after:
  BridgeTowerBehavior.cpp and CreateObjectDie.cpp (`??_7BehaviorModule@@6BObjectModule@@@` differs from
  the first copy), and streak.cpp (unresolved `?queryVisible@RenderObjClass`, held class).
- Not rowed (verdicts in re_attempts): `??_GDamageModule` at 0x004B973B, the last slot of
  `??_7DamageModule@@6BObjectModule@@@`, is a body only DamageModule's table reaches, so it needs a fold. The
  fold `Rva004B96CC -> DamageModule` refuses because the `??1DamageModule` ICF-twin row at 0x004B96CC starts
  with an inlined base restore (0x00BEEA7C) while `??0DamageModule` installs 0x00C598E4. The ElvenWood folds
  (Rva004C3905, Rva004C4044 and Rva004C4508 into ElvenWoodSpecialPower, WeaponChangeSpecialPowerModule and
  CloudBreakSpecialPower) pass `--dry-run` but clear no table: each ObjectModule table keeps three or more
  `__purecall` slots. Also left: the BridgeTowerBehavior/RunOffMapBehavior tables (positional `slot13`/`slot35`),
  GameFileClass and Weapon (held by ancalgonn-swarm-defects), setRenderingMode (gen-alias owner only) and
  BFME2Encoding1/2MotionChannel (lk72's flag override).
- Twin-clean tables are now exhausted outside positional slot names (147 tables) and excluded scopes (13).
  Next leads: (1) 37 getUpdate tables stay bridged on slots whose class view lacks the family override:
  15 SpecialPower tables name BehaviorModule's `getSpecialPower`/`slot43`/`slot44`, plus `getCreate` (8),
  `getBody` (6), `getDamage` (4), `getCollide` (4) and `getUpgrade` (3), where retail has the 0x002533D3-shape
  cast; 26 are also table-short. (2) Twelve tables point slot 9 (CashHack/Defector: slot 8) at
  `getUpdate@BehaviorModule` where retail has 0x002533D3: the UpdateModule view itself,
  Siege/Transport/WorkerAIUpdate, FireWeaponWhenDeadBehavior, ClearanceTestingSlowDeathBehavior,
  WeaponModeSpecialPowerUpdate, GiveOrRestoreUpgradeSpecialPower, Rva00481F82 and Rva00589079. Those views
  miss `UpdateModule::getUpdate` (an UpdateModule header fix, outside this lane). (3)
  `??_7BehaviorModule@@6BObjectModule@@@` differs from its first copy and blocks two units. (4) Naming the
  positional SubsystemInterface/ModuleData slots (lk73 lead 3).

**Module-family overrides missing from class views (2026-11-09, seat halilkkaya-lk75, base `83eecb709b`).**
Method: lk74's one-pass snapshot (old = new = HEAD's `tools/vtable_bridge.py`) after every batch, plus
a sweep for tables whose every mismatching slot names `?m@Base@@TAIL` while retail's target is rowed as
`?m@C@@TAIL` (same method and signature in another class: an override the view lacks).
- Done, 18 commits (`ee55ff5b145` .. `9b0806aa60a`):
  - declarations only, in existing views (no rows): `UpdateModule::getUpdate` (UpdateModuleCtor.cpp),
    `BodyModule::getBody` (ActiveBodyConstructor, InactiveBodyCtor), `CollideModule::getCollide`
    (FireWeaponCollide, CrateCollide, SalvageCrateCollide), `CreateModule::getCreate` (Preorder,
    SpecialPower, SupplyCenter Create), AIUpdateInterface's getCollide/getAIUpdateInterface (six views)
    and update/getDisabledTypesToProcess (seven views; AIUpdateInterfaceDestructor.cpp emits a second
    copy of two AIUpdateInterface tables and must agree, or link_check refuses AIUpdateInterfaceCtor.cpp);
  - base swaps: four ActiveBody views onto the registered BodyModuleClass.h, the Siege/Transport
    AIUpdateInterface views onto UpdateModule.h (the +0x10 placeholder XIface2 becomes
    `??_7X@@6BUpdateModule@@@`), ExperienceLevelCreate's ctor unit onto CreateModuleClass.h (which
    retired CreateModule.cpp's `??0ExperienceLevelCreateBase` /alternatename and its pin);
  - rows (`add_match --icf-owner`): 0x00497805, the `X::loadPostProcess() { Base::loadPostProcess(); }`
    fold (0x0058B03E is the bases' own body; several headers had this backwards), for 19 classes
    (9 module units, 8 Upgrade headers, StructureToppleUpdate's present-unmatched ZH body,
    AllowBannerSpawnUpgrade); 0x004DF396 (DISABLEDMASK_ALL) for FireWeaponWhenDeadBehavior,
    PropagandaTowerBehavior, PoisonedBehavior and FiringTracker; 0x004A2D67 (held-only mask) for
    StealthDetectorUpdate and ReplenishUnitsBehavior. Hatches: alternatename -1, pin -1,
    present_unmatched -1.
- Offline plan, base -> after: bridged 4,177 -> 4,124, already correct 1,494 -> 1,547, mismatching
  source slots 45,749 -> 45,675; refusals identical (110); no table newly bridged or lost (two
  Siege/Transport +0x10 names were renamed, and the new names are correct). link_check on every changed
  unit, owner and sibling table emitter: all LINK, bytes equal or higher.
- Not done: the 15 SpecialPowerModule tables (slots 8/43/44): slot 43's body 0x00251C11 takes a float,
  but BehaviorModule.h spells the interface slot `slot43(int)` (a 301-unit header fix first);
  LevelUpUpgrade/WeaponSetUpgrade (class:UpgradeModule held); BoneFXUpdate, DeletionUpdate,
  FireSpreadUpdate, FloatUpdate, ProjectileStreamUpdate, CashHack/DefectorSpecialPower (Zero Hour ports
  whose shim BehaviorModuleInterface is one slot short: 38 shifted slots each); MissileLauncherBuilding,
  StoreObjectsSpecialPower, ArrowStorm, GloriousCharge, RousingSpeech (SpecialAbilityUpdate scope).
- Next leads: (1) ObjectDefectionHelper/ObjectSMCHelper update tables want ObjectHelper's
  DISABLEDMASK_ALL getter (ObjectHelper.h, a shared header); (2) 27 one-slot tables (56 with BehaviorModule
  defaults only) whose slot is a positional `?slotNN@BehaviorModule` at a cast fold (0x004543A9, 0x003730FC, 0x004B4A8C, 0x00485EE9) need
  the slot named first; (3) the Upgrade family's +0x0C and UpgradeMux tables (getDamage 0x0045875F) once
  class:UpgradeModule is free; (4) WorkerAIUpdateCtor.cpp's two-slot private UpdateModuleInterface.

**Upgrade views, Zero Hour interface shims and BehaviorModule's slot names (2026-11-09, seat halilkkaya-lk76,
base `e1463f9bcb`).** Method: lk74's one-pass snapshot (old = new = HEAD's `tools/vtable_bridge.py`) after
every batch; per-slot retail overrides of the 47-slot interface read from every BehaviorModuleInterface
table row, and `call [reg+disp]` slots read from rowed retail callers.
- Done, three commits:
  - `281f685c531`: LevelUpUpgrade.cpp and WeaponSetUpgrade.cpp drop their private UpgradeModule/UpgradeMux
    copies for UpgradeModule.h (WeaponSetUpgrade.cpp includes it before Drawable.h, which selects the
    capitalized Snapshot slots and turned loadPostProcess/xfer into new slots 12-13), declare
    loadPostProcess/xfer (rows at 0x00497805 and 0x004B8710, `--icf-owner`) and LevelUpUpgrade's rowed
    upgradeImplementation. Four tables off: both BehaviorModuleInterface tables (0x00C57328) and both
    +0x18 tables (0x00C58790, now `@@6BUpgradeModuleInterface18@@@`).
  - `26b417439af`: the per-unit shims `reference/shims/bfme2_bonefxupdate` and `bfme2_flammableupdate`
    get the registered 47-slot interface (names and signatures as BehaviorModule.h spells them; the
    seat's scratch `shimfix.py` does the rewrite mechanically); FlammableUpdate::getDamage rowed at the
    0x004543A9 cast. Two tables off: BoneFXUpdate (0x00BEFF90) and FlammableUpdate (0x00C49800).
  - `5bc0d3fbab7`: ObjectDefectionHelper and ObjectSMCHelper declare Zero Hour's DISABLEDMASK_ALL
    getter (rows at 0x004DF396). BFME 2's ObjectHelper does not override the slot (0x00BFBCE4 and the
    Recovery/Repulsor helpers hold 0x00253376), so ObjectHelper.h is untouched. Two tables off.
- Offline plan, base -> after: bridged 4,099 -> 4,091, already correct 1,552 -> 1,560, mismatching
  source slots 45,616 -> 45,489; refusals identical (104); no table newly bridged or lost. link_check on
  every changed unit, owner and sibling emitter: all LINK, bytes equal or higher (FiringTrackerCtor.cpp and
  FireWeaponWhenDeadBehaviorDerived.cpp fail only against the 01:24 census objects of units lk75 changed
  later; with those units included they LINK).
- Blocked:
  - DeletionUpdate, FireSpreadUpdate, FloatUpdate and ProjectileStreamUpdate share
    `reference/shims/update_modules_bfme2/GameLogic/Module/BehaviorModule.h` with 12 more units.
    SlavedUpdate.h (same shim dir) overrides getSlavedUpdateInterface through it (class:SlavedUpdate is
    held through class:Locomotor), and BridgeBehavior.cpp's getBridgeBehaviorInterfaceFromObject calls
    getBridgeBehaviorInterface by name (retail slot 12). The same rewrite fixes the four tables once those
    overrides and calls have names in the registered header (below) or spell slot12()/slot26().
  - CashHack/DefectorSpecialPower compile against the pristine Zero Hour BehaviorModule.h
    (`reference/open-bfme-1/inputs/...`, not editable) with no shim of their own; their tables also need
    slots 43/44, so they wait on the slot names too.
  - LevelUpUpgrade/WeaponSetUpgrade stay bridged on primary slots 0 and 2 and UpgradeMux slots 2/8/10.
    `rename.py class --fold Rva004B3D3B --into LevelUpUpgrade --dry-run` is clean (2 rows in
    FireWeaponWhenDeadBehaviorDerived.cpp), but that unit's view would then emit a second, different
    `??_7LevelUpUpgrade@@6BObjectModule@@@` and a strong `??1LevelUpUpgrade` against the ctor unit's
    implicit one (lk71 lead 1), so that view must adopt UpgradeModule.h first. The name getters
    `Rva004B3D5BNamed`/`Rva004B56ABNamed` qualify for `function --to-class`. UpgradeMux slot 8 needs
    0x000B3FD0 (held); WeaponSet's slots 8/10 are rowed under the placeholder WeaponSetUpgradeSecondary.
  - Twelve simple Upgrade primary tables (Armor, LocomotorSet, DoCommand, Stealth, UnpauseSpecialPower,
    Garrison, ExperienceScalar, MaxHealth, ModelCondition, ReplaceSelf, AttributeModifier,
    RemoveUpgrade) are bridged only on slots 1 and 2: the 0x00497805 fold (as in 6d092563e4e) and
    GetSnapshotName, whose bodies are rowed as non-virtual `?name@X@@QBEPBDXZ`. `rename.py function
    --to-class` refuses a row already in X ("a readable class is a naming decision"), and `--new` needs a
    basis, so they need the naming lane or a rename.py mode for a real class's vftable slot (tooling
    lead). Single-emitter classes to start with: ArmorUpgrade, StealthUpgrade, RemoveUpgradeUpgrade.
- BehaviorModule.h slot names (investigation only; no header edit). Target facts first, donor facts after:
  - slot 12 getBridgeBehaviorInterface: retail getBridgeBehaviorInterfaceFromObject 0x00456556 calls
    `[vtbl+0x30]`; BridgeBehavior overrides 12 (0x004543A9). Donor: Zero Hour BehaviorModule.h:119.
  - slot 13 getBridgeTowerBehaviorInterface: 0x0045880B calls `+0x34`; BridgeTowerBehavior overrides 13.
  - slot 14 getBridgeScaffoldBehaviorInterface: 0x004582F3 calls `+0x38`; Rva00458402 overrides 14.
  - slot 20 getUpdateExitInterface: Object::getObjectExitInterface 0x0028B445 calls `+0x50`; the
    Queue/SpawnPoint ProductionExitUpdate overrides are already rowed under that name.
  - slot 22 getDockUpdateInterface: Object::getDockUpdateInterface 0x0028BCB4 calls `+0x58`;
    SupplyWarehouseDockUpdate overrides 22.
  - slot 28 getProductionUpdateInterface: 0x0049CEFC calls `+0x70`; ProductionUpdate overrides 28.
  - slot 30 getSpawnBehaviorInterface: Object::getSpawnBehaviorInterface 0x0028BCD4 calls `+0x78`;
    SpawnBehavior overrides 30.
  - slot 45 `mapLoadPostProcess(const Dict *)`: four overrides rowed under that name and signature
    (ThreatFinderUpdate 0x003ECE33, named from WorldBuilder; GettingBuiltBehavior 0x004543CA;
    DynamicPortalBehaviour 0x00461284; AISpecialPowerUpdate 0x004B33EB). Two one-slot tables
    (ThreatFinderUpdate, AISpecialPowerUpdate) wait only on this.
  - slot 43 takes a float, not an int: both overrides (SpecialPowerModule 0x00251C11,
    WeaponModeSpecialPowerUpdate 0x00494AC6) are `fld dword [esp+4]` and pass the float to slot 15 of a
    sub-object. No name evidence: keep it positional as `slot43(float)`. Slot 44 (0x00251C24 forwards to
    primary slot 12): no name evidence.
  - Not provable now: 5, 6, 11, 18, 23-27, 29, 31-42, 46 (one overriding class each, no rowed caller).
    The 27 one-slot cast-fold tables lk75 listed sit at slots 6, 11, 14, 20, 25-27, 29, 31, 33, 34, 36,
    37, 40, 41 and 45; slots 14, 20 and 45 have names above.
  - Units: about 920 objects include BehaviorModule.h; 198 emit tables naming `?slot43`/`?slot45`. Each
    rename respells the default row (SupplyTruckAIUpdateCtor.cpp), every view that overrides the slot
    positionally (BridgeBehaviorCtor.cpp `slot12`, BridgeTowerBehavior.cpp `slot13`) and the bridge
    tables: a full-gate edit.
  - rename.py cannot carry it. `function --rva 0x000D43D0 --old ?slot12@BehaviorModule@@UAEPAXXZ --new
    getBridgeBehaviorInterface --basis canonical:zh --evidence <ZH BehaviorModule.h:119> --dry-run`
    refuses: name_evidence.py has no zh-body candidate for a body every NULL getter folds into, and
    `--virtual` keeps the identifier. The slot 43/45 signature changes are outside `function`'s respell.
    The names need the naming lane's inferred basis, or a tooling mode that takes a rowed retail caller
    plus an override as evidence. 0x000D43D0 (the default rows) is also held by ancalgonn-swarm-defects;
    the edit was not made.
- Next leads: (1) a rename.py mode for vftable-proven interface slots, then name slots 12, 13, 14, 20,
  22, 28, 30 and 45 and set slot 43 to float; then rerun the shim rewrite on update_modules_bfme2 (four
  tables) and declare the one-slot overrides (27 tables). (2) The twelve simple Upgrade primary tables
  (fold row plus GetSnapshotName respell). (3) The LevelUp/WeaponSet folds after their
  FireWeaponWhenDeadBehaviorDerived.cpp views adopt UpgradeModule.h. (4) AudioLoopUpgrade's interface
  table (slots 7/10, casts 0x004523A9/0x004543A9) and ReplaceSelfUpgrade's (slot 3, 0x004B4A8C).

**Upgrade folds, slot-1 rows, cast slots and GetSnapshotName moves (2026-11-09, seat halilkkaya-lk77,
base `ab05313adb`).** Method: lk74's one-pass snapshot (old = new = HEAD's `tools/vtable_bridge.py`)
after every batch; lk56's per-class Upgrade header recipe; `rename.py class --fold` and
`function --to-class` (run, not edited); per-unit `??_7` diffs before and after each change.
- Done, 14 commits (`d4a137741a1` .. `43017abced0`):
  - LevelUpUpgrade.h and WeaponSetUpgrade.h over UpgradeModule.h, adopted by the ctor units and by
    FireWeaponWhenDeadBehaviorDerived.cpp, with the folds Rva004B3D3B -> LevelUpUpgrade and
    Rva004B568B -> WeaponSetUpgrade (the scaffold now owns the only strong `??1`, and its four table
    copies equal the ctor units') and `--to-class` of both name getters into GetSnapshotName. This
    was lk76's lead 3; the scaffold already included UpgradeModule.h, and the missing piece was a
    shared per-class header.
  - 0x00497805 `loadPostProcess` rows for eleven simple Upgrade classes (lk76 lead 2, slot 1).
  - `--to-class` GetSnapshotName for the five of those whose getter was still a placeholder
    (Garrison, ExperienceScalar, MaxHealth, ModelCondition, AttributeModifier).
  - Cast-slot overrides rowed as ICF twins (0x004523A9, 0x004543A9, 0x00485EE9, 0x003730FC):
    AudioLoopUpgrade (slots 7/10, lk76 lead 4), PropagandaTowerBehavior, PoisonedBehavior,
    BroadcastStealthUpdate, RadiateFearUpdate, ReplenishUnitsBehavior, AttributeModifierAuraUpdate,
    FireWeaponWhenDamagedBehavior, CritterEmitterUpdate, DamageFilteredCreateObjectDie,
    FakePathfindPortalBehaviour and StructureToppleUpdate (whose ctor unit and
    Rva0024A797Grandchildren.cpp must land together).
- Tables off the bridge: LevelUp and WeaponSet primary, the five GetSnapshotName tables, and 12
  BehaviorModuleInterface tables. Offline plan, base -> after: bridged 4,090 -> 4,067, already correct
  1,561 -> 1,576, mismatching source slots 45,483 -> 45,435; refusals identical (104); nothing newly
  bridged. The four "correct lost" are the deleted placeholder names `??_7Rva004B3D3B`/`Rva004B568B`
  on the shared 0x00C57328/0x00C58790 tables; the LevelUp/WeaponSet names there stay correct.
  link_check: every changed unit, sibling emitter and ICF owner LINKs, bytes equal or higher. The
  scaffold and UpgradeModuleTailDtors.cpp link only together with the Upgrade units rowed after the
  02:17 census (the eight 6d092563e4e class units, WeaponSet, LevelUp, ModuleNameGetters3,
  AllowBannerSpawnUpgradeCtor). Before that census is refreshed, stale index objects report duplicates.
- Blocked (re_attempts rows):
  - Slot 2 of ArmorUpgrade, LocomotorSetUpgrade, DoCommandUpgrade, StealthUpgrade and
    RemoveUpgradeUpgrade: the getters are `?name@X@@QBEPBDXZ` under the real class (hand-named
    `663fb9f2970`, so `revert` has nothing to restore). `function --to-class` refuses ("already a
    member of X" / "a readable name"); `--virtual --access protected` keeps the identifier `name` and
    refuses on the macro view ("no body of class X there declares name to make virtual"); `--new
    GetSnapshotName --basis inferred` refuses ("a real name, not a placeholder"). The naming lane
    serves only placeholders, so no supported route exists.
  - UnpauseSpecialPowerUpgrade slot 2: `--to-class` refuses because the compiled 0x00C57EA8 copy is 13
    slots: `?onCreate@UnpauseSpecialPowerUpgrade@@MAEXXZ` (0x004B54D9) is declared as a new virtual,
    while retail holds it in slot 5 (Module::onObjectCreated). The fix needs that row respelled first.
  - LevelUpUpgrade UpgradeMux slot 2: 0x004B3E7F is rowed as
    `?rva004CE2B0@LevelUpUpgrade@@UAE_NPAVRva00406F9C@@@Z`; the slot needs `wouldUpgrade(const
    BitFlags<128>&) const`, a signature respell no rename mode makes. Slot 8 needs 0x000B3FD0
    (held). WeaponSetUpgrade UpgradeMux 8/10: WeaponSetUpgradeSecondary is readable, and both
    `class --fold` and `--to-class` refuse.
  - ReplaceSelfUpgrade (slot 1 fold, getCreate 0x004B4A8C): FamilyDeletingDtors_muse-b1dd.cpp, a
    second emitter of its tables, is held by ancalgonn-swarm-defects.
  - Not attempted: the DamageModule fold (lk74's note stands), OpenContain's five cast slots (10+
    private views), FireWeaponWhenDeadBehavior/Rva00481F82 (their getUpdate slot needs UpdateModule.h),
    and CostModifier/SpellRechargeModifierUpgrade (folding Rva004B5982/Rva004B5D0B needs headers over
    their private UpgradeModule copies first).
- Next leads: (1) a rename.py mode that respells a readable-class row into the base virtual
  its retail vftable slot proves (identifier plus access, and for 0x004B3E7F the signature), using
  the registered base declaration as evidence. It clears five getter tables and unblocks
  UnpauseSpecialPower and the LevelUp UpgradeMux slot. (2) The CostModifier/SpellRechargeModifier
  header and fold. (3) ReplaceSelfUpgrade once its holder releases it. (4) The placeholder copies at the
  same addresses (Rva0048180C, Rva00499934, Rva004A4214, Rva004A4C19, Rva004839D3, Rva004AB246,
  Rva0049BFB7, Rva004A8091, Rva0045232D in Rva0024A797Grandchildren.cpp) fold into their real classes
  through the same recipe.

**Freed Upgrade slots, FireWeaponWhenDead's casts and OpenContain's interfaces (2026-11-09, seat
halilkkaya-lk78, base `98eb5d8c17`).** Method: lk74's one-pass snapshot (old = new = HEAD's
`tools/vtable_bridge.py`) after every batch; lk75/lk77's override recipe (declare what the view lacks,
row retail's body with `add_match --icf-owner` and `fold-proof=`); per-unit `??_7` and symbol diffs;
lk74_definers to find every emitter of a touched table.
- Done, 8 code commits (`d2e013aae38` .. `9c3bbbbdce7`):
  - LevelUpUpgrade UpgradeMux slot 8: `upgradeRemovalImplementation` in LevelUpUpgrade.h, rowed at
    0x000B3FD0 (both emitters agree).
  - ReplaceSelfUpgrade: the 0x00497805 `loadPostProcess` fold (primary slot 1) and the 0x004B4A8C
    `getCreate` cast (BehaviorModuleInterface slot 3), declared in both emitters (ReplaceSelfUpgrade.cpp,
    FamilyDeletingDtors_muse-b1dd.cpp, which land in one commit).
  - FireWeaponWhenDeadBehavior: `UpdateModule::getUpdate` declared in both private UpdateModule views
    (FireWeaponWhenDeadBehavior.cpp, Rva00589079Derived.cpp; lk75's f271d361784 precedent) plus the
    getDie/getUpgrade casts (0x004523A9, 0x004543A9). Rva00481F82 and Rva00589079 share the scaffold's
    view and gain slot 9 too. Full UpdateModule.h adoption in the scaffold was not taken: it merges the
    separate +0x10 bases, which turns Rva00481F82's alternatename-bound update slot into `__purecall`
    and renames three placeholder tables.
  - OpenContain (only OpenContainCtor.cpp and OpenContainDtorRva00464692.cpp emit its tables; the
    ten-plus derived views do not): the five BehaviorModuleInterface casts (slots 1-4, 7), declarations
    of the rowed loadPostProcess/xfer/onDelete (primary slots 1/3/8), and the +0x28/+0x34/+0x2C
    placeholder bases replaced by the registered DieModuleInterface, CreateModuleInterface and
    DamageModuleInterface (each proven by the getter that returns it and by the retail table's shape;
    onDie was rowed, the seven create/damage overrides are rowed as ICF twins of 0x000B3FD0,
    0x0047A699, 0x0047A69C and 0x000D1407).
- Tables off the bridge: ReplaceSelfUpgrade, FireWeaponWhenDeadBehavior and OpenContain
  BehaviorModuleInterface; OpenContain's die, create and damage tables (now correct under their real
  names); the placeholder `??_7ContainIface34@@6B@`/`??_7ContainIface2C@@6B@` leave the plan. Offline plan,
  base -> after: bridged 4,065 -> 4,057, already correct 1,577 -> 1,582, mismatching source slots
  45,430 -> 45,401; refusals identical (104); nothing newly bridged. The one "correct lost" is the
  deleted placeholder name `??_7ContainIface28@@6B@`; its address 0x00C1C780 keeps the correct real
  name `??_7DieModuleInterface@@6B@`. link_check over the 34 changed, owner and sibling-emitter units
  (with the Upgrade units lk77 rowed after the 05:57 census): all LINK, 23,991 -> 24,167 B. Emitter
  pairs fail alone against stale census objects and must land together (they share each commit).
- Blocked (re_attempts rows in `8dbba505b13`):
  - DamageModule fold (`Rva004B96CC -> DamageModule`): a rename.py false reject. inlined_base_restores
    accepts the old destructor rows, then the own-table loop runs own_table over the existing
    `??1DamageModule` ICF twin at the same 0x004B96CC and reads the same inlined BehaviorModule restore
    (0x00BEEA7C) as a second own table. rename.py is held by ancalgonn-swarm-seat2.
  - ReplaceSelfUpgrade primary slot 2: the name getter 0x004B7084 is the free function
    `?Rva004B7084Get@@YAHXZ`; `function --to-class` refuses ("not a method ... this mode can respell").
  - CostModifier/SpellRechargeModifierUpgrade folds: not attempted. Both constructors (0x004B5A06,
    0x004B5D7D) are byte-for-byte ReplaceSelfUpgrade's 0x004B7045 shape plus `mov byte [esi+0x20],1`,
    so ReplaceSelfUpgrade.cpp's view is the template; but SpellRechargeModifierUpgradeCtor.cpp builds
    hand-array tables (`_s_vtable` ... in data_ledger aliases) and CostModifierUpgrade.cpp's private
    UpgradeModule emits all-`__purecall` copies, so each constructor unit must move onto
    UpgradeModule.h with every slot declared (fold 0x00497805, name getters, the shared xfer
    0x004B5E06, onDelete, onCapture, mux 8/10, the +0x1C CreateModuleInterface slots) before the
    scaffold folds.
- Next leads: (1) rename.py: skip NEW's own ICF-twin destructor row in the fold's own-table test (the
  DamageModule fold), and a `--to-class` route for free-function placeholder getters (ReplaceSelfUpgrade
  slot 2). (2) The CostModifier/SpellRecharge constructor rewrite above. (3) ReplaceSelfUpgrade's and
  CostModifierUpgrade's +0x1C interface is CreateModuleInterface (getCreate returns it; four slots of its
  shape), so the same base swap fixes 0x00C58AB8 once `rva004B70F0` is renamed `onBuildComplete`.
  (4) OpenContain's +0x24 table is CollideModuleInterface (CollideModule.h): slot 0 is rowed as
  `?rva004628D1@Rva004628D1@@UAEXPAVObject@@HH@Z`, which needs a `--to-class OpenContain` respell to
  onCollide first; +0x20 (94 slots) and +0x30 (12) stay placeholders. (5) Rva00481F82 looks like
  TerrainResourceBehavior (TerrainResourceBehavior.cpp owns the data row of its ObjectModule table
  0x00C49408, and the scaffold binds its update slot to `TerrainResourceBehavior::update`); proving and
  folding that identity first lets its getCreate/getDie casts (0x003730FC, 0x004543A9) land under the
  real name.

**Abstract placeholder views in RvaSmallVtableCtors.cpp and lk78's leftovers (2026-11-09, seat
halilkkaya-lk79, base `06c0b727c0`).** Method: lk74's one-pass snapshot (old = new = HEAD's
`tools/vtable_bridge.py`) after every batch; each retail slot word read from the image; per-unit
`??_7` and symbol diffs; `rename.py class --fold` and `function --to-class` dry runs for the
identity routes.
- Done, 4 code commits (`458364fabd5` .. `c889ce74779`), all in RvaSmallVtableCtors.cpp: 17 views
  whose retail table is all `__purecall` (abstract tables retail folds across classes, 1 to 94
  slots, 256 slots in all) now declare retail's slot count of positional pure virtuals instead of an
  invented inline virtual destructor; four two-slot views (Rva0007DFE9, Rva003A538E, Rva005754ED,
  Rva005D1023: slot 0 their own rowed `??_G`, slot 1 `__purecall`) gained the pure slot 1; and
  Rva002D3347's view gained the three pure slots of the Rva002D3556 view (the fold below needs it;
  no count change alone). The pilot was 5 tables (`458364fabd5`), then 12 and 4.
- Tables off the bridge: 21. Offline plan, base -> after: bridged 4,057 -> 4,036, already correct
  1,582 -> 1,603, bridged slots 58,186 -> 57,904, mismatching source slots 45,401 -> 45,120;
  refusals identical (104); nothing newly bridged; no correct table lost. link_check over the unit
  (and, for `c889ce74779`, InlineDtorDeletingDtorsC01.cpp and RadarWindowOverrideCreatePing.cpp):
  all LINK, bytes unchanged (2,958 B for the unit). The changed classes appear in no other unit;
  the only symbol change is 17 unrowed `??_G` bodies leaving the object.
- RvaSmallVtableCtors classification (lk79 snapshot; 149 tables at base, 128 left). The `names`
  evidence is `data_ledger.csv`'s cache of relocation bindings (139 `literal`, 10 `provisional`),
  not a name basis: of the 71 tables that carry a readable co-name, the translator family
  (HotKeyTranslator, HintSpyTranslator, GameClientMessageDispatcher, WindowTranslator,
  UserInputTranslator) refuses the fold because `??1X` at 0x00429191 installs 0x00BDBA74, not the
  bound table; S3Money and PartitionFilterFlammable refuse the same way. Left in the file by slot
  shape: 98 tables hold rows of other classes (slot bodies rowed under other address placeholders or
  ICF-shared bodies: `o`/`o+` 37, `d o+` 35, mixed 26); 23 hold another class's deleting destructor
  in slot 0 and `__purecall` after it; 5 hold own-class rows; Rva005EEE6B and Rva0028AB0D are all
  `__purecall` too (8 and 10 slots) but object.h declares other views of them (Object's +0x6C/+0x70
  bases), so they wait on that shared header.
- Fold dry runs (`rename.py class --fold OLD --into NEW --dry-run`): clean for Rva0007829C ->
  FileClass, Rva003889DF -> GameSpyPeerMessageQueueInterface, Rva005EA1D5 -> UnitCountCollector,
  Rva002D3556 -> Rva002D3347, Rva0059675ABase -> Rva0059667D, Rva003E3C39 -> Rva003E3C22. Not
  applied for the three readable ones: the fold would leave a one-slot private copy of the real class
  in this unit, a second `??_7` beside the correct one, so each needs its full slot list (or the real
  header) in the same commit. Refused: MultiListObjectClass (registered canonical: adopt its header
  first), ObjectTracker, TotalHealthCollector/UnitHealthCollector, LivingWorldPhaseObserver and
  the 0x00CE.... Gen* tables (`a third name for the table`), Rva0020E20C and Rva00285635
  (registered: class-reconciliation commit), Rva004318D8, Rva004E179A, Rva005E9FA4 (ICF-folded
  tables or deleting destructors of distinct classes), Rva005D10D6 (no own table),
  Rva00666E10 (the constructor installs another table).
- Blocked (re_attempts rows in `7acd4922ea7`):
  - Rva002D3556 -> Rva002D3347 fold: rename.py verified it and the plan took the table off
    (4,036 -> 4,035), but link_check then refused RadarWindowOverrideCreatePing.cpp: its inline view's
    `__forceinline` constructor is emitted as a COMDAT `??0`, which after the fold duplicates this
    unit's strong `??0Rva002D3347@@QAE@XZ` row. Retail's 0x002D3CA5 inlines the base, so the view
    must stay inline. Reverted.
  - OpenContain's +0x24 slot 0 (lk78 lead 4): the `--to-class OpenContain --new onCollide` dry run
    needs prepared views (OpenContainCtor.cpp compiles no table matching 0x00C46064); the move keeps
    the placeholder's (Object*, int, int) tail, which cannot override CollideModule.h's
    `onCollide(Object*, const Coord3D*, const Coord3D*)`, and no rename.py route respells `H` to
    `PBVCoord3D@@`; class:OpenContain is held through class:Drawable's footprint
    (ancalgonn-pc-hdr-c). The +0x20/+0x30 tables were not attempted.
  - CostModifier/SpellRechargeModifierUpgrade: not attempted (lk78's plan stands). New finding:
    slot 9 of 0x00C581CC is rowed as `?onCapture@Rva004B5AC0_Primary@@QAIXHPAVPlayer@@0@Z` (a
    __fastcall spelling with a dummy int), so a to-class move cannot reach ObjectModule::onCapture
    until the body is rewritten as thiscall.
- Next leads: (1) the 13 one-slot `o` tables and the 24 `o+` tables are `function --to-class` moves
  of address-named slot bodies (e.g. 0x0037DE70 `?rva0037DE70@Rva0037DE70@@UAEHH@Z` into
  Rva0037DE63, a one-slot table, which the docs' one-slot rule proves alone), each with prepared
  views of this unit and the body's unit. (2) The Rva002D3556 fold, once RadarWindowOverrideCreatePing's
  inline view stops emitting the constructor COMDAT. (3) The 23 "other class's deleting destructor
  plus pure" tables: the two clean placeholder folds above, then the rest as their third names
  clear. (4) Tooling: rename.py's fold check could compile-test the folded unit set for duplicate
  strong/COMDAT definitions (link_check found what its own gates passed); and a `--to-class`
  parameter respell proven by a registered header's declaration (OpenContain onCollide).

**One- and three-slot placeholder tables in RvaSmallVtableCtors.cpp, and the Rva0024A797 UpdateModule family
(2026-11-09, seat halilkkaya-lk80, base `a8efeedc18e`).** Method: lk74's one-pass snapshot (old = new = HEAD's
`tools/vtable_bridge.py`) after every batch; `rename.py function --to-class` with prepared views (and
`--also` when no slot of the table resolved yet); per-object `??_7` and symbol diffs; `tu_skeleton.py --split
--dry-run` for the Derived.cpp destructors.
- Done, 9 code commits (`16cf6c36a78` .. `b0aa71bbba0`): each table's constructor view in
  RvaSmallVtableCtors.cpp now declares retail's slots instead of an invented inline virtual destructor, and
  each slot body is respelled into the constructor's class:
  - one-slot tables (the docs' one-slot rule proves each alone): Rva0020E394 (0x0020E39D,
    VslotSmallBodiesAB.cpp), Rva003F82E2 (0x003F82F4, VslotSmallBodiesAG.cpp), Rva00545D43 (0x00545B72
    `shouldExit`, VslotSmallBodiesF.cpp), Rva002B29F8 (0x002B89BB) and Rva002B29D8 (0x002BA392 `visit`), the
    last two also renaming LivingWorldLogic.cpp's inline visitor views (their inline constructors take a typed
    pointer, so the COMDAT `??0` cannot collide with the strong `(void *)` row);
  - three-slot "+4 payload" tables (`--also`): Rva002AAD9C (3 forwarders, VslotMemberForwarders.cpp),
    Rva003FC428 (VslotMemberForwarders.cpp + Rva003FD02EWrite.cpp), Rva00222A19 (VtableSlotBodiesR3.cpp,
    VslotMemberForwarders.cpp, VslotSmallBodiesR.cpp), Rva0052787E (GapBodiesGE28.cpp, VslotSmallBodiesAP.cpp,
    Bfme/Rva00527827Constructor.cpp).
- Tables off the bridge: 9. Offline plan, base -> after: bridged 4,034 -> 4,025, already correct 1,603 ->
  1,610, bridged slots 57,886 -> 57,869, mismatching source slots 45,072 -> 45,055; refusals identical (86);
  nothing newly bridged. The plan lists two "correct lost" names, `??_7Rva002B89BB@@6B@` and
  `??_7Rva002BA392ArmyVisitor@@6B@`: these are LivingWorldLogic.cpp's second names for 0x00BFE004 and
  0x00BFE000, deleted by the renames; both addresses keep a correct table under the constructor's name
  (`??_7Rva002B29F8@@6B@`, `??_7Rva002B29D8@@6B@`), so no correct table is lost. link_check over
  RvaSmallVtableCtors.cpp, every body unit and every unit storing a table by name (AITNGuard.cpp,
  Rva003F830F.cpp, Rva003FCD04Finish.cpp, Rva00222C93Concat.cpp, Rva0052798FConcat.cpp,
  LivingWorldRegionManagerUpdateBattleMarkers.cpp, W3DVideoBuffer.cpp): all LINK, bytes unchanged.
- Blocked (re_attempts rows in `5c37881ba5a`):
  - Rva0037DE63 (0x0037DE70, CarryoverUnit.cpp): link_check refuses a duplicate `??0Rva0037DE63@@QAE@XZ`.
    The visitor's inline constructor takes no argument, so its ANY COMDAT (MSVC 7.1 emits every referenced
    inline function, even when every call is inlined) has the strong `/Gy` row's name. The same trap stops
    lk79's two clean folds: FadeInTextRender.obj emits `??0Rva0059675ABase@@QAE@XZ` (implicit base
    constructor) and ScriptConditions_evaluateTeamStateIs.obj emits `??0Rva003E3C39@@QAE@XZ` (the
    TransportStatus view), each a duplicate of the target's strong row after the fold.
  - Rva0032A3C6 (0x0032AF9C, 0x0032AFCC, 0x0032AFA4): the prepared SidesList.cpp does not compile. Its
    ReaderB0032AF02 view stores the table through `extern "C" __identifier("??_7Rva0032A3C6@@6B@")`, probably
    clashing with the polymorphic class in the same TU. Rewrite that reader onto the class first.
  - Rva002AAD77 and Rva0059B060 (same three-slot shape): one slot body each lives in VslotSmallBodiesAI.cpp,
    held by ancalgonn-pc-bridge.
  - Rva0056AC9C: Rva0056AC26Constructor.cpp's visitor carries two `present-unmatched` markers keyed to
    its class name and derives from PendingBattleVisitor. Rva005CDCDC: Rva005CDDA4Ctor.cpp spells the
    body's mangled name in a counted `/alternatename`. Rva005EA1D5 -> UnitCountCollector: `class --fold`
    takes no prepared view, and the fold alone leaves a one-slot `??_E` copy beside the correct
    `??_7UnitCountCollector@@6B@` of StrategicInGameUIDynamicAutoResolveDialogImpl.cpp.
- Rva0024A797 family classification (lk80 snapshot):
  - Rva0024A797Derived.cpp: 30 classes, one 25-byte destructor row and one `??_G` each, all written against a
    private `UpdateModule` (destructor only, a private copy of the registered class), `MiBase1` and a per-class
    `_B2`. Their three tables are retail's ObjectModule (+0), BehaviorModuleInterface (+0x0C, the shared
    0x007EFF90) and UpdateModuleInterface (+0x10) tables. 11 readable classes: AssistedTargetingUpdate,
    AutoDepositUpdate, AutoFindHealingUpdate, BuildingBehavior, DemoTrapUpdate, EntEnragedUpdate,
    HeightDieUpdate, ObjectHelper, OathbreakersFadeAwayBehavior, PickupStuffUpdate and StealthUpdate (the only
    one registered: StealthUpdate.h). 19 are `Rva...` placeholders. 13 destructors have an approved TU (the 11
    named ones plus Rva0033EEC9 -> ProjectileStreamUpdate.cpp and Rva004A3F8B -> HijackerUpdate.cpp). The other
    17 (34 rows) have none.
    ObjectHelper's TU (Helper/ObjectHelper.cpp) has no file yet. Six ctor units already emit the
    canonical tables. Five of them include UpdateModule.h: AutoFindHealingUpdate.cpp, DemoTrapUpdate.cpp,
    EntEnragedUpdate.cpp, OathbreakersFadeAwayBehavior.cpp and PickupStuffUpdate.cpp. The sixth,
    Object.cpp, emits ObjectHelper's. In these units only the `6BObjectModule@@@` copy is bridged (15 of
    retail's 22 slots for AutoFindHealingUpdate), plus OathbreakersFadeAwayBehavior's `6B@`. Their
    `6BBehaviorModuleInterface@@@` and `6B@` (UpdateModuleInterface) copies are correct.
  - Rva0024A797Grandchildren.cpp: 21 classes one level deeper (a middle with three vptrs plus 1 or 2 own
    bases), 36 rows with no approved TU. Only BridgeScaffoldBehavior, StructureToppleUpdate and
    WallUpgradeUpdate have one.
  - Route tried: `tu_skeleton.py --split Rva0024A797Derived.cpp --for <approved TU> --dry-run`. That moves the
    destructor into the class's approved ctor TU, where it stores the canonical tables; the TU already
    emits them, so the class's three private bridged tables would leave. Each carved destructor
    byte-matches beside its TU ("alone: 2/2"), but every split is refused:
    - the link guard, for AutoFindHealingUpdate, AssistedTargetingUpdate, DemoTrapUpdate, EntEnragedUpdate,
      PickupStuffUpdate and OathbreakersFadeAwayBehavior: `selected implementation changes for ??1X@@UAE@XZ;
      outside consumers lose provider ??_7X@@6BMiBase1@@@; selected implementation changes for
      ??_7X@@6BMiBase1@@@`. Only Derived.obj (the carved destructor itself) references the private tables.
      This is recorded as a false-reject candidate (`5c37881ba5a`);
    - the link guard, for BuildingBehavior: `moved selected COMDAT ??1BuildingBehavior@@UAE@XZ lacks matching
      private/weak-free context` (and its `_B2` table);
    - `bytes` for StealthUpdate and Rva004A3F8B (HijackerUpdate.cpp);
    - compile (C2600: the TU's class view declares no destructor) for HeightDieUpdate, AutoDepositUpdate and
      Rva0033EEC9 (ProjectileStreamUpdate.cpp). HeightDieUpdate.cpp and AutoDepositUpdate.cpp hold no class
      view with tables at all.
    The in-place route (Derived.cpp onto UpdateModule.h) has to replace the private `UpdateModule` for all 30
    classes in one change, with every override that the six ctor units declare, so the COMDAT copies agree.
    Not attempted.
- Next leads: (1) tooling: `tu_skeleton.py` `outside_failures` should test whether the name is still
  referenced after the split (the census graph counts the cohort's own references). It should also accept a
  strong -> `/Gy` COMDAT move of byte-identical code whose relocations reach the same ledger addresses. That
  unblocks six Derived.cpp destructors (18 tables). (2) The COMDAT-constructor trap (Rva0037DE63,
  Rva0059667D, Rva003E3C22, lk79's Rva002D3556): move the strong constructor row into the approved TU of the
  unit that inlines it, so the inline definition is the row's provider. (3) Reconcile HeightDieUpdate.cpp,
  AutoDepositUpdate.cpp and ProjectileStreamUpdate.cpp with class views on UpdateModule.h that declare the
  destructor. (4) SidesList's reader view, then Rva0032A3C6. Rva002AAD77/Rva0059B060 once VslotSmallBodiesAI.cpp
  is free.

**The split link guard's false reject, fixed; the Rva0024A797Derived.cpp splits wait on a claim
(2026-11-09, seat halilkkaya-lk81, base `96b069b35c`).** Method: `tu_skeleton.py --split ... --dry-run
--no-claim`, with a temporary state dump of `outside_failures` (removed before the commit), the census
index's `touches`, and per-section COFF reads of the before and after objects.
- Guard verdict: a false reject, for both messages (lk80's `5c37881ba5a` row on 0x0049506E).
  - `outside consumers lose provider` for the private tables. AutoFindHealingUpdate's three private tables
    (`6BUpdateModule@@@`, `6BMiBase1@@@`, `6BRva0049506E_B2@@@`; the reason string shows only the first
    three failures) are defined and touched only by Rva0024A797Derived.obj. The residual neither defines
    nor references them, and no alias or ledger row names them. The fetched index (`d9f0e4778f`,
    `--update-index`) has no per-object reference contributions. So `SplitLinkGuard.view` keeps the
    aggregate graph, which still counts the carved destructor's own references.
  - `selected implementation changes` for `??1AutoFindHealingUpdate@@UAE@XZ`. Its bytes are identical
    before and after. Its four relocations sit at the same offsets with the same types. The three DIR32
    stores move from the private tables to the TU's `6BObjectModule@@@`, `6BBehaviorModuleInterface@@@` and
    `6B@` (the constructor's tables), and the tail jump to `??1UpdateModule@@UAE@XZ` is unchanged.
    RetailTruth judges both copies `unknown`, so "both ok" could never pass. Only Derived.obj and
    AutoFindHealingUpdate.obj (both replaced by the split) touch the name.
  - lk80's "strong (no /Gy) -> /Gy COMDAT" reading was wrong: both copies are COMDATs (digests
    `516b362fcc27` -> `4bb978049094`); only the relocation targets differ.
- Fix `5a28dc34f87` (Verifier-Change). It reuses the merge guard's touches rule, `LinkGuard.referenced_outside`.
  - A lost provider is refused only when something still reaches the name: an object outside the
    replaced ones, the split's new objects, an alias, or a ledger owner.
  - A changed selected implementation is waived only in two cases. Either the name has no definition left
    and no such referrer. Or no outside object or alias reaches it, its one definition after the split is
    its ledger owner's object, and that copy is not proven wrong.
  - Five SplitLinkGuardTests cover both directions (the two accept cases fail on the old guard). The
    tu_skeleton suites plus test_gate_exploits.py: 570 passed, 5 skipped.
- Dry-runs with the fix: AutoFindHealingUpdate, AssistedTargetingUpdate, DemoTrapUpdate (GameLogic/Object/
  Update/), EntEnragedUpdate, PickupStuffUpdate and OathbreakersFadeAwayBehavior (Common/) report "alone:
  2/2", "accepted: [TU, Rva0024A797Derived.cpp]", "rejected: {}".
- Splits done: none, so no tables have left the bridge yet (expected: 18, three private tables per class).
  Rva0024A797Derived.cpp lies in ancalgonn-pc-hdr-c's `class:StealthUpdate` scope (`claims.py claim
  --dry-run file:Code/GameEngine/Source/Common/Rva0024A797Derived.cpp` -> held by class:StealthUpdate). The
  C2600 reconciliations are held too: `class:HeightDieUpdate` and `class:AutoDepositUpdate` (hdr-a's
  class:AIGuardMachine and hdr-c), and `class:Rva0033EEC9` (hdr-c).
- Still refused: BuildingBehavior -> Common/BuildingBehavior.cpp (the tu_map's GameLogic/Object/Behavior/
  path is only proposed: "no row of that file is approved for that TU"). The refusal is `moved selected
  COMDAT ??1BuildingBehavior@@UAE@XZ lacks matching private/weak-free context; moved selected COMDAT
  ??_7BuildingBehavior@@6BRva004561A2_B2@@@ lacks matching private/weak-free context`. That is the
  moved-copy context check, which this fix does not change.
- Next leads:
  1. When the StealthUpdate claim clears, run `tu_skeleton.py --split
     Code/GameEngine/Source/Common/Rva0024A797Derived.cpp --for <TU>` for the six TUs above, one class per
     commit. Verify each per docs/consolidation.md, and run lk74_snap/lk74_cmp (expect 3 tables off per
     class).
  2. Tooling: `SplitLinkGuard.view` never rebuilds the reference graph from per-object contributions, as
     `LinkGuard.view` does. The published index carries none, so both guards rely on the touches fallback.
  3. BuildingBehavior's moved-copy context.
  4. The three C2600 TU views (lk80 lead 3), once their class scopes are free.

2026-11-09, 8615D4 float-slot investigation: the served Rva00283081Dtor
file remains strict 3/3 (84B destructor, 28B deleting wrapper, 10B handler).
A private nonvirtual-destructor/virtual-getter hypothesis emits the correct
4B table and matches the native destructor and float getter, but loses
natural deleting-wrapper emission here. No supported UAE-to-QAE family
route carries the destructor/G/EH identities; no live source is changed.
Neither deleting address appears as an aligned .rdata/.data pointer word,
which supports but does not establish that hypothesis. Real delete callers,
base/derived identity and legitimate wrapper ownership need investigation
before a separately reviewed tooling family and all-emitter reconciliation.
[Native/private proof and prerequisites](../../reverse/attempt_support/ai-stat-float-table-20261109/README.md).

2026-11-09, timeline 8675DC partial override recovery: Rva005202C8 now
implements the native slot3 draw and slot4 tooltip return-one bodies.
Both six-byte methods are verified ICF owners with explicit fold proofs;
no new pins or unique bytes. All existing object code/helpers and other
data are unchanged; the 44-byte table changes only those two referents.
Normal 138 code/one data, literals/floats/imports and fourteen EXACT EH
graphs pass; current scoped LINKS predicts 10,032 to 10,044. The native
table remains 56B and other overrides/tail slots still need class-owner
and container-view reconciliation. Input/factory targets held by others
were not touched. No bridge retirement or actual image result is claimed.
[Native words, complete object comparison and remaining scope](../../reverse/attempt_support/apt-timeline-window-slots-20261109/README.md).

Published as 7a26bac182 on attempt one in 52.3 seconds; post-publication
proof passes and all six claims release. Broader audit is INCONCLUSIVE at
717b70f4ab/base 96d5aca753 for this source's missing wider-view receipt.
Its own link_check verdict was clean and read before pushing. Remaining
table/class work and next-census/image selection are still unverified.

2026-11-09, LocalFile-derived 87AAE0: the 18-byte constructor now emits
its table naturally through the existing LocalFile interface. The derived
destructor view adopts that interface too, making both compiler copies
the full native 72B/18 slots. The strong array, unused base alias/pin and
an unused five-byte helper are removed; the explicit data owner transfers
at the same range. Normal 77 code/one data, 22 imports and seven EXACT
EH graphs pass. Own link_check preserves four LINKS/3,235 bytes. A bounded
four-provider replay changes one 18-slot bridge plus one strong refusal
to zero and one already-correct table; global census/image selection is
still pending. Original names and the common hierarchy remain unrecovered
partial views. The full cache refresh was held back after the normal gate
caught an unrelated retired name from stale objects; explicit data_rows
owns the repaired table. No foreign cache change is published.
[Complete slot, object, ownership and cache audits](../../reverse/attempt_support/local-file-derived-table-20261109/README.md).

Measured LocalFile confirmation: real-link run42624991783 at 1a6707e43c9
contains 5980fa928f. Its 0087AAE0 record is already correct over18slots/72B,
with no bridge or strong refusal; run42616556172 still needed the bridge
and refused the old array. Overall28unresolved/0duplicates/noimage remain.
This clears the scoped table-input gap, not full-image/gameplay requirements.

Published as 5980fa928f, first attempt in 36.7 seconds; four strict
providers, new-variant checks and normal hooks pass, as does post-push
proof. Broader selection remains INCONCLUSIVE: AIBuildable.cpp lacks a
current receipt at index 717b70f4ab/base 7a26bac182. No global image gain
is inferred from the bounded table result.

**The split route over the Derived grab-bags: 2 clean of 71, the moved-copy context check blocks 29
(2026-11-09, seat halilkkaya-lk82, base `edbf37dac3`).** Method: `tu_skeleton.py --split FILE` lists each
grab-bag's approved TUs (the map rebuilt in memory), then `--split FILE --for TU --dry-run --no-claim` per
pair; lk74_snap/lk74_cmp (old = new = HEAD's `vtable_bridge.py`) before and after each split.
- Survey of the nine named files (held and walled files excluded): 38 approved destructor pairs, all "alone:
  N/N" (the carved rows match beside the TU), 1 clean, 37 refused:
  - 18: `moved selected COMDAT X lacks matching private/weak-free context` (HealCrateCollide, GiantBirdSlowDeath,
    ten Rva00493DEF SpecialPower classes, SupplyCenter/SpecialPower/Preorder/LockWeapon/InheritUpgradeCreate,
    AssaultTransportAIUpdate);
  - 11 compile: the carved body or class is written against the grab-bag's private view (C2011 against the
    TU's real headers, C2504 base undefined, C2373 against an `extern "C" __identifier` vftable declaration,
    C2065 private members `m_extra03E4`/`m_extra0050`, C2600 for AISpellBookTreeKiller);
  - 3 link, the receiving AIUpdate TU views are incomplete: the destructor makes the TU emit its tables, whose
    slots are undefined (Animal/Siege/TransportAIUpdate: `new unresolved GetSnapshotName/...`);
  - 3 `bytes` from the merge verifier (WanderAIUpdate, ShipSlowDeathBehavior, UnitCrateCollide);
  - 2 "split it first": StructureToppleUpdate.cpp holds 0x001814D0 (`__uninitialized_fill_n<AngleFXInfo>`,
    mapped to dx8fvf.cpp), DefectorSpecialPower.cpp an overridable.cpp row.
  - Held: Rva0024A797Derived.cpp (class:StealthUpdate, hdr-c), Rva004D759CDerived.cpp (class:AIGuardMachine,
    hdr-a, until 13:14 UTC), ElvenWoodSpecialPower.cpp (class:ModuleData, hdr-b). No approved TU: 120 rows
    (Grandchildren 36, Rva005EE30C 44, Rva0024A797Derived 34, Rva004B8CDE 2, Rva00493DEF 2, Rva004D759C 12).
  - Rva004D759CDerived.cpp once free (7 pairs, all refused): moved-copy context for AIDockMachine,
    SupplyTruckStateMachine and TurretStateMachine (real names, so the table names stay the same and the copy
    digest is unchanged), `bytes` for AIGuard/AIGuardRetaliate/AITNGuardMachine, and AIStates.cpp holds rows
    of three state TUs (split it first).
- The 30 other Derived files (not in the brief): 26 free pairs, 1 clean, 25 refused (8 moved-copy context, 8
  compile, 6 bytes, 1 "split it first", 1 `selected implementation changes for ??1CrateCollide@@UAE@XZ`, which
  the six crate destructors tail-call from outside, so the guard is right). Rva00145000Derived.cpp is not mixed:
  every row is dx8renderer.cpp's (`use --merge`). Held: the AI tactic family (hdr-a), SupplyWarehouseDockUpdate
  (class:AIGuardMachine), PillageModule (class:BodyModule).
- Splits done:
  - `faa28ef43ee` Rva004BC4FCDerived.cpp -> SalvageCrateCollide.cpp (0x004BD207 and its ??_G). Inside the TU the
    class derives from the TU's CrateCollide view, so the destructor stores `??_7Rva004BD207@@6B@`,
    `6BBehaviorModuleInterface@@@` and `6BObjectModule@@@` instead of the three private names. Bridge: 3,998 ->
    3,997 tables, 57,714 -> 57,667 slots, already correct 1,637 -> 1,638 (0x0085A040), mismatching source slots
    44,717 -> 44,663, refusals identical, no correct table lost. 0x0085A9A8 and 0x0085A9C0 stay bridged under the
    new names because the class keeps its placeholder name (its ??_G is slot 0 of SalvageCrateCollide's
    0x00C5A9C0).
  - `95e87db74bd` Rva0055B0CCDerived.cpp -> AIUpgrade.cpp (0x0059734B). Bridge unchanged: `??_7AIUpgrade@@6B@`
    was already AIUpgrade.cpp's copy. Both: build exact, find_declared_unmatched clean, link_check LINKS for both
    units and every unit spelling the class, scoped DIR32 OK, no initializer or .bss change.
- Tooling compatibility audit (`edbf37dac3..HEAD`): no path added, renamed or deleted; the tool repointed
  functions.csv and tu_map.csv (3 rows) and the doxygen list. body_owners.csv, the code-identity and data-check
  baselines hold none of the moved RVAs; the header queue's SalvageCrateCollide.cpp entry (Player) is untouched;
  Rva004BC4FCDerived.cpp keeps its one counted `/alternatename`; the gen-uw pin at 0x0059734B is address-keyed;
  no tools/, .githooks/ or .github/ reference names either grab-bag.
- Tooling lead (false-reject candidate, re_log row on 0x004C2656): the moved-copy branch of
  `SplitLinkGuard` refuses whenever a changed object defines a relocation referent. A placeholder class moves
  whole (destructor, ??_G, private tables, byte-identical, same copy digest), so its referents are always defined
  by the replaced objects and the split is always refused, even when no source outside the grab-bag spells the
  class (Rva004C2656: only CashHackSpecialPower.cpp's tu-skeleton comments). lk81's
  `referenced_outside`/`own_row` waiver covers only the `selected implementation changes` branch; the same
  test (no outside referrer, one definition after the split in the ledger owner's object, copy not proven wrong)
  is not enough: an in-memory probe (tools/ untouched, its split plan deleted) waived the destructor but still
  refused `??_7Rva004C2656@@6BRva004C2656_B2@@@`, which has no ledger owner. Waiving on "no outside referrer,
  one definition after the split, not proven wrong" made the CashHack dry run pass ("accepted: [TU, residual]",
  "rejected: {}"); the 28 other pairs refused this way were not probed. A class whose table names change in
  the TU (lk81's six, SalvageCrateCollide) takes the `selected implementation changes` branch instead, which
  is why those pass; a real name whose tables keep their names (AIDockMachine, TurretStateMachine) does not.
- Next leads: (1) the moved-copy waiver above (tooling seat). (2) Fold Rva004BD207 into SalvageCrateCollide:
  `rename.py class --fold Rva004BD207 --into SalvageCrateCollide --dry-run` refuses because the unit now
  declares both views (`reconcile the two views in that unit first`), and the TU's SalvageCrateCollide view
  declares no destructor (the compiler emits an unrowed `??1SalvageCrateCollide@@UAE@XZ`); a fold that accepts
  a prepared unit would turn 0x0085A9A8/0x0085A9C0 correct. (3) lk81's six Rva0024A797Derived.cpp splits once
  class:StealthUpdate is free. (4) Rva00145000Derived.cpp -> dx8renderer.cpp is a `--merge` candidate, but
  the merge dry run is blocked: dx8renderer.cpp holds rows of another TU (split it first).

**The moved-copy split guard, fixed: 19 of lk82's 29 pairs clean, ten split (2026-11-09, seat halilkkaya-lk83,
base `4eb5ed5d3d`).** Method: an in-memory probe of `SplitLinkGuard.outside_failures` printing each moved-copy
refusal's referrers, definers, contexts and weak pairs; lk74_snap/lk74_cmp (old = new = HEAD's `vtable_bridge.py`)
before the first split, after three, six and ten.
- Guard verdict: a false reject for copies that nothing outside the split reaches; right for the rest.
  - The moved-copy branch proves a moved copy through its raw relocation context, which exists only for a
    selected-ANY COMDAT whose relocations all name undefined externals. A NODUPLICATES function never has one,
    and neither does a table that reaches a definition of its own object, so a class moved whole was always
    refused. CashHack, for example: `??1Rva004C2656@@UAE@XZ` (digest 0563fd409377) and
    `??_7Rva004C2656@@6BRva004C2656_B2@@@` (73a32fa98144) move unchanged, no object outside the two replaced
    ones touches them, and the TU's object is their only definer after the split.
  - Fix `963272c54a1` (Verifier-Change): the branch is waived when no object or alias outside the replaced
    ones reaches the copy (`referenced_outside(..., owned=False)`); the destination's object is its only
    definer and its holder; no ledger row places it elsewhere; it is not proven wrong; and every weak slot
    its section reaches keeps its route. Byte identity (same digest) stays the branch's precondition.
  - Four new SplitLinkGuardTests: the whole-class move is accepted, and both refusal directions are kept
    (an outside reference, alias or copy, a second definer, a ledger row elsewhere, changed bytes, a proven-wrong
    copy, and a weak slot reached, aliased or re-defaulted). Removing any one waiver condition fails a test.
    The tu_skeleton suites plus test_gate_exploits.py: 574 passed, 5 skipped.
- The 29 pairs, re-run as dry runs:
  - 19 clean: nine Rva00493DEF SpecialPowers (CashHack, GrabPassenger, UntamedAllegiance, PlayerUpgrade,
    PlayerHeal, Devastate, SplitHorde, Repair, CombineHorde), HealCrate, GiantBirdSlowDeath,
    LockWeapon/SpecialPower/SupplyCenterCreate, AssaultTransportAIUpdate, StructureBody, DelayedDeathBody, AIDock,
    SupplyTruckAIUpdate.
  - 8 still refused by the moved-copy check, correctly; each has a real outside referrer:
    - a sibling constructor unit that stores the table: StopSpecialPower, DetachableRiderBody,
      HordeTransportContainDamage, TurretAI (TurretStateMachineCtor.obj also becomes the table's holder);
    - other emitters of the table: W3DQuadrupedDraw (four W3D draw objects), W3DTreeDraw (`??_7Rva00252B68@@6B@`);
    - RespawnBody: Rva004C131BDerived.obj's derived destructors call `??1Rva004C131B`;
    - AptScriptColour: AptFactoryConstructors.obj aliases `??1AptScriptColour` to `??1Rva006F25D0`.
  - 2 refused for a new reason, `selected implementation changes` (InheritUpgradeCreate, PreorderCreate):
    the grab-bag's and the TU's class views emit different tables, and a table has no ledger owner.
- Splits done (one class per commit, `tu_skeleton.py --split`): LockWeaponCreate `3af7f216ab8`,
  SpecialPowerCreate `73fe94f720c`, SupplyCenterCreate `1baea78d352`, CashHack `3bebe90960e`, GiantBirdSlowDeath
  `eaccd93b912`, StructureBody `bdaf57d4de5`, DelayedDeathBody `f3dba20b532`, GrabPassenger `716780e1432`,
  UntamedAllegiance `78a813d68ba`, PlayerUpgrade `57d6731c5bb`.
  - Verification for each: build exact; find_declared_unmatched clean on both files; `class_gate.py --staged`
    clean; link_check over the residual, the TU and every census unit touching the class (all LINK, totals
    conserved across each grab-bag's splits); scoped DIR32 OK; no initializer, .CRT or .bss change.
  - Every moved destructor, `??_G` and table copy is byte-identical (same digest) to the residual's old one.
- Bridge: unchanged, as expected for byte-identical moves. 3,996 tables, 57,649 slots, already correct 1,639,
  mismatching source slots 44,644 before and after; refusals identical, nothing newly bridged, no correct table
  lost. The placeholder tables keep their names and bytes in the TU.
  - Their B2 slots (`?f2@Rva004C2656_B2@@UAEXXZ` ...) still resolve through the residual's counted
    `/alternatename` (hatch_baseline is file-keyed and unchanged), so that alias must outlive the moved tables.
- Not committed:
  - AIDock and SupplyTruckAIUpdate (Rva004D759CDerived.cpp). Each split passed the guard, built exact and linked,
    but the written TU carried the grab-bag's neighbouring private StateMachine views, and pre-commit's class
    gate refused the new private copies of AIGuardMachine, AITNGuardMachine and TurretStateMachine. Both were
    reverted (re_log on 0x005440BC). The AIDock state also predicted `??_7AIDockMachine@@6B@` moving from bridged
    to refused (`target-not-external`).
  - AssaultTransportAIUpdate and HealCrate were not tried: their grab-bags declare registered classes (HordeAIUpdate,
    TransportAIUpdate, AnimalAIUpdate, Coord3D), the same class-gate risk, and Coord3D is LINK-018's key.
- Tooling compatibility audit (`4eb5ed5d3d..57d6731c5bb`): no path added, renamed or deleted. The tool repointed
  functions.csv and tu_map.csv (20 rows each) and the doxygen list. None of the 20 moved RVAs is in
  body_owners.csv, the code-identity, data-check, gate or pin-consistency baselines, symbols.csv or
  data_rows.csv. The header-queue entries for GiantBirdSlowDeathBehavior.cpp, CashHackSpecialPower.cpp and
  GrabPassengerSpecialPower.cpp predate the splits and still hold. No tools/, .githooks/ or .github/ consumer
  names these paths.
- Next leads:
  1. Fold each moved placeholder class into the TU's real class (`rename.py class --fold`; lk82 lead 2). Tables
     leave the bridge only through that step: the split itself moves them unchanged.
  2. The nine remaining clean pairs (PlayerHeal, Devastate, SplitHorde, Repair, CombineHorde, HealCrate,
     AssaultTransportAIUpdate; AIDock and SupplyTruckAIUpdate once the carry is fixed).
  3. Tooling: `--split` should carry only the class views the carved rows need, or refuse a carry of a
     registered class before writing; the dry run cannot see the class gate today.
  4. Tooling: proving a moved copy that has an outside referrer would need each referent defined by a changed
     object to keep an identical selected body, recursively. A digest alone is not enough.
  5. InheritUpgradeCreate/PreorderCreate: reconcile the grab-bag's class view with the TU's, or prove the TU's
     table slots against retail (0x008596E4 / 0x00859664), before splitting.

**Six Rva0024A797Derived.cpp splits: 18 tables off the bridge; the fold pilot refused (2026-11-09, seat
halilkkaya-lk84, base `8757e1736a6`).** Method: `tu_skeleton.py --split ... --dry-run --no-claim` per pair, the real
split (one class per commit, the tool claims), lk83's object diff, consumer link_check and scoped DIR32, and
lk74_snap/lk74_cmp (old = new = HEAD's `vtable_bridge.py`) before the first split, after it, after six and after ten.
- Rva0024A797Derived.cpp survey, 13 approved pairs (34 rows have no approved TU):
  - 6 clean, all split: AutoFindHealingUpdate `e5e164e8949`, AssistedTargetingUpdate `b90855a3f07`, DemoTrapUpdate
    `817be25ce59`, EntEnragedUpdate `21b2fff089b`, PickupStuffUpdate `d4ef0cdeff3`, OathbreakersFadeAwayBehavior
    `bca88f1bcc0` (its `??_G` was already rowed in the TU). In each TU the destructor is declared by the TU's own view on
    UpdateModule.h, so it stores the canonical tables; every changed object keeps its COMDAT digests, initializers,
    .CRT and .bss.
  - 2 moved-copy context, correctly (real outside referrers): BuildingBehavior (GameLogic/Object/Behavior/
    BuildingBehavior.obj, a second unit of the class, references `??1BuildingBehavior` and emits its `??_G`) and
    ObjectHelper (its helper family's derived destructors and Object.obj call `??1ObjectHelper`).
  - 3 compile C2600, the TU's view declares no destructor: AutoDepositUpdate, HeightDieUpdate (HeightDieUpdateView.h)
    and Rva0033EEC9 -> ProjectileStreamUpdate.cpp.
  - 2 `bytes` from the merge verifier: StealthUpdate, Rva004A3F8B -> HijackerUpdate.cpp (as lk80 found).
- Bridge, base -> after six splits: tables 3,976 -> 3,958, slots 57,329 -> 56,951, mismatching source slots 42,921 ->
  42,550, already correct 1,659 -> 1,659, retail addresses 2,812 -> 2,807; refusals identical, nothing newly bridged,
  no correct table lost. Off: each class's `6BMiBase1@@@`, `6BUpdateModule@@@` and private `_B2` table
  (EntEnragedUpdate: `6BUpdateModuleInterface@@@`). The canonical `6BObjectModule@@@` copies of five of these TUs
  (and OathbreakersFadeAwayBehavior's `6B@`) stay bridged with 1-3 mismatching slots each.
- Four placeholder SpecialPower splits from Rva00493DEFDerived.cpp (`class_gate.py --staged` clean before each):
  PlayerHeal `a7692e8c4c2`, Devastate `1d6151ab184`, SplitHorde `0194f6c5ab9`, Repair `caba527f4ed`. Byte-identical
  moves; bridge unchanged, as lk83 measured. CombineHorde is still clean and not done.
- link_check over the 14 changed units and every census unit touching the ten classes: 23 of 23 LINK. Bytes are
  conserved: Rva0024A797Derived.cpp's 290 move to its six TUs; Rva00493DEFDerived.cpp's 424 are these four (212) plus
  lk83's four post-census splits. Scoped DIR32: OK.
- Fold pilot, not landed (re_log on 0x004BD207). Retail proves Rva004BD207 is SalvageCrateCollide:
  `??0SalvageCrateCollide` 0x004BD1D7 calls CrateCollide's constructor and stores 0x00C5A9C0 (+0), 0x00C5A040 (+0x0C)
  and 0x00C5A9A8 (+0x10); 0x004BD207 stores the same three and jumps to `CrateCollide::~CrateCollide` 0x004BC4FC; slot 0
  of 0x00C5A9C0 is `??_GRva004BD207` 0x004BD265 and slots 4, 12 and 13 are SalvageCrateCollide's own rows.
  `rename.py class --fold Rva004BD207 --into SalvageCrateCollide --dry-run` refuses "would declare class
  SalvageCrateCollide twice: reconcile the two views in that unit first", and so does Rva004C2656 ->
  CashHackSpecialPower. No byte-exact intermediate unit exists: the placeholder's rows need a class body spelled with
  its name until the fold, the token rewrite then always yields two bodies, and `--prepared` is refused for a NEW that
  is neither registered in canonical_classes.csv nor nested. A false reject; tools/ untouched.
- Tooling compatibility audit (`8757e1736a6..caba527f4ed`): no path added, renamed or deleted. The tool repointed
  functions.csv and tu_map.csv (19 rows each) and added five doxygen entries. None of the 19 moved RVAs is in
  body_owners.csv, symbols.csv, data_rows.csv, the header or ms-header queues, forced_row_moves.csv, or the
  code-identity, data-check, gate or pin-consistency baselines. The header-queue entries keyed to the residual and the
  receiving TUs name other RVAs and still hold. tools/ and its tests name the two grab-bags only in comments; no
  .githooks/ or .github/ consumer names a changed path.
- Next leads:
  1. Tooling: let `rename.py class --fold` take `--prepared REL=FILE` for an unregistered NEW whose unit declares both
     views. That unblocks SalvageCrateCollide (0x0085A9A8/0x0085A9C0), CashHackSpecialPower and probably
     Rva0033EEC9 -> ProjectileStreamUpdate (0x0033EEC9 sits between the class's constructor and its own rows, and
     ProjectileStreamUpdate.cpp keeps a present-unmatched marker for its destructor).
  2. Five `/alternatename` lines in Rva0024A797Derived.cpp are now dead (`?f2@` of the `_B2` placeholders
     Rva00486E18, Rva00491DD3, Rva0049506E, Rva00495916 and Rva004B89C4; the residual object no longer references
     them): remove them and lower the register with `hatch_counters.py --update` (Verifier-Change).
  3. AutoDepositUpdate, HeightDieUpdate and ProjectileStreamUpdate: declare the destructor in the TU's view (its
     class-scope claim first), then split; StealthUpdate and HijackerUpdate need their `bytes` cause read.
  4. CombineHorde's clean split; the `--split` carry of unused private views and blank lines (lk83 lead 3).

**The prepared fold into an unregistered class: SalvageCrateCollide folded, five dead hatches gone (2026-11-09, seat
halilkkaya-lk85, base `38ca5372077`).** Method: lk74_snap/lk74_cmp (old = new = HEAD's `vtable_bridge.py`) before and
after the fold; the objects' symbol tables, lk83's object diff, consumer link_check and scoped DIR32 for each change.
- Hatches (commit "Rva0024A797Derived.cpp: drop five dead /alternatename hatches"): the five `?f2@` lines of
  Rva00486E18/00491DD3/0049506E/00495916/004B89C4 `_B2` were dead. No object in a full build has a COFF symbol for any
  target (the grab-bag's only copy is its .drectve string; control: the live `?f2@Rva0033EEC9_B2` is a symbol there),
  and the census index (`8757e1736a`) shows only the pre-split grab-bag touching them. alternatename 2,694 -> 2,689;
  object unchanged but .drectve; the grab-bag and the six receiving TUs: 7 of 7 LINK.
- rename.py verdict (commit "rename.py class --fold: a prepared unit may fold two views into an unregistered NEW (layout
  held)"): lk84's refusal was false for a unit whose two views are one class. The `--prepared` limit was a scope choice
  (ea1cc82ec28, 6221facaeb5), not a protection. An unregistered global NEW may now come prepared: every unit spelling
  OLD prepared, OLD spelled nowhere, no prepared unit spelling no OLD, no body of a registered class added, and the
  compiler's record (`view_layouts`: sizeof, vfptr, bases, fields, introduced slots) equal for OLD's and NEW's views
  before the fold and for NEW's after the build (every file restored otherwise). 13 new or rewritten cases in
  test_rename_fold.py (131 pass); the rename suite's other 28 failures fail identically with HEAD's rename.py;
  test_gate_exploits.py passes.
- Fold (commit "Fold class Rva004BD207 into SalvageCrateCollide (retail vftable 0x00C5A9C0)"): retail re-read
  (??0SalvageCrateCollide 0x004BD1D7 and 0x004BD207 store the same three tables; 0x004BD265 is slot 0). Both views
  compile as {CrateCollide@0, 24 B, slot 0 the deleting destructor}. 21/21 exact; 6 of 6 units LINK, 19,294 bytes kept.
  Bridge: tables 3,953 -> 3,951, slots 56,938 -> 56,918, mismatching source slots 42,542 -> 42,530; refusals
  identical, nothing newly bridged. Off: `??_7Rva004BD207@@6B@` and `@@6BObjectModule@@@`; SalvageCrateCollide's
  ObjectModule table now has slot 0 right. Already correct 1,664 -> 1,663 only because the name
  `??_7Rva004BD207@@6BBehaviorModuleInterface@@@` is gone; 0x0085A040 keeps SalvageCrateCollide's correct copy.
- Refused (re_attempts.log):
  - Rva004B8DB1 -> SupplyCenterCreate (0x004B8DB1): identity proven, the fold verifies (with `--access protected`, and
    the constructor unit's unrowed present-unmatched `??1SupplyCenterCreate@@MAE@XZ` dropped), but SupplyCenterCreate.cpp
    goes LINKS -> does not link: its new table copies (CreateModuleClass.h, slots 1-3 real) differ from the first copy
    in link order, SupplyCenterCreateConstructor.cpp's private-view copies (`__purecall` slots 1-3, a one-slot
    ModuleInterface table). Reverted.
  - Twelve moved placeholders: their view and the TU's real view disagree on the layout (0x004C2656 row). CashHack's
    real view puts the destructor at slot 3 (36 B against 20 B); the six SpecialPower views GrabPassenger,
    PlayerUpgrade, PlayerHeal, Devastate, SplitHorde and Repair agree on size (20 B) and slot 0 but name opaque bases
    (Rva00493DEF/MiBase1/_B2) against SpecialPowerModule; UntamedAllegiance, StructureBody, SpecialPowerCreate,
    DelayedDeathBody and GiantBirdSlowDeathBehavior differ in size or bases.
- Tooling compatibility audit (`38ca5372077..HEAD`): no path added, renamed or deleted. Old spellings of
  Rva004BD207 remain only in generated or historical records: data_ledger.csv (3 alias names, tool-written;
  data_ledger.py regenerates it), vtable_bridge_queue.tsv (the next real-link publish), name_tiers.csv and
  wb_name_leads.csv (two rows each), deleted_rows.csv (the fold's tombstones), re_attempts.log, attempt_support and
  this entry. tools/, .githooks/ and .github/ name neither class; test_rename_fold.py names it in a comment only.
- Next leads:
  1. SupplyCenterCreate: merge SupplyCenterCreateConstructor.cpp into SupplyCenterCreate.cpp (its approved TU) or move
     its view onto CreateModuleClass.h (class:CreateModule is held by Burachi-3D), then fold and drop the duplicate body.
  2. The six 20-B SpecialPower placeholders: a "NEW keeps its layout" rule (OLD's rows byte-checked against NEW's view)
     would admit them. That is a tooling decision, not taken here. Folding them also kills 8 of the 20 `?f2@..._B2`
     alternatename lines in Rva00493DEFDerived.cpp, which today serve the moved TUs' placeholder tables (still live).
  3. SalvageCrateCollide's five remaining mismatches: slots 1-3 `__purecall` and 12/13 (the TU's CrateCollide view
     introduces xfer where retail has executeCrateBehavior), and 0x0085A9A8 `??_7SalvageCrateCollide@@6B@` (5 missing
     source slots).
  4. `claims.py release` with class:, file: and RVA keys in one call released 0; separate calls per kind work.

**Eight SpecialPower placeholders reconciled and folded: 24 placeholder tables gone, 18 off the bridge (2026-11-09,
seat halilkkaya-lk86, base `522bdc5dc9f`).** Method: per class, retail first (the constructor and the placeholder's
destructor store the same three tables; the destructor tail-calls `??1SpecialPowerModule` 0x00493DEF; its `??_G` is slot
0 of the +0 table), then the placeholder's view reconciled onto the TU's SpecialPowerModule view in its own commit, then
`rename.py class --fold OLD --into NEW --prepared TU=FILE --access protected` (dry run first). Each step: build exact,
find_declared_unmatched, lk83's object diff, consumer link_check, scoped DIR32 and lk74_snap/lk74_cmp (old = new = HEAD's
`vtable_bridge.py`).
- Retail settles every class in the family the same way: `??0X` (42 B) calls `??0SpecialPowerModule` 0x00493C5A and
  stores X's +0 table, 0x00BEFCF8 at +0x0C and X's +0x10 table; the destructor stores the same three; the +0 table has
  14 slots with `??_G` in slot 0 and getModuleNameKey in slot 4. lk85's "disagree on the layout" refusals were the
  placeholder's opaque bases (Rva00493DEF/MiBase1/`_B2`), not a real difference.
- Reconciled and folded (commits "<TU>: derive placeholder <OLD> from SpecialPowerModule" / "...: put both views of the
  class on SpecialPowerModule", then "Fold class <OLD> into <NEW> ..."): GrabPassenger Rva004C5019, PlayerUpgrade
  Rva004C7C33, Devastate Rva004C8213, SplitHorde Rva004C85A4, Repair Rva004C86E4, UntamedAllegiance Rva004C7B36, PlayerHeal
  Rva004C7EAE, and CombineHorde Rva004C87F4 after its split ("Split 2 rows of Rva00493DEFDerived.cpp into
  CombineHordeSpecialPower.cpp").
  - The six TUs with a BehaviorModule-based view needed only the placeholder's bases changed. The fold keeps NEW's own
    present-unmatched destructor definition (already the same body) and drops the placeholder's.
  - UntamedAllegiance's real view was a 4-byte stub (no base): grown onto SpecialPowerModule on the retail evidence above.
    PlayerHeal's view sat on a TU-local `ModuleBase` that put getModuleNameKey at slot 1: rebased onto BehaviorModule
    (m_moduleData +4 and m_object +8 come from Module/ObjectModule); all 15 rows kept their bytes.
  - New refusal, solved: for UntamedAllegiance and PlayerHeal the fold refused "nothing ties NEW to T": the data ledger
    names their +0 tables only for the placeholder, and the constructor units stored the addresses of TU-local dummy
    ints (attempt_support's dummy-vptr list, "needs-identity"). Each constructor unit now declares the class's TU view
    and stores the class's tables (42 B kept; .bss 12 -> 0); its select-any table and `??_G` copies have the TU's
    digests. Constructor unit and fold land in one commit (the tables reference `??1NEW`, which only the fold defines).
- Bridge, base -> after: tables 3,949 -> 3,931, slots 56,910 -> 56,394, mismatching source slots 42,034 -> 41,411,
  already correct 1,664 -> 1,664; refusals identical, no correct table lost. Off: the 24 placeholder tables
  (`6BRva00493DEF@@@`, `6BMiBase1@@@`, `6B<OLD>_B2@@@` of each class). Newly bridged under their own names: 6 tables of
  UntamedAllegiance and PlayerHeal, which had none before. Each class's ObjectModule table now has slots 0 and 4 right
  (5 left: slots 1-3, 12, 13); the +0x10 tables keep 22-25 `__purecall` mismatches (the unit's SpecialPowerModule view
  overrides none of SpecialPowerModuleInterface's slots).
- Hatches: alternatename 2,689 -> 2,681 (eight dead `?f2@<OLD>_B2` lines in Rva00493DEFDerived.cpp, each proven dead: no
  COFF symbol in any built object, only the grab-bag's .drectve string; control `?f2@Rva004C29BB_B2` is live), and
  present_unmatched 2,135 -> 2,129 (six destructor markers became rowed bodies). Commits "Rva00493DEFDerived.cpp: drop
  seven dead /alternatename hatches; ..." and "...: drop CombineHorde's dead /alternatename hatch; ..." (Verifier-Change).
- link_check: every changed unit and every unit touching the classes LINKS (FriendNew, member, Ctor, Slot13 units,
  ModuleFactoryInit.cpp, ConstIntGetters4.cpp, ModuleDataFriendNewFactories.cpp, the grab-bag). Grab-bag bytes 633 -> 580
  with CombineHorde's split, conserved in the TU. No initializer, .CRT or .bss change except the constructor units'
  dummies.
- Refused (re_attempts.log, 0x004C2656): CashHack. Retail gives it the family's shape (constructor stores only the three
  tables; destructor in slot 0), so the TU's ZH-header view (bfme2_specialpower_layout shim: Snapshot-primary, destructor
  at slot 3, 36 B) is the wrong one; putting the placeholder on it would make its tables worse. `?f2@Rva004C2656_B2` stays.
- Tooling compatibility audit (`522bdc5dc9f..HEAD`): no path added, renamed or deleted (one split into an existing TU).
  `rename.py check --range`: 0 renames, 0 problems (folds write no record). Old placeholder spellings remain only in
  generated or historical records: data_ledger.csv (17, tool-written; data_ledger.py regenerates it), vtable_bridge_queue.tsv
  (67, the next real-link publish), name_tiers.csv (16) and wb_name_leads.csv (8), deleted_rows.csv (the folds'
  tombstones), re_attempts.log and attempt_support. tools/, .githooks/ and .github/ name neither the classes nor the
  changed paths (tu_skeleton.py and its test name the grab-bag in comments only). The header-queue entries for
  GrabPassengerSpecialPower.cpp and PlayerHealSpecialPower.cpp key other RVAs and still hold.
- Next leads:
  1. CashHack: rebuild CashHackSpecialPower's view on BehaviorModule.h + SpecialPowerModule.h (its constructor,
     rva004C266F and the present-unmatched crc/xfer/loadPostProcess/doSpecialPowerAtLocation re-checked), then this recipe.
  2. The +0x10 tables (22-25 mismatches each): declare SpecialPowerModule's rowed SpecialPowerModuleInterface overrides
     (isReady 0x004934DE, getPercentReady, getPowerName, onSpecialPowerCreation, pauseCountdown, doSpecialPowerAt*,
     markSpecialPowerTriggered, startPowerRecharge ...) in the shared SpecialPowerModule view once SpecialPowerModule.h
     may change; one header fix would correct every SpecialPower table at once.
  3. The ObjectModule tables' slots 1-3 (`__purecall` where retail has 0x004C8A2F, the name getter, 0x004C8A95 xfer) and
     12/13 (SpecialPowerModule's rva00493805 and ApplyPowerToObject): Snapshot's slots in the shared view.
  4. The grab-bag's eleven remaining Rva00493DEF placeholders: Defector 0x004C29BB, OCL 0x004C3108, StopSpecialPower
     0x004C67A0 (lk83: its constructor unit stores the table, so split it with that unit), HordeDispatch 0x004C8A16
     (proposed TU), and seven tu_map assigns to ElvenWoodSpecialPower.cpp (0x004C3905..0x004C4DE9; check that
     assignment against retail before splitting). Each would follow split, reconcile, fold.
  5. Tooling: rename.py's "nothing ties NEW to T" refusal could name the dummy-store constructor row that blocks it.

**Eight more SpecialPower placeholders folded (seven ElvenWood classes, OCL): 21 tables off the bridge, eight dead
hatches (2026-11-09, seat halilkkaya-lk87, base `a7a3c4d962b`).** Method: lk86's recipe per class (retail first, split
with `tu_skeleton.py --split`, the placeholder reconciled onto the TU's SpecialPowerModule view, then `rename.py class
--fold OLD --into NEW --prepared TU=FILE --access protected`, dry run first). Each step: build exact,
find_declared_unmatched, lk83's object diff, consumer link_check, scoped DIR32 and lk74_snap/lk74_cmp (old = new =
HEAD's `vtable_bridge.py`).
- Identity (retail; tu_map is placement only, so each pair was read): every constructor calls `??0SpecialPowerModule`
  0x00493C5A and stores the class's +0 table, 0x00BEFCF8 and its +0x10 table; the placeholder destructor stores the
  same three and jumps to 0x00493DEF; its `??_G` is slot 0 of the +0 table, whose slot 4 is the class's name-key row.
  Rva004C3905 ElvenWoodSpecialPower (ctor 0x004C38D5), Rva004C4044 WeaponChangeSpecialPowerModule (0x004C3FF8),
  Rva004C43A3 ScavengerSpecialPower (0x004C4353, 46 B: also clears the bool at +0x34), Rva004C4508 CloudBreakSpecialPower
  (0x004C44D8), Rva004C48C6 TaintSpecialPower (0x004C4896), Rva004C4BD1 FreezingRainSpecialPower (0x004C4BA1),
  Rva004C4DE9 DarknessSpecialPower (0x004C4DB9), Rva004C3108 OCLSpecialPower (0x004C30D8).
- ElvenWoodSpecialPower.cpp (commits "Split 14 rows of Rva00493DEFDerived.cpp into ElvenWoodSpecialPower.cpp ...",
  "ElvenWoodSpecialPower.cpp: derive its seven placeholders from SpecialPowerModule", then seven "Fold class <OLD> into
  <NEW> ..."): one split for the seven (14/14 rows alone-clean, both units accepted), one homogeneous reconciliation
  (all seven pairs AGREE in `fold_layout_shape`; Scavenger's placeholder carries the class's `bool m_34`), one fold per
  class. The TU's views were already right (SpecialPowerModule@0, 0x34 B, dtor slot 0); six classes kept their own
  present-unmatched destructor definition. ScavengerSpecialPower declared no destructor (slot 0 held an implicit,
  unrowed `??_G...UAEPAXI@Z`): its fold adds the protected destructor its siblings declare.
- OCLSpecialPower.cpp (commits "OCLSpecialPower.cpp: let the constructor store the class's own tables", "Split 2 rows of
  Rva00493DEFDerived.cpp into OCLSpecialPower.cpp ...", "OCLSpecialPower.cpp: derive placeholder Rva004C3108 from
  SpecialPowerModule", "Fold class Rva004C3108 into OCLSpecialPower ..."): new obstacle, solved. The class was
  `__declspec(novtable)` and its constructor stored the placeholder's tables through `extern "C"` `__identifier`
  declarations, so the split failed to compile (C2373: the moved class defines those vftable symbols). Dropping
  novtable, the externs and the explicit stores keeps the constructor's 42 bytes (compiler stores) and the split then
  passes. OCL had no tables of its own before, so its four commits net zero tables (+3, 0, 0, -3) but move its +0/+0x10
  tables onto the class's own overrides.
- Bridge, base -> after (HEAD's `vtable_bridge.py`, old = new): tables 3,876 -> 3,855, slots 56,094 -> 55,492,
  mismatching source slots 41,111 -> 40,455, already correct 1,719 -> 1,719; refusals identical, no correct table lost.
  Off (24): the 21 ElvenWood-family placeholder tables (`6BObjectModule@@@`, `6BBehaviorModuleInterface@@@`, `6B@` of
  each, after the reconciliation renamed them from `6BRva00493DEF`/`6BMiBase1`/`6B<OLD>_B2`); OCL's three placeholder
  tables replaced by the class's own three (the 3 newly bridged). Each folded class's ObjectModule table now has slot 0
  (the rowed `??_G`) and slot 4 right.
- Hatches: alternatename 2,681 -> 2,673 (the eight `?f2@<OLD>_B2` lines of the folded placeholders, each proven dead: no
  COFF symbol in any built object, only the grab-bag's .drectve string; control `?f2@Rva004C29BB_B2` is live), and
  present_unmatched 2,118 -> 2,112 (six ElvenWood destructor markers became rowed bodies). Commits
  "Rva00493DEFDerived.cpp: drop seven dead /alternatename hatches; ..." and "...: drop OCLSpecialPower's dead
  /alternatename hatch" (Verifier-Change). `hatch_counters.py --update` also lowers `pin reverse/symbols.csv 0x00072892`
  3 -> 2 (slack from LINK-619's RefCountClass move, not this pass): left for its owner.
- link_check: every changed unit, the grab-bag and their consumers LINK (13 of 13 for ElvenWood: Choice, Slots,
  ConstIntGetters4, ModuleFactoryInit and the seven FriendNew units; 11 of 11 for OCL: its FriendNew, ModuleDataFriendNew
  and ModuleDataDtor units, ModuleFactory, ModuleFactoryInit, INI_Rva004C381CParseUpgradeOCL and two siblings). Grab-bag
  bytes 580 -> 159, conserved in the TUs. No initializer, .CRT or .bss change.
- Refused (re_attempts.log):
  - StopSpecialPower 0x004C67A0: StopSpecialPowerCtor.cpp stores the placeholder's tables by name, which blocks the
    split (lk83). Rewritten onto StopSpecialPower.cpp's view it keeps its 46 bytes and links, but class_gate refuses it:
    that view carries the TU's private SpecialPowerModuleInterface (gap slots, `isReady()` non-const,
    `doSpecialPower(int)`), a registered class. Reverted.
  - DefectorSpecialPower 0x004C29BB: not attempted; DefectorSpecialPower.cpp compiles the ZH-header view (lk86's CashHack
    reason).
  - HordeDispatch 0x004C8A16: not split; tu_map has its destructor only "proposed" (`K=Rva004C8A16`), its `??_G`
    0x004C8A79 approved.
- Tooling compatibility audit (`a7a3c4d962b..HEAD`): no path added, renamed or deleted (two splits into existing TUs;
  the tool added OCLSpecialPower.cpp to docs/doxygen/sources.cfg). `rename.py check --range`: 0 renames, 0 problems
  (folds write no record). Code/ spells none of the eight placeholders; old spellings remain only in generated or
  historical records: data_ledger.csv (17, tool-written; data_ledger.py regenerates it), vtable_bridge_queue.tsv (68,
  the next real-link publish), name_tiers.csv and wb_name_leads.csv (16 each), deleted_rows.csv (the folds' tombstones),
  re_attempts.log, attempt_support and LINK-073/this entry. tools/, .githooks/ and .github/ name neither the classes nor
  the changed paths (tu_skeleton.py and its test name the grab-bag in comments only). The header-queue entries for
  ElvenWoodSpecialPower.cpp and OCLSpecialPower.cpp key other RVAs and still hold.
- Next leads:
  1. StopSpecialPower: move StopSpecialPower.cpp's view onto the canonical SpecialPowerModule.h interface (renames of
     `?isReady@StopSpecialPower@@UAE_NXZ` 0x004C683C to the const form and `?doSpecialPower@...@UAEXH@Z` 0x004C67B9 to
     `UAEXI@Z`), or merge StopSpecialPowerCtor.cpp into StopSpecialPower.cpp; then the constructor rewrite (kept in
     lk87 scratch, 1/1 matched), split, reconcile (the TU view must declare `virtual ~SpecialPowerModule();`, or the
     placeholder's destructor inlines the base, and the placeholder needs `m_34`) and fold.
  2. Defector and CashHack: rebuild each TU's view on BehaviorModule.h + SpecialPowerModule.h (both still ZH ports with
     PreRTS.h; CashHack's module data keeps STLport vector rows), then this recipe.
  3. OCL's static `?rva0004C3147@OCLSpecialPower@@SA?AW4NameKeyType@@XZ` is slot 4 of 0x00C5CC74: a member rename to the
     virtual const `getModuleNameKey` would make that slot right too.
  4. lk86 leads 2 and 3 (SpecialPowerModule's interface overrides and Snapshot slots in the shared view) still hold for
     every folded class's +0x10 and ObjectModule tables.

**Four CrateCollide placeholders folded (Heal, Money, Unit, Veterancy): 12 opaque-base tables gone, four tables off the
bridge; the AIUpdate real-name splits refused (2026-11-09, seat halilkkaya-lk88, base `5c6ddfa8056`).** Method: per
class, retail first, then lk85/lk86's recipe (split with `tu_skeleton.py --split`, the TU's views reconciled, the
constructor unit rewritten onto the TU's view, `rename.py class --fold OLD --into NEW --prepared TU=FILE`, dry runs
first). Each step: build exact, find_declared_unmatched, lk83's object diff, consumer link_check, scoped DIR32,
class_gate --staged and lk74_snap/lk74_cmp (old = new = HEAD's `vtable_bridge.py`).
- Identity (retail): each `??0X` calls `??0CrateCollide` 0x004BC523 and stores X's +0 table, the family's 0x00C5A040
  (+0x0C) and 0x00C5A600 (+0x10); the placeholder destructor stores the same three and jumps to `??1CrateCollide`
  0x004BC4FC; its `??_G` is slot 0 of the +0 table, whose slots 4 and 12 are X's getModuleNameKey and
  executeCrateBehavior rows. Rva004BC83F HealCrateCollide (ctor 0x004BC80F, table 0x00C5A868), Rva004BC96F
  MoneyCrateCollide (0x004BC93F, 0x00C5A8A0), Rva004BCC43 UnitCrateCollide (0x004BCC13, 0x00C5A914), Rva004BCE62
  VeterancyCrateCollide (0x004BCE32, 0x00C5A954; slot 13 is its own isValidToExecute 0x004BCEF0).
- Commits, per class: HealCrateCollide.cpp had no CrateCollide view, so its split came first and the reconcile after
  ("Split 2 rows of Rva004BC4FCDerived.cpp into HealCrateCollide.cpp ...", "HealCrateCollide.cpp: derive the class and
  placeholder Rva004BC83F from CrateCollide"). Money, Veterancy and Unit had private one-vptr CrateCollide views, so
  the reconcile came first ("<TU>: put the class on CrateCollide's real view"; UnitCrateCollide.cpp also drops
  UnitCrateCollideView.h, which only it included), then the split. Each fold commit ("Fold class <OLD> into <NEW>
  (retail vftable ...); its constructor stores the class's tables") carries the constructor unit: it stored three
  TU-local dummy ints, so rename.py refused "nothing ties NEW to T" (Heal's dry run) until the unit declared the TU's
  views (42 B kept, .bss 12 -> 0; its table and `??_G` copies have the TU's digests).
- New obstacle, solved: Snapshot's slot names depend on include order. PlayerList.h, Drawable.h and ScriptEngine.h
  define BFME_SNAPSHOT_CAPITALIZED_SLOTS when they are the first to include Snapshot.h; CrateCollide's
  `virtual void xfer(Xfer *)` then overrides nothing and opens slot 12 (a 15-slot +0 table, executeCrateBehavior and
  isValidToExecute pushed to 13/14), while the constructor unit's copy of the same table had xfer at slot 3. Money's
  split showed it (commit "MoneyCrateCollide.cpp: include BehaviorModule.h before PlayerList.h": one changed COMDAT,
  the table now 14 slots); Veterancy and Unit include BehaviorModule.h first from their reconcile on. Check a crate
  TU's +0 table slot 3 after any include change.
- Bridge, base -> after (HEAD's `vtable_bridge.py`, old = new): tables 3,854 -> 3,850, slots 55,484 -> 55,296,
  mismatching source slots 40,446 -> 40,217, already correct 1,720 -> 1,724; refusals identical, no correct table lost.
  Off: the 12 `6BRva004BC4FC_Root/_Mid/_B2@@@` tables of the four placeholders. Each class's +0x0C table
  (`6BBehaviorModuleInterface@@@`) is already correct; its +0 and +0x10 tables stay bridged under the class's name
  (8 "newly bridged" at the same addresses). Left per class: +0 slots 1-3 (Heal: 1-2, as its view declares the
  `?xfer@HealCrateCollide` alias SalvageCrateCollide.cpp defines) and +0x10 slots 1-5.
- link_check: the four TUs, the four constructor units, their FriendNew units, Heal's Execute unit, Shroud's TU and
  constructor, SalvageCrateCollide, CrateCollide, the residual grab-bag, Rva004BB68EDerived, ConstIntGetters4 and
  ModuleFactoryInit: 21 of 21 LINK, 23,251 bytes kept. Grab-bag bytes 265 -> 53 (only Shroud's placeholder left),
  conserved in the TUs. No initializer, .CRT or .bss change except the constructor units' dummies.
- Hatches: none removed. Neither grab-bag has a `?f2@<placeholder>_B2` line; their one alternatename each
  (`?f1@Rva004BC4FC_Mid`, `?f1@Rva0026E836_M1`) is still live: the residual objects reference it (Shroud's
  placeholder; the six AIUpdate destructors).
- Refused (re_attempts.log):
  - AIUpdate real-name splits (row 0x00490544, naming all three): Siege, Animal and Horde are fully approved and their
    rows match in the TUs (2/2), but the link guard refuses new unresolved symbols: the TUs' canonical-header views
    first emit the class's tables, which name declared virtuals no object defines
    (`?GetSnapshotName@AIUpdateInterface`, `?vslot094@AIUpdateInterface`; `GetSnapshotName` and `loadPostProcess` of
    AnimalAIUpdate and HordeAIUpdate, whose retail slots are rowed under other names, e.g. 0x0049A7EE
    `?loadPostProcess@WorkerAIUpdate`). Horde also needs a prepared TU (HordeAIUpdate.h models +0x3E4 as a base, so
    the grab-bag's hand store into `m_extra03E4` does not compile). Assault, Transport and Wander: `??_G` displaced
    in tu_map, not tried.
  - ShroudCrateCollide 0x004BCB0D: `??_G` 0x004BCBF7 only proposed in tu_map; not split.
  - StopSpecialPower 0x004C676C, false reject: merging StopSpecialPowerCtor.cpp into StopSpecialPower.cpp with
    `--split --prepared` (whole-donor absorb; the TU view gains the constructor and `virtual ~SpecialPowerModule();`)
    matches 1/1, but the link guard reports a duplicate `??0StopSpecialPower` whose only other definer is the donor
    being absorbed.
- Tooling compatibility audit (`5c6ddfa8056..HEAD`): one path deleted (UnitCrateCollideView.h; no tool, doc, register
  or doxygen config spells it, only re_attempts.log and two attempt_support notes); four splits into existing TUs
  (the tool repointed functions.csv, tu_map.csv and docs/doxygen/sources.cfg). `rename.py check --range`: 0 renames,
  0 problems (folds write no record). Code/ spells none of the four placeholders; old spellings remain only in
  generated or historical records: data_ledger.csv (tool-written; data_ledger.py regenerates it),
  vtable_bridge_queue.tsv (the next real-link publish), name_tiers.csv, wb_name_leads.csv, deleted_rows.csv (the
  folds' tombstones), re_attempts.log, attempt_support and this entry. tools/, .githooks/ and .github/ name neither
  the classes nor the changed paths (tu_skeleton.py names the grab-bag in a comment). The header-queue entries for
  MoneyCrateCollide.cpp and VeterancyCrateCollide.cpp key other classes (Player, InGameUI) and still hold; the
  grab-bag's hatch_baseline line still matches its live hatch.
- Next leads:
  1. ShroudCrateCollide: approve `??_G` 0x004BCBF7 (slot 0 of its +0 table), then the Money/Veterancy order
     (reconcile with BehaviorModule.h first, split, fold with the constructor unit); that also kills
     `?f1@Rva004BC4FC_Mid` and empties the grab-bag.
  2. The crate +0x10 tables (slots 1-5 of 0x00C5A600: 0x004BC51B, rowed `?forward@Rva004BC51B`, and the folded
     0x0047A699, rowed as Xfer's `Is*` getters) and +0 slots 1-2 (0x00483CEF, rowed under several loadPostProcess
     names; each class's name getter, e.g. 0x004BC839, rowed as a free `Rva...Get` in ConstIntGetters4.cpp): naming
     those slots in the family's views would correct every crate table at once.
  3. SalvageCrateCollide.cpp includes PlayerList.h before BehaviorModule.h: the include-order fix above would fix its
     slots 12/13 (lk85 lead 3); not in this seat's scope.
  4. AIUpdate: define or alias the canonical headers' unrowed virtuals (GetSnapshotName, vslot094, loadPostProcess)
     before splitting; header-adoption territory.
  5. StopSpecialPower: fix the `--split --prepared` absorb guard (tooling), or lk87's route 1 (the canonical
     SpecialPowerModule.h interface: `isReady() const` with a `mutable m_34`, `doSpecialPower(unsigned int)`).
  6. Tooling: claim pushes fail under `MSYS_NO_PATHCONV=1` (tu_skeleton's split reported "claim push failed" three
     times; the same command without it claimed at once). Run claiming tools without it.
  7. The four constructor units now compile their TU's views; each can merge into its approved TU (consolidation).

**NetCommandMsg family: 11 bridged tables cleared (`0x008601F4..0x00860284`, `0x00860560`) and 5 hatches retired (2026-11-10, base `541f9d6d57d`).**
Method: class/method identity fixes + `tools/add_match.py --icf-owner` + `tools/hatch_counters.py --update`, checked with a bounded `vtable_bridge.plan()` over a 27-source `build/match/` cluster (`0x00860130..0x00860560`), `tools/build.py`, `tools/eh_verify.py`, and `tools/link_check.py`.
- Done, five commits stacked on `541f9d6d57d`:
  - `e1941663d35` (`Rva004D67D0Dtor.cpp`, `Rva004D6806Contents.cpp`): moved `0x004D6806` (192 B + 5 EH funclets `0x00791122..0x00791153` and EH handler) from placeholder `Rva004D6806` to `Rva004D67D0::getContentsAsAsciiString()` (`rename.py function --to-class`), declaring it on `Rva004D67D0` for retail vtable `0x00860560` slot 3.
  - `61c7078726d` (`NetCommandMsgCtor.cpp`, `Rva004D63DBContents.cpp`): moved `0x004D63DB` (141 B) from placeholder `Rva004D63DB` to `Rva004D5A10::getContentsAsAsciiString()`, declaring it on `Rva004D5A10` for retail vtable `0x00860284` slot 3.
  - `43bd5738bce` (`Disp8MovzxFieldGetters.cpp`, `NetCommandMsg.cpp`, `NetCommandMsgCtor.cpp`): retracted opaque `Rva004D5776MovzxWordField::get` (5 B, tombstoned; `Disp8MovzxFieldGetters.cpp` 3/3), rowed `NetAckStage1CommandMsg::getSortNumber` + ICF twins `NetAckBothCommandMsg::getSortNumber` and `NetAckStage2CommandMsg::getSortNumber` (`fold-proof=Code/GameEngine/Source/GameNetwork/NetCommandMsg.cpp`) at `0x004D5776` (5 B) in `NetCommandMsg.cpp` (`0x004D5776`'s approved TU, 19/19), and declared `virtual Int getSortNumber();` on those three classes in `NetCommandMsgCtor.cpp` (stripping `// ?getSortNumber@NetAckStage1CommandMsg@@UAEHXZ present-unmatched`).
  - `5c521b1d046` (`NetCommandMsgCtor.cpp`): rowed the 10 compiler-emitted `??1<Class>@@UAE@XZ` dtors (`0x004CEE78`, 7 B, `icf-owner ??1NetCommandMsg@@MAE@XZ`, `fold-proof=NetGameCommandMsgDtor.cpp`) and 10 `??_G<Class>@@UAEPAXI@Z` slot-0 deleting dtors (`0x004D5B30`, 28 B, `icf-owner ??_GNetKeepAliveCommandMsg@@MAEPAXI@Z`, `fold-proof=NetCommandMsgCtor.cpp`) for `NetAckBothCommandMsg`, `NetAckStage1CommandMsg`, `NetAckStage2CommandMsg`, `NetDisconnectKeepAliveCommandMsg`, `NetDisconnectPlayerCommandMsg`, `Rva004D580E`, `Rva004D582B`, `Rva004D598E`, `Rva004D59B8`, and `Rva004D5A10` (`NetCommandMsgCtor.cpp` 61/61).
  - `1b0891d9972` (`NetCommandMsgCtor.cpp`, `NetCommandMsg.cpp`, `Rva004D67D0Dtor.cpp`, `reverse/symbols.csv`, `reverse/hatch_baseline.tsv`; `Verifier-Change`): defined `NetKeepAliveCommandMsg::~NetKeepAliveCommandMsg() {}` inline under `protected:` and rowed `??1NetKeepAliveCommandMsg@@MAE@XZ` at `0x004CEE78` (retiring 1 `/alternatename` pragma and 1 redundant `0x004CEE78` pin, `2 -> 1`), removed both unneeded `// ??1NetCommandMsg@@MAE@XZ present-unmatched` comments (`NetCommandMsg.cpp`, `Rva004D67D0Dtor.cpp`), and updated `hatch_baseline.tsv` to 0 drift (`alternatename` `-1`, `pin` `-1`, `present_unmatched` `-3`).
- Verification:
  - Bounded `vtable_bridge.plan()` (27 `build/match/` objects covering `0x00860130..0x00860560`): all 11 previously bridged tables (`0x008601F4`, `0x00860204`, `0x00860214`, 6 shared `0x00860244` tables, `0x00860284`, `0x00860560`) plus `NetCommandMsg` (`0x00860130`) and `NetKeepAliveCommandMsg` (`0x00860244`) report `already_correct` (13/13; COFF checks confirm each `??_7` is defined only by `NetCommandMsgCtor.cpp` or `Rva004D67D0Dtor.cpp` and matches 4/4 retail slots). Only `NetFrameCommandMsg` (`0x00860140`) stayed out (`target-not-kept` in this slice because its slot-3 provider `NetFrameCommandMsgContents` was omitted).
  - Byte/EH/data/ledger: `build.py` 98/98 on directly edited 6 sources post-rebase (418/418 across the 18-source cluster and 95/95 across 9 additional consumer units before rebase), `eh_verify.py` 81/81 exact on the 18-source cluster, `data_check.py --converged` 0 second names, `check_csv.py`, `find_declared_unmatched.py --fail`, `pin_consistency.py --check`, `hatch_counters.py --report` 0 drift, and `rename.py check --range` 0 problems.
  - `link_check.py`: 25 of 26 cluster units link cleanly (`47,138 -> 47,138 B`; `NetCommandMsg.cpp` `355 -> 360 B` balances `Disp8MovzxFieldGetters.cpp` `20 -> 15 B`; `ConnectionManager.cpp` remains blocked on pre-existing `_STL::_Rb_tree` COMDATs). Next census/real-link confirmation pending publication.
- Next leads:
  1. `NetFrameCommandMsg` (`0x00860140`, `NetFrameCommandMsg.cpp`): `vtable_bridge_queue.tsv` shows only slot 0 (`0x004D5B30`); check if compiler-emitted `??1NetFrameCommandMsg` / `??_GNetFrameCommandMsg` match cleanly at `0x004CEE78` / `0x004D5B30`.
  2. `Rva004D65DCDtor.cpp:37` still carries an unnecessary `// ??1NetCommandMsg@@MAE@XZ present-unmatched` comment (same base dtor already matched in `NetGameCommandMsgDtor.cpp`).
  3. Header-queue items for `NetCommandMsgCtor.cpp` and `Rva004D67D0Dtor.cpp` remain blocked on `LINK-188` (`MemoryPoolObject`).

**`ProductionQueueHordeContainModuleData` / `SlaughterHordeContainModuleData` dtor alignment (2026-11-10):**
- `ProductionQueueHordeContainModuleDataDtor.cpp` (previously a 1-slot `GarrisonContainModuleData` scaffold copy) now includes canonical `HordeGarrisonContainModuleData.h`, emitting a 31-slot `??_7ProductionQueueHordeContainModuleData@@6B@` matching `ProductionQueueHordeContain.cpp`.
- Both `ProductionQueueHordeContainModuleDataDtor.cpp` and `SlaughterHordeContainModuleDataDtor.cpp` declare `inline __forceinline HordeGarrisonContainModuleData::~HordeGarrisonContainModuleData() {}` so retail's inlined `??1GarrisonContainModuleData@@UAE@XZ` tail call is preserved while emitting `sec=3 sel=2 len=5` `??1HordeGarrisonContainModuleData@@UAE@XZ` (`0x00257A05`). Row `0x00257A05` moves from `HordeGarrisonContainModuleDataDtor.cpp` (`sel=1` collision) to `SlaughterHordeContainModuleDataDtor.cpp` (`add_match.py --replace-existing`) and `HordeGarrisonContainModuleDataDtor.cpp` is retired (`-1` source file).
- Verification: `build.py` 7/7 exact across both dtor TUs, `eh_verify.py` 2/2 exact, `find_declared_unmatched.py --fail`, `class_gate.py`, and read-only `link_check` simulation dropping `HordeGarrisonContainModuleDataDtor.obj` (`9/9 LINKS`, net `+172 B` linked across cohort; census confirmation pending). `ContainModuleDeletingDtors.cpp` still carries `header_queue.tsv:2227` and `0x00848DC0`/`0x008490F8` retain the shared `ModuleData::slot14` difference in `vtable_bridge_queue.tsv`.

**Rva0024A797Grandchildren.cpp: WallUpgradeUpdate and the name-first route refused; one RvaSmallVtableCtors table
off the bridge (2026-11-10, seat halilkkaya-lk89, base `60189f9cedc`).** Method: lk74_snap/lk74_cmp (old = new =
HEAD's `vtable_bridge.py`), `tu_skeleton.py --split --dry-run --no-claim`, `rename.py class --fold` and `function
--to-class` dry runs, retail slot reads, per-object `??_7` comparisons against retail.
- WallUpgradeUpdate (0x004AB246, both rows approved): identity holds (ctor 0x004AB317 and dtor 0x004AB246 store
  0x00C54780/+0, 0x00C49800/+0x0C, 0x00C54774/+0x10, 0x00C54768/+0x20, 0x00C54764/+0x24; the dtor jumps to 0x0024A797;
  0x004AB392 is slot 0 of 0x00C54780). Not workable in this order: the split is refused (C2504, WallUpgradeUpdate.cpp
  defines private `UpdateModule`/`WallUpgradeUpdate` views and a ctor that stores the placeholder's tables by
  `__identifier`). The TU cannot be put on WallUpgradeUpdate.h alone (its real ctor would emit the class's tables
  and need `??1WallUpgradeUpdate`, which only the fold defines), and the fold into the registered class needs every
  unit spelling `Rva004AB246` prepared on that header, whose tables name `?loadPostProcess@WallUpgradeUpdate@@MAEXXZ`
  (retail slot 1 is the 0x00497805 ICF; that address is held by ancalgonn-swarm-seat6 through
  class:SpecialAbilityUpdate) and `?GetSnapshotName@WallUpgradeUpdate@@MBEPBDXZ` (0x004AB26D, rowed
  `?name@Rva004AB26DNamed`). Route once 0x00497805 is free: one commit puts the TU on WallUpgradeUpdate.h (real ctor;
  PoisonedBehavior's real ctor on the same base pair matches), rows the loadPostProcess ICF, respells the name getter
  and folds the placeholder (grab-bag prepared, the dead `?fe@/?ff@Rva004AB246_E*` alternatename lines dropped); the
  split follows.
- Name-first pilot: not workable. `rename.py class --fold` refuses "nothing ties NEW to T" for all six ZH classes with
  an out-of-line `~X` (ToppleUpdate, SlavedUpdate, StructureCollapseUpdate, DefaultProductionExitUpdate,
  SupplyCenterProductionExitUpdate, AutoHealBehavior): each constructor unit stores the placeholder's tables by
  `__identifier`, so each fold must carry that unit rewritten onto a view of X (lk88's recipe), and a view consistent
  with the TU's. PropagandaTowerBehavior refuses because its TU declares both views (the `Rva0048180C` helper for
  0x00481A9E). SlavedUpdate.cpp (the ZH-verbatim port) already defines `??1SlavedUpdate@@MAE@XZ` (present-unmatched)
  with retail's 32-byte shape, but its four tables carry Zero Hour's layout (21 of 57 slots wrong, against the
  placeholder's 15), so a real-name split there would worsen the tables until that TU's view is BFME2's. Every
  candidate except AutoHealBehavior has slot 1 = 0x00497805 (same claim). Four placeholders duplicate tables their
  real class already emits (ClickReactionBehavior, ShareExperienceBehavior, PropagandaTowerBehavior,
  RadiateFearUpdate: 16 tables at the same addresses); a fold there removes four tables each without any split.
- Done, one code commit ("Move ?rva000ABD68@Rva000ABD68Forwarder@@QAEXXZ into Rva000ABD56 ..."): lk80's one-slot
  recipe. Retail's one-slot 0x00BC957C, installed by `??0Rva000ABD56` (RvaSmallVtableCtors.cpp), holds 0x000ABD68; the
  forwarder body moved into the class with prepared views (the vptr replaces the old +0 pad). 205/205 matched;
  link_check over both units, VslotSizedForwarders2.cpp and GameLogic.cpp: 4 of 4 LINK, 17,616 -> 17,616 bytes;
  scoped DIR32 OK.
- Bridge, base -> after: tables 3,830 -> 3,829, already correct 1,761 -> 1,762, mismatching source slots 41,006 ->
  41,005; refusals identical, nothing newly bridged, no correct table lost. Off: `??_7Rva000ABD56@@6B@`.
- Refused (re_attempts.log, three rows): 0x004AB246 (above), 0x004A1855 (the pilot), and 0x00040ECE: the fold
  Rva00040ECE -> Rva0040EDB needs Rva00041004Lock.h, whose `__forceinline Rva0040EDB()` is the body rowed out of line
  as `??0Rva00040ECE` (lk80's COMDAT-constructor trap). Other one-slot and three-slot candidates are held
  (VslotSmallBodiesAI.cpp and VslotSmallBodiesC.cpp by ancalgonn-swarm-sweep-header) or fold across a third class's
  deleting destructor (Rva003F3FEC, Rva003EE734, Rva0020E6D6 install another class's table).
- Tooling compatibility audit (`60189f9cedc..HEAD`): no path added, moved or deleted; `rename.py check --range`: 0
  renames, 0 problems. The old spelling `?rva000ABD68@Rva000ABD68Forwarder@@QAEXXZ` remains only in deleted_rows.csv
  (the tombstone) and name_tiers.csv (generated); GameLogic.cpp still declares the unused `Rva000ABD68Forwarder` class
  (no definition, no reference). tools/, .githooks/ and .github/ name neither class.
- Next leads:
  1. WallUpgradeUpdate as above, once 0x00497805 is claimable.
  2. The four duplicate-table placeholders: fold each with its constructor TU prepared (each TU defines the ctor and
     an implicit destructor, so the TU must declare `virtual ~X();` and the grab-bag view must match the TU's bases).
  3. The six ZH classes: rewrite each constructor unit onto the class's view in the fold commit, then rebuild the map
     for Z approval and split; SlavedUpdate.cpp's view must first carry BFME2's slot order.
  4. Tooling: tu_map gives no Z/S for a placeholder-named destructor even when its constructor row names the class;
     a constructor-store tie (ctor and dtor install the same tables) could approve it directly.
- Addendum (same seat, base `bdd53035fb4`): the two leads above.
  - Duplicate-table placeholders (lead 2): ShareExperienceBehavior was folded with a reconcile commit first (the
    placeholder on ShareExperienceBehaviorInterface, as rename.py's per-unit layout check needs) and the TU prepared
    with `virtual ~ShareExperienceBehavior();`. Both units then emitted identical tables and `??_G` (same digests),
    4 of 4 LINK, and the bridge fell 3,829 -> 3,825 with nothing newly bridged. Reverted ("Revert the
    ShareExperienceBehavior fold and its reconcile ..."): tu_map's N signal names `<the row's directory>/<Class>.cpp`,
    and for a BFME-only class (no Z/S anchor) whose destructor is its first address, a regenerated map moves all 25
    rows to `Common/ShareExperienceBehavior.cpp` (rows in their approved TU 23,444 -> 23,423), while no map approves
    the destructor for the Behavior/ TU, so the split that would settle it is unavailable. ClickReactionBehavior and
    RadiateFearUpdate are BFME-only too: not attempted. PropagandaTowerBehavior (ZH, so Z-anchored) still needs its
    TU's two views and the constructor unit's third view reconciled first: skipped.
  - "Nothing ties NEW to T" (lead 3): cleared without rewriting the constructor onto a real view. rename.py's tie
    reads the installing rows' current objects, so respelling the constructor unit's `__identifier` table names to
    NEW's and rebuilding it (bytes unchanged) before the fold is enough; constructor unit and fold land together.
    Folded: SupplyCenterProductionExitUpdate (Rva004A653D) and DefaultProductionExitUpdate (Rva00487F3A), both
    already agreed by the name lane (name_agreed nl-94a22544e126, nl-edfe4ae01f4c). In memory the map now approves
    each destructor by Z for its Zero Hour TU (and two C rows each); its `??_G` goes displaced (it rides with the
    destructor); rows in their approved TU are unchanged. Bridge 3,829 -> 3,829: the eight placeholder tables
    become the classes' (same slots). link_check 7 of 7 and 8 of 8 LINK, bytes unchanged; scoped DIR32 OK.
  - The split does not follow yet: SupplyCenterProductionExitUpdate.cpp's view (ExitInterface.h, a one-argument
    getExitPosition opening a new primary slot, no declared destructor) fails the merge verifier ('bytes');
    DefaultProductionExitUpdate.cpp is the Zero Hour verbatim port, whose tables have ZH's layout (as SlavedUpdate's).
    Each TU's view must take retail's tables first.
  - Next leads: (1) tooling: tu_map's N should not take a grab-bag row's directory when the class's other rows sit in
    one TU; that unlocks the four duplicate-table folds (16 tables). (2) The same respell-then-fold for
    StructureCollapseUpdate (registered: needs its header in every prepared unit), ToppleUpdate and AutoHealBehavior
    (both held by ancalgonn-swarm-sweep-header today). (3) Reconcile the two ProductionExit TUs' views to retail's
    tables, then split.
  - Audit (`bdd53035fb4..HEAD`): no path added, moved or deleted; `rename.py check --range`: 0 renames, 0 problems;
    tools/, .githooks/, .github/ and docs name neither placeholder; old spellings remain only in generated or
    historical records (data_ledger.csv, vtable_bridge_queue.tsv, wb_name_leads.csv, name_votes/name_agreed,
    an attempt_support verdicts file, deleted_rows.csv tombstones, tu_map.csv until its next refresh).

Rva0056AC82, partial primary-table repair (base 40023db426). The retail
destructor at RVA 0x0056AC82 stores the primary table at RVA 0x0086D0A8
and the secondary table at 0x0086D06C. Primary slot 1 targets 0x0050B5C6
(`B0 01 C3`, true with no argument pop). Both Rva0056AC26Constructor.obj
and Rva0056AC26Derived.obj now reference the derived override at offset 4.
The two sources verify 47/47 rows. Link preview retains 352 and 292 bytes
respectively against census 60189f9ced. Both primary tables still emit only
two slots. The secondary table has 15 slots in the constructor unit and one
in the destructor unit. Adopting Base2 in the latter alone introduced an
extra secondary vptr store during destruction and failed byte verification.
The bridge remains open pending reconciliation of the base destructor.

Cancel-army-move button (base c96dacc181). Slot 1 in the two-entry
Rva005F5C77Base0 table at RVA 0x0087A630 targets __purecall. The
Rva005E91A9 constructor and destructor install the derived primary table
at RVA 0x00877FF0, whose slot 1 targets 0x005E9163. The compiler now emits
both base entries and both derived entries. Both installers' derived COFF
tables relocate offset 4 to the same virtual override. The original 23-byte
method retains its ledger coverage under the derived class. Verification:
14/14 matched rows across three sources; link preview at census 60189f9ced
retains 333/333 bytes. Other names sharing 0x0087A630 and the secondary
table at 0x00877FD0 remain separate work. Await the real link for bridge counts.

Rva0056ACFF (RVA 0x0086D160, secondary; 0x0086D19C, primary) is spelled:
slot 1 (0x0056ABCB, ?slot1@Rva0056ACFF@@UAE_NPAURva002B4BC9Arg@@@Z) and
slot 4 (0x0056ABD6, ?slot4@Rva0056ACFF@@UAE_NPAULivingWorldArmy@@PAVRva00318C32Ret@@@Z)
carry their contract names, both tables verify 15/15 and 5/5 AGREE against
retail, and a store-wide object scan finds no reference to the retired
names. The bridge rows retire by tooling at the next real link. Trial
results and retail targets are in `reverse/attempt_support/registry-acff-slot-contract.md`. The B2DD sibling table at RVA
0x0086D434 independently ties slot 4 to an army and destination region via
tutorial task case 5. The base contract and its default row still use two
integer parameters.

AI upgrade heuristic helper, RVA 0x008765A0. Constructor 0x005DA64B
installs this two-entry table. The factory calls slot 0 through its field
at +0x38 as int(int) and stores the result at +0x40. Rva005DA64B now emits
the zero-returning override at 0x005DAA6C (33 C0 C2 04 00); slot 1 retains
the deleting destructor at 0x005DA663. Its unit verifies 5/5 rows and the
preview retains 88/88 bytes against census 60189f9ced.

The other emitter, Rva005DAA5A in V3PolyDeferredCopyCtors.cpp, and its
sibling Rva005DAA48 at table 0x00876598 still need lifetime reconciliation.
An inline Rva005DAA36(void*) base constructor preserved both 18-byte
constructors, both slot targets and the 7-byte restores to VA 0x00C70B80.
It duplicated the strong constructor from V3PolyCopyCtors.cpp (preview
236 to 0). A shared inline definition alone removed the required standalone
body from that owner. Both trials were reverted; the three units verify
34/34 together. Await real-link provider selection for 0x008765A0.

The two GapBodiesGE08.cpp filter constructors match their existing filter
views in a scoped trial (13 and 29 bytes). Their one-slot placeholder
tables at 0x008172A8 and 0x007F8FE4 still need identity reconciliation.
Both fold dry runs reject the shared base restore at 0x0049C38A.
See `reverse/attempt_support/partition-filter-constructors-3674bd.md` for
the two slot maps, proposed signatures and reproduction commands.

CastleMemberBehaviorModuleData, RVA 0x0081A380. The 41-byte constructor
and 58-byte destructor now share a declaration on the canonical ModuleData
base. The compiler installs the table in the constructor and emits identical
124-byte tables with 31 DIR32 relocations in both units. Thirty entries
resolve to retail's words using the ledgers and the object's weak deleting
destructor default. Entry 14 references ModuleData::slot14(int) const;
retail calls 0x000B69A1. This shared identity is still open. Verification:
8/8 code rows, link preview 277/277 bytes at census 60189f9ced. The three
CastleMemberBehavior tables belong to the behavior object itself and remain
open. Real-link selection and runtime behavior await a new image.

Army unit swapper dialog, RVA 0x0087953C. Both the B17 object and the
real Rva005F566ADtor object now emit an eight-byte table with the deleting
destructor followed by __purecall (0x0003B810). The derived constructor
0x005E626D installs 0x00877DE8, where slot 1 is the existing no-argument
override 0x005E586B. StrategicInGameUI.obj retains that override and the
next method at 0x005E57A2. All three units pass byte verification and the
link preview retains 3,037 bytes against census 60189f9ced. Await the real
link before retiring the bridge.

RegionDetailsPanelStructuresPage, RVA 0x00877AD8. The constructor at
0x005E2237 installs the two-slot table. Slot 1 reads ProgressOverlayColor
using INI::initFromINI and the field table at VA 0x00C77A98. The official
to-class move assigned its existing 18-byte row at 0x005E2126 to
Rva005E9F7B. The constructor and B17 objects both emit eight bytes with
the deleting destructor at offset 0 and the parser at offset 4. The three
units verify 18/18 code rows and 2/2 data rows; the preview retains 476
bytes at census 60189f9ced. The other table name Rva005E2237 and real-link
provider selection are outside this scoped check.
Auto-resolve dialog base table, RVA 0x0087823C. Retail installs this table
in the constructor and destructor. Its second slot targets the shared RET
at RVA 0x000B3FD0. The derived table at RVA 0x00875540 overrides that
slot with the existing battle resolver method at RVA 0x005D0F95. Both
base COFF copies and both derived copies now contain eight bytes, with a
DIR32 relocation at offset four to the respective method. The five units
verify 43/43 functions. The seven-unit link preview (including current
providers for B17) retains 1,521 bytes against census 60189f9ced. Bridge
retirement awaits a real link.

The ACDF sibling of the ACFF tutorial task now overrides primary slot 1.
The destructor at RVA 0x0056ACDF installs table 0x0086D14C, whose second
word targets the guarded flag update at 0x0056AB97. The compiler now emits
a relocation to that 41-byte method in the derived object. The to-class
check verified the table and 19/19 functions in two units. With the
constructor included, the link preview retains 378 of 378 bytes at
60189f9ced. Secondary slot 14 is now spelled: 0x0056ACF1 carries
?slot14@Rva0056ACDF@@UAEHH@Z (`mov eax,[ecx+0x10]; ret 4`, this = the
Base2 subobject) in VslotSmallBodiesAN.cpp, and the ACFF secondary
contract is spelled. Remaining slots stay open.

ACC5 primary table, RVA 0x0086D0FC. Constructor 0x0056AEC6 clears
the flag at +0x18. Slot 1 reads it at 0x004C9990 and slot 2 sets it at
0x0056AB35 after the ID matches; the 83-byte setter is now spelled as the
AC26 override ?vslot02@Rva0056ACC5@@UAEXH@Z (Rva0056AB35Method.cpp), the
contract spelling that keeps the primary table at retail's 20 bytes.
Secondary slot 12 (0x0056AB88) is spelled ?slot12@Rva0056ACC5@@UAE_NH@Z
(Disp8ByteFieldGetters.cpp), comparing the first own member at +0x14
against the argument; a store-wide scan finds zero callers outside the
slot. Constructor and destructor objects each emit 12 bytes with DIR32
relocations to the flag getter and setter at offsets 4 and 8. Slots 3 and
4 of the retail five-entry table are still missing. The three changed
units verify 49/49 functions and three float literals. Including the
current ACDF provider in the link preview retains 768/768 bytes across
four units at census 60189f9ced. The separate ACFF secondary table is
spelled and awaits the real link.

ACFF constructor identity, RVA 0x0056AF94. The class fold verifies its
primary store of 0x0086D19C and its +8 store of 0x0086D160 against the
ACFF deleting destructor and adjustment thunk in their respective slot 0.
LivingWorldTutorial.obj now has a REL32 call to the ACFF constructor that
Rva0056AF94Ctor.obj defines. The three changed units verify 19/19 code
rows and both data rows. The scoped link preview retains 1,438 bytes at
census 60189f9ced. Both hand-written tables remain pending replacement.

ACFF native constructor trial after the class fold: 31/31 bytes match
with compiler-generated 20-byte and 60-byte tables. Five primary and
thirteen secondary relocations resolve to the retail targets. The secondary
overrides at offsets 4 and 16 now have typed providers (slot1 at
0x0056ABCB, slot4 at 0x0056ABD6); that dry-run refusal is historical. The
slot 4 to-class dry run rejects the old two-slot destructor table even
with the complete constructor table present. See the reproduction in
`reverse/attempt_support/registry-acff-slot-contract.md`. The production
tables remain in place.

ACFF paired installer trial. Both compiler-emitted tables now pass the data
verifier with the typed slot 4 provider and the contract slot1 symbol
(b1Slot1's successor, renamed with a tombstone).
The eight-unit link preview still loses 352 bytes in AC26Constructor due
to two shared base table definitions. Restoring production inputs returns
all 2,286 bytes. The reproducer and affected table names are in
`reverse/attempt_support/registry-acff-slot-contract.md`.

Adopting the canonical AC26 header in AC26Constructor on 860ce62b30 places
the ACC5 override 0x0056AB35 at offset 20 instead of the retail offset 8.
The trial object names the inherited default at offset 8. The constructor
unwind calls the shared destructor and cannot disambiguate the base.

The shared Rva0056AC26Base2 slot 4 now declares the army and destination
region pointers used by the override at 0x0056ABD6 and corroborated by
the B2DD pair comparison at 0x0056AB09. Its folded five-byte default row
at 0x0050B5F1 retains its source and fold proof. The 15 direct consumers
of the base headers and three related provider units verify 128/128
functions and four data rows. The same 18 units retain 3,781 bytes in
the link preview before and after the signature change at census
60189f9ced. The ACFF hand tables and secondary slot 1 remain open.

The shared secondary slot 1 now accepts Rva002B4BC9Arg *, the type already
used by ACFF's forwarder at 0x0056ABCB. Its target at 0x002B4BC9 reads the
string at +0x18. The shared slot retains its ordinal name and the five-byte
default at 0x005CB9FF retains its fold proof. Rebuilding the header consumers,
related providers and the forwarder's target verifies 129/129 functions and
four data rows. The same 19 units retain 3,845 bytes in the link preview
before and after the change at census 60189f9ced. ACFF's private override now
carries the contract name ?slot1@Rva0056ACFF@@UAE_NPAURva002B4BC9Arg@@@Z
(renamed from b1Slot1 with a tombstone), and the sibling slots are spelled
and judge AGREE; replacing the hand tables still awaits the real link.

ACDF constructor at 0x0056AF4B: the class fold ties both table stores to
ACDF's deleting destructor (0x0056AF78) and its secondary adjustment
thunk (0x0056ACF7). The tutorial object calls the ACDF constructor by REL32
and its constructor object defines that name. Both affected units verify
18/18 functions. The preview with all shared-header consumers retains
3,845/3,845 bytes in 19 units before and after the fold (60189f9ced).
The current destructor object still emits 2 of 5 primary entries and
1 of 15 secondary entries. Secondary slot 14 now targets 0x0056ACF1
under its contract name; adopting the full tables in the shared
ACFF/ACDF destructor unit remains.

The tutorial now constructs Rva0056AE4A at 0x0056ADF1. Its primary table
at VA 0x00C6D23C starts with the deleting destructor at RVA 0x0056AE2E.
The second table at VA 0x00C6D200 starts with the adjustor at 0x0056AE26.
The class fold verifies 19/19 functions and both data rows across the three
affected units. The same 19-unit preview retains 3,845 bytes at 60189f9ced.
Both tables still use the explicit arrays in Rva0056ADF1Ctor.cpp.

### Rva0007DFF2 and Rva00215E42 abstract base tables (2026-11-12)

The real-link queue at `12b12c9ec3` records one-slot copies of both tables
from `InlineDtorDeletingDtorsC01.cpp`. Retail's tables at `0x007C6F24`
and `0x007E5838` contain two and six slots respectively. The source now
declares the pure virtuals in order. Both current COFF tables match every
retail slot after resolving their deleting-destructor weak externals.

The emitter and `BannerUI.cpp` verify 140 functions, five data rows and
21 exception graphs. Both retain their combined 5,839 linked bytes in the
preview on index `80569f4278`. The next real link must confirm the two
table names no longer need bridges. The derived table at `0x00838B8C`
still needs its slot 5 override, and the other folded table names have
their own emitters.

The derived slot 5 at `0x00406B39` is also inherited or shared by the
table at `0x00838BA4`. Both pointers reach the same local-static storage
and guard at VA `0x00E02F64` and `0x00E02F68`. The to-class dry run
refused a single-class move. Prove the shared provider before changing
either table's slot binding.

The [tree-buffer fold investigation](../../reverse/attempt_support/tree-buffer-table-class-fold-20261112.md)
identifies the shared-header and member-lifetime prerequisite for
`0x007CEEA4`.

### Rva000906DE abstract table (2026-11-12)

Retail's table at `0x007C7E94` starts with four `__purecall` entries and
ends at the scalar deleting destructor at `0x000906DE`. The compiler
now emits all five targets in that order. The real constructor emits
the table, so the synthetic emission overload has been removed.

The emitter and its qualified destructor caller in
`Rva007B6880Thunks.cpp` verify 938 functions and 15 data rows. Their
link preview preserves 9,750 bytes on index `80569f4278`. The caller
emits no competing table. The next real link must confirm bridge
retirement for this name.

2026-11-12 Survey rows sourced from DieModuleDerived.cpp are historical: the scaffolding file retired (HeroDie, the last fake-MI branch; ten of ten). The surveyed kept-name slot-0 mappings (e.g. ??_EUpgradeDie@@UAEPAXI@Z -> 0x00486BE4) reached retail through the ??_E->??_G weak-alias bridge and are unchanged; the class TUs now emit the same 28B deleting dtors under real names, byte-proven against DieModuleDerived_pre.obj this session.

### Abstract placeholder tables: 42 off the bridge by declaring retail's slots (2026-11-12, seat halilkkaya-lk91)

Base `03f9e287ede`; measure lk74_snap/lk74_cmp with HEAD's `vtable_bridge.py`; census index `c31795c94c`.

**Survey.** The named grab-bags are expensive: AIStateRva0034005DCtor.cpp (23) needs the State base view and
placeholder renames, Rva005EE30CDerived.cpp (19) and FamilyTailDtors1DBAC3.cpp (13) need ICF twins of other
classes' bodies, and the Derived destructor grab-bags (Rva0024A797, Rva004DF7C2, Rva0058A0F4, Rva004BB68E) need
lk82-84's split per class. A global scan found 117 bridged tables whose every wrong or missing slot is
`__purecall` in retail (abstract bases whose views declare only the destructor). That recipe was taken.

**Done (commits by subject).**
- "Declare the retail slots of four short kept vftables in their emitters": `Rva0032989F` (0x00C0D8FC) and its
  base view (0x00BC9574), `Rva0043DABD` (0x00C3D954), `CommandPointsUpgrade`'s UpgradeMux table (0x00C59060):
  each view declares the class's existing virtual rows.
- "Declare the __purecall slots of sixteen abstract placeholder vftables" (InlineDtorDeletingDtors1/2.cpp; the
  second emitter Rva0054F434Dtor.cpp names its base slots 6 and 12 after its derived overrides, retail's
  positions).
- "Spell out six cleanup-deleting classes with their retail __purecall slots" (BfmeResourceEnumerator.cpp; the
  macro is unchanged, its standalone destructors carry absent-from-retail).
- "Declare the __purecall slots of ten BfmeDirtyBase-derived vftables" and "... of Rva00666BA0 and
  Rva00661350" (every emitting unit changed together).
- "Row six BfmeDirtyBase-derived deleting destructors as their ICF twins" (lk68's slot-0 recipe,
  `add_match.py --icf-owner`, fold-proof to the owner's unit).
- "Declare the __purecall slots of five more abstract vftables" (Rva00140C00, Rva00191120, Rva005CB8D4,
  SubtitleEntry, Rva0057F2DE).

**Measure (base -> after).** Bridged 3,776 -> 3,734; already correct 1,785 -> 1,827; mismatching source slots
40,186 -> 39,787; 42 bridged -> correct, nothing newly bridged, no correct table lost, refusals identical
(35). link_check over every changed unit and every object that names a changed table: all LINK with bytes
unchanged, except SidesList.cpp, which does not link at the base either; BfmeDirtyBaseDerived.cpp 99 -> 315.
Run link_check over both emitters of a table together: a stale index copy of the other one fakes a
"differs from the first copy" refusal.

**Refused / deferred (re_attempts.log).**
- `??_GRva00661350` (0x006613B0): the slot-0 twin is refused on bytes; Rva00666BA0Derived.cpp calls the
  destructor out of line where retail inlines it (needs a /EHs-c- unit).
- `??_7BfmeDirtyBase@@6B@` (0x00CE0FB8): Y2ScalarDeleters.cpp, the second emitter, instantiates the class.
- `?name@ArmorUpgrade` (0x004B341D): rename.py still refuses the GetSnapshotName respell (lk77's tooling lead).
  The same wall holds slot 2 of four more Upgrade tables, ObjectSMCHelper, TurretAI and MilesAudioManager.

**Next leads.**
1. About 70 pure-only tables are left. Most have a derived class in the same unit, whose table changes when
   the base gains slots: ProgressIndicator (Rva00355D66), Rva000F1B8FBase, Rva0057605DBase, Rva00575E4EBase1
   and Rva00575EEABase1 (both derived tables are correct today), AptDisplayStringBase, Rva00802CA0Base,
   Rva00802EC0Base, Rva007401F6 (W3DAptComponentView3D), DataChunkParser (Rva0041E6BE). Give each base's
   pure slots the names its derived views already override, at retail's positions, as for Rva0054F434Base.
   Several emitters name Rva002BED74, Rva0052B668, Rva006609D0Base and Rva005FBBEE.
2. Interface tables that are `__purecall` from slot 0 (0x00C4EF80, 0x00C40818, 0x00C1C780, 0x00BE2B78 and
   others, shared by many interface views) need views without a virtual destructor. Check the deletes first.
3. CommandPointsUpgrade's primary table (0x00C590A8) needs four slot fixes:
   - a loadPostProcess ICF row at 0x00497805 (fold-proof BattlePlanUpdate.cpp);
   - an xfer ICF row at 0x004B8710 (fold-proof ArmorUpgradeXfer.cpp);
   - the GetSnapshotName to-class move from `Rva004B85F4Named`;
   - a declared getModuleNameKey.
4. The Rampage/Enraged pin retirement pays at most two tables. lk56 measured the canonical view at 8/13 slots
   (loadPostProcess, GetSnapshotName and xfer still to row), so it is a whole-class job, not a pin deletion.

**Tooling compatibility audit** (`03f9e287ede..HEAD`): 24 files modified, none added, moved or deleted;
`rename.py check --range`: 0 renames, 0 problems; tools/, .githooks/ and .github/ name none of the touched
classes or the BFME_VPTR_CLEANUP_DELETING_DTOR macro (still used for Rva009EEA70CleanupDeleting).

### Pure-only tables, second pass: 40 off the bridge (2026-11-12, seat halilkkaya-lk92)

Base `cc46b486242`; measure lk74_snap/lk74_cmp with HEAD's `vtable_bridge.py`; census index `c31795c94c`.

**Survey.** lk91's scan (bridged tables whose every wrong or missing slot is `__purecall` in retail) gave 108 tables
at the base: 37 whose kept copy is merely short (slot 0 right, the view stops early), 14 with a destructor at a
retail `__purecall` slot 0, 14 with a non-pure placeholder there (several bound by `/alternatename` hatches to
`__purecall` or to a real body), 23 in FXParticleSystem units and a few in canonical-class copies. The short ones
were taken: every emitter of a table, and every emitter of a derived table that changes with it, found from the
objects (not from the views) and changed together.

**Done (commits by subject).**
- "Declare the __purecall slot 1 of ProgressIndicator and three listener bases": ProgressIndicator,
  Rva00575E4EBase1, Rva00575EEABase1, Rva0057605DBase; the pure slot is named after the derived override, so the
  correct derived tables 0x00C6E688/0x00C6E6B0 stay correct.
- "Declare the __purecall slots of six abstract interface vftables", "... of seven more interface vftables",
  "... of seven long interface vftables": twenty interface tables at 0x00C4EF80, 0x00C078DC, 0x00C40818,
  0x00C6F248, 0x00C42518, 0x00C40020, 0x00C430E8 (ContainIface20, 94 slots), 0x00C513F0, 0x00C52EE8, 0x00C633C0.
- "Declare the __purecall slots of six abstract base vftables": Rva005F6941Base, Rva005F69F5Base, Rva005F2B22Base,
  Base2, Rva00802CA0Base, Rva00802EC0Base (the two constructor units declare the same slots on their base-less
  views so the derived copies stay identical).
- "Declare the __purecall slots of four subsystems and two registration bases": four SubsystemInterface subclasses
  in GameEngineDeletingBaseDerived.cpp (slot14.. after SubsystemInterface's 14), Rva0052B668 (three emitters),
  Rva005FBBEE (three emitters, plus PlayerPanelMovieClip's second emitter).
- "Declare the __purecall slots of four more abstract vftables": Rva000F1B8FBase, Rva005890A6, Rva006892F0
  (VideoPlayer.cpp), Rva007401F6 (its slot 4 declared as SetLight, the derived override retail holds there).

**Measure (base -> after).** Bridged 3,734 -> 3,694; bridged slots 56,965 -> 56,436; already correct 1,827 ->
1,867; mismatching source slots 39,787 -> 39,373; 40 bridged -> correct, nothing newly bridged, no correct table
lost, refusals identical (35). link_check over every changed unit and every object that references a changed
table: all LINK, bytes unchanged. Each commit's objects differ only in `??_7` COMDATs (no symbol added or
removed, initializers and .bss unchanged).

**Refused / deferred (re_attempts.log, two rows).**
- A derived class is instantiated, so the base cannot take its pure slots alone (C2259): Rva006609D0Base
  (PingThread.cpp news Rva0055011A), Rva0041FE0E (VictoryConditions), Rva005F3444Base (IconSlot, slot 3 an ICF
  getter), Rva002BED74 (stack objects in Rva005CBB0AWrap.cpp). Prerequisite: the derived class's own overrides.
- A derived virtual destructor would move: Base1 (ChecklistUIImpl appends its destructor to the Base1 path;
  retail's 0x00C6F118 has none).

**Next leads.**
1. 17 short tables remain: the deferrals above; BfmeCtor001B3A20.cpp's five (one shared with
   ObjectConstructor.cpp, which also holds Rva00BFC290Base); SiegeDockingBehaviorSecondaryBase (a private header,
   SiegeDockingBehaviorView.h, so the full gate); UpdateModuleInterface, DataChunkParser and AptDisplayStringBase
   (canonical classes or nleigh's InlineDtorDeletingDtorsC01.cpp); `_vtbl_00C40818` (no emitter); BfmeDirtyBase
   (lk91's deferral).
2. The 14 tables with a non-pure slot 0: make the placeholder pure where nothing else binds it and drop the dead
   hatch with it (Cb00359D42's `/alternatename:...=__purecall`, Base00's present-unmatched `dummy`,
   Rva004E9FFD's and FireWeaponCollide's inline empty bodies). PropagandaTowerBehaviorIface and
   DelayedUpgradeUpdateInterface alias their slot to a real body that the derived table uses: those need the
   derived override declared first.
3. The 14 tables with a destructor at a retail `__purecall` slot 0 (lead 2 of lk91): retail's derived destructors
   are then non-virtual (Rva00527827's 0x00C68088 has no destructor slot), so each fix renames the derived
   `??1`/`??_G` rows; not attempted.
4. 23 FXParticleSystem tables (CategoryModuleInfo/ModuleInfoSecondBase interfaces, all one-slot `__purecall`):
   claim each unit and check its last 24 h of commits first.

**Tooling compatibility audit** (`cc46b486242..HEAD`): 51 Code files modified, none added, moved or deleted; no
class, function or row renamed (`rename.py check --range`: 0 renames, 0 problems); tools/, .githooks/ and .github/
name none of the touched classes (`Base2` appears only in a synthetic test fixture of test_rename_collisions.py).

### Slot-0 ICF twins, pure placeholders and ModuleData slot 14 (2026-11-12, seat halilkkaya-lk93)

Base `c735099a9c8`; measure lk74_snap/lk74_cmp with HEAD's `vtable_bridge.py`; census index `c31795c94c`.

**Survey (all 3,694 bridged tables, by the kinds of their wrong slots).** Slot kinds: P retail `__purecall`; M the
kept copy stops before a retail body; D an unrowed deleting destructor where retail has another class's (ICF twin
candidate); N an unrowed placeholder name; W a name rowed at another address; U other unrowed. Buckets:
(a) pure-only 68; (b) D only, plus P/M, 502; (c) short only (M, maybe P) 782; (d) N only, plus P/M, 547; (e) mixed
1,795. 67 kept copies are longer than retail. 647 tables have exactly one non-pure wrong slot: W 220, N 173, D 172,
U 48, d 34. Largest sources: RvaSmallVtableCtors.cpp 118 (b 65, e 39, c 12, a 2), Rva0024A797Grandchildren.cpp 82
(d 23, e 59), ParticleModuleInfoCopyCtors.cpp 72 (b 37, e 34), Rva0024A797Derived.cpp 72 (d 47, c 25),
ModuleCtorChainsB.cpp 63 (e 60), FXParticleSystem.cpp 58 (b 45), FXParticleSystemFactories.cpp 49. Two single-cause
clusters stood out: 100 tables whose only wrong slot is a deleting destructor (70 with our `??_GX` defined but
unrowed, 26 a strongly defined `??_E` adjustor thunk, 4 rowed elsewhere), and 179 module-data tables whose slot 14
is `?slot14@ModuleData@@UBE?AVAsciiString@@H@Z` (67 with no other wrong slot), retail's 0x000B69A1 rowed under the
placeholder `Rva000B69A1`.

**Done (commits by subject).**
- "Declare the __purecall slots of four placeholder vftables, drop two dead hatches": Cb00359D42 (0x00C1C780),
  Rva004E9FFD (0x00C62888), Rva0057BCD7 (0x00C6F248, nine slots), ClearanceTestingSlowDeathBehaviorIface5
  (0x00BE2B78). The `/alternatename:?cb@Cb00359D42...=__purecall` and `?base0@Rva0057BCD7Base0...=__purecall` lines
  were dead (the bridge reads the relocation, not the alias) and went with their register keys.
- "Row fifteen slot-0 deleting destructors as their ICF twins" (lk68/lk91's recipe run over the whole cluster):
  `add_match.py --icf-owner` for `??_GX` at the owner's address; where the twin calls the class's own out-of-line
  destructor, `??1X` was rowed first as the twin of retail's callee. No source change. 15 tables: BfmeAudioEventPrefix136,
  Rva002DA5D3, Rva002DA651, Rva002D3347, Rva00577FE2Base, LaserFXNugget, Rva005641BB, DamageModule (ObjectModule path),
  Rva004885DE, Rva00808CB0LanGameEntry, DrawModule, three MultiListClass instantiations, SubsystemSlot<Rva0022C38BSubsystem>.
- "Respell ?DoPlay@Rva0057C04F@@QAEXH@Z as virtual ..." and "Give Base00 and Rva0057C04F retail's slots, drop two
  present-unmatched dummies": Base00 (0x00C6FFFC) is two `__purecall`; Rva0057C04F (0x00C6F2D4) overrides slot 0 with
  the +0x18 flag getter, rowed as the ICF twin of 0x004C9990, and slot 1 with DoPlay.
- "Move ?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z into ModuleData as ?slot14@ModuleData@@UBE?AVAsciiString@@H@Z
  ...": `rename.py function --to-class ModuleData` admitted by retail_identity's MODULE_DATA_SLOT14 base entry (LINK-223's
  missing identity), and BfmeModuleData.h now declares slot14 instead of defining it inline. The rename alone turned 151
  bridged tables into refusals (target-not-winning-provider: 17 BfmeModuleData.h units emitted a COMDAT copy ahead of
  the row's unit); with the header change the row's unit is the only definer and all 67 single-cause tables go correct.

**Measure (base -> after, lk74_cmp).** Bridged 3,694 -> 3,606; bridged slots 56,436 -> 54,229; already correct 1,867
-> 1,955; mismatching source slots 39,373 -> 39,252; 88 bridged -> correct, nothing newly bridged, no correct table
lost, refusals identical (35). link_check (census c31795c94c): the pure-slot units and every object naming the
changed tables, the 15 ICF rows' units and every other definer of the new names (34 of 34 LINK, 61,945 -> 62,768
bytes), the Rva0057C04F family (7 of 7, 9,406 -> 9,410) and the slot-14 move (148 units: 145 LINK, 52,285 -> 52,337;
EvacuateDamage.cpp, AutoDepositUpdateModuleDataCtor.cpp and StructureToppleUpdateModuleDataCtor.cpp did not link at
the census either). A full incremental ./build.sh after the header edit: FULL GATE OK, 100,822/100,822 matched.

**Hatches.** alternatename -2 (Cb00359D42::cb, Rva0057BCD7Base0::base0), present_unmatched -2 (Base00::dummy,
Rva0057C04F::dummy). `hatch_counters.py --update` also offered to shrink other seats' keys (peerMangle.c `_ntohl@4`,
two pins, two export_alias allow stamps); those lines were restored, so the commit holds only its own keys.

**Refused / deferred (re_attempts.log, three rows).**
- 36 slot-0 ICF twins: the twin calls the class's own out-of-line destructor, which compiles as `jmp` to the base
  destructor (v3_rnd.cpp's four randomizers, NetFrameCommandMsg, Rva005C44A3) or another shape, while retail's twin
  calls the base destructor directly. Prerequisite: an empty inline base destructor in the emitting view (several
  are canonical headers: NetCommandMsg.h, v3_rnd.h).
- 9 slot-0 ICF twins refused on the deleting destructor's own bytes (Rva0044BA33, Rva00217497, Rva000657D9,
  Rva002293F9, Rva003E3C22, Rva007B12F0Base, Rva00661350, BFME2Encoding1/2MotionChannel).
- Lead-2 placeholders a derived table still names: Rva000BFB76Interface (W3DScriptedModelDraw's correct table names
  the base row), PropagandaTowerBehaviorIface, DelayedUpgradeUpdateInterface, ClickReactionBehaviorIface. Also
  BfmeParserBindingBaseVE (DataChunkParser's canonical table) and the CaveContain/TunnelContain B5 path.

**Next leads.**
1. 35 more slot-0 ICF candidates whose tables also miss `__purecall` slots (16 in RvaSmallVtableCtors.cpp, the
   BfmeDirtyBase family's second names Rva0065F130 etc.; GapBodiesGE31/41, TooltipBase, Rva005D0D85Base/Rva005D12E3Base,
   LANAPIInterface, GameSpyBuddyMessageQueueInterface, Y2ScalarDeleters' views): row the twin, then declare the pure
   slots (lk92's addp.py). RVAs were claimed and released untried.
2. 26 tables whose slot 0 is a strongly defined `??_EX@@W..` adjustor thunk (FXParticleSystem's ConcreteModuleTemplate
   family, AudioManager, W3DStatusCircle, Line3DClass, ProcessAnimateWindow's ??_E defined by
   ProcessAnimateWindowSpiralCtor.cpp): find why the unit materializes the vector deleting destructor.
3. 137 one-slot tables keep `__purecall` where retail has a body; 31 of them are the BehaviorModuleInterface getter
   fold 0x004543A9 (`return object ? object+0x20 : 0`), e.g. BattlePlanUpdate/MissileLauncherBuildingUpdate slot 25,
   SpawnUnitBehavior slot 11, AutoPickUpUpdate slot 27, RainOfFireUpdate slot 31: declare the class's slotNN override
   as SpecialAbilityUpdate.h does for slot 25 and row the ICF twin.
4. 71 tables need only rows of their own class declared or respelled virtual (`rename.py function --virtual`), e.g.
   MemberBaseDtorsB01.cpp Rva005FB1AD (four QAE rows), Watchdog, Rva0053FADE, AISpecialPowerUpdate/ThreatFinderUpdate
   slot 45 mapLoadPostProcess, SpawnBehavior (four tables), LivingWorldLogic OnRegionChangedOwnership (two tables).
   The `?name@X@@QBEPBDXZ` GetSnapshotName slot-2 cases stay on lk77's rename.py tooling lead.
5. Naming lead: TextureCategoryList and FVFCategoryList (0x001446F0/0x00144750 owners) fold with
   MultiListClass<DX8TextureCategoryClass>/<DX8FVFCategoryContainer>; they are probably those template instantiations.

**Tooling compatibility audit** (`c735099a9c8..HEAD`): 40 files modified, none added, moved or deleted;
`rename.py check --range`: 0 problems. tools/, .githooks/ and .github/ spell none of the renamed or touched names
(retail_identity.py already names 0x000B69A1 by its new spelling; rename.py mentions only BfmeModuleDataSnapshotBase in a
comment). The old `?rva000B69A1@Rva000B69A1@...` spelling remains in evidence files rename.py listed and left
(five reverse/attempt_support files, 33 class_contracts JSON notes, name_tiers.csv).

### Getter folds, interface overrides and ModuleData stand-ins: 76 off the bridge (2026-11-12, seat halilkkaya-lk94)

Base `ed9d78f95f6`; measure lk74_snap/lk74_cmp with HEAD's `vtable_bridge.py`; census index `c31795c94c`.

**Survey refresh (lk93's survey.py).** At the base: 3,606 bridged tables, buckets a 63, b 503, c 782, d 478, e 1,780;
585 tables with exactly one non-pure wrong slot (W 221, D 173, N 108, U 49, d 34). After this pass: 3,530 tables,
a 68, b 488, c 753, d 477, e 1,744; 532 one-slot tables (W 186, D 158, N 107, U 47, d 34). Two clusters were larger
than lk93 counted: 32 one-slot BehaviorModuleInterface tables whose wrong slot is retail's getter fold 0x004543A9, and
68 ModuleData-derived tables whose kept copy stops after slot 0 (36 with exactly ModuleData's default 30-slot tail).

**Done (commits by subject).**
- "Override the +0x20 interface getter in 28 module views (retail 0x004543A9 fold)": each emitting view declares the
  slot (slotNN, getDie, getDamage, getUpgrade, getCollide) and defines it out of line as the null-preserving cast to
  its +0x20 base; `add_match.py --icf-owner` rows it (owner `?get@Rva004543A9LeaNegSbbField@@UBEHXZ`, fold-proof
  GettingBuiltBehavior.cpp). 16 views in Rva0024A797Grandchildren.cpp plus BloodthirstyUpdate, ClickReactionBehavior,
  SiegeDockingBehavior, ShareExperienceBehavior, SpawnUnitBehavior, AutoPickUpUpdate, BattlePlanUpdate,
  LargeGroupAudioUpdate, EmotionTrackerUpdate, RainOfFireUpdate, Rva0044EF5E, MissileLauncherBuildingUpdate's private
  SpecialAbilityUpdate (declares the rowed slot25) and DockUpdate::slot22 (rowed only). 30 tables. Siblings that emit
  the same table from their own view (SiegeDockingBehaviorDtor.cpp, EmotionTrackerUpdateDtor.cpp) declare it too.
- "Row three ModuleData deleting destructors as their ICF twins at 0x004A10FD": `inline ModuleData::~ModuleData() {}`
  (29 units already have it) makes the implicit ~X retail's 7-byte vptr store at 0x0049B47C. 3 tables.
- "Declare five classes' rowed interface overrides in their emitting views": SpawnBehavior (three interface tables;
  its views now include the registered DieModuleInterface.h), CaveContain B5, AIUpdateInterface's +0x20 table,
  OathbreakersFadeAwayBehavior, ModelConditionAudioLoopClientBehavior Secondary10. 7 tables.
- "Row ten slot-0 deleting destructors as ICF twins, declare five tables' __purecall slots" (lk93 lead 1) and "Row
  four more slot-0 deleting destructors as their ICF twins": 7 tables (Rva003889DF, Rva0059667D, Gen007F4D00Listener,
  Rva007F6D60ChildBase, Rva00672490View, StructureCollapseUpdateModuleData, Impl; ImplBase, newly bound to retail by
  ??1Impl's vptr store, is measured correct instead of newly bridged).
- "Derive 19 stand-in ModuleData views from the canonical ModuleData", "Derive five more ModuleData views from
  ModuleData, constructor units included", "Give two stand-in ModuleData views their family's 31-slot base" and
  "Derive SlavedUpdate and ModelConditionSoundSelector module data from ModuleData": the EmitVtableTag stand-ins
  (FamilyDeletingDtors_muse-*.cpp, *ModuleDeletingDtors.cpp) and five base-less constructor-unit views take ModuleData
  (Rva00253487Base.h for the upgrade-data shape, ActiveBodyModuleData's rowed slot07). 28 tables.
- "Give WorkerAIUpdate's AI command view its aiDoCommand slot, drop the dead alias": as HordeWorkerAIUpdateDtor.cpp.
  1 table, alternatename -1.

**Measure (base -> after, lk74_cmp).** Bridged 3,606 -> 3,530; bridged slots 54,229 -> 51,778; already correct
1,955 -> 2,032; mismatching source slots 39,252 -> 38,329; 76 bridged -> correct, nothing newly bridged, no correct
table lost, refusals identical (35). Five still-bridged tables moved one slot toward retail (TooltipBase,
LANAPIInterface, GameSpyBuddyMessageQueueInterface, Rva005D0D85Base, Rva005D12E3Base: slot 0 now rowed); two derived
tables (Gen007F4D00's Listener table, Rva007F6D60Child) now carry inherited `__purecall` where the kept copy used to
stop. link_check (census c31795c94c) over every changed unit and every other definer of each changed table and new
name: all LINK; two units that did not link at HEAD stay so (OpenContainCtor.cpp, stale index after lk92;
BuddyThread_Unresolved.cpp, an STLport deque body).

**Refused / deferred (re_attempts.log).**
- 0x004A10FD ModuleData twins (UnpauseSpecialPowerUpgrade, FXListDie, KeepObjectDie, LockWeaponCreate,
  PhysicsBehavior module data): the implicit ~X jumps to an out-of-line base destructor (DestroyDieModuleData.h, a
  private UpdateModuleData view, Rva00253487Base).
- 17 slot-0 twins refused on the deleting destructor's own bytes (14 in RvaSmallVtableCtors.cpp, GapBodiesGE41,
  W3DAptComponentColorPicker, Y2ScalarDeleters' Rva00666BA0View): ours inline the class destructor where retail calls
  it, and some differ in the delete cleanup (unit flags). Pure slots deferred: TooltipBase (the unit news the derived
  class), LANAPIInterface (needs LANAPI's 58 slot names), Rva005D0D85Base/Rva005D12E3Base
  (OpaqueScalarDeletingDtorsB16.cpp and StrategicInGameUITacticalBattleResolverStateForward.cpp emit the derived
  tables from one-slot views), GameSpyBuddyMessageQueueInterface (shared BuddyThread.h).
- Nine more twins: five SpecialPowerModuleData classes (retail's ??1 is a bare jmp, ours stores the vptr first),
  TunnelContainModuleData, TooltipUpgradeModuleData, Gdiplus Image/Bitmap.
- DeflectSpecialPowerModuleData: DeflectSpecialPower.cpp derives it from an AIUpdateModuleData view while retail's
  table is ModuleData's default tail. GarrisonContain, SiegeEngineContain, HordeSiegeEngineContain and
  RiderChangeContain module data were tried and reverted: their constructor units emit the table from other views
  (link_check refused all four).

**Next leads.**
1. FX getClass (25 one-slot tables: FXParticleSystemFactories.cpp 17, FXParticleSystem.cpp 6,
   VectorDeletingDtorsV06.cpp 2): CategoryModuleInfo<N>'s slot 0 is retail's getClass (rowed in
   NamedModuleClassInstances.cpp and FXParticleSystemModuleGetClass.cpp), but the units call it `v1`, the name
   ConcreteModuleTemplate also uses to override the INFO bases' slot 1. Declare `getClass` (covariant on
   CategoryModuleClass<CAT>) in CategoryModuleInfo and ConcreteModuleTemplate, and keep `v1` only where the INFO base
   has it, or it becomes a new primary slot.
2. The remaining ModuleData short tables: the contain family's constructor units (other OpenContainModuleData views,
   TransportContain.cpp's private one), the five W3D draw module data (W3DModelDrawModuleData overrides at 14/18/22/30),
   BaseUpgrade/CostModifierUpgrade (private Rva00253487Base view with an inline Snapshot teardown), RespawnBody
   (ImmortalBody.cpp also emits it), TerrainResourceBehavior, Deflect.
3. 15 FX tables keep `__purecall` where retail has 0x0055E636 (ModuleCtorChainsB.cpp, ParticleModuleInfoCopyCtors.cpp).
4. Naming: BehaviorModule's slot 20 is getUpdateExitInterface (QueueProductionExitUpdate and
   SpawnPointProductionExitUpdate keep slot20 because their getter is rowed under that name); Watchdog's
   `?start@Watchdog@@UAEXXZ` (0x002256C0) is ThreadClass's slot-1 Execute override; TauntPointFilter's rowed `Allow`
   versus PartitionFilter.h's `allow`; DeployStyleAIUpdate's `?rva0048E8F7@...@@QAE...` is aiDoCommand (respell);
   TunnelContain's B5 slot needs the shared B5.h (and its alias) changed.
5. WorkerAIUpdateDtor.cpp still aliases f2/f4/wt0..wt2 placeholders onto real slots; each is the same one-view fix.

**Tooling compatibility audit** (`ed9d78f95f6..HEAD`): 64 files modified, none added, moved or deleted;
`rename.py check --range`: 0 renames, 0 problems; tools/, .githooks/ and .github/ name none of the touched files or
classes.

### FX getClass, FX base pure slots and tiny-body ICF twins: 78 off the bridge (2026-11-12, seat halilkkaya-lk95)

Base `9ace59152e2`; measure lk74_snap/lk74_cmp with HEAD's `vtable_bridge.py`; census index `c31795c94c`.

**Survey refresh (lk93's survey.py).** At the base: 3,530 bridged tables, buckets a 68, b 488, c 753, d 477, e 1,744;
532 tables with exactly one non-pure wrong slot (W 186, D 158, N 107, U 47, d 34), as lk94 left them. Grouped by the
retail target of the one wrong slot, the clusters were: 32 FX tables whose slot is a wrapper's getClass (lk94 lead 1),
23 tables where retail has `__purecall` and the kept copy a deleting destructor or a placeholder (17 of them the
one-slot FX table 0x00C1C780), 15 FX tables at 0x0055E636 (lk94 lead 3), 10 at the empty body 0x000B3FD0, 9 FX
`W7` deleting-destructor thunks (0x003A96BD/0x003A9655/0x003A9685), 7 at 0x0047A69C and 5 Snapshot-only FX info
tables at 0x003A7ABD. After this pass: 3,452 tables,
a 47, b 466, c 741, d 442, e 1,756; 495 one-slot tables (W 185, D 159, N 75, U 43, d 33).

**Done (commits by subject).**
- "Declare getClass in the FX category info and Snapshot slots in its info views" (lk94 lead 1): CategoryModuleInfo<N>'s one
  slot is `getClass() const = 0`, overridden covariantly by ConcreteModuleTemplate<TAG> under the rowed name
  (`UBEABV?$ConcreteModuleClass@...`); no primary slot is added. The placeholder info views (DefaultDraw/Update/Alpha/Color,
  RenderObjectDraw, GpuDraw, LightningDraw, RenderObjectUpdate, TerrainCollision; Modules' Streak/Quad/Butterfly) derive
  from ::Snapshot with their rowed LoadPostProcess/GetSnapshotName/DoXfer; the emission-volume module templates leave
  getClass pure (retail 0x00C1C780), so FXParticleSystem.cpp's six placeholder template globals go. All four emitters
  (FXParticleSystemFactories.cpp, FXParticleSystemModules.cpp, FXParticleSystem.cpp, VectorDeletingDtorsV06.cpp) change
  together: the census keeps Modules' copy, the real link Factories'. Covariance instantiates the wrapper class where the
  wrapper template is instantiated, which instantiates its tag's KEY/NAME initializers; Factories' clone specializations
  move next to their wrappers (event wrappers after the draw wrappers) and Modules' draw factory declarations ahead of
  the named wrappers, so both units' _$E sequences are unchanged by target (Modules' rowed _$E158/_$E160 untouched).
  The DefaultParticleModule<2> update tag has no retail wrapper: Factories no longer builds it, and Modules (whose
  numbered initializers depend on it) defines its getClass as a tail jump into the named update class's rowed
  getInstance, the bytes of retail 0x003AD131. 35 tables.
- "Row five FX info vector deleting destructors as their ICF twins at 0x003A7ABD": an absent-from-retail anchor in
  FXParticleSystem.cpp array-news EmissionVelocityInfo and the DefaultDraw/Streak/Quad/Butterfly infos; each ??_E is
  rowed as the twin of VectorDeletingDtorsV01.cpp's ??_ERva0049B47C. 5 tables.
- "Adopt the canonical Rva003AEEB3 and DefaultModuleHeadBase in three FX base units": DefaultModuleBaseCopyCtors.cpp,
  DefaultModuleHeadBase.cpp and ParticleModuleInfoCopyCtors.cpp include Rva003AEEB3.h / DefaultModuleHeadBase.h instead
  of private copies; the DefaultModuleSecondBase/ThirdBase views and their two present-unmatched markers go
  (present_unmatched 1,853 -> 1,851). 6 tables.
- "Declare retail's pure slots in the 0x003AE7B8 and 0x003AE6A9 copy-constructor views": one pure slot and no destructor
  for the second base; slot01..slot10 pure along the head chain (0x00C1B590, 0x00C1D420, 0x00C1D520). 5 tables.
- "Give three FX category templates' second base retail's one pure slot" (LifeEvent, TerrainCollision,
  RenderObjectDraw copy-constructor thunks). 3 tables.
- "Declare UpdateModule's third interface slot in its two table emitters" (UpdateModuleCtor.cpp,
  Rva0024A797DeletingDtor.cpp: rva0044DF8D(UpdateSleepTime), pure in the interface, UpdateModule's rowed override). 2 tables.
- "Declare DataChunkParser's pure slot in the base-template parser unit". 1 table.
- "Row six classes' empty slot 1 as ICF twins of 0x000B3FD0": Rva005E92F7RecordBase, Rva005F8CB0Base0, Rva005F830A,
  Rva005D06CBB1, Rva005D073AFirstBase and Rva001517DE declare an empty slot01 after the destructor, rowed as twins of
  ??1Region2D@@QAE@XZ; the constructor units emitting the same tables (Rva00151866Ctor.cpp, Rva005F830ACtor.cpp,
  Rva005D0B5ECtor.cpp, Rva005D0BDDCtor.cpp) declare it too. 7 tables.
- "Row three empty virtuals as ICF twins of 0x000B3FD0" (WaterTransparencySetting::slot1,
  SpawnedModelConditionCreate::onCreate, Anim2DCollection::reset: rows only). 3 tables.
- "Row five defined slot bodies as ICF twins of the shared tiny bodies retail holds" (Rva0078D310Host::vslot10 and
  HordeContainInterface::slot136 at 0x0047A699, W3DBoatWakeModelDrawModuleData::slot20 at 0x0047A6A9,
  LivingWorldObserver::onLivingWorldEvent at 0x001F01E8, WallHubBehaviorModuleData::slot06 at 0x0050B5C6: rows only).
  5 tables.
- "Give Rva0083702CObserver's slot 0 retail's shared `ret 4` body" (0x0047A69C). 1 table.
- "Give the TerrainLogic listener views retail's empty slot 2" (`ret 8` 0x0050B238; TerrainLogicCtor.cpp,
  W3DTerrainLogic.cpp and TerrainLogicDeleter.cpp). 4 tables.
- "Give Rva005F5C77Base0's slot 1 retail's shared empty body". 1 table.

The tiny-body pass is a reusable sweep: for a bridged table whose only wrong slot is unrowed (or pure) and whose retail
target is a matched row of at most a few bytes (`ret`, `ret N`, `xor al,al; ret`), define the slot in the emitting view
with the same signature and let `add_match.py --icf-owner` verify the twin; every other emitter of the table must
declare it too or link_check refuses the comdat.

**Measure (base -> after, lk74_cmp).** Bridged 3,530 -> 3,452; bridged slots 51,778 -> 51,395; already correct 2,032 ->
2,110; mismatching source slots 38,329 -> 38,200; 74 bridged -> correct and 4 bridged names gone (the
DefaultModuleSecondBase/ThirdBase spellings; their respelled tables are correct), nothing newly bridged, no correct
table lost, refusals identical (35). 13 still-bridged tables moved toward retail, none away. Initializers: Factories'
and Modules' `_$E` sequences unchanged by target; FXParticleSystem.cpp lost only the 12 initializers of its six
placeholder module-template globals (unrowed), the rest keep their order. link_check (census c31795c94c) over every
changed unit and every other definer of each changed table: all LINK, LINKED never lower (+1 to +10 bytes where a
row was added). ThrowingNewHelpers.cpp does not link standalone at HEAD (`selected ?reset@Rva005CE236`), unrelated to
this pass and untouched by it.

**Hatches.** present_unmatched 1,853 -> 1,851 (DefaultModuleBaseCopyCtors.cpp's two keys, with the views they described).

**Refused / deferred (re_attempts.log).**
- 0x0055E636 / 0x0055DBD3 / 0x0055CAAC (lk94 lead 3, 23 tables): the FX module slice slot is a per-module override
  retail ICF-merged; the rows are free `__stdcall` names, so both views (ModuleCtorChainsB.cpp, ParticleModuleInfoCopyCtors.cpp)
  need one shared slice class and the rows respelled as its overrides.
- The 9 W7 thunk tables (0x003A96BD/0x003A9655/0x003A9685): the thunk twins need their ??_E targets rowed, and no unit
  emits those ??_E (no array new); prerequisite: anchors where the wrapper destructor stays out of line.
- 0x00C1C780 views whose base destructor is rowed or referenced virtual (Rva002214A6, Rva005DCC4B, Rva004E5654Base,
  Rva00574CC1Base14): respell the destructor non-virtual first. ParticleModuleTemplateClones.cpp (the derived wrapper
  is new'd; its slot is a getClass), BfmeMakeBZA.cpp (the derived slot is ?run@Rva007F4440Runner), Rva005F3444Base
  (IconSlot's slot-3 getter fold), SecondBase005D2111 (one placeholder name aliased to two retail bodies).
- Withdrawn before commit: Rva005CE8F5's slot01 (also emitted by Rva005CF4A8SelectionCtor.cpp and ThrowingNewHelpers.cpp,
  the latter edited by another seat today) and TerrainFXShaderParameterSourceNamespace::setRenderingMode (0x002E6A93's
  only row is the gen-alias ?dup_002e6a93@@YAXXZ, GameSlot::setTeamNumber); both landed log rows voided.

**Next leads.**
1. More tiny-body twins: the last sweep listed 30 one-slot tables (18 distinct kept names); 5 landed, 6 were refused
   because the kept name is only declared in its unit (define it, as Rva0083702CObserver), one waits on a gen-alias
   owner, and the rest are ambiguous placeholders, vendored names (strstreambuf::setbuf, GDIFileStream::read) or
   ModuleData::crc. Pure-kept tables with a tiny retail body remain too (Radar, MineshaftPortalNetworkManager and
   DelayedExperienceLevelGrantSystem SubsystemInterface slot 1, DozerAIInterface slot 31, ExperienceLevelCreate slot 0,
   Rva00210CC5, Rva0056AD19): declare the class's override with an empty body and twin it.
2. The W7 thunk chains (9 tables) and the 0x00C1C780 virtual-destructor views above.
3. lk94 leads 2, 4 and 5 stand (ModuleData short tables, BehaviorModule slot 20 naming, WorkerAIUpdateDtor.cpp aliases:
   its remaining tables are multi-slot, so each alias fix moves a table without taking it off).

**Tooling compatibility audit** (`9ace59152e2..HEAD`): 33 files modified, none added, moved or deleted;
`rename.py check --range`: 0 renames, 0 problems; tools/, .githooks/ and .github/ name none of the touched files or
removed view classes (they mention only the FXParticleSystem namespace and one fixture row for W3DTerrainLogic).

**2026-11-12, seat halilkkaya-lk96: StructureBody's dummy vptrs.** The ctor (0x004C0951) already stored
`??_7Rva004C0988@@6BRva004BF951@@@` at +0; its +0x0C/+0x10 stores were TU-local zero ints. They now name the two
tables the same definer (StructureBody.cpp) emits for placeholder Rva004C0988, mapped by retail's immediates:
0x00C5AD78 `??_7Rva004C0988@@6BMiBase1@@@` (47 slots) and 0x00C5B5B0 `??_7Rva004C0988@@6BRva004C0988_B2@@@` (43),
both bridged ("Store StructureBody's real secondary tables instead of zero dummies"). Bytes exact; scoped DIR32 OK;
19/19 StructureBody units LINKS unchanged; bridge plan unchanged. This fixes the run-time vptrs only; the ActiveBody.h
walls above still stand for the class's own view. Remaining dummy-vptr ctors on the boot walk: LINK-627's
2026-11-12 inventory.

### Shared tiny bodies, empty overrides and collide defaults: 62 off the bridge (2026-11-12, seat halilkkaya-lk97)

Base `decf61df826`; measure lk74_snap/lk74_cmp with HEAD's `vtable_bridge.py`; census index `c31795c94c`.

**Shared-cause ranking (all 3,448 bridged tables at the base; a table counts when every wrong slot is covered).**
1. Unrowed tiny bodies: every wrong slot names a symbol with no ledger row whose retail target is a matched body of at
   most 8 bytes: 121 tables (90 with names consistent across tables; 26 already compiled byte-equal, rows only).
2. Pure-only (bucket a): 47. 3. Only 0x000B3FD0 (subsystem init/reset/update): 40. 4. Only `ret 4` 0x0047A69C: 26.
5. Module Snapshot pair (slot 1 = the 0x00497805 base-call fold, slot 2 = the class's name getter rowed under
   `?name@X` / `?RvaNNNNNNNNGet` placeholders): 22 exactly; 0x00497805 is a wrong slot in 155 tables.
6. SpecialPowerModule's BehaviorModuleInterface slots 8/43/44 (0x002533D3, 0x00251C11, 0x00251C24, the last two rowed
   as Rva placeholders in VslotSmallBodiesAG.cpp): 18 (6 in a unit another seat holds).
7. FX CategoryModuleTemplate<N> ModuleTemplate tables (??_E 0x00001EAE + 3 pure, FXParticleSystem.cpp): 17.
8. RenderObjClass Set_Animation (0x000D1407) + `ret 4`: 17. 9. FX slice slot 0x0055E636: 15.
10. Collide interface slots 1..5 (0x005CB9FF + 0x0047A699) in one-slot collide sub-tables: 14.
11. UpdateModule interface slots 0x0044DF8D + 0x004A2D67: 11 (+10 with 0x00253376). 12. StateMachine
    GetSnapshotName + xfer: 15. 13. Snapshot stand-ins (own ??_E, retail ??_ESnapshot + 3 pure): 10.
14. AIInternalMoveToState slot 7 (0x0033F2D7): wrong in 30, never alone. 15. MiBase1::f1 (0x000D43D0): 58, all multi-slot.

**Done (commits by subject).**
- "Row 83 compiled tiny virtuals as ICF twins: 26 vftables off the runtime bridge" and "Row 13 more compiled small
  virtuals as ICF twins: five vftables off the runtime bridge": cause 1 as a sweep (lk97/tiny.py, prefilter.py):
  rows only, add_match --icf-owner per slot; targets referenced by fewer than four retail words were left for a
  rename (they are the class's own body under a placeholder). 31 tables; present_unmatched 1,851 -> 1,848.
- "Give twelve classes retail's empty overrides for their __purecall slots" (ActionManager, GameStateMap's and
  Rva0041F94A's subsystem tables in both emitters, PlayerAITypeSet, Rva00221027, Rva00427311, GlobalLanguage, Radar,
  MineshaftPortalNetworkManager, ExperienceLevelCreate::onCreate, Rva0086E330Callback, Rva005E62F1 with retail's
  argument count). 12 tables.
- "Give four listener and observer bases retail's empty virtual bodies" (TerrainLogicListenerRootA/B,
  IconMouseObserver, LivingWorldBuildPlotObserver, Rva005D0643Base8). 7 tables.
- "Give the AIUpdate family's collide interface stand-ins CollideModule's five defaults" (Rva0026E836_M4,
  AIUpdateInterface24) and "Give three modules' collide interface views CollideModule's false defaults"
  (CritterEmitterUpdate, BezierProjectileBehavior, DeflectSpecialPower): cause 10. 11 tables.
- "Give the SkirmishAIManager placeholder's constructor view its empty init". 1 table.
- Withheld at landing: the Rva005746AF commit (slots 2..5 of 0x00C6E3B0 as retail's `xor eax,eax; ret 4` 0x005DAA6C
  and three `xor al,al; ret 4` 0x005CB9FF bodies, one argument each, in both emitters' private views) conflicted with
  StarkillerHDX's "Register canonical Rva005746AF, adopt it in 8 units", which replaced those views with the
  generated header. Lead: carry the four slot signatures and inline bodies into reverse/class_contracts/Rva005746AF.json
  (header_adopt_lane.py), then row the twins (RenderObjClass::Remove_Sub_Object, ?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z).
- "Give BezierProjectileBehavior its loadPostProcess base call (retail 0x00497805 fold)": half of cause 5; the
  table moves one slot toward retail.

**Measure (base -> after, lk74_cmp).** Bridged 3,448 -> 3,385; bridged slots 51,335 -> 50,594; already correct
2,110 -> 2,173; mismatching source slots 38,155 -> 37,946; 63 bridged -> correct (62 as landed, without the withheld Rva005746AF table), nothing newly bridged, no correct
table lost, refusals identical (36). Two still-bridged tables moved toward retail (BezierProjectileBehavior's primary,
Icon's IconMouseObserver table), none away. Buckets a 47, b 466, c 733, d 430, e 1,709. link_check (census
c31795c94c) over every changed unit, every other emitter of each changed table and every other view of each changed
class: all LINK, LINKED never lower. No alias, pin or marker added; no initializer added.

**Refused / deferred (re_attempts.log).**
- Cause 5's name getters rowed as `?name@<RealClass>@@QBEPBDXZ` (BezierProjectileBehavior 0x0045BFD3 and most of the
  22): `rename.py function --to-class` refuses a row already in its class; the getter needs the prepared `--respell`
  route (name lane) to `?GetSnapshotName@X@@MBEPBDXZ`. Placeholder-class getters (`?name@RvaNNNNNNNNNamed`) take lk76's
  --to-class recipe; free `?RvaNNNNNNNNGet@@YAHXZ` rows were not tried.
- Rva005CF27ABase / Rva00875284Base argument counts (withdrawn before commit): the derived views' argless overrides
  resolve through `/alternatename` lines; respelling them left the new names unresolved (3 units stopped linking).
- BaseHeightMapRenderObjClass's name getter 0x0006D054: BaseHeightMap.h defines it inline while the row sits under
  a placeholder in SubsystemNameGetters.cpp; needs a TU-approved row move first.
- The five all-pure BehaviorModuleInterface tables (CallHelpOnDamage, HitReactionBehavior, RebuildHoleExposeDie,
  CostModifierUpgrade, UpgradeBehaviorBaseView): adopting the canonical DamageModule/BehaviorModule changes
  `struct DamageInfo` to `class DamageInfo` in rowed spellings.

**Next leads.**
1. Cause 5 through the respell route (22 tables, two slots each; the loadPostProcess half is the lk75/lk77 recipe).
2. Cause 6: one SpecialPowerModule override set across ~12 units (rename the two VslotSmallBodiesAG.cpp rows into
   the class); ElvenWoodSpecialPower.cpp is another seat's today.
3. More collide defaults: FireWeaponCollide.cpp's private CollideModuleInterface/CollideModule views, AODCrushCollide
   and DozerAIUpdate's AIUpdateInterface24 (both held by another seat today), GarrisonContain's B6.
4. The pure-kept tables with a tiny shared retail body that remain (lk97/puretiny.py lists them; 0x00210CC5 waits on
   LivingWorldManager.h's BFME_LIVINGWORLDMANAGER_CTOR_PURE, LINK-073).

**Tooling compatibility audit** (`decf61df826..HEAD`): 32 files modified, none added, moved or deleted;
`rename.py check --range`: 0 renames, 0 problems; tools/, .githooks/ and .github/ name none of the changed views'
classes or spellings (fixture mentions of PlayerAITypeSet, GameStateMap, GlobalLanguage, ExperienceLevelCreate and
AssaultTransportAIUpdate are file-level and unchanged).

### The +0x2C damage-shaped interface tables (0x00C58790, 0x00C463D8): 13 off the bridge (2026-11-12, seat halilkkaya-lk100)

Base `257b90ffe74`; measure lk74_snap/lk74_cmp with HEAD's `vtable_bridge.py`; census index `c31795c94c`.

**Refreshed ranking at the base (3,391 bridged).** lk97's list holds. Two clarifications: 0x00497805 (cause 5) is
per class, not one shared declaration: it is every module's own `loadPostProcess` base-call override, ICF-folded, so
each table needs its class's override (lk97's BezierProjectileBehavior recipe) and its class's name getter; the
getters rowed `?name@<RealClass>@@QBEPBDXZ` cannot be respelled by any rename.py route today (`name` is a real
identifier: `inferred` and `canonical` both refuse it, `--to-class` refuses a member of its own class). Cause 6's 18
tables are one retail table, 0x007EFCF8, bound by 18 names; slot 43 is the blocker (below). New family found: the
three-slot interface at OpenContain/UpgradeModule +0x2C, shaped like DamageModuleInterface (ret 4, ret 4, ret 0Ch):
0x00C58790 (empty defaults) and 0x00C463D8 (GarrisonContain's onBodyDamageStateChange in slot 2), 18 tables, most
spelled as one-slot stand-ins (B6, B2C, Iface2C, ModuleInterface, UpgradeTail).

**Done (commits by subject).**
- "Give four UpgradeModule views the three empty UpgradeModuleInterface18 overrides": CostModifierUpgrade,
  DynamicPortalBehaviour, UpgradeModule (dtor unit) and GeometryUpgrade name the rowed `?vslot18_0N@UpgradeModule`
  defaults; no new row. 4 tables.
- "Give OpenContain's +0x2C interface stand-in B6 retail's three empty defaults": B6 in seven units (both emitters of
  the HordeContain and TransportContain tables: differing COMDAT copies made HordeContainDtor.cpp and
  TransportContainCtor.cpp stop linking until all emitters agreed); three ICF twin rows in TransportContainCtor.cpp.
  CaveContain, HordeContain, HorseHordeContain, TransportContain, GarrisonContain: 5 tables.
- "Give three GarrisonContain-derived views B6's defaults and GarrisonContain's slot-2 override": TunnelContain,
  SlaughterHordeContain, ProductionQueueHordeContain. 3 tables.
- "TunnelContainDtor.cpp: drop the dead /alternatename for ?b6@B6@@UAEXXZ": no object names the symbol after the
  above; alternatename register 2,326 -> 2,325.
- "Give TunnelContain's B2C stand-in the GarrisonContain family's +0x2C slots": 1 table, two twin rows.

**Measure (base -> after, lk74_cmp).** Bridged 3,391 -> 3,378; bridged slots 50,662 -> 50,623; already correct
2,171 -> 2,184; mismatching source slots 37,995 -> 37,957; 13 bridged -> correct, nothing newly bridged, no correct
table lost, refusals identical (35). link_check (census c31795c94c) over every changed unit, every other emitter of
each changed table (lk74_definers) and the owners of the twin rows: all LINK, LINKED never lower. No alias, pin or
marker added; no initializer added.

**Refused / deferred (re_attempts.log).**
- Cause 6, `?rva00251C11@Rva00251C11@@QAEXM@Z` (0x00251C11): retail's slot-43 override reads a float
  (`fld [esp+4]`) and forwards it to SpecialPowerModuleInterface::startPowerRecharge; canonical BehaviorModule.h
  spells `slot43(int)`, and `--to-class` refuses the parameter change. Prerequisite: BehaviorModule.h's slot 43
  respelled `Real` together with its base twin row `?slot43@BehaviorModule@@UAEXH@Z` (0x0047A69C); then move
  0x00251C11 and 0x00251C24 (slot 44 calls primary slot 12, `rva00493805`) into SpecialPowerModule and declare an
  inline getSpecialPower (`return this`, the 0x002533D3 fold) in the 12 emitting views.

**Next leads.**
1. Canonical Iface2C (`Code/GameEngine/Include/Common/Iface2C.h`, one slot): the same interface; AODHordeContain,
   HordeSiegeEngineContain, SiegeEngineContain (0x00C58790) and HordeGarrisonContain (0x00C463D8) stay bridged until
   its contract carries the three slots with B6's defaults (header_adopt_lane; full gate; 18 adopting units).
2. HealContain.cpp's Rva00220240FlatDtorM5 (0x00C58790): same fix; that unit was another seat's today.
3. A canonical B6: StarkillerHDX's lane is registering B1/B4/B5/B7 from majority views; B6's retail shape is now the
   three-slot one in 10 units (four sources still declare the old one-slot `b6()` and emit no table).
4. Tooling: a rename route for a retail-proven parameter type (cause 6) and for `?name@<RealClass>` getters to
   `GetSnapshotName` (cause 5, 22 tables) would unlock the two largest shared causes.

**Tooling compatibility audit** (`257b90ffe74..HEAD`): 18 files modified, none added, moved or deleted;
`rename.py check --range`: 0 renames, 0 problems; tools/, .githooks/ and .github/ spell none of the changed views,
symbols or files.

### Shared default bodies for pure and short slots: 16 off the bridge; three canonical-header causes wait on tooling (2026-11-12, seat halilkkaya-lk102)

Base `c8b5c6685e4`; measure lk74_snap/lk74_cmp with HEAD's `vtable_bridge.py`; census index `c31795c94c`.

**Refreshed ranking at the base (3,377 bridged; a table counts when every wrong slot is covered).** Pure-only 47;
only the `ret 4` body 0x0047A69C 20 (mostly views with a virtual destructor where retail has none); cause 6 (one
retail table 0x007EFCF8, slots 8/43/44) 18; FX CategoryModuleTemplate<N> 17; FX slice 0x0055E636 15; collide
slots 12; UpdateModule interface slots 11 + 10; Snapshot stand-ins 10. The module name getters alone hold 31 tables
(14 wrong only at slot 2, 17 only at slots 1-2 where slot 1 is the 0x00497805 loadPostProcess fold). 0x00497805 is
wrong in 154 tables and never alone: of the 11 whose slot 2 is already right, each also needs a class-specific slot
(placeholder ??_G, static getter, getUpdatePhase), so no table comes off from the loadPostProcess half by itself.

**Cause 6 retail evidence (slot 43 is a float).** The two retail overrides of BehaviorModuleInterface slot 43 both
load their argument with `fld dword [esp+4]` and forward it to a float slot 15: 0x00251C11 (SpecialPowerModule,
startPowerRecharge of the +0x10 interface) and 0x00494AC6 (WeaponModeSpecialPowerUpdate, tables 0x0084E998 and
0x0085D9C0, slot 15 of its +0x18 interface). The only caller, Object 0x0028B701 (the +0x244 module scan,
`?rva0028B701@Object@@QAEXM@Z`), passes `fld [esp+8]` / `fstp [esp]` to `call [eax+0ACh]`. The other 37
BehaviorModuleInterface tables hold the `ret 4` default. The 18 bridged names come from 12 units: ElvenWoodSpecialPower.cpp
(7, StarkillerHDX today) and CombineHorde, Devastate, GrabPassenger, ManTheWalls, OCL, PlayerHeal, PlayerUpgrade,
Repair, SplitHorde, UntamedAllegiance and SpecialPowerModuleCtor (+ SpecialPowerModuleDtor_Unresolved.cpp, the second
SpecialPowerModule emitter).

**Done (commits by subject).**
- "Give the four production-exit modules retail's update() that sleeps forever": DefaultProductionExitUpdate,
  SupplyCenterProductionExitUpdate, SpawnPointProductionExitUpdate and Rva00452D52 (0x00C4B1E0 slot 0 = 0x004A6563).
  4 tables.
- "Give three classes retail's shared default bodies for their pure interface slots": DelayedWeaponSetUpgradeUpdate
  (update -> 0x000910FB), DelayedExperienceLevelGrantSystem (init -> 0x000B3FD0), FireWeaponWhenDamagedBehavior
  (onHealing / onBodyDamageStateChange -> 0x0047A69C / 0x000D1407). 3 tables.
- "Give FiringTracker and two Rva0056AC26 children retail's folded slot bodies": FiringTracker's loadPostProcess
  (FiringTracker.cpp's existing body rowed; one present_unmatched hatch line retired) and getUpdatePhase (0x0044827C);
  Rva0056B188 / Rva0056B218 ac26Slot1 (`return m_20`, 0x00232E8F). 3 tables.
- "Give the Rva005CE8F5 observer base retail's empty slot 1 in all four views": Rva005CE8DC, Rva005CE8F5,
  Rva005CEE07. 3 tables.
- "Give three short tables retail's trailing empty slots in every emitter": Rva005C3F02, Rva005FA141,
  StrategicHUD::RegionDetailsStructuresMovieClip. 3 tables.
- "Record lk102's blocked LINK-514 verdicts": the three refusals below.
Each body is an inline or unit-local override with retail's argument list, rowed by add_match --icf-owner as the
twin of the address's named owner with `fold-proof=<owner's source>`; every emitter of each table changed together.

**Measure (base -> after, lk74_cmp).** Bridged 3,377 -> 3,361; bridged slots 50,619 -> 50,547; already correct
2,185 -> 2,201; mismatching source slots 37,955 -> 37,932; 16 bridged -> correct, nothing newly bridged, no correct
table lost, refusals identical (35). link_check (census c31795c94c) over every changed unit, every other definer or
referencer of each changed table and the owners' units: all LINK, LINKED never lower, except two verdicts that hold
at HEAD without these changes: ThrowingNewHelpers.cpp and OwnedPointerResets.cpp (`?reset@Rva005CE236`,
`?reset@Rva002D38AE`, `?reset@Rva002D390E`: the kept copy is not retail's; both units linked in the census, so this
came after it and is not attributed here), and OpaqueScalarDeletingDtorsB18.cpp, which links once the other two
emitters of `??_7Rva005FBBEE@@6B@` are rebuilt (stale census objects). No alias, pin or marker added; one
present_unmatched line removed; no initializer added.

**Refused / deferred (re_attempts.log).**
- false-reject rename.py function, `?slot43@BehaviorModule@@UAEXH@Z` (0x0047A69C): the parameter-only respell to
  `UAEXM@Z` that cause 6 needs is refused because the unchanged identifier slot43 is a placeholder
  (check_new_identifier). Not attempted: inventing a slot name.
- false-reject rename.py function, `?name@BezierProjectileBehavior@@QBEPBDXZ` (0x0045BFD3): no route respells a
  module name getter to `?GetSnapshotName@<Class>@@MBEPBDXZ` (--to-class refuses a member of the class and, for
  `?RvaNNNNNNNNGet@@YAHXZ`, a free function; --respell needs a vote). 31 tables.
- Rva005746AF (and Iface2C): a generated header's contract cannot carry a retail-proven slot signature or inline
  body once every unit has adopted it (header_adopt_lane declares slots only from private views). Rva005746AF 1
  table, Iface2C 4.

**Next leads.**
1. Cause 6 after the rename route exists: BehaviorModule.h `slot43(float)` with the base twin row, then per emitter
   `getSpecialPower() { return this; }` (0x002533D3), slot43 -> startPowerRecharge, slot44 -> primary slot 12
   (`?rva00493805@SpecialPowerModule@@UAEXXZ`) and the --to-class moves of 0x00251C11 / 0x00251C24.
2. One-slot stand-ins for DieModuleInterface: B5 / Iface28 (generated `b5()` / `f28()` headers plus private B5
   views; retail slot 0 is OpenContain::onDie in 0x00C46F78, 7 tables) and Rva0045D39E_E1 (generated today;
   SlowDeathBehavior::onDie in 0x00C42030, 5 tables) need the slot spelled `onDie(const DamageInfo *)` so the
   rowed overrides land there; the generated ones hit the contract gap above.
3. --to-class leads (placeholder-class bodies retail binds to derived slots): Rva005CEE9F / Rva005CEF2F slot 1
   (0x005CE9F7, 0x005CEA04 null forwarders); the Rva00567960BaseMid family, whose base table 0x00C7A630 wants the empty
   slot 1 and whose six derived tables hold class bodies there (0x005679A4, 0x005CC30B, 0x005E8CF8, 0x005F57D8,
   0x005F5B77, 0x005F5E69).
4. lk97/puretiny.py lists 83 pure-kept tables with tiny retail bodies at the end of this pass; most are Snapshot
   name getters (lead 2 of the refusals) or class-own bodies under placeholders.

**Tooling compatibility audit** (`c8b5c6685e4..HEAD`): 25 files modified, none added, moved or deleted;
`rename.py check --range`: 0 renames, 0 problems; tools/, .githooks/ and .github/ spell none of the changed files;
the only class mentions are fixture rows in tools/tests/fixtures/structural_queue.csv (DefaultProductionExitUpdate,
SupplyCenterProductionExitUpdate, SpawnPointProductionExitUpdate), file-level and unchanged.

Q3 factory family (2026-11-12): eight primary bridges remain open.
The [factory and destructor table pairs](../../reverse/attempt_support/q3-factory-vtables-20261112.md)
identify distinct destructor-installed tables for all eight and the competing
constructor identity for the five-slot case.

The AptLanLobby callback table at RVA 0083E020 remains bridged. A compiler
probe reproduces all 23 slot positions. The approved move of its slot 20
factory hits a [split refusal on two pairs of folded destructors](../../reverse/attempt_support/apt-lobby-slot20-split.md).

Wind category constructor 001F448D now constructs the two-interface base
and WindModuleInfo at +8. For RVAs 007BB58C, 007E16C8 and 007E16D8 both
ParticleSys.cpp and FXParticleSystem.cpp emit tables of 4, 16 and 16 bytes
with identical slot relocations. The middle table has three pure slots
after its deleting destructor. In the default wind implementation
(0081BFB8) slot 2 calls createModule, RVA 003AD97F. The constructor no
longer refers to the three address-named externals. Two-unit verification
matched 529 functions and 14 EH graphs; link preview kept 10,937 bytes.
Check the next real-link queue for bridge retirement and the selected
deleting destructors against retail before closing these three entries.

### Placeholder slot bodies moved into their tables' classes, collide defaults and the OwnedPointerResets regression: 17 off the bridge (2026-11-12, seat halilkkaya-lk104)

Base `d3809cf5c05`. Measured with lk74_snap/lk74_cmp and HEAD's `vtable_bridge.py`; census index `c31795c94c`.

**Regression first (LINK-662).** OwnedPointerResets.cpp's owning-pointer resets and clears call their 5-byte pointee
destructors out of line in retail. Five canonical-header adoptions (Rva00527FA2, Rva005D32D4 and Rva0052710C before the
census; Rva004E668E and Rva005E893E after it) replaced the unit's `__declspec(noinline)` views with plain `~X();`, so cl
inlined them and nine rows called the clear helper instead. The byte gate passed them because the two targets are one
`jmp` apart. ThrowingNewHelpers.cpp (1,388 B) stopped linking on `?reset@Rva005CE236`; OwnedPointerResets.cpp (1,927 B)
and AptPalantirCallbacks.cpp (1,639 B) were already at 0 in the census. "Keep OwnedPointerResets.cpp's six pointee
destructors out of line under their canonical headers" puts noinline on the unit's own definitions: 9 -> 0 REL32
targets differ from retail, and the 13 units that define, include or call these classes all LINK.

**Refreshed ranking at the end (3,344 bridged; a table counts when every wrong slot is covered).** UpdateModule interface
slots (0x004A2D67 / 0x00253376 + 0x0044DF8D) 24; only `ret 4` (0x0047A69C) 20; collide defaults 14 (12 are OpenContain's
interface table 0x00C46064 under the generated B4/Iface24 views, plus AODCrushCollide, which another seat holds, and
Rva005746AF); Rva005E12D1/Rva005E129B button bases 10; only 0x000B3FD0 8; pure-kept with tiny retail bodies 83
(lk97/puretiny.py, mostly FX slices and Snapshot name getters).

**Done (commits by subject).**
- "Keep OwnedPointerResets.cpp's six pointee destructors out of line under their canonical headers": LINK-662, above.
- "Move ?rva005CE9F7@Rva005CE9F7NullForwarder@@QAEXXZ into Rva005CEE9F as ?slot1@Rva005CEE9F@@UAEXXZ (retail vftable
  0x00C7522C slot 1)" and the matching 0x005CEA04 move into Rva005CEF2F (0x00C7523C slot 1): lk102's lead 3. 2 tables.
- The Rva00567960BaseMid family: "Move ?rva005F57D8@Rva005F57D8@@QAEXXZ into Rva005F5819 ...", "... ?rva005F5B77 ...
  into Rva005F5BF2 ...", "... ?rva005F5E69 ... into Rva005F5EA6 ...", "... ?rva005CC30B ... into Rva005CC37C ..." and
  "Move ?rva005E8DB5@Rva005E8DB5@@QAEPAXXZ into Rva005E8D71 ... (retail vftable 0x00C77F88 slot 2)". Each derived
  view declares the slot after its destructor (the generated BaseMid header declares only the destructor), every
  emitter changes together (both names bound at each address), and the body is defined under the class with the
  vptr in place of 4 pad bytes. 10 tables.
- "Give FireWeaponCollide's and DozerAIUpdate's collide interface views CollideModule's five defaults": lk97's collide
  lead 3 with the CollideModule.h spellings; the bodies were already rowed as twins, so no row is added. 4 tables:
  FireWeaponCollide, CollideModule, CollideModuleInterface, DozerAIUpdate's AIUpdateInterface24.
- "Give PlanningPhaseBuildingSelection's primary table retail's ninth slot, the shared false default": slot8 rowed as
  the 0x005CB9FF twin. 1 table.
- "Record lk104's blocked LINK-514 verdicts": the four deferrals below.

**Measure (base -> after, lk74_cmp).** Bridged 3,361 -> 3,344; bridged slots 50,547 -> 50,488; already correct
2,201 -> 2,218; mismatching source slots 37,932 -> 37,895; 17 bridged -> correct, nothing newly bridged, no correct
table lost, refusals identical (35). link_check (census c31795c94c) over the 50 units that changed, emit a changed
table, define or call a moved body, or include a LINK-662 class: 50 of 50 LINK, LINKED 42,400 -> 46,110 B, and no unit
is lower. No alias, pin, marker or hatch was added or removed. No initializer was added. The EH `$L`/`$T` labels of
eight units shifted, and the gates verified every funclet row through the parent EH data.

**Refused / deferred (re_attempts.log).**
- 0x005679A4 `StanceButton::DoUpdate`: slot 1 of Rva00567960's BaseMid table, but the row already carries the real
  class while both emitters spell Rva00567960; `--to-class` takes placeholder rows only. Prerequisite: fold
  Rva00567960 into StanceButton. 2 tables.
- 0x00518892 and the three sibling thunks: retail's BfmeAptFunctorMarker slot 0 is each class's this-adjusting
  deleting-destructor thunk, but the generated header declares `marker() = 0`. This is the contract gap lk102 named.
  4 tables.
- 0x005E1193 `OnRollOver`: the Rva005E12D1 button-base family needs six base slots (1..4 = 0x005E0D94, 5 =
  OnRollOver, 6 = 0x005E0D9C) and a per-class click override at slot 1. Slot 5 is rowed under
  StrategicHUD::CommandButtonMovieClipWithHelp while about 20 views spell Rva005E12D1, so the class identity comes
  first. 10 tables.
- 0x005CE7BF: the Rva005E67FE family (base 0x00C77E28, Rva005CE804/874 0x00C75184) needs eight default slots in the
  base, but PlanningPhaseBuildingSelection's slot 7 override is rowed `int(int)` over the base's `bool(int)` default.
  It needs a return respell, for which the rename tool has no route (as with lk102's slot43). 3 tables.

**Next leads.**
1. The UpdateModule interface family (24): Rva0026E836Derived.cpp alone holds six `_B2` tables (AIUpdate family);
   slot 1 is `?getDisabledTypesToProcess@AIUpdateInterface@@` (0x004A2D67, rowed). Slot 2
   `?rva0044DF8D@UpdateModule@@` needs a view that derives from the canonical UpdateModule instead of the
   Rva0026E836_B2 stand-in.
2. Tooling: header_adopt_lane could refuse an adoption that changes a matched row's REL32 target (LINK-662), and the
   byte gate could report a REL32 target one `jmp` away from retail's.
3. The four deferrals above, in table order: the E12D1 class identity (10), BfmeAptFunctorMarker's contract (4),
   the Rva005E67FE return respell (3) and the StanceButton fold (2).

**Tooling compatibility audit** (`d3809cf5c05..HEAD`): 24 files modified and 1 added (the LINK-662 entry), none moved
or deleted; `rename.py check --range`: 0 renames, 0 problems; tools/, .githooks/ and .github/ spell none of the moved
symbols or changed files except FireWeaponCollide fixture rows in tools/tests/fixtures (structural_queue.csv,
dead_ends.csv), which are synthetic, file-level and unchanged.

### Sentence-vector identity follow-up (2026-11-12)

At bfadd71c4cc, retire render2dsentence.cpp's false SentenceDataStruct vector
lifetime and 0x001A3B90 alias while preserving its native record assignment.
All 105 remaining rows across agg_def, collect and render2dsentence verify;
all three own link previews read LINKS against 9ca25659d0. Retail's complete
71-byte body remains under the two pointer-vector owners. The served
0x007D6C24 table still needs published real-link confirmation; no image or
bridge-retirement claim is made. The separate 0x007D3BC8 renderer and
0x008E0BC4 PrototypeClass/BfmeMsg entries remain open in LINK-619.
[Evidence](../../reverse/attempt_support/vector-table-identity-20261110.md).

### Rva0050EA74 empty-base slot (2026-11-12)

At b5bb464feb, Rva0050EA74Ctor.cpp's dummy keep() is replaced by the
virtual empty base destructor native table 0x007C6F20 requires. The emitted
29-byte deleting destructor is an independently verified ICF twin of the
existing Rva0007DF07 owner; all four original rows are unchanged. Five-row
normal verification and a strict reusable compiler receipt pass; own link
preview reads LINKS against 9ca25659d0. A bounded replay makes this base
name already correct. Derived 0x0086551C still needs its two setters and
three default slots; published confirmation for both tables is pending.
The follow-up moves the unique show/hide setters into this class through
rename.py while preserving their source paths, shares the declaration and
recovers the two native zero-return defaults. Edited sources pass 43/43
rows with strict receipts, the rename closure passes 4,573 bodies across
155 sources, and both own link previews pass. Bounded table replay:
2 generated -> 1, zero refusals; derived mismatches 6 -> 1. Remaining:
slot 5's empty body at 0x000B3FD0 is claimed by anchorist-codex-local-bfme2;
no override/alias for that held body is added. Complete it when available
before adopting the full header in the other page views or closing the file.
[Evidence and remaining file work](../../reverse/attempt_support/rva0050ea74-tables-20261112.md).

### 2026-11-12 — wind-info table 0x0081B568

The default and copy constructors at 0x003A5773 and 0x003AE07D install
this table. The shared Rva003AE07D declaration now emits all 16 bytes.
In a four-object replay, vtable_bridge matches all four source slots:
the weak deleting destructor resolves to the scalar body at 0x004A10FD,
LoadPostProcess returns at 0x000B3FD0, the getter at 0x003A5784 returns
"ParticleWindModuleInfo", and DoXfer at 0x003A578A transfers the float at +4.
The deleting body calls the seven-byte Snapshot reset at 0x0049B47C and
operator delete. Scoped link preview preserved all 504 bytes in three units.

The other provider Rva003A59C3B3 still has four mismatches. Sharing an
inline default constructor preserved the parent constructor's 127 bytes
and exact EH graph in a probe, but moved the standalone 17-byte body out
of its ledger object. Keep that provider open pending a verified arrangement
that preserves row ownership. Whole-image selection and bridge count await
the real link.

### Three opaque special-power destructor views use concrete Behavior defaults (2026-11-12)

At 93f9903fe4e, Rva00493DEFDerived.cpp replaces its twelve-byte padded base
plus MiBase1 with canonical BehaviorModule inheritance. All six destructor
rows and both affected constructor rows remain exact. StopSpecialPowerCtor
and SupplyTruckAIUpdateCtor (HordeDispatch) bind the new emitted primary and
tertiary table names at their same native addresses; all three own link
previews read LINKS, 247 -> 247 bytes against 9ca25659d0. The three rebuilt
188-byte Behavior tables have 44/47 native slot bodies correct; slots
8/43/44 and the other primary/special-interface recoveries remain. All nine
table repairs stay open; this is not a bridge-retirement or image result.
MiBase1's obsolete header-queue entry is retained: accept still requires its
old include, so the rejected retirement is recorded for tooling rather than
adding an unused include. The initial abstract-interface trial (all pure
calls, not retail's zero returns) was restored.
[Target evidence, consumer proof and prerequisites](../../reverse/attempt_support/rva00493def-behavior-20261112.md).

**2026-11-12, strstreambuf slot1: repair prepared, awaiting real-link confirmation.**
The table87A878's sole mismatch is the declared but undefined setbuf override.
The ordinary STLport4.6 definition returns this and exactly matches its
native five-byte slot13570. It is admitted as an ICF twin beside the
105-byte constructor; the destructor TU's obsolete alternate to the wide
base default is removed, retiring one hatch. All six rows and strict
preparation pass; both own link previews read LINKS. The eight-object
local planner changes one generated table to zero, with no refusals and
one already-correct table. The published bridge queue stays unchanged until
the next real link confirms it; no census or game-run clearance is claimed.
[Native/library proof and measured scope](../../reverse/attempt_support/strstream-setbuf-20261112.md).

**2026-11-12, Rva000F1B8F shared base and key: awaiting real-link confirmation.**
Both constructor and destructor TUs adopt canonical HashableClass and supply
the native table7CEFD4's Get_Key override at30F45F. Two private base views
and their single superseded29-byte deleting-destructor alias retire; the
real canonical owner and both exact copies retain that address's coverage.
All five rows and strict preparation pass, and both own previews read LINKS.
The three-object local planner changes the two-slot table from bridged to
already correct without a refusal. The published queue remains intact;
census/image confirmation and the separate hrawanim destructor-copy issue
remain open.
[Native hash-entry use and full retirement scope](../../reverse/attempt_support/hashable-entry-20261112.md).

The ProfileCmdInterface table at 0x008E7CB0 still lacks its deleting
destructor slot. The constructor and destructor fold dry runs refuse for
different table-ownership reasons. See the [profile command table
handoff](../../reverse/attempt_support/profile-command-table-008e7cb0.md).

At 0x0087598C five of eleven retail entries already target named HUD methods.
The recorded virtual destructors have no slot in that table. See the
[installer and method ownership checks](../../reverse/attempt_support/selection-ui-table-0087598c.md).

At 0x0085FC28, EvacuateGarrisonSpecialPower's slot zero calls 0x004CDC98.
Its call to 0x004CDC33 restores this table and the three secondary tables
before jumping to the base destructor. Both rows were previously claimed
as SupplyCenterDockUpdate. The corrected bodies match 28 and 32 bytes in
ModuleUpdateDtors.cpp. The constructor's local empty destructor is removed.
The two-unit preview preserves 909 linked bytes. The complete primary table
still needs 23 slots. Seventeen target the same bodies as the base, and
slots 0, 1, 2, 3, 4 and 19 differ. In particular, slot 2 at 0x004CDC2D
is still rowed as a free integer-returning function. Full-image retirement
requires a new published queue measurement.

2026-11-13 CastleMember native interface audit (root20, base3a7e946d6af):
its12/47/3-slot tables identify the DamageModuleInterface contract. Native
getDamage is the+0C slot4 conversion; getUpdate remains null. Recovery needs
the canonical Dict callback at BehaviorModuleInterface slot45, the getter and
two callback signature/owner corrections, and supported admission for the
empty healing callback. Neither an out-of-line base lifecycle call nor a
cross-TU duplicate row is a valid substitute. Sources unchanged;115/115 rows
and1data pass over the claimed producer and pulled Object area. [Native table
inventory and exact prerequisites](../../reverse/attempt_support/castlemember-native-interfaces-20261113-root20.md).

**Rva002215F4 callback-table review (2026-11-13, root20, dbe2a87683):**
native81C780=[purecall],7E6BA4=[5D124D], next7E6BA8 separately owned.
Ordinary12/12 rows349B pass; no edit. The previous nonvirtual-destructor
prerequisite cannot use current rename: generic special-member/signature
routes refuse U-to-Q and --virtual is one-way. Preserve deleting-helper2215FF
emission and resolve the callback's unrelated folded owners before recovery.
[Current evidence](../../reverse/attempt_support/callback-vtable-kind-20261113-root20.md).

**AttackPositionHordeStateMachine review (2026-11-13, root20, 5f3deb924b5):**
Native811CF0 has16slots; current slots2/3 inherit the wrong base providers.
An unlanded candidate passes41/41rows and both64-byte tables match all16
native slots with provisional33FC04 getter/33FB0B transfer bindings. Getter
--to-class refuses the already-named owner; transfer ICF admission is refused
by tu_ownership A1. No production change or bridge retirement.
[Candidate and exact prerequisites](../../reverse\attempt_support\attack-position-native-vtable-20261113-root20.md).

### Module name getters moved to their Snapshot override; slot43's respell needs a header route (2026-11-13, seat halilkkaya-lk106)

Base `5f3deb924b5`; measure lk74_snap/lk74_cmp with HEAD's `vtable_bridge.py` (local objects, no link).
Base: 3,324 bridged, 31 refused, 2,225 already correct.

**Tooling (both false rejects lk97/lk102 recorded).**
- `4d67bacc1ab` rename.py: a signature-only `--respell` keeps a placeholder identifier (no placeholder check on
  the unchanged identifier) and may retype a placeholder's top-level 4-byte scalar parameter (int, unsigned,
  long, unsigned long, float). Cause 6 (`?slot43@BehaviorModule@@UAEXH@Z` -> `UAEXM@Z`) is still blocked:
  slot43 is declared only in the canonical `Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h` (hand
  written, not generated) and in three shim copies (`reference/shims/bfme2_bonefxupdate`,
  `bfme2_flammableupdate`, `zh_outofline`), while `--prepared` takes Code `.cpp` sources only. Prerequisite: a
  respell route that prepares a registered canonical header (and its shim copies) and verifies its includers.
- `742789a3c34` rename.py `--to-class`: the one same-class move, `?name@C@@QBEPBDXZ` to
  `?GetSnapshotName@C@@MBEPBDXZ`, proved by slot 2 of C's own retail table, an installer view deriving C from
  Snapshot and the rebuilt table naming the override in slot 2. 25 bridged tables were wrong only at slot 2 (or
  slots 1-2) with a `?name@<RealClass>@@QBEPBDXZ` getter at the base.

**Done (commits by subject).**
- "Move ?name@BezierProjectileBehavior@@QBEPBDXZ into BezierProjectileBehavior as
  ?GetSnapshotName@BezierProjectileBehavior@@MBEPBDXZ": 0x00C41E04 off the bridge (3,324 -> 3,323; refusals
  identical; 2,225 -> 2,226 correct). link_check: ModuleNameGetters.cpp 288 B and BezierProjectileBehavior.cpp
  5,754 B LINK before and after.
- "Move ?name@PickupStuffUpdate@@QBEPBDXZ into PickupStuffUpdate as ?GetSnapshotName@PickupStuffUpdate@@MBEPBDXZ":
  slot 2 of 0x00C4DDA8 right (mismatching source slots 37,536 -> 37,535), still bridged at slot 1 alone (the
  0x00497805 loadPostProcess fold); bridged, refused and correct unchanged. ModuleNameGetters3.cpp 605 B and
  PickupStuffUpdate.cpp 831 B LINK before and after.
- "Give PickupStuffUpdate its loadPostProcess base call (retail 0x00497805 fold)": the lk97 recipe (inline-free
  override calling UpdateModule::loadPostProcess, rowed by add_match --icf-owner as the twin of
  ?loadPostProcess@Rva00497805@@MAEXXZ, fold-proof=BattlePlanUpdate.cpp). 0x00C4DDA8 off the bridge (3,323 ->
  3,322; refusals identical; 2,226 -> 2,227 correct). link_check PickupStuffUpdate.cpp 831 -> 836 B,
  ModuleNameGetters3.cpp 605 B, BattlePlanUpdate.cpp 2,621 B, all LINK (checked together: the census index
  predates the getter move, so alone the unit reads ModuleNameGetters3's old object).
- "Move ?name@ArmorUpgrade@@QBEPBDXZ into ArmorUpgrade as ?GetSnapshotName@ArmorUpgrade@@MBEPBDXZ": 0x00C570A0 off the bridge (3,322 -> 3,321; refusals identical; 2,227 -> 2,228 correct). link_check: ModuleNameGetters3.cpp 605 B and ArmorUpgrade.cpp 575 B LINK before and after.
- "Move ?name@AIGuardMachine@@QBEPBDXZ into AIGuardMachine as ?GetSnapshotName@AIGuardMachine@@MBEPBDXZ": 0x00C69680 off the bridge (3,321 -> 3,320; refusals identical; 2,228 -> 2,229 correct). Rva004D759CDerived.cpp (the destructor unit) and AIGuardMachineCtor.cpp both declare the override. link_check: ModuleNameGetters3.cpp 605 B, Rva004D759CDerived.cpp 588 B, AIGuardMachineCtor.cpp 451 B and AIGuard.cpp 2,050 B (a tu-skeleton comment respelled) LINK before and after.
- "Move ?name@AITNGuardMachine@@QBEPBDXZ into AITNGuardMachine as ?GetSnapshotName@AITNGuardMachine@@MBEPBDXZ": 0x00C6A090 off the bridge (3,320 -> 3,319; refusals identical; 2,229 -> 2,230 correct). Rva004D759CDerived.cpp and AITNGuardMachineCtor.cpp both declare the override. link_check: ModuleNameGetters3.cpp 605 -> 605 B, Rva004D759CDerived.cpp 588 -> 588 B, AITNGuard.cpp 1,033 -> 1,033 B, AITNGuardMachineCtor.cpp 417 -> 417 B LINK.
- "Move ?name@TurretAI@@QBEPBDXZ into TurretAI as ?GetSnapshotName@TurretAI@@MBEPBDXZ": 0x00C60D78 off the bridge (3,319 -> 3,318; refusals identical; 2,230 -> 2,231 correct). link_check: ModuleNameGetters.cpp 288 -> 288 B, TurretAI.cpp 2,665 -> 2,665 B, TurretAICtor.cpp 256 -> 256 B, TurretAIDeleter.cpp 28 -> 28 B, TurretAIDtor.cpp 96 -> 96 B LINK.

**Recipe and limits.** Prepare the getter unit (`BFME_LITERAL_NAME_GETTER(C, ...)` ->
`BFME_SNAPSHOT_NAME_GETTER(C, ...)`) and every installer unit whose view compiles C's table (a protected
`virtual const char *GetSnapshotName() const;` in C's body), then `rename.py function --rva R --to-class C --new
'?GetSnapshotName@C@@MBEPBDXZ' --prepared ...`. One move per commit: a second move with the first unstaged is
refused by name_dependents. A refused apply restores the files but leaves its verify objects in `build/match`:
rebuild those units before measuring.

**AI upgrade table boundary (2026-11-13, root20, e00363180fb):**
Native876510 has exactly2slots (5DA67F/5DA7D9). Constructor5DA831
independently installs876518, whose5DA854 entry is not a third slot.
Removed the stale slot2 from both placeholder destructor emitters: their
tables12->8B, only the third relocation removed; all other COMDATs unchanged.
Whole class/base cohort52/52rows; scoped3/3LINKS852->852B against oldindex.
Class fold and real slot0 override remain, no bridge retirement claimed.
[Boundary proof](../../reverse/attempt_support/ai-upgrade-table-boundary-20261113-root20.md).

**AI upgrade lifetime identity (2026-11-13, root20, after96001c50552):**
Owning ordinary fold unites5DA7F5/5DA7D9 and its EH row with the
constructor-owned AIUpgradeHeuristicFactoryUnlock. Explicit out-of-line
dtor declaration removes the ctor TU implicit non-retail competitor;
whole52/52rows and scoped3/3LINKS852->852B pass. Callback5DA67F still
needs a matching inherited signature before virtual respelling; bridge
remains. [Identity and provider proof](../../reverse/attempt_support/ai-upgrade-lifetime-identity-20261113-root20.md).

**AI upgrade abstract callback ABI (2026-11-13, root20):**
Dispatcher59710E and concrete5DA67F prove an integer result and one4B
carrier. Updated BaseRva005DAA36 contract and regenerated pure slot0
under the existing address-neutral rva005DA67F identifier. int/Player*
source semantics remain unresolved. All52rows,140COMDATs and38table
payloads/relocs remain exact before/after; sibling slot debt unchanged.
[ABI evidence](../../reverse/attempt_support/ai-upgrade-base-abi-20261113-root20.md).

**AI upgrade native dispatch (2026-11-13, root20):**
Owning --virtual transaction binds existing5DA67F callback to slot0 in
all3eight-byte AIUpgradeHeuristicFactoryUnlock tables; slot1 weakdefaults
resolve to the native28B deleting wrapper and sole60B dtor. Other137COMDATs,
base/sibling tables and weak sets unchanged;52/52rows and3/3LINKS852->852B.
Baseadoption is separately blocked by the conditional-include proof; both
private data views remain. Await authoritative bridge retirement, no queue
hand-edit. [Complete dispatch proof](../../reverse/attempt_support/ai-upgrade-native-dispatch-20261113-root20.md).
