// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@VRva004E194E@@V?$allocator@VRva004E194E@@@_STL@@@_STL@@IAEXPAVRva004E194E@@ABV3@ABU__false_type@2@I_N@Z,
// retail 0x00565E56, 183 bytes. STLport 4.5.3 vector<Rva004E194E>::_M_insert_overflow,
// false_type growth path. Element is 0x14 bytes with rowed copy ctor at 0x0052BE96;
// _Construct at 0x0052C3D7 and fill_n at 0x005656E4 and uninit copy at 0x0052C987
// and tidy at 0x00565A42. Caller at 0x0056639E; unblocks 0x00566371.
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

template void _STL::vector<Rva004E194E>::_M_insert_overflow(
	Rva004E194E *,
	const Rva004E194E &,
	const _STL::__false_type &,
	unsigned int,
	bool);
