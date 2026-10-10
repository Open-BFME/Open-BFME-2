# GameClient: drawables, FX, input and the message stream {#sub_gameclient}

The game client is everything one machine shows, plays and reads from the
player: drawables, effects, camera and display, the in-game UI, strings,
movies, keyboard and mouse. Client state is not part of the lockstep
simulation, so two machines may draw a game differently. By design,
gameplay changes reach the logic only as `GameMessage`s, which become
network commands, but the boundary is not perfectly clean
(\ref sub_gameclient_connects).

API group: \ref grp_gameclient. See also \ref page_frame_loop (one client
frame), \ref page_architecture and \ref page_core_frameworks (messages).

## Where it lives {#sub_gameclient_where}

Under `Code/GameEngine/Source/GameClient/`: most of the subsystem, flat;
`Drawable/Update/` (client modules; some still sit under
`GameLogic/Object/`); `Input/`; `MessageStream/` (translators, `MetaMap`);
`System/` (images, 2D animations, ray effects, particles in
`FXParticleSystem/`); `Terrain/` (roads, bridges); `GUI/` and `LivingWorld/`
(\ref sub_gui_apt, \ref sub_living_world). Device code is under
`Code/GameEngineDevice/Source/`, in `W3DDevice/GameClient/` and
`Win32Device/GameClient/`. Placement changes often and many files are split
units, so search `reverse/functions.csv` by class name; `GameClient::init`,
`reset` and `update` are in `GameClientDrawableTOC.cpp`.

## Key classes and singletons {#sub_gameclient_classes}

| Class (singleton) | Role |
|---|---|
| `GameClient` (`TheGameClient`) | owns the drawable list and lookup by id, creates the client services and translators, runs the client update; walks drawables for other subsystems (`iterateDrawablesInRegion`, `setTimeOfDay`, `releaseShadows`, `allocateShadows`); writes a table of drawable template names through `Xfer` (`xferDrawableTOC`), which Zero Hour stores in save games |
| `Drawable` | client twin of a logic `Object` (or a purely client-side thing): draw modules render it, client modules animate it; holds shroud, fade, indicator-colour, selection and veterancy display state |
| `InGameUI` (`TheInGameUI`) | selection, building placement, floating text, world animations, hints, superweapon and idle-worker displays; its `init` loads the `InGameUI` definition and creates the control bar |
| `Display` (`TheDisplay`), `View` (`TheTacticalView`), `MetaMap` (`TheMetaMap`) | screen, camera, key bindings |
| `FXList`, `FXListStore` (`TheFXListStore`); `ParticleSystemManager`, `FXParticleSystem` modules | named effect recipes; particles |
| `Eva` (`TheEva`), scored-kill announcer controller | announcer events |
| `GameTextManager` (`TheGameText`), `GlobalLanguage`, `LanguageFilter`, `VideoPlayer` | string tables, per-language fonts, chat word filter, movies |
| snow, cloud and cloud-break managers | weather |
| fire manager (`TheFireManager`) | burning-terrain fire, smoke and scorch effects (`Fire` block) |

## Lifecycle and entry points {#sub_gameclient_entry}

`GameEngine::init` registers shared client services (`TheGameText`,
`TheEva`, `TheMessageStream`, the particle-system manager, `TheFXListStore`
and others), then `TheGameClient`, and `TheMetaMap` after it
(\ref page_startup). `GameClient::init` creates the client's services, some
through its factory virtuals, the device-layer seam (display strings,
keyboard, mouse, fonts, display, window manager, `InGameUI`, terrain
visual, video player, weather and fire managers) and some directly
(mapped images, 2D animations, translators, header templates, shell, ray
effects); the language filter and IME manager come from free factory
functions.

`GameClient::reset` resets `InGameUI`, destroys every drawable and resets
the services. `GameClient::update` runs once per client frame
(\ref page_frame_loop lists its steps); all three are matched. Drawables
are updated only when time is not frozen or paused (and an unnamed
`GameLogic` flag is clear) and the client frame number has advanced.

## From input to commands {#sub_gameclient_input}

`Keyboard::createStreamMessages` and `Mouse::createStreamMessages` append
raw `GameMessage`s to `TheMessageStream`. `GameClient::init` attaches
fourteen translators (Zero Hour attaches ten), each at a fixed priority;
`MessageStream::propagateMessages` offers every message to each in turn, and
a translator may consume it or post new ones. Named ones include
`MetaEventTranslator` (key bindings from `MetaMap`), `CommandTranslator`
(clicks into orders such as move, attack or special power) and
`HintSpyTranslator`. Others sit at the priorities where Zero Hour registers
its hot-key and selection translators and, last, its
`GameClientMessageDispatcher` (Zero Hour names, matched by priority);
several are not yet named. What survives goes to the command list and the
network (\ref page_core_frameworks, \ref sub_network).

## Drawables and effects {#sub_gameclient_drawables}

- **Modules.** A drawable is built from its thing template's modules
  (\ref sub_rts_model, \ref sub_objects_modules): draw modules from the W3D
  device layer, and client modules. The module factory registers client
  updates (`SwayClientUpdate`, `RadarMarkerClientUpdate`,
  `BeaconClientUpdate`, `AnimatedParticleSysBoneClientUpdate`,
  `EvaAnnounceClientCreate`) and client behaviours such as
  `AnimationSoundClientBehavior`, the sound selectors,
  `ModelConditionAudioLoopClientBehavior` and
  `TerrainResourceClientBehavior`.
- **Interpolation.** A drawable keeps an interpolated position and
  transform cache, presumably to smooth motion between 5 Hz logic frames.
- **Shroud.** When time is not frozen and an unnamed `GameEngine`
  frame-timing check passes (Zero Hour's release build runs this pass
  unconditionally; only its debug and internal builds test the global
  shroud-on setting), `GameClient::update` refreshes, for the local
  player, the shroud state of every drawable that has an object. A newly
  fogged object stays visible for a grace period, as in Zero Hour (two
  seconds, five if dying; BFME 2 multiplies a global believed to hold the
  logic frame rate).
- **FX lists.** An `FXList` is a named list of nuggets run at a position or
  on an object. BFME 2's sixteen nugget keywords are `Sound`, `EvaEvent`,
  `RayEffect`, `LightPulse`, `CameraShakerVolume`, `ViewShake`,
  `AttachedModel`, `TerrainScorch`, `ParticleSystem`, `ParticleSysBone`,
  `FXListAtBonePos`, `CursorParticleSystem`, `DynamicDecal`, `Laser`,
  `TintDrawable` and `BuffNugget`; `CullingInfo` and `PlayEvenIfShrouded`
  in the same block are settings of the list, not nuggets.
- **Particles.** `FXParticleSystem` INI blocks, built from the modules in
  `System/FXParticleSystem/`, define particle effects. Zero Hour's
  `ParticleSystemManager` remains, registered as
  `TheFXParticleSystemManager`; how the layers divide the work is open.

## How it connects {#sub_gameclient_connects}

- **Reads the logic.** Drawables follow their objects. The client asks
  `GameLogic` for the frame and pause state, tells it to delete the load
  screen, and asks objects for their shroud status
  (\ref sub_gamelogic_map). It does not run simulation code.
- **Is read by the logic.** Logic code reads model bone positions through
  `Drawable::getPristineBonePositions`, for example in
  `Object::getSingleLogicalBonePosition`, `DockUpdate::loadDockPositions`,
  `SpawnPointProductionExitUpdate::initializeBonePositions` and
  `BoneFXUpdate::resolveBoneLocations`, so drawable and model changes can
  alter simulation results.
- **Other subsystems.** Rendering is \ref sub_w3d_rendering; the shell,
  window manager and Apt screens are \ref sub_gui_apt; FX sound nuggets
  play through \ref sub_audio. Definitions are INI blocks (\ref sub_ini)
  read through the file system and BIG archives (\ref sub_common_services).

## Compared with Zero Hour and BFME 1 {#sub_gameclient_zh}

BFME 1 facts are from Open-BFME-1's retail block list (`docs/ini_schema.md`)
and matched code, not its Zero Hour-derived `ini.cpp` table.

| Area | Zero Hour | BFME 1 | BFME 2 |
|---|---|---|---|
| Particles | `ParticleSystem` blocks | `FXParticleSystem`, no `ParticleSystem` block | as BFME 1 |
| FX nuggets | eight kinds, including `Tracer` | sixteen: drops `Tracer`; adds `EvaEvent`, `CameraShakerVolume`, `AttachedModel`, `ParticleSysBone`, `CursorParticleSystem`, `DynamicDecal`, `Laser`, `TintDrawable`, `BuffNugget` | as BFME 1 |
| Client behaviours | none | sound selectors, animation sounds (others not established) | those, plus audio-loop and terrain-resource behaviours |
| Announcer | `EvaEvent` blocks; `TheEva` made in `GameClient::init` | `PredefinedEvaEvent`, `NewEvaEvent` | adds `EvaEventForwardReference`, `ScoredKillEvaAnnouncer`; `TheEva` made in `GameEngine::init` |
| Weather | snow manager only | adds cloud-effect and cloud-break managers; `CloudEffect`, `CloudBreakEffect`, `WeatherData` blocks | as BFME 1 |
| Terrain fire | none | no `Fire` block; the matched `GameClient::reset` resets no fire manager | adds a `Fire` block (terrain fire, smoke and scorch settings); the client creates and resets `TheFireManager` |
| Translators | ten | not established | fourteen, several not yet named |
| Intro movies | played inline in `GameClient::update` | not established | `update` registers callbacks on its first pass, one of which starts the EA logo movie; it still returns early while the intro flags are set |
| Shroud pass | unconditional in release builds (debug and internal builds test the global shroud-on setting) | not established | guarded by an unnamed `GameEngine` frame-timing check |

## Modding notes {#sub_gameclient_modding}

- **Data-driven.** INI blocks define FX lists, particle systems, key
  bindings (`CommandMap`; `MetaMap::parseMetaMap` rejects unknown message
  names), mouse cursors (`Mouse`, `MouseCursor`), mapped images, fonts per
  language (`Language`), announcer events, roads and bridges, water and
  weather. Fixed paths include `Data\INI\DrawGroupInfo.ini`,
  `Data\INI\Default\Eva.ini` and `Data\INI\Eva.ini`, `Video.ini` (default,
  then override), the `Data\INI\MappedImages\` subfolders
  (`TextureSize_512`, `HandCreated`, `AptImages`, `ParticleTextures`,
  `TransitionImages`) and `langdata.dat`, all opened through the file
  system, so BIG archives can supply them. Intro movies are named in code
  (`EALogoMovie`, `NewLineLogo`, `TolkienLogo`, `Overall_Game_Intro`).
- **Strings.** `GameTextManager` loads the string table (normally the
  compiled CSF file; a plain STR file can be used instead) plus a per-map
  table (`initMapStringFile`); the window title is `GUI:FullGameName`.
- **Client data can still break online play.** `GameEngine::init`
  installs a checksum `Xfer` while it registers subsystems
  (\ref page_modding_rules). No registration there passes hard-coded INI
  paths (Zero Hour passes many), so what the FX list store or the
  particle-system manager loads at registration comes from the files
  `SubsystemLegend.ini` lists for it; the font library and the banner UI
  also load from the legend, in `GameClient::init` and `InGameUI::init`.
  BFME 1's legend loader passes the checksum to every file. BFME 2's is not
  yet matched and adds a gate and an exclusion list, so which of these
  files BFME 2 checksums is not established: do not assume client data is
  outside the checksum. `Water.ini`, `Fire.ini` and `Environment.ini` load
  through it directly; `CommandMap.ini`, the announcer's `Eva.ini` files,
  `ImageCollection::load` and `VideoPlayer::init` load without it.
- **Model bones are gameplay data.** Dock, spawn-point and `BoneFXUpdate`
  bones the logic reads (\ref sub_gameclient_connects) are not just visuals.
- **Hard-coded.** The translator chain and its priorities, the drawable
  update order, and the `TextureSize_512` set that `GameClient::init` loads
  mapped images from.

## Remastering notes {#sub_gameclient_remastering}

- **Backend seam.** `W3DGameClient` overrides `GameClient`'s factory
  virtuals: `createGameDisplay`, `createFontLibrary` and `createSnowManager`
  are matched under those names, and slots identified as Zero Hour's
  `createKeyboard` and `createMouse` build a DirectInput keyboard and a
  mouse derived from `Win32Mouse` (Zero Hour's `W3DMouse`), which is also
  kept in the global the window procedure feeds with mouse events. A new
  backend plugs in here.
- **Resolution.** `Drawable::drawVeterancy` scales X by width / 1024 and Y
  by height / 768 separately, stretching its icons at aspect ratios other
  than 4:3. `GlobalLanguage::adjustFontSize` scales fonts by horizontal
  resolution / 1024 only, so text grows with width, not height.
  `InGameUI::init` sizes the tactical view to the full display width and
  77% of its height, leaving room for the control bar, as Zero Hour does.
- **Timing.** Client delays counted in logic frames, such as the shroud
  grace period, follow game time, not the display rate.
- **Determinism boundary.** Keep the bone queries the logic makes through
  `Drawable` bit-identical (\ref sub_gameclient_connects).

## State of the reconstruction {#sub_gameclient_state}

As of October 2026, much matched code was still placeholder-named, mostly
in `Drawable`, `InGameUI`, the particle modules and the new translators;
`GameClient`, `Drawable` and `InGameUI` had no canonical shared header
(\ref page_reading_code); and several core files, including the one
holding `GameClient::init`, `reset` and `update`, did not link. This
changes daily: to refresh it, search `reverse/functions.csv` and
`reverse/link_status.csv` for the directory.

## Reading list {#sub_gameclient_reading}

- Zero Hour: `GameClient.cpp`, `Drawable.cpp`, `InGameUI.cpp`, `FXList.cpp`,
  `Eva.cpp` and `MessageStream/` in `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/`.
- BFME 1: `docs/ini_schema.md` and `game/GameEngine/Source/GameClient/` in
  the reference checkout. BFME 2's `reverse/module_factory_registrations.csv`
  lists the module types.
