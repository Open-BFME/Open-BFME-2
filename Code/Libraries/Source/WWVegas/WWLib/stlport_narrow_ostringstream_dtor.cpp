// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <sstream>

template class _STL::basic_ostringstream<char, _STL::char_traits<char>, _STL::allocator<char> >;
