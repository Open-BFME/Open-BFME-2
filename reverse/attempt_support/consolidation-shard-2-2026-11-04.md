# BFME 2 consolidation shard 2 handoff (2026-11-04)

Scope: mechanical TU consolidation only. `python3 /opt/runner/consolidation_queue.py --limit 100000` listed 66 unheld destinations for shard 2/5. Every destination examined passed `--check-tu`; no merge trial accepted a donor unchanged. No source or ledger changes remain in the worktree, and no claims remain held by this seat.

## Candidate trials and handoff

Each candidate below was checked with a current, narrowly scoped `name_lane.py consolidate` report (`--check build/consolidation` passed), `tu_skeleton.py --plan`, and `--merge TU --dry-run` unless noted.

- `Common/System/Geometry.cpp`: no donor accepted; dry run rejected candidates for flags/bytes and reported no verified merge.
- `GameLogic/Object/Made002CCB67.cpp`: ctor donor rejected by LinkGuard because it would break the census-linked TU (`Rva00507823` vslots unresolved).
- `Object/Update/AssistedTargetingUpdate.cpp`: donors need manual private-view/class reconciliation; class reports include `AssistedTargetingUpdate`, `ModuleData`, `FXList`, and `Object`.
- `Object/Behavior/WargBehavior.cpp`: ctor declaration/signature mismatch (`WargBehavior::WargBehavior(...)` not found); private views need reconciliation.
- `Object/Behavior/AutoHealBehavior.cpp`: donors fail class/compile checks; reconcile `AutoHealBehavior`, `ModuleData`, `FXList`, and `Object`.
- `Object/Collide/CrateCollide/HealCrateCollide.cpp`: ctor and execute donors fail private-view method/signature checks.
- `Object/Made002CCB04.cpp`: ctor donor rejected for bytes.
- `Object/Update/HeightDieUpdate.cpp`: ctor donors fail C++ declaration/signature checks.
- `Object/Create/LockWeaponCreate.cpp`: pool-key donor has a duplicate `SubsystemInterface` declaration.
- `GameLogic/AI/AerialPathfinder.cpp`: `ComputePath` donor rejected by LinkGuard; would break another unit's `?0Id@ProfileHighLevel@@QAE@XZ` provider.
- `Common/StatsReporter.cpp`: donor compile errors (`LivingWorldLogic::getFrame`, `Rva004EE037` absent from views); class-view reconciliation required.
- `WWVegas/WW3D2/animobj.cpp`: donor compile errors include return-type-only overload and missing class member; private view reconciliation required.
- `GameLogic/AI/Squad.cpp`: donor compile errors because `Object` view lacks `contain`/`id`.
- `GameClient/Drawable/Update/AnimatedParticleSysBoneClientUpdate.cpp`: ctor donor's class view lacks the corresponding constructor.
- `Object/Made002CCC2D.cpp`: `Made002CCC2DDtor.cpp` rejected with C2600, constructor cannot be defined as a compiler-generated special member because it is absent from the class declaration; reconcile `Made002CCC2D`.
- `WWVegas/WWLib/registry.cpp`: `RegistryDeleteValues.cpp` rejected for bytes.
- `Object/Update/RadarUpdate.cpp`: constructor donor fails on duplicate `BehaviorModuleInterface`/`BehaviorModule` declarations. Mixed file `Common/Rva0024A797Derived.cpp` was inspected with `--split`; splitting it to `RadarUpdate.cpp` is blocked because no row in that file is approved for this TU.
- `Object/Body/PorcupineFormationBody.cpp`: three donors fail because the `PorcupineFormationBodyModule(Thing *, const ModuleData *)` constructor is absent from the class view. Reconcile `ModuleBase`, `Object`, `PorcupineFormationBodyModule`, `PorcupineFormationBodyModuleData`, and `Rva004C2095Contain` before retrying.
- `W3DDevice/GameClient/W3DTaint.cpp`: destructor donor fails duplicate `_STL::set` explicit specialization; interpolate donor compile is inconclusive (`compile:`); matrix-set donor fails bytes. Reconcile `W3DTaint` before retrying class donors.
- `SkirmishAI/AIBaseBuilder/AIBase.cpp`: `AIBase_DoXfer.cpp` fails at `TheSkirmishAIManager` declaration (`missing ';' before '*'`, then C2501); reconcile `AIBase` views.

## Ownership refusal and rollback

`GameClient/Drawable/Update/W3DTornadoDraw.cpp` was the sole trial where dry run accepted an unchanged donor: `W3DTornadoDrawDtor.cpp`. The merge tool was applied, then `tu_ownership.py --staged` refused moved row `0x000CEB6F` (`??1Rva000B19A1@@UAE@XZ`): approved TU is `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTreeDraw.cpp`, not `W3DTornadoDraw.cpp`. This is an upstream ownership gate prerequisite; do not bypass it. The trial was fully restored. The tool acquired file/RVA claims were released; `claims.py release` reported 12 releases.

No source merge was applied, so net source files removed: 0; TUs merged: 0; matched rows preserved by verified merge: 0. Follow-up contributors need to resolve the listed class/header or ownership prerequisites, or select other allocated shard-2 TUs and rerun their current planner and dry runs.
