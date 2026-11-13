// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// The element is OpaqueRefElement4 (W5, tools/retail_identity.py OPAQUE_REF_DEQUE_DESTROY): retail's __destroy calls
// the rowed __destroy_aux<_Deque_iterator<OpaqueRefElement4>> 0x00054FD9, which destroys each element through
// ??_GOpaqueRefElement4 0x00051B1E and steps a 0x80-byte node by 4.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include "../../../../GameEngine/Include/Common/OpaqueRefElement4.h"
// W5's stride: the element these rows step is 4 bytes (tools/retail_identity.py OPAQUE_REF_DEQUE_*).
typedef char OpaqueRefElement4SizeIs4[sizeof(OpaqueRefElement4)==4?1:-1];

typedef _STL::_Deque_iterator<OpaqueRefElement4, _STL::_Nonconst_traits<OpaqueRefElement4> > OpaqueRefDequeIter;

// __destroy_aux stays visible: retail passes its __false_type tag as an address in the argument area, which the
// compiler does only with the callee's body in view. Its copy here is the rowed 0x00054FD9 body (StlportOwnedDeque.cpp).

template void _STL::__destroy<OpaqueRefDequeIter, OpaqueRefElement4>(OpaqueRefDequeIter, OpaqueRefDequeIter, OpaqueRefElement4 *);
