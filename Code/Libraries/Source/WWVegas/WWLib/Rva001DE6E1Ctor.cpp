// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva001DE6E1@@QAE@XZ @0x001DE6E1 70B default ctor with map plus vector plus trailing bytes.
// Evidence: __thiscall returns this; callees rowed map 0x0033C432 plus vector base 0x00211E58; callers 0x001DF4C2 0x001DF609 0x001DF734 0x001DF80F 0x001DF907; constants 0x4E20 0x5DC 5 plus 0 1 0.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

class Rva001DE6E1
{
public:
	Rva001DE6E1();
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_map14;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec20;
	unsigned char m_2C;
	unsigned char m_2D;
	unsigned char m_2E;
};

Rva001DE6E1::Rva001DE6E1()
	: m_00(0x4E20)
	, m_04(0x5DC)
	, m_08(0)
	, m_0C(0)
	, m_10(5)
	, m_2C(0)
	, m_2D(1)
	, m_2E(0)
{
}
