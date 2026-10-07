// ?push_back@?$vector@VRva004BA1D0@@V?$allocator@VRva004BA1D0@@@_STL@@@_STL@@QAEXABVRva004BA1D0@@@Z
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?push_back@?$vector@VRva004BA1D0@@V?$allocator@VRva004BA1D0@@@_STL@@@_STL@@QAEXABVRva004BA1D0@@@Z @0x004BA7E0 55B
// Evidence: vector<Rva004BA1D0> push_back fast Construct plus _M_insert_overflow growth path; callees rowed _Construct 0x004BA219 and _M_insert_overflow 0x004BA4D3; element 44B with vector<AsciiString> at +4 per overflow TU Rva004BA4D3Finish.cpp; callers 0x004BA817 and 0x004BA9E4; sits between TransitionDamageFX dtor 0x004BA7C4 and ReflectDamageModuleData buildFieldParse 0x004BAB25.
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

#include "ascii_string.h"

class Rva004BA1D0
{
public:
	Rva004BA1D0(const Rva004BA1D0 &other);
private:
	int m_00;
	_STL::vector<AsciiString> m_04;
	unsigned int m_10;
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1C;
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
};

namespace _STL
{
template <> void _Construct<Rva004BA1D0, Rva004BA1D0>(Rva004BA1D0 *, const Rva004BA1D0 &);
}

template void _STL::vector<Rva004BA1D0>::push_back(const Rva004BA1D0 &);
