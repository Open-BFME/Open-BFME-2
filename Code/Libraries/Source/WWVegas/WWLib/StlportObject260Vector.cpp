// cl: /O1 /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
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
#include "Object260.h"
typedef _STL::vector<BfmeFixedObject260, _STL::allocator<BfmeFixedObject260> > BfmeFixedObject260Vector;
template BfmeFixedObject260* BfmeFixedObject260Vector::_M_allocate_and_copy<const BfmeFixedObject260*>(unsigned int, const BfmeFixedObject260*, const BfmeFixedObject260*);

template void BfmeFixedObject260Vector::push_back(const BfmeFixedObject260&);
