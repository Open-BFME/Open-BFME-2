# Mechanical consolidation shard 1 trial handoff (2026-11-05)

No merge or split from these trials remains in the source tree. The tool accepted
no merge in the first 20 allocated TUs or the three later unmixed TUs tried.
All candidate plans passed `consolidation_queue.py --check-tu`; scoped planner
snapshots passed `name_lane.py consolidate --check build/consolidation`.

## New trials

- `GarrisonObjectGroupOrder.cpp`: four clean donors rejected at compile on
  class/vtable declarations, missing `xfer`, and abstract `AICommandInterface` /
  absent method declarations. LinkGuard identified five census-linked units;
  no donors accepted.
- `W3DTerrainVisual.cpp`: nine clean donors rejected on duplicate class/type
  declarations (`SubsystemInterface`, `Coord3D`, `RefCountClass`) or byte
  mismatch. Ten mixed donors remain. No donor accepted; LinkGuard named ten
  census-linked units.
- `RankInfo.cpp`: three donors rejected on STL `operator new/delete`, allocator,
  and vector declaration collisions. Class view reconciliation for `RankInfo`
  is a prerequisite.
- `Code/Libraries/Source/debug/debug_io_con.cpp`: both donors were rejected by
  LinkGuard because moving them would remove the separate `DebugIOCon` vtable
  provider required by the census-linked constructor/destructor objects.
- `BattlePlanUpdate.cpp`: all seven clean donors rejected on missing member
  declarations, signature mismatch, undeclared fields, or missing template
  types. Reconciliation spans `BattlePlanUpdate`, `BattlePlanUpdateModuleData`,
  `Object` and related views.

Earlier first-20 trial blockers and accepted-but-held `TooltipUpgrade` split
evidence are recorded in the session log; unchanged blocked donors were not
recompiled.

## TooltipUpgrade split: accepted then restored

`tu_skeleton.py --split Code/GameEngine/Source/GameLogic/Object/Update/ModuleDataBuildFieldParseChained.cpp --for Code/GameEngine/Source/GameLogic/Object/Upgrade/TooltipUpgrade.cpp --dry-run`
accepted carving row `0x004B7A2E`, carrying
`g_00C58C38TooltipUpgradeFieldParse`; residual and destination passed the
two-object LinkGuard. The required three claims were acquired, and the tool
applied the split. `./build.sh <TooltipUpgrade.cpp> <ModuleDataBuildFieldParseChained.cpp>`
passed for both TUs; `find_declared_unmatched.py` reported all defined functions
matched (with two unclaimed definition notices in the residual).

The staged `data_check.py --staged` then reported two findings outside the
baseline in `TooltipUpgrade.cpp` for `_DRAWABLE_FRAMES_PER_FLASH` (duplicate
definition and wrong name). Running `data_check.py` on the pre-split
`TooltipUpgrade.cpp` from `HEAD` reported zero findings. Per the mechanical lane
rules, this needs a separate data/code repair before retrying; the split trial
was restored and all three claims released. No source or ledger changes from
the split are pending.

`code_identity_gate.py --staged` had zero new findings before restoration.
`check_csv.py` passed. Exact source-path searches in `tools/`, `.githooks/`,
`.github/` and engine include trees found no active path consumer; the split
kept both source paths and changed row ownership only. Do not infer a link
regression from historical `link_status.csv`; the split LinkGuard passed its
pair comparison, while the new data-check finding blocks this trial.

## Other inspected first-20 candidates

`Made002CCA37.cpp`, `SynchronizeGroupOrder.cpp`, `CommandPointsUpgrade.cpp`,
`SiegeDeployHordeSpecialPower.cpp`, `LevelUpUpgrade.cpp`,
`QueueProductionExitUpdate.cpp`, `HordeMemberCollide.cpp`,
`BuildableHeroListUpgrade.cpp`, `OathbreakersFadeAwayBehavior.cpp`,
`DeletionUpdate.cpp`, `CashHackSpecialPower.cpp`, `PillageModule.cpp`,
`SupplyCenterCreate.cpp` and `StructureBody.cpp` produced no accepted merge.
Their dry-run failures were class-view/signature/duplicate-type compile blockers
or LinkGuard refusals for selected COMDATs/vtables. Mixed split dry runs checked
for the selected plans either found no approved row, byte mismatch, compile
blockers, or a LinkGuard refusal. Detailed prior outputs remain in the ignored
build trial logs and existing attempt-support handoffs. Do not repeat an
unchanged failed trial; resolve the named class/header or data prerequisite in
its owning lane first.

## Session scope

No consolidation was applied, so net source files removed: 0; TUs merged: 0;
matched rows preserved by edits: not applicable. The allocated shard has later
candidates beyond the first 20; this is a handoff, not a claim that the shard is
exhausted. No claims remain live.
