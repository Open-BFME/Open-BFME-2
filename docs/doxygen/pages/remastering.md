# Remastering and porting {#page_remastering}

For people planning a remaster, a port or a replacement backend: where the
engine touches Windows and its libraries, the assumptions about screens,
timing and memory written into the code, and what must stay identical to play
with the original game, watch its replays and load its saves.

Matched functions reproduce the retail 32-bit Windows build byte for byte,
so every seam below is the original one, not a redesign. "Zero Hour:"
marks facts from the ancestor source that are not confirmed for
BFME 2. Several subsystem pages carry their own remastering notes with more
detail (for example
\ref sub_w3d_rendering_remastering "rendering",
\ref sub_network_remastering "networking" and
\ref sub_save_load_crc_remastering "saves, replays and CRCs"); this page is
the overview.

## The seams at a glance {#page_remastering_seams}

| Concern | Engine-side interface | Retail implementation | Subsystem page |
|---|---|---|---|
| Process and window | `GameEngine` | `Win32GameEngine`, `WinMain`, `WndProc` | \ref sub_engine_core |
| Launcher handshake | `CopyProtect` | named mutex, event and shared memory | \ref sub_engine_core |
| Files and archives | `FileSystem` | a loose-file back end and a `.big` archive back end | \ref sub_common_services |
| Display | `Display` | `W3DDisplay` | \ref sub_w3d_rendering |
| Graphics API | `DX8Wrapper` (WW3D2) | Direct3D 9, loaded at run time, plus D3DX 9 | \ref sub_w3d_rendering |
| Input | `Keyboard`, `Mouse` | `DirectInputKeyboard`, `W3DMouse` | \ref sub_gameclient |
| Audio | `AudioManager` | `MilesAudioManager` over the Miles Sound System | \ref sub_audio |
| Movies | `VideoPlayer`, `VideoBuffer` | VP6 decoder, `W3DVideoBuffer` | \ref sub_gameclient |
| Network | `NetworkInterface`, `Transport`, `LANAPI` | Winsock UDP; GameSpy SDK and EA online code | \ref sub_network |
| Timers | called directly | `timeGetTime`, `QueryPerformanceCounter` | \ref page_frame_loop |
| Memory | `MemoryPool` API | EA `GeneralAllocator` heaps | \ref sub_memory |
| UI | Apt runtime, `GameWindowManager` | Apt movies; window layouts | \ref sub_gui_apt |

The engine reaches most of these classes through virtual factory methods on
`GameEngine` and `W3DGameClient`, such as `W3DGameClient::createGameDisplay`
(\ref page_architecture_seams). These overrides are where a replacement
backend plugs in. Zero Hour: `Win32GameEngine`'s overrides are where the
W3D, Win32 and Miles implementations of the abstract subsystems are chosen.

## Process, window and launcher {#page_remastering_win32}

`WinMain` (\ref page_startup) does the Windows-specific setup:

- It reads the command line as UTF-16 and converts it to UTF-8. If the first
  argument is `-DX` followed by hex addresses, it resolves each address
  through the debug stack walker and returns without starting the game.
  Otherwise it reads `-win`, `-fullscreen`, `-xpos` and `-ypos`, and
  recognises `-automatch` without acting on it. The
  \ref page_startup_winmain "start-up page" gives the full order of these
  steps.
- If `lotrsec.big` is not visible from the current directory, it changes to
  the executable's directory. Every relative data path depends on this.
- It loads `<language>Splash.jpg` (or `.bmp`) through ATL's `CImage`, which
  uses GDI+. A named mutex allows one running copy; a second start brings the
  first window to the front and exits.

**The launcher handshake.** `game.dat` does not run on its own.
`CopyProtect::isLauncherRunning` succeeds only if the launcher has already
created a named mutex. `CopyProtect::notifyLauncher` then waits up to a
minute for a named event, signals it, and waits up to ten seconds for a
thread message (`0xBEEF`) carrying a file-mapping handle, which it maps. If
either step fails, `WinMain` returns before `GameMain`. `CopyProtect::validate`
then checks the mapped data; its result does not stop start-up but is stored
(`CopyProtect::setVerified`) for later code to read. A port that starts the
engine directly has to replace the handshake and decide what that stored
result should be.

`Win32GameEngine::update` pumps the Windows message queue after each engine
update. While the window is minimised it sleeps in a loop instead, unless a
LAN or online game is running, so a minimised single-player game stops.
Keyboard input is DirectInput (`DirectInputKeyboard`). The mouse is a
`W3DMouse`, a `Win32Mouse` subclass: the game client's mouse factory also
stores it in `TheWin32Mouse`, and `WndProc` passes mouse window messages to
it with `Win32Mouse::addWin32Event`.

`WndProc` drops two mouse messages by position, as Zero Hour's does.
`WM_MOUSEMOVE` is ignored outside the rectangle `GetClientRect` returns,
and `WM_MOUSEWHEEL`, whose position is in screen coordinates, outside the
rectangle `GetWindowRect` returns. The window is created 800 by 600, and
in fullscreen every `SetWindowPos` call the game makes keeps size and
position. Both tests therefore rely on Direct3D's exclusive mode to make
the window cover the screen, and a backend that leaves the window at its
startup rectangle loses pointer moves and wheel turns outside it. Observed
under a reimplementation of Direct3D 9, not on retail Windows: while that
layer left the window alone, hover and wheel worked only inside the
startup rectangle.

`Mouse::createStreamMessages` sends the wheel as whole notches: for each
buffered wheel event it divides that event's delta by 120 and discards the
remainder; deltas are not summed across events. An event whose delta is
less than 120 in size produces a wheel message of zero notches, which
`rawMouseToWindowMessage` reads as a turn down. A trackpad or
smooth-scrolling wheel that sends small deltas therefore needs a backend
that gathers them into 120-unit events.

## Files and archives {#page_remastering_files}

All game data is read through `TheFileSystem`, a front end over a loose-file
back end and a `.big` archive back end. `GameEngine::init` has it create both
and mount the archives. Zero Hour and BFME 1 call the two back ends
`Win32LocalFileSystem` and `Win32BIGFileSystem`; `rg` the name in
`reverse/functions.csv` for the BFME 2 evidence behind a row.

By default `FileSystem::openFile` looks in the mounted `.big` archives first
and in loose files second, so a loose file is used only when no archive holds
that name. One flag reverses this. The `-mod` switch (`parseMod`) sets it,
and so does the `-preferLocalFiles` switch (`parsePreferLocalFiles`). The
start-up code that creates the two back ends also sets it when `shaders.big`
is not on disk. With the flag set, loose files are tried first and the
archives last, and the loose-file lookup tries, in order, an optional extra
directory, then `lang\<language>\`, then the plain name; without the flag
it tries only the plain name. `<language>` is the registry language
setting, which `GameEngine::init` records just before it creates the file
system; the archive back end uses the same setting for the `lang\`
archives below. The extra directory is empty unless another routine sets
it. That routine also sets the flag and mounts the directory's `*.BIG`
archives. An optional path filter can refuse a name before either back end
is tried.

`parseMod` also records the mod path in the global data, as a mod directory
or a mod `.big` file. How that path is then used is not established.

The archive back end mounts the `.big` archives in this order:

1. `lang\<language>*.big`, which includes the language's audio archive;
2. `lang\EnglishAudio.big`, only if `lang\<language>Audio.big` is not on disk;
3. `*.big` in the game directory;
4. `apt\*.big`.

The `lang\<language>*.big` archives are mounted with a flag that the
`EnglishAudio.big` fallback and the other archives do not get. Zero Hour:
that argument lets an archive's files replace files already mounted.

Points a port must keep:

- Paths are built mostly with backslashes (`lang\`, `Data\INI\`); the shader
  paths below use forward slashes. The directory listings of both back ends
  sort names without regard to case, and on Windows loose-file lookups ignore
  case too, so a port to a case-sensitive file system should expect to need
  a case-folding layer.
- The loose-file back end converts each UTF-8 name to UTF-16 and calls the
  wide-character Windows and C runtime functions, so a port needs the same
  Unicode path support.
- Miles reads sound files through callbacks that open them with
  `TheFileSystem` (`MilesAudioManager::init`), which is how it reaches audio
  inside archives.
- `InitializeAssetManager` (called from `W3DDisplay::init`) reads
  `asset.dat` from up to three places, each one that exists: an `asset.dat`
  entry inside the archive file named in the global data, then
  `<asset directory>\asset.dat`, then `asset.dat` in the current directory.
  The last is required, or the function returns false.
- Some code opens files directly, not through `TheFileSystem`.
  `InitializeAssetManager` uses C file I/O and parses the archive's BIG
  header itself. `RecorderClass::startRecording` writes replays with
  `_wfopen`, and the effect loader below can compile a shader file from disk.
  A replacement file layer must cover these direct opens as well.

## Rendering {#page_remastering_render}

Rendering is Westwood's WW3D2 on top of `DX8Wrapper`. Despite the name,
BFME 2 uses Direct3D 9: `DX8Wrapper::Init` loads `D3D9.DLL` at run time,
looks up `Direct3DCreate9`, and also picks up the `D3DPERF` marker functions
when a profiler is attached. The source keeps WW3D's Direct3D 8 type names
and calls the Direct3D 9 interface underneath.

The game also imports D3DX from `d3dx9_27.dll`, the D3DX runtime of the
DirectX 9.0c August 2005 SDK (\ref sub_wwlib_thirdparty). The functions in
`game.dat`'s import table for that DLL fall into five groups:

- textures, cube and volume textures and surfaces: creation, loading,
  filtering and image-information queries
  (`D3DXCreateTextureFromFileInMemoryEx`, `D3DXFilterTexture`,
  `D3DXGetImageInfoFromFileInMemory` and others);
- matrix, vector, plane and quaternion math (`D3DXMatrixInverse`,
  `D3DXQuaternionSlerp`, `D3DXVec3CatmullRom`, `D3DXPlaneFromPointNormal`
  and others);
- effects (`D3DXCreateEffect`, `D3DXCreateEffectFromFileA`);
- run-time shader assembly (`D3DXAssembleShader`,
  `D3DXGetShaderInputSemantics`);
- the vertex-format size helper `D3DXGetFVFVertexSize`.

`FXShaderAsset::Impl::Load` loads a precompiled `Shaders/Compiled/<name>o`
through `TheFileSystem` when that file exists. Otherwise it compiles
`Shaders/<name>` with `D3DXCreateEffectFromFileA`, which reads the file
itself. A port without D3DX has to replace every function in that import
table, not only the effect loader (\ref sub_w3d_rendering_remastering).

`W3DDisplay::init` creates the device:

- The resolution comes from the global data, and the colour depth is always
  32 bits. If WW3D cannot initialise, it throws. If the device cannot be
  created at the configured size, it writes 800x600 into the global data
  and retries; if that fails too, it throws. `GameEngine::init` catches the
  error, shows the localized Direct3D failure message and exits.
- In a window, the swap interval is set to 0 (no vertical sync); full screen,
  the cursor is clipped to the window. The 2D renderer's coordinate range is
  the screen size in pixels.
- Device creation, and much other device-layer code, runs under a recursive
  device lock that one thread owns at a time. `W3DDisplay::init` holds it
  in a scoped guard around device creation, so the throw when the 800x600
  retry also fails releases it. Which threads contend for it is not
  established; a replacement must keep that serialisation or show it is not
  needed.

There are two levels at which a new renderer can attach: below `DX8Wrapper`
(keep W3D, translate its Direct3D 9 and D3DX calls), or at `Display` and the
`W3DGameClient` factories (replace W3D). The second also means replacing the
draw modules that `W3DModuleFactory` registers.

## Audio and movies {#page_remastering_audio}

`TheAudio` is a `MilesAudioManager`. Its `init` sets the system volumes,
allocates the loop buffers and starts a worker thread for them, opens the
device and installs the file callbacks. `MilesAudioManager::openDevice`
points Miles at the `MSS\` directory and starts it. The destructor sets the
flag that ends the loop-buffer thread's loop, waits for the thread to exit,
and clears `TheAudio` if it still points at the manager. A replacement
implements `AudioManager`; the sound definitions are INI data
(\ref sub_audio).

Movies: `VideoPlayer::init` reads `Video.ini` from `Data\INI\Default\` and
then `Data\INI\`. Frames are decoded by an On2 VP6 decoder compiled into
`game.dat` (`Code/Libraries/Source/VP6`). The `Theora` directory beside it
holds helper routines of that decoder whose source text comes from
libtheora; it is not a Theora decoder. `W3DDisplay::createVideoBuffer`
supplies the surface the frames are drawn into.

## Networking and online services {#page_remastering_network}

Multiplayer is lockstep over UDP: `NetworkInterface` is the engine-facing
seam, the sockets sit behind `Transport` and the `UDP` class, and `LANAPI`
runs LAN discovery and lobbies over UDP broadcast
(\ref sub_network_remastering).

Online play depends on servers at host names compiled into `game.dat`. The
vendored GameSpy SDK names `peerchat.gamespy.com`, per-game hosts built from
patterns such as `<game>.master.gamespy.com` and
`<game>.available.gamespy.com`, and others (`gpcm.gamespy.com`,
`gpsp.gamespy.com` and `gamestats.gamespy.com`). A redirect has to cover the
per-game names, not only fixed ones. EA's online code names hosts under
`ea.com`: `fesl.ea.com` and `demangler.ea.com`; `game.dat` also contains
`bfme2.fesl.ea.com`. (External fact, not from the code: GameSpy's hosted
services closed in 2014.) A remaster cannot assume these hosts answer. It
has to supply replacement services, redirect these names, or drop online
play.
For online games the peer-to-peer game socket also comes from the online
NAT negotiation, so a replacement service must provide that transport too.
LAN play needs no outside server.

## Assumptions baked into the code {#page_remastering_assumptions}

**Resolution and aspect ratio.** Many client-side sizes are scaled from a
fixed design resolution, with separate width and height factors, so they
stretch on screens that are not 4:3. `Drawable::drawVeterancy` and
`GadgetListboxCreateScrollbar` scale from 1024x768;
`ControlBarResizer::sizeWindowsAlt` and `W3DGadgetHorizontalSliderImageDraw`
from 800x600. `GlobalLanguage::adjustFontSize` scales font sizes by
width / 1024 only, so on a wide screen text grows relative to the screen
height. Window layouts are scaled the same way (\ref sub_gui_apt_remastering).
How the Apt player fits a movie's stage to the screen is not established;
do not assume it is resolution-independent.

**Logic rate and render rate.** The logic runs at a nominal 5 ticks a second
and the client at 30 frames a second. Both are built into `game.dat` with no
known INI field. `GameLogic::update` runs a logic frame in six phases, and
the rate ratio is also six. As in BFME 1, `GameEngine::update` hands out one
phase per client frame: it advances a client-frame period on each call that
a script-engine check does not skip, starts a new logic frame after six (a
literal, not the ratio), and passes the period as the phase to a
`GameEngine` logic step that calls `GameLogic::update`. That step runs the
following phases in the same call only when the rate ratio is below six. If
phase 1 does not go ahead (for example, with no network running, while the
game is paused; in a network game, while the network has no frame to
advance), the period is held and phase 1 is tried again on the next client
frame. At a ratio of six or more, then, a logic frame takes at least six
client frames, and where nothing skips a client frame or holds phase 1 back
the simulation runs at one sixth of the real client frame rate. A higher
frame rate is not a client-only setting; see
\ref page_frame_loop_remastering.

**Floating point.** `setFPMode` resets the x87 unit and sets 24-bit
precision with round-to-nearest. Its callers include `GameLogic::init`,
`GameLogic::reset`, the start of a new game and the INI loaders
(`INI::load`, `INI::loadFile`); `GameLogic::update` calls it before its
simulation work and `GameLogic::getCRC` before computing the CRC. The INI
loaders set it before they parse, so INI values are read under this mode
too. The retail code was built by Visual C++ 7.1, and many
units, including the one holding `GameLogic::update`, are compiled with
`/arch:SSE` to reproduce it. That flag lets the compiler use SSE instructions
for single-precision arithmetic; the x87 mode does not govern those.
Lockstep and replays need every machine to compute the same logic results
bit for bit, so matching retail means reproducing that instruction-level
float behaviour, which a different compiler or a 64-bit build does not do by
itself.

**32-bit layouts.** Every class layout assumes 4-byte pointers, and many
source files describe a class by member offset rather than through a shared
header (\ref page_reading_code). Saves, replays and network commands store
values as x86 little-endian memory images (\ref sub_save_load_crc_remastering).
A 64-bit build has to give up byte matching and reconcile those layouts
first.

**Memory.** Global `operator new` and `delete` call through function
pointers that start-up code fills by looking up the exported `MemoryPool`
functions (`MemoryPool::_Allocate`, `MemoryPool::_Free` and others) in the
game's own export table. Those functions sit on EA `GeneralAllocator` heaps
and pick a per-thread current heap. Apt has its own pool managers. Replacing
the allocator means replacing that API as a whole (\ref sub_memory).

## Staying compatible with the original {#page_remastering_compat}

| To keep working with | What must stay identical |
|---|---|
| Retail players (LAN and online) | Everything `GameLogic` computes: objects and their modules, AI, scripts, the logic random stream, the float mode, the logic rate and phase layout. The command encoding and packet format (\ref sub_network_remastering). The values sent on joining: `LANAPI::RequestGameJoin` puts the executable identifier, the INI CRC, a further BFME-specific CRC from the global data (its meaning is not established) and the registry serial in the join request. Whether the LAN host compares them is not established; in Zero Hour's source the comparison is commented out (\ref sub_network). The GameSpy code registers `exeCRC`, `iniCRC`, `cmdCRC` and `gCRC` keys for its staging rooms, and the online custom-match screen refuses to join a room whose executable identifier, INI CRC or that further CRC differs from the player's own. |
| Desync detection | `GameLogic::getCRC`, which runs the logic state through the CRC form of `Xfer`. In multiplayer, each machine sends the value as a message every N logic frames, where N is the CRC interval stored in the game's settings (\ref sub_save_load_crc_crc). |
| Retail replays | The `BFME2RPL` format: the header that `RecorderClass::startRecording` writes (it includes the signature, version strings, the INI CRC, the player slots and any custom heroes; \ref sub_save_load_crc_replays lists the rest), then the commands that `RecorderClass::writeToFile` appends. On playback, `RecorderClass::playbackFile` reads the header and `RecorderClass::appendNextCommand` feeds the commands back through the same logic (\ref sub_save_load_crc_replays). |
| Retail saves | Each object's `xfer` order and version (`Xfer::Version`), and the named blocks that `GameState::init` registers (`CHUNK_GameState`, `CHUNK_Campaign` and others). `CHUNK_Audio` is the audio manager, so a replacement audio backend must still read and write it (\ref sub_save_load_crc). |

Saves store map paths in a portable form
(`GameState::realMapPathToPortableMapPath`), not tied to the install
directory. How the executable identifier is computed is not established.
A remaster that changes any logic-side behaviour, including a bug fix,
cannot stay compatible with retail multiplayer or retail replays. It can
keep loading retail saves only by reading the old versions.

## Modding notes {#page_remastering_modding}

- A data-only mod touches none of these seams. By default a loose file does
  not replace a file of the same name inside a mounted `.big`. The `-mod` or
  `-preferLocalFiles` switch makes loose files win (see
  \ref page_remastering_files).
- Anything that changes logic results breaks play with unmodified clients
  and existing replays. Changing INI data that the INI CRC covers also
  changes the INI CRC, even when the logic is unaffected. The INI CRC is
  sent with LAN join requests (whether the host checks it is not established;
  \ref sub_network), checked by the online custom-match join, and recorded
  in replays. `GameEngine::init` computes that CRC with a CRC `Xfer` that
  it gives to the subsystem list and to its loads of `Water.ini`, `Fire.ini`
  and `Environment.ini`, then adds a CRC of the loaded Create-a-Hero heroes,
  so custom-hero data feeds it too. \ref sub_save_load_crc_crc says which
  files it covers.

## Reading list {#page_remastering_reading}

- How much of each area is matched changes daily: \ref page_mainpage_state
  explains the figures, `python3 tools/progress.py` recomputes them, and
  `rg` on a name in `reverse/functions.csv` gives one function's status.
- \ref page_architecture, \ref page_startup, \ref page_frame_loop, and
  `docs/bfme2-network-timing-path.md` for frame rates and network pacing.
- BFME 2 sources:
  - `Code/GameEngine/Source/Main/WinMain.cpp`
  - `Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp`
  - `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayInit.cpp`
  - `Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp`
- Zero Hour sources, under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/`
  (use the `GeneralsMD` copy, not the `Generals` one):
  - `Win32Device/Common/Win32GameEngine.cpp`
  - `Win32Device/Common/Win32BIGFileSystem.cpp`
  - `W3DDevice/GameClient/W3DDisplay.cpp`
