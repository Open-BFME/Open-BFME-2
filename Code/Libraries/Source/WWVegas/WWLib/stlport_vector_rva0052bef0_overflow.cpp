// cl: /G7 /arch:SSE /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@VRva0052BEF0@@V?$allocator@VRva0052BEF0@@@_STL@@@_STL@@IAEXPAVRva0052BEF0@@ABV3@ABU__false_type@2@I_N@Z,
// retail 0x00566078, 183 bytes. STLport 4.5.3 vector<Rva0052BEF0>::_M_insert_overflow,
// false_type growth path. Element is 0xC bytes with rowed copy ctor at 0x0052BEF0;
// _Construct at 0x0052C431 and fill_n at 0x00565770 and uninit copy at 0x0052C9D3
// and clear at 0x004EE540. Caller at 0x00566444; unblocks 0x00566417.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#define _STLP_NO_EXCEPTIONS 1
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

template void _STL::vector<Rva0052BEF0>::_M_insert_overflow(
	Rva0052BEF0 *,
	const Rva0052BEF0 &,
	const _STL::__false_type &,
	unsigned int,
	bool);
