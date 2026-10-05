// ??0Rva000F9C3C@@QAE@XZ
// partial score=0.93 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva000F9C3C@@QAE@XZ @0x000F9C3C 97B ctor stores vtable 0x00BCF270 zeroes members constructs two BfmeE16 vectors
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva000F9C3C {
public:
	virtual ~Rva000F9C3C();
	Rva000F9C3C();
	int m04, m08, m0C, m10, m14, m18, m1C;
	float f20, f24, f28;
	_STL::vector<BfmeE16> v2C;
	_STL::vector<BfmeE16> v38;
	int m44, m48, m4C, m50;
};
// ??0Rva000F9C3C@@QAE@XZ present-unmatched
Rva000F9C3C::Rva000F9C3C() : m04(0), m08(0), m0C(0), m10(0), m14(0), m18(0), m1C(0), f20(0.0f), f24(0.0f), f28(0.0f), m44(0), m48(0), m4C(0), m50(0) {}
