// cl: /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@VRva0052BDE6@@V?$allocator@VRva0052BDE6@@@_STL@@@_STL@@IAEXPAVRva0052BDE6@@ABV3@ABU__false_type@2@I_N@Z,
// retail 0x00565C34, 183 bytes. STLport 4.5.3 vector<Rva0052BDE6>::_M_insert_overflow,
// false_type growth path sibling of the Pod40 overflow at 0x00565B7D (183B, same
// TU flags) and Rva003A6F70 overflow at 0x00565DA2. Element is 12 bytes with a
// virtual dtor so _M_clear stays out-of-line (30B tidy at 0x004EE540 via pin);
// _Construct at 0x0052C34D and fill_n at 0x00565643 are rowed. Allocate at
// 0x00395928 and uninitialized_copy at 0x0052C93B (4-push call sites 0x00565C75
// 0x00565CC0, body ignores tag) resolve via ICF-twin pins. Caller at 0x005662F9;
// landing unblocks 0x005662CC.
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

template void _STL::vector<Rva0052BDE6>::_M_insert_overflow(
	Rva0052BDE6 *,
	const Rva0052BDE6 &,
	const _STL::__false_type &,
	unsigned int,
	bool);
