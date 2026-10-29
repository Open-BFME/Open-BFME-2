// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(char const *, allocator<char> const &); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > money_put<char, ostreambuf_iterator<char, char_traits<char> > >::do_put(ostreambuf_iterator<char, char_traits<char> >, bool, ios_base &, char, long double) const; }
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
// bfme link decl-only end
// The string do_put is rowed in stlport_narrow_money_put_string.cpp (0xC410); this
// instantiation's own optimized copy also emitted a non-retail range constructor.
namespace _STL { template <> ostreambuf_iterator<char, char_traits<char> > money_put<char, ostreambuf_iterator<char, char_traits<char> > >::do_put(ostreambuf_iterator<char, char_traits<char> >, bool, ios_base &, char, basic_string<char, char_traits<char>, allocator<char> > const &) const; }
// Suppress this TU's non-retail copy of ?_M_allocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_allocate_block(unsigned int); }
// Suppress this TU's non-retail copy of ??$__copy@PADV?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@_STL@@H@_STL@@YA?AV?$ostreamb:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> ostreambuf_iterator<char,char_traits<char> > __copy<char *,ostreambuf_iterator<char,char_traits<char> >,int>(char *,char *,ostreambuf_iterator<char,char_traits<char> >,random_access_iterator_tag const &,int *); }
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
template class _STL::money_put<char, _STL::ostreambuf_iterator<char, _STL::char_traits<char> > >;
// The string do_put is declaration-only here, so its rowed helpers are
// instantiated explicitly.
template _STL::ostreambuf_iterator<char, _STL::char_traits<char> > _STL::fill_n(_STL::ostreambuf_iterator<char, _STL::char_traits<char> >, unsigned int, const char &);
template const _STL::moneypunct<char, false> &_STL::use_facet<_STL::moneypunct<char, false> >(const _STL::locale &);
template const _STL::moneypunct<char, true> &_STL::use_facet<_STL::moneypunct<char, true> >(const _STL::locale &);
