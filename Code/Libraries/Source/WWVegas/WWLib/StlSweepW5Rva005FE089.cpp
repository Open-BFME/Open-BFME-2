// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x005FE089 (29B) is STLport's __copy_backward_ptrs forwarder (const __false_type& tag): its
// REL32 lands on 0x005FDEEA, rowed as __copy_backward<Rva005FDEEAElement *> in
// StlSweepW5Rva005FDEEA.cpp. The element type is that row's (identity unresolved
// beyond it); the callee is only declared here, so this unit emits the forwarder alone.
#include <algorithm>

struct Rva005FDEEAElement;

namespace _STL {
template <> Rva005FDEEAElement *__copy_backward<Rva005FDEEAElement *, Rva005FDEEAElement *, int>(Rva005FDEEAElement *, Rva005FDEEAElement *, Rva005FDEEAElement *, const random_access_iterator_tag &, int *);
}

template Rva005FDEEAElement *_STL::__copy_backward_ptrs<Rva005FDEEAElement *, Rva005FDEEAElement *>(Rva005FDEEAElement *, Rva005FDEEAElement *, Rva005FDEEAElement *, const _STL::__false_type &);
