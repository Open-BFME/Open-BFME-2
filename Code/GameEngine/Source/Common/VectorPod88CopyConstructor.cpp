// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// vector<vector<BfmePod88>> copy constructor, retail 0x00500E7C, 96 bytes.
// Spelled after GeometryShapeVectorCopyConstructor.cpp: explicit
// instantiation so the headers emit the canonical copy ctor, which sizes
// via idiv 0xC, builds the base through the rowed _Vector_base, then copies
// with the rowed __uninitialized_copy at 0x00500B5B. Callers at 0x0050119F
// and 0x00501261.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct BfmePod88
{
	char m_body[88];
};

template class _STL::vector<_STL::vector<BfmePod88, _STL::allocator<BfmePod88> >, _STL::allocator<_STL::vector<BfmePod88, _STL::allocator<BfmePod88> > > >;
