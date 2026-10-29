// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

// Share the retail locale-copy operation with stlport_locale.cpp before
// ios_base::getloc is defined, so its return-value copy inlines here too.
#include <stl/_locale.h>
namespace _STL {
class _Locale_impl
{
public:
    virtual ~_Locale_impl();
    virtual void _M_incr();
    virtual void _M_decr();
    locale::facet **_M_facets;
    unsigned int _M_count;
};
inline locale::locale(const locale &that) _STLP_NOTHROW
{
    _M_impl = 0;
    _Locale_impl *impl = that._M_impl;
    impl->_M_incr();
    _M_impl = impl;
}
}
#include <istream>

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> locale basic_ios<unsigned short, char_traits<unsigned short> >::imbue(locale const &); }
// bfme link decl-only end
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
template class _STL::basic_istream<wchar_t, _STL::char_traits<wchar_t> >;
