// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> bool __get_decimal_integer<unsigned short *, long double>(unsigned short *&, unsigned short *&, long double &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(); }
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> unsigned short * basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_insert_aux(unsigned short *, unsigned short); }
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *); }
namespace _STL { template <> istreambuf_iterator<unsigned short, char_traits<unsigned short> > money_get<unsigned short, istreambuf_iterator<unsigned short, char_traits<unsigned short> > >::do_get(istreambuf_iterator<unsigned short, char_traits<unsigned short> >, istreambuf_iterator<unsigned short, char_traits<unsigned short> >, bool, ios_base &, int &, long double &) const; }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ??$__get_monetary_value@V?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@V?$back_inse:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool __get_monetary_value<istreambuf_iterator<unsigned short,char_traits<unsigned short> >,back_insert_iterator<basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> > >,unsigned short>(istreambuf_iterator<unsigned short,char_traits<unsigned short> > &,istreambuf_iterator<unsigned short,char_traits<unsigned short> >,back_insert_iterator<basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> > >,ctype<unsigned short> const &,unsigned short,int,unsigned short,basic_string<char,char_traits<char>,allocator<char> > const &,bool &); }
// Suppress this TU's non-retail copy of ??$uninitialized_copy@PAGPAG@_STL@@YAPAGPAG00@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned short * uninitialized_copy<unsigned short *,unsigned short *>(unsigned short *,unsigned short *,unsigned short *); }
// Suppress this TU's non-retail copy of ??$mismatch@V?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@PAG@_STL@@YA?AU?$pair@V?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> pair<istreambuf_iterator<unsigned short,char_traits<unsigned short> >,unsigned short *> mismatch<istreambuf_iterator<unsigned short,char_traits<unsigned short> >,unsigned short *>(istreambuf_iterator<unsigned short,char_traits<unsigned short> >,istreambuf_iterator<unsigned short,char_traits<unsigned short> >,unsigned short *); }
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@GV?$allocator@G@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<unsigned short, allocator<unsigned short> >::_M_deallocate_block(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@G@_STL@@QBEXPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<unsigned short>::deallocate(unsigned short *, size_t); }
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
// Keep the STLport allocation forwarding inline without an unused external copy.
typedef _STL::basic_string<wchar_t> WideString;
template _STL::back_insert_iterator<WideString> &_STL::back_insert_iterator<WideString>::operator=(const wchar_t &);
template WideString &WideString::_M_append_dispatch<wchar_t *>(wchar_t *, wchar_t *, const _STL::__false_type &);
template WideString &WideString::append<wchar_t *>(wchar_t *, wchar_t *);
