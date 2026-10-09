// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>

// The exact default constructor is owned by the verified dedicated unit.
// This whole-class instantiation emitted a non-retail copy; defer to that owner.
template <>
_STL::basic_ifstream<char, _STL::char_traits<char> >::basic_ifstream();

// Filename and descriptor constructors likewise defer to their exact owners.
template <>
_STL::basic_ifstream<char, _STL::char_traits<char> >::basic_ifstream(int, _STL::ios_base::openmode);
template <>
_STL::basic_ifstream<char, _STL::char_traits<char> >::basic_ifstream(const char *, _STL::ios_base::openmode, long);

template class _STL::basic_ifstream<char, _STL::char_traits<char> >;
