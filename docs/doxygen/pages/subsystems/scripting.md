# Scripting: map scripts and Lua {#sub_scripting}

BFME 2 has two scripting systems, and both run inside the deterministic game
logic. The **map script engine** (`ScriptEngine`) evaluates the scripts a
designer builds in WorldBuilder and saves into the map: per-side rules of the
form "if these conditions hold, do these actions". The **Lua engine**
(`LuaScriptEngine`) runs the game's Lua script file and answers object
events, such as a unit being damaged or a building being completed, by
calling Lua functions named in an XML file. Zero Hour has only the first; the
Lua engine is already in BFME 1.

The API group is \ref grp_scripting. Where both engines run in the frame is on
\ref page_frame_loop.

## Where it lives {#sub_scripting_where}

| Under `Code/GameEngine/Source/GameLogic/ScriptEngine/` | What is there |
|---|---|
| `ScriptEngine*.cpp` | `ScriptEngine`: init, reset, update, counters, flags, timers, sequential scripts, name lookups, the template tables |
| `ScriptActions*.cpp`, `ScriptConditions*.cpp` | one method per action or condition type, such as `ScriptActions::doNamedAttackArea` |
| `Script*.cpp`, `Condition*.cpp`, `OrCondition*.cpp`, `Parameter*.cpp`, `ObjectTypes*.cpp` | the data model: construction, copying, map-file reading and writing, save-game transfer |
| `Lua*.cpp`, `openLuaLibraries.cpp`, `ScriptEventFlags.cpp`, `Object*.cpp` (other than `ObjectTypes*`), `CurDrawable*.cpp` | `LuaScriptEngine` and the C functions Lua scripts call |
| `VictoryConditions.cpp` | part of `VictoryConditions`, the win and loss checks |

Elsewhere: `GameLogic/Object/Update/DelayedLuaEventUpdate*.cpp` (an object
update module that raises a Lua event on the other objects in range and then
destroys its own object) and `Code/Libraries/Source/Lua/` (the interpreter).
`reverse/tu_map.csv` maps most script files (many only as proposals) to six
original units: `ScriptEngine.cpp`, `ScriptActions.cpp`, `ScriptConditions.cpp`,
`Scripts.cpp`, `LuaScriptEngine.cpp` and `VictoryConditions.cpp`. Search by
function name rather than by file.

## Key classes and singletons {#sub_scripting_classes}

- `ScriptEngine` (`TheScriptEngine`) holds the runtime state: named counters
  and flags, sequential scripts, fades, attack priorities and the template
  tables. It runs the engine-level actions itself, such as counters
  (including setting a counter to a threat value), flags, timers, enabling
  scripts, calling subroutines, fades, sway (breeze) and attack priority,
  and passes the rest on.
- `ScriptActions` (`TheScriptActions`) and `ScriptConditions`
  (`TheScriptConditions`) carry out one action or test one condition each.
- The data model is Zero Hour's: a `ScriptList` per side holds `Script`s and
  `ScriptGroup`s; a `Script` has a chain of `OrCondition`s, each a chain of
  `Condition`s that must all hold, and true and false `ScriptAction` lists.
  Conditions and actions take up to twelve `Parameter`s. `SequentialScript`
  steps through a script's actions for one team or unit; `ObjectTypes` is a
  named list of object types.
- Templates describe each action and condition type for WorldBuilder and the
  map parser: an internal name such as `KILL_HORDE_MEMBERS`, a menu path,
  help text and the parameter types. BFME 2 has 599 action and 202 condition
  templates; `ScriptEngine::getActionTemplate` and
  `ScriptEngine::getConditionTemplate` map an out-of-range type to entry 0.
- `LuaScriptEngine` (`TheLuaScriptEngine`) owns the Lua state, the internal
  event table and the event lists read from XML. `DelayedLuaEventList` is a
  small saveable list that the code raising a Lua event passes to the
  dispatch; its exact role is not yet established.
- `VictoryConditions`, registered as `TheVictoryConditions`, decides defeat
  and victory per player. A separate `VictorySystem` subsystem is updated
  beside the script engines and is not covered here.

## Lifecycle and entry points {#sub_scripting_entry}

| Function | Role |
|---|---|
| `GameEngine::init` | registers `TheScriptEngine` and `TheLuaScriptEngine` as engine subsystems, before `ThePlayerList` and `TheGameLogic` |
| `ScriptEngine::init` | creates `TheScriptActions` and `TheScriptConditions`; in windowed mode optionally loads the script debug window and the FX particle editor DLL; initialises both new objects; fills the template tables; calls `reset` |
| `ScriptEngine::reset` | re-enables input and the mouse cursor; clears counters, flags, sequential scripts, object-type lists and per-player records; empties every side's script list |
| `GameLogic::update` | in the first phase of a logic frame: the time-freeze test, then `ScriptEngine::update` and the Lua engine's update |
| `ScriptEngine::update` | one logic frame of map scripts (below) |
| `ScriptEngine::executeScript` | tests a script with `ScriptEngine::evaluateConditions`, then runs its true or false actions with `ScriptEngine::executeActions` |

The Lua engine's own init, reset and update were not in the ledger when this
page was written; the contract above comes from their call sites.

## One logic frame of map scripts {#sub_scripting_frame}

`ScriptEngine::update`:

1. **Living World gate.** Under a `GameLogic` state test not yet named, it
   returns at once unless the Living World turn phase is in an allowed set
   (\ref sub_living_world).
2. **Timers.** It counts down the close-window and end-game timers and
   advances fades, and goes no further while the game is ending. Countdown
   counters drop by one.
3. **Sides.** For each side in `TheSidesList` it sets the current player and
   a *scope* string (the player's name) and walks that side's scripts and
   groups. The walkers are only partly named; Zero Hour runs
   `executeScript` on each active script here.
4. **Afterwards** it updates team states, clears the frame's UI
   interactions, advances sequential scripts and, with the debug window
   loaded, sends it each counter and flag as `scope/name`.

`ScriptEngine::evaluateConditions` treats the conditions as an OR of AND
terms and stops at the first true term; a condition marked disabled is
skipped. `ScriptEngine::evaluateCondition` answers true, false, counter, flag
and timer conditions itself and passes the rest to `TheScriptConditions`;
`ScriptEngine::executeActions` does the same with `TheScriptActions`.

## How it connects {#sub_scripting_connects}

- **Map data.** Scripts load with the map as `PlayerScriptsList`,
  `ScriptList`, `Script`, `ScriptGroup`, `OrCondition`, `Condition`,
  `ScriptAction` and `ScriptActionFalse` chunks; sides come from `SidesList`
  and trigger areas from `PolygonTrigger` (\ref sub_gamelogic_map).
- **Commands the world.** Actions find teams, units and players
  (`ScriptEngine::getTeamNamed`, `ScriptEngine::getUnitNamed`) and act through
  the AI (\ref sub_ai_pathfinding), objects (\ref sub_objects_modules),
  players (\ref sub_rts_model), the camera, Eva (the in-game announcer) and
  the UI (\ref sub_gameclient, \ref sub_gui_apt). `LIVING_WORLD_*` actions move,
  spawn and despawn campaign armies (\ref sub_living_world).
- **Freezes time.** Zero Hour: a script or a scripted camera move can freeze
  logic time, and `GameLogic::update` and `GameClient::update` test it.
  BFME 2's `GameLogic::update` makes the same kind of test on the tactical
  view and the script engine.
- **Lua events.** Logic code reports object events to `TheLuaScriptEngine`.
  For example, when a member dies and no remaining member is both alive and
  AI-controlled, `Team::notifyTeamOfObjectDeath` raises internal Lua event 7
  (by its slot, apparently `OnTeamDestroyed`; not yet confirmed) before
  running the team's own map-script hook. A team whose members have no AI
  raises it on every member death.

## Lua scripting {#sub_scripting_lua}

When a new game starts, game logic hands the map name to the Lua engine. On
first use the engine opens a Lua state with the base, I/O, string, math and
debug libraries, installs a line hook and registers its C functions as Lua
globals, among them `ExecuteAction` and `EvaluateCondition` (BFME 1: these
build a map-script action or condition from its template name and the Lua
arguments, then run or test it), `ObjectDispatchEvent`, the
`ObjectBroadcastEventTo*` family, object queries and commands such as
`ObjectHasUpgrade` and `ObjectDoSpecialPower`, `GetFrame` and
`GetRandomNumber`. It then runs `Data\Scripts\Scripts.lua` and reads
`Data\Scripts\ScriptEvents.xml`. BFME 1 also loads a `Scripts.lua` and a
`ScriptEvents.xml` from the map's own folder; that BFME 2 step is not yet
reconstructed. A second set, the `CurDrawable*` functions, works on the
drawable being animated.

The XML root is `SageLuaScriptSection`, with `Events` elements (declaring
`InternalEvent`, `ScriptedEvent`, `ModelConditionEvent` and
`ObjectStatusEvent` kinds) and `EventList` elements. An `EventList` has a
`Name`, may `Inherit` another list and holds `EventHandler` entries binding
an `EventName` to a `ScriptFunctionName`, with an optional `DebugSingleStep`.
The engine predefines 17 internal events, among them `OnDamaged`,
`OnDestroyed`, `OnCreated`, `OnTeamDestroyed` and `OnBuildingComplete`.

The interpreter is EA's fork of Lua 4.0.1 (`vendored=lua-4.0.1` rows), which
adds a real boolean type; Open-BFME-1's
`game/Libraries/Source/Lua/PROVENANCE.txt` lists the changes. It is
documented upstream and not described further here.

## BFME 2 compared with Zero Hour {#sub_scripting_zh}

- **Ownership.** Zero Hour's `GameLogic` creates `TheScriptEngine`,
  `TheScriptActions` and `TheScriptConditions`. BFME 2's `GameEngine::init`
  registers the script and Lua engines, and `ScriptEngine::init` creates the
  other two.
- **Counters and flags.** Zero Hour has 256 of each in fixed arrays. BFME 2
  keys them in maps by a scope string and the name (as BFME 1 does); while a
  side's scripts run, the scope is that side's player name.
- **Mode mask.** Each action and condition template carries a mode mask,
  compared with an engine mode of 1 or 2, taken from the same `GameLogic` test as the Living World
  gate; outside its mode a condition is false and an action is skipped. What
  the modes mean is not yet established.
- **Also new:** disabled conditions, the Living World gate, the per-side
  scope, and `DebugWindowLite.dll` as an alternative debug window.
- **More templates.** Hordes, emotions, foundations, command points and
  Living World armies (all in BFME 1 too), plus types that Open-BFME-1's
  tables lack, such as `CREATE_UNIT_REVIVAL_ENTRY`, `ENABLE_PLANNING_MODE`,
  `IS_GAME_MODE_ACTIVE` and `HAS_DELAYED_CARRYOVER_UNIT_OF_TYPE`.

## Modding notes {#sub_scripting_modding}

- **Data-driven:** map scripts (edited in WorldBuilder),
  `Data\Scripts\Scripts.lua` and `Data\Scripts\ScriptEvents.xml`, all opened
  through the game's file system (Zero Hour: which also searches the BIG
  archives). Lua handlers are bound by event and function name, so new
  handlers need no code change.
- **Hard-coded:** the action and condition types and their parameter types
  (built in code), twelve parameters at most, the 17 internal Lua events and
  the set of C functions Lua can call.
- **Map compatibility.** BFME 2's map writer stores each action's template
  internal name next to its type number. Zero Hour: on load the name wins
  over the number; an unknown name becomes a no-op action, so appending
  templates is safe and renaming one breaks maps that use it. BFME 2's reader
  has been reconstructed but is not yet byte-verified.
- **Lockstep.** Both engines run in `GameLogic::update` on every machine, so
  a script that behaves differently on one machine desyncs the game.
  `GetRandomNumber` uses the logic random generator;
  `GetClientRandomNumberReal`, registered with the `CurDrawable*` functions,
  uses the client generator and must never decide game state
  (\ref page_core_frameworks).
- **Timing.** Frame-based timers and countdowns count logic frames, and
  BFME 2 runs fewer logic frames per second than Zero Hour
  (\ref page_frame_loop), so a frame count copied from Zero Hour runs
  longer. The seconds-based timer actions convert seconds to frames when they
  are set, so they keep their real-time length.
- **Saves.** Script state is saved through `Script::xfer`,
  `ScriptGroup::xfer`, `SequentialScript::xfer`, `ObjectTypes::xfer` and
  `DelayedLuaEventList::xfer`. BFME 2's `ScriptGroup::xfer` keeps only the
  active flag, where Zero Hour also saves each script; how saved state is
  matched to a changed map's scripts is not yet reconstructed
  (\ref sub_save_load_crc).

## Remastering notes {#sub_scripting_remastering}

- **Platform seams are few.** `ScriptEngine::init` loads `DebugWindow.dll`
  or `DebugWindowLite.dll` with `LoadLibrary` (windowed mode with script
  debugging on) and, with particle editing on, the FX particle editor DLL
  (also windowed mode only); `ScriptEngine::update` polls that editor each
  logic frame and times slow script frames with `timeGetTime`.
- **Camera coupling.** Fades run from `ScriptEngine::update` on the logic
  side. In Zero Hour the freeze test asks the tactical view whether time is
  frozen and the camera move has finished; BFME 2 makes the same kind of
  call. A replacement camera has to answer that query for scripted scenes to
  pause logic as before.
- **Lua version.** The engine's bindings use the Lua 4.0 C API (`lua_open`
  with a stack size, `lua_pushcclosure`, `lua_setglobal`,
  `lua_setlinehook`), which later Lua versions changed; a newer interpreter
  needs those bindings rewritten. Script-level compatibility of the shipped
  Lua files has not been checked.

## State of the reconstruction {#sub_scripting_state}

Largely matched, with most bytes in named functions (the two template-table
builders above all). Many small helpers keep address-derived names, several
BFME-only action and condition names rest on WorldBuilder leads, and the
`ScriptActions` and `ScriptConditions` dispatchers and the Lua engine's init
and update were not yet reconstructed when this page was written. At that
time none of these classes had a shared header registered in
`reverse/canonical_classes.csv` (\ref page_reading_code). The vendored Lua sources nearly all link; the
script engine files do not all link yet. To refresh this, search
`reverse/functions.csv` and `reverse/link_status.csv` for the paths above.

## Reading list {#sub_scripting_reading}

- Zero Hour, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/`:
  `Include/GameLogic/Scripts.h`, `Include/GameLogic/ScriptEngine.h` and
  `Source/GameLogic/ScriptEngine/`. `ScriptEngine::init` there gives the
  original recipe for adding an action.
- BFME 1, in Open-BFME-1's `game/GameEngine/Source/GameLogic/ScriptEngine/`
  (the Lua engine, per-map Lua loading, scoped counters) and
  `game/Libraries/Source/Lua/PROVENANCE.txt`.
