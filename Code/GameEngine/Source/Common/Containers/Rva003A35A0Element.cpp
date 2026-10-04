// cl: /O1 /arch:SSE2 /MD /EHsc /Ireference/shims/bfme2_ascii /DWIN32 /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc/stl
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
// stlport
// Include only the existing BFME allocator override. Its directory root
// also contains force-inline algorithm overrides, which change insert214.
#define _STLP_NO_EXCEPTIONS 1
#include <cstddef>
#include "_alloc.h"
#include <vector>
// The existing retail max<unsigned int> body uses speed scheduling. Keep its
// 17-byte COMDAT identical while the native insert family retains /O1.
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int& max<unsigned int>(const unsigned int& a, const unsigned int& b) { return a < b ? b : a; }
}
#pragma optimize("", on)
#include "ascii_string.h"
#include <new>
struct Coord3DBase {float x,y,z;};
class Coord3D:public Coord3DBase {
public:
    Coord3D();
    Coord3D(const Coord3D&);
    ~Coord3D();
    // Native constructor3118DF's loop inlines these three zero stores.
    // This address-qualified helper adds no application method identity.
    // ?Coord3D::rva003118DFZero absent-from-retail
    __forceinline void rva003118DFZero() { x=0.0f;y=0.0f;z=0.0f; }
};
struct Rva00311FE2Words {
    // Native copy uses raw dwords; native default initialization uses SSE
    // zero stores. These two views describe storage and codegen only.
    union {
        struct {unsigned int word00,word04,word08;};
        struct {float zero00,zero04,zero08;};
    };
    // ?Rva00311FE2Words::rva003118DFZero absent-from-retail
    void rva003118DFZero() {zero00=0.0f;zero04=0.0f;zero08=0.0f;}
    // ?Rva00311FE2Words::Rva00311FE2Words absent-from-retail
    Rva00311FE2Words() {}
    // ?Rva00311FE2Words::Rva00311FE2Words present-unmatched
    Rva00311FE2Words(const Rva00311FE2Words& s) {word00=s.word00;word04=s.word04;word08=s.word08;}
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
// Emit the independently verified compiler-generated memberwise assignment.
Rva003A35A0Element& (Rva003A35A0Element::*emitRva00311537Assign)(const Rva003A35A0Element&)=&Rva003A35A0Element::operator=;
// Native STLport4.5.3 insert214 and its overflow191 use this same184B
// element. Actual full native call maps tie copy/assignment above to their
// Construct45,uninitialized-copy47,fill40 and backward-copy helpers.
template Rva003A35A0Element* _STL::vector<Rva003A35A0Element>::insert(Rva003A35A0Element*,const Rva003A35A0Element&);

// Native insert312EA4/destroy8AFFD both call89851. The existing ledgered
// 67B destructor destroys AsciiString+B0 and10Coord3D objects+2C, agreeing
// independently with the120B native copy above. Bind that same destructor
// ABI; its donor-carried RunwayInfo spelling does not name this target owner.
#pragma comment(linker, "/alternatename:??1Rva003A35A0Element@@QAE@XZ=??1RunwayInfo@FlightDeckBehavior@@QAE@XZ")


// Native Ghidra3118DF/149B establishes array construction and all zero
// bit patterns below. Array element ctor47A6A9/dtorB3FD0 are tied to the
// existing Coord3D identities by the separately verified copy4216D3.
// __ehvec_ctor629512 and StringBase<char>::releaseBuffer36410 are rowed.
// The float view of+00 and mixed views of+A4 are compiler-shape inferences;
// this does not assign original application types or an owner name.
Rva003A35A0Element::Rva003A35A0Element()
{
    point.rva003118DFZero();
    wordB4=0;
    text.clear();
    *(float*)&word00=0.0f;
    for(int i=0;i<10;++i) {
        values[i]=0.0f;
        points[i].rva003118DFZero();
    }
}
