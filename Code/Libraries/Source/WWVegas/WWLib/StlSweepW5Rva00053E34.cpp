// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x00053E34 (29B) is STLport's __copy_ptrs forwarder (const __false_type& tag): its
// REL32 lands on 0x00051BE1, rowed as __copy<UnicodeString *> in
// Rva00051C10Copy.cpp. The element type is that row's (identity unresolved
// beyond it); the callee is only declared here, so this unit emits the forwarder alone.
#include <algorithm>

class UnicodeString;

namespace _STL {
template <> UnicodeString *__copy<UnicodeString *, UnicodeString *, int>(UnicodeString *, UnicodeString *, UnicodeString *, const random_access_iterator_tag &, int *);
}

template UnicodeString *_STL::__copy_ptrs<UnicodeString *, UnicodeString *>(UnicodeString *, UnicodeString *, UnicodeString *, const _STL::__false_type &);
