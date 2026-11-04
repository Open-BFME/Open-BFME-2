# Shard 0 mechanical consolidation dry-run handoff

Inspected revision: `f33821b80212ed02ccb66d18b3eebe50df5f1e44` (BFME 2, 2026-11-04).
The read-only allocator reported shard `0/5`; `--check-tu` exited 0 for each
attempted destination. Each destination's scoped `name_lane.py consolidate`
snapshot was current before its plan/dry-run. No source or ledger was changed,
no claim was acquired, and no dry run accepted two or more donors. LinkGuard
reported the listed source units census-linked and rejected no candidate on
link loss except the explicit `XferMD5CRC` donor noted below.

| Destination | Dry-run blocker |
|---|---|
| `Common/MessageStream.cpp` | `GameMessage` / `SubsystemInterface` and `Coord3D` / `ICoord2D` redefinitions; `MessageTranslatorNode*` assignment mismatch; command-name donor `bytes`. |
| `Common/XferMD5CRC.cpp` | `XferSave::Open` is absent from the destination view; the GUI dtor donor loses its selected `Rva0052B497` vftable COMDAT under LinkGuard. |
| `Fesl/gamebrowser/gamebrowserpinger.cpp` | `Rva00803080` lacks `initPool`, `clear`, and `m_0c`; generated `Gen008030A0` vftable redefinition. |
| `GameLogic/Object/Upgrade/DelayedUpgrade.cpp` | `DelayedUpgrade` view lacks `upgradeImplementation` and referenced fields. |
| `GameLogic/Object/Create/EvaAnnounceClientCreate.cpp` | Destination class view lacks constructor, slot, and `xfer` declarations. |
| `Fesl/ariesudp.cpp` | GameNetwork donor fails byte verification. |
| `Common/LivingWorldBuildingNuggetSpawnArmy.cpp` | Destination class view lacks `rva004FA659`. |
| `GameLogic/Object/Update/ToggleDeploySpecialAbilityUpdate.cpp` | Destination class view lacks constructor and slot declarations (`rva004AE5B8`, `rva004AE6D7`, `getModuleNameKey`). |
| `W3DDevice/GameClient/Drawable/Draw/W3DQuadrupedDraw.cpp` | Destination class view lacks constructor; STLport `allocator` redefinition and `vector::resize` specialization conflict. |
| `Common/BfmeOwnVVD.cpp` | Donor needs `TheGameClient`, whose declaration is absent from the composed TU. |
| `GameLogic/AI/GroupOrder.cpp` | Donors redefine `GroupOrder` vftable; constructor compiler-generated-member conflict; STLport vector declaration conflict. |
| `GameClient/Snow.cpp` | `SubsystemInterface` redefinition; `WeatherSetting` special-member and constructor declaration conflicts; INI donor compile produced no diagnostic. |
| `W3DDevice/GameClient/GUI/W3DAptComponentColorPicker.cpp` | Donors require undefined base `Rva005248D0`. |
| `Apt/AptDate.cpp` | Donor's `objectMemberLookup` is absent from the destination class view. |
| `GameLogic/Object/Update/FreelistPool.cpp` | donor `Rva001EAFFEElementAt.cpp` fails byte verification. |
| `WW3D2/streak.cpp` | destructor donor explicitly specializes `SimpleVecClass<T>::~SimpleVecClass` after it has already been instantiated. |
| `W3DDevice/GameClient/camerashakesystem.cpp` | donor's `GenericMultiListClass` view lacks `m_headNext08` / `m_headPrev04`. |
| `WW3D2/agg_def.cpp` | donor `AggregateDefRva001A3930.cpp` defines `rva001A3930`, absent from the destination class view. |
| `GameLogic/Object/Upgrade/SpellRechargeModifierUpgrade.cpp` | constructor donor signature is absent from the destination class view. |
| `GameLogic/Object/Update/ModelConditionSoundSelectorClientBehavior.cpp` | module-data dtor and STLport vector donors both failed compilation without diagnostics; LinkGuard retained all three linked objects. |
| `GameLogic/Object/Create/SupplyWarehouseCreate.cpp` | `SupplyWarehouseCreatePoolKey.cpp` donor has duplicate `SubsystemInterface` declarations; LinkGuard retained both census-linked objects. |
| `GameLogic/Object/Behavior/BridgeTowerBehavior.cpp` | Pool-key donor has `SubsystemInterface` redefinition; Xfer donor has `Xfer` redefinition and missing `Version1`; OnDamage/OnHealing donors have `GameLogic` redefinition. LinkGuard retained all five census-linked objects; canonical header adoption/class reconciliation remain registered prerequisites. |
| `WWMath/wwmath.cpp` | `WWLib/wwmath.cpp` donor failed byte verification; LinkGuard retained both census-linked objects (existing common-profile handoff). |
| `Common/TaintManagerImpl.cpp` | `Bfme5SeventySix.cpp` donor defines an undeclared compiler-generated `BfmeTaintManager` constructor; class views require reconciliation. LinkGuard retained both census-linked objects. |
| `GameLogic/Object/Behavior/TerrainResourceBehavior.cpp` | module-data destructor donor failed byte verification; LinkGuard retained both census-linked objects. |
| `GameLogic/Object/Behavior/ShipSlowDeathBehavior.cpp` | constructor donor signature is absent from the destination class view; LinkGuard retained both census-linked objects (existing composition handoff). |
| `GameLogic/Object/Upgrade/ModelConditionUpgrade.cpp` | constructor donor signature is absent from the destination class view; LinkGuard retained both census-linked objects. |

Also not retried because the obstacle register already records an unchanged
prerequisite: `MemoryReadFile.cpp` (missing current consumer/index receipt),
`DevastateSpecialPower.cpp`, `SpecialPowerCreate.cpp`, and `ProcessAnimateWindow.cpp`.
The previously handed-off shard entries for W3DMouse, Command, matpass,
GrabPassengerSpecialPower, ToggleHiddenSpecialAbilityUpdate,
BfmeResourceEnumerator, LinearCampaignManager and AptLoadScreen were not retried.
DelayedDeathBody was not rerun because LINK-211 already records its missing
census-index prerequisite. BridgeTowerBehavior's canonical header and class
prerequisites are already recorded in LINK-168 and the canonical-module header
handoff.

## Follow-up dry runs after rebase onto `2ef33250353c722eeb98efd3b146d791bb4817dd`

Four more allocated destinations passed `--check-tu`, used a current scoped
planner report, and accepted no donors. LinkGuard retained all linked objects.

| Destination | Dry-run blocker |
|---|---|
| `GameLogic/Object/Update/FadeAndDieOrnamentUpdate.cpp` | Constructor donor signature is absent from the destination class view. |
| `GameLogic/Object/Update/SlavedUpdate.cpp` | Pool-key donor redefines `AsciiString`; constructor donor needs absent `m_secondary20` / `m_24`; Rva donor needs `Object::m_modelConditionWords`; Xfer donor redefines `Xfer` and lacks `Version`; move-to-repair donor redefines `Coord3D` and `GameLogic`. |
| `GameLogic/Object/Update/OCLUpdate.cpp` | Constructor donor signature is absent from the destination class view. |
| `GameLogic/Object/Create/InheritUpgradeCreate.cpp` | Constructor signature and `xfer` / `onBuildComplete` are absent from the destination class view; module-data constructor is an undeclared compiler-generated special member. |

These blockers need source/header owners to reconcile class declarations and
private views. Do not retry these unchanged compositions.

Next useful check: have the responsible code/header owners reconcile the stated
declarations, class layouts, STLport or byte prerequisites, then recheck the
destination's allocation and rerun the supported dry run. Do not apply any of
these candidates until it accepts unchanged donors and LinkGuard passes.

## Follow-up dry run on `7f32535bc6ab2a40f68cd6407f2fabf92dc794e7`

`Code/GameEngine/Source/GameLogic/Object/Update/StrafeAreaUpdate.cpp` passed
the shard allocation check and a fresh scoped consolidation snapshot. Its plan
had 19 approved rows, five donor files and two mixed files. The dry run accepted
no donors. `StrafeAreaUpdateCtor.cpp` fails with C2509 (`getModuleNameKey` is
not declared in `StrafeAreaUpdate`); the module-data constructor and destructor
donors fail with C2600 because their compiler-generated special members are not
declared first; `StrafeAreaUpdate_update.cpp` fails with C2504 (`Thing` base
undefined) and C2039 (`setOrientation` is not a member). LinkGuard retained all
five census-linked units. The plan names `AICommandInterface`,
`AIUpdateInterface`, `Thing`, `TerrainLogic`, `UpdateModule` and `WeaponStore`
for class/view reconciliation. No claim or source edit was made.

`SiegeDockingBehavior.cpp` remains blocked by another worker's claims on
`0x00068E15`, `0x0007E48F` and `0x002DFCF6` (read-only claim check on this
session: all three held by the Display seat). No claim was taken.

## Follow-up dry runs on `7f32535bc6ab2a40f68cd6407f2fabf92dc794e7`

Each destination below passed `--check-tu`, used a current scoped planner
snapshot, and accepted no donors. LinkGuard retained every census-linked unit.
No source or ledger was changed and no claim was taken.

| Destination | Dry-run blocker |
|---|---|
| `GameLogic/AI/MoveToGroupOrder.cpp` | `MoveToGroupOrderIsDone.cpp` redefines `rts::hash` (C2953); invalid template use follows (C3203). |
| `GameLogic/AI/AIGuardRetaliate.cpp` | Constructor/state donors need undeclared `xfer`; state donor has `ObjectID` syntax failure; machine donor calls missing `Object::getCurrentWeapon`. |
| `GameLogic/Object/Upgrade/ObjectCreationUpgrade.cpp` | Load donor redefines `StringBase`; constructor overload is absent; module-data ctor is undeclared compiler-generated special member; dtor donor fails byte verification. |
| `GameLogic/Map/FireLogicSystem.cpp` | `FireLogicSystemParseMaterial.cpp`, `StlSweepR3Rva0028681A.cpp` and `stlport_map_int_ptr_tree_dtor.cpp` each fail byte verification. |
| `GameLogic/Object/SpecialPower/CombineHordeSpecialPower.cpp` | `doSpecialPower` donor's constructor is absent from the destination class view. |
| `GameLogic/Object/Update/DemoTrapUpdate.cpp` | `onObjectCreated` donor redefines `Thing` and `Object` (C2011). |
| `GameLogic/Object/Update/TemporarilyDefectUpdate.cpp` | Constructor donor references undeclared destination members `m_p0C` and `m_p10`. |
| `GameLogic/Object/SpecialPower/LevelGrantSpecialPower.cpp` | Constructor donor overload is absent; module-data dtor donor fails compilation without a diagnostic. |

`GameClient/System/Image.cpp` was also rechecked, but its existing handoff already
records the same refusal: the tree-erasure donor fails LinkGuard because the
merged object loses its selected `_M_erase` COMDAT; the other STL donor fails
bytes and `ImageCollectionFindImage.cpp` has duplicate declarations. No new
merge or claim resulted. The three SiegeDockingBehavior RVA claims remained held
by the Display seat in the read-only claim check.

## Follow-up trials on `20cc875663d5e9397b7a4ff8e72fe853310547f5`

Fifteen further allocated destinations passed `--check-tu`, used current scoped
planner reports, and had supported dry runs. Fourteen accepted no donors; their
first blockers were:

| Destination | Dry-run blocker |
|---|---|
| `WW3D2/matpass.cpp` | `RefCountClass` redefinition; other constructor donors need absent class members; destructor/install donors lose rows. |
| `GameLogic/Object/Update/FadeAndDieOrnamentUpdate.cpp` | Constructor overload absent from destination class. |
| `GameLogic/Object/Upgrade/DelayedUpgrade.cpp` | `upgradeImplementation` absent from `DelayedUpgrade`. |
| `GameLogic/Object/Create/EvaAnnounceClientCreate.cpp` | Constructor overload, slot member and `xfer` absent from destination class. |
| `GameLogic/Object/Behavior/BridgeTowerBehavior.cpp` | Duplicate `SubsystemInterface`, `Xfer` and `GameLogic` declarations. |
| `W3DDevice/GameClient/Drawable/Draw/W3DLightDraw.cpp` | `DrawModule` undefined for Xfer/DoDraw donors. |
| `GameLogic/Object/Create/GrantUpgradeCreate.cpp` | Duplicate `SubsystemInterface`; missing `Object::rva00293077`; duplicate module-data declarations. |
| `Common/MemoryReadFile.cpp` | `StringBase` redefinition. |
| `Fesl/gamebrowser/gamebrowserpinger.cpp` | `initPool`, `clear` and `m_0c` absent; generated module vftable redefinition. |
| `GameLogic/Object/Create/InheritUpgradeCreate.cpp` | Constructor overload and `xfer`/`onBuildComplete` absent; undeclared generated special member. |
| `GameLogic/Object/SpecialPower/DevastateSpecialPower.cpp` | `doSpecialPower` and `doSpecialPowerAtLocation` absent from class. |
| `GameLogic/Object/Body/OathbreakerBody.cpp` | `attemptDamage` absent from class. |
| `Fesl/ariesudp.cpp` | `Rva00661650AriesUdp.cpp` fails byte verification. |
| `GameLogic/Object/Update/DelayedDeathBody.cpp` | Constructor overload and `xfer`/`m_b100` absent from class. |

The fifteenth destination, `W3DDevice/GameClient/W3DGameClient.cpp`, accepted
`Rva004C5C6.cpp` unchanged (three rows) and rejected the font factory on duplicate
STLport `pair`, snow factory on duplicate `createSnowManager`, `Rva0004C662Factory`
on absent `Rva004C743::rva0004C662`, and create-drawable donor on duplicate
`Coord3D`/`Thing`. The normal merge moved the accepted rows; the nine-row TU passed
`./build.sh` and `find_declared_unmatched.py`. `tu_ownership.py --staged`,
`code_identity_gate.py --staged` (shadow; zero new findings), `data_check.py
--staged`, and `ms_header_audit.py check --staged` passed. The merge tool's LinkGuard
kept all six census-linked source units. The new W3DGameClient object still needs a
current census/link-batch receipt; this merge claims no new linking coverage.

The tooling audit covered pending source paths: only the absorbed
`Code/GameEngine/Source/Common/Rva004C5C6.cpp` moved into the existing approved
W3DGameClient TU. Current source and doxygen ownership point to the TU. The old
path remains in historical naming votes/agreement evidence and the last census's
`reverse/link_status.csv`; these records were not rewritten. No active include,
tool, hook, workflow or build/configuration consumer of the old path was found.
The full outgoing-range provider/consumer check remains the publish hook's
`link_batch_audit`; its result determines whether this new object is verified.

Next: source/header owners should reconcile the tabled declaration, view, STLport
and byte prerequisites. Recheck allocation after inputs change. Carry
W3DGameClient into the scheduled census and review the publish hook's link audit;
do not claim link progress from the old per-file census row.

## AITNGuard ownership refusal on `5914fe65d8d5a562821d94563477fa7bf755c9d3`

`Code/GameEngine/Source/GameLogic/AI/AITNGuard.cpp` passed allocation and its
scoped plan. Dry-run accepted three unchanged donor files (12 rows); four donors
were rejected for missing `AITNGuardMachine::xfer`, `TheAI` declarations, or the
`AITNGuardMachine(Object *)` overload. LinkGuard retained all eight
census-linked objects. The applied subset built 12/12 and passed
`find_declared_unmatched.py`, but `tu_ownership.py --staged` refused:
`private body of registered class AITNGuardInnerState (header
Code/GameEngine/Include/GameLogic/AITNGuard.h)`. Restored the complete trial,
including transferred hatch/header/ledger changes, and released all 48 claims.
No source or ledger change remains. The canonical class/TU ownership prerequisite
is outside this mechanical lane; do not retry until its owner resolves it.
