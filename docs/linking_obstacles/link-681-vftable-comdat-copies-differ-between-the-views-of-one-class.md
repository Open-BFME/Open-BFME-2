### LINK-681: vftable COMDAT copies differ between the private views of one class

Status: Open; `Rva00785140Handle` repaired, the rest are leads. Updated: 2026-11-15; inspected revision: `cb43692212`.
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
- `LoadScreen.cpp`, `Rva003560EDDtor.cpp`: retail's `Rva003560ED` (0x00814EA4) and `Rva0035615D`
  (0x00814EBC) tables have six slots each and their virtuals are already rowed across
  `Rva003560EDEngineRefresh.cpp`, `ProgressIndicator.cpp` and the two destructor units; the views emit
  one or two slots. Seven units declare these classes (`GameLogicInit.cpp` and
  `OpaqueScalarDeletingDtorsB06.cpp` among them) and must change together.
- `AptValue.cpp`: its `RvaAptValueBase` has no `AddRef`/`Release`, so its `Rva006D6470Owner` table has
  one slot where the six other emitters have `AptValue::AddRef`, `AptValue::Release` and the destructor;
  its force-inlined two-base constructor model also emits a `??0Rva006D6470Owner@@QAE@HH@Z` copy that
  differs from the kept one.
- `StructureToppleUpdateModuleDataCtor.cpp`, `AutoDepositUpdateModuleDataCtor.cpp`: the losing units
  hold the 31-slot BFME 2 `ModuleData` list; the first copy is `ModuleFactory.cpp`'s 8-slot Zero Hour
  list (`crc`, `xfer`, `loadPostProcess`, destructor, ...). The repair belongs in `ModuleFactory.cpp`.
- `DynamicPortalBehaviourModuleDataDtor.cpp`: the constructor unit emits the 31-slot list; the
  destructor unit's private `Rva00253487Base` declares only a destructor, a shape its notes say the
  destructor's bytes depend on.
Clearance: `Rva00785140Handle` only, preview scope the two units above.
Census confirmation: awaiting.
