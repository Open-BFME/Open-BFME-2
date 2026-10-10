// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

// STLport 4.5.3 narrow basic_stringbuf members that retail compiled with /O1
// (EBP frames, uninlined push_back): overflow (0x1F95C4) and setbuf
// (0x1F9889). Sibling TU stlport_narrow_ostringstream.cpp keeps the base flags.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <sstream>

template class _STL::basic_stringbuf<char, _STL::char_traits<char>, _STL::allocator<char> >;
