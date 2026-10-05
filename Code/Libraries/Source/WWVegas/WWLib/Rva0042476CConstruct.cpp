// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??$_Construct@VRva0042476C@@V1@@_STL@@YAXPAVRva0042476C@@ABV1@@Z @0x00424BF4 45B
// Null-guarded placement-new copy over Rva0042476C (two vectors at +0 and +0xC from Rva0042476C.cpp). Evidence: calls rowed copy ctor 0x0042476C; caller 0x00424D9F in 0x00424D8C with 0x18 stride; neighbours same dir and flags.
#include <memory>

class Rva0042476C
{
public:
	Rva0042476C(const Rva0042476C &that);
	~Rva0042476C();
};

template void _STL::_Construct(Rva0042476C *, const Rva0042476C &);
