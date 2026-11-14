// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeStringHeadRecord184: _M_clear's destroy call goes to the rowed
// _Destroy<BfmeStringHeadRecord184 *> at 0x0008B632 (stlport_asciistring_record_bodies.cpp).
#include <vector>

#include "BfmeStringHeadRecord184.h"

// Declared only: the rowed copy serves the call.
namespace _STL { template <> void _Destroy<BfmeStringHeadRecord184 *>(BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *); }

template void _STL::vector<BfmeStringHeadRecord184, _STL::allocator<BfmeStringHeadRecord184> >::_M_clear(void);
