// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@VRva0052BEF0@@V?$allocator@VRva0052BEF0@@@_STL@@@_STL@@QAEXABVRva0052BEF0@@@Z,
// retail 0x00566417, 55 bytes. STLport 4.5.3 vector<Rva0052BEF0>::push_back,
// sibling of the Rva003A6F70 push_back at 0x0056633A (55B same flags). Fast path
// constructs via the rowed _Construct at 0x0052C431; full path calls the
// rowed _M_insert_overflow at 0x00566078 with n=1 fill=1. Chain from 0x00566078.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class Rva0052BEF0
{
public:
	virtual ~Rva0052BEF0();
	Rva0052BEF0(const Rva0052BEF0 &other);
	int a[2];
};
inline bool operator==(const Rva0052BEF0 &x, const Rva0052BEF0 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const Rva0052BEF0 &x, const Rva0052BEF0 &y) { return x.a[0] < y.a[0]; }

namespace _STL
{
template <> void _Construct<Rva0052BEF0, Rva0052BEF0>(Rva0052BEF0 *, const Rva0052BEF0 &);
}

template void _STL::vector<Rva0052BEF0>::push_back(const Rva0052BEF0 &);
