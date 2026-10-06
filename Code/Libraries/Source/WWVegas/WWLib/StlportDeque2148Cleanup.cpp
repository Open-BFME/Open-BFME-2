// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 view of the target iterator stride; original element name and
// fields are unknown. Verified operations cover iteration, growth and cleanup.
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

#include <deque>
struct BfmeOpaque2148 { unsigned char bytes[0x864]; };
template class _STL::deque<BfmeOpaque2148, _STL::allocator<BfmeOpaque2148> >;
template _STL::_Deque_iterator<BfmeOpaque2148, _STL::_Nonconst_traits<BfmeOpaque2148> > &
_STL::_Deque_iterator<BfmeOpaque2148, _STL::_Nonconst_traits<BfmeOpaque2148> >::operator++();

