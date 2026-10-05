// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00558D56@@QAE@XZ @0x00558D56 21B: Default ctor wraps DequeBase E16 with temp allocator plus 0 then returns this. Evidence: unlock lane calls rowed DequeBase 0x0055334A plus caller 0x00558F07 plus push0 lea-b shape.
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
struct BfmeE16 { float x, y, z, w; };
class Rva00558D56
{
	_STL::_Deque_base<BfmeE16, _STL::allocator<BfmeE16> > m_base;
public:
	Rva00558D56();
};
Rva00558D56::Rva00558D56() : m_base(_STL::allocator<BfmeE16>(), 0)
{
}
