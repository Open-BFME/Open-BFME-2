# View-reconcile screen before merge (dd-47, 2026-10-30)

Lane: reconcile a TU's private class views (dd-39's method), then
`tu_skeleton --merge`, preferring TUs where one merge would absorb many donor
files into an existing TU file. Base: `origin/master` `2fb449c3b1`. Sandbox
`fleet-dd-47` (bx_kux8df7x), snapshot `bfme2-toolchain-20261029b`.

Result: no merge landed. On this base the mechanical part of `tu_views.py` has
no remaining win in the top of the consolidation queue: for every TU measured,
the TU's own class is a `tu_views` CONFLICT, so the tool reverts its writes and
`--merge --dry-run` still accepts 0 donors. Evidence below so the next seat does
not repeat these dry runs.

## What was measured

`tu_skeleton.py --queue --limit 60` (in-memory map, current master) ranks by
files a merge would remove. The top of that list is not mergeable by view
reconcile:

| TU | files (queue) | fresh dry-run: accepted / rejected / mixed | blocker seen by tu_views |
|---|---|---|---|
| ScriptEngine.cpp | 76 | held by yasinschroeder-claudec (49 file claims) | not measured |
| Weapon.cpp | 63 | 11 file claims held (dd-30, yasinschroeder-claudeb2) | not measured |
| W3DProjectedShadow.cpp | 34 | dry run did not finish in 30 min under 4-way load | not measured |
| OpenContain.cpp | 43 | dry run crashed, see tooling note 2 | not measured |
| Team.cpp | 42 | not re-run | map: 34 view-like rejects |
| W3DTreeBuffer.cpp | 10 | 0 / 10 / 6 | `W3DTreeBuffer` base clause differs: seed `public Rva000E6AC0`, Xfer donor `-` (padding model) |
| W3DTankDraw.cpp | 11 | 0 / 12 / 4 | `W3DTankDraw` base clause differs (`W3DScriptedModelDraw` vs `W3DModelDraw` vs none); module base chain |
| ElvenWoodSpecialPower.cpp | 21 | 0 / 26 / 12 | `SpecialPowerModuleInterface`/`SpecialPowerModule` base undefined (C2504) + `getModuleNameKey` |
| MineshaftPortalBehaviour.cpp | 11 | 0 / 11 / 8 | `_STL::_Rb_tree` redefinitions (C2011/C2953) + `MineshaftPortalBehaviour` not a class |
| FirewallHelper.cpp | 18 | 0 / 15 / 3; **seed itself fails `bytes` under every merged flag set** | flag-override problem, not a view |
| CreateObjectDie.cpp | 14 | 0 / 14 / 4 | `CreateObjectDie` base clause differs (`-` vs `ModuleBase, BehaviorModuleInterface, DieModuleInterface`); ModuleData declspec |
| PhysicsUpdate.cpp | 14 | 0 / 25 / 12 | `PhysicsBehavior`/`UpdateModule`/`BehaviorModule` base clauses differ; `UpdateModuleInterface::update` return type differs |
| BoneFXUpdate.cpp | 10 | 0 / 10 / 2 | `BoneFXListInfo`/`BoneOCLInfo`/`BoneParticleSystemInfo` field under the bases; ModuleData declspec |
| ObjectFilter.cpp | 10 | 0 / 11 / 5 | `Rva00360F55`/`ObjectFilter` field overlap; `BfmeFixedStorage0004543D` shared member name |
| AptActionInterpreter.cpp | 19 | 0 / 17 / 4 | 14-file class `AptActionInterpreter` is a *plan*, but every write reverts (needs complete `AptValue`, `AptCallDebugStack`, `AptString`, `AptCIH`) |
| W3DTerrainBackground.cpp | 17 | not re-run | `W3DTerrainBackground` (16 files) and `WorldHeightMap` (11) conflicts |
| PartitionManager.cpp | 17 | not re-run | `BfmeThingCDE`, `ShroudManagerImpl`, `CDEArraySlot` conflicts |
| Mouse.cpp | 14 | not re-run | `Mouse` (13 files) conflict |
| WeaponSet.cpp | 16 | not re-run | `WeaponSet`/`WeaponTemplateSet` conflicts |
| VersionBlockParser.cpp | 16 | not re-run | `VersionBlockEntry` (14 files) conflict |
| AIStatCollector.cpp | 12 | not re-run | `AIStatCollector` conflict |
| RiderChangeContain.cpp | 12 | not re-run | `RiderChangeContain`/`ModuleData` conflicts |
| GiveUpgradeUpdate.cpp | 11 | 0 / 7 / 4 | donor views |
| AISpecialPowerUpdate.cpp | 11 | 0 / 6 / 2 | donor views |
| WoundArrowUpdate.cpp | 11 | 0 / 5 / 2 | donor views |

## Applies that ran and reverted

- `tu_views.py W3DTreeBuffer.cpp`: 9 classes planned, 4 reverted
  (`Rva000EADA7` and `Rva000ECF79Coord` need the *definition* of `ThreeDwords`,
  which lives in another file's block; `Rva000E6AC0` needs `Rva000E6AC0Base`,
  same shape). Merge accepted 0 -> 0.
- `tu_views.py AptActionInterpreter.cpp`: 20+ classes planned, `EAStringC`,
  `AptValue`, `AptActionInterpreter`, `AptInteger`, `AptCallDebugStack` all
  reverted (undefined complete types / `AptCIH` overload). Merge 0 -> 0.

The reverted class is the same failure both times: `tu_views` emits `class X;`
for classes its block names first, but a block that *contains* a base or a
by-value member needs the other file's definition, and the tool restores the
class instead of carrying the definition in.

## Hand union attempt: FakePathfindPortalBehaviour.cpp

Closest TU found (5 donors, one class). The donors disagree on the class's
base and on two member types, so a union was written by hand into the seed
(`UpdateModule` 0x20 with `m_data` +0x04/`m_owner` +0x08, one `Object` view
carrying `getControllingPlayer`, `position`, `angle`, `geometry`, `m_20`/`m_24`
as the two secondary vptrs, `m_28` as `Waypoint *[2]`, `m_34` as
`FakePathfindPortalTarget *`), plus `xfer` moved to `protected` so its mangling
stays `MAE` (the donor's row is `?xfer@...@@MAEXPAVXfer@@@Z`), and the update
donor's `m_object`/`m_registered`/`m_unregisterWhenActive`/`m_target` renamed to
the union's `m_owner`/`m_30`/`m_32`/`m_34`.

Verified: seed 6/6 rows + its data row exact, update donor 1/1 exact. Merge
still rejected all five donors: `Xfer`, `Slot0`, `Ctor` on `bytes` and
`Rva00461C1F`, `Update` with an *empty* `compile:` message (tooling note 3).
`Xfer` also calls `UpdateModule::xfer(xfer)`, so the union's `UpdateModule`
needs that virtual too — the class needs a real contract
(`reverse/class_contracts`), not a union view.

Reverted; nothing from this attempt is left in the tree.

## Tooling notes

1. `tu_views.py` cannot carry a *definition* another file owns (see above). A
   block that needs a base or a by-value member of a class another file defines
   is always reverted; carrying that definition in would turn two of these TUs
   from `reverted` into `plan`.
2. `tu_skeleton.py --merge OpenContain.cpp --dry-run` crashed:
   `UnicodeDecodeError: 'utf-8' codec can't decode byte 0x83 in position 19612`
   inside `build.try_compile_source` -> `subprocess.run(...).communicate()`
   (`tools/build.py:2394`). The compiler's output is not decoded with
   `errors='replace'`/the console code page, so one bad byte aborts the whole
   dry run.
3. Two `--merge --dry-run` refusals printed `compile: ` with no text
   (FakePathfindPortalBehaviour `Rva00461C1F` and `Update` after the union
   edit), so the refusal could not be diagnosed from the report.

## Suggested next step for this lane

These TUs are blocked on class contracts, not on view spelling: the module base
chain (`UpdateModule`/`BehaviorModule`/`SpecialPowerModuleInterface`), the MI
layouts (`Rva0024A797` + four interfaces at +0x0C/+0x10/+0x20/+0x24 for the
fake pathfind portal), and record-type naming (W3DTreeBuffer's
`Rva000ECF79Tree`/`Rva000EDA94Record`, `Rva000ECF79Type`/`W3DTreeType`). Land
the contract first (`class_contracts/`), then the merge is mechanical.
