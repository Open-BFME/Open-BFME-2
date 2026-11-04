# BFME 2 mechanical consolidation handoff (2026-11-03)

Seat 1, shard 1/5. No source or ledger files were changed, no claims were
taken, and no merge or split was applied. Thus matched rows and census linking
remain as they were before these trials; net source-file reduction: 0.

For each TU below, the current allocator check passed, its parent-scope
`name_lane.py consolidate` report was current, and `tu_skeleton.py --plan`
followed by `--merge TU --dry-run` accepted zero donors. The repeated terminal
verdict was `blocked: no verified merge of two or more donors`; LinkGuard
reported census-linked units and no composition was changed.

| Destination TU | Dry-run blocker |
| --- | --- |
| `AIReturnTheRingTactic.cpp` | donor needs `run` and `m_owner` on the target view |
| `GarrisonObjectGroupOrder.cpp` | duplicate vftable and missing `xfer` / abstract class declarations |
| `HordeMemberCollide.cpp` | constructor absent from target view |
| `WeaponSet.cpp` | private-view compile failures; LinkGuard selected `??_7WeaponSet@@6B@` refusal |
| `SiegeDeployHordeSpecialPower.cpp` | compile and byte failures; LinkGuard selected `??_7DeflectSpecialPowerModuleData@@6B@` refusal |
| `Made002CCA37.cpp` | LinkGuard selected `??1Made002CCA37@@UAE@XZ (retail)` refusal |
| `LevelUpUpgrade.cpp`, `TooltipUpgrade.cpp` | missing `UpgradeMux`, member, and base-class views |
| `DeletionUpdate.cpp` | duplicate/private `GameLogic`, `SubsystemInterface`, `Xfer`, and `Module` views |
| `QueueProductionExitUpdate.cpp` | duplicate `Coord3D` / `Xfer`, `BitFlags` mismatch, vftable conflicts |
| `CommandPointsUpgrade.cpp`, `PillageModule.cpp`, `BuildableHeroListUpgrade.cpp` | constructors or `getModuleNameKey` absent from target views |
| `StructureBody.cpp`, `SupplyCenterCreate.cpp` | constructor absent from target view |
| `InstantDeathBehavior.cpp` | duplicate `INI`, `SubsystemInterface`, `Module`, `GameLogic`, and `ModuleData` views; byte failure |
| `OathbreakersFadeAwayBehavior.cpp` | constructor and `getModuleNameKey` absent from target view |
| `SynchronizeGroupOrder.cpp` | special member absent and abstract class errors |
| `UpgradeDie.cpp` | member declarations missing from target view |
| `W3DFloorDraw.cpp` | missing `xfer` / constructor declarations, incompatible module-data view, byte failure |
| `CashHackSpecialPower.cpp` | duplicate UnicodeString / Coord2D / ModuleData declarations and duplicate constructor body |
| `AutoFindHealingUpdate.cpp` | constructor absent from target view |
| `DestroyEnvironmentUpdate.cpp` | undefined `UpdateModule` base and missing member declarations |
| `WoundArrowUpdate.cpp` | missing `SpecialAbilityUpdate` base/constructor and `xfer` declarations |

One separate mixed-file trial inspected
`GroupOrderDerivedDtors.cpp` with
`tu_skeleton.py --split FILE --for GarrisonObjectGroupOrder.cpp --dry-run`.
Although the carved rows matched, SplitLinkGuard rejected both sides; nothing
was written. No mixed source was split by hand.

The fresh allocator listing contains 96 destinations. After the initial
candidate batch, the next three checked destinations were
`AutoFindHealingUpdate.cpp`, `DestroyEnvironmentUpdate.cpp`, and
`WoundArrowUpdate.cpp`; each is blocked by the missing class views above. The
next untried destination in the current listing is
`Code/GameEngine/Source/GameLogic/System/RankInfo.cpp`; check its allocation
again before proceeding. There are no unpublished source changes or live
claims from this seat.

Verification: `python3 tools/name_lane.py consolidate --check build/consolidation`
passed for the latest Update-scope report. No TU build was run because the
dry-runs rejected every donor and no source was modified. Run
`python3 tools/progress.py origin/master` for the final session progress.

## Continuation (2026-11-03)

Resumed at `RankInfo.cpp` as handed off. Its allocated dry run accepted no
donors: `RankInfoCtor.cpp`, `Rva0022CA74Slot9.cpp`, and `RankInfoParse.cpp`
compile trials fail on conflicting STL declarations and `operator new/delete`
linkage. No source or ledger changes were made.

Moved to five other allocated destinations; each allocation check passed, each
narrow-scope consolidation report was current, and each merge dry run accepted
zero donors:

| Destination TU | Exact blocker summary |
| --- | --- |
| `RunOffMapBehavior.cpp` | constructor and `getModuleNameKey` absent from target view |
| `BloodthirstyUpdate.cpp` | vftable conflict; module-data constructor undeclared; module-data dtor bytes; LinkGuard reports unresolved `crc@UpdateModule`, `s04` and `s05` on the merged object |
| `SupplyWarehouseCripplingBehavior.cpp` | constructor absent from target view |
| `CurseSpecialPower.cpp` | constructor absent from target view |
| `AudioLoopUpgrade.cpp` | `update` undeclared, duplicate `StringBase`, undefined `UpgradeMux` |

No claims were taken. Across this and the preceding session there are 29
rejected merge dry runs, one guarded split refusal, and zero applied merges;
net file reduction remains 0. The allocator's shard listing has 96
destinations. The next allocated destination is
`Code/GameEngine/Source/GameLogic/Object/Upgrade/LocomotorSetUpgrade.cpp`;
recheck its allocation and the wind-down marker before proceeding. The latest
Upgrade-scope planner report passed `name_lane.py consolidate --check`.

## Continuation 2 (2026-11-03)

Resumed with `LocomotorSetUpgrade.cpp`, then checked four other allocated TUs.
All five dry runs accepted zero donors; there were no claims or source/ledger
edits.

| Destination TU | Dry-run blocker |
| --- | --- |
| `LocomotorSetUpgrade.cpp` | LinkGuard: merged object loses `GetSnapshotName@UpgradeModule`, `isSubObjectsUpgrade@UpgradeMux`, and `loadPostProcess@UpgradeModule` |
| `W3DTornadoDraw.cpp` | target view lacks `xfer`; module-data destructor fails byte check |
| `HordeMeleeAmoeba.cpp` | STL resize/template errors, missing ctor, byte failures, and LinkGuard selected-copy/vftable refusals |
| `Chat.cpp` | candidates lose matched rows under carried flags; one donor has no baseline match |
| `FireWeaponWhenDamagedBehavior.cpp` | duplicate private `Weapon` / `Object` class declarations in donor compositions |

The current shard listing has 93 destinations. After checking current
allocation, the next destination is
`Code/GameEngine/Source/GameLogic/Object/SpecialPower/DeflectSpecialPower.cpp`;
recheck it and the wind-down marker before proceeding. `git pull --rebase
origin master` completed before this handoff update; no source files were
touched by the rebase.

## Continuation 3 (2026-11-04)

Resumed with `DeflectSpecialPower.cpp`; after it, the following allocated
destinations were checked. Allocation checks passed, planners were current for
each relevant scope, and every merge dry run accepted zero donors:

| Destination TU | Dry-run blocker |
| --- | --- |
| `DeflectSpecialPower.cpp` | constructor lacks default construction; module-data ctor loses `DeflectSpecialPowerModuleData` destructor under LinkGuard |
| `BfmeItemKA.cpp` | GameSubTitle donors lack declarations/members; two STL donors fail bytes; candidates also lose rows or have no baseline match |
| `W3DDebrisDraw.cpp` | vftable type mismatch, missing `getModuleNameKey`, incompatible destructor types, and set-model byte failure |
| `SpecialDisguiseUpdate.cpp` | module-data special member undeclared, target ctor absent from view, module-data dtor byte failure |
| `ExperienceScalarUpgrade.cpp` | LinkGuard unresolved `GetSnapshotName@UpgradeModule`, `isSubObjectsUpgrade@UpgradeMux`, and `loadPostProcess@UpgradeModule` |
| `debug_io_con.cpp` | LinkGuard reports changed retail destructor and vftable copies |
| `BattlePlanUpdate.cpp` | empty compile failure, missing methods/members and ctor view, `AsciiString*`/`const char**` mismatch, undefined `BitFlags<N>` |
| `BfmeThingSVA.cpp` | `_STL::basic_string` redefinition in `Rva00028B90Siblings.cpp`; LinkGuard census-linked units |
| `OldSchoolHelpBoxContentSource.cpp` | missing `m_2a4` and `get` declarations; ctor donor byte failure; class views need reconciliation |
| `CastleUpgrade.cpp` | LinkGuard loses `GetSnapshotName@UpgradeModule`, `isSubObjectsUpgrade@UpgradeMux`, and `loadPostProcess@UpgradeModule` |
| `StdioStreambufBase.cpp` | STLport `char_traits`/`fpos` redefinitions and `locale` redefinition / missing `facet`; LinkGuard census-linked units |
| `CreateCrateDie.cpp` | donor compile fails on malformed `BitFlags` declaration; class view needs reconciliation |
| `AptAnimData.cpp` | donor references undeclared `map` / missing `findSlot`; class view needs reconciliation |
| `AptArray.cpp` | missing `m_data` and `Rva006D6470Owner` base declarations; multiple class views need reconciliation |
| `EvacuateDamage.cpp` | `EmitVtableTag` undeclared and STL allocator specialization already instantiated; class views need reconciliation |

No source/ledger changes or claims were made. Wind-down checks and allocation
checks passed before each destination trial. Planner currency checks passed;
no claims need release. Hidden `.tu_skeleton.cpp` scratch-file scan was empty.
No merge or mixed-file split was applied. The latest listing still has allocated
destinations beyond these trials; `BfmeThingSVA.cpp` was the first destination
checked after `BattlePlanUpdate.cpp`. The next candidate after `EvacuateDamage.cpp`
is `Code/GameEngine/Source/GameLogic/Object/Die/CreateObjectDie.cpp`; its
allocation check passed, but recheck wind-down before starting. Progress and
final session checks remain to be run.
