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
