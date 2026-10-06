// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00501DD4Sub@@QAE@ABU0@@Z @0x005017B4 95B: Sub copy ctor copying 5 dwords plus two vectors; evidence rowed vector copy 0x00500DA0 twice rowed EH_prolog 0x00629188 callers 0x0050182D 0x0050185E 0x00501DE6 0x00501E0B and dtor layout 0x00501776
#include <vector>

struct Rva00500DA0Element
{
	unsigned int m_data[5];
	~Rva00500DA0Element();
};

struct Rva00501DD4Sub
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	_STL::vector<Rva00500DA0Element> m_14;
	_STL::vector<Rva00500DA0Element> m_20;
	Rva00501DD4Sub(const Rva00501DD4Sub &that);
};

Rva00501DD4Sub::Rva00501DD4Sub(const Rva00501DD4Sub &that)
	: m_00(that.m_00)
	, m_04(that.m_04)
	, m_08(that.m_08)
	, m_0c(that.m_0c)
	, m_10(that.m_10)
	, m_14(that.m_14)
	, m_20(that.m_20)
{
}
