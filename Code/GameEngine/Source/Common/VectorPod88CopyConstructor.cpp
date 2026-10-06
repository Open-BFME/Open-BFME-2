// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// vector<vector<BfmePod88>> copy constructor, retail 0x00500E7C, 96 bytes.
// Spelled after GeometryShapeVectorCopyConstructor.cpp: explicit
// instantiation so the headers emit the canonical copy ctor, which sizes
// via idiv 0xC, builds the base through the rowed _Vector_base, then copies
// with the rowed __uninitialized_copy at 0x00500B5B. Callers at 0x0050119F
// and 0x00501261.
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

struct BfmePod88
{
	char m_body[88];
};

template class _STL::vector<_STL::vector<BfmePod88, _STL::allocator<BfmePod88> >, _STL::allocator<_STL::vector<BfmePod88, _STL::allocator<BfmePod88> > > >;
