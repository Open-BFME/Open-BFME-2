# Glossary {#page_glossary}

The words this guide uses, in five groups: how the engine is built, the game
data that modders edit, what keeps multiplayer and saves consistent, the
platform libraries a remaster would replace, and the vocabulary of the
reconstruction project itself. Each entry links to the page that explains
it. A statement marked "Zero Hour:" comes from the Zero Hour source that
BFME 2 descends from and is not yet confirmed in BFME 2 itself.

## Engine structure {#page_glossary_engine}

- **Device layer**: `Code/GameEngineDevice/`, the platform half of the
  engine: `Win32Device` (input and the local file system), `W3DDevice`
  (rendering and the W3D draw modules) and `MilesAudioDevice`. The engine
  above it creates these through virtual factory methods, so this is where
  a replacement backend plugs in. See \ref page_architecture.
- **GameClient**: the per-machine presentation side: drawables, the
  display, UI and input in `TheGameClient`; audio is a separate subsystem,
  `TheAudio`. Zero Hour: by design the client changes the simulation only
  by sending messages. See \ref sub_gameclient.
- **GameEngine**: the object that creates every subsystem in
  `GameEngine::init` and then runs the main loop (`TheGameEngine`); on
  Windows it is a `Win32GameEngine`. See \ref sub_engine_core.
- **GameLogic**: the deterministic simulation half: objects, AI, scripts,
  the map (`TheGameLogic`). Every peer runs it identically. See
  \ref sub_gamelogic_map.
- **Logic frame and phase**: one tick of the simulation.
  `GameLogic::update` takes a phase number from 1 to 6. Phase 1 runs the
  map and Lua scripts and executes the queued commands. Phase 2 updates
  the partition and collision managers. Phases 3 to 6 run the
  update-module lists, and phase 5 also updates the AI and the remaining
  logic subsystems (shroud, weapon and locomotor stores, team factory, the
  destroy list and others). Retail's timing globals hold 30 client frames
  and 5 logic frames per second. That ratio and BFME 1's frame loop
  suggest one phase per client frame, six per logic tick, but BFME 2's
  caller is still being reverse engineered. See \ref page_frame_loop.
- **MemoryPool**: BFME 2's heaps are reached through an exported
  `MemoryPool` API (`MemoryPool::_Allocate`, `_Free` and the rest) over
  EA's `GeneralAllocator`, not Zero Hour's GameMemory implementation. How
  much of Zero Hour's pooled-object layer remains is not yet established.
  See \ref sub_memory.
- **SAGE**: EA's RTS engine line: Generals, Zero Hour, BFME, BFME 2 and
  The Rise of the Witch-king. Its rendering and utility layer is Westwood's
  W3D/WWVegas.
- **Subsystem**: an engine singleton derived from `SubsystemInterface`.
  `GameEngine::init` creates them in a fixed order through
  `SubsystemInterfaceList::initSubsystem`, which names it, calls its
  `init` and loads its INI data. See \ref page_startup.
- **SubsystemLegend.ini**: `Data\INI\Default\SubsystemLegend.ini`, loaded
  first. Its `LoadSubsystem` blocks name, per subsystem, the INI files and
  directories to load. `SubsystemInterfaceList::initSubsystem` loads a
  subsystem's legend entry first and falls back to caller-supplied paths
  only when the entry lists nothing. `GameEngine::init` supplies no such
  paths, so in BFME 2 the INI that `initSubsystem` loads for a subsystem
  comes only from its `LoadSubsystem` block. A subsystem's own `init` can
  still parse INI itself (`InGameUI::init` parses its InGameUI
  definition). Only SubsystemLegend.ini itself, Water/Fire/Environment.ini
  (Default copy then override) and `CommandMap.ini` are loaded by name in
  `GameEngine::init`. Zero Hour has no legend.
- **TheXxx**: the global pointer to a singleton, such as `TheGameLogic` or
  `TheWeaponStore`. `GameEngine::init` registers each subsystem under a
  name of this form, which is how retail's strings identify them.
- **Zero Hour (GeneralsMD)**: Command & Conquer Generals: Zero Hour, whose
  source EA released under the GPL. BFME 2 keeps its layout and much of
  its code; the copy used here is under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/`.

## Game data and content {#page_glossary_data}

- **Apt**: EA's Flash-derived UI runtime (`Code/Libraries/Source/Apt/`).
  It plays `.apt` movies with an ActionScript interpreter; BFME 2's menus
  and HUD are Apt movies driven by game-side controller classes. Zero Hour
  has no Apt. See \ref sub_gui_apt.
- **BIG archive**: EA's `.big` resource archive. Retail's archive loader
  mounts `*.big` from the game directory, the `apt\` directory and the
  language archives under `lang\`, and `WinMain` looks for `lotrsec.big`
  to tell whether it is already in the game directory. See
  \ref sub_common_services.
- **CommandButton / CommandSet**: an INI-defined UI button and a named set
  of buttons. Zero Hour: a button names a command, its target and its
  look, an object's template names its set, and the `CommandSetUpgrade`
  module (which BFME 2 also registers) swaps the set at run time. See
  \ref page_core_frameworks.
- **CreateAHero**: BFME 2's custom hero creator (`TheCreateAHeroManager`).
  Its INI loads feed the INI CRC, and `GameEngine::init` adds the manager's
  own CRC on top.
- **FieldParse table**: how INI fields reach C++: each entry pairs a field
  name with a parse function and the offset of the member it fills, and a
  module data class's `buildFieldParse` combines several such tables. The
  tables therefore also describe the class layout. See \ref sub_ini.
- **FXList / ObjectCreationList (OCL)**: named INI lists of effects to play
  and of objects to spawn (`TheFXListStore`, `TheObjectCreationListStore`).
- **FXParticleSystem**: BFME 2's particle system, assembled from emitter,
  volume, velocity, physics and draw modules. Its manager,
  `TheFXParticleSystemManager`, takes Zero Hour's `ParticleSystemManager`
  place in the init order. See \ref sub_gameclient.
- **Horde**: a BFME battalion: many soldiers managed as one selectable
  object through `HordeContain` and its variants (horse, siege, transport
  and garrison hordes, among others). See \ref sub_objects_modules.
- **INI**: the text data format under `Data\INI\`. Most game content is
  INI: objects, weapons, armor, upgrades, sciences, special powers,
  locomotors, FX and command buttons. Some files load a default copy first
  and an override second, for example `Data\INI\Default\Water.ini` then
  `Data\INI\Water.ini`. See \ref sub_ini.
- **Living World / War of the Ring**: BFME 2's strategic campaign on a
  territory map (`TheLivingWorldLogic`, `TheLivingWorldManager` and a
  family of auto-resolve stores whose INI feeds the INI CRC). See
  \ref sub_living_world.
- **Lua**: BFME 2 embeds Lua 4.0.1 with EA's own changes;
  `TheLuaScriptEngine` updates in the first phase of every logic frame,
  next to the map script engine. Zero Hour has no Lua. See
  \ref sub_scripting.
- **Map script**: the condition-and-action scripts a map carries, run by
  `TheScriptEngine` in the first phase of each logic frame. Zero Hour: they
  are written in WorldBuilder and saved in the map file. See
  \ref sub_scripting.
- **Module / ModuleData / ModuleFactory**: a component that gives a thing
  behaviour (update, body, contain, die, upgrade, draw and so on), the
  settings parsed for it from INI, and the registry that creates both by
  name. Only the module names registered in code exist; INI chooses and
  configures them. See \ref sub_rts_model and \ref sub_objects_modules.
- **NameKey**: a small integer interned for a string, used for fast
  comparison of names such as module tags. See \ref sub_common_services.
- **Science / Upgrade / SpecialPower**: INI-defined sciences, upgrades and
  special powers, held in `TheScienceStore`, `TheUpgradeCenter` and
  `TheSpecialPowerStore`. See \ref page_core_frameworks.
- **String table**: player-visible text, looked up by label (such as
  `GUI:FullGameName`, which also titles the window) from a compiled `.csf`
  table or a text `.str` file; a map can bring its own string file.
- **Thing / Object / Drawable**: `Object` (the logic entity) and
  `Drawable` (its client-side visual twin) both derive from `Thing`, which
  holds shared queries such as kind-of tests and height above terrain.
  See \ref sub_objects_modules.
- **ThingTemplate / ThingFactory**: one INI object definition, and the
  store that holds the templates and creates objects from them
  (`TheThingFactory`). See \ref sub_rts_model.
- **Weapon / Armor / Locomotor**: INI definitions of how things attack,
  take damage and move, held in `TheWeaponStore`, `TheArmorStore` and
  `TheLocomotorStore`. See \ref page_core_frameworks.

## Determinism, multiplayer and saves {#page_glossary_sync}

- **CRC**: a checksum that proves two copies agree. The logic CRC
  (`GameLogic::getCRC`) runs the objects, the logic random seed, the
  partition and shroud managers, the players and the AI through an Xfer
  that checksums instead of writing. The INI CRC is collected by a CRC
  writer that `GameEngine::init` installs while it registers subsystems
  and loads Water/Fire/Environment.ini; the CreateAHero manager's own CRC
  is added at the end. A LAN join request carries the INI CRC plus a
  16-byte executable check value (named after Zero Hour's exeCRC) and a
  third BFME-specific value. Zero Hour's host-side CRC check on join is
  commented out; whether BFME 2 enforces one is not yet established. See
  \ref sub_save_load_crc.
- **CommandList / GameMessage / MessageStream**: `GameEngine::init`
  creates `TheMessageStream` and `TheCommandList`, and phase 1 of
  `GameLogic::update` executes the command list's messages and clears it.
  Zero Hour: input and UI post `GameMessage`s to the message stream, whose
  translators turn them into commands on the command list, which the
  network synchronises. See \ref page_core_frameworks.
- **Desync**: peers whose simulations have diverged. In multiplayer,
  `GameLogic::update` sends its logic CRC as a message at a frame interval
  the game settings choose, so peers can compare.
- **Float mode**: `setFPMode` sets the x87 FPU to 24-bit precision with
  round-to-nearest. The logic update, the CRC and INI loading call it so
  every machine computes the same floats.
- **GameState**: the save-game manager (`TheGameState`). Retail's save
  extensions are `.BfME2Campaign`, `.BfME2Skirmish`, `.BfME2WotR` and
  `.BfME2WotRMP`. See \ref sub_save_load_crc.
- **Lockstep**: the multiplayer model. Peers exchange commands (plus CRC
  and frame-timing reports) rather than object state. Zero Hour: each peer
  runs the same logic frames in the same order, so the same commands give
  the same result. See \ref sub_network.
- **Logic random values**: the game keeps separate random streams for
  logic, client and audio (`GetGameLogicRandomValue`,
  `GetGameClientRandomValue`, `GetGameAudioRandomValue`). The logic
  stream's seed is part of the logic CRC. Zero Hour: the streams are kept
  apart so that client-side effects cannot disturb the logic's sequence.
- **Packet router**: in BFME 2's lockstep, the one peer whose connection
  paces the game by elapsed time; the other peers admit frames against a
  frame ceiling (`docs/bfme2-network-timing-path.md`).
- **Recorder / replay**: `TheRecorder` writes the command messages to a
  replay file and plays them back; `GameEngine::init` can start a `.rep`
  file directly.
- **Snapshot**: the base of everything saved or checksummed. BFME 2's
  Snapshot has three virtual slots: load post-process, a snapshot-name
  getter and xfer (retail's exported overrides spell them
  `LoadPostProcess`, `GetSnapshotName` and `DoXfer`). Unlike Zero Hour's
  it has no separate `crc` method.
- **Xfer**: the serialisation visitor. One `xfer` method per snapshot
  saves, loads or checksums it, depending on the Xfer it is given
  (`Xfer::IsLoading`, `IsStoring`, `IsCRC`, `IsLightCRC`). A snapshot can
  write a version record (Xfer's Version type) ahead of its fields. Zero
  Hour: loading refuses a version newer than the code knows.

## Platform and libraries {#page_glossary_platform}

- **DirectInput**: keyboard and mouse input through `dinput8.dll`.
- **DX8Wrapper**: W3D's device wrapper. It keeps its Direct3D 8 name, but
  BFME 2 loads `Direct3DCreate9` at run time and imports `d3dx9_27.dll`, so
  the renderer is Direct3D 9. See \ref sub_w3d_rendering.
- **GameSpy / FESL / DirtySock**: the online stack: the vendored GameSpy
  SDK for lobbies, chat and server lists, and EA's FESL services over the
  DirtySock networking library. See \ref sub_network.
- **Miles**: the Miles Sound System (`mss32.dll`), the audio backend
  behind `MilesAudioManager`. See \ref sub_audio.
- **STLport**: the C++ standard template library retail was built with
  (namespace `_STL`). The C runtime is Microsoft's `msvcr71.dll`.
- **VP6**: an On2 VP6 decoder is linked into `game.dat`
  (`Code/Libraries/Source/VP6/`; retail reports "Could not open VP6 video
  file"). Retail still carries Bink-named movie window code (`BinkMovie`,
  an Apt Bink movie callback) but imports no Bink DLL; how the two relate
  is not yet established. Zero Hour: videos use Bink.
- **W3D / WW3D2**: Westwood 3D, the mesh, hierarchy, animation and
  rendering library, and its asset format. See \ref sub_w3d_rendering.
- **WWLib / WWVegas**: Westwood's foundation libraries (containers, files,
  math, debug) under `Code/Libraries/Source/WWVegas/`. See
  \ref sub_wwlib_thirdparty.

## Reconstruction terms {#page_glossary_project}

- **Canonical class**: a class with one shared header, registered in
  `reverse/canonical_classes.csv`, in place of per-file partial views.
- **Donor / reference**: existing source used as a starting point: Zero
  Hour, or Open-BFME-1's reconstructed BFME 1 (`reference/open-bfme-1/`).
  Its names and layouts are hypotheses until BFME 2 evidence confirms them.
- **Export**: a symbol in the retail export table (`reverse/exports.csv`).
  Exported names are authoritative.
- **Fold**: identical bodies the linker merged, so one retail address
  serves several names.
- **Generated placeholders**: `Code/gen_asm/`, `Code/gen_small/` and
  `Code/masm_dumps/`, byte-true stand-ins for code not yet written as C++.
  See \ref page_reading_code_staging.
- **Ledger**: the CSV files under `reverse/`, chiefly `functions.csv`, one
  row per recovered function. They are large; search them with `rg`.
- **Link census**: `reverse/link_status.csv` records, per source file,
  whether its objects link under the census rules (no unresolved names,
  losing COMDAT copies or wrongly selected definitions); see
  `tools/link_census.py`.
- **Matched**: a row whose C++ compiles to exactly the retail bytes. It
  proves bytes, not names or meaning.
- **Pin**: a line in `reverse/symbols.csv` proposing the retail address a
  name resolves to when compiled code calls it. It is a candidate list, so
  a pin that byte-matches still does not prove the name.
- **Placeholder name**: a name that admits the identity is unknown, such as
  an address-named function, class or file. Expect it to change.
- **Retail**: the shipped BFME 2 1.06 engine, `game.dat`; the ground truth.
  `game.dat` is started by a separate launcher; `WinMain` performs a
  handshake with it.
- **Row**: one line of `reverse/functions.csv`: a name, a retail address
  and size, a source file and a status.
- **RVA**: an address relative to the image base, the form the ledger uses.
  Source comments sometimes give absolute or BFME 1 addresses instead.
- **Shim**: a header overlay under `reference/shims/` that models a BFME 2
  layout in front of the Zero Hour headers.
- **tu_map**: `reverse/tu_map.csv`, the project's proposed assignment of
  retail code ranges to `Code/` translation units. Each row carries a
  confidence (`proposed`, `approved` or `displaced`) and its evidence; it
  is a working hypothesis, not EA's original file list.
- **View**: a file-private partial declaration of a class holding only
  the members one function touches; views may name a member differently.
- **WorldBuilder / WB lead**: the map editor, an unoptimised debug build
  of the same source tree, whose bodies read closer to the C++ and help
  identify game functions (`tools/wb_show.py`). A WB lead is a candidate
  name, not a confirmed one.

## Modding notes {#page_glossary_modding}

- Content is data: INI (through the legend and the stores above), maps
  with their scripts, Apt movies, string tables, W3D assets and BIG
  archives. New behaviour needs code: INI can only pick from the modules,
  block keywords and field names the engine registers.
- In BFME 2 the INI files loaded for each registered subsystem come
  entirely from SubsystemLegend.ini: `GameEngine::init` passes no fallback
  paths, so removing or emptying a subsystem's `LoadSubsystem` block means
  no INI is loaded for it (apart from any its own `init` parses). Only the
  legend itself, Water/Fire/Environment.ini (Default copy then override)
  and `CommandMap.ini` are loaded by name.
- Changing anything the logic reads (objects, weapons, upgrades, scripts,
  Lua) changes the simulation, so every player needs the same data.
  Changing startup INI can also change the INI CRC that a LAN join
  request carries.
- Saves store xfer'd state. Changing what a snapshot writes without
  bumping its version record breaks existing saves; with a bump, code can
  read older versions conditionally, as BFME 2's own xfer methods do (for
  example `AutoHealBehavior::xfer`). Zero Hour: a version newer than the
  code knows is refused, and a replay stores only the commands and
  re-simulates them, so it plays back correctly only with the same data
  and code.

## Remastering notes {#page_glossary_remaster}

- The platform seams are the device layer (`Win32Device`, `W3DDevice`,
  `MilesAudioDevice`), `DX8Wrapper` over Direct3D 9, DirectInput 8,
  Winsock with GameSpy and DirtySock, and the VP6 decoder.
- The client-frame count per logic frame is derived from two globals (30
  FPS and 5 logic frames per second in retail), and `GameLogic::update`
  runs in six phases. BFME 1 schedules one phase per client frame, which
  ties phase timing to the render-to-logic ratio. Changing the render rate
  therefore interacts with logic scheduling and is not a purely
  client-side change; how to decouple them is not yet established (see
  \ref page_frame_loop). `GameEngine::init` also sets a separate frame cap
  field to 45 (Zero Hour: the engine's maximum frames per second).
- The engine is 32-bit x86 code built with Visual C++ 7.1 and STLport.
  The engine's own allocator is the exported `MemoryPool` API over EA's
  `GeneralAllocator`; the CRT heap (`msvcr71.dll`) and Win32 heaps are
  imported as well.

## Maturity {#page_glossary_maturity}

The engine terms are settled: they rest on retail strings, exports and the
Zero Hour lineage. Most matched code by size carries real names, but many
smaller functions still have placeholder names, and some class names come
from WorldBuilder leads that may change; \ref page_reading_code explains
how to tell them apart.
