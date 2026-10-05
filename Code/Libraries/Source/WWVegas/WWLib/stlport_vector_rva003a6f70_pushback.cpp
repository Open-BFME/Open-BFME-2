// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@VRva003A6F70@@V?$allocator@VRva003A6F70@@@_STL@@@_STL@@QAEXABVRva003A6F70@@@Z,
// retail 0x0056633A, 55 bytes. STLport 4.5.3 vector<Rva003A6F70>::push_back,
// sibling of the Pod40 push_back at 0x00566295 (55B, same flags). Fast path
// constructs via the rowed _Construct at 0x0052BD04; full path calls the
// rowed _M_insert_overflow at 0x00565DA2 with n=1 fill=1. Caller at
// 0x0056654A; prev Pod40 push_back plus next Rva0056644E overflow same shape.
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

class Rva003A6F70
{
public:
	virtual ~Rva003A6F70();
	int a[7];
};
inline bool operator==(const Rva003A6F70 &x, const Rva003A6F70 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const Rva003A6F70 &x, const Rva003A6F70 &y) { return x.a[0] < y.a[0]; }

namespace _STL
{
template <> void _Construct<Rva003A6F70, Rva003A6F70>(Rva003A6F70 *, const Rva003A6F70 &);
}

template void _STL::vector<Rva003A6F70>::push_back(const Rva003A6F70 &);
