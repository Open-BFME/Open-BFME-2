// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@VRva0040AF66@@V?$allocator@VRva0040AF66@@@_STL@@@_STL@@IAEXPAVRva0040AF66@@ABV3@ABU__false_type@2@I_N@Z @ 0x0040B8E8 (183B). Vector fill insert overflow.
// Evidence: same shape as rowed 0x0040B834 calling rowed copy 0x0040B1CD construct 0x0040B17B fill 0x0040B1F3 clear 0x0040B5FC allocate 0x0040A673; stride 0x68; caller 0x0040BA6A.
// Finish from stash reverse/attempts/0x0040b8e8.cpp (0.95): private AsciiString replaced by the shared header (same 4B size; element copy is declared-only so no code change).
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

#include "ascii_string.h"
#include <vector>

enum ScienceType
{
	SCIENCE_NONE = 0
};

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);
private:
	char m_pad[0x1C];
};

class Rva0040AF66
{
public:
	Rva0040AF66(const Rva0040AF66 &other);
	Rva0040AF66 &operator=(const Rva0040AF66 &other);
private:
	int m_00;
	_STL::vector<ScienceType> m_04;
	_STL::vector<ScienceType> m_10;
	BfmeFixedStorage0004543D m_1C;
	BfmeFixedStorage0004543D m_38;
	AsciiString m_54;
	AsciiString m_58;
	int m_5C;
	int m_60;
	unsigned char m_64;
};

namespace _STL
{
template <> void _Construct<Rva0040AF66, Rva0040AF66>(Rva0040AF66 *, const Rva0040AF66 &);
}

template void _STL::vector<Rva0040AF66>::_M_insert_overflow(
	Rva0040AF66 *,
	const Rva0040AF66 &,
	const _STL::__false_type &,
	unsigned int,
	bool);
