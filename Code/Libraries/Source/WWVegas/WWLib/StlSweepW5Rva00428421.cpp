// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x00428421 (29B) is STLport's __copy_backward_ptrs forwarder (const __false_type& tag): its
// REL32 lands on 0x004282BD, rowed as __copy_backward<BfmeAssignRecord24 *> in
// stlport_asciistring_record_bodies.cpp. The element type is that row's (identity unresolved
// beyond it); the callee is only declared here, so this unit emits the forwarder alone.
#include <algorithm>

struct BfmeAssignRecord24;

namespace _STL {
template <> BfmeAssignRecord24 *__copy_backward<BfmeAssignRecord24 *, BfmeAssignRecord24 *, int>(BfmeAssignRecord24 *, BfmeAssignRecord24 *, BfmeAssignRecord24 *, const random_access_iterator_tag &, int *);
}

template BfmeAssignRecord24 *_STL::__copy_backward_ptrs<BfmeAssignRecord24 *, BfmeAssignRecord24 *>(BfmeAssignRecord24 *, BfmeAssignRecord24 *, BfmeAssignRecord24 *, const _STL::__false_type &);
