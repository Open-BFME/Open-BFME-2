# WWLib and third-party libraries {#sub_wwlib_thirdparty}

This subsystem is the support code that `game.dat` links in but that holds no
game rules: Westwood's general-purpose library, WWLib, and the outside
libraries EA built the game with, from compression codecs and the Lua
interpreter to pieces of Microsoft's runtime. Other subsystems use it for
files, chunked asset formats, registry access, CPU detection, threads, data
compression, scripting and the STL containers. Most of it is Westwood
code shared with Zero Hour or a published library at a known release.

Its API group is \ref grp_wwlib_thirdparty. The source layout and the
placeholder names are explained on \ref page_reading_code.

## Where it lives {#sub_wwlib_thirdparty_where}

| Path | What is there |
|---|---|
| `Code/Libraries/Source/WWVegas/WWLib/` | Westwood's foundation library (below), plus STLport template instantiations and address-named staging files |
| `Code/Libraries/Source/WWVegas/WWSaveLoad/` | a few pieces of Westwood's definition and parameter framework (`TwiddlerClass`, `DefinitionClass`) |
| `Code/Libraries/Source/WWVegas/WWDownload/` | Westwood's FTP download client (`Cftp`, `CDownload`) and its registry helpers |
| `Code/Libraries/Source/Compression/` | `CompressionManager`, EA's EAC codecs (RefPack, Huffman, binary tree), zlib and LZH-Light |
| `Code/Libraries/Source/Lua/` | the Lua interpreter: Lua 4.0.1 with EA's changes |
| `Code/Libraries/Source/STLport/`, `Code/stlport/` | parts of the STLport runtime library (iostreams, locale, strings) |
| `Code/Libraries/Source/ATL/`, `GdiPlus/` | ATL 7.1's `CImage` and the GDI+ 1.0 inlines it emits |
| `Code/Libraries/Source/VP6/` | the On2 VP6 video decoder, being rebuilt as a clean room from written specifications |
| `Code/Libraries/Source/Theora/` | two VP3-heritage helpers of the VP6 decoder, written from libtheora text (libtheora itself is not linked) |
| `Code/Libraries/Source/Benchmark/` | BYTEmark (nbench), the CPU benchmark |
| `Code/Libraries/Source/CRT/` | MSVC 7.1 runtime pieces compiled from source (run-time-check support) |
| `vendor/` | inputs not compiled from source: the STLport 4.5.3 headers and Microsoft libraries (C runtime, comsupp, dxerr9, the D3DX 9 import library), each with a provenance file |

Neighbouring directories belong to other pages: `WWMath`, `WW3D2` and
`wwshade` to \ref sub_w3d_rendering; `WWDebug` (which in BFME 2 holds EA's
debug library) and the EA `debug`, `profile` and `string` libraries to
\ref sub_common_services; `xfer` to \ref sub_save_load_crc; `Apt/` and `EA/`
to \ref sub_gui_apt; DirtySock to \ref sub_network (the GameSpy SDK is not
here but under `Code/GameEngine/Source/GameNetwork/GameSpy/`, also
\ref sub_network); `assetmanager` to \ref sub_common_services;
`partitionmanager` to \ref sub_gamelogic_map; `subsystem` to
\ref sub_engine_core. The list is not complete: `file/`, for example, holds
one address-named row that no page owns yet.

## WWLib: the Westwood foundation {#sub_wwlib_thirdparty_wwlib}

WWLib is the library Westwood's W3D engine is built on, and Zero Hour ships
the same library. The parts BFME 2 has recovered under their own names:

- **Files.** `FileClass` is the abstract file; `RawFileClass` wraps a Win32
  file and `BufferedFileClass` adds a read buffer
  (\ref grp_w1_wwlib_targa_bufffile, which also covers the `Targa` image
  reader and writer). WWLib keeps two global file factories that decide
  which `FileClass` a library caller gets: a read factory (default
  `SimpleFileFactoryClass`, buffered disk files) and a writing factory
  (`RawFileFactoryClass`, raw Win32 files).
- **Chunk files.** `ChunkLoadClass` and `ChunkSaveClass` read and write
  Westwood's nested chunk format: chunks with a type id and a size whose top
  bit marks a chunk that holds sub-chunks, plus small "micro chunks". W3D
  assets use it: `MeshGeometryClass::Load_W3D`, `HTreeClass::Load_W3D`,
  `HRawAnimClass::Load_W3D`, `VertexMaterialClass::Load_W3D` and
  `SceneClass::Load` all read through `ChunkLoadClass`.
- **Westwood INI.** `INIClass` reads and writes section-and-key text. It is
  not the parser for the game's data INI files, which is the engine's own
  (\ref sub_ini). Its known users are
  `VertexMaterialClass::Parse_Mapping_Args`, which parses a W3D material's
  texture-mapper arguments as INI text and passes the section to the mapper
  constructors (`GridTextureMapperClass`, `WSEnvMapperClass` and others),
  and `RegistryClass::Load_Registry` and `RegistryClass::Save_Registry`.
- **Registry.** `RegistryClass` reads and writes values under one key. The
  renderer stores its chosen device there:
  `DX8Wrapper::Registry_Load_Render_Device` and
  `DX8Wrapper::Registry_Save_Render_Device` construct it.
- **Strings and containers.** `StringClass` and `WideStringClass` (the
  engine's `AsciiString` and `UnicodeString` are a separate family,
  \ref sub_common_services); `VectorClass`, `DynamicVectorClass`,
  `HashTableClass`, `GenericMultiListClass` and `ObjectPoolClass`
  (\ref sub_memory).
- **Streams.** The `Pipe` and `Straw` families: push and pull byte streams
  that chain buffer, file, Base64 and cache stages
  (\ref grp_w1_wwlib_streams).
- **Checksums and crypto.** CRC routines (`CRC`, `CRCEngine`, `CRC_Memory`;
  W3D checksums materials and UV buffers with `CRC_Memory`), MD5, and the
  `PKey` public-key class over the `XMP_` multi-precision maths
  (\ref grp_w1_wwlib_pkey_mpmath).
- **Random numbers.** The `RandomClass` family
  (\ref grp_w1_wwlib_random_strutil). These generators are not the game
  logic's deterministic random values (\ref page_core_frameworks).
- **Threads and timing.** `ThreadClass` starts a thread with
  `_beginthreadex`; the mouse thread (`MouseThreadClass`) and the `Watchdog`
  are built on it. `MutexClass` and `CriticalSectionClass` lock;
  `SysTimeClass` is a millisecond clock over `timeGetTime`.
- **CPU detection.** `CPUDetectClass` identifies the processor, its caches
  and speed and the installed memory, using `CPUID` and `RDTSC`. A static
  initialiser in `cpudetect.cpp` runs it before `WinMain`.

The directory also holds code that is not Westwood's: the `stlport_*` files
are STLport template instantiations from across the binary, and some files
hold game-side classes that retail placed among WWLib's code. Their location
is a holding area, not ownership; `reverse/tu_map.csv` proposes original units
for many of them.

## Vendored and third-party code {#sub_wwlib_thirdparty_vendored}

Most of the third-party code is reproduced at an exact upstream release,
recorded in its rows' `vendored=<library>-<version>` note and, where one
exists, a provenance file: zlib, LZH-Light, Lua, STLport, ATL, GDI+, the
MSVC runtime, comsupp, dxerr9 and GameSpy. Those are documented upstream and
get no project API docs here. The EAC codecs and BYTEmark carry no vendored
tag; the EAC codecs follow Zero Hour's source (\ref grp_w1_eac_huffman
documents the Huffman codec). No D3DX library code is linked in: the game
imports D3DX from its DLL through the import library in `vendor/d3dx9/`,
whose provenance file explains the choice of SDK.

| Library | Release | What the game uses it for |
|---|---|---|
| EAC codecs | as in Zero Hour's source | RefPack, Huffman and binary-tree decoding |
| zlib | 1.1.4 | the zlib formats of `CompressionManager` |
| LZH-Light | 1.0 | the NOX format; EA changed the decompressor (see its `PROVENANCE.txt`) |
| Lua | 4.0.1, modified by EA | `LuaScriptEngine` (\ref sub_scripting) |
| STLport | 4.5.3 headers | every `std::` container; some float-formatting bodies are tagged as STLport 4.6 or 4.6.2 source |
| ATL, GDI+ | ATL 7.1, GDI+ 1.0 | `CImage`, which `WinMain` uses for the splash image |
| BYTEmark | nbench-byte 2.1 (Mayer's port; EA's `RunBenchmark` replaces `main`) | `RunBenchmark`, called by `W3DShaderManager::testMinimumRequirements` |
| MSVC 7.1 runtime | Visual C++ .NET 2003 | CRT startup and helper objects linked beside `msvcr71.dll` |
| comsupp | Visual C++ .NET 2003 | COM support (`_variant_t`, BSTR conversion, `_com_error` raising) |
| dxerr9, D3DX 9 | DirectX SDK, August 2005 | DirectX error strings; D3DX is imported from `d3dx9_27.dll` |
| GameSpy SDK | 2004 | online services (\ref sub_network) |

Two directories are not vendored source. The VP6 decoder is being rebuilt as
a clean room from written specifications; read
`reverse/vp6_cleanroom/README.md` first, because that lane forbids consulting
any VP6 decoder source. `Theora/` holds text taken from libtheora for helpers
the VP6 decoder inherited from VP3; libtheora itself is not linked.

## Entry points and how it connects {#sub_wwlib_thirdparty_connects}

These are libraries, so there is no single entry point. The notable ways in:

- **Static initialisation**, before `WinMain` (\ref page_startup): CPU
  detection, and a `SimpleFileFactoryClass` as WWLib's default read factory.
- **W3D model loading** (\ref sub_w3d_rendering). The asset prototypes,
  among them those that load HLODs, trees and animations, open each W3D file
  through a helper that is not yet named and that retail places among
  `W3DFileSystem`'s functions. It asks the engine's `TheFileSystem`
  (\ref sub_common_services) for an engine `File`. BFME 2's `ChunkLoadClass`
  is constructed on that stream and reads it directly, where Zero Hour's
  reads a WWLib `FileClass`.
- **WWLib's read factory** is a separate seam. `W3DFileSystem` installs
  itself as that factory when constructed and removes itself when destroyed.
  Its `W3DFileSystem::Get_File` hands out a `GameFileClass`, which opens
  read-only through `TheFileSystem`. In retail the factory's users are
  WWLib's own `Targa` image reader, `INIClass` loading, and
  `WW3D::Make_Screen_Shot`, which probes it for an unused file name.
- **Splash image**: `WinMain` loads it with `CImage`.
- **Hardware test**: `GameLODManager::init` and
  `GameLODManager::findStaticLODLevel` call
  `W3DShaderManager::testMinimumRequirements`, which reads `CPUDetectClass`
  and runs the benchmark.
- **Compressed data**: `CompressionManager::isDataCompressed`,
  `CompressionManager::getUncompressedSize` and
  `CompressionManager::decompressData`. Retail calls all three from one
  function that is not yet named, next to the DataChunk code. Zero Hour: the
  matching caller is `CachedFileInputStream::open`, which unpacks compressed
  chunk files such as maps.
- **Lua**, entered from `LuaScriptEngine` (\ref sub_scripting), which opens
  the base, I/O, string, maths and debug libraries.

## BFME 2 compared with Zero Hour {#sub_wwlib_thirdparty_zh}

- **Shared**: WWLib, WWSaveLoad, WWDownload, BYTEmark, STLport 4.5.3 (the
  version Zero Hour's tree names) and the compression library;
  `CompressionManager` keeps Zero Hour's formats, tags and test order.
- **New in BFME 2**: Lua (Zero Hour has none); the VP6 decoder, where Zero
  Hour plays video through Bink; ATL and GDI+ for the splash image.
- **Changed**: WWDownload's registry helpers root every path under the
  game's registry path, read at run time, instead of Zero Hour's fixed EA
  key. `W3DShaderManager::testMinimumRequirements` keeps Zero Hour's CPU
  thresholds and benchmark call; BFME 2 reports installed memory as a 64-bit
  value (`CPUDetectClass` queries `GlobalMemoryStatusEx`), where Zero Hour
  uses a 32-bit `Int`. `ChunkLoadClass` reads the engine's `File` stream
  instead of a WWLib `FileClass` (its constructor takes BFME's own stream
  interface and leaves the `FileClass` slot empty).
- **Open**: many Zero Hour WWLib files (its LZO, SHA and Blowfish code, for
  example) have no BFME 2 rows. Whether retail lacks them or they are not
  recovered yet is not known.

## Modding notes {#sub_wwlib_thirdparty_modding}

- **No game rules live here.** These libraries carry data in the formats
  below; they do not define units, costs or behaviour.
- **W3D files are chunk files** read by `ChunkLoadClass`, opened through the
  engine's file system (\ref sub_common_services). The model loaders pass
  two extra values from the asset prototype along with the open request;
  what they select is not yet established.
- **Lua is version 4.0, not 5.x,** with EA's changes: a boolean type with
  `true` and `false` keywords, EA's own `print` and `tostring`, and a fixed
  generic error result from some I/O functions. Open-BFME-1's Lua provenance
  file lists them; BFME 2's own Lua tree (`Code/Libraries/Source/Lua/`)
  carries the same changes.
- **Texture-mapper parameters are asset data.** A W3D vertex material stores
  its mapper arguments as INI-style text in the model file;
  `VertexMaterialClass::Load_W3D` reads them and
  `VertexMaterialClass::Parse_Mapping_Args` hands them to the mapper
  constructors through `INIClass`.
- **Splash image**: `WinMain` loads `<language>Splash.jpg`, falling back to
  `<language>Splash.bmp`, with the language taken from the registry. GDI+
  opens it by path, so it must be a loose file; BIG archives are not
  searched.
- **Compressed data** starts with an eight-byte header: a four-character tag
  (`EAR`, `NOX`, `ZL1` to `ZL9`, `EAB` or `EAH`, each with a trailing NUL)
  and then the uncompressed size. Data without a known tag is treated as
  uncompressed. The game never compresses through this path:
  `CompressionManager::compressData` has no caller in retail.

## Remastering notes {#sub_wwlib_thirdparty_remastering}

- **Win32 seams.** `RawFileClass` uses Win32 file calls, `RegistryClass` the
  registry (including the renderer's saved device, through `DX8Wrapper`),
  `ThreadClass` `_beginthreadex` and `SysTimeClass` `timeGetTime`. These
  classes are where a port substitutes other platform calls.
- **x86 assumptions.** `CPUDetectClass` uses inline x86 assembly, and the
  hardware test compares the detected CPU with vendor and model constants of
  the game's era. `GameLODManager::init` and
  `GameLODManager::findStaticLODLevel` use those results to choose the
  default detail level.
- **Memory size is 64-bit.** `CPUDetectClass` reads memory with
  `GlobalMemoryStatusEx` and keeps the totals as 64-bit values; Zero Hour
  used `GlobalMemoryStatus` and a 32-bit result.
- **The engine's `TheFileSystem` is the asset seam.** W3D model loading
  opens files through it directly, and WWLib's read factory (replaced by
  `W3DFileSystem`, serving `Targa` and `INIClass` loads through
  `GameFileClass`) also ends there, so a new read backend belongs in the
  engine file system. Writes such as `WW3D::Make_Screen_Shot` still use
  WWLib's writing factory and Win32 `RawFileClass` directly.
- **Runtime DLLs.** The game uses the DLL C runtime (`msvcr71.dll`), imports
  D3DX from `d3dx9_27.dll`, and the splash path needs GDI+ (`gdiplus.dll`).
- **Formats are fixed by the codecs.** A replacement compression library has
  to decode the same RefPack, Huffman, binary-tree, zlib and LZH-Light
  streams behind the header above; a replacement Lua has to reproduce EA's
  changes for any script that relies on them.

## State of the reconstruction {#sub_wwlib_thirdparty_state}

As of October 2026. The vendored libraries are essentially complete: nearly
every vendored row carries its upstream name, and the code is upstream's
apart from the changes the provenance files list. WWLib's core classes are
largely named, mostly recovered from Zero Hour's source. A large share of
the WWLib directory's bytes are STLport instantiations (the `stlport_*` and
similar STL sweep files), and address-named staging files remain beside the
Westwood classes; both will move or be renamed, so expect churn there. The
VP6 decoder is being recovered function by function in an active clean-room
lane; `reverse/vp6_cleanroom/queue.tsv` lists its functions, and the ledger
shows which still have placeholder rows. For current figures, filter
`reverse/functions.csv` by source path with `rg`.

## Reading list {#sub_wwlib_thirdparty_reading}

- Zero Hour: `Code/Libraries/Source/` under
  `reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/`.
- Provenance: `vendor/*/PROVENANCE*`,
  `Code/Libraries/Source/Compression/LZHCompress/PROVENANCE.txt`,
  `reference/shims/nbench/PROVENANCE.md`
  and Open-BFME-1's `game/Libraries/Source/Lua/PROVENANCE.txt`.
- `reverse/vp6_cleanroom/README.md` for the VP6 lane.
