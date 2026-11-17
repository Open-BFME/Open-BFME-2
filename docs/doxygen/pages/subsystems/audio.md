# Audio {#sub_audio}

The audio subsystem turns named sound events into sound. Game code asks the
audio manager, `TheAudio`, to play an event such as a unit's voice line or a
weapon sound; the event's definition, loaded from INI, says which files to
pick from and how to vary pitch, volume and delay. The manager queues the
request and plays it through the Miles Sound System as a 2D sample, a 3D
sample or a stream. Unlike Zero Hour, BFME 2 (like BFME 1) has large-group
audio, which works out where a group sound for many nearby units should sit.
It is driven from the game logic, which starts and stops the group sounds
itself through virtual calls on `TheAudio`; which audio-manager functions
those calls reach is not established.

The audio manager runs on the client side of the engine, and sound-event
variation (file, pitch, volume) comes from the audio random stream rather
than the logic one. Large-group audio is the exception: its update module
runs in the logic and draws from the logic stream (see the modding notes).
Logic code also calls the manager (object modules such as
`AudioLoopUpgrade`), and a few script conditions read music state; the
notes below say what that means for multiplayer. Its API group is \ref grp_audio, and the singleton model is
on \ref page_architecture.

## Where it lives {#sub_audio_where}

| Path under `Code/` | What is there |
|---|---|
| `GameEngineDevice/Source/MilesAudioDevice/` | `MilesAudioManager`, the Miles Sound System backend: device and provider setup, sample pools, the request queue, music, loop buffers, and the file cache (`AudioFileCache`, `MilesAudioCache.cpp`). Split over many files; `MilesAudioManager.cpp` holds most of it |
| `GameEngine/Source/Common/Audio/` | `AudioEventRTS`, one playing or pending instance of a sound event, and accessors of `AudioEventInfo`, the event definition |
| `GameEngine/Source/Common/INI/` | the parsers for the audio INI blocks, with the other INI parsers (\ref sub_ini) |
| `GameEngine/Source/GameLogic/LargeGroupAudio/` | `LargeGroupAudio` (`TheLargeGroupAudio`), its audio maps, grid cells and key lists |
| `GameEngine/Source/GameLogic/Object/Update/LargeGroupAudio*.cpp` | `LargeGroupAudioUpdate`, the object module that registers a unit with large-group audio |
| `GameEngine/Source/Main/AudioManager*.cpp` | the focus handler that `WndProc` calls |

Source-file path strings in retail name the original units
`MilesAudioDevice/MilesAudioManager.cpp`, `Common/Audio/AudioEventRTS.cpp` and
`GameLogic/Object/Update/LargeGroupAudioUpdate.cpp`; some of them are the file
arguments of random-value calls. Many current files are split pieces of these,
so search by function name.

## Key classes and singletons {#sub_audio_classes}

- `AudioManager` (`TheAudio`) is the engine-wide interface. Other
  subsystems call it mostly through virtual functions, which the backend
  overrides.
- `MilesAudioManager` is the concrete manager. It owns the Miles device,
  the 2D and 3D sample pools, the queue of audio requests that game code
  posts and the playing-audio lists. It also owns the loop buffers that a
  worker thread refills and the music state, which BFME 2 keeps per view.
  Its state is guarded by one mutex shared with that thread.
- `AudioEventInfo` is one sound definition from INI: the kind of block
  that defined it (sound effect, music track, dialog, ambient stream or
  streamed sound; a `Multisound` block probably also makes one, holding a
  list of subsounds, but that is not confirmed), weighted lists of file
  names, optional attack and decay files, and the pitch, volume and delay
  ranges.
- `AudioEventRTS` is one request to play an `AudioEventInfo`: its owner
  (a fixed position, a drawable or an object as in Zero Hour, or, in
  BFME 2, a Living World entity or army, as
  `AudioEventRTS::internalXfer` shows; the identity of one further owner
  kind is not established), the chosen file and the chosen pitch and
  volume. It knows which portion (attack, main sound, decay) plays next.
- `AudioFileCache` holds sound file images in memory. A worker loop of its
  own takes pending files from three priority queues and reads them
  (`AudioFileCache::readAudioFile`); Zero Hour's cache reads a file when it
  is asked for it. It reads WAV headers through Miles, keeps PCM files as
  they are, expands IMA ADPCM files when they are loaded, and frees unused
  files once its total size passes a budget.
- `LargeGroupAudio` (`TheLargeGroupAudio`) is a logic-side subsystem that
  `GameLogic::init` creates. Units with the `LargeGroupAudioUpdate` module
  register with it (BFME 1: again when, among other changes, the unit's
  position, model condition or stealth state changes). Each audio map
  (class `LargeGroupAudioAudioMap`, a name taken from the WorldBuilder
  build, defined by a `LargeGroupAudioMap` INI block) tracks the matching
  units on a grid, weighted per cell.
  `LargeGroupAudioGridCell::getPreferredAudioPosition` puts the group sound
  at the cell, shifted toward its more heavily weighted neighbours (by up
  to a third of a cell), at ground height.

## Data flow {#sub_audio_flow}

1. **Definitions.** `MilesAudioManager::init` loads `AudioSettings.ini`,
   then the `Default` copies of `Music.ini`, `Speech.ini`,
   `SoundEffects.ini` and `AmbientStream.ini`, then `Music.ini`,
   `SoundEffects.ini`, `Speech.ini`, `Voice.ini`, `AmbientStream.ini` and
   `MiscAudio.ini`, all under `Data\INI\`. `LargeGroupAudio::init` loads
   `Data\INI\LargeGroupAudio.ini`.
2. **Device.** `MilesAudioManager::openDevice` returns at once when audio
   is switched off in the global data. Otherwise it starts Miles with the
   output format from `AudioSettings`; if that fails it switches every
   channel off. `MilesAudioManager::selectProvider` then picks the 3D
   provider (see the remastering notes).
3. **Requests.** Game code creates an `AudioEventRTS` and hands it to
   `TheAudio`, which records a request; requests are applied in a batch
   (`MilesAudioManager::processRequestList`). Retail's request-name table
   lists eight kinds: play, stop one handle, stop music, push music, pop
   music, and activate, deactivate or clear out a music system.
4. **Choosing the file.** For sound-effect events,
   `AudioEventRTS::generateFilename` picks one of the listed files by
   weight, rerolling to avoid the file played last (or takes them in order
   when a control flag is set or the event is sequential); other kinds use
   their single file. `AudioEventRTS::generatePlayInfo` rolls pitch and volume
   and, for sound effects, picks the attack and decay files by weight. Both
   use the audio random stream (\ref page_core_frameworks).
5. **Playback.** Positional events become 3D samples, others 2D samples or
   streams. Miles reads files through callbacks that open them with
   `TheFileSystem`, so sounds can live in BIG archives.

`TheAudio` is updated once per client frame and large-group audio during
the logic update; \ref page_frame_loop gives the order.

## Entry points {#sub_audio_entry}

| Function | Role |
|---|---|
| `GameEngine::init` | registers `TheAudio` from a `GameEngine` factory virtual (Zero Hour: `createAudioManager`; which BFME 2 override returns the Miles manager is not established), quits if the music check fails, then sets the five channel switches from the global data |
| `MilesAudioManager::init` | loads the audio INI, sets the system volumes, starts the loop-buffer thread, opens the device |
| `MilesAudioManager::openDevice`, `MilesAudioManager::selectProvider` | Miles start-up and 3D provider choice |
| `MilesAudioManager::onAudioLODChanged` | when the audio level of detail changes, picks the 3D provider again unless EAX 3 is in use or the current provider still fits whether Dolby is allowed, then resets the ambient-stream limit |
| `MilesAudioManager::stopAudio` | stops everything on the given channels |
| `AudioManager::regainFocus` | called from `WndProc`'s `WM_ACTIVATE` arm (through `TheTransitionHandler`, when it exists) when the window becomes active. The body ignores its receiver: for the music, sound and 3D-sound channels it computes a volume from a base value and the volume factors of entries gathered through `TheTransitionHandler`, and applies it through `TheAudio`. The name `AudioManager::regainFocus` comes from the Zero Hour method this body corresponds to; the class it really belongs to in BFME 2 is not settled |
| `LargeGroupAudio::init`, `LargeGroupAudio::update`, `LargeGroupAudio::reset`, `LargeGroupAudio::xfer` | large-group audio lifecycle and save data |

## How it connects {#sub_audio_connects}

- **Created by** \ref sub_engine_core, which registers `TheAudio` early,
  before the data stores. `TheEva` is registered right after it.
- **Fed by the client** (\ref sub_gameclient): the `Sound` nugget of an FX
  list (`SoundFXNugget`) and client behaviours such as
  `AnimationSoundClientBehavior` and `ModelConditionAudioLoopClientBehavior`.
- **Fed by logic modules** (\ref sub_objects_modules): `AudioLoopUpgrade`
  starts a sound owned by its object when the upgrade is applied (and can
  stop it after a set time), and `LargeGroupAudioUpdate` feeds large-group
  audio.
- **Fed by** \ref sub_scripting (script actions reach `TheAudio` through its
  virtual functions) and \ref sub_living_world (campaign acts can contain
  `AudioEvent` steps; `LivingWorldSound` parses its sounds).
- **Apt UI** (\ref sub_gui_apt): the Apt runtime has its own `Sound` object
  (`AptSound`); how it reaches `TheAudio` is not established.
- **Reads** the file system and archives (\ref sub_common_services), INI
  (\ref sub_ini) and the audio level of detail from `TheGameLODManager`.
- **Saved** with the game (\ref sub_save_load_crc): `LargeGroupAudio::xfer`;
  the map polygon triggers the manager tracks for audio, saved as trigger
  IDs and rebuilt in `MilesAudioManager::loadPostProcess`, which throws an
  Xfer exception when a saved trigger ID matches no polygon trigger
  (Zero Hour: `GameState::loadGame` catches such an exception and reports
  the load as failed); and `AudioEventRTS::internalXfer`, which is
  versioned.

## BFME 2 compared with Zero Hour {#sub_audio_zh}

Zero Hour's code is in `GameEngine/Source/Common/Audio/` (`GameAudio.cpp`,
`GameSounds.cpp`, `GameMusic.cpp`, `AudioEventRTS.cpp`) and
`GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp`.

- **Channels.** Zero Hour has four (music, sound, 3D sound, speech) plus
  the `AudioAffect_SystemSetting` flag. Unlike Zero Hour, BFME 2 (like
  BFME 1) has a fifth channel, `AudioAffect_AmbientStream`, and
  `AudioAffect_SystemSetting` moves up one bit to make room.
- **Event kinds.** Unlike Zero Hour, BFME 2 has `AmbientStream`,
  `StreamedSound` and `Multisound` INI blocks; BFME 1 already has the first
  two. As in Zero Hour, sound effects, music tracks and dialog start from
  `DefaultSoundEffect`, `DefaultMusicTrack` and `DefaultDialog`; ambient
  streams and streamed sounds start from `DefaultAmbientStream` and
  `DefaultStreamedSound`. Retail has no `DefaultMultisound` block name.
  Unlike Zero Hour and BFME 1, BFME 2 does not load a
  `Default\Voice.ini`.
- **Requests.** Zero Hour has three request kinds (play, pause, stop);
  BFME 2's request-name table has the eight listed under data flow, most
  of them for music.
- **File choice.** For sound effects in random mode, BFME 2 picks by weight
  and rerolls until the file differs from the last one played; Zero Hour
  picks uniformly when its random flag is set and, with more than two
  files, steps to the next file on a repeat. In both, the other mode plays
  the files in order, and the other event kinds use one file. Zero Hour
  also draws "logical" sounds from the logic random stream, so that all
  machines agree on a sound's length; BFME 2 uses only the audio stream.
  One control bit makes the file name bare (no folder prefix or extension
  added).
- **3D provider.** Zero Hour passes the options' preferred provider to
  `selectProvider`, which uses it only to return early when that provider
  is already selected; it then picks `Dolby Surround` for headphone or
  multi-speaker setups, otherwise `Miles Fast 2D Positional Audio`
  (Miles Fast 2D is also the fallback).
  BFME 2 keeps that chain, tries `Creative Labs EAX 3 (TM)` first when the
  EAX 3 option is on, and also requires the audio level of detail to allow
  Dolby.
- **Music.** BFME 2's music systems, per-view-type music state and music
  stack have no Zero Hour counterpart (Zero Hour plays music tracks without
  them; BFME 1 already has push and pop music requests and music systems):
  for each view type the manager records which of several music systems is
  active, and it can stack the playing music and resume it later. What the
  view types stand for is not established.
- **Large-group audio** is not in Zero Hour; it already exists in BFME 1.

## Modding notes {#sub_audio_modding}

- **Data-driven.** Sound definitions are INI. The audio blocks include
  `AudioEvent`, `MusicTrack`, `DialogEvent`, `AmbientStream`,
  `StreamedSound` and `Multisound`, plus `AudioSettings`, `MiscAudio`,
  `AudioLOD`, `LargeGroupAudioMap` and `LargeGroupAudioUnusedKnownKeys`.
  Sound files are found through the file system, so a BIG archive or a
  loose file can supply them.
- **Fixed file list.** The audio INI file names above are written in the
  manager's code. `SubsystemInterfaceList::initSubsystem` runs
  a subsystem's `init` before its `SubsystemLegend.ini` lookup, so any
  files a legend entry added for `TheAudio` would load after the built-in
  ones, and would count toward the INI checksum (see **Checksum** below);
  \ref sub_ini_legend describes the legend loader.
- **map.ini limits.** Sound definitions cannot be defined or overridden in
  a map's `map.ini`. Their parsers throw an INI exception when the file is
  loaded in the INI override mode (Zero Hour loads `map.ini` in that
  mode): the `MusicTrack`, `AudioEvent`, `DialogEvent`, `AmbientStream`
  and `StreamedSound` blocks share one parser, whose retail message is
  "You cannot define or override a %s in map.ini" with the block name
  filled in, and `AudioSettings` and `Multisound` have their own messages.
  Zero Hour's `MusicTrack`, `AudioEvent`, `DialogEvent` and
  `AudioSettings` parsers have no such check, and Zero Hour has no
  `AmbientStream`, `StreamedSound` or `Multisound` blocks. A retail error
  message also says that `AnimationSoundClientBehaviorGlobalSetting`
  cannot be overridden there. A `LargeGroupAudioMap` can be overridden in
  the override mode; `LargeGroupAudio::reset` removes the overrides.
- **Multisound rules** (from retail error messages): the only control flags
  are `PLAY_ONE` and `LOOP`; `LOOP` needs `PLAY_ONE` and only music-track
  subsounds; a multisound cannot list itself.
- **Large-group audio maps.** Within one `LargeGroupAudioMap`, `Sound`
  block names must be unique (retail error message).
- **Random or in order.** A sound effect that lists several files picks
  one at random by weight and rerolls rather than repeat the file played
  last; a control flag, or a sequential event, makes it cycle through the
  files in order instead. Other event kinds name a single file. Which INI
  control keyword sets that flag in BFME 2 is not confirmed.
- **File formats.** Files loaded through the cache must be PCM or IMA
  ADPCM WAV; any other format is recorded as failed and not loaded.
  Zero Hour: streams (music, speech) bypass this cache.
- **3D sounds must be mono.** A positional event whose file has more than
  one channel is not started as a 3D sample. Zero Hour also refuses such a
  file, in its file cache.
- **Ambient streams are capped.** The number of ambient streams comes from
  the audio level-of-detail settings, but the code limits it to two
  whatever those settings say.
- **Checksum.** The manager's and `LargeGroupAudio`'s hard-coded INI
  loads pass no CRC writer, so edits that reach the game only through those
  loads do not change the INI checksum that online games compare
  (\ref sub_engine_core). Files loaded through a `SubsystemLegend.ini`
  entry are different: `SubsystemInterface::loadIniFilesFromLegend` loads
  them through the subsystem list's writer, which `GameEngine::init` sets
  to the INI CRC writer, so any audio files a legend entry adds are
  checksummed. Whether retail's legend has a `TheAudio` entry, and which
  files it would name, is not checked here.
- **Determinism.** Sound variation draws only from the audio random
  stream and leaves the logic stream alone. `LargeGroupAudioUpdate` is
  different: it is a logic module and draws its update delay from the logic
  random stream. Changing which objects carry it, or its timing, changes
  the simulation, so every player and every replay needs the same data.
  Map scripts can also test music state (retail has the conditions
  `MUSIC_TRACK_HAS_COMPLETED` and `MUSIC_IS_PLAYING_FROM_SCRIPT`).
  Retail's script-editor text for `MUSIC_TRACK_HAS_COMPLETED` warns that
  it may only be used to start other music and that using it any other
  way breaks replays: music state is not kept in step across machines.
  Whether `MUSIC_IS_PLAYING_FROM_SCRIPT` carries the same risk is not
  established.
- **Saves.** Large-group audio state, the audio manager's polygon-trigger
  list and saved sound events are written into save games. Changing what
  they store breaks old saves unless the version handling is extended.
  `MilesAudioManager::loadPostProcess` throws an Xfer exception when a
  saved trigger ID matches no polygon trigger in the map (Zero Hour:
  `GameState::loadGame` catches such an exception and reports the load as
  failed).

## Remastering notes {#sub_audio_remastering}

- **Backend seam.** A new backend implements `AudioManager` and is returned
  by the `GameEngine` factory virtual that `GameEngine::init` calls to
  create `TheAudio` (Zero Hour: `createAudioManager`). Zero Hour's
  `GameAudio.h` shows the shape of that interface, but BFME 2 adds to it:
  `MilesAudioManager::onAudioLODChanged`, for one, has no Zero Hour
  counterpart. Check a replacement against BFME 2's virtual table, not
  Zero Hour's.
- **Miles dependencies.** `mss32.dll` with its providers in the `MSS\`
  directory, `AIL_quick_startup` with the `AudioSettings` output rate, bits
  and channels, Miles WAV parsing and ADPCM decompression, and Miles file
  callbacks into `TheFileSystem`. A port must replace or emulate all of them
  and keep archive access for sound files. The shipped `mss32.dll` is Miles
  6.6g (its version strings), and a replacement has to keep these
  behaviours of the shipped binaries:
  - `MilesAudioManager::selectProvider` sets the chosen 3D provider's
    rolloff factor to 0. With 0, the Miles Fast 2D provider (`msssoft.m3d`)
    applies no distance falloff up to a sample's maximum distance and, by
    default, silences it beyond; the EAX provider (`msseax.m3d`) hands the
    0 to the DirectSound 3D listener. A backend must not add a default
    falloff of its own.
  - The stream playback-rate command (`SetStreamPlaybackRateCommand::execute`,
    a name inferred in this tree) reads the data rate from
    `AIL_stream_info` and passes it, times a scale, to
    `AIL_set_stream_playback_rate`. Miles 6.6g reports that rate in samples
    a second (Hz), not bytes a second.
  - Two manager virtuals set Miles preference 0x2A to an `AudioSettings`
    value (`MixaheadLatency` or `MixaheadLatencyDuringMovies`) divided by
    preference 0x22, so a replacement must not report preference 0x22 as 0.

  Observed under a reimplementation of the Miles API, not on retail Miles:
  while that layer ignored the rolloff of 0 and applied a falloff of its
  own, battle sounds were quieter, and while it gave the data rate in
  bytes a second, 16-bit stereo music played four times too fast.
- **3D providers are hard-coded by name.** With the EAX option on, the
  manager tries `Creative Labs EAX 3 (TM)`. Next comes `Dolby Surround`
  when the Windows speaker setup and the audio level of detail allow it,
  then `Miles Fast 2D Positional Audio`. The speaker type comes from the
  DirectSound speaker configuration, with a headphone override. The video
  player is told when the provider changes.
- **Threads.** `MilesAudioManager::init` starts a worker thread with
  `CreateThread` that refills the loop buffers on a cycle time from the
  settings; the manager's mutex guards the shared state. The file cache's
  loader loop runs on a thread of its own and takes the cache's mutex. A
  replacement must keep that locking or remove the threads.
- **Timing.** Audio runs at the client frame rate, not the logic rate;
  large-group audio is updated from the logic side (\ref page_frame_loop).

## Following the reconstruction {#sub_audio_state}

This page describes behaviour, not progress. Which audio functions are
matched and named, and which of these files link, changes daily; the
queries in \ref page_reading_code_lookup answer it for any file or
function, for example `rg -F "/MilesAudioDevice/" reverse/functions.csv`
and the same search in `reverse/link_status.csv`. Expect file names,
private class views (\ref page_reading_code) and some names in these
directories to keep changing.

## Reading list {#sub_audio_reading}

- Zero Hour, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/`:
  `GameEngine/Source/Common/Audio/GameAudio.cpp`, `AudioEventRTS.cpp`,
  `GameEngine/Include/Common/AudioEventInfo.h`, `AudioSettings.h`,
  `AudioRequest.h` and
  `GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp`.
- BFME 1, in Open-BFME-1's `game/` tree: `GameEngine/Source/Common/Audio/`
  and `GameEngine/Source/GameLogic/LargeGroupAudio/`.
