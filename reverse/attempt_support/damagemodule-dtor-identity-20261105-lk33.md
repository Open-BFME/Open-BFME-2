# ~DamageModule identity and the `??1PB_DeepBase@@UAE@XZ` real-link name (lk33, 2026-11-05)

Handoff for the next seat. Target facts are retail bytes and ledger rows; donor facts are Zero
Hour's; inferences are marked.

## Why the name cannot resolve in one step

`??1PB_DeepBase@@UAE@XZ` is referenced only by EvacuateDamageCtorModuleFactoryBody.cpp. Its private
`DamageModule : PB_DeepBase, PB_Iface1, EvacuateDamageInterface` view has an implicit destructor:

- the constructor's unwind funclet (row 0x0078F58B, retail `jmp 0x004B96CC`) calls the unit's
  `??1DamageModule@@UAE@XZ` COMDAT, which calls `~PB_DeepBase`;
- the implicit `??1EvacuateDamage@@UAE@XZ` (row 0x0002CD7B) inlines `~DamageModule` and calls
  `~PB_DeepBase` directly. That row matches only through the pin `??1PB_DeepBase@@UAE@XZ` ->
  0x0002CCC3. Retail 0x0002CD7B is `~INIMacroTable` (target fact: atexit 0x007B6A6E runs it on
  0x00DDF58C, which `??0INIMacroTable` 0x0002DC3C builds through the dynamic initializer
  0x007ABBB3). The real `~EvacuateDamage` is `??1EvacuateDamage@@MAE@XZ` at 0x004BAEC8.

The unit's wrong `??1DamageModule@@UAE@XZ` COMDAT is the only definer of that name in the tree.
Every unit that starts calling `??1DamageModule@@UAE@XZ` therefore gets link_check's `selected`
blocker, and that couples every step below.

## Measured this pass

1. **DamageModuleCtor.cpp on canonical DamageModuleClass.h (the LINK-514 dummy-vptr fix).** The
   source below is byte-exact on the first build (1/1 rows). The compiler's own order reproduces
   retail's four stores: DamageModuleInterface's implicit constructor at +0x10, then +0, +0x0C and
   +0x10. The scoped DIR32 check is OK. Tables, slot by slot against retail:
   - `??_7DamageModule@@6BObjectModule@@@` vs 0x00C598E4: 10/12 equal. Slot 0 is `??_EDamageModule`
     (retail `??_G` 0x004B973B, the same `??_E` as BoneFXDamage.cpp's canonical table) and slot 5 is
     the unrowed inline `Module::onObjectCreated`. Neither is wrong.
   - `??_7DamageModule@@6BBehaviorModuleInterface@@@` vs 0x00C597F8: 43/47 equal. Slots 1, 9 and 19
     are unrowed inline getters; slot 4 is the unrowed inline `getDamage`. Neither is wrong.
   - `??_7DamageModule@@6B@` (the +0x10 interface table) vs 0x00BE2B78: 3/3 equal.

   **Not landed.** link_check: DamageModuleCtor.cpp LINKS 49 B -> does not link, with
   `selected ??1DamageModule@@UAE@XZ (the definition the link keeps is not retail's)`. The
   emitted `??_EDamageModule` calls `~DamageModule`, and the only definer is the EvacuateDamage
   unit's wrong COMDAT. The change is reverted. Re-apply it in the same change as step 4 below.
   The other 18 checked units (siblings and co-definers) were unchanged.

   ```cpp
   // cl: /O1 /DNDEBUG /MD
   #include "../../../../Include/GameLogic/Module/DamageModuleClass.h"

   // ??0DamageModule@@QAE@PAVThing@@PBVModuleData@@@Z @0x004B9704
   inline DamageModule::DamageModule(Thing *thing, const ModuleData *moduleData) :
   	BehaviorModule(thing, moduleData)
   {
   }
   // (keep the existing bfmeEmitDamageModuleCtor anchor and its present-unmatched marker)
   ```

   It also retires the header-queue row `DamageModule DamageModuleCtor.cpp 0x004B9704`
   (`header_adopt_lane.py accept --class DamageModule ...DamageModuleCtor.cpp`).

2. **rename.py fold relaxation (landed in this seat's tool commit).** `inlined_base_restores` lets
   a destructor family whose stores an inlined base destructor explains take the destructor-only
   route. With step 1 built, `fold_evidence(Rva004B96CC, DamageModule)` proves:
   - the ctor 0x004B9704 installs 0x00C598E4 as its own;
   - the dtor stores 0x00BE2B78 at +0x10, which is the ctor's last store there;
   - the dtor stores BehaviorModule's 0x00BEEA7C/+0 and 0x00BEE9C0/+0x0C, which ??0BehaviorModule
     0x00253330 installs last and which the ctor calls;
   - 0x00C598E4 is named `??_7DamageModule@@6BObjectModule@@@`, from DamageModuleCtor.cpp's DIR32
     binding;
   - `??_G` 0x004B973B is slot 0, and it calls 0x004B96CC.

   The fold is then refused only by: "DamageModule is registered in canonical_classes.csv: the fold
   would turn Rva0049B47CThreeVptrDerived.cpp, Rva004B96CCDerived.cpp, TailJumpWrappers5B.cpp's
   class Rva004B96CC into a private copy".

## Ordered plan

1. **Re-identify row 0x0002CD7B** (identity lane; tu_map: `displaced`, no approved home). It is
   `INIMacroTable`'s destructor:
   - it calls the nocase-set `_Rb_tree` dtor 0x0002CC38 on +0x14, then 0x0002CCC3 on +0;
   - 0x0002CCC3 is byte-identical to the `rts::hash<AsciiString>` hashtable dtor 0x002236B9 except
     for its FuncInfo, so it is a second instantiation.

   INIMacroTable.cpp's view must change to match: `set<AsciiString, less>`, and a hash_map whose
   dtor is 0x002236B9, are both contradicted. Its constructor row's callee names (hash_map ctor
   0x0002DC1D, set ctor 0x000D3A71) bind the current spelling, so check their ICF folds before
   respelling. Until this row leaves EvacuateDamageCtorModuleFactoryBody.cpp, that unit cannot
   stop emitting the implicit `~DamageModule`.
2. **rename.py: registered NEW with prepared units** (tool, tests, Verifier-Change). Today
   `plan_fold` refuses `--prepared` unless `--into` is nested, and it refuses a registered NEW
   whenever a unit declares OLD. Extend the nested path: for a registered NEW, every unit that
   spells OLD (text or object consumer) must come `--prepared`, and none may spell OLD. The
   source edits go through `_batch_source_edits`; class_gate in the commit checks then decides on
   private copies. Draft tests (fixture `make_dtor_tree` plus a canonical_classes.csv row for
   D_NEW):
   - registered D_NEW, D_OLD declared in Dtor.cpp, no `--prepared`: refused with "registered in
     ... private copy" (unchanged);
   - registered D_NEW, `--prepared Code/Game/Dtor.cpp=<file including the canonical header and
     defining D_NEW::~D_NEW()>`: plans, renames the rows and writes the prepared file;
   - registered D_NEW, a second unit spelling D_OLD not prepared: refused, naming that unit;
   - a prepared file that still spells D_OLD: refused ("the fold leaves no ... behind");
   - an unregistered NEW with `--prepared` and not nested: still refused (unchanged).
3. **Atomic change: DamageModule identity.** One commit; every unit byte-exact; link_check over all
   of them and the co-definers.
   - Re-apply step 1's DamageModuleCtor.cpp first, then build it, so that the `??_7` name binds.
   - `rename.py class --fold Rva004B96CC --into DamageModule --prepared ...` for each spelling unit:
     - Rva0049B47CThreeVptrDerived.cpp (the definer). It includes DamageModuleClass.h, supplies
       `inline BehaviorModule::~BehaviorModule() {}` and defines `DamageModule::~DamageModule() {}`.
       That gives retail's +0x10, +0, +0x0C order, then the tail jump to `??1ObjectModule@@UAE@XZ`
       (pinned 0x0049B47C). The `Rva004B96CC_Anchor` new/delete cannot instantiate the abstract
       class, so `??_GDamageModule` must come from the unit's own vftable emission. Check that it
       is `??_G`, not `??_E`: see the slot-0 note above.
     - Rva004B96CCDerived.cpp: the BoneFXDamage, Rva004BAB36 and Rva004BB0CC dtors on the
       canonical base.
     - HordeTransportContainDamageCtor.cpp: its `__identifier("??_7Rva004BB0CC@@6BRva004B96CC@@@")`
       vftable name follows Rva004B96CCDerived.cpp's new table name.
     - TailJumpWrappers5B.cpp: `CallHelpOnDamage::~CallHelpOnDamage`, 0x004BB4D1, `jmp 0x004B96CC`.
     - TransitionDamageFXDtor.cpp and EvacuateDamage.cpp (`typedef Rva004B96CC DamageModule`).
     - The declaration-only leftovers in TailJumpWrappers5B_~Rva002563CE.cpp and
       W3DAptComponentView3D.cpp.

     The pin `??1DamageModule@@UAE@XZ` -> 0x004B96CC is dropped as the row's own name. Access: the
     canonical header and every current reference spell public (`UAE`). Zero Hour's
     `MEMORY_POOL_GLUE_ABC` makes it protected, which is a donor fact and not changed here.
4. **EvacuateDamageCtorModuleFactoryBody.cpp** declares `virtual ~DamageModule();` out of line
   after step 1 has moved row 0x0002CD7B out. The unit then emits no `~DamageModule` and does not
   reference `~PB_DeepBase`. It can then merge into its approved TU, EvacuateDamage.cpp.

Steps 3 and 4 may land in either order once step 1 is done. Step 3 alone leaves the EvacuateDamage
COMDAT beside the new strong definition, and that unit already does not link. Run link_check over
the definer's consumers.

## Same-shape folds the relaxation already plans

`Rva004BB68E -> CollideModule` (retail vftable 0x00C5A130, ctor 0x004BB702 in FireWeaponCollide.cpp)
now passes `fold_evidence`, and CollideModule is not registered. The fold is not landed as a token
rewrite. In Rva0049B47CThreeVptrDerived.cpp the private `CollideModule : PrimaryP,
Rva004BB68E_B2` would emit a 1-slot `??_7CollideModule@@6B@`, its B2 table holding
`?f2@Rva004BB68E_B2@@UAEXXZ` (digest 738c089f32c3). FireWeaponCollide.cpp already emits that name
for the CollideModuleInterface subobject (digest 204e51db8d05), so the two COMDAT copies would
differ. Prepare the definer on FireWeaponCollide.cpp's CollideModule view, as in step 3 above.
Rva0049B47CThreeVptrDerived.cpp's other PrimaryP middles, Rva00484EF4 and Rva00462151, have the same
shape. Find their class from the ctor whose own table holds their `??_G`.
