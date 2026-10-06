// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Deque_base<BfmePod16> ctor retail 0x0041A157 75B. Same shape as the Pod28
// base at 0x0041A10C; calls rowed _M_initialize_map for BfmePod16 at
// 0x00419ED4 and ICF alloc_proxy bodies at 0x0014F3C4; unlocks 0x0041A6E5.
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

#include <deque>
#include <queue>
struct BfmePod16 { int a[4]; };
template _STL::_Deque_base<BfmePod16, _STL::allocator<BfmePod16> >::_Deque_base(const _STL::allocator<BfmePod16> &, size_t);
template _STL::queue<BfmePod16, _STL::deque<BfmePod16, _STL::allocator<BfmePod16> > >::queue();
