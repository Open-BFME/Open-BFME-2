// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>

// The exact default constructor is owned by the verified dedicated unit.
// This whole-class instantiation emitted a non-retail copy; defer to that owner.
template <>
_STL::basic_ofstream<char, _STL::char_traits<char> >::basic_ofstream();

template class _STL::basic_ofstream<char, _STL::char_traits<char> >;
