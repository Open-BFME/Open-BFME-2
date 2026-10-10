# Startup: from WinMain to the first frame {#page_startup}

This page follows the process from the Windows entry point to the main loop,
and back out at exit. Startup decides which global services exist, in what
order they are created and which data files each one reads, so nearly every
other part of the engine depends on it. What happens on each frame is on
\ref page_frame_loop; the singleton and subsystem model is on
\ref page_architecture.

## Where it lives {#page_startup_where}

| Directory or file | What is there |
|---|---|
| `Code/GameEngine/Source/Main/` | `WinMain.cpp` (`WinMain`, `WndProc`, `initializeAppWindows`, `GameMain`, `shutdownGameEngine`), `CreateGameEngine.cpp`, and the `Win32GameEngine` files (constructor, `update`, the message pump, factory overrides) |
| `Code/GameEngine/Source/Common/GameEngineInit.cpp` | `GameEngine::init`, the creation order of every subsystem |
| `Code/GameEngine/Source/Common/GameEngine*.cpp` | the rest of `GameEngine`: `reset`, `createFileSystem`, frame timing and the client half of the frame |
| `Code/GameEngine/Source/Common/CommandLine*.cpp` | one handler per command-line option |
| `Code/GameEngine/Source/Common/System/CopyProtection.cpp` | mainly `CopyProtect`, the launcher handshake |
| `Code/GameEngine/Source/Common/System/CopyProtectVerified.cpp` | `CopyProtect::setVerified` and `CopyProtect::isVerified` |
| `Code/Libraries/Source/subsystem/` | mainly `SubsystemInterface` and `SubsystemInterfaceList`, the registration framework |
| `Code/GameEngine/Source/Common/System/SubsystemInterface.cpp` | `SubsystemInterfaceList::postProcessLoadAll` |

**Key classes.** `GameEngine` owns startup and the main loop, and
`Win32GameEngine` is the Windows subclass `CreateGameEngine` builds.
`SubsystemInterface` is the base of every registered service (`init`,
`postProcessLoad`, `reset`, `update`, plus `loadIniFilesFromLegend`, which
the BFME games add; BFME 1 has it too); `SubsystemInterfaceList` (`TheSubsystemList`)
keeps them in registration order. `SubsystemLegend` reads
`SubsystemLegend.ini`, which tells each subsystem which INI files to load.
`GlobalData` (`TheWritableGlobalData`) holds the settings that the command
line and the INI files fill in.

## The path at a glance {#page_startup_overview}

| Step | Function | Status |
|---|---|---|
| 1 | `WinMain`: command line, working directory, splash, window, launcher handshake | matched |
| 2 | `GameMain`: create, initialise and run the engine | matched |
| 3 | `CreateGameEngine`: allocate a `Win32GameEngine` and pass it the window's focus state | matched |
| 4 | `GameEngine::init`: core services, then about ninety subsystems in a fixed order | matched |
| 5 | `GameEngine::execute`: the main loop; returns only when the game quits | not yet reconstructed |
| 6 | back in `WinMain`: launcher cleanup and engine teardown | matched |

Because steps 1 to 4 and 6 are byte-matched, the order described below is the
retail order, not a guess.

## WinMain {#page_startup_winmain}

`WinMain` keeps Zero Hour's outline. In order, it:

1. reads the Unicode command line and converts it to UTF-8 (before its
   `try` block);
2. changes to the executable's folder, but only if `lotrsec.big` is not
   visible from the current directory;
3. splits the line into at most 32 arguments (the code rewrites a leading
   byte 0x96, the Windows-1252 en dash, to a hyphen; because the line is
   already UTF-8 at that point, a real en dash does not match and is left
   alone);
4. handles `-DX <hex addresses>` (resolves each through the debug stack
   walker, then exits) and reads `-win`, `-fullscreen`, `-xpos` and `-ypos`;
   `-automatch` is recognised and ignored here;
5. loads `<language>Splash.jpg` (else `.bmp`) from disk with ATL's `CImage`,
   the language coming from `GetRegistryLanguage`;
6. takes a named mutex so only one copy runs (a second launch brings the
   first window forward and exits), then creates the window with
   `initializeAppWindows` (\ref page_startup_remastering);
7. creates `TheVersion` and hands its strings to `Debug::SetBuildInfo`;
8. runs the launcher handshake. It exits silently if the launcher is not
   running (`CopyProtect::isLauncherRunning` checks for the launcher's named
   mutex) or does not answer (`CopyProtect::notifyLauncher` signals the
   launcher's named event, waiting up to a minute, and waits for a reply
   message carrying a shared-memory handle). The result of
   `CopyProtect::validate`, which checks a string in that memory, is only
   stored (`CopyProtect::setVerified`) for later checks through
   `CopyProtect::isVerified`; it does not stop startup;
9. calls `GameMain`, which is three calls: `CreateGameEngine` (stored in
   `TheGameEngine`), `init(argc, argv)` and `execute()`. A `catch (...)`
   around the rest of `WinMain` swallows any exception that escapes.

## GameEngine::init {#page_startup_init}

`setName("GameEngine")` runs first. Everything from the core services
through the `-file`, headless and shell-map checks runs inside one `try`
block; a short tail runs after it.

**Core services first.** A provisional frame-rate cap is set and
`TheSubsystemList` is created, with the engine as its first member.
`InitRandom` seeds the random generators from the clock, the registry
language is stored, `TheFileSystem` comes from the `createFileSystem` factory,
and `TheNameKeyGenerator` and `TheCommandList` are created (plus a second
`CommandList` whose role is not yet known). Finally a CRC-computing `Xfer`
becomes the subsystem list's current xfer for the rest of the sequence
(\ref sub_save_load_crc).

**Then the subsystems.** `TheSubsystemLegend` is registered first and
`Data\INI\Default\SubsystemLegend.ini` is loaded directly. Next comes
`TheWritableGlobalData`, after which the command line is applied to it (see
\ref page_startup_modding). Then a `GameLODManager` is created and `Water.ini`,
`Fire.ini` and `Environment.ini` are loaded, each from `Data\INI\Default\`
first and then from `Data\INI\`. After that the long registration chain runs,
in this order (abridged; the names are the strings retail registers):

| Group | Registered, in order |
|---|---|
| Text and sound | TheGlobalLanguageData, TheGameText, TheAudio, TheEva |
| Rules data | TheScienceStore, TheUpgradeCenter, TheMultiplayerSettings, TheTerrainTypes, TheTerrainRoads, TheGlobalWeatherSystem, TheFunctionLexicon, TheModuleFactory, TheMessageStream, TheSidesList, TheCaveSystem, TheRankInfoStore, ThePlayerAITypeSet, ThePlayerTemplateStore |
| Combat and effects | TheFXParticleSystemManager, TheFXListStore, TheWeaponStore, TheObjectCreationListStore, TheLocomotorStore, TheSpecialPowerStore, TheDamageFXStore, TheArmorStore, TheBuildAssistant, TheCrowdResponseStore, the Living World auto-resolve stores, TheMissionObjectiveTracker, TheEmotionSystem |
| Objects and UI | TheThingFactory, TheStancesStore, TheFormationAssistant, TheAiOrdersManager, TheLightPointSystem, TheExperienceLevelSystem, TheDelayedExperienceLevelGrantSystem, TheAptPlayer |
| Living World and client | Living World template and region stores, TheLivingWorldManager, TheLivingWorldLogic, TheGameClient, TheLinearCampaignManager |
| Logic | TheAI, TheAerialPathfinder, TheSplineService, TheAttributeModifierStore, TheTaintManager, TheScriptEngine, TheLuaScriptEngine, TheTeamFactory, TheCrateSystem, ThePlayerList, TheGameLogic, TheRecorder, TheRadar |
| Rules and campaign | TheVictoryConditions, TheMetaMap, TheHouseColorSystem, TheMeshInstancingManager, TheLivingWorldCampaignManager, TheVictorySystem, TheFireLogicSystem, TheMineshaftPortalNetworkManager, TheSkirmishAIManager, TheArmyDefinitionManager, TheBaseTemplateLibrary, TheThreatFinderManager, TheAITargetHeuristicLibrary |
| After `CommandMap.ini` | TheActionManager, TheGameStateMap, TheGameState, TheGameResultsQueue, TheLivingWorldBuildingTemplateStore, TheAwardSystemManager, TheCreateAHeroManager, TheScoredKillEvaAnnouncerController, three auto-resolve schedule stores |

For many BFME 2-only entries the class behind the name is not yet
identified. If `TheAudio` reports its music is not loaded, the engine is
marked as quitting, but registration continues.

**Closing steps.** The CRC xfer is closed and its value, plus the
Create-a-Hero data's own CRC, becomes the global data's INI CRC.
`SubsystemInterfaceList::postProcessLoadAll` gives every subsystem a pass
after all data is in. The real frame-rate cap and the audio switches are
applied from the global data, `TheNetwork` is left null (Zero Hour: it is
created when a network game starts), and `TheMapCache` is built; a
map-cache-only run marks the engine as quitting (init still completes).
An initial `-file` naming a `.map` turns off the shell map and intro and,
unless an unidentified global-data flag is set, queues a new-game message
for it (Zero Hour: `MSG_NEW_GAME`); a multiplayer map gets a one-player
skirmish setup. A `-file` naming a `.rep` is played back as a replay.
The `_EA_RTS_HEADLESS` environment variable turns off the shell map and the
intro (and one more global-data flag whose meaning is not known); a shell
map that is not in the map cache turns off only the shell map.

**Failures.** A Direct3D initialisation error shows the localised
`ERROR:D3DFailurePrompt` / `ERROR:D3DFailureMessage` box and exits (if the
text system is not up yet, it goes to the crash handler instead); any other
`ErrorCode` is swallowed and startup continues. An `INIException` goes to
the crash handler with its failure message, and any other exception with a
fixed "uncaught exception" message.

**After the `try`.** The number of client frames per logic frame is
computed from the render and logic rate globals (see \ref page_frame_loop),
`resetAll` resets every subsystem, the control bar is hidden, the watchdog
thread is created and started if it is enabled, and the engine's timers are
initialised.

### How one subsystem is registered {#page_startup_registration}

Each registration goes through an `initSubsystem` template, which stores the
new object in its global and calls `SubsystemInterfaceList::initSubsystem`.
That function names the subsystem with its registration string, calls its
`init`, then asks it to load its data from the legend, and records it in the
list together with a small slot object that owns the subsystem (destroying
the slot deletes the subsystem and clears its global). Only if the legend
supplied nothing does it load the INI paths the caller passed;
`GameEngine::init` passes none. `GameEngine::init` also passes a CRC xfer to
some registrations and none to others, but that argument only reaches those
unused fallback paths. Which subsystems' legend data enter the INI CRC
therefore depends on the legend lookup
(`SubsystemInterface::loadIniFilesFromLegend`), which is not yet matched;
the current draft finds the `LoadSubsystem` block named after the subsystem
and loads every file and directory it lists through the list's CRC xfer, for
all of them. See \ref sub_ini.

## Shutdown {#page_startup_shutdown}

When `execute` returns, `WinMain` calls `CopyProtect::shutdown` (which
unmaps the launcher's shared memory) and deletes `TheVersion`. A global-data
flag whose meaning is not yet known then picks one of two paths.

- **Flag set.** If `TheGameEngine` is set, `shutdownGameEngine` tears
  down the engine, after which `WinMain` clears `TheGameEngine`. This path
  also deletes one further global whose class is not yet identified.
- **Flag clear.** `shutdownRenderDevice` (a provisional name; the donors'
  counterpart is WW3D's shutdown) stops any movie capture, ends the 1 ms
  timer period, shuts down the DirectX 8 wrapper unless WW3D runs in Lite
  mode, frees the default static sort lists and marks WW3D as no longer
  initialised. `WinMain` then deletes the audio manager (`TheAudio`, the
  object registered as "TheAudio") and clears it. The engine itself is not
  deleted on this path.

## BFME 2 and Zero Hour {#page_startup_zh}

- **Data loading.** Zero Hour has no legend: its `GameEngine::init` passes
  each subsystem's INI paths in code (for example `Data\INI\Weapon.ini`).
  BFME 2, like BFME 1, moves that list into `SubsystemLegend.ini`.
- **Many more subsystems.** The Living World, Lua, Apt, Create-a-Hero and
  skirmish AI library registrations are not in Zero Hour.
- **WinMain.** Zero Hour reads the ANSI `lpCmdLine`, always changes to the
  executable's folder and shows `Install_Final.bmp` through `LoadImage`.
  BFME 2 reads the Unicode command line, changes folder only when
  `lotrsec.big` is not found, and shows a per-language JPEG or BMP.
- **Engine lifetime.** Zero Hour's `GameMain` deletes the engine; BFME 2
  leaves teardown to `WinMain`.
- **Frame model.** Zero Hour runs logic once per client frame; BFME 2 runs
  logic at a lower rate than rendering (\ref page_frame_loop).

## Modding notes {#page_startup_modding}

- **Which INI files load is data.** Each subsystem reads the files and
  directories its `LoadSubsystem` block in
  `Data\INI\Default\SubsystemLegend.ini` lists, looked up by the registration
  name in the table above. There are no fallback paths in code, so a
  subsystem with no block loads nothing through registration. Files named in
  code here are only `SubsystemLegend.ini`, `Water.ini`, `Fire.ini`,
  `Environment.ini` and `CommandMap.ini`.
- **The order is code.** It decides which data exists when a later subsystem
  initialises. Adding a subsystem or reordering needs a code change.
- **Some rules data is checksummed.** `Water.ini`, `Fire.ini` and
  `Environment.ini` definitely load through the CRC xfer, and the
  Create-a-Hero data's own CRC is added to the INI CRC. `GameEngine::init`
  passes a CRC xfer to some registrations and none to others, but that
  argument only reaches the unused fallback paths. Which subsystems' legend
  data enter the INI CRC depends on the legend lookup, which is not yet
  matched; the current draft uses the list's CRC xfer for all of them.
  `SubsystemLegend.ini` and `CommandMap.ini` load without it.
- **Where the CRC is checked.** In BFME 2, `LANAPI::RequestGameJoin` sends
  the INI CRC with a LAN join request, and the online custom-match join
  refuses a room whose executable CRC, INI CRC or a third checksum differs
  ("GUI:JoinFailedCRCMismatch"). A client whose executable or checksummed
  INI data differ from the room's is therefore refused by the online join
  screen; a change outside those checksums is not shown to cause a
  mismatch. What a LAN host does with the CRC is not yet traced (Zero Hour's
  LAN check is commented out). Zero Hour also writes the INI CRC into replay
  headers, and its replay code reports, but does not refuse, a replay whose
  CRC differs.
- **Useful options** (handlers in `CommandLine*.cpp`; names from the retail
  option table):
  - `-mod <folder or .big>` records a mod folder or archive path in the
    global data, provided the path exists (a relative path is resolved
    against a game folder), and sets the same flag as `-preferLocalFiles`
    (Zero Hour's archive file system then mounts the archive; the BFME 2
    consumer is not yet traced);
  - `-file <map or replay>` sets the initial file handled at the end of
    init (above); `-noshellmap` skips the menu background map;
  - `-xres` and `-yres` set the resolution and `-win` windowed mode;
  - `-randomSeed` stores a seed value (Zero Hour uses it to seed game-logic
    random numbers from the map-select menu; the BFME 2 consumer is not yet
    traced);
  - `-Watchdog` or `-noWatchdog` decide whether `GameEngine::init` starts
    the watchdog thread at the end of initialisation.

  The dispatcher that reads the option table is not yet matched.
- **Read from disk before the file system exists:** the splash image and the
  window icon (`lotrbfme.ico`), so they cannot come from a BIG archive.

## Remastering notes {#page_startup_remastering}

- **Platform seam.** Window creation and the message loop are in
  `WinMain.cpp` and `Win32GameEngine`, but Win32 calls also appear elsewhere
  on this path: `GameEngine::init`'s Direct3D-failure message box and
  timers, the `CopyProtect` launcher code, and the render-device shutdown.
  Zero Hour: the engine's `create*` factory virtuals
  (`createGameLogic`, `createGameClient`, `createAudioManager`, `createRadar`
  and so on) are where the Win32, W3D and Miles implementations are chosen,
  so a new backend plugs in there. In BFME 2 most of `Win32GameEngine`'s
  overrides are not yet identified (\ref sub_w3d_rendering, \ref sub_audio).
- **Window.** The window is created for an 800 by 600 client area, placed
  near the screen centre unless `-xpos` and `-ypos` are given. The display
  resolution is not chosen here: `-xres` and `-yres` write it into the global
  data, which the renderer reads later (Zero Hour: `W3DDisplay::init`).
  In `WinMain.cpp`, windowed and fullscreen differ by window style, topmost
  z-order and whether the splash is painted (painting is switched off once
  the fullscreen window exists), and in fullscreen `WndProc` blocks moving,
  sizing, maximising, the system menu and monitor power-down. The splash is
  drawn at a fixed 800 by 600.
- **Launcher and copy protection.** The game refuses to start without the
  launcher handshake, and `WndProc` keeps listening for the launcher's
  message. A remaster must replace or remove `CopyProtect`.
- **Focus handling.** `WndProc` passes focus changes to the engine and the
  render device, and ignores `WM_CLOSE`.

## State of the reconstruction {#page_startup_state}

The startup path is largely matched through `GameEngine::init`, including
the command-line handlers and the launcher code. Still open: the main loop
(`GameEngine::execute` and `GameEngine::update`, described only by contract
on \ref page_frame_loop), the command-line dispatcher, the legend lookup,
and the identity of many registered BFME 2-only classes and of
`Win32GameEngine`'s factory overrides. `GameEngine` has no shared header yet:
each source file declares only the members it uses (\ref page_reading_code).
To refresh this picture, search `reverse/functions.csv` for the file names
above.

## Reading list {#page_startup_reading}

- \ref sub_engine_core; \ref sub_ini for the legend; \ref sub_network for
  how the INI CRC is used in multiplayer.
- Zero Hour, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/`:
  `GeneralsMD/Code/Main/WinMain.cpp`,
  `GeneralsMD/Code/GameEngine/Source/Common/GameMain.cpp` and
  `GeneralsMD/Code/GameEngine/Source/Common/GameEngine.cpp`.
