// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?push_back@?$vector@VRva0040AF66@@V?$allocator@VRva0040AF66@@@_STL@@@_STL@@QAEXABVRva0040AF66@@@Z @ 0x0040BA6A (55B). Vector push_back fast path via rowed _Construct 0x0040B17B else rowed _M_insert_overflow 0x0040B8E8.
// Evidence: chain lane calls 0x0040B8E8 just landed; retail cmp je Construct add 0x68 vs overflow with n=1; caller 0x0040BAE7; same 55B shape as sibling pushback 0x0040BA33.
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

template void _STL::vector<Rva0040AF66>::push_back(const Rva0040AF66 &);
