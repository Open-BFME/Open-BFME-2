# BehaviorModule's Snapshot slots and BoneFXDamage's three real-link names (2026-11-05, seat halilkkaya-lk28)

Real link 42035295927 at `dbde7dbe3b` lists three unresolved names from
`Code/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp`, all referenced by
that unit's unrowed Zero Hour bodies (`BoneFXDamage::crc/xfer/loadPostProcess`, marked
present-unmatched), which its Zero Hour-shaped vtables reference:
`?crc@DamageModule@@MAEXPAVXfer@@@Z`, `?xfer@DamageModule@@MAEXPAVXfer@@@Z` and
`?loadPostProcess@DamageModule@@MAEXXZ`.

## Target facts (retail bytes)

- DamageModule primary table VA 0x00C598E4: slot 1 `0x0058B03E`, slot 2 `0x004B9735`
  (rowed `DamageModule::GetSnapshotName`), slot 3 `0x004CE56D`. No crc slot.
- BoneFXDamage primary table VA 0x00C598B4: slot 1 `0x00497805`, slot 2 `0x004B96FE`
  (rowed `BoneFXDamage::GetSnapshotName`), slot 3 `0x0045CE8C`. No crc slot.
- BehaviorModule primary table VA 0x00BEEA7C: slot 1 `0x000B3FD0` (row
  `?loadPostProcess@BehaviorModule@@MAEXXZ`), slot 2 `0x0024A791`, slot 3 `0x004C9C7D`
  (row `?xfer@BehaviorModule@@QAEXPAVXfer@@@Z`).
- `0x0058B03E` = `e9 -> 0x000B3FD0`. `0x00497805` = `e9 -> 0x0058B03E`.
- `0x004CE56D` = `push esi; mov esi,ecx; Version1 (0x53EE); call 0x004C9C7D`, 27 B;
  its approved TU is `DieModule.cpp` (placement C), so the fold's kept copy is
  DieModule's; DamageModule's is a twin.
- `0x0045CE8C` = the same shape calling `0x004CE56D` (BoneFXDamage::xfer's fold).

## Landed here: `?loadPostProcess@DamageModule@@MAEXXZ` (1 of 3)

ICF twin row at 0x0058B03E, defined in `DamageModule.cpp` (the class's approved TU)
as Zero Hour's `{ BehaviorModule::loadPostProcess(); }`. The base call needs
`BehaviorModule::loadPostProcess` declared, which canonical `BehaviorModule.h` did not.

### Why the declaration is opt-in (`BFME_BEHAVIORMODULE_LOADPOSTPROCESS`)

Declared unconditionally (measured on all 856 ledger sources whose objects include the
canonical header, rebuilt: 856/856 byte-exact), it changes 56 emitted vtables in 48
units, every one the same way: slot 1 goes from `__purecall` to
`?loadPostProcess@BehaviorModule@@MAEXXZ`, and each object gains that undefined name.
No other COMDAT digest or symbol changes. The classes are those whose views declare no
loadPostProcess of their own:

ActiveBody AllowBannerSpawnUpgrade ArmorUpgrade AttributeModifierUpgrade BaseUpgrade
BodyModule CastleUpgrade ClearanceTestingSlowDeathBehavior CloudBreakSpecialPower
CombineHordeSpecialPower CrateCollide CrushDie DamageFilteredCreateObjectDie
DarknessSpecialPower DelayedUpgrade DevastateSpecialPower DoCommandUpgrade
DynamicPortalBehaviour ElvenWoodSpecialPower ExperienceLevelCreate ExperienceScalarUpgrade
FXListDie FreezingRainSpecialPower GarrisonUpgrade GiveOrRestoreUpgradeSpecialPower
GrabPassengerSpecialPower HighlanderBody ImmortalBody InactiveBody LevelUpUpgrade
LocomotorSetUpgrade ManTheWallsSpecialPower MaxHealthUpgrade ModelConditionUpgrade
PlayerUpgradeSpecialPower PorcupineFormationBodyModule RefundDie RepairSpecialPower
RespawnBody Rva00481F82 Rva00589079 ScavengerSpecialPower SiegeAIUpdate SpecialPowerCreate
SpecialPowerModule SplitHordeSpecialPower StealthUpgrade SupplyCenterCreate TaintSpecialPower
TooltipUpgrade TransportAIUpdate UnpauseSpecialPowerUpgrade UpdateModule UpgradeDie
WeaponChangeSpecialPowerModule WeaponModeSpecialPowerUpdate

`link_check` on the 48 changed units plus the one other definer of a changed table
(`SpecialPowerModuleDtor_Unresolved.cpp`, already not linking in the census on
`??_7SpecialPowerModule@@6B@`, a table the change does not touch): 48/48 still LINK,
bytes unchanged. In the census index (c95fcfcfcd) no changed table but
`??_7SpecialPowerModule@@6BObjectModule@@@` has more than one copy.

The landed opt-in form, rebuilt over the same 856 sources: 856/856 byte-exact; against the
object-store variants built from the unedited header, 855 objects have identical COMDAT
digests and external symbol sets; `DamageModule.cpp` adds only the definition
`?loadPostProcess@DamageModule@@MAEXXZ` and the reference
`?loadPostProcess@BehaviorModule@@MAEXXZ` (defined by `BehaviorModuleLoadPostProcess.cpp`).
No `??_7` changed anywhere. `link_check`: DamageModule.cpp LINKS 6 -> 11 B; BoneFXDamage.cpp
keeps only the crc and xfer names; BehaviorModuleLoadPostProcess.cpp,
UpdateModuleLoadPostProcess.cpp and UpgradeModule.cpp LINK unchanged.

### Retail truth at slot 1 of the 56 tables

Each table was found in `tools/vftable_map.py`'s map of retail's installed tables by its
`??_7` name, and slot 1 was read from the image. **None holds BehaviorModule's
0x000B3FD0**, so the unconditional form makes 0 of the 56 equal to retail at slot 1:

- 0x00497805 (`jmp 0x0058B03E`, which jumps to the empty `ret`), 27 tables:
  AllowBannerSpawnUpgrade 0x00C59030, ArmorUpgrade 0x00C570A0,
  AttributeModifierUpgrade 0x00C587E8, BaseUpgrade 0x00C57120, CastleUpgrade 0x00C58880,
  CrateCollide 0x00C5A618, CrushDie 0x00C4AC34, DamageFilteredCreateObjectDie 0x00C4AB54,
  DelayedUpgrade 0x00C573E4, DoCommandUpgrade 0x00C57B58, ExperienceLevelCreate 0x00C5956C,
  ExperienceScalarUpgrade 0x00C584E8, FXListDie 0x00C4AD04, GarrisonUpgrade 0x00C58088,
  InactiveBody 0x00C5AE34, LevelUpUpgrade 0x00C57460, LocomotorSetUpgrade 0x00C57530,
  MaxHealthUpgrade 0x00C58590, ModelConditionUpgrade 0x00C58658, RefundDie 0x00C4A70C,
  Rva00589079 0x00C70190, SpecialPowerCreate 0x00C596B4, StealthUpgrade 0x00C57E30,
  SupplyCenterCreate 0x00C593B8, TooltipUpgrade 0x00C58C08,
  UnpauseSpecialPowerUpgrade 0x00C57EA8, UpgradeDie 0x00C4AEBC.
- 0x0058B03E (`jmp 0x000B3FD0`; rows UpdateModule/UpgradeModule/DamageModule
  `loadPostProcess`), 2 tables: BodyModule 0x00C5AE68, UpdateModule 0x00BF004C.
- 0x00483CEF (`jmp 0x00497805`), 3 tables: ClearanceTestingSlowDeathBehavior 0x00C49E4C,
  GiveOrRestoreUpgradeSpecialPower 0x00C5FA40, WeaponModeSpecialPowerUpdate 0x00C4EA54.
- 0x004C8A2F (`jmp 0x00493B1E`, SpecialPowerModule::loadPostProcess, 182 B with EH), 14
  tables: CloudBreak 0x00C5D42C, CombineHorde 0x00C5E76C, Darkness 0x00C5D854,
  Devastate 0x00C5E494, ElvenWood 0x00C5CE8C, FreezingRain 0x00C5D764,
  GrabPassenger 0x00C5D93C, ManTheWalls 0x00C5E044, PlayerUpgrade 0x00C5E184,
  Repair 0x00C5E6A4, Scavenger 0x00C5D304, SplitHorde 0x00C5E5FC, Taint 0x00C5D5CC
  (all `...SpecialPower`), WeaponChangeSpecialPowerModule 0x00C5D1B4. SpecialPowerModule
  0x00C4E868 holds 0x00493B1E itself.
- 0x004C202F (`jmp 0x004BF40F`, placeholder `Rva004BF40F`, 191 B with EH, calls
  0x0058B03E), 4 tables: HighlanderBody 0x00C5B440, ImmortalBody 0x00C5B550,
  PorcupineFormationBodyModule 0x00C5C3C8, RespawnBody 0x00C5B9A0. ActiveBody 0x00C5B038
  holds 0x004BF40F itself.
- 0x0049A7EE (`jmp 0x002686A4`, AIUpdateInterface::loadPostProcess), 2 tables:
  SiegeAIUpdate 0x00C4D330, TransportAIUpdate 0x00C53AA8.
- 0x0048223D (row `TerrainResourceBehavior::loadPostProcess`, 28 B), table Rva00481F82
  0x00C49408; 0x00461274 (row `DynamicPortalBehaviour::loadPostProcess`, 16 B), table
  DynamicPortalBehaviour 0x00C428C4.

So the unconditional form would be behaviourally retail's (an empty `ret` reached through
a tail-jump chain) for 32 tables. For the other 24 it would replace a `__purecall` with a
silent no-op where retail runs real post-load code. That is no fix, so the declaration
stays opt-in. A table moves to retail only through its own family's override.
`SpecialPowerModule::loadPostProcess` (rowed 0x00493B1E), declared in the special-power view,
would make SpecialPowerModule's table equal retail at slot 1. The 14 derived tables would then
run retail's body, which retail reaches through the 0x004C8A2F tail jump; their slot still
differs until each class's own override is a twin there. ActiveBody's 0x004BF40F does the same
for 5 tables once that placeholder is named, and AIUpdateInterface's 0x002686A4 for 2.
BodyModule and UpdateModule need their 0x0058B03E names (UpdateModule's is rowed;
BodyModule's would be a twin like DamageModule's), and the 27 + 3 tail-jump tables need each
class's own override as an ICF twin of 0x00497805 or 0x00483CEF.

`DamageModule.cpp` includes `GameClient/BuffManager.h`, which selects Snapshot's
capitalized spelling, so in that unit the declaration is a new virtual rather than an
override; the unit emits no vtable (its object defines no `??_7`), and the symbol is the
same.

## Still blocked: `?xfer@DamageModule@@MAEXPAVXfer@@@Z`

The twin at 0x004CE56D compiles from `xfer->Version1(); BehaviorModule::xfer(xfer);`, but a
canonical `BehaviorModule::xfer` is protected virtual (`MAE`) and the ledger names
0x004C9C7D `?xfer@BehaviorModule@@QAEXPAVXfer@@@Z`, bound to the real spelling by the
`/alternatename` hatch in `BehaviorModuleXfer.cpp`. The byte verifier resolves calls only
through ledger rows and pins, so the twin cannot verify, and a pin would put a second name
on a named address. Order of work:

1. Respell the 12 private views that call the `QAE` name so they call `MAE` (or adopt the
   canonical header): BodyModule.cpp, SpawnBehaviorXfer.cpp, BridgeTowerBehaviorXfer.cpp,
   GateOpenAndCloseBehaviorXfer.cpp, CastleMemberBehaviorCtor.cpp, UpdateModule.cpp,
   Rva00493009Xfer.cpp, Rva00589051Xfer.cpp, Rva00589079Derived.cpp, CreateModuleXfer.cpp,
   UpgradeModule.cpp, Rva004CE56DXfer.cpp. Views without a vptr need a qualified call
   (`->BehaviorModule::xfer(xfer)`) once the member is virtual.
2. Rename the 0x004C9C7D row to `MAE`, put `BehaviorModuleXfer.cpp` on the canonical header
   and drop its `/alternatename` (hatch count -1).
3. Declare `xfer` in `BehaviorModule.h` (same opt-in or unconditional decision as above;
   slot 3 of non-overriding tables would go from `__purecall` to BehaviorModule's).
4. Twin row `?xfer@DamageModule@@MAEXPAVXfer@@@Z` at 0x004CE56D in `DamageModule.cpp`
   (needs `BfmeXfer.h` for `Version1`).

`rename.py function --rva 0x004C9C7D --virtual --dry-run` (2026-11-05) plans the respelling
over 13 sources. It gives `UAE`, not Zero Hour's protected `MAE`: the tool changes only
virtuality, so the `/alternatename` would remain as `MAE=UAE`. Two views declare a
derived `xfer` non-virtual, and a virtual base makes those virtual too, changing their rows'
spelling:
- `UpdateModule.cpp`, row `?xfer@UpdateModule@@QAEXPAVXfer@@@Z` 0x0044DF9F, which 15 census
  objects touch;
- `CastleMemberBehaviorCtor.cpp`, row `?xfer@CastleMemberBehavior@@QAEXPAVXfer@@@Z` 0x003957C6.

So those rows need their own `--virtual` respelling, with UpdateModule's callers, before
step 2 can verify. Not applied.

## Still blocked: `?crc@DamageModule@@MAEXPAVXfer@@@Z`

BFME 2 has no crc slot (above), so nothing can define this name honestly. It goes away only
when `BoneFXDamage.cpp` leaves the Zero Hour view for canonical `DamageModuleClass.h` in
retail's slot order: then `BoneFXDamage::crc` is absent-from-retail, `xfer` is the 0x0045CE8C
twin, `loadPostProcess` the 0x00497805 twin, `getModuleNameKey` the 0x004B9757 row
(placeholder `rva004B9757`, static spelling), and the destructor is `Rva004B96E5` (0x004B96E5,
`??_G` 0x004B97C6), which needs `rename.py class --fold Rva004B96E5 --into BoneFXDamage`.
The unit's rowed `onObjectCreated` and `onBodyDamageStateChange` also need canonical Object
`findUpdateModule` and BoneFXUpdate views.
