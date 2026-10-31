// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@VRva0052BDE6@@V?$allocator@VRva0052BDE6@@@_STL@@@_STL@@QAEXABVRva0052BDE6@@@Z,
// retail 0x005662CC, 55 bytes. STLport 4.5.3 vector<Rva0052BDE6>::push_back,
// sibling of the Rva003A6F70 push_back at 0x0056633A (55B, same flags) and
// Pod40 push_back at 0x00566295. Fast path constructs via the rowed
// _Construct at 0x0052C34D; full path calls the rowed _M_insert_overflow at
// 0x00565C34 with n=1 fill=1. Caller jumps at 0x0056653A.
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

class Rva0052BDE6
{
public:
	virtual ~Rva0052BDE6();
	int a[2];
};
inline bool operator==(const Rva0052BDE6 &x, const Rva0052BDE6 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const Rva0052BDE6 &x, const Rva0052BDE6 &y) { return x.a[0] < y.a[0]; }

namespace _STL
{
template <> void _Construct<Rva0052BDE6, Rva0052BDE6>(Rva0052BDE6 *, const Rva0052BDE6 &);
}

template void _STL::vector<Rva0052BDE6>::push_back(const Rva0052BDE6 &);
