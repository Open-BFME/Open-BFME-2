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

First stated as: the canonical Vector3 declares a copy constructor, and these private copies do not. Tested on
2026-11-15 and refuted for the four units the trials could judge:
- with no user copy constructor (V1), and with Zero Hour's assignment-body copy and value constructors (V2),
  Rva000E48BC, HordeContain, IterateDrawables and W3DRopeDraw give the same result as with the canonical header. The
  trials were uninformative for the other two: Locomotor produced no result line, and SunRaysSetup stopped at its data
  row, because its set() calls were not respelled in these trials;
- in the one difference examined (0x000E49B8), no copy happens at the site that differs.

Restated, and still only a hypothesis (untested for Locomotor and SunRaysSetup): the canonical Vector3 is not a plain aggregate (it has user-declared
constructors), and that changes the operand order the compiler chooses in inlined transforms. The private copies
match retail. Evidence at 0x000E49B8: 24 bytes differ, all in the Y row of the inlined Matrix3D transform. Retail
multiplies row[1].Z*v.Z before row[1].X*v.X, and with the canonical class the compiler takes X first. Rva000E48BC's
own comment blames the default constructor.

It cannot be tested cheaply: an aggregate Vector3Data.h does not compile, because its own members and most of its
dependents construct Vector3(x,y,z). These six stay banked until there is retail evidence for which Vector3 these units
used.

## HTreeClass (separate)

Its private copy declares a copy constructor (assignment body), a `__declspec(dllimport) __forceinline` Lerp, a
dllimport k*a and a plain `inline` operator+. Adopted, Combo_Update compiles to 2250 bytes against retail's 2277. The
instruction streams diverge about 345 of 566 instructions in, in the quaternion product: the same operations,
scheduled in a different order with other registers.

Header variants tried (2026-11-15), none of which matches:
- no copy constructor (2 of 8 rows fail);
- assignment-body copy and value constructors;
- the copy constructor alone in that form;
- the copy constructor alone in that form, plus `X = X*k` in *=;
- (diagnostic only) the private dllimport and inline forms.
The last four leave the same 1 of 8 rows failing. The most likely cause is the compiler's scheduling sensitivity to
the extra content the canonical header brings into the unit, as seen with W5's PlaceEventTranslator. It stays banked.

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
