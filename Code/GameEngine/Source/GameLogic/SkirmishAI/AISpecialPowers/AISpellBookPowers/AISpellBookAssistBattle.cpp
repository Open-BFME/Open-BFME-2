// cl: /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Rva005D839BCheck RVA 0x005D839B size 168 evidence vector BfmeE8 TheGameLogic+0x40, call site 0x005D84BB.
// The random-range __FILE__ literal is the one retail pushes (0x00C76008,
// AISpellBookAssistBattle.cpp); the banked attempt carried AIStates.cpp.
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

struct BfmeE8 { unsigned int a, b; };

class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_40;
};

extern GameLogic *TheGameLogic;
extern _STL::vector<BfmeE8> g_00E06654;
extern int g_00E06650;
// g_00E06650: matched references place it at VA 0xe06650 (zero-filled .bss).
int g_00E06650;
extern int g_00E06660;
// g_00E06660: matched references place it at VA 0xe06660 (zero-filled .bss).
int g_00E06660;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

struct Rva005D839BParam
{
	char m_pad00[0x54];
	int m_54;
};

bool __fastcall Rva005D839BCheck(int dummy, Rva005D839BParam *p)
{
	_STL::vector<BfmeE8>::iterator first = g_00E06654.begin();
	_STL::vector<BfmeE8>::iterator last = g_00E06654.end();
	BfmeE8 *found = 0;
	if (first != last)
	{
		for (BfmeE8 *it = first; it != last; ++it)
		{
			if (found != 0)
				break;
			if (it != 0 && it->a == (unsigned int)p->m_54)
				found = it;
		}
	}
	if (found == 0)
	{
		BfmeE8 tmp;
		tmp.a = (unsigned int)p->m_54;
		tmp.b = TheGameLogic->m_40;
		g_00E06654.push_back(tmp);
		found = &g_00E06654[g_00E06654.size() - 1];
	}
	if (found->b <= TheGameLogic->m_40)
	{
		unsigned int r = (unsigned int)GetGameLogicRandomValue(g_00E06650, g_00E06660, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookAssistBattle.cpp", 0x4D);
		found->b = TheGameLogic->m_40 + r;
		return true;
	}
	return false;
}
