// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _Deque_base map setup for deque<BfmePod20>: _M_initialize_map 152B at
// 0x0054FAD4. Same placeholder-element convention as the sibling
// stlport_deque_e12_o1.cpp (BfmePod20 names only the 20-byte element SIZE:
// 128/20 = 6 per node, node stride 0x78, imul 0x14). Split into its own TU
// without /EHsc: retail carries no exception-handling frame (the
// _STLP_TRY/_STLP_UNWIND rollback compiles to nothing once
// _STLP_USE_EXCEPTIONS is off), matching stlport_deque_e12_new_elements.cpp
// which hosts the 152B BfmeE12 initmap at 0x00584D55. Calls rowed
// allocate 0x00068E15 and _M_create_nodes 0x00421918 (both size-independent
// 120B node bodies shared with the E12 family).
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
struct BfmePod20 { int a[5]; };
template class _STL::deque<BfmePod20, _STL::allocator<BfmePod20> >;
