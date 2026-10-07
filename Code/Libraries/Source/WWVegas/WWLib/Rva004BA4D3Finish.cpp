// ?_M_insert_overflow@?$vector@VRva004BA1D0@@V?$allocator@VRva004BA1D0@@@_STL@@@_STL@@IAEXPAVRva004BA1D0@@ABV3@ABU__false_type@2@I_N@Z
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@VRva004BA1D0@@V?$allocator@VRva004BA1D0@@@_STL@@@_STL@@IAEXPAVRva004BA1D0@@ABV3@ABU__false_type@3@I_N@Z,
// retail 0x004BA4D3, 183 bytes. Dedicated TU.
//
// STLport 4.5.3 vector<Rva004BA1D0>::_M_insert_overflow, the growth path of
// the push_back at 0x004BA7E0 (55B, fast Construct plus this slow path).
// Sits between TransitionDamageFX dtor 0x004BA47C and ModuleData ctor.
// Byte-identical shape to the PrereqUnitRec overflow at 0x004F5165 (183B,
// same /G7 /arch:SSE + bfmealloc recipe) and the string-record overflows.
// Retail calls allocate 0x0007E364, copy 0x004BA246, _Construct 0x004BA219,
// fill_n 0x004BA26C and _M_clear 0x004BA3CC, all rowed. Explicit member (not
// whole-class) instantiation keeps push_back owned by its own TU. The value
// type carries a vector<AsciiString> at +4, so its dtor is non-trivial and
// _M_clear is emitted out-of-line exactly as retail's call shows.
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

template void _STL::vector<Rva004BA1D0>::_M_insert_overflow(
    Rva004BA1D0 *, const Rva004BA1D0 &, const _STL::__false_type &, unsigned int, bool);
