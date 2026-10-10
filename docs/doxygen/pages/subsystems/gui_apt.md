# GUI and the Apt UI {#sub_gui_apt}

BFME 2 draws its front end and most of its in-game HUD with **Apt**, EA's
user-interface player for Flash-derived movies scripted in ActionScript
bytecode. The game's C++
code does not lay these screens out. It loads a movie, registers native
callbacks under string names, and the movie's script calls them. Beside Apt
the **window system** that Zero Hour uses for all of its UI is still
present: `GameWindowManager`, the gadgets, `Shell`, the transitions and the
`ControlBar` with its command sets.

The API group is \ref grp_gui_apt. Where the UI runs in the frame is on
\ref page_frame_loop.

## Where it lives {#sub_gui_apt_where}

| Directory | What is there |
|---|---|
| `Code/Libraries/Source/Apt/` (with `AptObject/`, `AptValue/`, `string/`) | the Apt library: interpreter, value and object model, display lists, characters, rendering context, memory pools |
| `Code/Libraries/Source/EA/Apt/` (with `AptString/`) | more of Apt's string code, including the string class `EAStringC` and its string pool; string code is split between `Apt/string/` (the retail path) and `EA/Apt/` with `AptString/` |
| `Code/GameEngine/Source/GameClient/GUI/` | the window system (`GameWindow*`, `GameWindowManager*`, transitions, `HeaderTemplate*`, `IMEManager`, `WinInstanceData`), the game-side Apt player and screen factories |
| `GUI/GUICallbacks/Apt/` | one controller per Apt screen: `AptMainMenu`, `AptOptions`, `AptSkirmish`, `AptSaveLoad`, `AptLanLobby`, `AptOnlineCustomMatch`, `AptCreateAHero`, `AptPlayerStatus` and others |
| `GUI/GUICallbacks/Menus/` | files named after Zero Hour's window-layout menus, and the preference classes (`OptionPreferences`, `CustomMatchPreferences`, `QuickMatchPreferences`) |
| `GUI/Gadget/`, `GUI/Shell/`, `GUI/ControlBar/` | gadgets (buttons, list boxes, sliders, text entry), the shell screen stack and menu schemes, the control bar |
| `GUI/InGame/Tactical/`, `GUI/Palantir/` | the battle HUD pieces |
| `GUI/InGame/Strategic/` | War of the Ring HUD panels (more sit in `Common/`, see below) |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/` | W3D drawing for windows and gadgets, game fonts, and the Apt draw hooks |

`GUI/` rows are under `Code/GameEngine/Source/GameClient/`. Many HUD and Apt
units sit in `Code/GameEngine/Source/Common/`, `StrategicHUD.cpp` among
them, and many address-named staging units hold more
(\ref page_reading_code_staging): search by class.

## The Apt runtime {#sub_gui_apt_runtime}

- **Values and objects.** Every script value is an `AptValue`, reference
  counted and also marked by a garbage collector (retail asserts name an
  `AptGC.cpp`). Objects keep their properties, and their prototype
  (`__proto__`), in an `AptNativeHash`. Built-ins include `AptArray`,
  `AptDate` (the ActionScript `Date` methods) and `AptString`; retail
  assert file names add XML, colour, sound and text-format objects.
- **Interpreter.** `AptActionInterpreter` runs the bytecode through a table
  of opcodes, each with one static handler, `_FunctionAptAction<Name>`. The
  set covers Flash's actions (stack and arithmetic, `DefineFunction2`, `Try`,
  `Extends`, `InstanceOf`, frame and sprite control) plus Apt's fused forms
  such as `PushStringGetVar`, `CallFuncAndPop` and the dictionary pushes.
  Where checked, the opcode numbers are SWF's.
- **Display.** A loaded movie is a set of characters (`AptCharacter`);
  placed instances (`AptCIH`) live in display lists (`AptDisplayList`) and
  carry event handlers. Drawing walks them through an `AptRenderingContext`,
  which keeps stacks of vertex matrices and colour transforms.
- **Levels.** Movies load into numbered levels, as in Flash. Native code
  reaches into a movie by dotted path, for example
  `_level<n>.<prefix>_UpgradeIcon<i>`, and the library's
  `AptSetInternalVariable` and `AptGetInternalVariable` read and write
  variables on the level-0 movie.
- **Memory.** Apt has its own pool managers (`DOGMA_PoolManager`) and a
  collected allocator for values, and reports its total bytes at shutdown
  (\ref sub_memory).

## Screens, the shell and native callbacks {#sub_gui_apt_screens}

- **The shell** (`TheShell`) is Zero Hour's screen stack, at most 16 deep.
  BFME 2 pushes Apt screens by file name: `Shell::push` with `MainMenu.apt`
  brings up the main menu, and the shell creates each pushed screen through
  the window manager's `winCreateLayout`. `Shell::top` returns the top
  screen (`Shell::findScreenByFilename` survives from Zero Hour but has no
  known caller). Movies that code opens directly come from the `Apt\`
  folder.
- **Screen factories.** Screens are created through small factory
  functions, referenced from a table, that allocate the screen's controller
  object. In BFME 2 one controller class, `AptPlayerStatus`, serves both
  `PlayerStatus.apt` and `Objectives.apt`. BFME 1: the table pairs each
  screen file name with a factory, and both of those names point at one
  factory.
- **Callbacks by name.** A controller registers member functions under
  strings, and the movie's script calls them by those strings:
  `AptMainMenu::Skirmish` or `AptMainMenu::Options` for buttons,
  `Objective<n>` or `ScoreScreen:PlayerColor:<slot>` for values the movie
  asks native code for, and level-prefixed names such as
  `_level<n>_OnHelpBoxUnloaded` for clip events.
- **Render callbacks.** The battle HUD's palantir registers four callbacks
  that the movie calls with points: `AptPalantir::ClipRadar` takes the
  radar's rectangle from the movie, `RenderRadarViewBox` draws the radar
  view box, `RenderMovie` moves a movie window to a rectangle the movie
  supplies and refreshes it, and `RenderGlobe` draws a line between two
  points the movie supplies.
- **The game-side player.** `GameEngine::init` registers a subsystem named
  `TheAptPlayer`, and the callbacks are registered with that object. Its
  class is not yet proven; the WorldBuilder build calls it `AptPlayer`, with
  tables of commands, value queries, rollover handlers, custom renderers
  and timers. How the engine updates and draws it each frame is not yet
  reconstructed.

## The window system {#sub_gui_apt_windows}

Zero Hour's window system remains and is matched largely from the Zero Hour
and BFME 1 sources:

- `GameWindowManager` (`TheWindowManager`) owns every `GameWindow`, focus,
  modality and the destroy list, and parses `.wnd` layout scripts
  (`GameWindowManagerScript*`). Each window has a `WinInstanceData` and a
  set of system, input, tooltip and draw callbacks.
- Gadgets are windows with a class: push button, check box, radio button,
  list box, combo box, sliders, progress bar, static text, text entry and
  tab control. The W3D device layer draws them.
- `GameWindowTransitionsHandler` (`TheTransitionHandler`) plays named
  transition groups, `AnimateWindowManager` slides windows in and out, and
  `HeaderTemplateManager` and the font library supply fonts.
- `ControlBar` parses command buttons and command sets
  (\ref page_core_frameworks) and fills its contexts for the current
  selection: multi-select, structure inventory, construction, timers,
  observers. `ControlBarScheme` and `ShellMenuScheme` hold visual schemes.
- `IMEManager` is the Windows input-method editor support for text entry.

## In-game HUD {#sub_gui_apt_hud}

The battle HUD is built from Apt interfaces: the palantir (radar, player
statistics, radar pings), the side command bar, the spell book, the hero
buttons, planning mode, stance buttons and banners, in
`GUI/InGame/Tactical/` and `GUI/Palantir/`. The War of the Ring HUD is
`StrategicHUD` with one movie-clip wrapper per panel (army details, build
queue, region details, battle prompt, auto-resolve and others), split
between `GUI/InGame/Strategic/` and `Common/` and described on
\ref sub_living_world. Most of these class names come from the WorldBuilder
build and may still change. `InGameUI` (\ref sub_gameclient) owns
selection and the pending commands behind them.

## Lifecycle and entry points {#sub_gui_apt_entry}

| Function | Role |
|---|---|
| `GameEngine::init` | registers the `TheAptPlayer` subsystem (\ref sub_engine_core) |
| `GameClient::init` | creates `TheHeaderTemplateManager`, `TheWindowManager`, `TheIMEManager`, `TheShell` and `TheInGameUI`, in that order |
| `GameWindowManager::init` | creates `TheTransitionHandler`, which loads `Data\INI\WindowTransitions.ini` |
| `GameClient::update` | after input, `TheWindowManager->update`; later `Shell::update` and any pending display-mode change (skipped while an unnamed game-logic flag is set, unless a shell flag overrides it), then `InGameUI::update` |
| `GameWindowManager::update` | processes the destroy list, then updates the transitions |
| `GameWindowManager::reset` | destroys all windows, then resets the transitions |

## How it connects {#sub_gui_apt_connects}

- **Mostly client side.** The UI runs from `GameClient` on each machine
  (\ref sub_gameclient). The screens checked here change a running game by
  posting `GameMessage`s: the main menu's `StopGameMovie`, the quit menu's
  restart (a new-game message; a campaign restart goes through a direct
  call instead) and the control bar's command messages with object
  arguments (\ref page_core_frameworks). Some callbacks also call game
  systems directly: `AptMainMenu::ExitGame` raises a shell script event
  through the script engine, and the palantir's observer buttons call the
  player list.
- **Driven by the logic side too.** At mode changes the logic side drives
  the shell, for example by pushing `MainMenu.apt` when a new game returns
  to the shell.
- **Reads game state.** Screens and the HUD read players, game setup, saves,
  preferences and Living World state, and set up LAN and online games
  (\ref sub_rts_model, \ref sub_save_load_crc, \ref sub_living_world,
  \ref sub_network).
- **Draws through W3D** (\ref sub_w3d_rendering) and loads its data
  through the file system and INI parser (\ref sub_common_services,
  \ref sub_ini).

## BFME 2 compared with Zero Hour and BFME 1 {#sub_gui_apt_zh}

- **Zero Hour has no Apt.** Its menus are `.wnd` layouts driven by
  `GUICallbacks/Menus/*.cpp`, and its HUD is the control bar.
- **BFME 1 already uses Apt.** Open-BFME-1 reconstructs an Apt library and
  an `AptPalantir` with the same radar, movie and globe render callbacks,
  plus `AptMainMenu` and the screen factories.
- **HUD classes.** In BFME 1 the spell book and hero selector are part of
  `AptPalantir`; BFME 2 has separate classes for them (names from the
  WorldBuilder build). Open-BFME-1 has no `StrategicHUD` or Create-a-Hero
  source.
- **Font substitution.** BFME 2 loads `data\ini\fontsubstitution.ini` in
  `FontLibrary::init` (Zero Hour: empty). BFME 1 already loads the same
  file from a function Open-BFME-1 has not yet named.

## Modding notes {#sub_gui_apt_modding}

- **Data-driven:** the movies (`*.apt` from the `Apt\` folder; the archive
  file system also mounts every `*.big` in `apt\`), their layout, art and
  ActionScript. Screen files named in code include `MainMenu.apt`,
  `Options.apt`, `Skirmish.apt`, `SaveLoad.apt`, `LoadScreen.apt`,
  `Palantir.apt`, `StrategicHUD.apt`, `CreateAHero.apt` and `ScoreScreen.apt`.
  INI data: `CommandButton.ini`, `CommandSet.ini`, `ControlBarScheme.ini`,
  `WindowTransitions.ini`, `HeaderTemplate.ini` and
  `fontsubstitution.ini`.
- **Hard-coded:** the screen factory table, every native callback and its
  string name, and fixed row counts such as twelve objective rows
  (`Objective1` to `Objective12`, each with an `Objective<n>Status` twin)
  and eight player-colour slots (`ScoreScreen:PlayerColor:0` to `7`). A
  movie can restyle a screen but cannot add a game action that no
  controller registers.
- **Names are the contract.** Binding is by string in both directions, so a
  replacement movie must keep the callback names it calls and the clip
  names and paths that native code looks up.
- **Lockstep.** ActionScript's random numbers (`random` and `Math.random`)
  come from a separate Mersenne Twister generator, not the logic one. Screens mostly act on the game through
  `GameMessage`s, but some callbacks also call the script engine directly,
  for example to raise shell script events. Treat any UI change that
  touches logic-side state as a lockstep risk.
- **INI CRC.** `CommandButton.ini`, `CommandSet.ini`,
  `ControlBarScheme.ini`, `HeaderTemplate.ini` and `fontsubstitution.ini`
  load without the CRC `Xfer`, so the INI CRC check (\ref sub_ini) does
  not cover them. Whether a mismatch between machines would desync is not
  yet established.

## Remastering notes {#sub_gui_apt_remastering}

- **Two UI stacks.** A new UI must replace or host both the Apt player and
  the window system; both draw through the W3D device layer, which is where
  a new renderer plugs in.
- **Resolution.** `.wnd` layouts store a creation resolution and are
  scaled with separate width and height factors, so a layout authored at
  one aspect ratio is stretched non-uniformly at another. How the Apt
  player fits a movie to the screen has not been traced. A display-mode
  change deletes and recreates the shell on `MainMenu.apt` rather than
  re-laying out the open screens.
- **Hosting the movies.** Keeping the shipped movies means keeping an Apt
  interpreter with this bytecode and value model, plus the named callbacks
  and render hooks. Replacing them means reimplementing each controller's
  callbacks against the game.
- **Platform seams:** `IMEManager` (Windows IME), the window resize in
  `AptMainMenu::ResetResolution` (Win32 calls for windowed mode), and the
  online screens over GameSpy and EA's FESL services (\ref sub_network).

## State of the reconstruction {#sub_gui_apt_state}

The Apt library is well named from retail asserts and from the symbols of
another EA game's Apt library (version 0.19.03, The Godfather for Xbox),
many of whose function bodies match BFME 2's. That BFME 2 uses the same Apt
release is not established, and many Apt helpers still have address names.
The window system follows Zero Hour closely and is largely matched. Screen
controllers and the HUD mix real names, names from the WorldBuilder build
and address names, and their classes have no shared headers yet
(\ref page_reading_code). Coverage changes daily: search
`reverse/functions.csv` and `reverse/link_status.csv` for the paths above.

## Reading list {#sub_gui_apt_reading}

- Zero Hour: `Include/GameClient/` (`GameWindowManager.h`, `GameWindow.h`,
  `Shell.h`, `ControlBar.h`) and `Source/GameClient/GUI/` under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/`.
- BFME 1: Open-BFME-1's `game/Libraries/Source/Apt/` and
  `game/GameEngine/Source/GameClient/GUI/`.
- `reverse/apt_donor_01903.json`: the symbol evidence for Apt names.
