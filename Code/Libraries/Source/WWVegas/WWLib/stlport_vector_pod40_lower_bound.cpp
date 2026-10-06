// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__lower_bound@PAUBfmePod40@@U1@U?$less@UBfmePod40@@@_STL@@H@_STL@@YAPAUBfmePod40@@PAU1@0ABU1@U?$less@UBfmePod40@@@0@PAH@Z @0x00540253 (66B):
// __lower_bound over BfmePod40 pointers with default less<> on a[0]; idiv
// stride count plus halving loop. Caller 0x00540319.
// Evidence: unlock lane, all callees rowed, unblocks 0x00540301.
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
struct BfmePod40 { int a[10]; __forceinline bool operator<(const BfmePod40 &o) const { return a[0] < o.a[0]; } };
template class _STL::vector<BfmePod40, _STL::allocator<BfmePod40> >;
template BfmePod40 *_STL::__lower_bound<BfmePod40 *, BfmePod40, _STL::less<BfmePod40>, int>(BfmePod40 *, BfmePod40 *, const BfmePod40 &, _STL::less<BfmePod40>, int *);
