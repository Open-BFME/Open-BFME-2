// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

// ~basic_string<unsigned short> binds to the rowed retail 63B copy (0x0000B3C0): this
// unit's own copy is not retail's and comes before it in link order.
#include <string>
template <> _STL::basic_string<unsigned short, _STL::char_traits<unsigned short>, _STL::allocator<unsigned short> >::~basic_string();
#include <locale>
// STLport defines locale::facet::~facet out of line in locale_impl.cpp, where
// retail's ??_Gfacet (0x00007490) inlines the empty body; seeing it here makes
// this unit's select-any copy of ??_Gfacet retail's.
namespace _STL { inline locale::facet::~facet() {} }
// The complete native float scanners are owned by the read_float units
// (F850 narrow;10420 wide). Keep this unit's generic copies out of the link.
namespace _STL {
template <> bool _M_read_float<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, wchar_t>(
    string &, istreambuf_iterator<wchar_t, char_traits<wchar_t> > &,
    istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, ios_base &, wchar_t *);
}
// basic_string<char>::reserve is retail's 116-byte body at 0x0000C390, owned by
// stlport_narrow_string_reserve.cpp; this unit's header copy is not retail's and
// came before it in link order, so only declare its instantiation here.
namespace _STL { template <> void basic_string<char, char_traits<char>, allocator<char> >::reserve(unsigned int); }
// The wide __get_integer<unsigned short/long/unsigned long> instances are rowed at
// 0x0000AFA0 and its siblings and emitted by stlport_wide_get_integer_{uint16,long,
// ulong}.cpp; declaring their instantiations keeps this unit's own copies, which
// came first in link order, out of the link. With them declared, this unit's
// _M_do_get_integer<wchar_t,G/J/K> copies come out as retail's bodies.
namespace _STL {
extern template bool __get_integer<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, unsigned short>(istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, int, unsigned short &, int, bool, char, const string &, const __false_type &);
extern template bool __get_integer<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, long>(istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, int, long &, int, bool, char, const string &, const __true_type &);
extern template bool __get_integer<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, unsigned long>(istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, int, unsigned long &, int, bool, char, const string &, const __false_type &);
}
// The complete retail scanner at 0x0000A0F0 supplies the native wide
// iterator and locale behavior; keep the generic header copy out of this unit.
namespace _STL {
template <> int _M_get_base_or_zero<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, wchar_t>(
    istreambuf_iterator<wchar_t, char_traits<wchar_t> > &,
    istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, ios_base &, wchar_t *);
}

// Suppress this TU's non-retail _String_base<char> dtor copy (family2-LK3 rows
// 22/26): the rowed 63B copy in stlport_narrow_string_base_dtor.cpp serves the link.
template <> _STL::_String_base<char, _STL::allocator<char> >::~_String_base();
// Likewise the wide one: the rowed 63B fold in that unit serves the link.
template <> _STL::_String_base<unsigned short, _STL::allocator<unsigned short> >::~_String_base();
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> istreambuf_iterator<unsigned short, char_traits<unsigned short> > num_get<unsigned short, istreambuf_iterator<unsigned short, char_traits<unsigned short> > >::do_get(istreambuf_iterator<unsigned short, char_traits<unsigned short> >, istreambuf_iterator<unsigned short, char_traits<unsigned short> >, ios_base &, int &, float &) const; }
namespace _STL { template <> istreambuf_iterator<unsigned short, char_traits<unsigned short> > num_get<unsigned short, istreambuf_iterator<unsigned short, char_traits<unsigned short> > >::do_get(istreambuf_iterator<unsigned short, char_traits<unsigned short> >, istreambuf_iterator<unsigned short, char_traits<unsigned short> >, ios_base &, int &, double &) const; }
namespace _STL { template <> istreambuf_iterator<unsigned short, char_traits<unsigned short> > num_get<unsigned short, istreambuf_iterator<unsigned short, char_traits<unsigned short> > >::do_get(istreambuf_iterator<unsigned short, char_traits<unsigned short> >, istreambuf_iterator<unsigned short, char_traits<unsigned short> >, ios_base &, int &, long double &) const; }
// do_get(bool &) is rowed in stlport_wide_num_get_bool.cpp (0x0000B140).
namespace _STL { template <> istreambuf_iterator<unsigned short, char_traits<unsigned short> > num_get<unsigned short, istreambuf_iterator<unsigned short, char_traits<unsigned short> > >::do_get(istreambuf_iterator<unsigned short, char_traits<unsigned short> >, istreambuf_iterator<unsigned short, char_traits<unsigned short> >, ios_base &, int &, bool &) const; }
namespace _STL { template <> bool __get_integer<istreambuf_iterator<unsigned short, char_traits<unsigned short> >, __int64>(istreambuf_iterator<unsigned short, char_traits<unsigned short> > &, istreambuf_iterator<unsigned short, char_traits<unsigned short> > &, int, __int64 &, int, bool, char, basic_string<char, char_traits<char>, allocator<char> > const &, __true_type const &); }
namespace _STL { template <> bool __get_integer<istreambuf_iterator<unsigned short, char_traits<unsigned short> >, unsigned __int64>(istreambuf_iterator<unsigned short, char_traits<unsigned short> > &, istreambuf_iterator<unsigned short, char_traits<unsigned short> > &, int, unsigned __int64 &, int, bool, char, basic_string<char, char_traits<char>, allocator<char> > const &, __false_type const &); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@GV?$allocator@G@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<unsigned short, allocator<unsigned short> >::_M_deallocate_block(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@G@_STL@@QBEXPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<unsigned short>::deallocate(unsigned short *, size_t); }
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
// The uint reader shares the separately compiled scanner and wrapper.
namespace _STL {
template <> bool __get_integer<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, unsigned int>(istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, int, unsigned int &, int, bool, char, const string &, const __false_type &);
template <> istreambuf_iterator<wchar_t, char_traits<wchar_t> > _M_do_get_integer<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, unsigned int, wchar_t>(istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, ios_base &, int &, unsigned int &, wchar_t *);
}
template class _STL::num_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
// Native 18050..1805F: the out-of-line use_facet<ctype<wchar_t> > (push
// ctype<wchar_t>::id VA 0x00DA6200, locale::_M_use_facet), an orphan .text
// hole beside this unit's size() copy at 0x00018040.
template const _STL::ctype<wchar_t> &_STL::use_facet<_STL::ctype<wchar_t> >(const _STL::locale &);

// Retain the rowed iterator helpers formerly emitted by the generic uint scanner.
template void _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >::_M_bumpc();
template wchar_t _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >::operator*() const;
template _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > &_STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >::operator++();
template bool _STL::operator!=<wchar_t, _STL::char_traits<wchar_t> >(const _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > &, const _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > &);
