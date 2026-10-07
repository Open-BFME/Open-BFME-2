// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport

#include <stl/_alloc.h>
// Public malloc release uses retail's unoptimized import entry; callers keep the header inline body.
namespace _STL {
#pragma optimize("", off)
template <> __forceinline void __malloc_alloc<0>::deallocate(void *p, size_t) { free((char *)p); }
#pragma optimize("", on)
}

#include <locale>

template class _STL::num_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
