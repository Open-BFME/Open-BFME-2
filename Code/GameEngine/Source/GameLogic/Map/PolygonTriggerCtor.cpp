// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// PolygonTrigger::PolygonTrigger(int identifier, int count), retail
// 0x002E3FAB..0x002E4049 (158 B, ret 12 with the hidden most-derived flag).
// WorldBuilder AB9C60 is the constructor and the chunk parser's new(0x64)
// supplies the two int arguments. Layout measured from the constructor and
// its thunks (2E3E80..2E3EB0): primary Rva00330C50 (vptr +0, vbptr +4,
// container +8, flag +34, vtordisp +38) with the virtual interface at +0x3C,
// a secondary polymorphic base at +0x38 whose vptr is stored after the base
// call, and a plain {next} base at +0x3C stored BEFORE it. Declaring the
// next-link base FIRST in the base list is what orders its store ahead of
// the Rva00330C50 call (construction order is declaration order, layout
// puts the data-only base after the polymorphic ones). The rowed
// Rva00330C50 constructor (0x00330C50) and the 0x002E36B7 initialiser are
// declared only; their bodies live in Common/Rva00330C50Ctor.cpp and
// PolygonTrigger.cpp. The names are address-derived; the base roles are
// inferred from bytes.
struct Region2D;
struct Rva0030B72CPoint;
#include "../../../Include/GameLogic/PolygonTrigger.h"



#include "ascii_string.h"
class PolygonTrigger;
PolygonTrigger::PolygonTrigger(int identifier,int count):id(identifier)
{ rva002E36B7(count); }
