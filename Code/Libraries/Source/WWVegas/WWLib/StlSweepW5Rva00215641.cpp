// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x00215641 (29B) is STLport's __copy_backward_ptrs forwarder (const __false_type& tag): its
// REL32 lands on 0x00215551, rowed as __copy_backward<BfmeVectorRecord0002154F3 *> in
// stlport_vector_record_2154f3_allocate_copy.cpp. The element type is that row's (identity unresolved
// beyond it); the callee is only declared here, so this unit emits the forwarder alone.
#include <algorithm>

struct BfmeVectorRecord0002154F3;

namespace _STL {
template <> BfmeVectorRecord0002154F3 *__copy_backward<BfmeVectorRecord0002154F3 *, BfmeVectorRecord0002154F3 *, int>(BfmeVectorRecord0002154F3 *, BfmeVectorRecord0002154F3 *, BfmeVectorRecord0002154F3 *, const random_access_iterator_tag &, int *);
}

template BfmeVectorRecord0002154F3 *_STL::__copy_backward_ptrs<BfmeVectorRecord0002154F3 *, BfmeVectorRecord0002154F3 *>(BfmeVectorRecord0002154F3 *, BfmeVectorRecord0002154F3 *, BfmeVectorRecord0002154F3 *, const _STL::__false_type &);
