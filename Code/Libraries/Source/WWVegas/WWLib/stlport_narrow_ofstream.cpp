// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>

// The exact default constructor is owned by the verified dedicated unit.
// This whole-class instantiation emitted a non-retail copy; defer to that owner.
template <>
_STL::basic_ofstream<char, _STL::char_traits<char> >::basic_ofstream();

// Filename and descriptor constructors likewise defer to their exact owners.
template <>
_STL::basic_ofstream<char, _STL::char_traits<char> >::basic_ofstream(int, _STL::ios_base::openmode);
template <>
_STL::basic_ofstream<char, _STL::char_traits<char> >::basic_ofstream(const char *, _STL::ios_base::openmode, long);
template <>
_STL::basic_ofstream<char, _STL::char_traits<char> >::basic_ofstream(const char *, _STL::ios_base::openmode);

template class _STL::basic_ofstream<char, _STL::char_traits<char> >;
