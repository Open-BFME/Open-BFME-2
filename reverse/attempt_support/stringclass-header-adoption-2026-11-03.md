# StringClass header adoption, 2026-11-03

Inspected source revision: `f2dff5220a`. Claim owner:
`yasinschroeder-codexb`. Published census index: 2026-11-03 20:03,
`8661f15284` (confirmed by `link_check.py --fetch-index`).

## Cause and repair

These seven units carried private StringClass bodies. Replacing those bodies
with only the declaration header loses the inline destructor that directly
calls the rowed Free_String provider. Each unit now includes
`Code/Libraries/Source/WWVegas/WWLib/StringClassData.h` and defines the same
inline destructor out of class, preserving its existing inline/forceinline
choice. The shared header itself is unchanged.

Rva00109C7FDtor also retains its inline character-pointer conversion.
AggregatePrototypeRegistration replaces its private `str()` accessor with the
header's declared character-pointer conversion, defined inline in that TU.
This avoids the queue's ambiguous token rename of `buffer`, which is also a
ChunkLoadClass field. No original derived-class identity is asserted.

## Verification

`./build.sh` verified the six destructor units together (28/28 code rows),
and AggregatePrototypeRegistration separately (5/5). String, float and import
reference checks passed. Renumbered compiler labels were resolved through
the verified parent EH graphs, including all ten affected funclet rows.
`find_declared_unmatched.py` passed before and after each edit; the existing
absent-from-retail anchor in Rva00180A46Dtor remains as before.

`header_adopt_lane.py accept --class StringClass --header
Code/Libraries/Source/WWVegas/WWLib/StringClassData.h` passed for every listed
unit and retired precisely seven queue rows. No queue row was removed by hand.

Combined `link_check.py` preview, paths under `Code/GameEngine/Source/Common/`:

| Unit | Census-linked bytes | Preview-linked bytes |
| --- | ---: | ---: |
| AggregatePrototypeRegistration.cpp | 365 | 365 |
| Rva000F1B8FDtor.cpp | 92 | 92 |
| Rva00109C7FDtor.cpp | 86 | 86 |
| Rva0017FB94Dtor.cpp | 145 | 145 |
| Rva0017FFCABase.cpp | 145 | 145 |
| Rva00180527Dtor.cpp | 118 | 118 |
| Rva00180A46Dtor.cpp | 118 | 118 |
| Total | 1,069 | 1,069 |

All seven preview verdicts are LINKS. This is preservation evidence against
the named census, not a new census or a real game-link measurement. Other
StringClass queue entries remain outside this verified scope.
