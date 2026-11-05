### LINK-514: kept `??_7` copies differ from retail's vftables (runtime vtable survey)
Status: Open (partly repaired). Updated: 2026-11-05; inspected revision: e5e17e246f (census index c95fcfcfcd).
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
