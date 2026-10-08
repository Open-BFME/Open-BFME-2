// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <locale>
// The complete retail scanner at 0x0000A0F0 supplies the native wide
// iterator and locale behavior; keep the generic header copy out of this unit.
namespace _STL {
template <> int _M_get_base_or_zero<istreambuf_iterator<wchar_t, char_traits<wchar_t> >, wchar_t>(
    istreambuf_iterator<wchar_t, char_traits<wchar_t> > &,
    istreambuf_iterator<wchar_t, char_traits<wchar_t> > &, ios_base &, wchar_t *);
}

template class _STL::num_get<wchar_t, _STL::istreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> > >;
