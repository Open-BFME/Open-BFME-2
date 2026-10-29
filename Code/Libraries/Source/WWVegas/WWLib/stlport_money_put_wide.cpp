// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46
// Retain only this unit's three owned helper instantiations. The full
// money_put class also emitted a competing do_put implementation and
// unrelated string constructors/destructors; their verified owners provide
// those bodies independently.
#include <locale>
namespace _STL {
typedef ostreambuf_iterator<wchar_t, char_traits<wchar_t> > WideOut;
template WideOut fill_n<WideOut, unsigned int, wchar_t>(WideOut, unsigned int, const wchar_t &);
template const moneypunct<wchar_t, false> &use_facet<moneypunct<wchar_t, false> >(const locale &);
template const moneypunct<wchar_t, true> &use_facet<moneypunct<wchar_t, true> >(const locale &);
}
