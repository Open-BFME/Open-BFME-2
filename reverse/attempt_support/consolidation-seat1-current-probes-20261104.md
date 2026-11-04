# Consolidation shard 1 current probes (2026-11-04)

The current allocator still reports shard 1/5 with 99 unheld destinations. The
earlier continuation and reassessment handoffs cover the full listing; these
additional destinations passed `consolidation_queue.py --check-tu`, and each
narrow `name_lane.py consolidate` snapshot passed `--check` before planning.
Every dry run accepted zero donors. No claims, source edits, or merge trials
were retained.

| Destination | Rejected-donor evidence |
| --- | --- |
| `WeaponSet.cpp` | All donors rejected. Compile failures include duplicate `AsciiString`, `Weapon`, and `WeaponSet` views, missing `WeaponSet` declarations and incompatible `BitFlags` templates. LinkGuard found provider COMDAT losses for `WeaponSet` vtable consumers. |
| `Made002CCA37.cpp` | LinkGuard rejected the only donor: the merged composition changes selected `Made002CCA37` deleting-destructor COMDAT. |
| `OathbreakersFadeAwayBehavior.cpp` | Constructor/update donors need the `OathbreakersFadeAwayBehavior` view reconciled (`C2511`/missing member); no donor accepted. |
| `SynchronizeGroupOrder.cpp` | Donors fail on undeclared special members and an abstract class view; class reconciliation is required. |
| `DeletionUpdate.cpp` | Donors fail duplicate `GameLogic`, `SubsystemInterface`, `Xfer` and `Module` declarations. |
| `PillageModule.cpp` | Constructor donor lacks the matching class declaration; another donor fails the `GeometryInfo` slot prerequisite. |
| `BuildableHeroListUpgrade.cpp` | Constructor donor fails `C2511` because its declaration is absent from the target view. |
| `CommandPointsUpgrade.cpp` | Constructor and mux-slot donors lack matching target class declarations (`C2511`/`C2509`). |
| `HordeMemberCollide.cpp` | On-collide donor fails `C2511` for the constructor absent from the target class view. |
| `QueueProductionExitUpdate.cpp` | All seven donors rejected for duplicate `Coord3D`, `Module`/`ObjectModule` views or incompatible vftable declarations. |
| `SiegeDeployHordeSpecialPower.cpp` | Donors fail class-view prerequisites and one donor fails bytes; LinkGuard rejects the seed composition for a changed `DeflectSpecialPowerModuleData` vftable COMDAT. |
| `SupplyCenterCreate.cpp` | Constructor donor fails `C2511` because its declaration is absent from the target view. |
| `RankInfo.cpp` | Donors conflict on STL allocator/vector definitions and operator new/delete linkage; no donor accepted. |

The remaining prerequisites are manual class/view/compiler or provider repairs,
which are outside this mechanical seat. No TU merge, matched-row preservation,
or file reduction is claimed.
