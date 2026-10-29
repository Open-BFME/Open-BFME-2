// cl: /ICode/Libraries/Source/WWVegas/WWLib/TimeInfoLink /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
// Instantiate the protected locale-time overload directly from STLport 4.5.3
// stl/_time_facets.h. Vtables BBBBC0 (narrow) and BBBBEC (wide) are independently
// established by the matched default constructors and destructors;
// _Time_Info starts at +0xC in both facets.
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
// Suppress this TU's int __get_decimal_integer copies: do_get_year calls them
// out of line, and retail folds them into the long readers at 0x00009CD0 and
// 0x0000B4C0, whose units emit the int instantiations too.
namespace _STL {
template <> bool _STLP_CALL __get_decimal_integer<istreambuf_iterator<char, char_traits<char> >, int>(
    istreambuf_iterator<char, char_traits<char> > &, istreambuf_iterator<char, char_traits<char> > &, int &);
template <> bool _STLP_CALL __get_decimal_integer<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, int>(
    istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, int &);
}
template _STL::time_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >::time_get(_Locale_time *, size_t);
template _STL::time_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >::time_get(_Locale_time *, size_t);
