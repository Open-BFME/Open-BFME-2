// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@VRva004E32F2@@V?$allocator@VRva004E32F2@@@_STL@@@_STL@@QAEXABVRva004E32F2@@@Z, retail 0x00566BB4, 55 bytes.
// STLport 4.5.3 vector<Rva004E32F2>::push_back.
// Evidence: chain lane calls just-landed _M_insert_overflow 0x00566ACA plus rowed _Construct 0x0052D4A2; same 55B shape as rowed 0x005662CC.
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

#include <vector>

class Rva004E32F2
{
public:
	Rva004E32F2(const Rva004E32F2 &o);
	virtual ~Rva004E32F2();
private:
	char m_pad[0x14];
};

namespace _STL
{
template <> void _Construct<Rva004E32F2, Rva004E32F2>(Rva004E32F2 *, const Rva004E32F2 &);
}

template void _STL::vector<Rva004E32F2>::push_back(const Rva004E32F2 &);
