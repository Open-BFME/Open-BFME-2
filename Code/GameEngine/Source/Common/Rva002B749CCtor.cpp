// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva002B749C@@QAE@XZ @0x002B749C 66B ctor calls map 0x0033C432 at +0 and Vector_base BfmeE16 0x00211E58 at +0xc then inits floats from g_Va00BBB8D8 and ints 0/-1.
// Evidence: push ecx push esi mov esi ecx lea esp+7 pattern for Vector_base; movss from g_Va00BBB8D8 at +0x18/+0x1c/+0x20; and-mem-0 at +0x24/+0x28 and or-mem--1 at +0x2c/+0x30 under /O1; caller 0x002BC944; callees rowed.
#include <map>
#include <vector>

struct BfmeE16 { float x, y, z, w; };

extern float g_Va00BBB8D8;

class Rva002B749C
{
public:
	Rva002B749C();
private:
	_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > m_00;
	_STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_0c;
	float m_18;
	float m_1c;
	float m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
};

Rva002B749C::Rva002B749C()
	: m_00(),
	  m_0c(_STL::allocator<BfmeE16>())
{
	float f = g_Va00BBB8D8;
	m_24 = 0;
	m_28 = 0;
	m_2c = -1;
	m_30 = -1;
	m_18 = f;
	m_1c = f;
	m_20 = f;
}
