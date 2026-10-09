// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>

// Native allocation owner 0x00013F10 (189 bytes) supplies this helper.
// BFME 1 FilebufInstantiations at f98983a7d3 likewise defers allocation.
// The generic emitted copy differs from the complete retail body.
namespace _STL {
template <> bool basic_filebuf<char, char_traits<char> >::_M_allocate_buffers(char *, streamsize);
}


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
