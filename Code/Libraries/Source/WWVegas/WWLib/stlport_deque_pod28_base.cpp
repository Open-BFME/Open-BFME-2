// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Deque_base<BfmePod28> ctor retail 0x0041A10C 75B. Same shape as the 75B
// Pod492/Pod840/BuddyRequest and BfmeE12 Deque_base ctors; calls rowed
// _M_initialize_map for BfmePod28 at 0x00419E3D and ICF alloc_proxy bodies
// at 0x0014F3C4; unlocks 0x0041A6D0.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
#include <queue>
struct BfmePod28 { int a[7]; };
template _STL::_Deque_base<BfmePod28, _STL::allocator<BfmePod28> >::_Deque_base(const _STL::allocator<BfmePod28> &, size_t);
template _STL::queue<BfmePod28, _STL::deque<BfmePod28, _STL::allocator<BfmePod28> > >::queue();
