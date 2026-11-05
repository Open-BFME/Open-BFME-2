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
// Suppress this TU's basic_string<char> default constructor and reserve copies: they
// allocate through the stock pool but free through the game's free, and as the first
// definer they beat the retail copies (0x00007850 stlport_narrow_string_default_ctor.cpp,
// 0x0000C390 stlport_narrow_string_reserve.cpp; game allocate and free) in the link, so
// the first string grown faulted in GeneralAllocator. Plain declaration-only form (no
// __imp_), as for the proxy above.
namespace _STL {
template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string();
template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(size_t);
}
template class _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> >;
