# Rva0052413E consumer header adoption, 2026-11-05

Inspected source revision: `e633f06883be`. Claim owner:
`yasinschroeder-codex3`. The published link index is `c95fcfcfcd`, measured
2026-11-05 05:17. These are scoped previews, not a new census or real-link run.

## Accepted scope

Replaced the private `Rva0052413E` definitions with the existing canonical
`Code/GameEngine/Include/Common/Rva0052413E.h` in:

- `Code/GameEngine/Source/Common/Rva0052634FPermuted.cpp`
- `Code/GameEngine/Source/Common/Rva0052A470Dtor.cpp`
- `Code/GameEngine/Source/Common/Rva005FCFEADtor.cpp`
- `Code/GameEngine/Source/GameClient/GUI/InGame/InGameNotificationBoxMovieClip.cpp`
- `Code/Libraries/Source/WWVegas/WWLib/Rva0050ED58Dtor.cpp`

The target facts documented by the existing header establish a nonvirtual,
12-byte, four-byte-aligned member with out-of-line lifetime methods. None of
these consumers accesses the replaced class's private fields. The automatic
adopter refused ambiguous field-token renames or the vector-to-opaque-storage
mapping; replacing the complete unused private declarations requires no field
rename. The canonical header itself was unchanged. Original class/member names
remain unproven; no new naming or donor-source claim is made.

`header_adopt_lane.py accept --class Rva0052413E` passed all five sources and
retired exactly their five rows from `reverse/header_queue.tsv` through its
normal verdict path. The final `./build.sh` of those five sources plus the
restored `Rva005D25F2Dtor.cpp` passed **89/89 rows**, including the changed
consumers' 64 rows, one data row, literal/import checks and parent-bound funclet
verification. `find_declared_unmatched.py` passed. `link_check.py` reported all
five consumers LINKS, preserving the index's **2,246 -> 2,246 linked bytes**
(215, 466, 74, 1,390 and 101 respectively). No source paths, pins, hatches,
shared headers, data names or function rows changed.

## Remaining queue entries

`Code/GameEngine/Source/Common/Rva005D25F2Dtor.cpp`: the same replacement changes
the 717-byte `StrategicHUD::CommandUIImpl` constructor at `0x005D2BD4`.
Its private class declared a potentially throwing constructor; the canonical
header declares `Rva0052413E() throw()`. The trial removes the native
`mov byte ptr [ebp-4],1` before the member construction at +0x0C and changes
subsequent EH/funclet emission. Restored the original source and verified all
25 rows again. Investigate the native caller's exception-state contract before
changing this shared declaration; neither a header change nor a nonmatching
source is retained.

`Code/Libraries/Source/WWVegas/WWLib/Rva0052413EDtor.cpp`: the owner defines
`~Rva0052413E` with an actual `vector<AsciiString>` member. Its implicit member
destruction after the clear call is part of the rowed 47-byte body and EH graph.
The canonical opaque char array does not express that destruction. The adopter
refused the typed-to-opaque field mapping; the owner source remains unchanged.
A later owner/header reconciliation must preserve this vector lifetime and the
consumer constructor exception contract together. Both queue rows remain.

Local logs: `build/rva0052413e-adopt-codex3.log`,
`build/rva0052413e-build-codex3.log`, `build/rva0052413e-accept-codex3.log`,
`build/rva0052413e-final-build-codex3.log`, `build/rva0052413e-link-codex3.log`.
