// cl: -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// stlport
// ?resize@?$vector@V?$vector@URva0019D850Value@@V?$allocator@URva0019D850Value@@@_STL@@@_STL@@V?$allocator@V?$vector@URva0019D850Value@@V?$allocator@URva0019D850Value@@@_STL@@@_STL@@@2@@_STL@@QAEXI@Z
// retail 0x0032FF48, 73 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Rva0019D850NestedVectorRelease.cpp: the donor
// preamble and this one vector<vector<Rva0019D850Value> > member, the donor's
// other definitions omitted. Rva0019D850Value is an opaque twelve-byte payload
// stand-in; the outer resize body only constructs, resizes and destroys a
// temporary element, so no element identity reaches the bytes.
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

struct Rva0019D850Value
{
	int m_words[3];
};

template void _STL::vector<_STL::vector<Rva0019D850Value> >::resize(unsigned int);
