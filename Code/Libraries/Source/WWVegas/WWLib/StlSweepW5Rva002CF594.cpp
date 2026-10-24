// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x002CF594 (29B) is STLport's __copy_ptrs forwarder (const __false_type& tag): its
// REL32 lands on 0x004F4DC0, rowed as __copy<Rva004F4DC0Element *> in
// StlSweepW5Rva004F4DC0.cpp. The element type is that row's (identity unresolved
// beyond it); the callee is only declared here, so this unit emits the forwarder alone.
#include <algorithm>

struct Rva004F4DC0Element;

namespace _STL {
template <> Rva004F4DC0Element *__copy<Rva004F4DC0Element *, Rva004F4DC0Element *, int>(Rva004F4DC0Element *, Rva004F4DC0Element *, Rva004F4DC0Element *, const random_access_iterator_tag &, int *);
}

template Rva004F4DC0Element *_STL::__copy_ptrs<Rva004F4DC0Element *, Rva004F4DC0Element *>(Rva004F4DC0Element *, Rva004F4DC0Element *, Rva004F4DC0Element *, const _STL::__false_type &);
