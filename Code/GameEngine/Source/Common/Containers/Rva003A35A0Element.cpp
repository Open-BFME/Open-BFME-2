// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii
// Reference lead: Open-BFME-1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/Containers/Rva003A3A90.cpp. Its whole /O1
// unit places the 214B STLport insert at target312E04, whose native calls
// identify this 184B element's copy311FE2,assignment311537,dtor89851.
// Native120B copy and118B assignment independently prove the following
// subobjects: a dword at00, ten float scalars at04, ten12B objects at2C,
// a12B subobject atA4, a string atB0, and a dword atB4. The 2C array's
// constructor iterator names the already-rowed Coord3D copy4216D3 and
// empty destructorB3FD0. B0 calls canonicalStringBase<char> copy365F0
// and assignment366F0 through the canonicalAsciiString header below.
// Original element/owner names and the A4 scalar types remain unknown;
// unsigned words model the target's integer copies, not a semantic claim.
// The donor-qualified element spelling preserves existing caller symbols.
#include "ascii_string.h"
#include <new>
struct Coord3DBase {float x,y,z;};
class Coord3D:public Coord3DBase {
public:
    Coord3D();
    Coord3D(const Coord3D&);
    ~Coord3D();
};
struct Rva00311FE2Words {
    unsigned int word00,word04,word08;
    Rva00311FE2Words();
    // ?Rva00311FE2Words::Rva00311FE2Words present-unmatched
    Rva00311FE2Words(const Rva00311FE2Words& s):word00(s.word00),word04(s.word04),word08(s.word08){}
};
struct Rva003A35A0Element {
    Rva003A35A0Element();
    ~Rva003A35A0Element();
    unsigned int word00;
    float values[10];
    Coord3D points[10];
    Rva00311FE2Words point;
    AsciiString text;
    unsigned int wordB4;
};
// Emit the compiler-generated memberwise copy; this anchor has no retail row.
// ?emitRva00311FE2Copy present-unmatched
void emitRva00311FE2Copy(Rva003A35A0Element* p,const Rva003A35A0Element* s)
{
    new(p) Rva003A35A0Element(*s);
}
// Assignment remains present-unmatched until the second per-body commit.
// ??4Rva003A35A0Element@@QAEAAU0@ABU0@@Z present-unmatched
Rva003A35A0Element& (Rva003A35A0Element::*emitRva00311537Assign)(const Rva003A35A0Element&)=&Rva003A35A0Element::operator=;