# The frame loop: client frames and logic frames {#page_frame_loop}

After \ref page_startup, `GameEngine::execute` runs the main loop until the
game quits. Each pass is one *client frame* (input, user interface, audio and
drawing), run at each machine's own pace. The deterministic simulation in
`GameLogic` advances in slower *logic frames* of six phases each, which every
machine in a network game must run identically. This page explains how the
two rates fit together and how input becomes a game action.

Most of a frame's path is byte-matched: `Win32GameEngine::update`, the client
half (under a placeholder name), `GameClient::update`,
`MessageStream::propagateMessages`, `GameLogic::update`, `setFPMode` and the
network's admission queries. `GameEngine::execute`, `GameEngine::update` and
the phase scheduler are not yet reconstructed, so this page gives only their
contract. `rg` a name in `reverse/functions.csv` for status; many sources below
are split units that `reverse/tu_map.csv` will merge, so search by name.

## Where it lives {#page_frame_loop_where}

| Class (global) | Role in the frame | Source today, under `Code/GameEngine/Source/` |
|---|---|---|
| `GameEngine` (`TheGameEngine`) | Owns the loop, the client pacing state and `reset` | `Common/GameEngine.cpp` and split files beside it |
| `Win32GameEngine` | Windows subclass: message pump, minimised-window wait | `Main/Win32GameEngineUpdate.cpp` |
| `GameClient` (`TheGameClient`) | Input, drawables, display and UI on this machine | `GameClient/GameClientDrawableTOC.cpp` |
| `GameLogic` (`TheGameLogic`) | The simulation, `GameLogic::update(int phase)` | `GameLogic/System/GameLogicInit.cpp` |
| `MessageStream` (`TheMessageStream`) | This frame's input messages and their translators | `Common/MessageStream_propagateMessages.cpp` and siblings |
| `CommandList` (`TheCommandList`) | Commands waiting for the next logic frame | created by `GameEngine::init` |
| `NetworkInterface` (`TheNetwork`) | Whether the next logic frame may run | `Common/NetworkInterfaceFrameAdvance.cpp` and `...FramePacing.cpp` |

## Two clocks {#page_frame_loop_clocks}

- **Client frame:** one pass of the main loop. The nominal render rate is 30
  per second; the real pass rate depends on the frame-rate cap and the machine.
- **Logic frame:** one simulation step at a nominal 5 per second (200 ms).
  Both rates are initialised data in the retail executable (`game.dat`) with
  no known INI field. Phase 1 of `GameLogic::update` advances the logic frame
  counter when a still-unidentified check allows it and time is not frozen.
- **Phases:** `GameLogic::update` takes a phase from 1 to 6, doing a different
  share of the logic frame in each; the rate ratio is also six. BFME 1's
  `GameEngine::update` passes its client-frame period (1 to 6) as the phase,
  one per client frame; for BFME 2 this is unconfirmed.
- **Sub-frame position:** `GameEngine` keeps a 0..1 ratio, the client's
  position between two logic frames; its readers are not yet traced.

## One pass of the main loop {#page_frame_loop_pass}

1. **`GameEngine::execute`** (contract) loops until the engine is quitting and
   calls the `update` virtual once per pass. Zero Hour: it also catches
   exceptions around each update and waits to stay under a frame-rate cap.
   BFME 2's `GameEngine::init` sets that cap from `TheGlobalData`.
2. **`Win32GameEngine::update`** calls `GameEngine::update`, then pumps Windows
   messages. While the window is minimised it instead sleeps in 5 ms steps,
   pumping messages and updating `TheLAN`, until it is restored, the game
   quits, or the game is a LAN or online match. A minimised single-player game
   therefore stops; a network game keeps going.
3. **`GameEngine::update`** (contract): the client half, then the logic half.

## The client half {#page_frame_loop_client}

A `GameEngine` virtual in `Common/GameEngineClientSubsystems.cpp` (its name is
still a placeholder). In order, it:

1. calls `GameLogic::deleteLoadScreen`, advances the `GameClient` frame number
   while a client flag says time is running, and updates the window manager.
   `GameLogic::update` sets and clears that flag; BFME 1's
   `GameEngine::update` also writes it, and BFME 2's is not reconstructed;
2. when `TheNetwork` exists, **skips** the rest of the frame if
   `NetworkInterface::getFramePacingStatus` (for a client, the admitted logic
   frames not yet run) exceeds a fixed threshold (a lower one while the
   client-frame period kept on `GameEngine` is ahead of its counter). A global
   time scale below 1 or a period of 1 disables the test, which also adjusts
   an adaptive limit on `GameEngine` whose consumer is not traced. A skipped
   frame is counted and returns before `GameClient::update`: no radar, input,
   drawing, message, audio or network work;
3. updates the radar, runs `GameClient::update` and moves this frame's messages
   on with `MessageStream::propagateMessages`;
4. runs the timed-operation queue; while it holds input locked, `InGameUI`
   engine input is off and the mouse cursor hidden;
5. updates audio (`TheAudio`) and gives the network a light update.

`GameClient::update` is where input enters and the frame is drawn. After the
snow, cloud-break and fire managers and 2D animations, it runs the keyboard,
the EVA announcers and the mouse (`update`, then `createStreamMessages`).
During the intro it only draws. Otherwise it updates the window manager, the
video player and, unless time is frozen (camera, script or pause) or the
client frame has not advanced, every `Drawable`. Last, it updates the display,
draws its views (`drawViews` renders the 3D scene) and updates display
strings, the shell and `InGameUI`.

## The logic half {#page_frame_loop_logic}

The logic half (contract; see `docs/bfme2-network-timing-path.md`, *the timing
note*) consults the network's frame-admission queries,
`NetworkInterface::getFrameAdvanceCount` and `getFramePacingStatus`, then
calls `GameLogic::update(phase)` for each phase that is due. Each call that
reaches the simulation work runs `setFPMode` first, then:

| Phase | Work |
|---|---|
| 1 | Freeze test; advance the logic frame counter; `ScriptEngine`, `LuaScriptEngine`, `TerrainLogic` and `TheVictorySystem` updates; for a multiplayer recording (not in skirmish, and behind one more unidentified check), a CRC message every N logic frames, where N is the game's CRC interval held in `TheGameInfo`; recorder, trigger, weather and damage-over-time updates; every `TheCommandList` message goes to the logic message dispatcher and the list is reset; per-object status work |
| 2 | `ThePartitionManager` and `TheCollisionManager`; a per-object hook for objects not yet handled this logic frame |
| 3 and 4 | First and second half of update-module list 0 |
| 5 | Update-module lists 1 and 2; then `TheAI`, shroud, large-group audio, the destroy list, the weapon and locomotor stores, the team factory and several BFME 2 managers |
| 6 | Update-module list 3 |

- **Update modules sleep** (\ref sub_objects_modules). Phases 3 to 6 skip a
  module until the logic frame it asked to wake on, or while its object is
  disabled in a way it does not handle. `update` returns the frames to sleep;
  phases 4 to 6 move modules that sleep forever to a separate list.
- **Freezes.** While the camera or a script freezes time, phase 1 does not
  advance the counter and, unless a pending command forces the script engine
  on (Zero Hour: a clear-game-data message, so quitting works), skips its
  other work and clears the client's time-running flag, halting drawable
  updates. Only phase 1 tests for a freeze.

## From input to game action {#page_frame_loop_messages}

1. **Raw input.** `GameClient::update` has the keyboard and mouse append
   `GameMessage`s to `TheMessageStream`.
2. **Translation.** `MessageStream::propagateMessages` passes every message to
   each translator, lowest priority value first (`attachTranslator` keeps them
   sorted); a translator can destroy one. Survivors go to `TheCommandList`.
3. **Admission.** For a non-router client, `getFrameAdvanceCount` allows the
   next logic frame only when the connection manager reports that frame's
   commands complete; the packet router paces by timer. How received commands
   reach the logic frame is not yet traced. Zero Hour: commands are exchanged
   per frame and run once all players' commands have arrived.
4. **Execution.** Phase 1 of a later logic frame dispatches each command.

## How it fits {#page_frame_loop_fits}

Owners: \ref sub_engine_core, \ref sub_gamelogic_map, \ref sub_gameclient
(split explained in \ref page_architecture). \ref sub_network admits logic
frames; \ref sub_save_load_crc covers the CRC and recorder;
\ref page_core_frameworks covers messages. Logic-frame work is mostly
\ref sub_scripting and \ref sub_objects_modules; \ref sub_gui_apt,
\ref sub_audio and \ref sub_w3d_rendering run on the client half.

## BFME 2 compared with Zero Hour {#page_frame_loop_zh}

- **Rates.** Zero Hour runs 30 logic frames per second, like its render rate,
  calling `GameLogic::update()` (no phase) once per client frame when the
  network has that frame's data or, offline, when not paused. The phases come
  from BFME 1: Open-BFME-1's `GameLogic.cpp` has the same six-phase update and
  module lists, and its `GameEngineFramePacing.cpp` the same client-frame skip.
- **Module scheduling.** Zero Hour keeps sleeping modules in one priority queue
  ordered by wake frame; BFME 2 uses four phase lists plus a sleeping list.
- **CRC.** Zero Hour also builds it in single-player games and replays
  (`REPLAY_CRC_INTERVAL`). BFME 2 builds it only for multiplayer recordings,
  apart from a forced-frame override.
- **Changes.** BFME 2 adds `LuaScriptEngine`, a trigger manager, and weather
  and damage-over-time updates; victory checking (Zero Hour:
  `TheVictoryConditions`) runs in phase 1 via `TheVictorySystem`. A
  scene-capture mode (switch not yet named) appends client state to
  `scenecapture.dat` beside the map, then quits.

## Modding notes {#page_frame_loop_modding}

- **`GameLogic::update` is lockstep code.** Modules, AI, weapons, scripts and
  Lua all run inside it, so a change must give the same result on every
  machine or the periodic CRC exposes a mismatch. Zero Hour: replays are
  re-simulated from recorded commands, so logic changes alter existing replays.
- **Durations become logic frames.** INI durations are in milliseconds; the
  parsers multiply by a fixed 0.005 (frames per millisecond at 5 Hz) and round
  integer durations up. Map-script timers in seconds use the same scale, and a
  randomised timer draws from the logic random generator. Update modules sleep
  in whole logic frames; scripts, Lua and commands run once per logic frame.
- **Not data-driven:** the nominal rates, the duration scale, the six phases
  and their module lists. Many systems (objects, scripts, AI, network, some
  client code) read the logic rate from one global, but the duration scale is
  separate and the frame gate and phase scheduler compare the rate ratio with a
  literal 6 (timing note), so changing the global alone is inconsistent. Any
  change breaks play with unmodified clients and replays.
- **Frame-rate cap.** Zero Hour reads it from `GameData.ini`
  (`FramesPerSecondLimit`, `UseFPSLimit`); BFME 2's field names are unconfirmed.

## Remastering notes {#page_frame_loop_remastering}

- **Render rate is coupled to logic scheduling.** Per the timing note, phases
  are handed out per client frame from the rate ratio. Open-BFME-1's mod notes
  report BFME 1's offline game speed as the frame rate divided by six, so
  raising the cap alone speeds up a skirmish; for BFME 2 this awaits the
  scheduler's reconstruction. Decoupling the rates means changing it.
- **Floating point.** On each `GameLogic::update` that reaches the simulation
  work, `setFPMode` resets the x87 unit to 24-bit precision, round-to-nearest.
  Retail also has SSE code (the timing note records SSE maths in the
  `GameEngine` frame-ratio helper), so a port that must match retail clients or
  replays, 64-bit or not, has to reproduce each function's float behaviour.
- **Platform seams.** A different window, renderer, audio or timer backend
  connects at the Windows pump in `Win32GameEngine::update`, the display's
  `drawViews` in `GameClient::update`, `TheAudio` in the client half, and
  `timeGetTime` (`GameEngine::reset`, the network's stall timer) and
  `QueryPerformanceCounter` (the packet router's pacing).

## Reading list {#page_frame_loop_reading}

- The timing note: pacing, admission, scheduler arithmetic, open hypotheses.
- Zero Hour: `Common/GameEngine.cpp` and `GameLogic/System/GameLogic.cpp`
  under `GeneralsMD/Code/GameEngine/Source/`.
- BFME 1: `GameLogic/System/GameLogic.cpp` and `Common/GameEngineUpdate.cpp`
  under Open-BFME-1's `game/GameEngine/Source/`.
