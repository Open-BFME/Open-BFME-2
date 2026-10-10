# Engine core: startup, main loop and subsystems {#sub_engine_core}

The engine core is the frame around everything else. It owns the Windows
entry point and window, the launcher handshake, the creation of every
engine-wide service (the `TheX` singletons) and the main loop that alternates
client frames with logic frames. It does almost no game work itself: it
decides what exists, in what order, which data each service loads, and when
each service runs.

This page is the map of the subsystem; its API group is
\ref grp_engine_core. The step-by-step paths are on
\ref page_startup (process start, `GameEngine::init`, shutdown) and
\ref page_frame_loop (one pass of the main loop); the singleton model is on
\ref page_architecture.

## Where it lives {#sub_engine_core_where}

| Path under `Code/` | What is there |
|---|---|
| `GameEngine/Source/Main/` | `WinMain.cpp` (`WinMain`, `WndProc`, `initializeAppWindows`, `GameMain`), `CreateGameEngine.cpp`, and the `Win32GameEngine` units: constructor, `update`, message pump, factory overrides |
| `GameEngine/Source/Common/GameEngine*.cpp` | `GameEngine` itself: `init` (in `GameEngineInit.cpp`), `reset`, `createFileSystem`, the headless-client helpers, and the client half of the frame with its pacing state |
| `GameEngine/Source/Common/CommandLine*.cpp` | handlers for the command-line options, mostly setting fields in the global data |
| `Libraries/Source/subsystem/`, `GameEngine/Source/Common/System/SubsystemInterface.cpp` | `SubsystemInterface`, `SubsystemInterfaceList` and the `initSubsystem` registration helper |
| `GameEngine/Source/Common/GlobalData*.cpp` | `GlobalData` (`TheWritableGlobalData`), covered on \ref page_core_frameworks |
| `GameEngine/Source/Common/Version*.cpp` | `Version` (`TheVersion`) and the parser for its build-information block |
| `GameEngine/Source/Common/System/CopyProtect*.cpp` | `CopyProtect`, the launcher handshake |
| `GameEngine/Source/Common/UserPreferences*.cpp` | `UserPreferences`, the per-user option files |
| `GameEngineDevice/Source/Win32Device/` | Windows input classes (`Win32Mouse`, `DirectInputKeyboard`, `DirectInputMouse`), see \ref sub_gameclient, and part of `Win32LocalFileSystem`, see \ref sub_common_services |

Many of these files are split units. `reverse/tu_map.csv` assigns them to their
original translation units (for example the `Win32GameEngine` pieces to
`GameEngineDevice/Source/Win32Device/Common/Win32GameEngine.cpp`, where Zero
Hour keeps that class), so search by function name rather than by file.

## Key classes and singletons {#sub_engine_core_classes}

- `GameEngine` (`TheGameEngine`) owns startup, the main loop and the
  engine-wide reset. `GameEngine::init` builds every other subsystem;
  `GameEngine::reset` returns them to their starting state (Zero Hour calls
  it when a game ends and before a saved game loads).
  It also keeps the client-frame pacing state that \ref page_frame_loop
  describes. As in Zero Hour, `GameEngine` derives from `SubsystemInterface`
  and gets several services, the platform-specific ones among them, from
  `create*` factory virtuals:
  the call sites in `GameEngine::init` show which subsystem each one produces
  (game logic, client, message stream, module and thing factories, function
  lexicon, radar, particle systems, audio, Apt player, file system).
- `Win32GameEngine` is the Windows subclass that `CreateGameEngine`
  builds. Its constructor sets the process error mode so Windows shows no
  critical-error dialogs (as in Zero Hour); `Win32GameEngine::update` adds the
  Windows message pump and the minimised-window wait to each frame. It
  overrides most of the factory virtuals. Their slot order differs from
  Zero Hour's, and the concrete classes they create are mostly not yet
  named.
- `SubsystemInterface` is the base class of every registered service:
  `init`, `postProcessLoad`, `reset`, `update`, plus the BFME-only
  `loadIniFilesFromLegend`. Several further virtual slots have default
  bodies but no recovered names.
- `SubsystemInterfaceList` (`TheSubsystemList`) keeps the registered
  subsystems in creation order and runs whole-list passes over them, such
  as `postProcessLoadAll` after all data is loaded and the reset pass that
  `GameEngine::reset` uses. During `GameEngine::init` it also holds the
  CRC-computing `Xfer` that the INI CRC is built with
  (\ref sub_save_load_crc).
- `SubsystemLegend` (`TheSubsystemLegend`) holds
  `Data\INI\Default\SubsystemLegend.ini`: one `LoadSubsystem` block per
  subsystem name, listing the INI files and directories that subsystem
  loads (\ref sub_ini).
- `GlobalData` (`TheWritableGlobalData`) holds the settings that the
  command line and the INI files fill in. `Version` (`TheVersion`) and
  `CopyProtect` are small services for `WinMain`; `UserPreferences` is the
  base of the per-user preference files that the option, skirmish, LAN and
  online menus read and write.

## How a subsystem is registered {#sub_engine_core_registration}

`GameEngine::init` registers each service through the `initSubsystem`
template. The new object is stored in its global, named with its
registration string (such as `TheWeaponStore`), initialised, and then offered
its data from the legend; `SubsystemInterfaceList::initSubsystem` loads the
INI paths its caller passed only if the legend supplied nothing. Each list
entry is paired with a small slot object that owns the subsystem: destroying
the slot deletes it and clears its global. The legend lookup
(`SubsystemInterface::loadIniFilesFromLegend`) is not yet matched; its draft
follows BFME 1. \ref page_startup gives the registration order.

## Entry points {#sub_engine_core_entry}

| Function | Role | State |
|---|---|---|
| `WinMain` | process entry: command line, window, launcher handshake, then `GameMain` | matched |
| `WndProc` | window procedure: focus, mouse messages, launcher messages | matched |
| `GameMain` | creates the engine with `CreateGameEngine`, then runs `init` and `execute` | matched |
| `GameEngine::init` | creates and registers every subsystem | matched |
| `GameEngine::execute` | the main loop; returns when the game quits | contract only |
| `GameEngine::update` | one client frame, then any logic work due | contract only |
| `Win32GameEngine::update` | `GameEngine::update` plus the message pump | matched |
| `GameEngine::reset` | engine-wide reset of every subsystem | matched |
| `SubsystemInterfaceList::initSubsystem` | registration and data loading for one subsystem | matched |

The two contract-only functions, and the routine that schedules the logic
phases, are active reverse-engineering targets: \ref page_frame_loop gives
their contract and `docs/bfme2-network-timing-path.md` what is known of their
arithmetic.

## How it connects {#sub_engine_core_connects}

- **Creates everything.** `GameEngine::init` first creates the file system
  (\ref sub_common_services), name keys and command list, then registers the
  services of nearly every other subsystem: data stores (\ref sub_ini,
  \ref sub_rts_model), simulation (\ref sub_gamelogic_map,
  \ref sub_scripting, \ref sub_ai_pathfinding, \ref sub_living_world),
  client (\ref sub_gameclient, \ref sub_gui_apt, \ref sub_audio), and the
  recorder and game state (\ref sub_save_load_crc).
- **Runs everything.** Each pass of the main loop runs the client half
  (input, UI, audio, drawing) and then the logic half, which calls
  `GameLogic::update` for each logic phase that is due. In a network game,
  \ref sub_network decides when a logic frame may run and can make the
  engine skip client work to catch up.
- **Resets everything.** `GameEngine::reset` shows a blank window layout,
  resets every subsystem on the list, deletes the network object after a
  multiplayer game (subject to one further condition not yet identified),
  stops any headless clients and restarts the client pacing state.
- **Talks to Windows.** `WndProc` forwards mouse messages to `Win32Mouse`,
  passes focus changes to the engine and the Direct3D device
  (\ref sub_w3d_rendering) and checks each message it handles (after the
  debug hook and the IME manager) for the launcher's reply.

## BFME 2 compared with Zero Hour {#sub_engine_core_zh}

- **Data loading comes from the legend.** Zero Hour has no
  `SubsystemLegend`; its `GameEngine::init` passes each subsystem's INI paths
  in code. BFME 2 gives the legend first refusal and passes no INI paths to
  `initSubsystem`; the few files `GameEngine::init` still loads itself are
  listed under \ref sub_engine_core_modding.
- **Subsystem ownership.** Zero Hour's list holds plain pointers, and a
  subsystem's destructor removes it from the list. In BFME 2 the
  `SubsystemInterface` destructor is empty; the per-subsystem slot object
  stored beside each entry owns and deletes it.
- **Two rates.** Zero Hour runs at most one logic frame per client frame
  (when the network allows), with a logic timestep of 1/30 s
  (`LOGICFRAMES_PER_SECOND`); the client frame cap comes from the global
  data. BFME 2 runs logic at a lower nominal rate than rendering, split
  into phases, and can skip client frames under network pressure
  (\ref page_frame_loop). The phase model and the client-frame skip are
  already in BFME 1.
- **Headless clients** (also in BFME 1, not in Zero Hour). The engine can
  launch up to seven extra copies of the game, each with a numbered
  `_EA_RTS_HEADLESS` environment variable. Such a copy skips the shell map
  and intro, opens the LAN lobby instead of the main menu and offsets its
  LAN port by its instance number. The map-select menu starts them: its
  `HeadlessCount` combo box (`MapSelectMenu.wnd`) offers 1 to 7, and
  starting a map from the multiplayer list with a count chosen hosts a local
  LAN game on the loopback address 127.0.0.1 and launches that many copies.
  `GameEngine::reset` and the LAN lobby's cleanup stop them. Whether
  retail's shell can reach this menu is not established.
- **Window procedure.** BFME 2 lets a debug hook claim each message first,
  ignores `WM_CLOSE` (Zero Hour, unless already quitting, queues an
  instant-quit game message on the message stream), notifies two further
  singletons when the application gains or loses activation and handles one
  private window message.
- **Build information.** Zero Hour's `WinMain` fills `Version` from
  compile-time macros. BFME 2's `Version` reads its build title, user,
  machine, GUID, time, date and configuration from a small key-value block
  embedded in the executable.
- **Preferences.** `UserPreferences` has a `load` overload for Unicode file
  names, and its core get/set accessors are virtual (in Zero Hour only the
  destructor, `load` and `write` are). Startup differences (Unicode command
  line, splash, launcher result) are on \ref page_startup.

## Modding notes {#sub_engine_core_modding}

- **Which files a subsystem loads is data; which subsystems exist is code.**
  A mod can redirect or extend a subsystem's INI files through its
  `LoadSubsystem` block in `SubsystemLegend.ini`, looked up by the
  registration name (the lookup itself is reconstructed from BFME 1 and not
  yet byte-verified). Adding a subsystem, removing one or changing the
  creation order needs a code change in `GameEngine::init`.
- **Some files are fixed paths.** `GameEngine::init` loads a few files
  directly rather than through legend entries, so the legend cannot
  redirect them: `SubsystemLegend.ini` itself, `Water.ini`, `Fire.ini` and
  `Environment.ini` (each read from `Data\INI\Default` and then again from
  `Data\INI` as an override), and `CommandMap.ini`.
- **Startup data is checksummed.** While it registers subsystems,
  `GameEngine::init` gives the subsystem list a CRC-computing `Xfer`, which
  the legend loader (reconstructed from BFME 1) passes to the INI files it
  reads; the Water, Fire and
  Environment INI files are read through the same `Xfer`. The result, plus
  the create-a-hero data's CRC, is the INI CRC. A LAN join request carries
  it, GameSpy game listings advertise it, and the online custom-match join
  screen refuses a game whose INI CRC differs from its own, so a mod that
  changes this data cannot join an unmodified online game. Whether a LAN
  host checks it is not yet traced. `SubsystemLegend.ini` itself and
  `CommandMap.ini` are loaded outside the CRC. \ref page_startup has the
  details and the command-line options such as `-mod`.
- **Preference files are outside the archives.** `UserPreferences` reads and
  writes plain `key = value` text files with the C runtime, not through the
  game's file system, in a folder whose path the global data supplies (Zero
  Hour: the user-data folder). A BIG archive therefore cannot supply or
  override them.
- **Local LAN instances.** The headless-client mode above starts at most
  seven extra instances. The limit is hard-coded twice: in a fixed-size
  table in `GameEngine` and in the fixed 1-to-7 loop that fills the menu's
  combo box.

## Remastering notes {#sub_engine_core_remastering}

- **Platform seam.** Windows-specific engine code sits in `WinMain.cpp` and
  `Win32GameEngine` (window, message pump, error mode, focus), with input in
  `Win32Device`; the headless clients use `CreateProcess` and environment
  variables. The `create*` factory virtuals are the backend seam: in Zero
  Hour they are where the Win32, W3D and Miles implementations are chosen,
  and in BFME 2 `GameEngine::init` shows which subsystem each produces. A
  new backend plugs in there. `createFileSystem` and `createMessageStream`
  are identified; the classes that `Win32GameEngine`'s overrides create are
  mostly not yet named.
- **Focus and device loss.** When the application gains or loses focus,
  `WndProc` calls `Reset_D3D_Device` and updates the engine's active flag;
  in fullscreen it blocks window moves, resizes, the system menu and monitor
  power-down.
- **Launcher dependency.** The game exits at startup without the launcher
  handshake, and the launcher check does not end there: `GameLogic::update`
  also calls a `CopyProtect` check. A remaster must replace both.
- **Timing.** The frame-rate cap comes from the global data after a
  provisional value during init, and `GameEngine::reset` restarts the pacing
  state from `timeGetTime`. Logic and render rates are coupled through the
  phase scheduler (\ref page_frame_loop).

## State of the reconstruction {#sub_engine_core_state}

The startup path is largely matched and named: `WinMain`, `WndProc`,
`GameMain`, `CreateGameEngine`, `GameEngine::init`, `GameEngine::reset`,
`Win32GameEngine::update`, `SubsystemInterfaceList::initSubsystem` and the
launcher code. The main loop (`GameEngine::execute`, `GameEngine::update`
and the phase scheduler) is not yet reconstructed. Several engine helpers,
the message pump, the factory overrides and many virtual slots still carry
placeholder names. `GameEngine` has no shared class declaration yet: each
source file declares only the members it uses (\ref page_reading_code).
Several key units, `GameEngineInit.cpp` among them, do not link yet. To
refresh this picture, search `reverse/functions.csv` and
`reverse/link_status.csv` for the files above.

## Reading list {#sub_engine_core_reading}

- Zero Hour, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/`:
  `Main/WinMain.cpp`, `GameEngine/Source/Common/GameEngine.cpp`,
  `GameEngine/Include/Common/SubsystemInterface.h` and
  `GameEngineDevice/Source/Win32Device/Common/Win32GameEngine.cpp`.
- BFME 1, in Open-BFME-1's `game/` tree:
  `Libraries/Source/subsystem/SubsystemInterface.cpp` and
  `GameEngine/Source/Common/System/SubsystemLegend.cpp`.
