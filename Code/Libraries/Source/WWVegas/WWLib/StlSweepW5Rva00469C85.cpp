// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x00469C85 (29B) is STLport's __copy_ptrs forwarder (const __false_type& tag): its
// REL32 lands on 0x004FB354, rowed as __copy<const BfmeE16 *> in
// stlport_vector_e16_o1.cpp. The element type is that row's (identity unresolved
// beyond it); the callee is only declared here, so this unit emits the forwarder alone.
#include <algorithm>

struct BfmeE16;

namespace _STL {
template <> BfmeE16 *__copy<const BfmeE16 *, BfmeE16 *, int>(const BfmeE16 *, const BfmeE16 *, BfmeE16 *, const random_access_iterator_tag &, int *);
}

template BfmeE16 *_STL::__copy_ptrs<const BfmeE16 *, BfmeE16 *>(const BfmeE16 *, const BfmeE16 *, BfmeE16 *, const _STL::__false_type &);
