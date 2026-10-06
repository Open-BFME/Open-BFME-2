// cl: /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva005D8317@@QAE@H@Z RVA 0x005D835A size 65 evidence vtable 0x00875FEC base 0x005EE2E6 TheGameLogic+0x40 vector erase 0x003FA4DB caller 0x0058A6A8
#include <vector>

struct BfmePod8 { int a[2]; };

class Rva005EE30C
{
public:
	Rva005EE30C();
	virtual ~Rva005EE30C();
private:
	char m_pad04[0x28 - 4];
};

class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_40;
};

extern GameLogic *TheGameLogic;
extern _STL::vector<BfmePod8> g_00E06654;

class Rva005D8317 : public Rva005EE30C
{
public:
	Rva005D8317(int v);
	virtual ~Rva005D8317();
private:
	int m_28;
};

Rva005D8317::Rva005D8317(int v)
	: m_28(v)
{
	if (TheGameLogic->m_40 <= 1)
	{
		_STL::vector<BfmePod8>::iterator first = g_00E06654.begin();
		_STL::vector<BfmePod8>::iterator last = g_00E06654.end();
		if (first != last)
			g_00E06654.erase(first, last);
	}
}
