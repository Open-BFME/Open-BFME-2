// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Deque_base<BfmePod8> ctor retail 0x0054A1B7 75B. Same shape as the Pod16
// base at 0x0041A157 and Pod28 base at 0x0041A10C; calls rowed
// _M_initialize_map for BfmePod8 at 0x00549E3F and ICF alloc_proxy bodies
// at 0x0014F3C4; unlocks 0x0054B7B7.
//
// ??0?$_Deque_base@UBfmePod8@@V?$allocator@UBfmePod8@@@_STL@@@_STL@@QAE@ABV?$allocator@UBfmePod8@@@1@I@Z @0x0054A1B7 (75B):
// Deque_base ctor over 8-byte POD with dual AllocProxy plus initialize_map.
// Caller 0x0054B7E8.
// Evidence: unlock lane, all callees rowed, unblocks 0x0054B7B7.
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
struct BfmePod8 { int a[2]; };
template _STL::_Deque_base<BfmePod8, _STL::allocator<BfmePod8> >::_Deque_base(const _STL::allocator<BfmePod8> &, size_t);
template _STL::queue<BfmePod8, _STL::deque<BfmePod8, _STL::allocator<BfmePod8> > >::queue();
