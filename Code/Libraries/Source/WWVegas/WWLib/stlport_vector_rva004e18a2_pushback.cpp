// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@VRva004E18A2@@V?$allocator@VRva004E18A2@@@_STL@@@_STL@@QAEXABVRva004E18A2@@@Z,
// retail 0x005663A8, 55 bytes. STLport 4.5.3 vector<Rva004E18A2>::push_back,
// sibling of the Rva004E194E push_back at 0x00566371 (55B same flags). Fast path
// constructs via the rowed _Construct at 0x0052BD16; full path calls the
// rowed _M_insert_overflow at 0x00565F0D with n=1 fill=1. Chain from 0x00565F0D.
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

class Rva004E18A2
{
public:
	virtual ~Rva004E18A2();
	Rva004E18A2(const Rva004E18A2 &other);
	int a[3];
};
inline bool operator==(const Rva004E18A2 &x, const Rva004E18A2 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const Rva004E18A2 &x, const Rva004E18A2 &y) { return x.a[0] < y.a[0]; }

namespace _STL
{
template <> void _Construct<Rva004E18A2, Rva004E18A2>(Rva004E18A2 *, const Rva004E18A2 &);
}

template void _STL::vector<Rva004E18A2>::push_back(const Rva004E18A2 &);
