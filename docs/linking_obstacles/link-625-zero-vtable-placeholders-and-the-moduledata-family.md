### LINK-625: Zero vtable placeholders, and the ModuleData family's vptrs

Status: Open (partly repaired). Updated: 2026-11-08 (seat ancalgonn-swarm-defects); earlier: 2026-11-07 (seat halilkkaya-lk49); base `f0cce4d912f`, census index
`c26c6b63fa`.

Evidence / affected units: [inventory TSV](../../reverse/attempt_support/zero-vtable-placeholders-20261107-lk49.tsv)
(one row per placeholder: family, symbol, defining unit, retail VA, class from the table's slot 0, canonical header,
the functions that store it, LINK-514 status, this entry's status). It sits between LINK-623 (lk45's sweep found these)
and LINK-514 (the runtime vtable survey, which judges `??_7` copies and cannot see an installer that stores no `??_7`).

**Problem.** A constructor that stores the address of a zero placeholder as its vptr (`char g_00XXXXXX`, a TU-local
`static int s_dummy0C`, an `*VTableAnchor`) crashes at its first virtual call, and the real link's vtable bridge cannot
repair it: the bridge places retail tables by the `??_7` name a vptr store relocates to, and these stores name nothing.
For module data the first virtual call comes during INI loading and object creation (ThingTemplate's slot-4 AI query
0x0033B387, Drawable's slot-22 LOD check 0x002797BD), so a single zero vptr on a common module data stops the game.

**Inventory (re-run of lk45's sweep, regenerated ledger in scratch only).** 267 zero placeholders (ours all zero, no
relocations, retail non-zero; padding, name lists and ThrowInfo anchors left out):

| family | count | notes |
|---|---:|---|
| ModuleData vptrs (`char g_00XXXXXX` stored by a module-data ctor) | 13 | 8 repaired below, 5 walled |
| other extern placeholders | 32 | module tables (DamageField, GloriousCharge, HordeTransportContain, Invisibility, the sound selectors, RunOffMap, W3DDefault/TreeDraw, UpgradeModule, UpgradeMux, ...) |
| TU-local dummy vptrs (`s_dummy*`, `s_secondary*`, `s_vtable*`, `*VTableAnchor`) | 222 in 71 units | 151 already listed by LINK-514 (87 need-identity, 37 need-view, 7 safe transient first stores, 7 blocked); 69 not in LINK-514 |

**Repaired: the ModuleData family** (eight extern placeholders and one TU-local dummy). Each constructor now derives from the canonical header and lets the compiler install
the class's `??_7`, and every other unit that emits the same table (the deleting-destructor scaffold or the destructor
unit) uses the same view, so both copies have one digest. Every repaired table has 31 slots against retail's 31:
GetSnapshotName equal by address, the other 30 inline bodies of retail's shapes (`ret`, `mov al,0/1; ret`, `xor eax,eax;
ret`, the `??_G`). Each batch: `./build.sh` exact, find_declared_unmatched clean, scoped DIR32 OK, and a link_check A/B
(HEAD vs change, both rebuilt) over every object defining an added or changed name and every unit naming the class, with
no verdict or byte change unless stated.

| class (ctor) | retail table | header | other copy fixed | link_check |
|---|---|---|---|---|
| StructureBodyModuleData (0x00257006) | 0x00BF4028 | ActiveBodyModuleData.h | FamilyDeletingDtors.cpp (1 slot) | 67/75 unchanged |
| CommandPointsUpgradeModuleData (0x00254891) | 0x00BF2658 | Rva00253487Base.h | FamilyDeletingDtors_muse-7c2e.cpp, with RefundDieModuleData | scaffold 0 -> 56 B LINKS |
| AIUpdateModuleData (0x0058925D) | 0x00C70220 | ModuleData.h | _muse-5c79.cpp, with WeaponModeSpecialPowerUpdateModuleData (0x00C4EA88) | 148/157 unchanged |
| TaintSpecialPowerModuleData (0x004C4AB8) | 0x00C5D608 | SpecialPowerModuleData.h | SpecialPowerModuleDeletingDtors.cpp; ElvenWood TU's Darkness, ElvenWood, FreezingRain, WeaponChange tables 1 -> 31 | 88/95 unchanged |
| UpgradeDieModuleData (0x002550ED) | 0x00BF33C0 | DestroyDieModuleData.h | FamilyUpgradeModuleDataDtors.cpp (owns ??1) | 441/456 unchanged |
| BoredUpdateModuleData (0x004966FE) | 0x00C4F590 | ModuleData.h | BoredUpdateModuleDataDtor.cpp (owns ??1) | 86/93 unchanged |
| EvacuateDamageModuleData (0x004BAD10) | 0x00C59CF8 | ModuleData.h | EvacuateDamageModuleDataDtor.cpp (owns ??1) | 85/93 unchanged |
| ExperienceLevelCreateModuleData (0x004B9220) | 0x00C595E8 | ModuleData.h (slot 9 override) | none existed | 79/86 unchanged |
| FXListDieModuleData (0x00253A78, `s_vtable`, LINK-514 needs-view) | 0x00C4ED70 (shared fold) | DestroyDieModuleData.h | none existed | 72/79 unchanged |

Taint's hand-built `vtbl_00C5D608` array (LINK-623 leftover) is gone; the CommandPoints unwind no longer goes through an
`/alternatename` to operator delete (its hatch line over-grants by one until `hatch_counters.py --update`). Sweep after:
267 -> 259 placeholders, none new (before the FXListDie repair; 258 after it).

Recipes that worked (reusable):
- **ModuleData.h's constructor is `__declspec(dllimport) __forceinline`** (BfmeModuleData.h precedent). MSVC 7.1 emits an
  implicitly defined or plain inline constructor as a COMDAT wherever it is generated, even fully inlined; a canonical
  `??0ModuleData@@QAE@XZ` then lost the census to ModuleFactory.cpp's Zero Hour copy (first in link order), so any ctor
  constructing ModuleData inline stopped linking (AIUpdateModuleData: LINKS 68 B -> not linking). After the change the
  only semantic difference over the 262 dependent objects is OpenContainModuleDataCtor.cpp dropping unreferenced
  COMDATs, and it now LINKS (0 -> 94 B).
- **A destructor unit that owns `??1X` keeps retail's inlined teardown** (member release, then Snapshot's vptr restore with
  no base call) by defining the empty base destructors inline in that unit only (`inline ModuleData::~ModuleData() {}`,
  likewise DestroyDieModuleData; Rva004ABFD9Dtor.cpp precedent). The restore then relocates to `??_7Snapshot@@6B@`
  (retail 0x00BBB554).
- **Scheduling:** when the compiler sinks its vptr store below the member stores (Taint, UpgradeDie), writing the first
  member through a pointer (`int *p = &m_x; *p = 0;`) keeps the store first, as retail has it. Dropping `/Oy-` kept
  StructureBody's ctor exact and made its compiler `??_G` frameless like retail's.
- **Include order:** in a TU whose first Snapshot include is ObjectModule.h (crc spelling), include ModuleData.h first;
  this changes nothing for module classes that declare no `crc` (EvacuateDamage.cpp: module tables unchanged).

**Walled (ModuleData family):**
- AutoDepositUpdateModuleData (0x002540ED, `g_00BF1BC8`) and StructureToppleUpdateModuleData (`g_00BF43A8`):
  ModuleFactory.cpp, first in link order, owns the rowed `??_G` and emits the Zero Hour 8-slot `??_7` (crc, xfer,
  loadPostProcess, `??_E`, four ZH getters: slot 0 is not even the destructor). A 31-slot copy in the ctor unit would lose
  the census, and that TU cannot include the canonical ModuleData. Needs ModuleFactory.cpp's two tag-constructor views off
  its Zero Hour ModuleData (or the `??_G` rows in an approved TU).
- TransitionDamageFXModuleData (0x004BA58A, `g_00C59B20`): TransitionDamageFX.cpp takes Snapshot through Drawable.h, which
  selects the capitalized slot spelling; ModuleData's lowercase loadPostProcess/xfer then add slots (33-slot table, slots
  1/3 `__purecall`). Including ModuleData.h first would respell Drawable's overrides in that TU (re_attempts 0x004BA58A).
- SpawnBehaviorModuleData (`g_00BF4128`) and AttributeModifierAuraUpdateModuleData (`g_00C50EE8`): their canonical
  headers keep the vector members (+0x20, +0x0C) as opaque bytes, while the constructors construct and clear them. The
  headers need the vector types (STLport in the header and in their includers) first.

**Other findings.**
- **MessageStream, boot path: repaired 2026-11-07 (seat halilkkaya-lk52, LINK-557).** `??0MessageStream@@QAE@XZ`
  (0x0030F697, MessageStreamListCtors.cpp) stored `s_messageStreamVtable`, a zero int; the factory 0x00225F12 creates
  TheMessageStream with it. After the seed's out-of-line init/reset/update were made inline (retail's slots hold the
  shared empty body) and MessageStreamDtor.cpp adopted canonical MessageStream.h, the constructor unit adopted
  MessageStream.h and CommandList.h: 19/19 rows exact, the constructor stores `??_7MessageStream@@6B@` (retail
  0x00C09890), the placeholder is deleted, and the unit's GameMessageList/CommandList tables grow from 3 slots to
  retail's 18. Both copies of `??_7MessageStream@@6B@` (ctor and dtor units) are identical, 20 slots against retail's 20.
  link_check: the ten MessageStream/CommandList units LINKS, bytes unchanged. Still wrong by name: slots 16/17 (seed
  Zero Hour removeMessage/containsMessageOfType) and CommandList slot 9 (see LINK-557); the bridge covers them.
- **GameClient::init's translators, boot path: repaired 2026-11-07 (seat halilkkaya-lk52).** GameClient::init news
  ten message translators and attaches them to TheMessageStream; two constructors stored a zero static anchor:
  `??0Rva005A7A90@@QAE@XZ` (0x004296C2, CommandXlat.cpp, priority 70, `_Rva005A7A90VTableAnchor`) and
  `??0Rva005B1A00@@QAE@XZ` (0x0043132D, Rva005B1A00Ctor.cpp, priority 40, `_Rva005B1A00VTableAnchor`). The tables they
  install, 0x00C3C6AC and 0x00C3C968, hold the real-named rows CommandTranslator::translateGameMessage (0x0042B0DE) and
  GUICommandTranslator::translateGameMessage (0x004314B1) in slot 0, so the first message any translator passed on
  jumped through zero. Both constructors are now those classes' own (hand renames, tombstoned; rename.py has no mode
  for a constructor into a class that already names rows), derive from FormationTranslator.h's GameMessageTranslator,
  and install `??_7CommandTranslator@@6B@` / `??_7GUICommandTranslator@@6B@`: 2 slots each, both resolving to rows at
  retail's words. Each unit defines its class's empty destructor (Zero Hour has both out of line) and emits the
  deleting destructor; they are rowed as fold-proof ICF twins of the translators' folded 0x00429191 (7 B) and
  0x004296EE (28 B). GameClientDrawableTOC.cpp's views and `new` calls follow the names (GameClient::init: bytes
  unchanged, only the two call relocations renamed). Seventeen units (both translators, TOC, WindowXlat, the
  SelectionXlat pair, the Rva0042CBB6/Rva00431F61/Rva00431FB5/Rva00575F38/Rva00576C4B/Rva0042C5C3 translator units,
  GUICommandTranslatorTranslateGameMessage and the MessageStream units) LINKS with bytes unchanged
  (Rva005B1A00Ctor.cpp 53 -> 88 B with its two twin rows).
- ToggleMountedSpecialAbilityUpdateModuleData (`s_vtableAnchor`): retail stores the vptr second; a compiler store sinks
  fourth (probe-proven in the unit's comment), so a class view alone does not match.
- BoredUpdate (the module, `s_dummy0C`/`s_dummy10` at +0x0C/+0x10): UpdateModule.h would give it retail's three tables
  (HeightDieUpdate recipe, LINK-514), but class:BoredUpdate is held (Burachi-3D, ArrowStormUpdate scope); not attempted.

Remaining / next check: (MessageStream done, LINK-557) the 69 dummy-vptr units LINK-514 does not list (DamageField,
GloriousCharge, Rampage, Enraged, StealthDetector, the special powers; mostly UpdateModule.h or SpecialPowerModule views,
LINK-514's recipe) and the 32 extern placeholders. Re-run the sweep (`lk45_sweep.py` over a scratch `data_ledger.py --out`)
before and after; every repaired constructor must leave the inventory with its table's copies identical.

**Boot-path triage of what is left (2026-11-07, lk52; retail call sites of each open constructor).** Constructed at
engine init: only the walled ModuleData family (SpawnBehavior, TransitionDamageFX, AttributeModifierAura, AutoDeposit,
StructureTopple and ToggleMounted, all built by their `friend_newModuleData` during INI load) and LaserFXNugget
(`g_00BDD7B8`, built by `LaserFXNugget::parse` 0x001E1519 while FXList INI loads; its first virtual call is the first
laser FX). LaserFXNugget's table 0x00BDD7B8 is [the nuggets' folded `??_G` 0x001E1152, its own doFXPos/doFXObj rows,
`ret 8` 0x0050B238 for Rva001DFEAABase's slot03, the base's rva001DFF5D]; 0x001E1152 calls the folded destructor
0x001E116E that releases a four-byte string at +0x148, so its +0x148 field is a string owner (as
CursorParticleSystemFXNugget's in HelixContainModuleDataDtor.cpp), not the `const char *` the ctor unit declares.
Constructed when objects are created (shell map, skirmish): W3DDefaultDraw (`g_00BC98B0`) and W3DTreeDraw
(`g_00BCCCF8`); both tables are 62 DrawModule.h slots of shared default bodies, but their slot 2 (GetSnapshotName) and
slot 0/`??1` rows sit under placeholders (`Rva000CEB69Named::name`, `Rva000CEB6F`) and slot 3 under
`W3DPropDraw::xfer`, so each needs that identity first, then DrawModule.h's pure slots (11-14, 35, 38, 39) declared as
the shared empty bodies. `VideoBuffer::VideoBuffer` (`_Rva0081C2F0VTableAnchor`, from W3DVideoBuffer's constructor)
is a transient first store the derived constructor overwrites. Rva0057551C, the Aries/Fesl/BfmeThingDGD network units
and the DirtySock debug print are off the boot path.

Clearance: none claimed (no real link or census run since); the eight installers now name their tables, so the
next real link's image report and bridge queue are the check.
Census confirmation: none claimed.

**2026-11-07, crash-prevention lane (seat ancalgonn-swarm-seat4), image `2bac16a657` (real-link run 42391021797).**
A store scan checked every boot-reachable retail vptr store (the LINK-627 walker, 7,809 stores) against the linked
diagnostic image: the image's copy of the same instruction, the table it really installs, and each of retail's slots
(jump-thunk chains followed, byte-equal bodies credited). It reproduces P18 exactly. Module data that stop Object INI
load (parseModuleName calls slot 4 unconditionally, retail 0x0033D865+0x249), first retail INI use in brackets:
AttributeModifierAuraUpdate `g_00C50EE8` (cinematicobjects.ini:6498), TransitionDamageFX (17072, triage), SpawnBehavior
(civilianbuildings.ini:18898), AutoDepositUpdate (35180), StructureToppleUpdate (civilianprop.ini:6722),
ToggleMountedSpecialAbilityUpdate (createahero.ini:358), CurseSpecialPower and ArrowStormUpdate (createaheropowers.inc
949 and 2779); the first six are this entry's walls. Open question: AttributeModifierAura precedes TransitionDamageFX
in the same file and its slot 4 is also 0 in this image, yet P18 stopped on TransitionDamageFX; P18's next receipt
should settle it.
- Repaired: CurseSpecialPowerModuleData (0x004CCD34) stored `extern "C" char SpyVisionUpdate_vftable = 56`, a misread
  .rdata byte. The unit already compiles the canonical chain, so dropping the hand store installs
  `??_7CurseSpecialPowerModuleData@@6B@`: 31 slots in ModuleData order against retail 0x00C5F778 (ICF-shared with
  EvacuateGarrison, StoreObjects and TeleportToCaster), store in retail's place, 5/5 exact (906c92743d).
- Walled: ArrowStormUpdateModuleData (0x00490639) stores `_vtbl_00C4D5A0`, an `/alternatename` for
  `??_7ArrowStormUpdateModuleData@@6B@`, and the kept copy is the 1-slot SELECT_ANY COMDAT from
  UpdateModuleDataDeletingDtors.obj, the scaffold of the rowed `??_G` 0x00490679 (slot 4 reads ASCII). The scaffold TU
  takes ModuleData from BfmeModuleData.h, so its view cannot derive from canonical SpecialAbilityUpdateModuleData; the
  map approves the ctor, `??_G` and `??1` for ArrowStormUpdate.cpp, but the scaffold and ArrowStormUpdate.cpp are both
  mixed, and a compiler-installed vptr was already refuted for this ctor (re_attempts line 1345). Route: split the
  scaffold, then merge into ArrowStormUpdate.cpp with one canonical view.
- Scaffold rule on this image: no table where a longer copy loses; 335 tables kept from a deleting-dtor scaffold, 23 of
  them module data. Of those 23, 20 constructors install a hand-built 31-slot array equal to retail (latent: replace
  the array and the scaffold view in one commit), ArrowStorm is live, SpawnBehavior and TransitionDamageFX store zero.

Update (2026-11-07, crash-triage seat2, P18; claim file:TransitionDamageFX.cpp and 0x004BA58A): TransitionDamageFX is the
boot path's next stop once P16 is passed (call 0x0 from ThingTemplate::parseModuleName+0x24c; the job's smoke.json regs
put eax at `?g_00C59B20@@3DA`). Taken with one Snapshot spelling for the unit, as the 0x004BA58A record proposes:
TransitionDamageFX.cpp includes the canonical ModuleData.h before Drawable.h (Drawable.h selects the capitalized slots
only when Snapshot.h is not yet included), its UpdateModuleData view derives from ModuleData, the explicit vptr member and
`g_00C59B20` go, and the class declares its out-of-line virtual destructor (0x004BA715). Branch commit 7b3a0f3a07: 58/58
exact, `??_7TransitionDamageFXModuleData@@6B@` 31 slots in ModuleData's order (retail 0x00C59B20 is 0x00C4ED70 with its own
`??_G` in slot 0), the unit's `??_G` byte-identical to retail 0x004BA6F9. No shared header edited. Pending a branch
receipt and review.
Correction (same day): the first branch receipt (2026-11-07T172257Z-boot_smoke-7aa7683f0547, d048b0c454) still stopped in
parseModuleName, one virtual call later (+0x25f, slot 7, `_bfmeDisp0Slot_Purecall`): the image's
`??_7TransitionDamageFXModuleData@@6B@` was FamilyDeletingDtors.obj's one-slot copy (one slot, then a zero word) (its one-virtual scaffold view emits the
rowed ??_G 0x004BA6F9, displaced in tu_map), which won the COMDAT selection over the constructor unit's 31-slot table. The
scaffold's view now derives from the same UpdateModuleData-over-ModuleData bases, as 8606f0149f and 4d44fb30c14 did, so both
copies have the same 31 slots and the same ??_G.
Scan rule for this shape (for the crash-prevention lane): a deleting-destructor scaffold (FamilyDeletingDtors*.cpp,
*DeletingDtors*.cpp, OpaqueScalarDeletingDtors*.cpp) declares a class as `class X { public: X(EmitVtableTag *); virtual ~X(); };`
so that it emits the rowed `??_GX`. That view also emits a one-slot `??_7X@@6B@` COMDAT. When nothing else defines `??_7X`,
or the constructor unit stores a placeholder instead, the short copy is the kept table; when the constructor unit is fixed to
emit the full table, the scaffold's short copy can still win the COMDAT selection (TransitionDamageFX above). Detect it on an
image's own inputs (image_objects.json): for every `??_7` defined as a COMDAT in two or more objects, compare each
definition's size and flag names whose copy kept in exit.map is shorter than another definition; separately list the tables
kept from a scaffold object rather than retail_vtables.obj. In image d048b0c454: 108 one-virtual EmitVtableTag scaffold
views; 57 of their tables are kept from the scaffold object (23 of them ModuleData classes, e.g. SpawnBehavior,
AttributeModifierAuraUpdate, InheritUpgradeCreate, GrantUpgradeCreate, SpecialPower, MonitorConditionUpdate,
PickupStuffUpdate, PropagandaTowerBehavior, HordeGarrisonContain), 51 are bridged; TransitionDamageFX was the only case
where a longer source copy lost. Fix rule: whenever a constructor unit is made to emit a class's real table, give the
scaffold's view the same bases in the same commit so both copies are identical.

**Consolidation follow-ups (for the merge lanes).**
- ArrowStormUpdate.cpp merge (parked by the crash-prevention lane, 2026-11-07). Split
  `Code/GameEngine/Source/GameLogic/Object/Update/UpdateModuleDataDeletingDtors.cpp` so that `??_GArrowStormUpdateModuleData`
  (0x00490679) can leave it. Then merge the approved rows into ArrowStormUpdate.cpp (`tu_skeleton --plan`: 29 rows,
  11 donors, 4 mixed, among them ArrowStormUpdate.cpp itself), with ctor 0x00490639, `??_G` and `??1` 0x00490695 under one
  ArrowStormUpdateModuleData view over canonical SpecialAbilityUpdateModuleData. That view must come before the TU's
  Drawable.h include, or Snapshot takes the capitalized spelling. This retires the `/alternatename:_vtbl_00C4D5A0` hatch and
  the 1-slot scaffold table that the ctor's store resolves to today. The ctor store order is a separate wall
  (re_attempts 0x00490639, lines 1345 and the 2026-11-07 blocked verdict). Until this lands, the first ArrowStormUpdate block
  in Object INI (createaheropowers.inc:2779) reads a non-code slot 4 unless the real link bridges 0x00C4D5A0.
- Latent, bridged today: `??_7StoreObjectsSpecialPowerModuleData@@6B@` compiles to 33 slots in
  MissileLauncherBuildingUpdate.cpp: `__purecall` at slots 1 and 3, then ModuleData's lowercase loadPostProcess/xfer at 4/5.
  Retail 0x00C5F778 has 31 slots, ICF-shared with Curse, EvacuateGarrison and TeleportToCaster, whose units compile 31.
  The TU takes the capitalized Snapshot spelling before SpecialAbilityUpdateModuleData.h. It needs this entry's
  one-spelling fix before the vtable bridge retires.

**2026-11-07, crash-prevention lane (seat ancalgonn-swarm-seat4): Tier 1 module data after P18.**
- AttributeModifierAuraUpdateModuleData (P19, f7a542e290) and SpawnBehaviorModuleData (ec91896fc6): the vector-member
  wall above holds for the canonical headers (most of their includers are not STLport units, so the headers cannot take
  the vector types). Each constructor unit therefore keeps its own typed view, but on canonical ModuleData instead of the
  explicit vptr member over an empty local base. Each deleting-dtor scaffold view gets the same base in the same commit
  (BuildingBehavior.cpp for AMA, FamilyDeletingDtors.cpp for Spawn). Both copies of each `??_7` are identical: 31 slots
  in ModuleData order, retail 0x00C50EE8 / 0x00BF4128, with byte-identical `??_G`. The ctor unwinds now call the rowed
  `??1ModuleData@@UAE@XZ` 0x0049B47C. AMA's alias row `??1UpdateBase@@QAE@XZ` is retired in deleted_rows.csv; Spawn's
  unwind used to call `??1BehaviorModuleData@@QAE@XZ`, which no row names.
- AutoDepositUpdateModuleData (0x002540ED) and StructureToppleUpdateModuleData (0x00257A5E): still walled, now
  measured. The same constructor change compiles exact (branch `scan/adst-interim-vptr`, 000641716b, parked), but
  ModuleFactory.cpp, first in link order, emits Zero Hour 8-slot copies of both names (`crc`, `xfer`,
  `loadPostProcess`, `??_E`, four Zero Hour getters) beside the rowed `??_G` it owns (0x0025528B, 0x00257B5E, both
  displaced in tu_map), so the constructor units' 31-slot tables lose the SELECT_ANY selection. An offline
  `vtable_bridge.plan()` over the exit link's own inputs, with the parked change built:
  - committed `reverse/data_ledger.csv`: both names (and AMA's and Spawn's) are unindexed bindings and are not
    planned. Retail 0x007F1BC8 / 0x007F43A8 / 0x00850EE8 / 0x007F4128 are still kind=global under the placeholder
    names, so the interim would leave the Zero Hour copy kept. Not landed;
  - regenerated ledger (`data_ledger.py --out`, scratch): all four are planned at 31 slots with no refusal.
  Interim route: land 000641716b with the next ledger refresh (Link tooling lane), checked by the same offline plan.
  The bridged state is debt, not progress. Lasting fix: TU approval for 0x0025528B and 0x00257B5E so the `??_G` rows can
  leave ModuleFactory.cpp for a unit on canonical ModuleData; queued for the TU-evidence work.
- Update (same day): landing order is constructors first, then the ledger. `data_ledger.py` derives its rows from
  objects, so the Link lane's regeneration on master could not bind `??_7AutoDepositUpdateModuleData@@6B@` /
  `??_7StructureToppleUpdateModuleData@@6B@` while the constructors still stored `g_00BF1BC8` / `g_00BF43A8`. The
  scratch plan above was built on the parked change. The constructors land now (interim, bridged), and the
  regeneration follows and re-checks both at 31 slots. Both classes crash at INI load either way until then.
- ToggleMountedSpecialAbilityUpdateModuleData (0x004AE0AC): blocked. Naming the real table in the explicit store is
  refused by MSVC (C2373: the polymorphic class owns `??_7…@@6B@`), and a compiler-installed vptr reproduces the
  recorded sink-to-fourth schedule (FAIL 1/1). The deleter's full-table view is ready but moot without a constructor
  spelling that stores the vptr second (re_attempts 0x004AE0AC).
- ToggleMountedSpecialAbilityUpdateModuleData (0x004AE0AC): repaired the same day, which retracts the blocked note above.
  The schedule wall came from a wrong member type. Retail's dtor 0x004AE10B releases +0xD0 through AsciiString's
  0x00036410, so MountedTemplate is a string. With that type, the float and both flags in the initializer list, and the
  virtual dtor declared, the compiler installs the real `??_7` second, as retail does (exact). The deleter's view
  derives from the same canonical bases, and both copies are 31 identical slots.
- W3DTreeDraw (ctor 0x000CEB4D, `g_00BCCCF8`, 267 Object INI uses): the three walled slots, by the retail tables that
  hold them:
  - slot 0 `??_GRva000CEB6F` 0x000CEF83: slot 0 of DrawModule's own table 0x00BC9690 and of W3DDefaultDraw, W3DTreeDraw,
    W3DBuffDraw and W3DPropDraw. Its `??1` 0x000CEB6F (16 direct callers) is already rowed as `??1DrawModule@@MAE@XZ`, so
    `Rva000CEB6F` folds into DrawModule, not W3DTreeDraw. DrawModule is registered in canonical_classes.csv, so the
    `rename.py class --fold` waits for seat6's tool. For W3DTreeDraw it is then an ICF alias of DrawModule's `??_G`.
  - slot 2 `Rva000CEB69Named::name` 0x000CEB69: only W3DTreeDraw's table holds it, so it is W3DTreeDraw's own
    GetSnapshotName. `--to-class W3DTreeDraw` needs `--prepared` for W3DDrawNameGetters.cpp (not a proof failure).
  - slot 3 `W3DPropDraw::xfer` 0x000B221A: slot 3 of W3DDefaultDraw, W3DTreeDraw, W3DBuffDraw, W3DPropDraw and
    W3DStreakDraw, and absent from DrawModule's table. That is an ICF fold of the per-class xfers, so it is an alias row
    `?xfer@W3DTreeDraw@@MAEXPAVXfer@@@Z` via `add_match.py --icf-owner ?xfer@W3DPropDraw@@MAEXPAVXfer@@@Z` with
    fold-proof, defined in the unit that gets W3DTreeDraw's DrawModule.h view.
  Order: the DrawModule class fold (seat6's tool), then slot 2, slot 3 and the slot-0 alias, then W3DTreeDraw.cpp on
  DrawModule.h with its pure slots (11-14, 35, 38, 39) as the shared empty bodies. W3DDefaultDraw (`g_00BC98B0`, 94
  uses) shares slots 0 and 3 and follows the same path.
- Bridge check after the ledger regeneration d88c3448da (2026-11-07, crash-prevention lane): an offline
  `vtable_bridge.plan()` over the exit link's inputs at master 43f1ab7bb0 plans `??_7AutoDepositUpdateModuleData@@6B@`
  (0x007F1BC8) and `??_7StructureToppleUpdateModuleData@@6B@` (0x007F43A8) at 31 slots with no refusal. That is the
  interim, bridged state, debt until the `??_G` TU approval. AttributeModifierAura, SpawnBehavior and ToggleMounted are
  planned at 31 too. ArrowStormUpdateModuleData (repaired in 43f1ab7bb0, after this ledger was built) is an unindexed
  binding: its retail row 0x0084D5A0 is still `global _vtbl_00C4D5A0` (the removed hatch's name), so the next
  regeneration binds it. Until then the constructor unit's full 31-slot copy is the one kept: link order follows object
  path, and `arrow^storm^update^module^data^ctor.obj` sorts before `update^module^data^deleting^dtors.obj`, the scaffold
  that keeps a 1-slot copy because its TU defines ModuleData through BfmeModuleData.h.

**2026-11-08, static-defects lane (seat ancalgonn-swarm-defects): image_report's `ours_zero_retail_not` at real link
`0448c6d48c` (26 rows, plus `contents_differ` 1).** Each row was read against retail. They are not scattered statics:

- 25 of the 26 are this entry's zero vptr placeholders: a constructor or destructor stores `&g_00XXXXXX`, a 1-byte zero
  `char`, as a vptr. They cover 15 classes, and each class still needs its first virtual call fixed.
- The 26th, `g_00C6E614` (Rva0057551C / Rva00575540), is also a stored vptr; this entry's boot-path triage already puts it
  off the boot path.
- `contents_differ` is the DirtySock format string `_Rva012C4C24`, LINK-623's padding artifact, not an image defect.

The real link names none of these tables, so the bridge cannot repair them (see Problem, above). No extracted retail INIs
are reachable from srv1, so I could not rank by INI use. Every class is first constructed at object creation, not at
engine init.

| class (tables) | status |
|---|---|
| W3DTreeDraw, W3DDefaultDraw (267 and 94 INI uses, above) | walled above: the DrawModule fold |
| UpgradeModule, UpgradeMux | LINK-218 |
| DamageFieldUpdate (`g_00C4D970`, `g_00C4D964`) | **repaired**, below |
| GloriousChargeUpdate, RousingSpeechUpdate, ArrowStormUpdate | **repaired** on canonical SpecialAbilityUpdate, compiler-installed tables: 71 of 82 slots resolve to retail's address on each, the rest are the base's inline bodies equal to retail's, slot 1's jmp and slot 2's name (P41). A byte-exact ctor was not enough: on its private base GloriousCharge was 21/21 with a short table and purecalls. See the notes below |
| InvisibilitySpecialPower, SpecialPowerTimerRefreshSpecialPower | open, header lane: `SpecialPowerModule`'s slots are rowed under real names, but it has no canonical header, only the placeholder-named `Rva00493009` (Rva00493009.h), and about 53 units declare the class privately |
| SpawnedModelConditionCreate | **repaired**: canonical CreateModule, compiler-installed tables; 55 of 63 slots resolve to retail's address, the other 8 are the same one-instruction shapes or the deleting destructor, except slot 2 (name getter, a non-virtual row) |
| RunOffMapBehavior | **repaired**: `onObjectCreated` (agreement `nl-e30c47943087`), canonical BehaviorModule, empty ctor body, compiler-installed tables. All 12 primary, 47 interface and 1 `triggerFlee` slots resolve or equal retail's bytes, slot 2's name included. The slot check also found slot 35, retail's null-guarded return of the +0x10 interface: inherited, it would have returned null. `BehaviorModule.h` asks units with its opt-in macros to emit no derived table because they go unmeasured; this unit's are measured here |
| UpgradeSoundSelectorClientBehavior, ModelConditionSoundSelectorClientBehavior | **repaired** over a real 19-slot base (`Common/Rva00252B68.h`): empty ctor bodies, compiler-installed tables, all 3 interface slots and 17 of 19 primary slots resolve or equal retail's bytes. Slot 2 reads the base's name (P41). Slot 1 is `DrawableModule::loadPostProcess`, still Module.cpp's: retail's 0x000B3FD0 was claimed by another worker, so it is not rowed yet. See the notes below |
| HordeTransportContain | open, large: its ctor stores 10 tables (OpenContain, TransportContain and Horde levels); nearly all 31 primary slots are rowed under real names, but no shared view of the chain exists |

**Repaired: DamageFieldUpdate** (ctor 0x004912A9, dtor 0x0049122C). The HeightDieUpdate recipe, with FireWeaponUpdate on the
canonical UpdateModule: the compiler installs `??_7DamageFieldUpdate`'s three tables in retail's order.

- Bytes: 36/36 across the unit, FamilyDeletingDtors.cpp and DamageFieldUpdateRva004911AE.cpp.
- Slots: 60 of 63 resolve to retail's address against 0x00C4D970, 0x00BEFF90 and 0x00C4D964. Slot 0 is the weak `??_E` of the
  rowed `??_G`; slot 1 is `UpdateModule::loadPostProcess`, where retail's 0x00483CEF is a `jmp` to 0x00497805, one of that
  name's addresses; slot 2 reads "UpdateModule" (below).
- A trap for this family: FamilyDeletingDtors.cpp's `EmitVtableTag` scaffold emits a one-slot `??_7Class@@6B@`, the name the
  real class gives its +0x10 table, so one copy would have won silently. Move each `??_G` with its class (a displaced
  deleting destructor rides with the vtable's unit, docs/consolidation.md), or give the scaffold the same view.
- link_check: run the unit and FamilyDeletingDtors.cpp together. Alone, the unit reports "does not link" against the census's
  old first copy of `??_7DamageFieldUpdate@@6B@`. Together: 6/6, LINKED 18,685 unchanged.

**Open: slot 2.** `rename.py function --to-class DamageFieldUpdate --new ?GetSnapshotName@DamageFieldUpdate@@MBEPBDXZ` for
0x0049125E plans and builds exact, then its post-build check refuses because slot 1 differs. Recorded as a false reject.

**2026-11-08: slot 2 returns the base's name (packet P41; not a boot stop).** A class moved to real tables by this entry's or
LINK-514's recipe inherits its base's `GetSnapshotName`, where retail's table holds the class's own getter: the getter is rowed
under a non-virtual or placeholder name, so nothing overrides the slot. Classes: DamageFieldUpdate ("UpdateModule"),
SpawnedModelConditionCreate ("CreateModule"), and LINK-514's Wall 1 (HeightDieUpdate, BoredUpdate, StealthDetectorUpdate and the rest of
that recipe); RunOffMapBehavior when it lands.

- **The reader.** `GameState::addPostProcessSnapshot` (0x002DCF6C, GameStatePostProcess.cpp:106) is the only reader in our source.
  It compares the name with exactly two strings: "Object" goes to the front of the post-process list, "Weapon" is left off it, the
  rest go to the back. A module that returns its base's name takes the same branch as under its own name.
- **The two names that matter.** `Object`'s getter is rowed and its table holds it. `Weapon`'s is not: retail table 0x00C0214C holds
  0x002CC2F6, rowed as the free function `?Rva002CC2F6Get@@YAHXZ`, and `??_7Weapon@@6B@` in WeaponCtor.cpp and WeaponDtor.cpp had
  `__purecall` in slots 1-3, hidden by the bridge; retiring it would have crashed the first Weapon a load reaches. Repaired 2026-11-08 (below).
- **The bridge.** The same applies to the module tables: where the bridge binds `??_7Class`, the image has retail's slot 2. This entry's
  repaired classes get that binding from the next ledger regeneration (their rows are still address-named `global`s).
- **Not compared.** No save/load has been run. Other readers under other spellings are not excluded: a scan of retail's `call [reg+8]`
  sites followed by a string-taking call found 85, and the 30 I read are not Snapshots, but it is not a census. CRC: no reader in our
  source, not checked against retail's XferCRC.

**Family size** (`mov eax,imm32; ret` at slot 2 of a table in retail, a string as the result):

| Row today | Getters |
|---|---:|
| already `GetSnapshotName` | 140 |
| `?name@C@@QBEPBDXZ`, on the class the string names | 96 |
| `?name@RvaNNNNamed@@QBEPBDXZ`, a placeholder class | 197 |
| `?RvaNNNNGet@@YAHXZ`, a free function | 289 |
| other | 1 |

**A mechanical fix, as a tool change.** The string itself proves the class, and the slot's name comes from the class's declaration, the
evidence `rename.py function --to-class` already accepts. That route takes placeholder-class members (197). It refuses a row already on
the class ("is already a member": the 96, and RunOffMapBehavior's `rva00462213`) and has not been tried on a free function (289). Teaching
it those two shapes, and letting its post-build check follow a `jmp` thunk (the DamageFieldUpdate false reject), would let a batch respell
each class's getter as that class gains real tables. A class without an installer that compiles its table gains nothing yet, so this
follows the family rather than replacing it.

**2026-11-08: image_report's `with_wrong_pointers` (7 rows at real link afebf7e78c), read one by one.** Every row is a kept table with
`__purecall` or a base's slot where retail has a body, and every row is bridged today, so none crashes in the current image. Each becomes
a crash on its first virtual call **if the bridge retires that table first.** Report order, with the earliest boot-walk order of a store
(`seat4/build/crashprev/scan3.tsv`; reachability, not a trace, and the bridge makes each store fine today):

| table (retail) | order | conflicting slots | state |
|---|---:|---:|---|
| `??_7Rva0023DB34@@6B@` (0x00BEDAA8) | 25465, via LivingWorldLogic | 4 | **repaired**: the view declared the four slots pure; all four were rowed under the class. 4/4 resolve |
| `??_7StancesBehavior@@6BObjectModule@@@` (0x00C424DC) | 9960 | 2 | Fixed 2026-11-08: both units on the canonical class, the hand-built array retired for the compiler's table. Read back 0 differ of 13, 47 and 3 |
| `??_7Rva00481F82@@6BObjectModule@@@` (0x00C49408) | 10078 | 5 | P42: TerrainResourceBehavior's own table under a placeholder; `class --fold` refuses (the ledger names the table for the placeholder), and the unit carries hatches |
| `??_7LargeGroupAudioUpdate@@6BUpdateModule@@@` (0x00C548F0) | 10669 | 1 | P42: `--to-class` for 0x004AB9D5 needs LargeGroupAudioUpdate.cpp prepared; the dtor's view is a scaffold, and the ctor unit hand-builds the table |
| `??_7GiveOrRestoreUpgradeSpecialPower@@6BSpecialPowerUpdateInterface@@@` (0x00C552A4) | 10579 | 8 | the SpecialAbilityUpdate base (below in this entry): the table is shared, and this class's scaffold is only the kept copy; the base's slots are now all defined, so a class on canonical SpecialAbilityUpdate no longer emits these 8 |
| `??_7ChangeStanceGroupOrder@@6B@` (0x00C6A36C) | 22257 | 8 | P42 source repair verified 2026-11-08: both emitters now produce the native 14 slots; complete 56-byte compiler table and all relocations pass. Temporary shared ABI view preserves rowed names; canonical hierarchy and next real-image check remain open. [Evidence](../../reverse/attempt_support/change-stance-native-table-20261108/README.md) |
| `??_7Rva003FA118@@6B@` (0x00C3789C) | not in the walk | 1 | P42: slot 0 is `?rva0056B613@Rva0056B613@@QAEXH@Z`, a non-virtual placeholder row; **2026-11-09 (`0x0056B7A0` virtual respell)**: base `Rva003F9FE6` now fills slot 0 with `?rva0056B7A0@Rva003F9FE6@@UAEEH@Z` instead of `__purecall`, remaining bridged until `0x0056B613` moves as `unsigned char` onto `Rva003FA118 : public Rva003F9FE6` |

**Weapon was not among the seven** (the report sees only rows with a ledger name it can match), though it had the same defect, and an earlier reachable store
than any of them (order 2116): **repaired.** Both `??_7Weapon@@6B@` copies are now the 4 slots retail holds in 0x00C0214C (the deleting destructor, an empty
`loadPostProcess`, `GetSnapshotName` returning "Weapon", `xfer`), so `GameState::addPostProcessSnapshot` still leaves Weapons off its list with the bridge retired.
Its getter row 0x002CC2F6 is still the free-function placeholder `Rva002CC2F6Get`, a name debt (P41) and no longer a trap.

**Before retiring any bridged table: compare the kept copy's slots with retail's.** The image report's seven undercount this (Weapon), `pointers_unchecked` is 8,314, and a bridged image hides all of it.

**For the header seats, so they need not re-read these** (each row of the status table above carries its blocker): SpecialPowerModule's slots are rowed under real names
(pauseCountdown, getPowerName, doSpecialPower*, isReady, startPowerRecharge, ApplyPowerToObject and more) and need one canonical class in place of `Rva00493009` and the private views. HordeTransportContain's
10 stores are 3 zero placeholders plus 7 folded tables under other classes' names (AODHordeContain, HordeSiegeEngineContain, TransportContain); its primary slots are nearly all rowed under OpenContain, TransportContain and the class.

**The SpecialAbilityUpdate family, notes for the next class.**

- The list at +0x88 is a real member, not a missing one. `m_88(Rva0029FB3BAlloc())` calls the allocator constructor 0x0029FB3B;
  the empty temporary is the spare `ebp+0xF` stack byte the old casts spelled as a "context". The allocator needs a user
  constructor, or the temporary is zeroed (`xor eax,eax; stosb`). With `reset` and the destructor `throw()` no second EH state
  appears. RousingSpeechUpdate and ArrowStormUpdate use this; GloriousChargeUpdate still has the older private list view and hand calls.
- `Rva0044EF5E` stays as an intermediate class. The ledger's row at 0x0044EF5E carries that name, so `??0SpecialAbilityUpdate`
  compiles byte-exact and is unresolved in the link. Renaming the owner reaches 38 units and is still to do.
- Check slots against each class's own table. ArrowStormUpdate overrode primary slot 16 (0x00490628, now `continuePreparation`)
  and +0x20 slot 8 (0x004906CD, now `vslot08`), both already byte-exact under placeholders; the byte gate could not see them
  missing from the table.
- `vslot08`'s parameter is spelled `int` across the family (0x0044EDA6, 0x004AE583, 0x0049C553, 0x004929D1, 0x00492E79).
  ArrowStormUpdate's body uses it as a `const Coord3D *`, so the family's real signature is probably the pointer. Respelling it is one change over six rows.
- `SpecialPowerUpdateInterface`'s slots 1-5 and the base's other inline bodies still show as different addresses because retail
  folded them with unrelated one-instruction functions. They are equal in bytes, so this is not a defect.
- RousingSpeechUpdate's TU merge is blocked only by the `RousingSpeechUpdateModuleDataCtor.cpp` donor's view. ArrowStormUpdate's is
  blocked by the TU holding `Rva0029FB80Store` (0x0029FB80, approved for InGameUI.cpp). Its header-queue row for the ctor retires once
  the SpecialAbilityUpdate units reach the census, since the hook judges that unit alone.

**The sound selectors, notes for the rest of this base.**

- The "redundant first store" to +0x0C is an interface base's own constructor. Any ctor here that writes +0x0C twice in that order
  wants a second base class with a vptr, not a volatile store.
- Retail's selectors have no `??_G` of their own because theirs fold with `??_GRva00252B68`. Ours compile their own deleting destructors,
  equal to retail's bytes outside relocations, with an implicit `??1` that is just a jump to the base's. The behaviour is the same.
- `DrawableModule::xfer` is now rowed at 0x00560AE1 (retail's 0x00C07E54 slot 3, Version1 twice). Module.cpp held Zero Hour's different body.
  Its other present-unmatched bodies, including `DrawableModule::loadPostProcess`, may be wrong the same way.
- `??_7Rva00252B68@@6B@` itself is still short and bridged. Three units emit it, and all three must take the header together: `Rva00252B68Ctor.cpp`,
  `Rva0049B47CDerived.cpp` and `AnimationSoundClientBehavior.cpp` (the copy ctor 0x004CA125, on a private `Rva004C9FBF` view). The first two
  alone are 11/11 exact with 0 slots differing, but leave a COMDAT conflict that costs AnimationSound its 2,360 linked bytes. The table is
  only live during construction and destruction.
- Other classes on this base store real tables by hand, so they are not zero-vptr defects, and can take the header later:
  TerrainResourceClientBehavior, ModelConditionAudioLoopClientBehavior, RandomSoundSelectorClientBehavior and AnimationSoundClientBehavior.

**`RenderObjClass` against retail, found while checking BaseHeightMap (fixed by P53, below; P23's handoff has the detail).** Slots 51 and 52: `rendobj.h` returns `const Matrix3D &`,
but the ledger rows at 0x0006D06D return by value through a hidden pointer. Slot 98: the header's `Is_Visible` is a bit test, retail's 0x0013B6D0 is 55 bytes. Every class that
compiles a RenderObjClass table carries these. The fix is a full-gate edit of `rendobj.h`.

**`Rva000E3B41` (flat height map) against retail, 2026-11-08.** The class the boot stop reaches: 129 compiled slots against 149 in retail's 0x00BCE788, with
slot 145 the call at `W3DTerrainLogic::getGroundHeight+0x3F`. Thirteen slot bodies were rowed as non-virtual methods of private views, and the table inherited the
base's instead. They are now virtual overrides on `Rva000E3B41`, with both installers on the canonical `BaseHeightMap.h`. Read back by slot on both: 149 (allowed gaps 0, 51, 52, 98), 1, 2 and 4.
- The byte gate could not see any of this: every moved body matched before and after. The slot read found one more after the primary table was right: `DX8_CleanupHook` slots 0 and 1 (0x000E1271, 0x000E1276) were rowed under the view's name and the table inherited the base's bodies.
- A `__forceinline` wrapper is no way to move a slot. It compiles to a bare `jmp` for a body with EH state, moves registers in larger bodies (0x000E3CE1, 0x000E1669), and leaves an unrowed definition. Make the view the table's class, with its first pad 4 smaller.
- `class RefRenderObjListIterator;` at namespace scope in `BaseHeightMap.h` is a repeatable C1001 in `Rva000E1341FillSlots.cpp` (`msc1.cpp` line 2701), though other units compile it. The cause is not understood. Elaborating the type in the parameter avoids it, with the same mangled name.
- Renumbering the labels voids a parent's funclet `object-symbol=` tokens, and funclet rows locate only through a parent row that exists. Row the parent first, then rebind from the unwind map by state against retail's.
- Still open: `Rva000E3B41` and its slots' names are placeholders until the class rename to `FlatHeightMapRenderObjClass`.

**The `crc` trio and `GameClient::loadPostProcess`, P54, 2026-11-08.** Retail's Snapshot slot 2 returns the class's name. `Locomotor`, `WeaponSet` and `GameClient` compiled Zero Hour's `crc(Xfer *)` there, an empty `ret 4`, so a caller that pushes nothing, like `GameStatePostProcess.cpp`'s `snapshot->GetSnapshotName()`, would unbalance its stack. All three tables are bridged, so slot 2 is right in today's image: this was latent, and retiring those bridges would have exposed it. Each row now has the class's name (`GetSnapshotName`), and the `present-unmatched` definitions are gone.
- `Locomotor` and `WeaponSet` rows are in their approved units. `GameClient`'s two stay put: 0x0004C457 and 0x00239A9D have only proposed TUs.
- `WeaponSet.cpp` still compiles Zero Hour's class, so it includes `WeaponSetNameSlot.h` beside it: Zero Hour's header plus the one declaration. A new `GameLogic/WeaponSet.h` under `reference/shims` reads as a shared-header change reaching 1,405 sources, whatever includes it; `reverse/cl_include_roots.txt` also refuses a new root. Its emitters (`WeaponSetCtor`, `Deleter`, `Dtor`) are what fill the table. Retire the file when the unit adopts `WeaponSetClass.h`.
- **Not fixed: `Locomotor`'s slot 3 (save/load).** Retail's table 0x00BDE888 holds 0x001E525A at slot 3, 382 bytes that save the object's state, rowed `?xfer@Rva001E3E43@@`. `?xfer@Locomotor@@` is rowed at 0x00341E2D as an ICF twin, 27 bytes that write only a version, on the claim that BFME 2's `Locomotor` keeps no state. 0x00341E2D is held by three other tables (0x00BC7318, 0x00C07D38, 0x00C117A4), not this one. The bridge has the slot right today, so it goes live when `??_7Locomotor@@6B@` retires: a loaded game would lose every locomotor's state.
- `Rva001E3E43` is `Locomotor`: same table, with its ctor-side rows (copy ctor 0x001E4641, `operator=` 0x001E3CF4, dtor 0x001E3E43, deleting 0x001E4625) under the address name. It needs folding. `LocomotorCtor.cpp`'s comment also places the dtor at 0x003067D2, but that body installs 0x00C07D2C, another class.

**`getPercentReady` and `MeshGeometryClass`, P54, 2026-11-08.** Same defect class, also bridged, so also latent today.
- `getPercentReady`: Zero Hour's body had a 0.99999 paused-at-ready case and lacked retail's early return on the byte at interface+0x18. Retail's 0x0049355E now carries the name, from `Rva0049355ERatio.cpp`. Its approved unit, `SpecialPowerModule.cpp`, compiles a class with neither that byte nor the reload field at +4, so the row stays until that unit takes the real layout.
- `MeshGeometryClass`: slots 2 and 4 named Zero Hour's bodies, whose signatures differ from retail's (`Load_W3D` returns bool; `Compute_Vertex_Normals` is ret 8). The emitters now declare retail's, the shim's through `BFME_MESHGEOMETRY_RETAIL_SLOTS`. It stays opt-in because `meshmdl.h` still overrides Zero Hour's `Load_W3D`: drop the macro when `MeshModelClass` takes retail's.

**P53: `RenderObjClass` slots 51, 52 and 98, 2026-11-08.** `rendobj.h` declares retail's signatures. Slot 98's name, `queryVisible`, is a placeholder until its vote lands. 51, 52 and 98 differ on none of the 21 `RenderObjClass` tables with a known retail table.
- Live, unlike P54's bridged slots: the bridge refuses 19 of these tables (`target-not-winning-provider`): AABox, Animatable3DObj, Box, Camera, CompositeRenderObj, Line3D, Mesh, Null3DObj, OBBox, ParticleBuffer, ParticleEmitter, RenderObj, Rva000E3B41, Rva001684D6, SegmentedLine, StreakLine, TerrainTracks, Water and Light. Of the bridged ones, this touches `??_7HLodClass@@6BRefCountClass@@@`, whose retirement it makes safe.
- `hlod.h` sits beside the reference `animobj.h`, so a quoted include finds that copy before any `/I`. The seven HLod units include the `bfmeanimobj` shim first and its guard does the rest. A unit that reaches `animobj.h` through `hlod.h` without it fails C2555.
- Not covered: `DistLODClass` compiles the old slots through the `sweep` copy of `rendobj.h`. Other copies of `rendobj.h` (`bfmerendobj`, `bfmestreak`, `bfmesegline`, `bfme2_treebuffer`) still spell the old slots too, though no table on this list compiles through them. `Rva00166DE0`, `Rva007C454` and `W3DStatusCircle` were not read back: the bridge knows no retail table for them.
- Other slots still differ on some of these classes (`MeshClass` 19, `Rva001684D6` 9, `HLodClass` 8, `Animatable3DObjClass` 7, others fewer). Not read individually: they are not this defect and may be the next one.

**P68: `MeshClass`'s table, 2026-11-08.** Refused by the bridge, so live: 18 slots ran `RenderObjClass`'s defaults. Read back whole against 0x00BD35A8: 1 of 129 differs, slot 0, the known `delete this` difference.
- Target facts on the names. Slot 61 (0x0014B5E0) passes its argument to 0x0014A3F0, which reads only a center (+4) and extent (+0x10) from it, so it takes an AABox test. Slots 124 (0x0014B800), 125 (0x0014B8C0) and 126 (0x0014C470) replace a texture pair through the model and recolor materials, with the strings `HOUSECOLOR`, `HouseColorEnable` and `HouseColorTexture`. Slots 4 and 5 return this, and retail gives no name.
- Donor names still in `rendobj.h` for those slots: `Intersect_OBBox`, `Create_Decal`, `Delete_Decal`, `Add_Dependencies_To_List`. `BFME_RENDOBJ_MESH_SLOTS` takes retail's spelling in one unit. It retires when the rows that carry the donor names are renamed, through the naming route: `?Intersect_OBBox@HLodClass@@`, `?Intersect_OBBox@CompositeRenderObjClass@@`, `?Create_Decal@HLodClass@@`, `?Delete_Decal@HLodClass@@`, `?rva0019BA70@HLodClass@@`. They forward the same arguments, so this is naming, not behaviour.
- The list of overrides in `MeshClassLifetime.cpp` retires when a canonical `MeshClass` header is registered and adopted: none exists today, and `mesh.cpp` still compiles Zero Hour's layout, where the model's sort byte is 4 too high.
- A Zero Hour body can be the only emitter of a row. `mesh.cpp`'s `MeshClass::Set_Sort_Level` emitted the inline at 0x006BD4E0, and the class name that row carried was disproved by retail: +0x20 against the class's +0x1C. Likewise `Get_Vertex_Shade_Index_Array` under P54. A red `symbol not found` after removing a hatch means this: read the row before restoring anything.

**P69: `Locomotor` is one class, 2026-11-09.** Clears the "Not fixed" slot 3 entry above. `Rva001E3E43`'s rows now read `Locomotor` through `rename.py --identity --basis retail` on a reviewed family entry, and `?xfer@Locomotor@@` at 0x00341E2D is retracted: `?xfer@AIGoingIdleState@@` keeps that address. Read back whole against 0x00BDE888 from `Locomotor.cpp` and `LocomotorCtor.cpp`: slots 1, 2 and 3 agree; slot 0 spells `??_E`, which in both objects is a weak external defaulting to the rowed `??_G`, so it is the same body unless something else defines `??_E` at link. The whole image's resolution was not read. `link_check`: 74 of 74, on `LocomotorClass.h`'s dependents and the providers. Latent, since the table is bridged: nothing has exercised save/load on it, and it goes live when `??_7Locomotor@@6B@` retires.
- `Locomotor.cpp`'s `loadPostProcess` had no row; retail folds slot 1 into the shared empty body 0x000B3FD0, so it now has an ICF row there and its `present-unmatched` marker is gone.
- Still open: `??0Rva001E3E43Element@@` is a separate placeholder, 0x002BEDBE's `getLegalSurfaces` name is doubtful (P69's packet: 0 direct callers, 0 words hold its address, owner unknown), and `Rva001E3E43Xfer.cpp` keeps its path until consolidation moves it.
- For a tools seat: the respell's post-check asks each row for a reference into retail `.text`. Three of this family's six rows have none (two bodies that bind nothing, and a destructor whose references are data), so each needed an exception by address. For a family with table facts, that may be the wrong question.

**`Rva001684D6`'s table, 2026-11-08.** The line-strip render object behind `W3DStreakDraw`; same defect as P68, also refused by the bridge. Read back whole against 0x00BD41C8 from both installers: 1 of 129 differs, slot 0. The class stays address-named: `Rva001684D6Ctor.cpp` records a WB lead to `SimpleStreakLineClass`, which goes through the naming route.

**P80: `ParticleEmitterDefClass`'s table, 2026-11-09.** 20 slots of 0x00BD74E8 compiled Zero Hour's `WW3DErrorType` bodies where retail's rowed bodies return `bool`. One `part_ldr.h` at BFME 2's path replaces three shims, and `part_ldr.cpp` gives up those 20 bodies, none of them rowed. Read back by slot bytes from both emitters: 0 of 79 differ. Bridged, so latent; no reach through these slots has been read.
- Compare tables by `slot_bytes`, not by names. A name comparison reported 24 slots here and 102 on `Rva001684D6`, because a slot naming a base method is correct when its body is byte-equal to retail's folded one. Slots 15 and 42 are that case and still want a naming pass: `Set_Burst_Size` and `Set_Subdivision_Level` sit on byte-equal twins at 0x00262FEB and 0x00314119.
- Four units need `#include "./part_ldr.h"`. The plain spelling read the reference copy in those four, though the include is direct and the sibling exists; unexplained. Read a unit's `.deps.json` after moving a header: the build stays green either way, since each row's bytes are still exact, and only the table shows it.
- `ParticleEmitterLoaderClass` is not in retail as far as read (the ctor's one direct caller is `Build_Definition`) and nothing of ours registers it, so its body stays an unreachable hatch.

**P54: `CompositeRenderObjClass`'s decal slots, 2026-11-09.** Slots 124 and 125 of 0x00BD6F30 and 0x00BD6D10 are `RenderObjClass`'s empty bodies in retail, so the Zero Hour overrides and their two `present-unmatched` bodies are gone, and `composite.h` sits at BFME 2's path. Read back: both slots equal retail on both tables.
- Three units read that header: `composite.cpp`, `animobj.cpp` and `distlod.cpp`. The other 18 includers still read a reference copy (10 `game/`, 8 Zero Hour) and emit no reference to the removed symbols. `distlod.cpp` has to include it before `distlod.h`, whose quoted include finds the reference copy beside it.
- Still differ: Composite slot 11, and Animatable slots 6, 11, 53 and 59. Slots 11, 53 and 59 are rowed overrides (0x001A5F00 `Get_Num_Verts`, 0x001A4E70, 0x001A5460) whose names and, at 59, signature do not match the base slots `_bfme_ro_v9`, `_v50` and `_v56`, so the tables compile the base defaults. Slot 6 has no row at 0x0015E600.

**`Rva003F9FE6` base slot 0 (`0x00C37898` / RVA `0x00837898` and `0x00C3789C` / RVA `0x0083789C`), 2026-11-09.** Respelled `0x0056B7A0` via `rename.py function --rva 0x0056B7A0 --virtual` from non-virtual `?rva0056B7A0@Rva003F9FE6@@QAEEH@Z` to virtual `?rva0056B7A0@Rva003F9FE6@@UAEEH@Z` across 5 files (`Rva0056B613Forward.cpp`, `Rva003F9FE6CopyCtor.cpp`, `Rva003F9FE6Dtor.cpp`, `Rva00402F28ItemDtor.cpp`, `Rva0056B7E4Ctor.cpp`, removing `Rva0056B7E4`'s synthetic `??_ERva0056B7E4@@UAEPAXI@Z` slot 0 into `reverse/deleted_rows.csv`). Verified 15/15 matched across the 5 edited units plus 41/41 matched + 1 data row across the 7 cohort siblings, `eh_verify.py` exact, `class_gate.py` / `data_check.py` / `hatch_counters.py` / `find_declared_unmatched.py` clean, `link_check` 12/12 (`2,377 -> 2,377 B`, index `001bd86fc0`), and bounded `vtable_bridge.plan()` simulation over the 12 cohort objects in both `CopyCtor_first` and `B7E4Ctor_first` link orders: all three `0x00837898` tables (`??_7Rva003F9FE6@@6B@`, `??_7Rva00402C0F@@6B@`, `??_7Rva0056B7E4@@6B@`) land in `correct` (0 mismatches) in both orders. `??_7Rva003FA118@@6B@` (`0x0083789C`, 1 slot) now carries `?rva0056B7A0@Rva003F9FE6@@UAEEH@Z` at slot 0 instead of `__purecall` and remains bridged until `0x0056B613` (`?rva0056B613@Rva0056B613@@QAEXH@Z`) is respelled from `void` to `unsigned char` (`ret 4` leaves `al` set) and overrides `rva0056B7A0` on `Rva003FA118 : public Rva003F9FE6`.
