// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target vector<Owner900> dtor at 0x004CB996/63 and _M_clear at 0x004CB9D5/30 via rowed _Destroy 0x004CB97E and _free 0x30830.
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

#include "OwnedRecord900.h"
template class _STL::vector<BfmeRecordOwner900, _STL::allocator<BfmeRecordOwner900> >;
