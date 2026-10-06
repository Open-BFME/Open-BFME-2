// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??$_Construct@VRva001ED03C@@V1@@_STL@@YAXPAVRva001ED03C@@ABV1@@Z @0x001ED1F1 45B.
// Null-guarded placement copy over the 0x24-byte element whose real copy ctor
// is the rowed ??0Rva001ED03C@@QAE@ABV0@@Z at 0x001ED03C.
// Same 45B shape as the rowed _Construct<AsciiString> at 0x0002C485 and the
// Rva00585B16 precedent at 0x005859C6. Callers at 0x001ED22C 0x001ED257 0x001ED4CC 0x001ED55B.
#include <memory>

class Rva001ED03C
{
public:
	Rva001ED03C(const Rva001ED03C &other);
private:
	char m_body[0x24];
};

template void _STL::_Construct<Rva001ED03C, Rva001ED03C>(Rva001ED03C *, const Rva001ED03C &);
