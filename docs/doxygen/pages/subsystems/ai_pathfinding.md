# AI, pathfinding and skirmish AI {#sub_ai_pathfinding}

This subsystem decides how units move and fight once they have been told
what to do, and plays the computer opponents. It has four layers: per-unit
AI, a state machine owned by each unit's AI update module; groups and group
orders, which turn one command into coordinated orders for many units; the
pathfinder, which plans routes over a cell grid of the map; and player-level
AI, which in BFME 2 is mostly the new skirmish AI. All of it runs inside the
deterministic game logic, so every machine in a multiplayer game computes
the same decisions.

Its API group is \ref grp_ai_pathfinding. The unit-side module that owns a
unit's AI, `AIUpdateInterface`, is described with the other update modules
on \ref sub_objects_modules.

## Where it lives {#sub_ai_pathfinding_where}

All paths are under `Code/GameEngine/Source/GameLogic/`.

| Path | What is there |
|---|---|
| `AI/` | `AI` (`TheAI`), the AI state machine and its states, guard machines, `TurretAI`, `AIGroup` and the group orders, `AIPlayer` and `AISkirmishPlayer`, and much of the pathfinder (`Pathfinder*.cpp`, `Path*.cpp`) and `AerialPathfinder` |
| `Pathfinder/` | more of the pathfinder: `pathfinder.cpp`, path layers, the zone manager's save code, new-map and reset |
| `SkirmishAI/` | BFME 2's skirmish AI: `SkirmishAI`, `AIBuilder`, base, unit, team, economy, upgrade and wall builders, `TacticalAI` with its tactics and target chooser, special-power and spell-book use, `AIDifficulty`, `ArmyDefinition` |
| `System/AiOrdersManager*.cpp` | the group-order manager |

The formation helpers are outside that tree, in
`Code/GameEngine/Source/Common/System/FormationAssistant.cpp`.

Retail assert strings confirm `AI/` (`AIGroup.cpp`, `AIGuard.cpp`,
`AIPlayer.cpp`, `AISkirmishPlayer.cpp`, `AIStates.cpp`, `AITNGuard.cpp`,
`TurretAI.cpp`), a second spelling `Ai/` (`AIGuardRetaliate.cpp`,
`AIHarvest.cpp`), and the `SkirmishAI/` directory with many of its
subdirectories (`AIBaseBuilder`, `AISpecialPowers`, `AITacticalAI`,
`AITeamBuilder`, `AIUnitBuilder`, `AIUpgrade`, `AIWallBuilder`, plus
`AIDifficulty.cpp`). No assert names a file in `Pathfinder/`. Zero Hour keeps
the pathfinder in `AI/AIPathfind.cpp`. Most files here hold one or a few
functions, and `reverse/tu_map.csv` maps them back to original units
(\ref page_reading_code).

## Key pieces {#sub_ai_pathfinding_pieces}

- **AI (TheAI).** The subsystem object. Its constructor creates the AI
  tuning data (`TAiData`; Zero Hour fills it from the `AIData` INI block) and
  the `Pathfinder`, which everything else reaches through
  `TheAI->pathfinder()`. `AI::createGroup` makes the `AIGroup`s that
  commands and scripts work through. Other members answer world queries,
  such as `AI::findClosestEnemy` and `AI::findClosestRepulsor`.
- **Unit AI.** `AIUpdateInterface::makeStateMachine` creates an
  `AIStateMachine` for each unit. Its constructor registers every AI state
  under a fixed state id, each with the ids of the states to enter on success
  and failure; the first state is the default. As in Zero Hour's
  `StateMachine`, a state has `onEnter`, `update` and `onExit`, and `update`
  returns continue, a sleep time, success or failure. Some states run a
  nested machine: guarding uses `AIGuardMachine`, and the guard-retaliate
  and tunnel-network guard machines follow the same pattern. `TurretAI`
  runs a separate small machine for each turret.
- **Commands.** `AICommandInterface` is the command API of a unit's AI:
  methods such as `aiAttackPosition`, `aiGuardPosition` and
  `aiFollowWaypointPath` pack the command and its source into a
  parameter block and pass it to the AI's single command entry, which picks
  the state.
- **Groups and orders.** `AIGroup` holds the units selected together and
  issues group commands (`groupAttackObject`, `groupDoCommandButton` and
  others), computing per-unit destinations so a group keeps its shape. BFME 2 adds
  persistent group orders: `GroupOrder` and its subclasses
  `MoveToGroupOrder`, `MoveToFormationGroupOrder`, `AttackObjectGroupOrder`,
  `GarrisonObjectGroupOrder`, `ChangeStanceGroupOrder` and
  `SynchronizeGroupOrder`. `TheAiOrdersManager` creates and registers them;
  `TheFormationAssistant` supports formations.
- **Pathfinder.** The map is a grid of cells, each classified by the terrain
  under it (`Pathfinder::classifyMapCell`). Cells sit on layers: the
  ground (layer 1) and bridges (layers 2 to 15), with a fixed array of
  sixteen layer slots covering values up to 15. BFME 2 also uses layer values of 16 and above, a
  ramp value and a range of wall values (their naming is not yet settled),
  which the pathfinder handles outside that array; their heights come from
  a separate pathfinder query. As in
  Zero Hour, zones group cells that are reachable from each other for a kind
  of locomotor, so `Pathfinder::QuickDoesPathExist` can rule out impossible
  requests cheaply; full searches are hierarchical
  (`Pathfinder::FindHierarchicalPath`), and `Pathfinder::GetAircraftPath`
  serves flyers. A result is a `Path`, a
  linked list of nodes. Units ask for paths through
  `AIUpdateInterface::requestPath`, which queues them with
  `Pathfinder::queueForPath` (Zero Hour serves that queue from
  `AI::update`).
- **AerialPathfinder (TheAerialPathfinder).** A separate subsystem for
  flying units. Its reconstructed members keep flyers apart, pushing a unit
  away from overlapping neighbours, and probe ground height around a flyer.
  It also stores no-fly zones read from INI.
- **Player AI.** `AIPlayer` builds teams from a queue (`TeamInQueue`,
  `WorkOrder`), finds dozers and trains units for computer-controlled
  players; `AISkirmishPlayer` derives from it.
- **Skirmish AI.** On a new map with game setup info, and only in certain
  game modes (a further logic check, which the ledger reads as a replay
  guard, also stops it; the exact guards are not yet named),
  `TheSkirmishAIManager` sets up AI for each eligible player whose type
  marks it as computer-controlled, or for every eligible player when a
  force flag is set. Other eligible players get an `AIStatCollector`,
  which records their units. The AI-creation call is not yet
  reconstructed; that it creates a `SkirmishAI` is inferred from
  WorldBuilder names. A `SkirmishAI` owns an
  `AIBuilder`, whose components manage dozers, the base, the economy and
  walls, and a `TacticalAI`, which generates tactics (`AITactic` and subclasses such as
  `AIFlankAttackTactic`, `AIRoamingDefenseTactic`, `AIStructureCreepTactic`
  and `AIFarmKillSquad`) and picks targets (`AITargetChooser` with target
  heuristics). `AIDifficulty` makes skirmish-AI decisions pass a chance
  roll whose odds come from a per-difficulty table held by the skirmish AI
  manager, using the logic random generator. Supporting subsystems are
  `TheArmyDefinitionManager`, `TheBaseTemplateLibrary`,
  `TheThreatFinderManager` and `TheAITargetHeuristicLibrary`.

## Lifecycle and entry points {#sub_ai_pathfinding_lifecycle}

1. **Engine start.** `GameEngine::init` creates, in this order,
   `TheFormationAssistant`, `TheAiOrdersManager`, `TheAI`,
   `TheAerialPathfinder`, then `TheSkirmishAIManager`,
   `TheArmyDefinitionManager`, `TheBaseTemplateLibrary`,
   `TheThreatFinderManager` and `TheAITargetHeuristicLibrary`
   (\ref page_startup). Each can load the INI files that
   `SubsystemLegend.ini` lists for it (\ref sub_ini). The pathfinder,
   created inside `AI::AI`, loads its own file.
2. **New map.** `GameLogic::reset` resets `TheAI`; starting a game has the
   pathfinder rebuild its grid, layers and zones for the map.
   `TerrainLogic` registers each bridge with the pathfinder as a layer and
   updates it when a bridge is destroyed or repaired, and water changes
   force a recalculation (\ref sub_gamelogic_map).
3. **Each logic frame.** Unit AI runs inside each unit's AI update module,
   in the update-module phases. In phase 5 `GameLogic::update` calls
   `AI::update`, then later the skirmish AI manager's update
   (\ref page_frame_loop). Zero Hour:
   `AI::update` serves the queued path requests and updates the player
   list, which runs each `AIPlayer`. BFME 2's `AI::update` is described
   here by contract only.
4. **Commands in.** Player orders arrive as messages that the logic
   dispatcher turns into `AIGroup` or `AICommandInterface` calls (Zero Hour
   structure; BFME 2's dispatcher is still being traced). Map scripts build
   temporary groups with `AI::createGroup` and command them
   (\ref sub_scripting).
5. **Save and checksum.** States, machines, groups, group orders and AI
   players all have `xfer` functions. `GameState::init` registers the
   skirmish AI manager (`CHUNK_SkirmishAISystem`) and the orders manager
   (`CHUNK_AiOrdersManager`) as save blocks. `GameLogic::getCRC` includes
   `TheAI`, the skirmish AI manager and the player list
   (\ref sub_save_load_crc).

## How it connects {#sub_ai_pathfinding_connects}

- **Objects** (\ref sub_objects_modules): `AIUpdateInterface` and its
  subclasses own the state machines and drive locomotors along paths;
  `TurretAI` is configured by the `Turret` and `AltTurret` blocks of an AI
  update module's INI.
- **Players and teams** (\ref sub_rts_model): `Player` forwards unit
  creation to its skirmish AI; teams are what `AIPlayer` builds.
- **Map and terrain** (\ref sub_gamelogic_map): the pathfinder reads
  terrain, bridges and water from `TerrainLogic` and the partition manager
  answers proximity queries.
- **Scripts** (\ref sub_scripting): actions command groups; conditions ask
  `QuickDoesPathExist`.
- **Rendering** (\ref sub_w3d_rendering): `W3DTerrainLogic::getLayerHeight`
  and `BaseHeightMapRenderObjClass::isClearLineOfSight` read pathfinder
  layers.

## BFME 2 and Zero Hour {#sub_ai_pathfinding_zh}

The unit AI, groups, pathfinder and `AIPlayer` descend from Zero Hour's
`GameLogic/AI/` (`AI.cpp`, `AIStates.cpp`, `AIGroup.cpp`, `AIPathfind.cpp`,
`AIPlayer.cpp`, `AISkirmishPlayer.cpp`). Differences seen in BFME 2's
bodies:

- **States.** Melee and horde states (`AIAttackMeleeEngageState`,
  `AIAttackMeleeHordeApproachTargetState`, `AIAttackMeleeSquishState`,
  `AIMeleeReAcquireState`), `AIChargeTargetState`, `AIFearState`,
  `AIRampageState`, `AIBackAwayState` and others are not in Zero Hour; they
  already exist in the Open-BFME-1 tree. Machines are identified by a name
  key where Zero Hour passes a name string.
- **Group orders, formations, stances.** `GroupOrder`,
  `TheAiOrdersManager`, `TheFormationAssistant` and stance templates have
  no Zero Hour counterpart.
- **Skirmish AI.** The `SkirmishAI/` tree is new. Many of
  `AISkirmishPlayer`'s virtual overrides only forward to `AIPlayer`.
- **Pathfinder.** The path-request queue (512 slots, as in Zero Hour)
  becomes a ring object, and BFME 2 adds a second ring of the same shape
  whose use is not yet known. The zone manager is reworked: Zero Hour's
  zone equivalency tables are stored differently. New-map setup also marks
  the cells under certain map waypoints. A layer without a bridge takes
  its bounds from a chain of polygon triggers. Several queries are
  horde-aware. `Pathfinder.ini` and `AerialPathfinder` are BFME
  additions, present in BFME 1 as well.
- **Rate.** AI timers count 5 Hz logic frames, against Zero Hour's 30.

## Modding notes {#sub_ai_pathfinding_modding}

- **Data-driven:** INI blocks `AIData`, `SkirmishAIData`,
  `AIDozerAssignment`, `PlayerAIType`, `AIBase`, `ArmyDefinition`,
  `FormationAssistant`, `StanceTemplate` and `AerialPathfindNoFlyZone`
  (a map trigger area name, `TriggerArea`, and a `Height`; an unknown area
  is ignored); a unit's turret fields such as `TurretFireAngleSweep` and
  `ControlledWeaponSlots`. Skirmish base layouts are binary data-chunk files,
  `Bases\<name>\<name>.bse`, each read for its `CastleTemplates` chunk; a
  missing file is skipped, but one that fails to parse aborts loading with
  an INI error. Map scripts steer AI through script actions
  (\ref sub_scripting).
- **Hard-coded:** the set of AI states and their transitions, the six
  group-order classes, the tactic and heuristic classes, the sixteen
  ground/bridge layer slots and the fixed range of wall layer values, the
  path cell size of 10 world units, and the 512-slot request ring (one
  slot stays free, so at most 511 requests wait), which refuses new
  requests when full.
- **Checksums:** `TheAI` and `TheAerialPathfinder` are initialised with
  the INI checksum transfer. The skirmish AI, formation, orders, army,
  base, threat and heuristic subsystems are initialised with none, and
  whether their legend-listed INI enters the checksum depends on the
  legend loader, which is not yet verified. The pathfinder's
  `Data\INI\Pathfinder.ini` is read with no checksum transfer, so it is
  not part of that checksum.
- **Multiplayer:** AI runs in the logic on every machine, including the
  skirmish AI, whose difficulty rolls use the logic random generator. Any
  change that alters AI or pathfinding results or their saved state
  desyncs against unchanged clients, because AI state is in the logic CRC
  (\ref page_core_frameworks).
- **Saves:** group orders are saved by class name (through the name-key
  xfer), and each AI class versions its own block. Changing what a block
  writes breaks loading of retail saves unless the old version is still
  read.

## Remastering notes {#sub_ai_pathfinding_remaster}

- No platform code. The one device-side dependency runs the other way: the
  W3D terrain and height-map code queries pathfinder layers, so a new
  renderer or terrain backend must keep answering those queries from the
  same logic data.
- Timers and repath intervals are in logic frames. Changing the logic rate
  changes AI behaviour and breaks lockstep and replays with retail
  (\ref page_frame_loop).
- The pathfinder is one large object with fixed-size arrays (layers,
  request rings, zone tables) built for the 32-bit retail layout. No
  canonical header declares `Pathfinder`, `AIStateMachine` or `AIGroup`
  yet; source files carry their own partial views.

## State of the reconstruction {#sub_ai_pathfinding_state}

Naming is uneven: some classes, including several of the skirmish AI's
supporting managers, are still address-named and appear here under their
subsystem names, and many method names come from WorldBuilder leads and
may change. Check `reverse/link_status.csv` for which files link; class
and member pages wait for canonical headers. `AI::update` and the logic dispatcher's AI commands are described here by
contract. To list the rows, run
`rg ',Code/GameEngine/Source/GameLogic/(AI|Pathfinder|SkirmishAI)/' reverse/functions.csv`.

## Reading list {#sub_ai_pathfinding_reading}

- Zero Hour: `Code/GameEngine/Source/GameLogic/AI/` and
  `Code/GameEngine/Include/GameLogic/` (`AI.h`, `AIStateMachine.h`,
  `AIPathfind.h`, `AIPlayer.h`, `AIGuard.h`) under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/`,
  and `Code/GameEngine/Source/Common/StateMachine.cpp` for the state machine.
- BFME 1: `reference/open-bfme-1/game/GameEngine/Source/GameLogic/AI/` and
  `Pathfinder/` for the BFME-era states, `AerialPathfinder` and the
  pathfinder changes.
