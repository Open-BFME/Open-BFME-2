# Game logic and the map {#sub_gamelogic_map}

This subsystem is the root of the deterministic simulation. `GameLogic`
(`TheGameLogic`) owns the list of live objects, the logic frame counter, the
start of a game and the per-frame update that runs every other logic
system; the map side (`TerrainLogic`, `SidesList`, waypoints, trigger areas,
bridges and water) holds what a map file contributes to the simulation. Every
machine in a multiplayer game runs this code in lockstep on the same
commands, so it must produce the same results everywhere.

Its API group is \ref grp_gamelogic_map. The client frame and the scheduling
of logic work are on \ref page_frame_loop; the singleton model is on
\ref page_architecture.

## Where it lives {#sub_gamelogic_map_where}

| Path under `Code/` | What is there |
|---|---|
| `GameEngine/Source/GameLogic/System/` | `GameLogic` (`GameLogicInit.cpp` holds `init`, `reset`, `update`, the per-map INI loading and the game-start code; most other methods are one-function files), plus world systems: weather, crates, experience and ranks, attribute modifiers, terrain resources, caves |
| `GameEngine/Source/GameLogic/Map/` | `TerrainLogic`, `Bridge`, `Waypoint`, `PolygonTrigger`, `SidesList` and its records, standing water, fire logic |
| `GameEngine/Source/GameLogic/LargeGroupAudio/` | `LargeGroupAudio`, the logic side of crowd sound |
| `GameEngine/Source/GameLogic/Object/PartitionManager*.cpp`, `Libraries/Source/partitionmanager/` | the spatial partition and its filters |
| `GameEngineDevice/Source/W3DDevice/GameLogic/` | `W3DTerrainLogic`, the renderer-backed `TerrainLogic` subclass |

The Living World code under `GameLogic/System/LivingWorld/` belongs to
\ref sub_living_world. Many files here are split units that
`reverse/tu_map.csv` assigns to an original translation unit (Zero Hour keeps
`GameLogic` in `GameLogic.cpp` and `GameLogicDispatch.cpp`), so search by
function name rather than by file.

## Key classes and singletons {#sub_gamelogic_map_classes}

- `GameLogic` (`TheGameLogic`, created by `GameEngine::init`) owns the object
  list and the object-id lookup (`GameLogic::findObjectByID`,
  `GameLogic::registerObject`, `GameLogic::destroyObject`), selection,
  pause state, load progress, the update-module schedule and the
  multiplayer CRC check (`GameLogic::getCRC`).
  `GameLogic::init` creates the logic-private services:
  `ThePartitionManager`, `TheShroudManager`, `TheCollisionManager`, the
  ghost-object manager, `TheTerrainLogic`, `TheLargeGroupAudio` and
  `TheBuffLogic`, and three owned helpers, one of them the `DOTManager`
  that phase 1 updates.
- `TerrainLogic` (`TheTerrainLogic`) answers ground-height and layer queries
  (`TerrainLogic::getGroundHeight`, `TerrainLogic::getLayerHeight`), owns the
  bridges, waypoints and water changes, and loads the logic part of a map
  (`TerrainLogic::loadMap`). `W3DTerrainLogic` is its device-layer subclass.
  Its `loadMap` reads the map's height data to record the terrain extents
  and height range, then hands over to `TerrainLogic::loadMap`; its height,
  cliff and cell queries forward to the terrain render object. Zero Hour:
  `GameLogic` gets it from a factory virtual that `W3DGameLogic` overrides.
- `Bridge` is one bridge span: deck corners, bounds, an optional outline
  polygon and its towers. `Bridge::isPointOnBridge` and
  `TerrainLogic::findBridgeAt` choose between ground and bridge layers.
- `Waypoint` and `PolygonTrigger` are the named points, paths and areas
  that scripts and AI refer to (`TerrainLogic::getWaypointByName`,
  `TerrainLogic::getTriggerAreaByName`, `PolygonTrigger::pointInTrigger`).
- `SidesList` (`TheSidesList`) holds a map's sides (`SidesInfo`, each with
  its script list and build list of `BuildListInfo` records) and teams
  (`TeamsInfoRec`), in a normal and a skirmish set. It also holds
  castle-template build lists and paths keyed by faction, and per-faction
  build lists.
- The partition manager indexes objects in space for range and visibility
  queries, and the shroud manager tracks what each player has seen.
- World systems: weather (`GlobalWeatherSystem`), fire spread
  (`FireLogicSystem`), crates (`CrateSystem`), ranks and experience levels
  (`RankInfoStore`, `TheExperienceLevelSystem`), attribute modifiers
  (`AttributeModifierStore`), `DOTManager` (role not yet traced; the name
  suggests damage over time), terrain resources and crowd audio
  (`LargeGroupAudio`). Most are configured by INI blocks (see the
  modding notes).

## The logic update {#sub_gamelogic_map_update}

`GameLogic::update` takes a phase number. Each logic frame is phases 1 to 6,
and the engine spreads them over the client frames of one logic tick
(shipped rates: 30 client frames and 5 logic frames per second; see
\ref page_frame_loop for the scheduler, which is described there by its
contract). All phases run inside a floating-point mode guard.

| Phase | Work |
|---|---|
| 1 | Advance the logic frame when a `GameLogic` state check passes (its flags are not yet named) and time is not frozen (the frozen test has the same shape as Zero Hour's `freezeTime` check); script engine, Lua script engine, terrain and `TheVictorySystem` updates; the periodic multiplayer CRC message; recorder, fire-logic, weather and `DOTManager` updates; then every command on `TheCommandList` goes to `logicMessageDispatcher` and the list is reset |
| 2 | Partition manager and collision manager updates, and a per-object frame hook |
| 3, 4 | The first update-module list, half each |
| 5 | Update-module lists two and three; then `TheAI`, the shroud manager, the taint manager, the build assistant, crowd audio, the destroy list (`GameLogic::processDestroyList`), weapon and locomotor stores, the victory conditions, delayed experience grants, one owned helper not yet identified, the skirmish AI manager, the mineshaft portal network manager and teams |
| 6 | The fourth update-module list |

The phase 5 services named by role are known by the names `GameEngine::init`
registers them under (`TheTaintManager`, `TheBuildAssistant`,
`TheVictoryConditions`, `TheSkirmishAIManager`,
`TheMineshaftPortalNetworkManager`). A `GameLogic` helper, not yet named,
also runs in every phase between `TheAI` and the shroud manager.

An update module runs only when its wake frame has come and its object's
disabled state allows it; the sleep time it returns sets its next wake frame
(`GameLogic::friend_awakenUpdateModule` reschedules one). Modules that sleep
forever leave the lists. When time is frozen, phase 1 returns at once unless
a particular queued command makes the script engine continue; when a
single-player game is halted (the flag's exact meaning is still open), phase
1 only drains the command list and the other phases do nothing.

## Starting a game {#sub_gamelogic_map_start}

Game start opens the load screen, initialises the logic, loads the map,
creates players from the network slots or the campaign, and places
multiplayer starting buildings. Zero Hour does this in one
`GameLogic::startNewGame`; BFME 2 splits it into separate functions whose
names are not yet confirmed. The game-start code also runs the per-map INI
loader (Zero Hour and BFME 1 call it `loadMapINI`), which loads the map
folder's `map.ini` and `solo.ini` as overrides and its `map.str` strings
(Zero Hour's `loadMapINI` loads all three the same way), and a sibling
step loads `ambientlightmap.tga` from the same folder into
`TerrainLogic`. A Living World battle also ties map sides to campaign
players (\ref sub_living_world).

## Entry points {#sub_gamelogic_map_entry}

| Function | Role |
|---|---|
| `GameLogic::init` | creates the logic-private services |
| `GameLogic::reset` | clears objects and resets every logic service |
| `GameLogic::update` | one phase of a logic frame |
| `GameLogic::processCommandList` | dispatches and clears the command list |
| `logicMessageDispatcher` | applies one command |
| `TerrainLogic::loadMap`, `TerrainLogic::newMap` | map load into the logic |
| `TerrainLogic::xfer`, `GameLogic::xferObjectTOC` | save and load |

To see whether each one is matched yet, search `reverse/functions.csv` for
its name.

## How it connects {#sub_gamelogic_map_connects}

- **Driven by the engine.** \ref sub_engine_core creates `TheGameLogic` and
  calls its update for each due phase; in a network game \ref sub_network
  decides when a logic frame may run and supplies the commands.
- **Runs the other logic systems.** Objects and their modules
  (\ref sub_objects_modules), AI and pathfinding (\ref sub_ai_pathfinding),
  map scripts and Lua (\ref sub_scripting) and teams (\ref sub_rts_model)
  are all updated from `GameLogic::update`.
- **Map data feeds scripts and AI.** Scripts name waypoints, trigger areas
  and teams from the map; `Team` and `Object` area tests use
  `PolygonTrigger`; the pathfinder tests bridges through
  `Bridge::isPointOnBridge`.
- **Checked and saved.** The CRC path, the recorder and the save files run
  through \ref sub_save_load_crc.
- **Seen by the client.** `GameLogic::bindObjectAndDrawable` pairs each
  object with its client `Drawable` (\ref sub_gameclient), and
  `TerrainLogic::loadMap` hands the map stream to the client's terrain
  visual (\ref sub_w3d_rendering).

## BFME 2 compared with Zero Hour {#sub_gamelogic_map_zh}

- **Phased update.** Zero Hour's `GameLogic::update` runs everything once per
  frame at 30 logic frames per second. BFME 2 splits each logic frame into
  six phases; the phase layout is already in BFME 1.
- **Module schedule.** Zero Hour keeps every update module in one priority
  queue ordered by wake frame (an older always-run list is compiled out).
  BFME 2 keeps four update lists, checks each module's wake frame as it
  walks them, and parks modules that sleep forever on a separate list.
- **Who creates what.** Zero Hour's `GameLogic::init` also creates the script
  engine; in BFME 2 `GameEngine::init` does. BFME 2 adds a separate shroud
  manager (Zero Hour keeps shroud in the partition manager), the collision
  manager, crowd audio and buff logic.
- **More per-frame systems**, none of them in Zero Hour: Lua, fire logic,
  weather, `DOTManager`, crowd audio, delayed experience grants, the taint
  manager, the skirmish AI manager and the mineshaft portal network manager.
  BFME 2 also updates a separate `TheVictorySystem` in phase 1, besides the
  victory conditions in phase 5 (Zero Hour updates `TheVictoryConditions`
  every frame). The CRC is normally computed in a lighter mode, and a
  full mode can be switched on.
- **Map data.** A map can hold 20 sides and 20 skirmish sides (Zero Hour:
  16). The sides list also holds castle-template build lists and paths keyed
  by faction, and per-faction build lists, and a map can reference library maps, whose scripts and teams appear to be
  merged in (not yet traced). Waypoints carry a type and a type option.
  Standing water comes in its own `StandingWaterAreas` chunk
  (Zero Hour marks water with flagged polygon triggers). Bridges may have an
  outline polygon (also in BFME 1), and several bridge-layer queries drop
  Zero Hour's wall-layer case.

## Modding notes {#sub_gamelogic_map_modding}

- **Maps are data.** A map supplies its height map, objects, waypoints (path
  labels, bidirectional flag, type and type option are map-object
  properties), trigger areas, sides, teams, build lists, scripts and water.
  Scripts find waypoints, areas and teams by name, so renaming one in
  WorldBuilder breaks the scripts that use it.
- **Per-map files.** `map.ini` and `solo.ini` in the map folder override INI
  definitions for that map only, `map.str` adds its strings and
  `ambientlightmap.tga` its ambient light map. Some blocks refuse map
  overrides: `WeatherData` throws "Cannot define WeatherData in map.ini".
- **INI blocks** for this subsystem: `WeatherData`, `CrateData`, `Rank`,
  `ExperienceLevel`, `ModifierList`, `FireLogicSystem` and
  `LargeGroupAudioMap`.
- **Hard-coded limits.** 20 sides and 20 skirmish sides per map; five weather
  types (`NONE`, `CLOUDY`, `RAINY`, `CLOUDYRAINY`, `SUNNY`), each with only
  `WeatherSound` and `HasLightning`; 64 water areas changing height at once
  (as in Zero Hour).
- **Determinism.** Everything `GameLogic::update` runs must give identical
  results on every machine. A change to logic code or logic-side data that
  only some players have desyncs the game, and the periodic CRC message
  reports it. Zero Hour: replays re-run the logic from recorded commands, so
  such a change also breaks existing replays.
- **Saves.** `TerrainLogic`, waypoints and build lists write versioned
  blocks, and crowd audio and terrain resources are saved too; a change to
  saved state needs a version bump to keep old saves loading. Saves record
  object templates by name through `GameLogic::xferObjectTOC`, so renaming
  or removing a template affects saves made before the change.

## Remastering notes {#sub_gamelogic_map_remastering}

- **Floating point.** `setFPMode` resets the x87 unit and selects 24-bit
  precision with round-to-nearest; `GameLogic::init`, `GameLogic::reset` and
  every `GameLogic::update` phase apply it. A port that computes logic floats
  differently (for example an x64 build, a different compiler, or
  optimisation settings that change float precision or evaluation order)
  cannot stay in sync with retail
  clients or replay retail recordings unless it reproduces those results bit
  for bit.
- **Timing.** Wake frames, module sleep times and the CRC interval are
  counted in logic frames, and a logic frame's work is spread over client
  frames by phase. Changing the logic rate changes the real-time length of
  every such count; changing the client rate changes how the phases are
  spread (\ref page_frame_loop).
- **Renderer seam.** `GameLogic` gets `TerrainLogic` and its ghost-object
  manager from factory virtuals, and `W3DTerrainLogic` in the W3D device
  layer answers height, cliff and cell queries from the terrain render
  object; `TerrainLogic::loadMap` passes the map to the client's terrain
  visual. A new renderer replaces these. Zero Hour: `W3DGameLogic`
  overrides both factories.
- **Copy protection.** At a fixed logic frame `GameLogic::update` runs a
  `CopyProtect` check (it ends in `CopyProtect::validate`) and posts a
  message if the check fails. Zero Hour has the same check under
  `DO_COPY_PROTECTION`, where the message is `MSG_SELF_DESTRUCT`. A
  remaster or reimplementation has to account for this check.
- **Scene capture.** An unnamed `GlobalData` option makes phase 1 append an
  Xfer-format snapshot, written by a game-client routine that is not yet
  identified, to `scenecapture.dat` in the map folder on each logic frame
  up to a configured frame, and then quit the game. It is gated by the same
  `GameLogic` flags as the frame advance.

## State of the reconstruction {#sub_gamelogic_map_state}

As of October 2026. The `GameLogic` core is matched and named: `init`,
`reset`, `update`, the command-list path, object registration and lookup.
The per-map INI loader (Zero Hour and BFME 1 name: `loadMapINI`) and the CRC
comparison are matched; the CRC comparison's name is still an unverified
WorldBuilder lead. `TerrainLogic`'s map load, bridge, waypoint and save code
and much of `SidesList` are matched, largely from Zero Hour and BFME 1
donors. Many matched bodies, and many helpers called from
`GameLogic::update`, still carry placeholder names. `logicMessageDispatcher`
is not reconstructed, the partition and shroud managers are mostly
unrecovered, the game-start stage names are unconfirmed WorldBuilder leads,
and the key units (`GameLogicInit.cpp`, the `TerrainLogic` and `SidesList`
files) do not link yet. There is no complete shared declaration of
`GameLogic` or `TerrainLogic` yet: most files declare a private view of the
members they use, and only a partial lookup view of `GameLogic` is
registered as canonical (see `reverse/canonical_classes.csv` and
\ref page_reading_code). To refresh this picture, search
`reverse/functions.csv` and `reverse/link_status.csv` for the directories
above.

## Reading list {#sub_gamelogic_map_reading}

- Zero Hour, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/`:
  `Source/GameLogic/System/GameLogic.cpp`, `GameLogicDispatch.cpp`,
  `Source/GameLogic/Map/TerrainLogic.cpp`, `SidesList.cpp`,
  `PolygonTrigger.cpp` and `Source/GameLogic/Object/PartitionManager.cpp`.
- BFME 1, in Open-BFME-1's `game/GameEngine/Source/GameLogic/` tree, the
  donor for the phased update and much of the map code.
- `docs/bfme2-network-timing-path.md` for the client and logic rates.
