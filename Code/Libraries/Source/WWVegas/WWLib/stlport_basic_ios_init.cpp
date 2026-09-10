// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Dedicated TU for basic_ios<char>::init. The retail body uses the generic
// ctype<char>::widen virtual rather than STLport's char widening
// specialization. Do not edit stlport_narrow_fstream.cpp.

#define _STLP_NO_METHOD_SPECIALIZATION
#include <istream>
#include <ostream>

template class _STL::basic_istream<char, _STL::char_traits<char> >;
template class _STL::basic_istream<wchar_t, _STL::char_traits<wchar_t> >;
template class _STL::basic_ostream<char, _STL::char_traits<char> >;
template class _STL::basic_ostream<wchar_t, _STL::char_traits<wchar_t> >;
