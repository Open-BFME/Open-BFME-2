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

Retail's slot 1 in those tables is the family's tail jump (0x0058B03E or 0x00497805) to
the same empty `ret` 0x000B3FD0, so the unconditional form calls what retail calls, where
the current `__purecall` would abort a save load that reaches those modules. It is still a
change to 56 emitted tables, which this seat's brief does not allow without the lead's
decision, so the declaration ships behind the opt-in and the measurement stays here.
Next: decide the unconditional form (drop the `#ifdef`), or give each family header its own
`loadPostProcess` override first (UpgradeModule, SpecialPowerModule, BodyModule, DieModule,
CollideModule, UpdateModule views; their rows are the 0x0058B03E and 0x00497805 folds).

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

## Still blocked: `?crc@DamageModule@@MAEXPAVXfer@@@Z`

BFME 2 has no crc slot (above), so nothing can define this name honestly. It goes away only
when `BoneFXDamage.cpp` leaves the Zero Hour view for canonical `DamageModuleClass.h` in
retail's slot order: then `BoneFXDamage::crc` is absent-from-retail, `xfer` is the 0x0045CE8C
twin, `loadPostProcess` the 0x00497805 twin, `getModuleNameKey` the 0x004B9757 row
(placeholder `rva004B9757`, static spelling), and the destructor is `Rva004B96E5` (0x004B96E5,
`??_G` 0x004B97C6), which needs `rename.py class --fold Rva004B96E5 --into BoneFXDamage`.
The unit's rowed `onObjectCreated` and `onBodyDamageStateChange` also need canonical Object
`findUpdateModule` and BoneFXUpdate views.
