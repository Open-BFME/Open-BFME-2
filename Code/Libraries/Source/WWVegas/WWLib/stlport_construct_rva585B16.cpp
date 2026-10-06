// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ??$_Construct@VRva00585B16@@V1@@_STL@@YAXPAVRva00585B16@@ABV1@@Z @0x005859C6 45B.
// Null-guarded placement copy over the 0x54-byte element whose real copy ctor
// is the rowed ??0Rva00585B16@@QAE@ABV0@@Z at 0x0058596B.
// Same 45B shape as the rowed _Construct<AsciiString> at 0x0002C485 and the
// Pod88 precedent at 0x004E3706. Callers are uninitialized_copy/fill loops
// at 0x005859F3 0x00585CE0 0x00586C56.
#include <memory>

class Rva00585B16 {
public:
	Rva00585B16(const Rva00585B16 &other);
private:
	char m_body[0x54];
};

template void _STL::_Construct<Rva00585B16, Rva00585B16>(Rva00585B16 *, const Rva00585B16 &);
