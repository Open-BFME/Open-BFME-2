# GpuDrawModuleInfo post-load export provider

Inspected revision: `bcd3f6cf12`. Scope: LINK-583's missing
`?LoadPostProcess@GpuDrawModuleInfo@FXParticleSystem@@UAEXXZ` export only.

Target evidence: export ordinal 1309 names the callback at RVA `0x000B3FD0`.
The canonical `GpuDrawModuleInfo.h` records the native four-slot table at
VA `0x00C1C1E8`, with this callback in slot 1. No donor source is needed.

Added the empty out-of-line C++ member beside the other post-load callbacks in
`Code/GameEngine/Source/GameClient/FXParticleSystem.cpp`. Registered the complete
one-byte fold with `add_match.py --icf-owner '??1Coord2D@@QAE@XZ'`, retaining
the existing coordinate owner and recording its source as `fold-proof`.
Read-only COFF inspection of the normally built object confirms the exact named
definition has full section bytes `c3` and no relocations, equal to retail's
one byte at `0x000B3FD0`. No definitions, aliases or pins were removed.

Verification:

- `./build.sh Code/GameEngine/Source/GameClient/FXParticleSystem.cpp`: passes
  all 384 code checks, one data row, 17 string references and 10 float references.
- `find_declared_unmatched.py` after the edit: all defined functions matched.
- `check_csv.py`: passes, 99,484 function rows.
- `link_check.py Code/GameEngine/Source/GameClient/FXParticleSystem.cpp`:
  LINKS, 5,650 / 5,650 own bytes, against the published 2026-11-05 15:19
  index at `f44cbcf5b0`. This is a prediction, not a new image or census.

Result: one missing exported name now has a verified provider; zero additional
unique matched bytes. The three default constructor exports in LINK-583 remain
outside this repair. A new real link must confirm removal of this export error.
