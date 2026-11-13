// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// The element is OpaqueRefElement4 (W5, tools/retail_identity.py OPAQUE_REF_DEQUE_DTOR): retail's _Destroy calls the
// rowed __destroy 0x00055880 of deque<OpaqueRefElement4>'s iterator.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include "../../../../GameEngine/Include/Common/OpaqueRefElement4.h"
// W5's stride: the element these rows step is 4 bytes (tools/retail_identity.py OPAQUE_REF_DEQUE_*).
typedef char OpaqueRefElement4SizeIs4[sizeof(OpaqueRefElement4)==4?1:-1];

typedef _STL::_Deque_iterator<OpaqueRefElement4, _STL::_Nonconst_traits<OpaqueRefElement4> > OpaqueRefDequeIter;

// The range teardown is StlSweepW5Rva00055880.cpp's row 0x00055880: declared only here.
namespace _STL { template <> void __destroy<OpaqueRefDequeIter, OpaqueRefElement4>(OpaqueRefDequeIter, OpaqueRefDequeIter, OpaqueRefElement4 *); }

template void _STL::_Destroy<OpaqueRefDequeIter>(OpaqueRefDequeIter, OpaqueRefDequeIter);
