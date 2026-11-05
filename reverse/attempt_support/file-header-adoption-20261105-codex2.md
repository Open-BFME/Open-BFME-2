# Canonical File adoption, 2026-11-05

Base: `a2d8264b22`. Header: `Code/GameEngine/Include/Common/File.h`.

Retired nine File header-queue rows through one cohort-wide
`header_adopt_lane.py accept --class File` invocation over all thirteen queued
sources. Accepted sources:

- `Code/GameEngine/Source/Common/Rva00605C91Ctor.cpp`
- `Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript_parseLayoutBlock.cpp`
- `Code/GameEngine/Source/GameClient/GameText.cpp`
- `Code/GameEngine/Source/GameClient/GlobalLanguage.cpp`
- `Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp`
- `Code/Libraries/Source/WWVegas/WW3D2/GenRva001808B0.cpp`
- `Code/Libraries/Source/WWVegas/WW3D2/Gen_dtor_00970f60.cpp`
- `Code/Libraries/Source/WWVegas/WW3D2/HTreePrototypeLoad.cpp`
- `Code/Libraries/Source/WWVegas/WW3D2/Rva0014D078LoadAnim.cpp`

The constructor drops padding now supplied by the 0x14-byte File base. The
layout parser passes scanString's reference argument; GameText uses the
header's deleteOnClose accessor. The four WW3D factories cast the stream at
the existing BFMEChunkInput constructor boundary and close through File's
slot 2. Their unused private BFMEChunkInput declarations are removed.

Verification:

- Normal scoped build: 551/551 functions and nine data rows byte-match;
  string, float and import reference checks pass. Final source forms also
  pass the adoption tool's byte gates and declared-unmatched check.
- Before/after COFF audit with `class_cleanup.snapshot` and `same_runtime`:
  no external definition removed and no weak binding changed in any source.
  Eight complete runtime graphs are identical, including bytes, relocation
  bindings and COMDAT policies. GameText adds only the external definition
  `?deleteOnClose@File@@QAEXXZ`; all original definitions remain.
- Current-object link preview: nine of nine sources LINKS, preserving
  50,611/50,611 census-linked bytes against the 2026-11-05 15:19 index at
  `f44cbcf5b0`. Miles reports seven unreferenced allocator relocation
  diagnostics, which the preview explicitly classifies as nonblocking.
  This is a preview, not a new census or real-link measurement.
- Existing alternatename directives are retained. No shared header, ledger
  identity, pin, source path or data definition changes.

Four original queue entries remain unchanged: System/File.cpp,
FileSystemOpenFile.cpp and TextFile.cpp need their embedded string ownership
reconciled with the canonical opaque name storage; Win32LocalFileSystem.cpp
also needs its scalar-deleting-destructor call protocol reconciled with the
canonical virtual destructor. No passing retirement is claimed for them.
