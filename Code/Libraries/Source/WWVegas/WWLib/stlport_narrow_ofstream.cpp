// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <fstream>
namespace _STL {
template<> basic_filebuf<char,char_traits<char> >::pos_type basic_filebuf<char,char_traits<char> >::seekpos(pos_type,ios_base::openmode);
template<> basic_filebuf<char,char_traits<char> >::pos_type basic_filebuf<char,char_traits<char> >::seekoff(streamoff,ios_base::seekdir,ios_base::openmode);
template<> fpos<int> basic_filebuf<char,char_traits<char> >::_M_seek_return(long,int);
template<> int basic_filebuf<char,char_traits<char> >::overflow(int);
}

// bfme link decl-only begin
namespace _STL { template <> basic_filebuf<char, char_traits<char> > * basic_filebuf<char, char_traits<char> >::open(char const *, int); }
// bfme link decl-only end

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
