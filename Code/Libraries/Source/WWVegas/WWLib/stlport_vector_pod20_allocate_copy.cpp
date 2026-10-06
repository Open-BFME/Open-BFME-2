// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 20-byte POD element.
// The allocator and the trivial-copy worker are both settled; the placeholder
// BfmePod20 names only the 20-byte stride, matching the pod-vector TU convention.
//
// ??$__lower_bound@PAUBfmePod20@@U1@U?$less@UBfmePod20@@@_STL@@H@_STL@@YAPAUBfmePod20@@PAU1@0ABU1@U?$less@UBfmePod20@@@0@PAH@Z @0x005413F2 (66B):
// __lower_bound over BfmePod20 pointers with default less<> on a[0]; idiv
// stride count plus halving loop. Caller 0x0054150A.
// Evidence: unlock lane, all callees rowed, unblocks 0x0054150A.
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
#include <algorithm>
struct BfmePod20 { int a[5]; __forceinline bool operator<(const BfmePod20 &o) const { return a[0] < o.a[0]; } };
template class _STL::vector<BfmePod20, _STL::allocator<BfmePod20> >;
template BfmePod20 *_STL::__lower_bound<BfmePod20 *, BfmePod20, _STL::less<BfmePod20>, int>(BfmePod20 *, BfmePod20 *, const BfmePod20 &, _STL::less<BfmePod20>, int *);
