// cl: /ICode/Libraries/Source/WWVegas/WWLib/TimeInfoLink /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <string>
// Use the rowed 14-byte string destructor at RVA 0x00142D70.
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }

// Suppress this TU's non-retail _String_base<char> dtor copy (family2-LK3 rows
// 22/26): the rowed 63B copy in stlport_narrow_string_base_dtor.cpp serves the link.
template <> _STL::_String_base<char, _STL::allocator<char> >::~_String_base();
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
// bfme link decl-only end
// ostreambuf_iterator<char>::operator= and basic_streambuf<char>::sputc are inlined into
// every caller here; retail keeps the out-of-line operator= that calls sputc
// (stlport_ostreambuf_iterator_assign.cpp). Bind it to the kept retail copy instead of
// emitting this unit's own; sputc is spelled through the put area (_M_put is private)
// so it still inlines through the imported operator=.
namespace _STL {
struct _BfmeStreambufPutView { void *_M_vfptr; FILE *_M_get; FILE *_M_put; };
struct _BfmeStreambufOverflow : basic_streambuf<char, char_traits<char> > { using basic_streambuf<char, char_traits<char> >::overflow; };
__declspec(dllimport) __forceinline int _BfmeSputc(basic_streambuf<char, char_traits<char> > *__buf, char __c) {
  int __res;
  FILE *&_M_put = ((_BfmeStreambufPutView *)__buf)->_M_put;
  if (_FILE_O_avail(_M_put) > 0) { _FILE_O_postincr(_M_put) = __c; __res = char_traits<char>::to_int_type(__c); }
  else __res = static_cast<_BfmeStreambufOverflow *>(__buf)->overflow(char_traits<char>::to_int_type(__c));
  return __res;
}
template <> __declspec(dllimport) __forceinline ostreambuf_iterator<char, char_traits<char> > & ostreambuf_iterator<char, char_traits<char> >::operator=(char __c) { _M_ok = _M_ok && !char_traits<char>::eq_int_type(_BfmeSputc(_M_buf, __c), char_traits<char>::eof()); return *this; }
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void allocator<char>::deallocate(char*, size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *allocator<char>::allocate(size_t, const void*);
}
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > time_put<char, ostreambuf_iterator<char, char_traits<char> > >::do_put(ostreambuf_iterator<char, char_traits<char> >, ios_base &, char, const tm *, char, char) const; }
template class _STL::time_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
