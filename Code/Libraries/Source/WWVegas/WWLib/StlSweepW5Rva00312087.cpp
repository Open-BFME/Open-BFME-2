// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is BfmeStringHeadRecord184: this forwarder's only call goes to the rowed
// __copy_backward<BfmeStringHeadRecord184 *> at 0x003115CC (stlport_asciistring_record_bodies.cpp),
// which also emits this same forwarder for BfmeStringHeadRecord184.
#include <vector>

#include "BfmeStringHeadRecord184.h"

// Declared only: the rowed copy serves the call.
namespace _STL { template <> BfmeStringHeadRecord184 *__copy_backward<BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, int>(BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, const random_access_iterator_tag &, int *); }

template BfmeStringHeadRecord184 *_STL::__copy_backward_ptrs<BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *>(BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *, const _STL::__false_type &);
