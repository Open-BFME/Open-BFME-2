// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 operations for the target fixed-storage record view.
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

#include "Object156.h"
template BfmeOpaqueRecord156 *_STL::__uninitialized_copy<BfmeOpaqueRecord156 *, BfmeOpaqueRecord156 *>(BfmeOpaqueRecord156 *, BfmeOpaqueRecord156 *, BfmeOpaqueRecord156 *, const _STL::__false_type &);
template BfmeOpaqueRecord156 *_STL::__uninitialized_fill_n<BfmeOpaqueRecord156 *, unsigned int, BfmeOpaqueRecord156>(BfmeOpaqueRecord156 *, unsigned int, const BfmeOpaqueRecord156 &, const _STL::__false_type &);
template void _STL::vector<BfmeOpaqueRecord156>::_M_insert_overflow(BfmeOpaqueRecord156 *, const BfmeOpaqueRecord156 &, const _STL::__false_type &, unsigned int, bool);
template BfmeOpaqueRecord156 *_STL::__copy<BfmeOpaqueRecord156 *, BfmeOpaqueRecord156 *, int>(BfmeOpaqueRecord156 *, BfmeOpaqueRecord156 *, BfmeOpaqueRecord156 *, const _STL::random_access_iterator_tag &, int *);
template void _STL::vector<BfmeOpaqueRecord156>::push_back(const BfmeOpaqueRecord156 &);
