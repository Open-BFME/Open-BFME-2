// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004BA1B2@@QAE@XZ, retail 0x004BA1B2 22B: default ctor constructs Vector_base<BfmeE16> at +4 via rowed 0x00211E58.
// Evidence: callees all rowed; callers at 0x004972BE 0x004BA82A 0x004C793A; BfmeE16 is the 16B stand-in from stlport_vector_e16_o1.
#include <vector>

struct BfmeE16 { float x, y, z, w; };

class Rva004BA1B2 {
public:
	Rva004BA1B2();
private:
	int m_00;
	_STL::vector<BfmeE16> m_04;
};

Rva004BA1B2::Rva004BA1B2()
{
}
