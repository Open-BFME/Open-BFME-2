// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 narrow istreambuf_iterator instantiation. The retail library
// emits the class members out of line, so the explicit instantiation below is
// what produces them.

#include <iterator>

template class _STL::istreambuf_iterator<char, _STL::char_traits<char> >;
