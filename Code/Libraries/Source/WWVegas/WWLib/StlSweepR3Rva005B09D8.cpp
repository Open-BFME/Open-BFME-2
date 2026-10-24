// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x005B09D8 (29B) is STLport's __copy_ptrs forwarder (const __false_type& tag): its
// REL32 lands on 0x005B04D3, rowed as __copy<Rva005B09D8Record *> in
// Rva005B09D8CopyPointers.cpp. The element type is that row's (identity unresolved
// beyond it); the callee is only declared here, so this unit emits the forwarder alone.
#include <algorithm>

struct Rva005B09D8Record;

namespace _STL {
template <> Rva005B09D8Record *__copy<Rva005B09D8Record *, Rva005B09D8Record *, int>(Rva005B09D8Record *, Rva005B09D8Record *, Rva005B09D8Record *, const random_access_iterator_tag &, int *);
}

template Rva005B09D8Record *_STL::__copy_ptrs<Rva005B09D8Record *, Rva005B09D8Record *>(Rva005B09D8Record *, Rva005B09D8Record *, Rva005B09D8Record *, const _STL::__false_type &);
