// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x0007EA02 (29B) is STLport's __copy_ptrs forwarder (const __false_type& tag): its
// REL32 lands on 0x0007E422, rowed as __copy<BfmePod44 *> in
// stlport_pod_vector_bodies.cpp. The element type is that row's (identity unresolved
// beyond it); the callee is only declared here, so this unit emits the forwarder alone.
#include <algorithm>

struct BfmePod44;

namespace _STL {
template <> BfmePod44 *__copy<BfmePod44 *, BfmePod44 *, int>(BfmePod44 *, BfmePod44 *, BfmePod44 *, const random_access_iterator_tag &, int *);
}

template BfmePod44 *_STL::__copy_ptrs<BfmePod44 *, BfmePod44 *>(BfmePod44 *, BfmePod44 *, BfmePod44 *, const _STL::__false_type &);
