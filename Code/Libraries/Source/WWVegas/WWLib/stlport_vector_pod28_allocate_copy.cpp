// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Exact no-EH STLport vector allocation/copy for the retail 28-byte POD element.
// The allocator and the trivial-copy worker are both settled; the placeholder
// BfmePod28 names only the 28-byte stride, matching the pod-vector TU convention.
//
// ??$__lower_bound@PAUBfmePod28@@U1@U?$less@UBfmePod28@@@_STL@@H@_STL@@YAPAUBfmePod28@@PAU1@0ABU1@U?$less@UBfmePod28@@@0@PAH@Z @0x005413B0 (66B):
// __lower_bound over BfmePod28 pointers with default less<> on a[0]; idiv
// stride count plus halving loop. Caller 0x005414DA.
// Evidence: unlock lane, all callees rowed, unblocks 0x005414C2.
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
#include <algorithm>
struct BfmePod28 { int a[7]; __forceinline bool operator<(const BfmePod28 &o) const { return a[0] < o.a[0]; } };
template class _STL::vector<BfmePod28, _STL::allocator<BfmePod28> >;
template BfmePod28 *_STL::__lower_bound<BfmePod28 *, BfmePod28, _STL::less<BfmePod28>, int>(BfmePod28 *, BfmePod28 *, const BfmePod28 &, _STL::less<BfmePod28>, int *);
