// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x000B67BC (29B) is STLport's __copy_ptrs forwarder (const __false_type& tag): its
// REL32 lands on 0x000B6894, rowed as __copy<Rva00B6CF1 *> in
// stlport_vector_rva00b6cf1_destroy.cpp. The element type is that row's (identity unresolved
// beyond it); the callee is only declared here, so this unit emits the forwarder alone.
#include <algorithm>

struct Rva00B6CF1;

namespace _STL {
template <> Rva00B6CF1 *__copy<Rva00B6CF1 *, Rva00B6CF1 *, int>(Rva00B6CF1 *, Rva00B6CF1 *, Rva00B6CF1 *, const random_access_iterator_tag &, int *);
}

template Rva00B6CF1 *_STL::__copy_ptrs<Rva00B6CF1 *, Rva00B6CF1 *>(Rva00B6CF1 *, Rva00B6CF1 *, Rva00B6CF1 *, const _STL::__false_type &);
