// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport46

#include <fstream>
namespace _STL {
template<> basic_filebuf<char,char_traits<char> > *basic_filebuf<char,char_traits<char> >::open(const char*,ios_base::openmode);
}


// Native allocation owner 0x00013F10 (189 bytes) supplies this helper.
// BFME 1 FilebufInstantiations at f98983a7d3 likewise defers allocation.
// The generic emitted copy differs from the complete retail body.
namespace _STL {
template <> bool basic_filebuf<char, char_traits<char> >::_M_allocate_buffers(char *, streamsize);
}

// _M_seek_return calls the exact owner 0x00014430 out of line, as retail does.
namespace _STL {
template <> void basic_filebuf<char, char_traits<char> >::_M_exit_input_mode();
// close (0x000150B0) and overflow (0x00015AB0) defer to their exact owners.
template <> basic_filebuf<char, char_traits<char> > *basic_filebuf<char, char_traits<char> >::close();
template <> int basic_filebuf<char, char_traits<char> >::overflow(int);
}


// The exact default constructor is owned by the verified dedicated unit.
// This whole-class instantiation emitted a non-retail copy; defer to that owner.
template <>
_STL::basic_ifstream<char, _STL::char_traits<char> >::basic_ifstream();

// Filename and descriptor constructors likewise defer to their exact owners.
template <>
_STL::basic_ifstream<char, _STL::char_traits<char> >::basic_ifstream(int, _STL::ios_base::openmode);
template <>
_STL::basic_ifstream<char, _STL::char_traits<char> >::basic_ifstream(const char *, _STL::ios_base::openmode, long);

#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> > & basic_string<char, char_traits<char>, allocator<char> >::operator=(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> locale basic_ios<char, char_traits<char> >::imbue(locale const &); }
namespace _STL { template <> void basic_ios<char, char_traits<char> >::init(basic_streambuf<char, char_traits<char> > *); }
namespace _STL { template <> char basic_ios<char, char_traits<char> >::widen(char) const; }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void allocator<char>::deallocate(char*, size_t);
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *allocator<char>::allocate(size_t, const void*);
}
template class _STL::basic_ifstream<char, _STL::char_traits<char> >;
