// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@VRva004E18A2@@V?$allocator@VRva004E18A2@@@_STL@@@_STL@@IAEXPAVRva004E18A2@@ABV3@ABU__false_type@2@I_N@Z,
// retail 0x00565F0D, 180 bytes. STLport 4.5.3 vector<Rva004E18A2>::_M_insert_overflow,
// false_type growth path. Element is 0x10 bytes with rowed copy ctor at 0x0052BB6D;
// _Construct at 0x0052BD16 and fill_n at 0x00565726 and uninit copy at 0x0052C2A4
// and clear at 0x00565A60. Caller at 0x005663D5; unblocks 0x005663A8.
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

template void _STL::vector<Rva004E18A2>::_M_insert_overflow(
	Rva004E18A2 *,
	const Rva004E18A2 &,
	const _STL::__false_type &,
	unsigned int,
	bool);
