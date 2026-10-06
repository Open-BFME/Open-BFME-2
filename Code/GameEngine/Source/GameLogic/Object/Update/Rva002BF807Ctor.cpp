// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva002BF807@@QAE@XZ, retail 0x002BF807, 58 bytes.
// Default ctor of the 44B member payload inside PartTheHeavensUpdateModuleData
// (three instances at +0x10/+0x3C/+0x68 per the rowed dtor 0x004ACCCD;
// blocked ModuleData ctor 0x004ACBF8 needs this pin). Layout: ints at +0/+4
// (0), BfmeE16 vector at +8 via the folded Vector_base 0x00211E58 with an
// explicit allocator temp (frameless lea esp+7), unused int at +0x14,
// BfmeE16* at +0x18 caching m_vec.end(), floats at +0x1c/+0x20/+0x24/+0x28
// (0.0f). Shape follows W3DStreakDrawModuleDataCtor2 (explicit allocator,
// body float stores after the vector call).
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva002BF807
{
public:
	Rva002BF807();

private:
	int m_00;
	int m_04;
	_STL::vector<BfmeE16> m_vec;
	int m_unused14;
	BfmeE16 *m_end18;
	float m_1c;
	float m_20;
	float m_24;
	float m_28;
};

Rva002BF807::Rva002BF807()
	: m_00(0),
	  m_04(0),
	  m_vec(_STL::allocator<BfmeE16>()),
	  m_end18(m_vec.end())
{
	m_28 = 0.0f;
	m_24 = 0.0f;
	m_20 = 0.0f;
	m_1c = 0.0f;
}
