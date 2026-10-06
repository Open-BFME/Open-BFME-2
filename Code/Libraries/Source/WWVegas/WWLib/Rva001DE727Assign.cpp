// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4Rva001DE727@@QAEAAV0@ABV0@@Z, retail 0x001DE727 85B chain.
// Evidence: 5 dwords + Rb_tree set at +0x14 via rowed assign 0x001DDC52 +
// 4B-POD vector at +0x20 via int pin at 0x0021C21B + 3 bytes at +0x2C.
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <vector>

struct BfmeRecord001DD3BC
{
	unsigned char m_data[8];
};

bool operator<(const BfmeRecord001DD3BC &a, const BfmeRecord001DD3BC &b);

typedef _STL::_Rb_tree<BfmeRecord001DD3BC, BfmeRecord001DD3BC, _STL::_Identity<BfmeRecord001DD3BC>, _STL::less<BfmeRecord001DD3BC>, _STL::allocator<BfmeRecord001DD3BC> > BfmeRecord001DD3BCSetTree;

class Rva001DE727
{
public:
	Rva001DE727 &operator=(const Rva001DE727 &that);

private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	BfmeRecord001DD3BCSetTree m_set14; // +0x14
	_STL::vector<int, _STL::allocator<int> > m_vec20; // +0x20
	unsigned char m_2C;
	unsigned char m_2D;
	unsigned char m_2E;
};

Rva001DE727 &Rva001DE727::operator=(const Rva001DE727 &that)
{
	m_00 = that.m_00;
	m_04 = that.m_04;
	m_08 = that.m_08;
	m_0C = that.m_0C;
	m_10 = that.m_10;
	m_set14 = that.m_set14;
	m_vec20 = that.m_vec20;
	m_2C = that.m_2C;
	m_2D = that.m_2D;
	m_2E = that.m_2E;
	return *this;
}
