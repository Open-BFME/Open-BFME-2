# Modding guide {#page_modding}

This page is for people who change BFME 2's content: units, powers, maps,
scripts, the interface and text. It follows content from the files on disk
(\ref page_modding_files) through INI templates (\ref page_modding_ini)
and their modules (\ref page_modding_modules) to map scripts and Lua
(\ref page_modding_scripts), the interface (\ref page_modding_ui) and
strings (\ref page_modding_strings). It then lists what a mod must keep
intact so multiplayer, replays and saves keep working
(\ref page_modding_rules). Statements taken from Zero Hour or BFME 1 are
labelled as such, and details not yet established are marked.

## Files and BIG archives {#page_modding_files}

`GameEngine::init` stores the language name it reads from the registry
(the buffer holds `English` until then), creates `TheFileSystem`, and then
runs a set-up step that creates two backends: one that reads loose files
on disk and one that reads BIG archives. That step mounts the archives in
this order:

1. every `*.big` in the `lang` folder whose name starts with the language
   name;
2. `lang\EnglishAudio.big`, but only when `lang\<language>Audio.big` is not
   found on disk (the test is the disk backend's existence check, not an
   archive lookup);
3. every `*.big` in the game folder;
4. every `*.big` in the `apt` folder.

Within one folder the archives are taken in case-insensitive name order.
The first group is mounted with a flag the others do not get. Zero
Hour: that flag lets an archive replace files that earlier archives
already supplied; without it the first archive that supplies a path keeps
it, so archive names decide which copy wins. Following that Zero Hour
rule, because the language archives are mounted first they would win over
the game-folder and `apt` archives, with later language-archive names
winning among themselves. BFME 2's directory-tree code has not been
identified yet, so treat this rule as Zero Hour's until it is.

**Archives or loose files first.** By default `FileSystem::openFile`
searches the mounted archives first and loose files on disk only after
that, so an archived file wins over a loose file with the same path. When
the prefer-local flag is set, the order flips: loose files are tried first
(first under an optional language directory set elsewhere, whose value
is not yet established, then as `lang\<language>\<file>`, then as the
plain path) and the archives last. A request that creates a file (Zero
Hour's `CREATE` access bit) never goes to the archives. The flag is set
by:

- `-mod` (`parseMod`), always;
- `-preferLocalFiles` (`parsePreferLocalFiles`);
- the set-up step above, when `shaders.big` is not found on disk;
- a setter that also stores the language directory and mounts every
  `*.BIG` in it with the first group's flag; what calls it is not yet
  identified.

The global names `TheArchiveFileSystem` and `TheLocalFileSystem` in the
current sources are provisional and point at the opposite backends:
`TheArchiveFileSystem` holds the disk backend and `TheLocalFileSystem` the
archive backend.

`-mod` takes a folder or a single `.big` file. A relative path is joined
to a base folder held in the global data (in BFME 1 it is the user data
folder). A folder is recorded as the mod directory, a file as the mod
archive. Zero Hour: `ArchiveFileSystem::loadMods` then mounts the mod
archive, and every `*.big` in the mod folder, with the replace flag set,
so mod files win over the game's. In BFME 2 the code that consumes the two
settings has not been identified yet.

\ref sub_common_services covers the file system classes.

## INI definitions {#page_modding_ini}

`GameEngine::init` loads `Data\INI\Default\SubsystemLegend.ini` before any
other INI file. Each subsystem's INI files come from its `LoadSubsystem`
entry in the legend. `SubsystemInterfaceList::initSubsystem` would load
code-supplied paths when the legend loader reports that it loaded nothing,
but `GameEngine::init` supplies none, so the legend is the only source of
each store's INI file list (Zero Hour, which has no legend, wrote these
paths in code). The legend loader's BFME 2 body is not reconstructed yet.
Compared with BFME 1's it adds a check for a `mithriledition.txt` file and,
according to `reverse/re_attempts.log`, an exclusion list; what either
changes is not yet understood.

Besides the legend itself, `GameEngine::init` names INI files directly:
`Water.ini`, `Fire.ini` and `Environment.ini`, each a base file in
`Data\INI\Default` followed by an overlay of the same name in `Data\INI`
and read through the CRC writer (\ref page_modding_rules), and
`CommandMap.ini`, read without it.

The stores `GameEngine::init` creates include, in creation order, sciences, upgrades,
multiplayer settings, terrain types and roads, rank information, player
templates (factions), FX lists, weapons, object creation lists,
locomotors, special powers, damage FX, armor, the Living World auto-resolve
stores, the thing factory (object templates), experience levels, the
Living World player templates and the CreateAHero manager. The full order
is on \ref page_startup.

Parsing is strict. An unknown field raises an error naming the block, file
and line; an unknown block keyword raises one naming the block and file.
Either stops loading. Very long lines are cut; the details are on
\ref page_core_frameworks.

**Per-map overrides.** When a map loads, the game logic looks in the
map's folder for `map.ini` and `solo.ini` and loads each one in
override mode, without the CRC writer, then loads `map.str` as the map's
string table. A separate step loads the folder's `ambientlightmap.tga`
into the terrain, if present.

\ref sub_ini covers the parser, the legend and the stores.

## Objects and modules {#page_modding_modules}

An `Object` block defines a thing template. Its behaviour comes from
modules: each `Behavior = ModuleName ModuleTag` (or `Body = ...`) line
starts a nested block whose fields fill that module's data.
`ThingTemplate::parseModuleName` enforces the rules, with these retail
error messages:

- a `Body` line must name a body module, and a `Behavior` line must not;
- in an override file such as `map.ini`, new modules need `AddModule`;
- `ReplaceModule` must use a module of the same type and give the
  replacement a new, unique tag.

Zero Hour: `Draw` and `ClientUpdate` lines attach presentation modules the
same way.

**The module catalogue is fixed in code.** `ModuleFactory::init` registers
309 module names: 297 logic modules (behaviours, bodies, updates, contains,
special powers, upgrades and so on), 6 client updates and 6 client
behaviours, the last a module type that Zero Hour does not have (BFME 1
already uses it, for example `AnimationSoundClientBehavior`).
`W3DModuleFactory::init` adds 20 draw modules, among them
`W3DDefaultDraw`, `W3DScriptedModelDraw`, `W3DHordeModelDraw` and
`W3DTornadoDraw`. A mod can combine and configure these modules freely,
but a module name that is not registered cannot be used: new behaviour
needs new code. The registrations, with their
module types and interface masks, are listed in
`reverse/module_factory_registrations.csv`.

Weapons, armor, locomotors, special powers, upgrades, sciences, FX lists and
object creation lists are separate definitions that objects and modules
refer to by name; \ref page_core_frameworks introduces them and
\ref sub_objects_modules and \ref sub_rts_model cover the code.

**Command sets.** `CommandButton` and `CommandSet` definitions connect the
interface to logic commands. A command set holds 32 button slots, and
`CommandSet::getCommandButton` does not check the index. BFME 2 adds a run-time
substitution: before using a slot, it asks the game logic whether a
replacement button is registered for that set name and slot. Where those
replacements come from is not yet established.

## Map scripts and Lua {#page_modding_scripts}

Map scripts are made in WorldBuilder and stored in the map; the
`ScriptEngine` evaluates their conditions and runs their actions during the
logic update. The available condition and action types are tables built in
code, so a new type needs new code. \ref sub_scripting has the details.

BFME 2 also runs Lua 4.0.1. `LuaScriptEngine` registers 41 native
functions (for example `ObjectHasUpgrade`, `ObjectGrantUpgrade`,
`ObjectDoSpecialPower`, `ObjectBroadcastEventToAllies` and
`GetRandomNumber`), then loads `Data\Scripts\Scripts.lua` and
`Data\Scripts\ScriptEvents.xml`. `GetRandomNumber` draws from the logic
random stream, so Lua that runs in the simulation is part of the lockstep
contract like any other logic code.

## Interface {#page_modding_ui}

Front-end screens and parts of the in-game interface are Apt movies,
EA's Flash-derived format, and the `apt` folder's archives are mounted
with the rest (\ref page_modding_files). A movie's look, layout and
ActionScript are data. Screens are C++ objects, created from tables of
factory functions, that register named callbacks with the Apt player for
their movies to call. Whether a movie can trigger game actions beyond
those callbacks is not yet established. Which in-game pieces still use
the older window manager is covered on \ref sub_gui_apt.

## Strings {#page_modding_strings}

`GameTextManager::init` loads the main string table, from a compiled CSF
file or a text STR file, and sets the window title from the
`GUI:FullGameName` label. `GameTextManager::initMapStringFile` loads a map's
`map.str` alongside it. A lookup searches the main table first and the
map's table second, so a map can add labels but cannot replace existing
ones. A label found in neither is shown as the word MISSING followed by
the label's name, which makes missing strings easy to spot.

## Rules a mod must respect {#page_modding_rules}

**Lockstep determinism.** Multiplayer sends only commands; every machine
runs the same simulation and must reach the same result. Anything on the
logic side must therefore be identical everywhere: logic INI values,
scripts and Lua, the order and number of logic random draws, and
floating-point behaviour. Visual and audio code use separate random
streams and may differ. \ref page_core_frameworks explains the random
streams and the floating-point mode, and \ref page_frame_loop the frame
model.

**Data CRC.** `GameEngine::init` creates a CRC writer and installs it as
the subsystem list's xfer from just before the legend is loaded until after
the last INI store is created. `Water.ini`, `Fire.ini` and
`Environment.ini` (base and overlay) are loaded through that writer
directly, and its result plus the CreateAHero manager's CRC is stored as
the INI CRC. BFME 1's legend loader passes the subsystem list's xfer to
every file it loads; if BFME 2's does the same, legend-listed files feed
the INI CRC too. BFME 2's legend loader is not yet reconstructed and has
extra gate and exclusion logic, so which legend files feed BFME 2's INI
CRC is not yet established.

A LAN join request carries the INI CRC, together with a 16-byte block the
donor sources call the executable CRC and one further BFME CRC. How the
BFME 2 host uses them is not yet established. (Zero Hour: the LAN host's
CRC check is commented out; the online lobby client refuses to join a room
whose CRCs differ from its own.)

**Game-state CRC.** During play `GameLogic::getCRC` computes a CRC of the
logic state, including the logic random seed. (Zero Hour: peers exchange
these CRCs and compare them to detect a desync.)
\ref sub_save_load_crc covers the check.

**Saves and replays.** Save files use one extension per mode:
`.BfME2Campaign`, `.BfME2Skirmish`, `.BfME2WotR` and `.BfME2WotRMP`. Each
saved class writes a version number and refuses versions older than its
earliest supported one or newer than its own (\ref page_core_frameworks).
The save refers to object templates by name. Zero Hour: on load, an
object whose template no longer exists is skipped, so renaming or removing
a template makes such objects vanish from old saves. A replay stores the game
settings, including the map name and the random seed, and the commands.
`RecorderClass::playbackFile` starts a new game on that map, reseeds the
logic random stream from the stored seed and simulates the game again, so
the map must still exist under the same name. Any change that alters the
simulation therefore makes existing replays play out differently.

## Modding notes {#page_modding_modding}

- Data-driven: the INI file lists (legend), every template and module
  field, map overrides, Lua scripts, Apt movies, strings and assets.
- Fixed in code: the module catalogue, the script condition and action
  types, the Lua native functions, the callbacks screens register with
  Apt, 32 slots per command set, the archive mount order and the files
  named in code (`Water.ini`, `Fire.ini`, `Environment.ini`,
  `CommandMap.ini`, and per map `map.ini`, `solo.ini` and `map.str`).
- When unsure whether a change is safe for multiplayer, ask whether it
  changes anything the logic reads. If it does, every player needs it.

## Remastering notes {#page_modding_remastering}

- **Files.** `GameEngine::init` creates `TheFileSystem` and then a set-up
  step that creates a disk backend and a BIG-archive backend and mounts the
  archives (\ref page_modding_files). A replacement backend or package
  format plugs in at that step. Keep the default archive-first precedence,
  the prefer-local-files switch and the language lookups, or existing mods
  will load differently. (Zero Hour created the two backends through the
  Win32 device layer instead.)
- **Compatibility.** A remaster that wants to keep existing mods, saves
  and replays must keep the INI grammar, the module names and their
  fields, the Lua native functions and the save format, and must
  reproduce logic results bit for bit.

## Reading list {#page_modding_reading}

- \ref page_architecture for the template and module model,
  \ref page_startup for the load order.
- BFME 2 sources: `Code/GameEngine/Source/Common/GameEngineInit.cpp`,
  `Code/Libraries/Source/subsystem/SubsystemInterface.cpp` (its
  `loadIniFilesFromLegend` is BFME 1's body, not BFME 2's),
  `Code/GameEngine/Source/Common/Thing/ThingTemplateParseModuleName.cpp`,
  `Code/GameEngine/Source/Common/Thing/ModuleFactoryInit.cpp`,
  `Code/GameEngine/Source/GameClient/GUI/FileSystemOpenFile.cpp` and
  `Code/GameEngine/Source/GameClient/GameText.cpp`. The file-system global
  names in `FileSystemOpenFile.cpp` are provisional and swapped; the
  file-system set-up step that `GameEngine::init` calls right after
  `createFileSystem` shows which backend each global holds. In retail the
  `lang\<language>` lookup in `openFile` reads the language buffer, which
  starts as `English`.
- Zero Hour:
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/System/ArchiveFileSystem.cpp`
  and, under the same prefix, `Common/Thing/ThingTemplate.cpp`.
- Open-BFME-1's `docs/ini_schema.md` lists BFME 1's INI block keywords and
  fields, the nearest documented relative of BFME 2's.
