// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 24-byte Rva000BB491 vector allocation/copy helper: base Rva000B9074
// (0x14) plus int tail, stride 0x18. Copy ctor is rowed at 0x000BB491 and
// _Construct at 0x000BB993; vector instantiation emits the __uninitialized
// callers (0x000BBAC7 0x000BBAED and siblings).
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

class Rva000BB491
{
public:
	Rva000BB491();
	Rva000BB491(const Rva000BB491 &o);
private:
	char m_pad[0x18];
};
#include <vector>
template class _STL::vector<Rva000BB491, _STL::allocator<Rva000BB491> >;
