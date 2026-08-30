// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <iterator>

template class _STL::ostreambuf_iterator<char, _STL::char_traits<char> >;
template class _STL::ostreambuf_iterator<wchar_t, _STL::char_traits<wchar_t> >;
