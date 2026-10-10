// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <locale>
// basic_string<char>::reserve is retail's 116-byte body at 0x0000C390, owned by
// stlport_narrow_string_reserve.cpp; this unit's header copy is not retail's and
// came before it in link order, so only declare its instantiation here.
namespace _STL { extern template void basic_string<char, char_traits<char>, allocator<char> >::reserve(size_t); }
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

template class _STL::num_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
