// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Dedicated no-EH instantiation of vector<BfmeE8>::_M_allocate_and_copy.
// stlport_vector_e8_o1.cpp uses /EHsc and emits an EH frame; retail is the
// 45-byte ebp+tag body twin of vector<AsciiString>::_M_allocate_and_copy.

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
struct BfmeE8 { int a, b; };
template class _STL::vector<BfmeE8, _STL::allocator<BfmeE8 > >;
