### LINK-694: UpdateModule stand-in bases block header adoption in the bridged-table emitters

Status: Open (partly repaired). Updated: 2026-11-20; inspected revision: `5b1cc1a3150` plus the seat's eight
commits below (seat halilkkaya-um, not yet on master).

**Question.** Two vtable-bridge families wait on the real UpdateModule base: the 47-slot
BehaviorModuleInterface tables whose canonical copy is UpdateModule's 0x00BEFF90 (108 bridged tables,
4,103 mismatching slots) and the three-slot UpdateModuleInterface tables of UpdateModule's 0x00BFBCE4 shape
(102). The header queue lists UpdateModule / BehaviorModule adoption as FAIL in their emitters. Why?

**Census** (bridge plan over build/match, base = HEAD objects: 3,084 bridged tables, 33,299 mismatching
source slots; `header_adopt_lane.py adopt --class UpdateModule --header
Code/GameEngine/Include/GameLogic/Module/UpdateModule.h` dry run over the 75 units emitting a table of
either family, plus each unit's compiled UpdateModule/BehaviorModule header, its table base names and the
claims). First blocker per unit (units / family tables / mismatching slots):

| First blocker | Units | Tables | Slots |
|---|---|---|---|
| stand-in bases: UpdateModule or its intermediate modelled as a padded root plus one-slot sibling stand-ins (`MiBase1`/`*_M1` at +0x0C, `*_B2` at +0x10, `*_E1` at +0x20) | 40 | 149 | 3,822 |
| claimed by another seat | 3 | 6 | 147 |
| already on the canonical header; residual per-class override slots | 21 | 40 | 63 |
| ZH shim copy `reference/shims/update_modules_bfme2` (34-slot interface) | 4 | 4 | 60 |
| compile (C2511, C2027), bytes, field renames | 4 | 8 | 198 |
| adoptable as is (Rva0058A0F4Dtor.cpp, WorkerAIUpdateCtor.cpp) | 2 | 2 | 49 |

Stand-in units by the canonical base they need (units / tables / slots): UpdateModule 4/51/1,338,
OpenContain 14/28/698, AIUpdateInterface 4/18/444, SpecialAbilityUpdate 3/16/354, DockUpdate 3/10/250,
ObjectHelper 2/7/241, SpecialPowerModule 5/10/207, SlowDeathBehavior 2/3/141, FoundationAIUpdate,
FireWeaponUpdate and BezierProjectileBehavior 1 each.

**Cause.** The lane's swap replaces a private class of the requested name. These units either have no
private `UpdateModule` (`no private view found`: the root is `Rva0026E836_Root`, `Rva00451F45_Root`,
`B0`, ...) or one that is only the padded 12-byte root (`UpdateModule::m_pad04: unused byte storage has no
complete unchanged layout proof`); swapping it alone would keep the stand-ins as extra bases and move every
vptr. The canonical headers are not the cause: UpdateModule.h / BehaviorModule.h already give retail's
13 / 47 / 3 slots, and the BehaviorModule getters, UpdateModule's own slots and the Module defaults are all
rowed.

**Repair (by hand per family; the lane has no route).** Derive each class from the canonical chain
(UpdateModule.h, or the intermediate's view: ObjectHelper.h, SpecialAbilityUpdate.h, the DockUpdate of
`DockUpdate/SupplyWarehouseDockUpdateNative.h`) and declare only overrides a row spells under the class's
own name. Where another unit already emits the class's canonical tables, declare exactly that unit's
override list (tabdump: identical slot symbols, so the COMDAT copies are one copy). Units that store a
stand-in table by name (`extern "C" __identifier("??_7X@@6BX_B2@@@")`) rebind to the compiler's names at
the same native addresses (bytes unchanged; precedent aa7acf764db); a unit that declares the class itself
cannot extern its own table name (C2373) and drops the explicit stores instead (BannerCarrierUpdate.cpp:
the compiler's three stores give the retail bytes). Before removing a stand-in, check that it defines
nothing another object references.

**Done** (each commit: build.sh exact, bridge plan judged against the previous snapshot with nothing
newly bridged at another table, no correct table lost, refusals identical, no new unresolved or multiply
defined name; inline COMDATs byte- and relocation-identical to other objects' copies; link_check LINKS the
units and their consumers):

| Commit subject (abridged) | Bridged | Correct | Mismatching slots |
|---|---|---|---|
| four ObjectHelper destructor views on ObjectHelper.h (Rva004DF7C2Derived.cpp) | 3084 -> 3072 | 2420 -> 2420 | 33299 -> 33051 |
| six SpecialAbilityUpdate destructor views on SpecialAbilityUpdate.h (+6 ctor rebinds) | 3072 -> 3064 | 2420 -> 2428 | 33051 -> 32618 |
| ObjectSMCHelper destructor view on ObjectHelper.h | 3064 -> 3061 | 2428 -> 2428 | 32618 -> 32557 |
| MonsterDockUpdate destructor view on the DockUpdate view (+2 ctor rebinds) | 3061 -> 3059 | 2428 -> 2430 | 32557 -> 32480 |
| RadiusDecalUpdate on UpdateModule.h (its view header) | 3059 -> 3057 | 2430 -> 2432 | 32480 -> 32423 |
| 24 Rva0024A797Derived.cpp destructor views on UpdateModule.h (+StealthUpdateCtor.cpp view, 9 ctor rebinds, BannerCarrierUpdate.cpp stores) | 3057 -> 3023 | 2432 -> 2453 | 32423 -> 31031 |
| WeaponFireSpecialAbilityUpdate on SpecialAbilityUpdate.h (private copy over WFS_* stand-ins) | 3023 -> 3020 | 2453 -> 2456 | 31031 -> 30954 |
| LevelGrantSpecialPower constructor view on SpecialAbilityUpdate.h | 3020 -> 3017 | 2456 -> 2459 | 30954 -> 30877 |

Total: bridged 3,084 -> 3,017, correct 2,420 -> 2,459, mismatching source slots 33,299 -> 30,877; names
undefined with no definer 3,155 -> 3,127. Dead hatches left in the sources (register slack for
`hatch_counters.py --update`): 20 /alternatename, 6 present_unmatched.

**Remaining / next check.**
- Header queue: UpdateModule and UpdateModuleInterface on Rva0024A797Derived.cpp, UpdateModule and MiBase1
  on StealthUpdateCtor.cpp now hold no private view; `header_adopt_lane.py accept` waits on the
  `file:reverse/header_queue.tsv` claim another seat holds.
- DynamicShroudClearingRangeUpdateView.h: the same re-base is refused by the bridge judge (one new
  unresolved name). Its private `ModuleInterface` is the only object defining
  `?moduleInterfaceAnchor@ModuleInterface@@UAEXXZ`, which six other objects' tables still reference
  (seven before the LevelGrantSpecialPower commit) (the
  registered ModuleInterface.h declares it out of line). Prerequisite: an owner for that anchor.
- Rva0058A0F4Derived.cpp (DockUpdate, 3 classes): same route as MonsterDockUpdate, held by another seat's
  class-identity work; RepairDockUpdateBehaviorCtor.cpp stores its tables by name.
- AIUpdateInterface family (Rva0026E836Derived.cpp, 6 classes with 153/154 primaries; Worker,
  DeployStyle and HordeWorker destructors): the peer constructor units carry private AIUpdateInterface
  views of their own and the canonical primaries are themselves 145-146/154 wrong. AIUpdate.h adoption
  first.
- OpenContain (14 contain units, flat `B0`..`B8` bases), SlowDeathBehavior (no canonical header),
  SpecialPowerModule-family `_S1`/`_S2` stand-ins: each needs its canonical intermediate first.
- The 38 new UpdateModule-chain names that stay bridged differ from retail in per-class overrides only
  (loadPostProcess fold 0x00497805, the name getter, getModuleNameKey, update): class identity work for
  the address-named classes (folds into the real classes need equal virtual lists, which the views now
  share with UpdateModule).

**Automated re-base (seat halilkkaya-rb, 2026-11-20).** `build/rb/rebase.py` (scratch, not a tool under
`tools/`) applies the recipe above from retail facts: for a bridged primary table whose direct base is certain
in the retail hierarchy (`build/rb/hier.py`: destructor and constructor table stores agree, or one source plus
consistent slots) and registered in `reverse/canonical_classes.csv`, it re-bases every view of the class whose
unit emits one of its tables, removes stand-ins and hand table stores, respells stand-in fields as the
canonical class's fields at the same offset, declares overrides rowed under the class's own name (or carried
by a co-emitter's copy), rebinds `__identifier` table stores in other units, and keeps a stand-in only as a
thin `class X : public A` when it spells a base-constructor call the ledger rows under X's name
(`??0Rva0044EF5E` at 0x0044EF5E is SpecialAbilityUpdate's constructor). Each family is verified (layouts,
`./build.sh`, tabdump, COMDAT copies, bridge judge, link_check) and reverted on any failure. Base (objects
refreshed for the touched units): 2,976 bridged / 2,519 correct / 31,078 mismatching slots. Four commits:
three SpecialAbilityUpdate families (ModuleUpdateDtors.cpp's 14 views with their constructor units,
TeleportToCasterSpecialPower in OCLUpdateCtor.cpp, DominateEnemySpecialPower) and Rva000A882D on Rva0040EDB in
RvaSmallVtableCtors.cpp: bridged 2,976 -> 2,976, correct 2,519 -> 2,561, mismatching slots 31,078 -> 30,803,
no table newly bridged, link_check unchanged.

Of 2,976 bridged names, 1,088 have a certain chain, 761 a canonical ancestor on it, 129 a canonical direct
base with a stand-in or no base in the emitting unit (94 families). Refusals by cause (latest per family):
emitter-stub views smaller than the ancestor (24); stand-in bases ending before or after sizeof(A) (19,
usually a missing intermediate such as CollideModule, W3DModelDraw, OpenContain); own fields below sizeof(A)
(11); byte mismatches (7); generated canonical headers that need prerequisites the unit lacks
(GameMessageTranslator, Xfer, Base: 6); no measured gain (6, the SubsystemInterface subsystems); claims held
elsewhere (2); excluded ancestors (5). Stub views retried with the size check relaxed (no field, no
constructor other than an EmitVtableTag emitter, only destructor rows for the class): none taken; their table
or inline copies differ from the class's other emitters (6), the emitter constructor needs a default
constructor the canonical class lacks (3), or the bytes move (2).
