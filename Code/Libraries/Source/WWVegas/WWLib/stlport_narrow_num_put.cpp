// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport46

// Keep unused inline storage allocation local to this numeric facet.
#define _M_allocate_block _M_allocate_block_NumPut_RV
#include <string>

// Bind string copies to their independently rowed owner.
namespace _STL {
template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(const basic_string<char, char_traits<char>, allocator<char> > &);
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// Native base cleanup is supplied by the independently verified B3C0 owner.
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }

namespace _STL
{
template <>
basic_string<char, char_traits<char>, allocator<char> >::~basic_string();

template <>
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(
        char*, size_t);
}

#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, the
// retail unit that also holds this file's facet constructor (0x00006F50): its
// scalar deleting destructor (0x00007490) inlines the empty body. Seeing the
// body here makes this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }
// bfme link decl-only begin
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > __copy_float_and_fill<char, ostreambuf_iterator<char, char_traits<char> > >(char const *, char const *, ostreambuf_iterator<char, char_traits<char> >, int, int, char, char, char); }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > __copy_integer_and_fill<char, ostreambuf_iterator<char, char_traits<char> > >(char const *, int, ostreambuf_iterator<char, char_traits<char> >, int, int, char, char, char); }
namespace _STL { template <> char * __write_decimal_backward<long>(char *, long, int, __true_type const &); }
namespace _STL { template <> char * __write_integer_backward<long>(char *, int, long); }
namespace _STL { template <> char * __write_integer_backward<unsigned long>(char *, int, unsigned long); }
namespace _STL { template <> char * __write_integer_backward<__int64>(char *, int, __int64); }
namespace _STL { template <> char * __write_integer_backward<unsigned __int64>(char *, int, unsigned __int64); }
namespace _STL { template <> char * __write_decimal_backward<__int64>(char *, __int64, int, __true_type const &); }
namespace _STL { template <> char * __write_decimal_backward<unsigned __int64>(char *, unsigned __int64, int, __false_type const &); }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > _M_do_put_float<char, ostreambuf_iterator<char, char_traits<char> >, double>(ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, double); }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > __put_integer<ostreambuf_iterator<char, char_traits<char> > >(char *, char *, ostreambuf_iterator<char, char_traits<char> >, ios_base &, int, char); }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > num_put<char, ostreambuf_iterator<char, char_traits<char> > >::do_put(ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, void const *) const; }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > num_put<char, ostreambuf_iterator<char, char_traits<char> > >::do_put(ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, bool) const; }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > _M_do_put_float<char, ostreambuf_iterator<char, char_traits<char> >, long double>(ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, long double); }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > __put_float<ostreambuf_iterator<char, char_traits<char> > >(char *, char *, ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, char, char, const basic_string<char, char_traits<char>, allocator<char> > &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$allocator@D@_STL@@QBEPADIPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * allocator<char>::allocate(unsigned int,void const *); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEPADI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * _STL::_STLP_alloc_proxy<char *,char,_STL::allocator<char> >::allocate(unsigned int, const void*); }
// __copy_integer_and_fill<char> is owned by stlport_narrow_copy_integer_and_fill.cpp.
// This unit's copy is not retail's and inlined sputc into an out-of-line
// ostreambuf_iterator<char>::operator= that came first in link order, ahead of
// retail's. The fill_n, __copy and __copy_aux helpers it instantiated are emitted
// by stlport_narrow_num_put_bool.cpp.
// basic_string<char>::reserve is retail's 116-byte body at 0x0000C390, owned by
// stlport_narrow_string_reserve.cpp; this unit's header copy is not retail's and
// came before it in link order, so only declare its instantiation here.
namespace _STL { extern template void basic_string<char, char_traits<char>, allocator<char> >::reserve(size_t); }

// do_put(bool) and do_put(const void *) are owned by stlport_narrow_num_put_bool.cpp and
// stlport_narrow_num_put_voidptr.cpp; leave them declared so this unit emits neither (nor their getloc).
namespace _STL {
template <> ostreambuf_iterator<char, char_traits<char> >
num_put<char, ostreambuf_iterator<char, char_traits<char> > >::do_put(
    ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, bool) const;
template <> ostreambuf_iterator<char, char_traits<char> >
num_put<char, ostreambuf_iterator<char, char_traits<char> > >::do_put(
    ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, const void *) const;
}
template class _STL::num_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;

// The float writers are declared above (their rowed copies live in
// stlport_narrow_num_get_double.cpp); the rowed find<char*,char> they used to
// pull in stays emitted through this anchor.
extern char *(*const _bfmeAnchorFindChar)(char *, char *, const char &) = &_STL::find<char *, char>;
