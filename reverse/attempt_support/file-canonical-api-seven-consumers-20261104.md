# Canonical File API adoption, seven consumers (2026-11-04)

Inspected source revision: `89310c1788f5a95031cebb4ea812c4abfd50746e`. Existing canonical header:
`Code/GameEngine/Include/Common/File.h` (unchanged).

## Scope and evidence

- `Code/GameEngine/Source/Common/BfmeB996Range.cpp`
- `Code/GameEngine/Source/Common/Rva000AF917Finish.cpp`
- `Code/GameEngine/Source/Common/Rva0041AD08Read.cpp`
- `Code/GameEngine/Source/Common/System/XferSaveAsText.cpp`
- `Code/GameEngine/Source/Common/calcCRC.cpp`
- `Code/GameEngine/Source/GameClient/MapPreviewImage.cpp`
- `Code/Libraries/Source/WWVegas/WW3D2/TextureAssetImplPreLoad.cpp`

The private views already selected the canonical virtual slots: close at +0x08,
read at +0x0C, seek at +0x14, and size at +0x2C. The existing header documents
those slots from retail File's table and rowed providers. Replace the private
views with its relative include, use File::START/CURRENT/END with their existing
0/1/2 values, and call the established read/close/size methods. These are API
reconciliations, with no new name, pin, alias, layout or shared-header change.

TextureAsset::Impl::PreLoad previously stored 1 at File+0x0D. The header's
inline deleteOnClose performs that same store; use it for both file pointers.
The header cites the independent native LanguageFilter store as target evidence.

## Verification

- `./build.sh` with the seven paths: 87/87 matched rows; 59 string literals,
  15 empty-string references, 2 compiler float literals and 6 named imports
  verified. Existing renumbered funclet labels resolve through their parent EH
  graphs; no ledger change required.
- `find_declared_unmatched.py` before and after each source edit: passing.
- `eh_verify.py` with the seven paths: 11 EH graphs EXACT, zero non-exact,
  zero baselined and zero missing objects.
- `header_adopt_lane.py accept --class File` with the seven paths: all pass;
  the owning tool removed exactly their seven File rows from header_queue.tsv.
- Combined `link_check.py` preview against the 2026-11-04 07:28 index at
  `a62ac1c10b`: all seven LINKS, preserving 10,906 -> 10,906 authored bytes.
  Per-unit byte counts in the source order above: 1468, 378, 2814, 4566, 286,
  1182, 212. No census, image-ownership or runtime gain is claimed.
- `git diff --check`: passing.

Acceptance output:

```text
  PASS Code/GameEngine/Source/Common/BfmeB996Range.cpp
  PASS Code/GameEngine/Source/Common/Rva000AF917Finish.cpp
  PASS Code/GameEngine/Source/Common/Rva0041AD08Read.cpp
  PASS Code/GameEngine/Source/Common/System/XferSaveAsText.cpp
  PASS Code/GameEngine/Source/Common/calcCRC.cpp
  PASS Code/GameEngine/Source/GameClient/MapPreviewImage.cpp
  PASS Code/Libraries/Source/WWVegas/WW3D2/TextureAssetImplPreLoad.cpp
  retired 7 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

## Remaining scope

The other File queue entries remain owned by their existing acceptance path.
This repair does not address their construction/lifetime, concrete subclass,
string storage or stream adapter differences. The XferSaveAsText row retired
here is for File only; its separate Xfer work in LINK-004 remains unchanged.

## Initial picker lead

The initial exit-link lead LivingWorldAIOrders.cpp already has its needed
40-byte g_Va00E04508 provider in Rva007B6880Thunks.cpp. Its five rows pass the
normal byte gate. A paired current-object preview makes LivingWorldAIOrders
LINKS (967 -> 967), while the provider unit still reports the separate
?g_Va00DF2984@@3PAIA dependency. No edit or register retirement was made for
that stale consumer lead; the corresponding body and file claims were released.
