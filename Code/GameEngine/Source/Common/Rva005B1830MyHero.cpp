// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva005B1830@Rva005B1830@@QAEXXZ, retail 0x005B1830 211B.
// Double loop over +0x174 calling rowed 0x005B129F then three MyHero StringBase blocks via rowed 0x005241DF.
// Evidence: rowed 0x005B129F and 0x005241DF plus StringBase ctor/release rows; literals MyHero::BaseAttrib/CurAttrib/MaxAttrib; callers 0x005B19BA 0x005B1B6E.
#include "ascii_string.h"

class Rva005B129FClass
{
public:
	int m_0;
	int m_4;

	int rva005B129F(int a1, int a2);
};

struct Rva005B1830Item
{
	Rva005B129FClass inner;
	int m_8;
};

class Rva005241DF
{
public:
	void rva005241DF(const StringBase<char> &val);
};

struct Rva005B1830Holder
{
	char m_pad00[0x228];
	Rva005241DF m_228;
};

class Rva005B1830
{
public:
	void rva005B1830();

private:
	char m_pad00[0x140];
	Rva005B1830Holder *m_140;
	char m_pad144[0x174 - 0x144];
	Rva005B1830Item m_174[2];
};

void Rva005B1830::rva005B1830()
{
	for (int i = 0; i < 2; ++i) {
		Rva005B129FClass &slot = (Rva005B129FClass &)m_174[i];
		int b = slot.m_4;
		int a = slot.m_0;
		slot.rva005B129F(a, b);
	}
	{
		AsciiString s("MyHero::BaseAttrib");
		((Rva005241DF *)((char *)m_140 + 0x228))->rva005241DF(*(const StringBase<char> *)&s);
	}
	{
		AsciiString s("MyHero::CurAttrib");
		((Rva005241DF *)((char *)m_140 + 0x228))->rva005241DF(*(const StringBase<char> *)&s);
	}
	{
		AsciiString s("MyHero::MaxAttrib");
		((Rva005241DF *)((char *)m_140 + 0x228))->rva005241DF(*(const StringBase<char> *)&s);
	}
}
