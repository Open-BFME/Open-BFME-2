# Vector3 adoption trials that leave one row unmatched (2026-11-14, placeholders lane)

Matrix3D canon step 1 adopts the canonical Vector3 (`Code/Libraries/Source/WWVegas/WWMath/Vector3Data.h`, with
the step-1 inline members) in units that keep a private copy. In the seven units below, the adoption leaves one
row unmatched. Each .cpp.txt file here is the whole tried unit text: the private `class Vector3 { ... };` replaced by
`#include "Vector3Data.h"`, plus the edits noted per unit.

Every row is matched today under the unit's private Vector3. That is why these trials are kept here and not under
`reverse/attempts/`, which tools/check_csv.py refuses for matched addresses. Verdicts are in
`reverse/re_attempts.log` with status `attempted`, each naming its file here. The `partial` rows first recorded for
them pointed at a `reverse/attempts/` stash that does not exist, and are retracted with `void`.

| File | Row | Unit | Private copy | Note |
|---|---|---|---|---|
| 0x000e49b8.cpp.txt | 0x000E49B8 | Common/Rva000E48BC.cpp | no constructors | its comment already blames the canonical constructors |
| 0x0047a895.cpp.txt | 0x0047A895 | Contain/HordeContainRva0047A895.cpp | default and (x,y,z) constructors, no copy constructor | |
| 0x001e9a00.cpp.txt | 0x001E9A00 | Object/LocomotorRva001E9A00AerialMove.cpp | default and (x,y,z) constructors, no copy constructor | |
| 0x00086245.cpp.txt | 0x00086245 | W3DViewIterateDrawablesInRegion.cpp | no constructors | |
| 0x000ca9f1.cpp.txt | 0x000CA9F1 | Draw/W3DRopeDraw.cpp | (x,y,z) constructor only, no copy constructor | 11/12 rows match |
| 0x0009cd9b.cpp.txt | 0x0009CD9B | Rva0009CD9BSunRaysSetup.cpp | no constructors | set() calls respelled Set() |
| 0x00165820.cpp.txt | 0x00165820 | WW3D2/HTreeClassFirstCapturedBone.cpp | declares a copy constructor | 7/8 rows match; own operator+ and k*a dropped |

## One canonical-wide hypothesis (the first six)

The canonical Vector3 declares a copy constructor. The private copies of the first six declare none, so they use
the implicit, trivial copy, and the declared copy constructor shifts their codegen. Testing it means changing the
canonical constructors, which reaches all 266 units that include Vector3Data.h. That is out of step 1's scope (the
coordinator ruled the canonical constructors unchanged there).

## HTreeClass (separate)

Its private copy declares a copy constructor (assignment-style body), its Lerp is `__declspec(dllimport)
__forceinline`, and its operator+ is plain `inline`. Making the canonical operator+ plain `inline` did not change
the result. The remaining suspects are the copy-constructor style and the dllimport Lerp.

## Rva0007E6F6Rva0007E6F6.cpp's operator copies (0x000659e3.cpp.txt, 0x000663b8.cpp.txt): not landed

A trial defined Vector3's free operators in Vector3Data.h as plain `__forceinline` (Zero Hour's WWINLINE; retail
imports none of them, so not `dllimport`). This unit then had to drop its own `__declspec(dllimport) __forceinline`
definitions. Its row still matched (1/1), but it emitted unreferenced out-of-line copies of a-b (`??G`) and a+b
(`??H`): 56 bytes each, while retail's rows (0x000659E3, 0x000663B8, owned by colmathaabox.cpp) are 55. Both files
are that trial's unit text.

These copies are select-any COMDATs, and select-any lets the linker keep any definition, so nothing proved the image
would keep retail's bytes. The operators therefore moved to Vector3Operators.h, which only the units that use them
include, and this unit keeps its own definitions unchanged. The verdicts are `attempted` rows in
reverse/re_attempts.log.
