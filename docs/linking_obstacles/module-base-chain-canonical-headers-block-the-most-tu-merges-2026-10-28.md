### Module base chain: canonical headers block the most TU merges (2026-10-28)

2026-11-05: Thirteen ModuleData consumers now adopt the canonical header with explicit opaque-record views; 125/125 rows exact, thirteen header rows retired, and 23,819 preview-linked bytes preserved. [Scoped evidence; wider module-chain work remains open](../../reverse/attempt_support/moduledata-header-cohort-20261105-codex2.md).

2026-11-05: Six Player consumers now adopt canonical TeamPrototype while retaining their iterator bodies; 21/21 rows exact, six header rows retired, 2,948 preview-linked bytes preserved and no external definitions lost. [Evidence; wider Team consolidation prerequisites remain](../../reverse/attempt_support/teamprototype-player-headers-20261105-codex2.md).

2026-11-05: Nine TeamPrototype consumers now adopt Common/Team.h while retaining TU-local iterator implementations; nine header rows retire, 24/24 rows byte-match, and 3,939 preview-linked bytes remain. [Scoped evidence; wider Team.cpp prerequisites remain](../../reverse/attempt_support/teamprototype-header-adoption-20261105-codexb.md).

2026-11-05: Three AIUpdateInterface temporary-state units now use the canonical AIUpdateInterface/AIStateMachine fields; 3/3 rows byte-match, three header rows retire, and all 73 preview-linked bytes remain. [Scoped evidence; wider module-chain work remains open](../../reverse/attempt_support/aiupdate-temporary-state-headers-20261105-codex3.md).

2026-11-05: InstantDeathBehavior parser-vector views now reconcile; the two-parser merge passes bytes/EH but is restored after an ownership refusal on an existing OCL ICF fold. [LINK-422 and next check](link-422-instantdeath-parser-merge-icf-owner-transfer.md).

2026-11-05: Three client consumers now adopt AIUpdateInterface; seven existing AI adoptions reverified, ten header rows retired, and 12,939 client preview-linked bytes preserved; two voice cleanup-wrapper identity findings remain for follow-up. [Receipts and remaining cohort prerequisites](../../reverse/attempt_support/aiupdate-client-header-adoption-20261105-codex3.md).

2026-11-04: AIUpdateInterface adopted in two AI consumers; eight existing adoptions reverified, ten header rows retired, 5,269 preview-linked bytes preserved. [Cohort receipts and remaining prerequisites](../../reverse/attempt_support/aiupdate-header-cohort-20261104-codexb4.md).

2026-11-04: RebuildHoleExposeDie now adopts canonical ModuleData/DestroyDieModuleData and eight further module-data headers; ten header-queue rows retire with 11/11 functions and its data row exact, and a passing link preview. Factory/Dock base conflicts and LINK-167 remain open. [Scoped evidence](../../reverse/attempt_support/rebuild-hole-moduledata-headers-20261104.md).

2026-11-04: Team.cpp now adopts canonical NameKeyGenerator (156/156 exact; 7,862 preview-linked bytes preserved; one header-queue row retired); its remaining merge prerequisites and the claim-blocked five-donor trial are recorded in [scoped evidence](../../reverse/attempt_support/team-namekey-header-20261104-codexb4.md).

2026-11-04: InstantDeathBehavior's constructor/onDie/pool-key leaf declarations now agree (8/8 rows exact; 521 preview-linked bytes unchanged); its merge still needs the seed's legacy headers and module-data views reconciled. [Scoped evidence and audit boundary](../../reverse/attempt_support/instantdeath-leaf-views-20261104-codex4.md).

`header_adopt_lane.py order --merges` ("Rank the class-header tier by TU-merge donors unblocked") ranks classes by queued
merge donors whose private views they split. The module chain leads after
Object/Thing: Module, ObjectModule, BehaviorModule(Interface),
UpdateModule(Interface) score 296 donors (UpdateModule's own views: 296
donors, 1,065 rows, 89 TUs); UpgradeModule 50 donors in 22 TUs. In many upgrade
TUs the leaf class also conflicts only because its base clause differs, so it
waits on the same header. Static verdicts agree with `tu_views --dry-run` on 25
of 29 classes sampled across 6 TUs.

Current BuildableHeroListUpgrade check (2026-10-29, 29c5ceda1f): the normal
merge dry run accepts the three implementation rows but rejects the 49-byte
constructor on its conflicting UpgradeModule base view (C2504). tu_views
places the constructor's explicit +0 vtable field under the other view's
bases. No applying merge occurs; moving only one donor to the absent
destination would remove no net file. Reconcile that constructor/base view
through the module-chain prerequisites before retrying.
[Scoped composition evidence](../../reverse/attempt_support/buildable-hero-upgrade-composition-20261029-round3.md).

None can be settled through the lane yet:
- `class_contract.py --class Module` (82 views) queues vtable slots 1-4 and
  11-14 (placeholder names `s01`/`v1`/`f01` against `onObjectCreated`,
  `getModuleNameKey`, `preloadAssets`). BehaviorModule and UpdateModule inherit
  those slots. Settle them from retail vftables and ZH `Module.h` first.
- `--class UpgradeModule` (71 views) settles with no queue, but it flattens
  base fields (`m_moduleData` +4, `m_object` +8, extra vfptrs) into the class
  and names four bases without headers (BehaviorModule, BehaviorModuleInterface,
  UpgradeMux, ModuleInterface). An unapplied
  `run --generate --sample 12` passes 0/12 in all three variants (C2143 7, C3861
  4, C2039 1). The bases need headers first, and the contract has to stop
  re-declaring inherited fields.
- MemoryPoolObject (zh-decided, sizeof 4) and Team (no queue, sizeof 52, only
  the vfptr decided) settle. In Team.cpp, though, Team, TeamPrototype,
  TeamFactory and TeamTemplateInfo also block, so no donor is unblocked by one
  header alone.

Update 2026-10-28 (module-contract pass):

- **Module's retail vtable (target facts).** No Module table exists in the
  image: its constructor is inlined and the store eliminated. The derived
  tables fix it. ObjectModule (VA 0x00C07E1C, installed by
  `??0ObjectModule` 0x00306AA7) has exactly 10 slots, then its name literal;
  DrawableModule (0x00C07E54) 11; BehaviorModule (0x00BEEA7C) 12. Shared
  slots 0-8: 0 deleting dtor; 1 empty `ret` (UpdateModule overrides it with
  `loadPostProcess` 0x0058B03E); 2 a per-class name-literal getter
  (`mov eax, imm; ret`); 3 xfer (`?xfer@ObjectModule` 0x00560AE1); 4
  `__purecall`; 5-8 the empty `ret` 0x000B3FD0. Slot 9 differs per class
  (ObjectModule `ret 8`, DrawableModule `xor eax,eax; ret`), so Module has 9
  slots. Slots 1-3 are Snapshot's (`reference/shims/moduledata/Common/Snapshot.h`:
  loadPostProcess, GetSnapshotName, xfer). `??_GObjectModule` 0x004A10FD calls
  0x0049B47C, which restores Snapshot's table 0x00BBB554 at `[this]`: the only
  non-empty base destructor is Snapshot's, at offset 0. The ObjectModule and
  DrawableModule constructors store the ModuleData argument at +4.
- **Overriders (ledger names, target).** Over the 323 Module-family tables
  (slot 4 pure or `getModuleNameKey`), slot 5 is `onObjectCreated` (18
  matched overriders), slot 6 `onDrawableBoundToObject` (7), slot 8
  `onDelete` (32). Slot 4 is `getModuleNameKey`: InvisibilityUpdate's own
  slot-4 row, and `Object::findModule` (0x0028B6D6, byte-matched) calls
  `[vtable+0x10]`. Slot 7 has one distinct overrider, 0x000B7C18
  (W3DScriptedModelDraw, 7 tables). It takes no stack argument.
- **Donor facts.** In ZH, Module derives from MemoryPoolObject and Snapshot,
  with getModuleNameKey, onObjectCreated, onDrawableBoundToObject,
  `preloadAssets(TimeOfDay)` and onDelete. BFME 1's Module.h drops the
  Snapshot base and keeps crc/xfer/loadPostProcess.
- **Decision (inference from the above).** BFME2 `Module : Snapshot` at
  offset 0: slots 1-3 inherited, 4 `getModuleNameKey() const = 0`, 5
  `onObjectCreated()`, 6 `onDrawableBoundToObject()`, 7 a zero-argument
  virtual in ZH's `preloadAssets` position (ZH's TimeOfDay argument is gone:
  every implementation is a plain `ret`; the name is a hint, not proof), 8
  `onDelete()`. `m_moduleData` is at +4 and sizeof is 8. ObjectModule adds
  `onCapture` (slot 9, two stack arguments) and `m_object` +8.
  The contract cannot reach this decision yet. Of 81 views, 14 are empty, 26
  are vfptr-only, 13 have sizeof 8 and 6 have sizeof 140 (other classes named
  Module), so the majority sizeof is 4 and +4 is a 21-view outlier. None
  spells the Snapshot base. Eight views vote on slots: UnitRevivalTracker
  (v0-v14), InvisibilityManagerRva00438E5B (f00-f22, turnOff 23),
  DrawableConstructor and DrawableDestructor (s00-s09, rva28; they merge
  DrawableModule into Module), ObjectFindModule and
  ObjectFindDynamicPortalBehaviour (`_r1`-`_r3`, getModuleNameKey 4: right
  shape), GateOpenAndCloseBehaviorOnObjectCreated (onObjectCreated at 1) and
  GameLogic.cpp (ZH order). Slots 9-23 come from views that call a derived
  class's slot through `Module *` (`findModule(...)->v14()`). Those calls need
  a derived view with a cast, not more Module slots. `class_contract` has no
  retail rule for a class without its own constructor rows (`retail_vtable`
  reads only tables those constructors store, slotted from the stale
  `reverse/vtables.tsv`, 161 tables, none in this family).
- **class_contract fixed (8d9328de31).** A derived contract now names its
  bases and votes only on members outside their extent (from the views that
  spell the bases); views that copied the base in no longer tie inherited
  slots. header_adopt_lane includes registered base headers and refuses a
  base with no header. UpgradeModule now decides no own fields (sizeof 28
  from the four bases) and stops on the four unheadered bases.
- **`run --generate` cannot adopt a polymorphic class.** `generate()` emits
  fields (skipping VPTR) and, in the methods variant, view methods that name no
  unknown type. It emits no vslots, so a generated Module header would have no
  vfptr. The module chain needs hand-written canonical headers from the retail
  facts, like Snapshot.h, adopted through the fixed-header path
  (`run --class X --header PATH` without `--generate`).
- **Merge candidates fail on other blockers.** Recomputed: 137 single-blocker
  TUs. UpgradeModule-only: CommandSetUpgrade, RadarUpgrade. UpdateModule-only:
  StealthDetectorUpdate. UpgradeMux-only: UpgradeModule.cpp. ArmorUpgrade is
  blocked by BehaviorModule and UpgradeModule. `tu_skeleton --merge --dry-run`
  accepts no donor in any of them:
  CommandSetUpgrade (Rva004B3AFFNotify: C2143 `TheControlBar`), RadarUpgrade
  (Object nested in `Rva004B46F9`), StealthDetectorUpdate
  (`UPDATE_SLEEP_FOREVER` C2365, then the leaf class), UpgradeModule.cpp
  (UpgradeMuxCtor C2600, an undeclared special member) and ArmorUpgrade
  (C2039 `upgradeImplementation`, a leaf view). The textual ranking
  overstates the chain. Every candidate also has a mixed donor
  (FireWeaponWhenDeadBehaviorDerived, ModuleDataBuildFieldParse,
  ConstIntGetters5, ModuleNameGetters3) that must be split first.
- **Next prerequisites, in order.** (1) A hand-written canonical
  `Module.h` (Snapshot base, the 9 slots above, m_moduleData), then
  ObjectModule and DrawableModule, adopted unit by unit. Retarget the eight
  slot-voting views first, moving derived-slot calls onto derived views.
  (2) BehaviorModuleInterface, UpgradeMux and ModuleInterface from their
  retail tables (UpgradeModule installs 0x00C42720 (18 slots) and 0x00C42768).
  (3) The per-TU leaf and Object views named above.

Update 2026-10-28 (generator pass):

- class_contract review fixes landed (f1aea79ad0): disagreeing base extents
  or slot counts and leaves the bases do not declare are queued before any
  member is dropped, and the retail vftable bound judges the inherited slots.
- The generator now declares decided vslots (ad330fd48a); an undecided slot,
  a tie or a gap refuses. Six Module views were retargeted to the retail
  slots (a6d5334f7d). Generation still refuses Module: the view majority
  sizeof is 4 and GameLogic.cpp (claimed by another seat) spells ZH order,
  so slot 9 repeats loadPostProcess. A hand-written
  `Code/GameEngine/Include/Common/Module.h` (Snapshot base, slots 4-8,
  m_moduleData +4) is adopted in 39/81 units (b5a7b8290a); 42 queued.
- GateOpenAndCloseBehaviorOnObjectCreated's body (0x0049936A) sits in slot 1
  of 0x00C50144 (loadPostProcess's slot) and calls
  `BehaviorModule::loadPostProcess()` first: its ledger name
  `onObjectCreated` is probably wrong (vtable-slot hint only; for the naming
  lane). Its view was left alone.
- ObjectModule and DrawableModule still refuse: their views do not spell
  the Module base, so slots 1-8 (ObjectModule also 9-12) are undecided, and
  DrawableModule's views put ZH's onCapture/onDisabledEdge at slots 9-10,
  where retail DrawableModule returns 0. Their views need the same
  retargeting first.
- Reach (40-view seeded samples, top 36 establish-header classes of
  `order --merges`): 12 now generate (ObjectShroudClient, ScriptEngine,
  BehaviorModuleBase, BehaviorModuleOther, UpdateModuleInterface,
  CollideModuleInterface, MemoryPoolObject, Team, Overridable,
  SpecialPowerUpdateInterface, Rva0044EF5E, B0); 24 refuse on queued
  sizes/fields or undecided, tied or gapped slots (Object: size; Thing,
  Drawable: slot 0; AIUpdateInterface: 141 queued slots).

Update 2026-10-29 (adoption pass):

- ObjectModule.h (Module base, slot 9 onCapture, m_object +8; hand-written
  from vftable 0x00C07E1C) adopted in 121 units (1c1d489768);
  MemoryPoolObject generated and adopted in 29 (a59a357115). With both,
  `tu_skeleton --merge FireWeaponCollide.cpp` accepted CollideModuleCtor.cpp
  (3d222b2da9, one source file removed).
- DrawableModule not adopted: retail slots 9 and 10 (vftable 0x00C07E54,
  both `xor eax,eax; ret`) have no evidenced names, and its views spell
  ZH's onCapture/onDisabledEdge there.
- **Lane hazard: `run --apply` does not run the link guard.** A generated
  CollideModuleInterface header (variant data+includes, 5/8 units
  byte-match) declares `wouldLikeToCollideWith` out of line, from the one
  view that spells it. FireWeaponCollide.cpp's old view declared an inline
  slot instead, so with the header its vtable needs an undefined
  `?wouldLikeToCollideWith@CollideModuleInterface@@UAE_NPBVObject@@@Z` and
  the census-linked unit would stop linking (`tu_skeleton --dry-run`
  link_guard). The commit was dropped before push. Until apply checks
  link coverage (as `accept` does), check
  `tu_skeleton --merge --dry-run` or `link_check` on adopted units before
  pushing a generated polymorphic header.

Update 2026-10-29 (Thing, Object, ObjectShroudClient decisions):

- **Thing decided and adopted in 6 units (0c7187617e).** Retail vftable
  0x00C086E0 (??0Thing 0x0030A188, ~Thing 0x0030A120) has 8 slots: 0
  calculateHeightAboveTerrain; 1-4 return NULL in Thing and `this` in
  Object's 0x00BFC300 (1-2) and Drawable's 0x00BFB0B4 (3-4): ZH's
  asObjectMeth/asDrawableMeth pairs, const first; 5 pure
  reactToTransformChange; 6 an empty virtual only Object overrides
  (0x0028B193, unnamed: placeholder `vslot6`); 7 the deleting destructor.
  Most of Thing's 388 views put the destructor at slot 0, which is
  wrong. **Next prerequisite: Matrix3D.** 298 of the 382 queued units fail
  C2079 on `Thing::m_transform` (by value). Matrix3D has no canonical
  header (about ten shim variants, 143 private views), so a canonical
  Matrix3D comes before the bulk of Thing (and Object, Drawable).
- **Object.** `dest` now resolves to
  Code/GameEngine/Source/GameLogic/Object/object.h (588a38cb67: BFME 1's
  object.h holds the class, ObjectStatusBits.h a padded 4-member view).
  The contract (read only; `class:Object` is held by another seat) over
  2,127 views decides sizeof 604 only by a thin majority (240 views; 1084:
  196, 120: 137, 68: 129, 632: 84, 596: 62 ...) and bases [] by majority,
  though retail Object derives from Thing at +0 (table 0x00BFC300) with
  Snapshot at +0x60 and interface tables at +0x64, +0x6C and +0x70 (ctor
  0x00298EA9). ZH's Object.h does not compile here. It queues slots 3, 4,
  5, 6, 8, 9 and 10, which are placeholders for Thing's slots now settled
  in thing.h. Object waits on Thing (Matrix3D) and its own base clause; do
  not generate it from this contract.
- **ObjectShroudClient: no header yet, and the views are wrong.**
  ??0Object (0x00298EA9) stores a 6-slot table at +0x64 (0x00BFC2D8):
  0 an AsciiString getter (rva00290EE0), 1 empty, 2 getGhostObject
  (0x00290EFE), 3 rva002941EA, 4 ShroudGetValueRangeAndMask, 5
  ShroudHideIfFogged. Another subobject's table sits at +0x68. So the
  interface is 4 bytes with 6 slots, but all three views (sizeof 8, 1-2
  slots at 0-1) treat the next base's vfptr as a pad. No reference header
  defines it (an Object-only BFME 2 interface, name invented), so its
  destination is its own header next to object.h,
  Code/GameEngine/Source/GameLogic/Object/ObjectShroudClient.h. Retarget
  the three views (ObjectPartitionShroudQueries, ObjectShroudRangeQuery,
  ObjectShroudValueRangeAndMask) to the 6-slot table and the 4-byte size
  before generating it.

Update 2026-10-30 (ObjectShroudClient query interface):

- **Correction to the 2026-10-29 layout account above:** Object+68 is a vbptr,
  not another subobject's vfptr. Constructor 298EC8 installs BFC320 there;
  its signed entries -4/+46C reach the virtual base at Object+4D4. The
  existing 28AADF base constructor and Object lifetime hierarchies retain
  their virtual inheritance. No complete original four-byte base is proved.
- **Query declaration scope cleared:** independent native table bytes prove
  the six targets at 7FC2D8 and slots 3/4/5 for the three query methods.
  All three files adopt ObjectShroudClient.h through the header lane. This
  is a four-byte compatibility surface with a separate eight-byte storage
  wrapper reserving the native vbptr; it is not an original class-name or
  full-hierarchy recovery. The empty slot has a protected opaque declaration
  that these views never call. Private probes and actual objects preserve
  all five matched rows and all ten external code definitions/relocations;
  bounded prediction conserves 1,622 linked bytes. Evidence:
  `reverse/attempt_support/shroud-interface-header-20261030/`.
- **Remaining:** full Object/BfmeCtor001B3A20 identity and hierarchy, the
  empty slot's actual signature, and Partition's preceding slots. No existing
  header debt key is retired and no census gain is claimed. The outgoing
  batch still requires the normal broader audit; an inconclusive audit is
  unverified outside this stated scope.

- **Publication receipt:** the shroud interface landed as a6312d3202 after a
  normal lost-race retry. Its final broader audit was INCONCLUSIVE: index
  ccafe54d1d predates outgoing base d6fa23a6fd and affected consumer
  `Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacked a current
  receipt. Five rows and the three-unit preview remain the verified scope.

Update 2026-10-30 (Rva00395C80Check Module header debt):

- Canonical Module's +4 member is ModuleData, not the old private view's
  purported next-module link. Native 395CC9/CF/D2 independently show module
  byte +25, pointer +4, then data byte +19. Separate partial module/data
  views retain that storage without inventing a derived identity or getter.
- All three rows and the parent's EH graph match retail; both external
  functions and their relocations are unchanged. Normal Module header
  acceptance retires this file's one key. The bounded preview conserves
  106 linked bytes; no census gain is claimed. Evidence:
  `reverse/attempt_support/castle-member-module-data-20261030/`.
- The previous failed header-only swap remains in the attempt log. This
  closes its missing-private-fields prerequisite; actual flag meanings and
  original function/derived data class names remain unrecovered. Broader
  audit results retain their published-index/current-receipt limitations.

Update 2026-10-30 (Rva004AC7C9FindModuleObject Module header debt):

- Native helper 4AC5F5 reads Object's module array at +244, adjusts each
  receiver by +0C, and calls secondary-interface slot +7C. Adopt canonical
  Module with a separately evidenced four-byte gap and the existing interface
  member at +0C. The derived/interface identities and slot spelling are not
  recovered or renamed. Existing helper/caller bodies keep their internal
  EAX convention; no public convention substitution or getter is introduced.
- All eight private row checks and the parent's EH graph are exact; all eight
  emitted external code definitions and symbolic relocations are unchanged.
  Normal Module header acceptance retires this source's one queued key.
  Evidence: `reverse/attempt_support/find-module-interface-header-20261030/`.
  Current-source build verifies all eight rows and the bounded preview
  conserves 410 linked bytes; no census gain is claimed, and the broader
  audit remains qualified.
- This closes the former bare-swap failure's missing `m_interface` storage.
  The file's other partial views and original placeholder identities remain
  separate work; this does not establish a complete derived layout.

Update 2026-10-29 (DieModule and BehaviorModuleInterface, d8d766afec7 / 7f9ddce7413):

- **BehaviorModuleInterface (target facts).** ??0BehaviorModule (0x00253330)
  stores the interface's own table 0x00BEE900 and then BehaviorModule's
  0x00BEE9C0 at +0x0C, and the primary 0x00BEEA7C at +0. BehaviorModule's
  sizeof is 0x10. 0x00BEE900 is exactly 47 `__purecall` slots: the primary
  table starts right after entry 46 of 0x00BEE9C0, so the interface has no
  virtual destructor. In 0x00BEE9C0 slots 0-42 are 0x000D43D0 (`xor
  eax,eax; ret`, a NULL getter), 43/45/46 are `ret 4` and 44 is `ret`.
- **Family getter map (target).** Over every matched
  `??0X@@QAE@PAVThing@@PBVModuleData@@@Z`, the +0x0C table each
  constructor stores differs from 0x00BEE9C0 at one slot per family: body
  modules 0, collides 1, contains 2, creates 3, damages 4, dies 7
  (DieModule's 0x002533D3 returns its +0x10 interface), special powers 8,
  updates 9, upgrades 10, AI updates 19. Client behaviours and draws, which
  are not BehaviorModules, also differ at many slots; their +0x0C is
  another interface (noise in this scan).
- **The ZH off-by-one.** ZH's BehaviorModuleInterface puts getDestroy at
  5 and getDie at 6. BFME 2's dies override slot 7, so one slot was added
  at 5 or 6, and ZH names from slot 5 on are shifted. The views that spell
  ZH names (getDie at 6, getSpecialPower at 7, getUpdate at 8 ...) are wrong
  from there on. BehaviorModule.h names only the family-pinned slots; the
  others stay placeholders (`slotNN`; BehaviorModule's own primary slots
  10-11 are `vslot10/11`).
- **DieModule (target).** ??0DieModule (0x0045CEBD) puts DieModuleInterface
  at +0x10. Its own table 0x00C1C780 has one pure slot (onDie), so sizeof
  is 0x14. DieModule's +0x0C table 0x00C4A650 overrides only slot 7.
  ~DieModule (0x0045CE54) restores BehaviorModule's tables inline (its
  destructor is empty and inline). The rowed ?isDieApplicable@DieModule@@IBE
  is protected.
- **Lane fix (69b428859e2).** Adoption strips the private views of every
  class the header defines or includes; before, units kept copies of
  DieModule's bases and failed C2011.
- **Adopted 14, queued 12:**
  - TailJumpWrappers5B.cpp and RebuildHoleExposeDie.cpp byte-match but
    would stop linking (link_check: 314 -> 0 and 187 -> 0 bytes), so they
    were dropped.
  - Six units hang accessors or fields on their private BehaviorModule
    stub: InstantDeathBehaviorOnDie (`object`), DamageFilteredCreateObjectDieCtor
    (`m_p14`), KeepObjectDie (`m_08`), FXListDieOnDie (getFXListDieModuleData),
    UpgradeDieOnDie (`->m_upgradeName`), CreateCrateDie (`objectModuleAnchor`).
    Each moves the accessor onto its leaf view, as CrushDieOnDie did.
  - CreateObjectDie_onDie calls the protected isDieApplicable through a cast
    pointer (C2248). Rewrite it as a member call, as RefundDieOnDie did.
  - RebuildHoleExposeDieFind needs getKey on DieModule (C2039).
  - DamageFilteredCreateObjectDieDtor and DieModuleDerived have mismatched
    destructor bytes (the destructor's inline/out-of-line shape).
- **TU merges.** RefundDie merged (7f9ddce7413, RefundDieOnDie.cpp removed).
  CrushDie dry-runs clean, but CrushDieOnDie carries a private `Thing` view
  (getUnitDirectionVector2D), and class_gate refuses it in the merged TU.
  It needs thing.h, which needs a canonical Matrix3D. HeroDie's donors adopt,
  but the link guard reports the seed HeroDie.cpp missing from the census
  index; wait for the next census. CallHelpOnDamage, GrantUpgradeCreate and
  CreateObjectDie wait on DamageModule, CreateModule and CreateObjectDie's
  queued unit.

2026-11-03: RadarMarkerClientUpdate's getter/updater views reconcile and pass local link checks; merging them also requires Radar factory return-interface reconciliation, while the destructor still needs DrawableModule getter and Rva00362EC7 vtable work ([reconciliation](../../reverse/attempt_support/radarmarkerclientupdate-consolidation-20261103.md), [Radar adoption trials and next step](../../reverse/attempt_support/radarmarkerclientupdate-radar-adoption-20261103.md)).

- 2026-11-04: GrantUpgradeCreate_onBuildComplete now adopts canonical CreateModule (78 bytes matched, link preview unchanged); reconcile seed/donor declarations and ModuleDataDtor bytes before merging. [Evidence](../../reverse/attempt_support/grantupgradecreate-buildcomplete-canonical-base-2026-11-04.md).
- 2026-11-04: GrantUpgradeCreate's seed now uses canonical Player and onCreate's Player queue row passed acceptance and retired (3/3 code rows exact; previews 177 -> 177 bytes); module/Object declarations and ModuleData lifetime shapes still block consolidation. [Evidence](../../reverse/attempt_support/grantupgradecreate-player-reconciliation-20261104.md).

- 2026-11-04: GrantUpgradeCreate's lifecycle donors now share canonical CreateModule and matching leaf declarations (2/2 rows exact; 196 preview bytes preserved); seed module/Object and module-data lifetime reconciliation still block merging. [Evidence](../../reverse/attempt_support/grantupgrade-lifecycle-base-20261104-codexb4.md).

- 2026-11-05 allocated `GrantUpgradeCreate.cpp` merge dry run still accepts no donors: donor Module/Object definitions conflict, the module-data ctor has duplicate `StringBase`/class declarations, and the dtor is byte-rejected. [Current dry-run evidence](../../reverse/attempt_support/grant-upgrade-create-consolidation-20261105-codex.md).

- 2026-11-04: ToggleMountedSpecialAbilityUpdate constructor merged into its approved TU (one source removed, 18 exact rows, census link guard passing); module-data constructor/deleter remain separate. [Audit and remaining blockers](../../reverse/attempt_support/togglemounted-constructor-merge-20261104-codexb4.md).
