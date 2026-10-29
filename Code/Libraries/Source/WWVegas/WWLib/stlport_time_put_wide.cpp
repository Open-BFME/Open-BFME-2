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

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
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
template <> void allocator<char>::deallocate(char*, size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *allocator<char>::allocate(size_t, const void*);
}
template class _STL::time_put<wchar_t, _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
