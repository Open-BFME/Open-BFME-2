// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /G7
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 12-byte BfmeE12
// element. The allocator at 0x395928 and the trivial-copy worker at 0x766F5
// are both rowed under the BfmeE12 spelling; this shard reuses it.
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

#include <vector>
struct BfmeE12 { int a[3]; };
template class _STL::vector<BfmeE12, _STL::allocator<BfmeE12> >;
