// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <sstream>

#include <cstddef>
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
// Keep uninitialized_copy<char*,char*> inline-only: no retail copy exists
// (every caller inlines it), and this TU's tail-jump copy differs from the
// memmove copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
char *uninitialized_copy<char *, char *>(char *__first, char *__last, char *__result)
{ return (char *)__copy_trivial(__first, __last, __result); }
}
template class _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> >;
