// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??0?$vector@VRva004E32F2@@V?$allocator@VRva004E32F2@@@_STL@@@_STL@@QAE@ABV01@@Z, retail 0x0052D4F5, 96 bytes.
// _STL::vector<Rva004E32F2> copy ctor via Vector_base count plus rowed uninit-copy 0x0052D4CF.
// Evidence: chain lane calls just-landed 0x0052D4CF; count via idiv 0x18; same 96B shape as rowed 0x000BCE36.
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

class Rva004E32F2
{
public:
	Rva004E32F2();
	Rva004E32F2(const Rva004E32F2 &o);
private:
	char m_pad[0x18];
};
#include <vector>
template class _STL::vector<Rva004E32F2, _STL::allocator<Rva004E32F2> >;
