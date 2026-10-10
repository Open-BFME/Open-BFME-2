// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

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

template class _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> >;
