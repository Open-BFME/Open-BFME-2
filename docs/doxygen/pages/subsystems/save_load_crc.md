# Save and load, CRC and replay {#sub_save_load_crc}

One serialisation mechanism, `Xfer`, does four jobs: it writes and reads
saved games, computes the checksum that proves every machine in a
multiplayer game still agrees, checksums most INI data loaded at startup,
and stores small structures inside replays. Every class with state to keep
derives from `Snapshot` and has one transfer function that lists its fields
once; the kind of `Xfer` passed in decides whether they are written, read or
checksummed. Around it sit `GameState` (save files), `GameStateMap` (the map
inside a save) and `RecorderClass` (replays).

The API group is \ref grp_save_load_crc. \ref page_frame_loop shows where
the checksum runs in a frame, and \ref page_core_frameworks covers the
deterministic random numbers it includes.

## Where it lives {#sub_save_load_crc_where}

| Path under `Code/` | What is there |
|---|---|
| `GameEngine/Source/Common/System/Xfer.cpp` and the `Xfer*.cpp` files beside it | the `Xfer` base: typed transfer operators, versions, enums, raw bytes, strings, and helpers for engine types such as object-id lists, sciences and upgrades |
| `Libraries/Source/xfer/` | the stream classes `XferSave` and `XferLoad` (some members still sit in staging files elsewhere) and the checksum accumulator |
| `GameEngine/Source/Common/System/Snapshot.cpp` | `Snapshot`; its shared declaration is `reference/shims/moduledata/Common/Snapshot.h` |
| `GameEngine/Source/Common/System/SaveGame/` | `GameState`: save blocks, save-file reading, the save list, map paths |
| `GameEngine/Source/Common/Recorder.cpp`, `GameEngine/Source/Common/System/Recorder*.cpp` | `RecorderClass` |
| `GameEngine/Source/GameLogic/System/` | `GameLogic::getCRC` in `GameLogicGetCRC.cpp` (the donor name; the WorldBuilder twin calls it `CalcCRC`), and the checksum writer's constructor |
| `*Xfer.cpp` files throughout the tree | transfer functions of individual classes |

The WorldBuilder twin names the original units
`Libraries/Source/xfer/xfer_save.cpp` and `xfer_load.cpp`,
`Common/System/SaveGame/GameState.cpp` and `GameStateMap.cpp`, and
`Common/Recorder.cpp`. `GameStateMap` and several `RecorderClass` and stream
members currently sit in address-named staging files; search
`reverse/functions.csv` for exact locations.

## Key classes {#sub_save_load_crc_classes}

- `Snapshot` is the base of everything saved or checksummed. After the
  destructor come three pure virtual functions: `loadPostProcess`, a name
  getter and the transfer function `xfer`. The exported particle-system
  classes spell them `LoadPostProcess`, `GetSnapshotName` and `DoXfer`. Zero
  Hour: once a load has read every block, each system's `loadPostProcess`
  rebuilds what the transfer could not, such as pointers.
- `Xfer` is the visitor a `Snapshot` is handed. BFME 2 exports its
  interface: `Xfer::operator==` overloads (the exported name; they transfer,
  they do not compare) for built-in types, strings, coordinates, regions,
  colours, `Xfer::Version` and any `Snapshot`; `Xfer::XferEnum`,
  `Xfer::XferRawBytes`; and the mode queries `Xfer::IsLoading`,
  `Xfer::IsStoring`, `Xfer::IsCRC` and `Xfer::IsLightCRC`. Each operator
  ends in one pure virtual data function that receives a four-character type
  tag (`int`, `real`, `astr` and so on), an address and a size. Many units
  still call Zero Hour spellings (`xferInt`, `xferSnapshot`) through their
  own view of the class; those reach the same virtual functions.
- `XferSave` and `XferLoad` write and read a byte stream. The checksum
  writer derives from `XferSave`; its class name is still a placeholder.
- `GameState` (`TheGameState`) owns save files, `GameStateMap`
  (`TheGameStateMap`) the map stored in them, and `RecorderClass`
  (`TheRecorder`) replays.

## How a class saves itself {#sub_save_load_crc_xfer}

- **One function, every mode.** A transfer function transfers its version,
  then its fields in a fixed order, so save, load and checksum visit the
  same fields in the same order.
- **Versions.** `Xfer::Version` holds the current version and the earliest
  one still readable; one byte is stored. Loading a version newer than the
  current or older than the earliest throws an `XferException`.
  `Xfer::Version1` is the shortcut for a class at version 1.
- **Memory images.** An `int` is its four bytes, a `float` its four IEEE
  bytes, a coordinate its three floats. A string is a length byte (255
  escapes to a four-byte length) and its characters, two bytes each for
  `UnicodeString`. `Xfer::XferEnum` accepts one to four bytes.
- **Blocks and tags.** Top-level sections, and some sub-records, are wrapped
  in blocks: a `BLOK` marker and the offset of the block's end, so a reader
  can skip it; tagged streams add the block name and an `EBLK` end marker. A
  stream starts with the signature `ALAE2STR`, a value from the caller and a
  flag; with the flag set every value is preceded by its type tag and
  `XferLoad` checks it ("Expected '...' but found '...'"). Which files use
  the tagged form is not yet established.

## Saving and loading a game {#sub_save_load_crc_saves}

- `GameState::init` registers named blocks (`CHUNK_GameState`,
  `CHUNK_GameLogic`, `CHUNK_Players`, `CHUNK_LivingWorldLogic`,
  `CHUNK_Audio` and many more) with `GameState::addSnapshotBlock`. They go
  into separate lists: the full save list, a logic-only list (Zero Hour uses
  its counterpart for deep checksums; its BFME 2 user is not yet
  identified), and two short lists (mainly game state, campaign, map, game
  logic, audio and Living World logic) whose use is not yet identified.
- `GameState::xferSaveData` walks one list. Saving writes each block name,
  the block, then an end-of-file token; loading reads names up to that token
  and skips any block whose name is not registered.
- `GameState::getSaveGameInfoFromFile` reads only the `CHUNK_GameState`
  block, the summary shown in the save list. `GameState::iterateSaveFiles`
  and `GameState::populateSaveGameListbox` build the save and load screens,
  with auto-saves in a second list. The auto-save routine passes the
  description `__AUTO#SAVE__`, but the list is chosen by the auto-save flag
  in the save summary (BFME 1 tests the description instead).
- Saves live in a `Save` folder under the user-data folder, with one
  extension per kind of game: `.BfME2Campaign`, `.BfME2Skirmish`,
  `.BfME2WotR` or `.BfME2WotRMP`.
- `GameStateMap::DoXfer` stores the map path in portable form
  (`GameState::realMapPathToPortableMapPath`), embeds a copy of the map (the
  original on the first save, the in-use copy later, and from its version 2
  the map's `.wak` file), and the next free object and drawable ids. In some
  Living World and campaign states it stores no map. Loading writes the copy
  back into the save folder and plays it;
  `GameStateMap::clearScratchPadMaps` later deletes the `.map`, `.wak` and
  `.lws` files there.
- `GameLogic::xferObjectTOC` and `GameClient::xferDrawableTOC` save tables
  that map template names to small ids, so saves name their templates.
- The routines that write and read a whole save file (Zero Hour: `saveGame`,
  `loadGame`) are not yet reconstructed.

## Checksums {#sub_save_load_crc_crc}

- **INI CRC.** `GameEngine::init` attaches a checksum writer to the
  subsystem list, so every INI file a subsystem loads through its
  `SubsystemLegend.ini` entry passes through it (`SubsystemLegend.ini`
  itself does not; \ref sub_ini). The fallback paths used when a subsystem
  has no legend entry are checksummed for some subsystems only. `Water.ini`,
  `Fire.ini` and `Environment.ini` are also loaded through it. The sum plus
  a Create-a-Hero checksum becomes the global data's INI CRC, which
  `LANAPI::RequestGameJoin` puts in LAN join requests (\ref sub_network) and
  replays record.
- **Logic CRC.** `GameLogic::getCRC` sets the floating-point mode, then
  hashes every object (in light-CRC mode `Object::xfer` hashes only a short
  summary of each), a checksum of the logic random seed, the partition,
  collision, shroud and taint managers, a skirmish-AI manager, the player
  list, the AI and, in some games, the Living World logic. Flags whose
  setter is not yet known can leave parts out. It does not hash the script
  engine, teams, sides or terrain logic, which are saved (Zero Hour's deep
  CRC also walks a block list that includes the script engine). Given a
  stream, the writer also writes everything it hashes there; that is how
  deep-CRC dumps are made.
- **When it runs.** Periodically, every CRC-interval logic frames (the
  interval is in the game's settings), in multiplayer games: each machine
  computes the logic CRC and sends it in a logic-CRC message (Zero Hour:
  `MSG_LOGIC_CRC`). Reports are kept per frame until every player has sent
  one; a mismatch starts desync handling, which can write diagnostic dumps
  and notify the network layer. The comparing routine is matched, but its
  name is not yet confirmed.
- **Arithmetic.** The sum rotates left one bit and adds each 32-bit word,
  then each leftover byte. Zero Hour's `XferCRC` byte-swaps each word and
  packs leftover bytes into one word, so the games' values differ.
- **Client check.** A guard around the client update records the logic CRC
  first. In BFME 1 it compares afterwards and, on a difference, shows
  "GameLogic changed outside of GameLogic::update()!" and appends to
  `CLIENT_DESYNC_<machine>.txt`. BFME 2 has the same strings, but only the
  guard's constructor is matched so far. A flag enables the check.

## Replays {#sub_save_load_crc_replays}

- Replays go to a `Replays` folder under the user-data folder, extension
  `.BfME2Replay`. `RecorderClass::startRecording` writes the header: the
  `BFME2RPL` signature (Zero Hour: `GENREP`); slots for the start and end
  times and the frame count, which `RecorderClass::logGameStart` and
  `RecorderClass::logGameEnd` fill in; two values that
  `RecorderClass::logCRCMismatch` fills with the CRC interval and the logic
  frame of a mismatch (Zero Hour: a single desync flag); a byte Zero Hour
  uses as a quit-early flag; eight per-slot disconnect flags that
  `RecorderClass::logPlayerDisconnect` sets; then the replay name, version
  strings, the INI CRC and two more global-data values, the slot list, the
  local slot, each slot's custom hero (transferred with `XferSave`),
  difficulty, game mode, rank points and the frame-rate cap.
- `RecorderClass::writeToFile` appends each command (frame, type, player,
  arguments); `RecorderClass::appendNextCommand` reads them back.
- `RecorderClass::playbackFile` reads the header, selects the recorded map,
  takes the CRC interval from the recorded settings, posts a new-game
  message and reseeds the random numbers. A replay is a re-simulation from
  commands, not a recording of state.
- `RecorderClass::dumpCommandHistory` writes recorded commands as readable
  text, with object, template and special-power names resolved.

## Entry points {#sub_save_load_crc_entry}

| Function | Role | State |
|---|---|---|
| `GameState::init` | registers the save blocks | matched |
| `GameState::xferSaveData` | walks one block list to save, load or checksum | matched |
| `GameStateMap::DoXfer` | the map, its path and the id counters in a save | matched |
| `GameLogic::getCRC` | the logic checksum | matched |
| `RecorderClass::startRecording` | opens a replay and writes its header | matched |
| `RecorderClass::playbackFile` | starts replay playback | matched |
| whole-file save and load | write or read a save file | not yet reconstructed |

## How it connects {#sub_save_load_crc_connects}

- `GameEngine::init` creates `TheGameState`, `TheGameStateMap` and
  `TheRecorder`, builds the INI CRC and can start replay playback
  (\ref sub_engine_core).
- The simulation subsystems implement `Snapshot` and are saved:
  \ref sub_gamelogic_map, \ref sub_objects_modules, \ref sub_ai_pathfinding,
  \ref sub_scripting, \ref sub_rts_model and \ref sub_living_world. The
  logic CRC covers objects, the AI, players, the partition, collision,
  shroud, taint and skirmish-AI managers and, conditionally, the Living
  World logic, but not the script engine.
- Client state is saved but not in the logic CRC: blocks for the game
  client, in-game UI, tactical view, particles, terrain visuals and audio
  (\ref sub_gameclient, \ref sub_gui_apt, \ref sub_w3d_rendering,
  \ref sub_audio).
- \ref sub_network carries the logic-CRC messages; save summaries and
  embedded maps go through the engine file system
  (\ref sub_common_services).

## BFME 2 compared with Zero Hour {#sub_save_load_crc_zh}

- **Snapshot.** Zero Hour's has `crc`, `xfer` and `loadPostProcess`; BFME 2
  has a name getter instead of `crc`. The shared header keeps both spellings
  behind macros so Zero Hour-derived units still compile.
- **Xfer.** Zero Hour has one named function per type and untagged data.
  BFME 2 has the exported operator family, a type tag on every value,
  optional tagged streams and block markers, and keeps the stream classes in
  their own library.
- **Versions.** Zero Hour refuses only versions newer than the current; BFME
  2 also refuses versions older than a stated minimum.
- **More state.** BFME 2 adds blocks for Living World logic, audio,
  Palantir, taint, weather, skirmish AI, spells and objectives among others,
  and fills four block lists where Zero Hour fills two.
- **Files.** One save extension per kind of game (Zero Hour: `.sav`), and
  the map's `.wak` file travels with it.
- **Replays.** New signature and custom heroes, and a CRC mismatch is
  recorded as the interval and frame rather than as a flag. In normal play
  BFME 2 generates logic-CRC messages only in multiplayer games (a debug
  command-line option can force them for chosen frames); Zero Hour also
  computes them in single-player games and their replays.

## Modding notes {#sub_save_load_crc_modding}

- **Nothing here is data-driven.** Block lists, folders, extensions and the
  replay format are code; a mod changes what is saved only by changing the
  classes that save themselves.
- **Data changes break multiplayer and replays.** The INI files loaded
  through `SubsystemLegend.ini` entries, and `Water.ini`, `Fire.ini` and
  `Environment.ini`, feed the INI CRC that LAN joins carry and replays
  record. Anything that changes logic results, INI values the simulation
  reads included, changes the logic CRC: unmodified players desync, and old
  replays play out differently.
- **Version every saved class.** Adding, removing or reordering a field
  changes the stream; bump the version and keep reading the old ones, or old
  saves fail to load. Unknown top-level blocks are skipped. Some classes
  also wrap sub-records in named blocks, matched by name: an object's
  behaviour modules (`Object::xfer`), a drawable's modules and a Living
  World building's nuggets (`LivingWorldBuilding::DoXfer`). Saved data for a
  module tag or nugget the object or building no longer has is skipped.
  Plain fields are not skipped: a field change needs a version bump.
- **Templates are saved by name.** Renaming or removing a template affects
  saves that use it. Zero Hour skips such objects on load; BFME 2's handling
  is not yet traced.
- **Maps travel with saves.** A save restores its own map copy, so editing a
  map file does not change saves made on it.
- **Fixed limits.** The replay header holds eight player slots, versions are
  one byte, and enum fields are at most four bytes.

## Remastering notes {#sub_save_load_crc_remastering}

- **Layout is the format.** Values are x86 little-endian memory images, and
  composite types are copied whole. Another compiler or a 64-bit build must
  keep each transferred type's size and layout to read retail saves and
  replays.
- **Checksums hash float bits.** Playing with retail clients needs the
  logic's float results bit for bit; `GameLogic::getCRC` resets the
  floating-point mode first (\ref page_core_frameworks).
- **File access is mixed.** Replays use the C runtime with wide file names,
  scratch maps are deleted with Win32 calls, and save summaries and embedded
  maps use the engine file system. A port replaces all three.
- **A new backend is a new stream.** Any target, such as another file format
  or a debug dump, plugs in as an `Xfer` subclass that implements the data
  function; the tagged mode already helps diagnose format mismatches.
- **Timing.** The CRC interval counts logic frames, independent of the
  render rate (\ref page_frame_loop).

## State of the reconstruction {#sub_save_load_crc_state}

The `Xfer` base and its operators, the stream classes, the `Snapshot`
header, `GameState` block registration and save-list code, `GameStateMap`,
`GameLogic::getCRC` and most of `RecorderClass` are matched and named,
mostly from exports, the WorldBuilder twin and the BFME 1 and Zero Hour
donors. `GameLogic::getCRC` is the donors' name; the WorldBuilder twin uses
another (see the table above), so it may still be renamed. Whole-file save
and load and the client check's comparison are not yet reconstructed; the
CRC report comparison is matched but its name is not yet confirmed, and the
checksum writer's class name is a placeholder. Hundreds of per-class
transfer functions are named, but a large share still sit in address-named
files, and many units here do not link yet. To refresh this picture, search
`reverse/functions.csv` and `reverse/link_status.csv` for the files above.

## Reading list {#sub_save_load_crc_reading}

- Zero Hour, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/`:
  `Include/Common/Snapshot.h`, `Include/Common/Xfer.h`,
  `Source/Common/System/Xfer.cpp`, `XferCRC.cpp`, `XferLoad.cpp`,
  `XferSave.cpp`, `Source/Common/System/SaveGame/GameState.cpp`,
  `GameStateMap.cpp` and `Source/Common/Recorder.cpp`.
- BFME 1, in Open-BFME-1's `game/` tree:
  `GameEngine/Source/GameLogic/System/GameLogicCRC.cpp`,
  `GameEngine/Source/GameNetwork/native_desync_report.cpp` and
  `GameEngine/Source/Common/System/SaveGame/`.
