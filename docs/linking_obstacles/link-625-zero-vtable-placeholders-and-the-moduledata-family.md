### LINK-625: Zero vtable placeholders, and the ModuleData family's vptrs

Status: Open (partly repaired). Updated: 2026-11-07 (seat halilkkaya-lk49); base `f0cce4d912f`, census index
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

**Repaired: the ModuleData family.** Each constructor now derives from the canonical header and lets the compiler install
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

Taint's hand-built `vtbl_00C5D608` array (LINK-623 leftover) is gone; the CommandPoints unwind no longer goes through an
`/alternatename` to operator delete (its hatch line over-grants by one until `hatch_counters.py --update`). Sweep after:
267 -> 259 placeholders, none new.

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
- **MessageStream, boot path:** `??0MessageStream@@QAE@XZ` (0x0030F697, MessageStreamListCtors.cpp) stores
  `s_messageStreamVtable`, a zero int; the factory 0x00225F12 creates TheMessageStream with it, so its first virtual call
  (init/update from the engine loop) jumps through zero. The kept `??_7MessageStream@@6B@` (MessageStreamDtor.cpp) is a
  10-slot Zero Hour view; retail 0x00C09890 follows BFME 2's SubsystemInterface.h (loadIniFilesFromLegend in slot 2,
  reset/update at 9/10). Canonical MessageStream.h already derives from that SubsystemInterface, but the unit's bodies use
  a private GameMessage (`deleteInstance(int)`) and LINK-557 walls the destructor unit; header_queue rows 1251/2202/3270.
  Highest-value next item in this family.
- ToggleMountedSpecialAbilityUpdateModuleData (`s_vtableAnchor`): retail stores the vptr second; a compiler store sinks
  fourth (probe-proven in the unit's comment), so a class view alone does not match.
- BoredUpdate (the module, `s_dummy0C`/`s_dummy10` at +0x0C/+0x10): UpdateModule.h would give it retail's three tables
  (HeightDieUpdate recipe, LINK-514), but class:BoredUpdate is held (Burachi-3D, ArrowStormUpdate scope); not attempted.

Remaining / next check: MessageStream first; then the 69 dummy-vptr units LINK-514 does not list (DamageField,
GloriousCharge, Rampage, Enraged, StealthDetector, the special powers; mostly UpdateModule.h or SpecialPowerModule views,
LINK-514's recipe) and the 32 extern placeholders. Re-run the sweep (`lk45_sweep.py` over a scratch `data_ledger.py --out`)
before and after; every repaired constructor must leave the inventory with its table's copies identical.

Clearance: none claimed (no real link or census run since); the eight installers now name their tables, so the
next real link's image report and bridge queue are the check.
Census confirmation: none claimed.
