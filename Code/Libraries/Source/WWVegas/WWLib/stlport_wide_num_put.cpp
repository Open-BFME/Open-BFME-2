// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport46

#include <stl/_alloc.h>
// The 18-byte malloc release is owned by STLMallocAlloc0Deallocate.cpp; this
// unit's copy is not retail's, so declare the instantiation only.
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, size_t); }

#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }
// The 64-bit integer writers are owned by stlport_write_integer_backward_64.cpp,
// stlport_write_integer_backward_int64.cpp and stlport_write_decimal_backward_u64.cpp.
// This unit's copies are not retail's; declare their instantiations only.
namespace _STL { template <> char * __write_integer_backward<__int64>(char *, int, __int64); }
namespace _STL { template <> char * __write_integer_backward<unsigned __int64>(char *, int, unsigned __int64); }
namespace _STL { template <> char * __write_decimal_backward<unsigned __int64>(char *, unsigned __int64, int, __false_type const &); }

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> ostreambuf_iterator<unsigned short, char_traits<unsigned short> > _M_do_put_float<unsigned short, ostreambuf_iterator<unsigned short, char_traits<unsigned short> >, double>(ostreambuf_iterator<unsigned short, char_traits<unsigned short> >, ios_base &, unsigned short, double); }
namespace _STL { template <> ostreambuf_iterator<unsigned short, char_traits<unsigned short> > _M_do_put_float<unsigned short, ostreambuf_iterator<unsigned short, char_traits<unsigned short> >, long double>(ostreambuf_iterator<unsigned short, char_traits<unsigned short> >, ios_base &, unsigned short, long double); }
namespace _STL { template <> ostreambuf_iterator<unsigned short, char_traits<unsigned short> > __copy_float_and_fill<unsigned short, ostreambuf_iterator<unsigned short, char_traits<unsigned short> > >(unsigned short const *, unsigned short const *, ostreambuf_iterator<unsigned short, char_traits<unsigned short> >, int, int, unsigned short, unsigned short, unsigned short); }
namespace _STL { template <> ostreambuf_iterator<unsigned short, char_traits<unsigned short> > __put_integer<ostreambuf_iterator<unsigned short, char_traits<unsigned short> > >(char *, char *, ostreambuf_iterator<unsigned short, char_traits<unsigned short> >, ios_base &, int, unsigned short); }
namespace _STL { template <> char * __write_decimal_backward<long>(char *, long, int, __true_type const &); }
namespace _STL { template <> char * __write_integer_backward<long>(char *, int, long); }
namespace _STL { template <> char * __write_integer_backward<unsigned long>(char *, int, unsigned long); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
// The 4.6 non-const allocator shares retail's complete 29-byte word body at
// 0x00017710 with the const member in stlport_wide_string.cpp. GameMemory.cpp
// owns its static byte allocator. The word-vector growth paths need this
// out-of-line name too; retain it explicitly in this /O2 unit.
extern "C" char *__cdecl __identifier("?allocate@?$allocator@D@_STL@@SAPADIPBX@Z")(size_t, const void *);
namespace _STL {
template <> __declspec(noinline)
unsigned short *allocator<unsigned short>::allocate(size_t count, const void *)
{
    return count != 0 ? reinterpret_cast<unsigned short *>(__identifier("?allocate@?$allocator@D@_STL@@SAPADIPBX@Z")(count * sizeof(value_type), 0)) : 0;
}
}
template unsigned short *_STL::allocator<unsigned short>::allocate(size_t, const void *);
namespace _STL { template <> ostreambuf_iterator<unsigned short, char_traits<unsigned short> > num_put<unsigned short, ostreambuf_iterator<unsigned short, char_traits<unsigned short> > >::do_put(ostreambuf_iterator<unsigned short, char_traits<unsigned short> >, ios_base &, unsigned short, void const *) const; }
namespace _STL { template <> ostreambuf_iterator<unsigned short, char_traits<unsigned short> > num_put<unsigned short, ostreambuf_iterator<unsigned short, char_traits<unsigned short> > >::do_put(ostreambuf_iterator<unsigned short, char_traits<unsigned short> >, ios_base &, unsigned short, bool) const; }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
namespace _STL { template <> ostreambuf_iterator<unsigned short, char_traits<unsigned short> > __copy_integer_and_fill<unsigned short, ostreambuf_iterator<unsigned short, char_traits<unsigned short> > >(unsigned short const *, int, ostreambuf_iterator<unsigned short, char_traits<unsigned short> >, int, int, unsigned short, unsigned short, unsigned short); }
namespace _STL { template <> ostreambuf_iterator<unsigned short, char_traits<unsigned short> > __put_float<ostreambuf_iterator<unsigned short, char_traits<unsigned short> > >(char *, char *, ostreambuf_iterator<unsigned short, char_traits<unsigned short> >, ios_base &, unsigned short, unsigned short, unsigned short, basic_string<char, char_traits<char>, allocator<char> > const &); }
// bfme link decl-only end
// ostreambuf_iterator<wchar_t>::operator= and sputc are inlined into every caller here;
// retail keeps the out-of-line operator= that calls sputc
// (stlport_ostreambuf_iterator_assign.cpp). Bind both to the kept retail copies instead
// of emitting this unit's own operator=, which inlines sputc.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned short basic_streambuf<unsigned short, char_traits<unsigned short> >::sputc(unsigned short __c) { return ((_M_pnext < _M_pend) ? char_traits<unsigned short>::to_int_type(*_M_pnext++ = __c) : this->overflow(char_traits<unsigned short>::to_int_type(__c))); } }
namespace _STL { template <> __declspec(dllimport) __forceinline ostreambuf_iterator<unsigned short, char_traits<unsigned short> > & ostreambuf_iterator<unsigned short, char_traits<unsigned short> >::operator=(unsigned short __c) { _M_ok = _M_ok && !char_traits<unsigned short>::eq_int_type(_M_buf->sputc(__c), char_traits<unsigned short>::eof()); return *this; } }
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
template class _STL::num_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
// The two writers above are declared only; keep the retail helpers they
// instantiated in this unit as explicit instantiations.
template unsigned short * _STL::find<unsigned short *, unsigned short>(unsigned short *, unsigned short *, unsigned short const &);
template _STL::ostreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> > _STL::__copy_aux<unsigned short const *, _STL::ostreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> > >(unsigned short const *, unsigned short const *, _STL::ostreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> >, _STL::__false_type const &);
template _STL::ostreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> > _STL::fill_n<_STL::ostreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> >, int, unsigned short>(_STL::ostreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> >, int, unsigned short const &);
template _STL::ostreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> > _STL::__copy<unsigned short const *, _STL::ostreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> >, int>(unsigned short const *, unsigned short const *, _STL::ostreambuf_iterator<unsigned short, _STL::char_traits<unsigned short> >, _STL::random_access_iterator_tag const &, int *);
