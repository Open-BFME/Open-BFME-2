// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0018C54E@@QAE@XZ 0x0018C54E 46B ctor with vector<BfmeE16> at +0x14 plus zeroed header/trailer; callee Vector_base row; caller 0x001735F9 new(0x28)
#include <vector>
struct BfmeE16 { float x, y, z, w; };
class Rva0018C54E {
	unsigned char m_00;
	int m_04;
	void *m_08;
	void *m_0c;
	void *m_10;
	_STL::vector<BfmeE16> m_14;
	int m_20;
	int m_24;
public:
	Rva0018C54E();
};
Rva0018C54E::Rva0018C54E() : m_00(0), m_04(0), m_08(0), m_0c(0), m_10(0), m_14(), m_20(0), m_24(0)
{
}
