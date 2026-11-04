# Mechanical consolidation shard handoff (2026-11-04)

Shard 1/5, selected from `/opt/runner/consolidation_queue.py --limit 100000`.
For each destination, the allocator check passed, the scoped consolidation
planner report passed `name_lane.py consolidate --check build/consolidation`,
and the normal `tu_skeleton.py --plan` / `--merge --dry-run` path preserved the
current sources. No source changes or claims were made. All candidates below
were rejected unchanged by the merge tool:

- `Code/GameEngine/Source/GameLogic/Object/Body/StructureBody.cpp`: no donor
  accepted. The destination's merged composition fails its census link check
  because `?rva004C09A1@Rva004C09A1@@QAEXPBURva004C09A1Object@@@Z` is duplicated;
  `StructureBodyCtor.cpp` also fails byte verification.
- `Code/GameEngine/Source/GameLogic/Object/Create/SupplyCenterCreate.cpp`: no
  donor accepted. `SupplyCenterCreateConstructor.cpp` fails C2511 because the
  destination class view lacks `SupplyCenterCreate(Thing *, const ModuleData *)`.
- `Code/GameEngine/Source/Common/BfmeThingSVA.cpp`: no donor accepted.
  `Rva00028B90Siblings.cpp` fails compilation with C2953, `_STL::basic_string`
  already defined, followed by C2955.
- `Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/AptAnimData.cpp`: no
  donor accepted. `AptAnimDataRenderData.cpp` fails compilation with C2065,
  `map` undeclared, and C2228 on `.findSlot`.
- `Code/GameEngine/Source/GameLogic/Object/Damage/EvacuateDamage.cpp`: no donor
  accepted. `EvacuateDamageModuleDataDtor.cpp` fails with undeclared
  `EmitVtableTag`; `EvacuateDamageEvacuationSum.cpp` reports the STLport
  `__node_alloc::deallocate` specialization already instantiated.
- `Code/GameEngine/Source/GameLogic/Object/Die/CreateCrateDie.cpp`: no donor
  accepted. `CreateCrateDieTestKillerType.cpp` fails with C2143 before `<` and
  C2904 because `BitFlags` is already used as a template name.
- `Code/GameEngine/Source/GameLogic/System/AiOrdersManager.cpp`: no donor
  accepted. `AiOrdersManagerPatrol.cpp` fails with C2460 because
  `Rva0054840A::ObjectID` uses `Rva0054840A` while it is being defined, followed
  by C2065 for `ObjectID`.
- `Code/GameEngine/Source/GameLogic/System/GameLogicDispatch.cpp`: no donor
  accepted. `GameLogic_clearGameData.cpp` fails at `VS` with C2059/C2146;
  `Rva00377064Update.cpp` fails with `SubsystemInterface` and `Shell` C2011
  redefinitions.
- `Code/GameEngine/Source/GameClient/VideoPlayer.cpp`: the earlier bounded
  destructor merge is no longer accepted by the current dry run. Donors now
  fail on `SubsystemInterface` C2011 redefinition, missing `Rva00689180`, or
  the `void *` to `Rva00688980 *` conversion in the element destructor. This
  follows the 2026-11-04 `VideoPlayer.cpp` source update; reconcile the changed
  views and rerun the provider/consumer audit before applying.

No accepted merge, build, or post-merge audit occurred. Source reduction is
zero. Prior unchanged blockers were skipped using `reverse/re_attempts.log` and
the corresponding `docs/linking_obstacles/` entries.
