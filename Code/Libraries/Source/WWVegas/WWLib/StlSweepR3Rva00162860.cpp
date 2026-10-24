// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x00162860 (32B) is STLport's __copy_backward_ptrs forwarder (const __false_type& tag): its
// REL32 lands on 0x001611B0, rowed as __copy_backward<Elem36 *> in
// StlportCapturedBoneCopyBackward.cpp. The element type is that row's (identity unresolved
// beyond it); the callee is only declared here, so this unit emits the forwarder alone.
#include <algorithm>

struct Elem36;

namespace _STL {
template <> Elem36 *__copy_backward<Elem36 *, Elem36 *, int>(Elem36 *, Elem36 *, Elem36 *, const random_access_iterator_tag &, int *);
}

template Elem36 *_STL::__copy_backward_ptrs<Elem36 *, Elem36 *>(Elem36 *, Elem36 *, Elem36 *, const _STL::__false_type &);
