// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva001B4FB8@@QAE@XZ RVA 0x001B4FB8 49B
// Evidence: leaf lane; ctor initializing three vector<BfmeE16> at +0/+0xC/+0x18
//   via rowed 0x00211E58 Vector_base then clearing dword at +0x24; returns this;
//   caller 0x0022E356 in FUN_0062e2e4.
#include <vector>

struct BfmeE16
{
	float x, y, z, w;
};

class Rva001B4FB8
{
public:
	Rva001B4FB8();

private:
	_STL::vector<BfmeE16> m_v0; // +0
	_STL::vector<BfmeE16> m_v1; // +0xC
	_STL::vector<BfmeE16> m_v2; // +0x18
	int m_24; // +0x24
};

Rva001B4FB8::Rva001B4FB8()
{
	m_24 = 0;
}
