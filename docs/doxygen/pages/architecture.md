# Architecture {#page_architecture}

BFME 2 runs on EA's SAGE engine, a descendant of Command & Conquer
Generals: Zero Hour, and the source keeps Zero Hour's overall shape. This
page is the map: the layers, the engine object that creates every subsystem,
the split between deterministic logic and per-machine client, how INI data
becomes game objects, notes for modders and remasterers, and the subsystem
pages.

## Layers and directories {#page_architecture_layers}

| Directory | Layer | What lives there |
|---|---|---|
| `Code/GameEngine/Source/Main/` | Process entry | `WinMain`, `GameMain`, `CreateGameEngine`, the window procedure, `Win32GameEngine` |
| `Code/GameEngine/Source/Common/` | Engine core and shared services | `GameEngine`, global data, INI parsing (`INI/`), the RTS model (`RTS/`, `Thing/`), system services (`System/`), plus a large flat area of reconstructed files |
| `Code/GameEngine/Source/GameLogic/` | Simulation | `GameLogic`, objects and modules, AI and pathfinding, skirmish AI, map scripts, terrain logic, Living World logic |
| `Code/GameEngine/Source/GameClient/` | Presentation | `GameClient`, drawables, input, the message stream, GUI, terrain visuals, Living World client code |
| `Code/GameEngine/Source/GameNetwork/` | Multiplayer | lockstep transport, LAN, GameSpy and EA online glue |
| `Code/GameEngineDevice/Source/` | Device layer | `Win32Device` (input, local files), `W3DDevice` (renderer bindings), `MilesAudioDevice` (audio) |
| `Code/Libraries/Source/` | Libraries | WWVegas, Apt, the `subsystem` and `xfer` libraries, compression, DirtySock, vendored third-party code |

A file's directory is where the reconstruction put it, not proof of the
subsystem it belongs to. `Common/` in particular holds thousands of files at
its top level, many of them logic or client code waiting to be merged into
their original translation units; `reverse/tu_map.csv` records the proposed
and approved homes. Address-named files and `Code/gen_*` are placeholders
(\ref page_reading_code_staging).

## From WinMain to the engine {#page_architecture_entry}

- `WinMain` reads the Unicode command line, makes the executable's folder
  the working directory unless `lotrsec.big` is already visible, parses the
  window options, loads the splash image, refuses a second instance,
  creates the main window, completes the launcher handshake through
  `CopyProtect` and calls `GameMain`. It handles teardown afterwards.
- `GameMain` calls `CreateGameEngine`, which builds a `Win32GameEngine`
  and copies the window's active flag into it. `GameMain` then stores the
  engine in `TheGameEngine`, calls `GameEngine::init` and hands control to
  `execute`, the main loop.
- `Win32GameEngine::update` runs the engine update, then pumps the Windows
  message queue.

\ref page_startup has the full sequence and \ref page_frame_loop the loop.

## Subsystems {#page_architecture_subsystems}

Almost every engine service is a *subsystem*: an object derived from
`SubsystemInterface`, created once and reached through a global pointer
named `TheXxx` (`TheGameLogic`, `TheGameClient`, `TheAudio`,
`TheThingFactory`, `TheScriptEngine`, ...). `GameEngine` is one too.

`GameEngine::init` creates most of them in a fixed order through
`SubsystemInterfaceList::initSubsystem` (the file system, name-key
generator, command lists, LOD manager and map cache are created directly).
`initSubsystem` names the subsystem with its `TheXxx` string, calls its
`init`, calls the subsystem's legend loader (believed to load the
`InitFile` and `InitPath` entries listed under that name in
`SubsystemLegend.ini`; that body is not reconstructed yet), records it in
`TheSubsystemList`, and loads the caller's fallback paths only if the
legend loader reported nothing. The legend is the first subsystem created
this way, and `Data\INI\Default\SubsystemLegend.ini` is loaded right after
it. When all are up, `SubsystemInterfaceList::postProcessLoadAll` runs a
post-load pass.

## Platform seams {#page_architecture_seams}

`GameEngine::init` gets its main services from virtual factory methods on
`GameEngine`: the file system, game logic, game client, message stream,
module factory, thing factory, function lexicon, radar, particle system
manager, audio manager and Apt player. `Win32GameEngine` overrides most of
them; the file-system and message-stream factories are `GameEngine`'s own
and are inherited unchanged, while the other nine are pure virtual in
`GameEngine` (as the two classes' retail vtables show). Which
concrete class each BFME 2 override builds is still being identified.
`init` names no platform class, though its error path still calls Win32
message-box and window APIs directly, and it reads the Win32 timer.

The pattern repeats lower down: `W3DGameClient` overrides the client's
factories for the display, the font library and the snow manager, and
`W3DModuleFactory::init` calls `ModuleFactory::init` and then registers
the W3D draw modules, which only the device layer knows about.

## GameLogic and GameClient {#page_architecture_split}

- **GameLogic** is the simulation: objects and their modules, AI,
  pathfinding, map scripts and Lua, players and teams, victory, and the
  Living World campaign logic. In multiplayer every machine runs it in
  lockstep, so the same commands must give the same results everywhere.
- **GameClient** is what one machine shows and hears: drawables, the
  display, UI, FX, audio and input. It may differ between machines.

The client reaches the logic through commands. Input and UI post
`GameMessage`s to the message stream; commands land on `TheCommandList`,
the network layer exchanges them, and `GameLogic::processCommandList` hands
each one to the logic's message dispatcher. `GameLogic::update` takes a
phase number (1 to 6), and the engine derives the client frames per logic
tick from the two timing globals (30 and 5 as shipped, per
`docs/bfme2-network-timing-path.md`). BFME 1: `GameEngine`'s update passes
one phase to the logic on each client frame; the BFME 2 caller is not yet
reconstructed (\ref page_frame_loop).

Determinism is protected in three visible ways:

- **Separate random streams.** Logic code draws from
  `GetGameLogicRandomValue`; client and audio code use
  `GetGameClientRandomValue` and `GetGameAudioRandomValue`, each with its
  own seed. The file and line arguments only feed an optional log of logic
  draws, used to chase desyncs.
- **A fixed FPU mode.** `setFPMode` resets the x87 FPU and selects 24-bit
  precision with round-to-nearest. INI loading and `GameLogic`'s `init`,
  `reset`, `update` and `getCRC` all call it.
- **Checksums.** `GameLogic::getCRC` feeds the objects, the logic random
  seed and several logic managers through a checksum-computing `Xfer`.
  In multiplayer games, `GameLogic::update` periodically posts that value
  as a message. Zero Hour: the logic compares the values from all players
  and treats a difference as a desync. While `GameEngine::init` loads data,
  a separate checksum `Xfer` is attached to the subsystem list; its result,
  plus a value from the Create-a-Hero manager, goes into the global data as
  the INI CRC, which `LANAPI::RequestGameJoin` copies into LAN join
  requests.

\ref page_core_frameworks covers random values, messages and command lists.

## Things, templates and modules {#page_architecture_modules}

- A `ThingTemplate` is one INI `Object` definition: stats, flags and a list
  of modules with their settings. `TheThingFactory` stores templates and
  creates instances.
- An `Object` is the logic instance; a `Drawable` is its client-side twin.
  Both constructors build a `Thing` base, the owner type
  `ModuleFactory::newModule` takes.
- Behaviour comes from modules. `ModuleFactory::newModuleDataFromINI` parses
  a module's settings from the template, and `ModuleFactory::newModule`
  builds the per-instance module from them.
- `ModuleFactory::init` registers every logic module class by name, plus the
  client update modules and BFME 2's client behavior modules, a module type
  Zero Hour does not have. `reverse/module_factory_registrations.csv` lists
  the registrations.

\ref sub_rts_model and \ref sub_objects_modules go further.

## Libraries {#page_architecture_libraries}

- **WWVegas** (Westwood): WWLib, WWMath, WW3D2 with `DX8Wrapper`, wwshade,
  WWDebug, WWSaveLoad, WWDownload.
- **EA libraries**: Apt (the player for the Flash-derived UI movies),
  `subsystem`, `xfer`, `string`, `debug`, `profile`, `assetmanager`,
  `partitionmanager`, compression and DirtySock.
- **Vendored code**, at the releases named in the ledger: the GameSpy SDK,
  Lua 4.0.1, zlib 1.1.4, LZHL, STLport, ATL, GDI+, the MSVC 7.1 runtime and
  dxerr9 (\ref sub_wwlib_thirdparty).
- **Video**: `Code/Libraries/Source/VP6/` holds the On2 VP6 codec.

## BFME 2 compared with Zero Hour {#page_architecture_vs_zh}

- **Logic rate.** Zero Hour's logic runs at 30 frames per second. BFME 2's
  timing globals hold 30 frames and 5 logic ticks per second, a ratio of
  six client frames per logic tick, and its `GameLogic::update` runs in
  phases. The actual frame-rate cap is set separately in `GameEngine::init`
  from global data.
- **INI paths in data.** Zero Hour's `GameEngine::init` passes hard-coded
  INI file and directory paths to the subsystems that load data. BFME 2
  passes none and relies on the legend, apart from a few files `init` loads
  by fixed name (`SubsystemLegend.ini`, `Water.ini`, `Fire.ini`,
  `Environment.ini`, `CommandMap.ini`).
- **New systems.** The Apt UI player, Lua scripting, the Living World
  stores and managers and Create-a-Hero have no Zero Hour counterpart.
- **Platform.** A Unicode command line, a JPG splash through ATL,
  Direct3D 9 behind the `DX8Wrapper` name, and VP6 video instead of Bink.
- **Layout.** `Win32GameEngine` is under `Main/` here; Zero Hour kept it in
  `GameEngineDevice/Source/Win32Device/` and `WinMain` in `Code/Main/`.

## State of the reconstruction {#page_architecture_state}

Every ledger row is byte-matched; what varies is naming and linking. The
entry path (`WinMain`, `GameMain`, `GameEngine::init`) and the top-level
`GameLogic::update` and `GameClient::update` are reconstructed, but
`GameEngine::update` and `execute` are still active targets, so only their
contracts are documented. Game logic, client and network code is largely
named; the flat part of `Common/` is still mostly address-named; WWMath,
Lua, compression and the `subsystem` library are almost fully named. Many
classes exist only as per-file partial views, and not every unit links yet.
To refresh: `rg` a name in `reverse/functions.csv`, and read
`reverse/link_status.csv`.

## Modding notes {#page_architecture_modding}

- **The legend decides which INI files load.** `SubsystemLegend.ini` holds
  `LoadSubsystem` blocks with `InitFile` and `InitPath` entries, matched to
  subsystems by name (the lookup itself is not reconstructed yet). Because
  BFME 2's `init` passes no fallback paths, a subsystem without a legend
  entry loads no INI data through this route.
- **Override files.** `Water.ini`, `Fire.ini` and `Environment.ini` load
  from `Data\INI\Default\` and then again from `Data\INI\`, so the second
  copy can override the first.
- **Content is data; module kinds are code.** New units, buildings and
  powers can be assembled in INI from registered modules. A new kind of
  module, a new subsystem or a different creation order needs C++.
- **Lockstep and checksums.** Everything the logic computes, including
  its random stream, must match on every peer, so a change to logic data
  or code makes this machine's simulation diverge from unmodified peers as
  soon as it changes simulated state, and the periodic logic CRC can then
  differ. Client-only changes (visuals, sounds, UI) stay out of that only
  if they never draw from the logic stream or touch logic state.
- **The INI CRC covers some visual data.** Startup INI data feeds the INI
  CRC in LAN join requests. The startup loads of `Water.ini`, `Fire.ini`
  and `Environment.ini` go through the INI CRC writer, so editing them can
  change the INI CRC even when logic state is untouched. `init` also hands
  that writer to presentation-side stores such as the FX list and damage
  FX stores; which legend-loaded files count depends on the unreconstructed
  legend loader, and whether a BFME 2 host refuses a mismatch is not
  established.
- **Saves and replays.** Zero Hour: saves use the same `Xfer` snapshots as
  the logic CRC and replays store only commands, so a logic change affects
  both (\ref sub_save_load_crc).

## Remastering notes {#page_architecture_remastering}

- **Where a backend plugs in.** The `GameEngine` and `W3DGameClient`
  factory methods are the intended seams, and a port would supply its own
  `GameEngine` subclass: it supplies the factories `Win32GameEngine`
  overrides and inherits the file-system and message-stream factories.
  Platform code also sits outside them: `WinMain.cpp`, `CopyProtect`, the
  Win32 calls in `GameEngine::init`'s error path and its timer read, and the
  direct Direct3D use inside `DX8Wrapper`.
- **Win32.** `WinMain.cpp` owns the window and `WndProc`, splits the
  command line and handles the window options (`-win`, `-fullscreen`,
  `-xpos`, `-ypos`). `GameEngine::init` passes the whole argument list to
  `parseCommandLine` right after creating the global data (its BFME 2 body
  is not reconstructed; Zero Hour: it sets the other options in the global
  data). The window is created with an 800 by 600 client area near the
  screen centre, unless `-xpos`/`-ypos` are given, and is resized when the
  renderer initialises. `Win32GameEngine::update` idles while the window
  is minimised, except in LAN and online games. Keyboard input uses
  DirectInput 8.
- **Rendering.** The renderer is WW3D2 over `DX8Wrapper`, which loads
  `D3D9.DLL` at run time and calls `Direct3DCreate9`; the game also imports
  D3DX 9 functions directly, such as `D3DXCreateEffect` and
  `D3DXAssembleShader`. Whether every draw path (UI, video) goes through
  `DX8Wrapper` has not been traced. If initialisation throws the engine's
  invalid-Direct3D error, `GameEngine::init` shows a localized message box
  and exits; when the string table is not loaded yet it takes the debug
  crash path instead.
- **Audio, video and network.** Audio is the Miles Sound System behind
  `MilesAudioManager`, video uses the linked-in VP6 decoder, and networking
  uses Winsock, the GameSpy SDK and DirtySock (\ref sub_network).
- **Timing and floats.** The 5-tick logic rate and the x87 mode set by
  `setFPMode` are part of the lockstep contract; a port that changes either
  should be expected to diverge from retail logic results (inference: every
  peer must compute identically, and `setFPMode` exists to pin x87
  precision). The engine derives its client frames per logic tick from the
  two timing globals, so changing either changes that ratio. The render
  frame cap is separate: `init` applies it from a global-data value through
  `setFramesPerSecondLimit`.
- **Headless runs.** If the environment variable `_EA_RTS_HEADLESS` is set,
  `GameEngine::init` turns off the shell map and the intro.
- **32-bit layouts.** The source reproduces the retail x86 build, so class
  layouts assume 4-byte pointers, and many files model classes by member
  offset. A 64-bit build would first have to reconcile those layouts.

## Subsystem pages {#page_architecture_map}

- \subpage sub_engine_core
- \subpage sub_common_services
- \subpage sub_memory
- \subpage sub_save_load_crc
- \subpage sub_ini
- \subpage sub_rts_model
- \subpage sub_objects_modules
- \subpage sub_ai_pathfinding
- \subpage sub_scripting
- \subpage sub_gamelogic_map
- \subpage sub_living_world
- \subpage sub_gameclient
- \subpage sub_gui_apt
- \subpage sub_network
- \subpage sub_audio
- \subpage sub_w3d_rendering
- \subpage sub_wwlib_thirdparty

## Reading list {#page_architecture_reading}

- `Main/WinMain.cpp` and `Common/GameEngineInit.cpp` under
  `Code/GameEngine/Source/`, and `SubsystemInterface.cpp` under
  `Code/Libraries/Source/subsystem/`.
- Zero Hour, under `reference/open-bfme-1/inputs/reference/`: `GameEngine.h`,
  `SubsystemInterface.h`, `Module.h` and `Win32GameEngine.h`.
- `docs/bfme2-network-timing-path.md` for the frame rates; \ref page_glossary
  for terms.
