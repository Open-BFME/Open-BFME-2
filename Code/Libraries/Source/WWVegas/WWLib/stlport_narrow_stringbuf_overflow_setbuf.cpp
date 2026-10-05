// cl: /EHsc /O1 /MD /D_STLP_USE_STATIC_LIB
// stlport

// STLport 4.5.3 narrow basic_stringbuf members that retail compiled with /O1
// (EBP frames, uninlined push_back): overflow (0x1F95C4) and setbuf
// (0x1F9889). Sibling TU stlport_narrow_ostringstream.cpp keeps the base flags.
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

template class _STL::basic_stringbuf<char, _STL::char_traits<char>, _STL::allocator<char> >;
