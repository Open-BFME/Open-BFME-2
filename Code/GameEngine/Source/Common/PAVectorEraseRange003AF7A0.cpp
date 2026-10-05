// cl: /O1 -GX- /Ireference/shims/bfmealloc
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/PAVectorEraseRange003AF7A0.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// vector<Elem003AF7A0>::push_back 0x005DC54E (56B). Callee addresses are read
// off retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
//
// Open-BFME5: STLport vector::erase(first,last) at retail 0x003AF7A0 (77B).
// Same shape as PAVectorEraseRange.cpp (0x00147180): virtual element dtor
// called as scalar-deleting with 0, then add esi, element-size. Stride here
// is 8. Not ICF with the 0x5C-element PA twin (different imm in the loop).

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct Elem003AF7A0
{
	virtual ~Elem003AF7A0();

	char m_body[ 8 - 4 ];

	Elem003AF7A0();
	Elem003AF7A0( const Elem003AF7A0 & );
	Elem003AF7A0 &operator=( const Elem003AF7A0 & );
};

// Only the placed member is instantiated (the donor's whole-class
// instantiation emitted every other member as a private copy).
template void _STL::vector<Elem003AF7A0>::push_back( const Elem003AF7A0 & );
