// cl: /G7 /arch:SSE /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@VRva0040AEE3@@V?$allocator@VRva0040AEE3@@@_STL@@@_STL@@IAEXPAVRva0040AEE3@@ABV3@ABU__false_type@2@I_N@Z @ 0x0040B834 (180B). Vector fill insert overflow.
// Evidence: calls rowed Construct 0x0040B14E Fill 0x0040B1A8 destroy 0x0040B5DE allocate 0x002226BE copy 0x0040B2FD; caller 0x0040BA60 pushback path; vector start/finish/end at +0/+4/+8 stride 0x10.
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

#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

class Rva0040AEE3
{
public:
	Rva0040AEE3(const Rva0040AEE3 &other);
	Rva0040AEE3 &operator=(const Rva0040AEE3 &other);
private:
	_STL::vector<ScienceType> m_0000;
	int m_000C;
};

namespace _STL
{
template <> void _Construct<Rva0040AEE3, Rva0040AEE3>(Rva0040AEE3 *, const Rva0040AEE3 &);
}

template void _STL::vector<Rva0040AEE3>::_M_insert_overflow(
	Rva0040AEE3 *,
	const Rva0040AEE3 &,
	const _STL::__false_type &,
	unsigned int,
	bool);
