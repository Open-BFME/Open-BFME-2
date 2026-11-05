# RvaSmartPtr12: six canonical consumers (2026-11-05)

Base: `2374560648`. Related obstacle: LINK-155.

Six existing units include `Include/Common/RvaSmartPtr12.h` instead of a
private class declaration. Five retain their existing guarded unlink as a
TU-local inline destructor definition; the shader binders retain force-inlining.
The canonical header is unchanged. The enable-path getter reads canonical
`field00` at the same offset. No symbol, pin, alias, source path or ledger row
moves. This is header-debt cleanup, with no new unique coverage.

| Source | External definitions before/after |
| --- | --- |
| `Code/GameEngine/Source/Common/Rva00098690Destructor.cpp` | 4/4 |
| `Code/GameEngine/Source/Common/Rva003FDC46.cpp` | 2/2 |
| `Code/GameEngine/Source/Common/Rva001F69B1ParticleDrawBinder.cpp` | 36/36 |
| `Code/GameEngine/Source/Common/Rva001F73D5ParticlePhysicsUpdateBinder.cpp` | 35/35 |
| `Code/GameEngine/Source/GameClient/System/FXParticleSystem/GPUParticleStorageConstructor.cpp` | 82/82 |
| `Code/GameEngine/Source/GameClient/System/FXParticleSystem/Rva003A5A58WindUpdate.cpp` | 11/11 |

Verification:

- `./build.sh` over these six units: 75/75 matched rows, including EH rows;
  21 string literals plus two empty-string references, 10 float literals and
  three imports verified. Declared-unmatched scan passes.
- One `header_adopt_lane.py accept --class RvaSmartPtr12` over all six units
  passes each unit and retires six rows through the owning tool.
- Ordinary combined `link_check.py` preview: all six LINKS, preserving
  7,252/7,252 census-linked bytes against index `f44cbcf5b0`
  (2026-11-05 15:19). This predicts the stated scope; it is not a real link
  or game-run result.
- Rebuilt all six original sources through `./build.sh` (75/75), compared
  their COFF external-definition sets with the adopted objects through
  `exit_link.external_definitions`, then restored and byte-verified the adopted
  sources again (75/75). Each source preserves its complete definition set:
  170 definitions total, none removed or added. No link-wide alias is removed.
  This specifically avoids dropping a private view's sole inline provider.

A seventh trial, `Common/System/SmartPtrRvoGetter.cpp`, was restored: its
165-byte stop path needs the original if-null operator-arrow branch ordering;
using the canonical ternary changes that branch despite equal body length.
Its queue row remains, and the failed hypothesis is recorded with `re_log.py`.
The other 25 RvaSmartPtr12 queue rows remain. Next work is scoped adoption of
those consumers, preserving inline lifetimes and addressing default construction
or operator-arrow shape where required. No shared-header change was trialed.
