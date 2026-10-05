// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BFME2's 24-byte Rva000BB4AC vector allocation/copy helper: base Rva000B9074
// (0x14) plus refcounted pointer tail, stride 0x18. Copy ctor is rowed at
// 0x000BB4AC and _Construct at 0x000BB9C0; vector instantiation emits the
// __uninitialized callers (0x000BBB12 0x000BBB38 and siblings).
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

class Rva000BB4AC
{
public:
	Rva000BB4AC();
	Rva000BB4AC(const Rva000BB4AC &o);
private:
	char m_pad[0x18];
};
#include <vector>
template class _STL::vector<Rva000BB4AC, _STL::allocator<Rva000BB4AC> >;
