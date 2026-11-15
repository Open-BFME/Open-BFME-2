### LINK-681: vftable COMDAT copies differ between the private views of one class

Status: Open; eight families repaired or equalized, the rest are leads. Updated: 2026-11-15; inspected revision: `bb0460844a`.
Evidence / affected units: census 2026-11-15 08:36 (`331df3e3ff`) holds 24 units out on a `??_7` name
that "differs from the first copy in link order (no retail address)". Each is a class whose views
declare different virtual lists, so the units emit different tables. One cause is measured: a
LINK-675 slot declaration rewrites the view that installs a table and leaves the class's other views.
`AptShapeContainer.cpp` (3,449 B) left the census this way at 2026-11-14 21:11 (`071e9ff88d`):
`f5d27a753c` gave `Rva00782CB0` its five slots in `Rva00785140HandleDestructor.cpp`, whose
`Rva00785140Handle` derives from it, while `AptShapeContainer.cpp` kept a base-less one-slot handle.
Completed (`Rva00785140Handle`, retail table VA 0x00BC940C, five slots): both views now derive the
handle from `Rva00782CB0` and declare retail's own list, read off the table: the deleting destructor
(0x000A9ECD), folded 0x000910FB (returns 1), the base's folded 0x000D43D0, folded 0x0047A6A9 (returns
this) and folded 0x005C4AD1 (address of +4). The three overrides are inline and rowed under the
class's names through `add_match.py --icf-owner` (LINK-675's rule). The base's pure slot04 returns
`int` in both views so the override can return 1. `AptShapeContainer.cpp` instantiates the handle, so
its base view needs the base constructor: retail's 27-byte handle constructor expands it inline, and
its one out-of-line body is rowed at 0x000A8EB9 in the destructor unit as an ordinary definition. A
plain inline or implicit constructor made the container unit emit a second definition (preview:
duplicate `??0Rva00782CB0@@QAE@XZ` in both units), so that view declares it
`__declspec(dllimport) __forceinline`: expanded, not emitted. `./build.sh` of both units: 65/65
functions exact. Both objects emit the same table (digest baaaf95952ba) whose five slots are retail's.
Preview against index `bb93a2a56e`: `AptShapeContainer.cpp` LINKS 0 -> 3,449,
`Rva00785140HandleDestructor.cpp` keeps 106; no other census object touches a changed name.
Remaining / next check (the other 23 units, cause not yet read for each; compare against retail's
table before either view is taken as the model): `AptValue.cpp` (`Rva006D6470Owner`, 2,714 B, also its
constructor), `LoadScreen.cpp` (`Rva0035615D`, 1,046 B), `InheritUpgradeCreate.cpp` (525 B),
`EvacuateDamage.cpp` (452 B), `BoneFXDamage.cpp` (433 B), `MonitorConditionUpdate.cpp` (334 B),
`StructureToppleUpdateModuleDataCtor.cpp` (266 B), `SpecialPowerModuleDtor_Unresolved.cpp` (222 B),
`Rva004FB130Dtor.cpp` (222 B), `Rva0052634FPermuted.cpp` (215 B),
`DynamicPortalBehaviourModuleDataDtor.cpp` (172 B), `Rva003560EDDtor.cpp` (140 B),
`ThreatFinderUpdateDtor.cpp` (125 B), `SingleBaseCtors.cpp` (114 B), `Rva005C96EBFinish.cpp` (114 B),
`DebugDestructorThunk.cpp` (99 B), `Rva004E5610Ctor.cpp` (85 B),
`AutoDepositUpdateModuleDataCtor.cpp` (84 B), `FunctorRefInvoke005D388B.cpp` (61 B),
`Rva001E7087Ctor.cpp` (53 B), `Rva005FA393Dtor.cpp` (40 B), `Rva000AAD5CCtor.cpp` (39 B),
`DamageModuleDeletingDtors.cpp` (28 B). The base constructor's approved unit is
`AptDisplayStringBase.cpp`; the data ledger names retail's base table both `??_7Rva00782CB0@@6B@` and
`??_7Rva000AADC1Base@@6B@`, so those two classes are one and still await a class fold.
Read so far, not repaired (2026-11-15, object tables at index `bb93a2a56e`):
- `LoadScreen.cpp`, `Rva003560EDDtor.cpp`: **equalized 2026-11-15 (base `1de491bcfb`), not yet retail's
  list.** Four units emitted `??_7Rva003560ED@@6B@` or `??_7Rva0035615D@@6B@`: `LoadScreen.cpp` with two
  slots (its `Rva00355D66` derives from the canonical `ProgressIndicator`, whose slot 1 is pure), the two
  destructor units and `OpaqueScalarDeletingDtorsB06.cpp` with one. The destructor units' base view now
  derives from `ProgressIndicator` too (retail's base constructor 0x00355D4E calls 0x00355C60), and B06's
  tag emitter of `Rva0035615D` is dropped: its `??_G` row went home to `Rva003561BEDtor.cpp` earlier
  (same repair as `51a544eb33`). 50/50 functions exact over the four units; both names have one digest
  each (3077e33acacd, a26ab0a9d0f9); preview `LoadScreen.cpp` LINKS 0 -> 1,046, `Rva003560EDDtor.cpp`
  0 -> 140, the other two keep linking, no other object touches a changed name.
  Still open, retail's six slots: 0x00814EA4 is destructor, 0x00355DF4, 0x00356724, 0x00355DDD,
  0x00355E20, folded 0x0050B5C6 (`mov al,1`); 0x00814EBC is destructor, 0x00355DF4, 0x00356889,
  0x00355E85, 0x00355E20, 0x00355E4C. All are rowed, but slot 1 overrides `ProgressIndicator::slot1(int)`
  and is rowed as `Rva003560ED::rva00355DF4`; slots 2 to 4 belong to the base (`Rva00355D66`, table
  0x00814E5C: `LoadScreen::update` 0x00355FF9, three pure, 0x0050B5C6) under one name per subclass; and
  0x00355DF4 and 0x00355E20 are shared by both subclasses (an ICF fold of two 44-byte bodies). The list
  therefore needs function renames across the family and the class folds `LoadScreen` = `Rva00355D66`,
  `ShellGameLoadScreen` = `Rva00355DC5`, `MapTransferLoadScreen` = `Rva00355F3E`, not a view edit.
- `AptValue.cpp`: its `RvaAptValueBase` has no `AddRef`/`Release`, so its `Rva006D6470Owner` table has
  one slot where the six other emitters have `AptValue::AddRef`, `AptValue::Release` and the destructor.
  Its `??0Rva006D6470Owner@@QAE@HH@Z` copy has retail's 43 bytes (0x006D6410) and differs from the five
  other copies only in the callee's name: it calls `??0Rva006D6360Base@@QAE@HH@Z` where they call the
  rowed `??0Rva006D6360@@QAE@HH@Z`. Both blockers are one stale spelling of the chain
  `AptValue` / `BfmeAptValue006DCD20` / `Rva006D6360` as `RvaAptValueBase` / `Rva006D6360Base`. The
  unit cannot simply adopt the real names: it already defines `AptValue` (from `AptScriptFunction.h`)
  and a non-polymorphic accessor view named `BfmeAptValue006DCD20`, and its two-base `Rva006DBits`
  model is what gives the six rowed subclass constructors retail's memory-form mask. Class-fold work.
- `StructureToppleUpdateModuleDataCtor.cpp`, `AutoDepositUpdateModuleDataCtor.cpp`: the losing units
  hold the 31-slot BFME 2 `ModuleData` list; the first copy is `ModuleFactory.cpp`'s 8-slot Zero Hour
  list (`crc`, `xfer`, `loadPostProcess`, destructor, ...). Blocked, the wall LINK-625 already records:
  `ModuleFactory.cpp` emits those two tables through `EmitVtableTag` constructors only to keep the rowed
  `??_G` bodies 0x0025528B and 0x00257B5E, which `tu_map.csv` leaves displaced (no approved unit), so
  they cannot move to the constructor units that already emit them beside the right table. The other
  way, giving `ModuleFactory.cpp` the 31-slot list, means replacing Zero Hour's `ModuleData` under the
  roughly 150 Zero Hour module headers the unit includes. Prerequisite: a TU approval for the two `??_G`
  rows, or `ModuleFactory.cpp` on the canonical `ModuleData.h`.
- `DynamicPortalBehaviourModuleDataDtor.cpp`: the constructor unit emits the 31-slot list; the
  destructor unit's private `Rva00253487Base` declares only a destructor, a shape its notes say the
  destructor's bytes depend on.
Completed 2026-11-15 (base `c64c20ff06`), module classes whose destructor sits in another unit than the
class's other rows. In both, the module's own unit already emitted retail's slots and the destructor
unit's view lacked the class's overrides, so its copy fell back to the base's names:
- `ThreatFinderUpdate` (retail 0x008360CC, 13 slots): `ThreatFinderUpdateDtor.cpp` now declares the
  protected `loadPostProcess()` override (slot 1, rowed in `ThreatFinderUpdate.cpp` at the folded
  0x00497805). Preview: `ThreatFinderUpdateDtor.cpp` LINKS 0 -> 125.
- `InheritUpgradeCreate` (retail 0x008596E4 and 0x008596F4): `Rva004B8CDEDerived.cpp`, which rows the
  destructor 0x004B9458, now declares `getModuleNameKey`, inline `onCreate`, `onBuildComplete`, `slot02`
  and protected `xfer` as `InheritUpgradeCreate.cpp` does. Preview: `InheritUpgradeCreate.cpp` LINKS
  0 -> 525.
15/15 functions exact over the two edited units; both names of each class have one digest; the two other
census objects touching a changed name keep linking.
Completed 2026-11-15 (base `77bf9b3aee`), three constructor units whose view lacked what the unit owning
the class's destructor declares:
- `Rva000AAD5CCtor.cpp` (39 B) and `SingleBaseCtors.cpp` (114 B) began the class with a pure slot;
  retail's slot 0 is the deleting destructor (0x000AB0B8 of table 0x007C9468, 0x00211121 of 0x007E5118),
  rowed in `OpaqueScalarDeletingDtorsB08.cpp` and `B04.cpp`. The views now declare the rowed virtual
  destructors instead. One slot of retail's five and four: the rest still needs LINK-675's rule.
- `Rva001E7087Ctor.cpp` (53 B) had a base-less class; `Locomotor.cpp` derives it from `Snapshot`, whose
  three pure slots follow the destructor. The constructor unit now derives from the same shim under
  `BFME_SNAPSHOT_CONSTRUCTOR_ONLY`, and its 53-byte constructor still stores one vptr. Retail's table
  0x007DE950 holds `LocomotorSet::DoXfer` in slot 3, so the class is `LocomotorSet` under a second name.
9/9 functions exact over the three units; each table has one digest in both emitters; preview all three
LINK and B04, B08 and `Locomotor.cpp` keep linking.
Completed 2026-11-15 (base `bb0460844a`): `Rva0052634F_Base` (retail table 0x00867E3C, five slots, no
deleting destructor). `GapBodiesGE12.cpp`, which rows the constructor 0x00524F61, declared a virtual
destructor, so its one-slot copy named `??_E` and came first in link order;
`Rva0052634FPermuted.cpp` rows the non-virtual destructor 0x00524F5A and slot 0's folded 0x0047A69C
as `v00`. GE12's view now matches it. 9/9 functions exact; preview `Rva0052634FPermuted.cpp` LINKS
0 -> 215, GE12 and the one other object touching a changed name keep linking.
Slot comparison of each remaining copy against retail's table (2026-11-15), still open:
- `MonitorConditionUpdate.cpp` (334 B) and `BoneFXDamage.cpp` (433 B): the module unit's private class
  is right (`getModuleNameKey` and, for BoneFXDamage, `onDamage`, `onHealing`,
  `onBodyDamageStateChange`, `onObjectCreated`, `loadPostProcess`, `GetSnapshotName`, `xfer`); the first
  copy comes from a unit on the generated canonical header (`Common/MonitorConditionUpdate.h`,
  `Module/BoneFXDamageClass.h`), which declares none of them. The repair is the class contract
  (`reverse/class_contracts/<Class>.json`) and a regenerated header, then the module unit adopting it.
- `EvacuateDamage.cpp` (480 B): two things differ. Its `DamageModule` is a private view (slots 1 and 2
  pure, ten slots) where `EvacuateDamageCtorModuleFactoryBody.cpp` uses the canonical
  `DamageModuleClass.h`; and the constructor unit declares no destructor, so its table names the public
  `??_EEvacuateDamage@@UAEPAXI@Z` where retail's row is the protected `??_GEvacuateDamage@@MAEPAXI@Z`.
- Small tables, retail's list beside each copy: `Rva005FA393Dtor.cpp` declares a virtual destructor
  where retail's `BattlePromptMovieClip` table (0x008078DC) is five pure slots, as the shared
  `GameClient/BattlePromptMovieClip.h` has it, so its row `??1BattlePromptMovieClip@StrategicHUD@@UAE@XZ`
  (0x005FA393) is a non-virtual destructor under a virtual name and needs a rename first;
  `Rva005C96EBFinish.cpp` (114 B) derives the class from a private `BfmeAptScreenBase` whose first
  virtual is `slot0`, where retail's slot 0 (table 0x00874B70, eleven slots) is the deleting destructor
  0x005C9753 that B14 and `Rva005C9659Dtors.cpp` name. Tried 2026-11-15 and reverted: a virtual
  destructor in that base keeps the unit's 2/2 rows exact and equalizes `??_7Rva005C96EB@@6B@`, but the
  base is shared, and the unit then loses on `??_7BfmeAptScreenBase@@6B@` (first copy
  `BfmeAptScreenBaseConstructor.cpp`, also `slot0`) and on `??1BfmeAptScreenBase@@UAE@XZ`
  (`BfmeAptGameWindowConstructor.cpp` emits a 5-byte jump under that name). The three units' views of
  the base have to change together;
  `FunctorRefInvoke005D388B.cpp` is the right copy (`what@exception` in slot 1, retail 0x006299B8) and
  the eight one-slot copies are wrong; `Rva004E5610` is `ResourceEntryCollector` under a second name
  (retail's one slot is `ResourceEntryCollector::rva004E55B9`) and neither copy has it.
Plain forms of the base constructor in `AptShapeContainer.cpp`'s view, retested 2026-11-15 at
`1de491bcfb` (each built with `./build.sh`, then the object's symbols read): declared without a body,
the 27-byte handle constructor calls it out of line and `??0Rva00785140Handle@@QAE@ABVAssetReference@@@Z`
fails its byte match; `Rva00782CB0() {}` in the class, an implicit constructor and a plain
`__forceinline` one all keep the 27 bytes but emit a 9-byte `??0Rva00782CB0@@QAE@XZ` (MSVC 7.1 emits a
used inline constructor even when every call is expanded), a second definition beside the ordinary one
`Rva00785140HandleDestructor.cpp` rows at 0x000A8EB9. So the `dllimport __forceinline` form stays. It
can go when the base's three rows (0x000A8EB9, 0x000A8EC2, 0x000A8EC9; approved unit
`AptDisplayStringBase.cpp`) are defined inline in a unit that itself constructs a subclass: retail's
copies are header inlines that first unit emitted, and then every view can use the in-class form.
Clearance: `Rva00785140Handle`, the two load-screen tables, `ThreatFinderUpdate`, `InheritUpgradeCreate`,
`Rva000AAD5C`, `Rva00210EF1`, `Rva001E7087` and `Rva0052634F_Base`; preview scope the units named for each.
Census confirmation: awaiting.
