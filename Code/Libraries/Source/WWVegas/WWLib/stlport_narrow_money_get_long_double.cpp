// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// STLport 4.5.3 money_get<char>::do_get over long double.
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

#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }
// basic_string<char>::reserve is retail's 116-byte body at 0x0000C390, owned by
// stlport_narrow_string_reserve.cpp; this unit's header copy is not retail's and
// came before it in link order, so only declare its instantiation here.
namespace _STL { extern template void basic_string<char, char_traits<char>, allocator<char> >::reserve(size_t); }

// Keep the vendor _M_getc body visible for MSVC's side-effect analysis while
// preserving retail's out-of-line calls. A declaration alone makes the compiler
// spill the iterator instead of retaining it in ebp/ebx across those calls.
namespace _STL
{
template <>
__declspec(noinline) void istreambuf_iterator<char, char_traits<char> >::_M_getc() const
{
    if (_M_have_c)
        return;
    int_type c = _M_buf->sgetc();
    _M_c = traits_type::to_char_type(c);
    _M_eof = traits_type::eq_int_type(c, traits_type::eof());
    _M_have_c = true;
}
}
// istreambuf_iterator<char>::equal is retail's 126-byte body at 0x0000FA00, owned by
// stlport_narrow_istreambuf_iterator_equal.cpp. This unit's copy (with _M_getc out of
// line) is not retail's and came before it in link order; the body still inlines
// here, imported, so the unit emits no copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool istreambuf_iterator<char, char_traits<char> >::equal(const istreambuf_iterator<char, char_traits<char> >& __i) const {
  if (this->_M_buf)
    this->_M_getc();
  if (__i._M_buf)
    __i._M_getc();
  return this->_M_eof == __i._M_eof;
}
}
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> char * basic_string<char, char_traits<char>, allocator<char> >::_M_insert_aux(char *, char); }
namespace _STL { template <> bool __get_decimal_integer<char *, long double>(char *&, char *&, long double &); }
namespace _STL { template <> istreambuf_iterator<char, char_traits<char> > money_get<char, istreambuf_iterator<char, char_traits<char> > >::do_get(istreambuf_iterator<char, char_traits<char> >, istreambuf_iterator<char, char_traits<char> >, bool, ios_base &, int &, basic_string<char, char_traits<char>, allocator<char> > &) const; }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
// bfme link decl-only end
// Nothing here calls _String_base<char>'s destructor out of line, and this unit's
// frameless copy is not retail's 0x0000B3C0 body; keep it inline only.
namespace _STL { template <> __declspec(dllimport) __declspec(nothrow) __forceinline _String_base<char, allocator<char> >::~_String_base() { _M_deallocate_block(); } }
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Instantiate only the rowed long-double overload. Whole-class instantiation
// also emitted a constructor and vtable referencing the separate string parser.
template _STL::istreambuf_iterator<char, _STL::char_traits<char> >
_STL::money_get<char, _STL::istreambuf_iterator<char, _STL::char_traits<char> > >::do_get(
    _STL::istreambuf_iterator<char, _STL::char_traits<char> >,
    _STL::istreambuf_iterator<char, _STL::char_traits<char> >,
    bool, _STL::ios_base &, int &, long double &) const;
