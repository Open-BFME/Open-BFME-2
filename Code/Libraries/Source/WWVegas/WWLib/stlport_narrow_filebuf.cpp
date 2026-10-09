// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>

// The verified narrow_ifstream owner supplies these native seek operations.
namespace _STL {
template <> bool basic_filebuf<char, char_traits<char> >::_M_seek_init(bool);
template <> basic_filebuf<char, char_traits<char> >::pos_type
basic_filebuf<char, char_traits<char> >::seekpos(pos_type, ios_base::openmode);
}


// STLport 4.5.3 src/fstream.cpp: the page size the mmap path rounds to,
// .data VA 0x00DA6CC8, retail initial value 4096.
size_t _STL::_Filebuf_base::_M_page_size = 4096;

template class _STL::basic_filebuf<char, _STL::char_traits<char> >;

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?_M_release_lock@NodeAllocMutex@_STL@@QAEXXZ=?_M_initialize@_STLP_mutex_base@_STL@@QAEXXZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Rva008947A0Elem@@QAE@XZ=?_M_initialize@_STLP_mutex_base@_STL@@QAEXXZ")
