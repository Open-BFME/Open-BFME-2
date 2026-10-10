# Core frameworks {#page_core_frameworks}

These frameworks are used by almost every subsystem, so they are explained
once here. \ref page_architecture shows the layers they sit in.

Almost all come from Zero Hour and keep its design. Statements marked
"Zero Hour:" come from the Zero Hour source
(`reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD`)
and are not yet confirmed for BFME 2; the rest rests on BFME 2's matched code.

| Framework | Main types | Lives in |
|---|---|---|
| base types and math | `Int`, `Real`, `Bool`, `Coord2D`, `Coord3D` | `Lib/Coord2D.h`, `Lib/Coord3D.h`; bodies in `WWMath/coord*.cpp` |
| global data | `GlobalData`, `TheWritableGlobalData` | `Common/GlobalData*.cpp` |
| random values | `GetGameLogicRandomValue` and its twins | `Common/*RandomValue*.cpp`, `GameClient/ClientRandomValue*.cpp` |
| messages | `GameMessage`, `MessageStream`, `CommandList` | mainly `Common/MessageStream*.cpp`, `GameClient/MessageStream/` |
| weapons, damage, armor | `WeaponStore`, `WeaponSet`, `ArmorStore`, `DamageInfo` | `GameLogic/Object/` |
| upgrades, sciences, powers | `UpgradeCenter`, `ScienceStore`, `SpecialPowerStore` | `Common/System/`, `Common/RTS/` |
| command sets and buttons | `CommandSet`, `CommandButton`, `ControlBar` | `GameClient/GUI/ControlBar/`, `Common/INI/` |

Paths are under `Code/GameEngine/Source/`, except `Lib/` (in
`Code/Libraries/Include/`) and `WWMath/` (in `Code/Libraries/Source/WWVegas/`).
`GameEngine::init` creates the global data, the stores and
`TheMessageStream` at start-up (\ref page_startup).

## Base types and math {#page_core_frameworks_types}

The code writes `Int`, `UnsignedInt`, `Real`, `Bool` and similar names:
Zero Hour's typedefs from `Lib/BaseType.h` (`Int` is `int`, `Real` is
`float`, `Bool` is `bool`). BFME 2 has no copy of that header; a few files
include Zero Hour's and most declare the typedefs they need. Sizes assume the
32-bit x86 build, and `Real` is single precision everywhere.

`Coord2D` and `Coord3D` (float x, y, z) and the integer `ICoord2D` are the
point and vector types; `Region3D`, `IRegion2D` and `RealRange` pair a low
and a high value. BFME 2 keeps Zero Hour's lowercase helpers
(`Coord3D::length`, `Coord3D::normalize`, `Coord3D::crossProduct`,
`Coord2D::length`) and its exports add a capitalised method set
(`Coord3D::Add`, `Coord3D::Scale`, `Coord3D::Normalize`,
`Coord3D::GetLength`, `Coord2D::Rotate` and more) plus a `Coord3DBase` data
struct. The headers hold only the members needed so far. Matrices and the
W3D vector classes belong to WWMath (\ref sub_w3d_rendering).

## Global data {#page_core_frameworks_globaldata}

`GlobalData` holds game-wide tuning and option values: screen resolution,
time of day and its lighting (`GlobalData::setTimeOfDay`), the user's
options (`GlobalData::applyOptionPreferences`) and many more.
`GameEngine::init` creates it as a subsystem named `TheWritableGlobalData`;
read-only code writes `TheGlobalData` (Zero Hour: a const view of the same
pointer). Zero Hour fills it from the `GameData` INI block and lets a later
load, such as a map's INI, push an override on top; BFME 2 registers the same
keyword, but its parser is not reconstructed yet. There is no shared
declaration yet: files use partial views (\ref page_reading_code), so do not
trust a field name seen in one file.

## Deterministic random values {#page_core_frameworks_random}

| Stream | Functions | For |
|---|---|---|
| logic | `GetGameLogicRandomValue`, `GetGameLogicRandomValueReal` | the simulation |
| client | `GetGameClientRandomValue`, `GetGameClientRandomValueReal` | visuals, particles, UI |
| audio | `GetGameAudioRandomValue`, `GetGameAudioRandomValueReal` | sound variation |

Each stream has its own seed state; all use one generator, `randomValue`.
Only the logic stream is part of the lockstep contract: every peer seeds it
alike and must draw in the same order, so one extra logic draw desyncs the
game. `GameLogic::getCRC` folds `GetGameLogicRandomSeedCRC` into the game
state CRC (\ref sub_save_load_crc). The `file` and `line` arguments name the
caller; the logic forms log them with the value drawn (`logicrandom = ...`)
when a log is open, which is how a desync is traced.

`InitRandom` with no argument seeds all streams from the clock
(`GameEngine::init` calls it); the seeded `InitRandom` and
`InitGameLogicRandom` start a match or a replay. BFME 2 adds a check Zero
Hour lacks: when `TheGameLogic` exists and a particular `GameLogic` field is
not -1, that field's value replaces the requested seed. The reconstruction
labels it a frame, but it is not the frame counter other matched code reads;
what it holds and why it overrides the seed are not yet established.

**Random variables** (`GameLogicRandomVariable`, `GameClientRandomVariable`)
store a range and a distribution: `CONSTANT`, `UNIFORM`, `GAUSSIAN`,
`TRIANGULAR`, `LOW_BIAS` or `HIGH_BIAS`. As in Zero Hour, `getValue`
implements only `CONSTANT` (when low equals high; otherwise it behaves as
`UNIFORM`) and `UNIFORM`; any other type yields 0.
`INI::parseGameClientRandomVariable` reads the type by name from a
`DistributionTypeNames` table and defaults to `UNIFORM`.

**Floating-point mode.** `setFPMode` resets the floating-point unit and sets
the x87 control word only: 24-bit precision, round-to-nearest. It runs in
`GameLogic::getCRC`, in the logic's init, reset and update, at every INI load
and in some client and asset-loading paths.

## Messages and command lists {#page_core_frameworks_messages}

Every player action reaches the logic as a `GameMessage`: a
`GameMessage::Type` plus typed arguments (`GameMessage::appendRealArgument`,
`appendObjectIDArgument` and the rest). `GameMessage::getCommandTypeAsAsciiString`
names each type, so it is the readable index of the enum.

1. Input code appends messages to `TheMessageStream`.
2. Each client frame the engine's client-subsystem update calls
   `MessageStream::propagateMessages` (it has other callers, one on the
   logic's CRC path whose name is not yet confirmed). Each attached
   `GameMessageTranslator` sees every message in turn, returns
   `KEEP_MESSAGE` or `DESTROY_MESSAGE`, and may append new ones.
   `MessageStream::attachTranslator` orders them by priority (lower first);
   `GameClient::init` attaches the standard set.
3. Survivors move in one call to `TheCommandList`
   (`CommandList::appendMessageList`).
4. The network layer shares the list with the peers and returns it for its
   scheduled logic frame (\ref sub_network, \ref page_frame_loop).
5. `GameLogic::update` calls `GameLogic::processCommandList`, which hands
   each message to the logic's dispatcher (Zero Hour:
   `GameLogic::logicMessageDispatcher`; not yet reconstructed in BFME 2) and
   resets the list. Zero Hour's version also compares CRC messages; BFME 2's
   does not (\ref sub_save_load_crc).

`GameClient/MessageStream/` holds Zero Hour's translators (meta events and
key bindings, windows, selection, commands, hint spy). Key bindings come from
`CommandMap` INI blocks, mapped to message types by `MetaMap::parseMetaMap`.

## Weapons, damage and armor {#page_core_frameworks_weapons}

- `WeaponStore` (`TheWeaponStore`) owns the `WeaponTemplate`s from `Weapon`
  blocks (`WeaponStore::parseWeaponTemplateDefinition`).
  `WeaponStore::findWeaponTemplate` treats `None` as no weapon;
  `WeaponStore::allocateNewWeapon` makes an object's `Weapon`, and
  `WeaponStore::createAndFireTempWeapon` fires one no object holds.
- An object's `WeaponSet` holds its weapons per slot, locks a slot
  (`WeaponSet::setWeaponLock`) and answers attack questions
  (`WeaponSet::getAbleToAttackSpecificObject`, `WeaponSet::isOutOfAmmo`).
  BFME 2 has six slots; Zero Hour has three.
- Damage travels as a `DamageInfo` (input and output halves,
  `DamageInfoInput` and `DamageInfoOutput`, as in Zero Hour) into
  `Object::attemptDamage`. BFME 2's version differs from Zero Hour's direct
  forward to the body module: depending on a field of the `DamageInfo` it
  either queues a copy on the object for later or passes it on at once; what
  that field means is not yet established. Zero Hour: the body module
  applies armor and calls the damage modules' `onDamage` and, on death, the
  die modules' `onDie` (\ref sub_objects_modules).
- `ArmorStore` (`TheArmorStore`) holds `ArmorTemplate`s from `Armor` blocks:
  one coefficient per damage type, `Default` setting them all
  (`ArmorTemplate::parseArmorCoefficients`), plus a `DamageScalar`. BFME 2
  builds an `Armor` from the armor's name (`ArmorStore::makeArmor`); Zero
  Hour's holds a template pointer.

BFME 2 has 27 damage types (`FORCE`, `SLASH`, `PIERCE`, `SIEGE`, `MAGIC`,
`HERO`, `CAVALRY` and others). Zero Hour has 38; about a third of BFME 2's
names (`CRUSH`, `FLAME`, `HEALING`, `POISON`, `WATER` and others) also exist
there, and the rest are new.

## Upgrades, sciences and special powers {#page_core_frameworks_upgrades}

- `UpgradeCenter` (`TheUpgradeCenter`) holds `UpgradeTemplate`s from
  `Upgrade` blocks (`UpgradeCenter::findUpgrade`,
  `UpgradeCenter::findUpgradeByKey`). `UpgradeCenter::init` also creates one
  upgrade for each veterancy level above regular (veteran, elite, heroic),
  found with `UpgradeCenter::findVeterancyUpgrade`. Zero Hour: each upgrade
  owns a bit in a fixed-size mask.
- `ScienceStore` holds `Science` blocks. `ScienceStore::getSciencePurchaseCost`
  returns `SciencePurchasePointCostMP` in multiplayer games, in one further
  game mode (Zero Hour numbers that mode as skirmish; the BFME 2 meaning is
  not confirmed) and in replays of multiplayer games; otherwise
  `SciencePurchasePointCost`. `ScienceStore::getPurchasableSciences` lists
  the sciences a player could buy, and
  `ScienceStore::playerHasPrereqsForScience` (used by
  `Player::hasPrereqsForScience`) checks prerequisites.
- `SpecialPowerStore` holds `SpecialPowerTemplate`s from `SpecialPower`
  blocks. `SpecialPowerStore::canUseSpecialPower` checks, as Zero Hour does,
  for a module for the power and the required science; BFME 2 accepts any of
  several sciences and adds checks whose purpose is not yet established.

## Command sets and buttons {#page_core_frameworks_commands}

`CommandButton` blocks define one button (command type, the upgrade or
special power it uses, image, label); `CommandSet` blocks list an object's
buttons. `ControlBar::parseCommandButtonDefinition` and
`ControlBar::parseCommandSetDefinition` parse them. Buttons are more than
UI: `CommandButton::isReady` and `CommandButton::isValidObjectTarget` decide
whether a command can be used, and the command a button issues reaches the
logic as a `GameMessage`. BFME 2 differences: up to 32 buttons per set (Zero Hour: 18);
`CommandSet::getCommandButton` first asks the game logic for a run-time
override of that slot; `CommandButton::isReady` refuses a missing source
object and adds a check for one command type. The in-game UI is Apt-based
(\ref sub_gui_apt), but `ControlBar` still owns the definitions.

## Data reloading {#page_core_frameworks_reload}

The `Weapon`, `Upgrade`, `Science`, `CommandButton` and `CommandSet` block
parsers handle an INI load mode (load type 5) that Zero Hour lacks. A
definition seen again is replaced by a fresh entry. Weapon, Upgrade and
Science keep the old entry aside (on a retired list or vector) rather than
freeing it. Retail also has an on-screen notice, "ControlBar
(CommandSet/CommandButton) reloaded", shown when command data is reloaded.
How the mode is triggered is not yet established (\ref sub_ini).

## Modding notes {#page_core_frameworks_modding}

- **Data-driven (INI):** `Weapon`, `Armor`, `Upgrade`, `Science`,
  `SpecialPower`, `CommandButton`, `CommandSet`, `CommandMap` (key bindings)
  and `GameData` (global tuning). `None` means no weapon.
  `SciencePurchasePointCostMP` applies beyond multiplayer games (see above).
- **Hard-coded:** the 27 damage types, six weapon slots, 32 buttons per
  set and the message types are fixed enums or arrays. Only `CONSTANT` and
  `UNIFORM` random distributions produce values; other types yield 0.
- **Lockstep:** weapon, armor, upgrade, science and power data are
  simulation inputs. Peers with different values, or code that changes the
  order or number of logic random draws, diverge: the game state CRC reports
  a mismatch, and older replays stop playing back the same. Client-only code
  must use the client or audio stream.
- **Saves:** weapon sets and other logic state are saved through versioned
  `Xfer` code; changing what a class saves needs a version bump that keeps
  old saves loadable (\ref sub_save_load_crc).

## Remastering notes {#page_core_frameworks_remastering}

- **Floating point:** most of BFME 2's game engine was compiled with SSE
  enabled, so much logic math runs as SSE scalar code, while the remaining
  x87 code runs under the mode `setFPMode` re-applies. To stay compatible
  with retail peers and replays a port must reproduce results bit for bit,
  matching which operations used which unit and precision, not just forcing
  one FP mode.
- **32-bit layouts:** the base types, coordinate structs and offset-based
  class views assume the 32-bit x86 build.
- **Input seam:** commands reach the logic as `GameMessage`s through
  the message stream and command list; a new input or UI layer plugs in as a
  translator or by appending messages.

## Status and further reading {#page_core_frameworks_reading}

The random streams, message stream and store lookups are largely matched;
`GlobalData` and the weapon code only partly (search `reverse/functions.csv`
by class name). Zero Hour's headers (`Weapon.h`, `Science.h`, `ControlBar.h`
and so on) give the original design, `docs/bfme2-network-timing-path.md`
covers command scheduling, and \ref page_glossary defines terms.
