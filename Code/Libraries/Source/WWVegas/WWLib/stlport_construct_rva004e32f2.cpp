// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??$_Construct@VRva004E32F2@@V1@@_STL@@YAXPAVRva004E32F2@@ABV1@@Z, retail 0x0052D4A2, 45 bytes.
// _STL::_Construct<Rva004E32F2,Rva004E32F2> null-guarded placement-new copy
// over a single element via the rowed copy ctor at 0x0052D477.
// Evidence: chain lane calls just-landed 0x0052D477; same 45B EH shape as
// rowed _Construct<AsciiString> at 0x0002C485; callers 0x0052D4DD 0x00566A88 0x00566B20 0x00566BC6.
#include <memory>

class Rva004E32F2
{
public:
	Rva004E32F2(const Rva004E32F2 &other);
};

template void _STL::_Construct<Rva004E32F2, Rva004E32F2>(Rva004E32F2 *, const Rva004E32F2 &);
