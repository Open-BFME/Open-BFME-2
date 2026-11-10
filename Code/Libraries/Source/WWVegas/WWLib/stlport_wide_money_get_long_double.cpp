// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// STLport 4.5.3 money_get<wchar_t>::do_get over long double.
// /D_CRTIMP= keeps free a direct call to the game allocator, and /EHs lets it
// throw, preserving retail's unwind states.
#include <stdlib.h>

#include <stl/_alloc.h>
// Keep retail's inline character-buffer cleanup; the public allocator
// entry point is supplied by its separately verified owner.
namespace _STL {
template <> void __malloc_alloc<0>::deallocate(void *, size_t);
template <> __forceinline void allocator<char>::deallocate(char *p, size_t) const { if (p != 0) free(p); }
template <> __forceinline void allocator<unsigned short>::deallocate(unsigned short *p, size_t) const { if (p != 0) free(p); }
}

#include <string>
// The canonical default constructor is verified at retail7850.
namespace _STL { template <> basic_string<char>::basic_string(); }
#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }

// Keep the vendor _M_getc body visible for MSVC's side-effect analysis while
// preserving retail's out-of-line calls. A declaration alone makes the compiler
// spill the iterator instead of retaining it in ebp/ebx across those calls.
namespace _STL
{
template <>
__declspec(noinline) void istreambuf_iterator<wchar_t, char_traits<wchar_t> >::_M_getc() const
{
    if (_M_have_c)
        return;
    int_type c = _M_buf->sgetc();
    _M_c = traits_type::to_char_type(c);
    _M_eof = traits_type::eq_int_type(c, traits_type::eof());
    _M_have_c = true;
}
// operator* stays inline-only: with _M_getc out of line its copy would differ
// from retail's and be the first one in link order.
template <> __declspec(dllimport) __forceinline
wchar_t istreambuf_iterator<wchar_t, char_traits<wchar_t> >::operator*() const
{ this->_M_getc(); return _M_c; }
}

namespace _STL
{
template <>
wchar_t *allocator<wchar_t>::allocate(size_t, const void*) const;
}

// Suppress this TU's non-retail _String_base<char> dtor copy (family2-LK3 rows
// 22/26): the rowed 63B copy in stlport_narrow_string_base_dtor.cpp serves the link.
template <> _STL::_String_base<char, _STL::allocator<char> >::~_String_base();
// The wide one stays inline. Without nothrow, the wide ~basic_string copy that
// do_get's unwind funclet calls keeps retail's EH frame (the 63B body rowed at
// 0xB3C0); this unit precedes that row's owner in link order, so its copy is kept.
namespace _STL {
template <> __declspec(dllimport) __forceinline _String_base<unsigned short, allocator<unsigned short> >::~_String_base() { _M_deallocate_block(); }
}
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> bool __get_decimal_integer<unsigned short *, long double>(unsigned short *&, unsigned short *&, long double &); }
namespace _STL { template <> bool __get_monetary_value<istreambuf_iterator<unsigned short, char_traits<unsigned short> >, back_insert_iterator<basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > >, unsigned short>(istreambuf_iterator<unsigned short, char_traits<unsigned short> > &, istreambuf_iterator<unsigned short, char_traits<unsigned short> >, back_insert_iterator<basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > >, ctype<unsigned short> const &, unsigned short, int, unsigned short, basic_string<char, char_traits<char>, allocator<char> > const &, bool &); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(); }
namespace _STL { template <> unsigned short * basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_insert_aux(unsigned short *, unsigned short); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> istreambuf_iterator<unsigned short,char_traits<unsigned short> > money_get<unsigned short,istreambuf_iterator<unsigned short,char_traits<unsigned short> > >::do_get(istreambuf_iterator<unsigned short,char_traits<unsigned short> >,istreambuf_iterator<unsigned short,char_traits<unsigned short> >,bool,ios_base &,int &,basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> > &) const; }
// Suppress this TU's non-retail copy of ??$mismatch@V?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@PAG@_STL@@YA?AU?$pair@V?:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> pair<istreambuf_iterator<unsigned short,char_traits<unsigned short> >,unsigned short *> mismatch<istreambuf_iterator<unsigned short,char_traits<unsigned short> >,unsigned short *>(istreambuf_iterator<unsigned short,char_traits<unsigned short> >,istreambuf_iterator<unsigned short,char_traits<unsigned short> >,unsigned short *); }
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// The locale owner emits the rowed constructor. Instantiate only this numeric
// overload here so its vtable does not pull in the separate string parser.
template _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >
_STL::money_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >::do_get(
    _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >,
    _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >,
    bool, _STL::ios_base &, int &, long double &) const;
