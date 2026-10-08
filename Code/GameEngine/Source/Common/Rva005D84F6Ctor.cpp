// cl: /MD
// stlport
// ??0Rva005D84F6@@QAE@XZ RVA 0x005D8539 size 56 evidence vtable 0x008760A4 base ctor 0x005EE2E6 TheGameLogic+0x40 erase vector at 0x00E06670 caller 0x0058AA1A
#include <vector>

struct BfmePod8 { int a[2]; };

class Rva005EE30C
{
public:
	Rva005EE30C();
	virtual ~Rva005EE30C();
};

class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_40;
};

extern GameLogic *TheGameLogic;
extern unsigned int g_Va00E06670;	// vector object at 0x00E06670 (Rva007B6880Thunks.cpp)

class Rva005D84F6 : public Rva005EE30C
{
public:
	Rva005D84F6();
	virtual ~Rva005D84F6();
};

Rva005D84F6::Rva005D84F6()
{
	_STL::vector<BfmePod8> &list = (_STL::vector<BfmePod8> &)g_Va00E06670;
	if (TheGameLogic->m_40 <= 1)
	{
		if (!list.empty())
			list.erase(list.begin(), list.end());
	}
}
