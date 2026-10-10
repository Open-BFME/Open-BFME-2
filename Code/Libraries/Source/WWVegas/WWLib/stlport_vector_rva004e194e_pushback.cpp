// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@VRva004E194E@@V?$allocator@VRva004E194E@@@_STL@@@_STL@@QAEXABVRva004E194E@@@Z,
// retail 0x00566371, 55 bytes. STLport 4.5.3 vector<Rva004E194E>::push_back,
// sibling of the Rva0052BEF0 push_back at 0x00566417 (55B same flags). Fast path
// constructs via the rowed _Construct at 0x0052C3D7; full path calls the
// rowed _M_insert_overflow at 0x00565E56 with n=1 fill=1. Chain from 0x00565E56.
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

class Rva004E194E
{
public:
	virtual ~Rva004E194E();
	Rva004E194E(const Rva004E194E &other);
	int a[4];
};
inline bool operator==(const Rva004E194E &x, const Rva004E194E &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const Rva004E194E &x, const Rva004E194E &y) { return x.a[0] < y.a[0]; }

namespace _STL
{
template <> void _Construct<Rva004E194E, Rva004E194E>(Rva004E194E *, const Rva004E194E &);
}

template void _STL::vector<Rva004E194E>::push_back(const Rva004E194E &);
