// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0040A530@@QAE@_N@Z @0x0040A530 28B
// Evidence: unlock lane; calls rowed Vector_base<BfmeE16> 0x00211E58; copies byte to +0xC; callers 0x21FEC3 0x5B582C.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva0040A530
{
public:
	Rva0040A530(bool flag);
private:
	_STL::vector<BfmeE16> m_0000;
	bool m_000C;
};

Rva0040A530::Rva0040A530(bool flag)
	: m_0000()
	, m_000C(flag)
{
}
