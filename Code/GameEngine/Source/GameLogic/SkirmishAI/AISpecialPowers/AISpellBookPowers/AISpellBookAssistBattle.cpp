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

// Target 0x005D8571: ArmyBreaker __FILE__ identifies the neighbouring source
// family; native reads use the same +0x54 key, +0x40 game frame, 8-byte
// key/deadline records and callback ABI as the verified AssistBattle check.
// Record application identity and the parameter's remaining layout are open.
// Reuse the vector storage owner used by Rva005D84F6Ctor.cpp.
extern unsigned int g_Va00E06670;
int g_00E06668; // Native .bss random lower endpoint, VA 0x00E06668.
int g_00E0666C; // Native .bss random upper endpoint, VA 0x00E0666C.
bool __fastcall Rva005D8571Check(int dummy, Rva005D839BParam *p)
{
	_STL::vector<BfmeE8> &list = reinterpret_cast<_STL::vector<BfmeE8> &>(g_Va00E06670);
	_STL::vector<BfmeE8>::iterator first = list.begin();
	_STL::vector<BfmeE8>::iterator last = list.end();
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
		list.push_back(tmp);
		found = &list[list.size() - 1];
	}
	if (found->b <= TheGameLogic->m_40)
	{
		unsigned int r = (unsigned int)GetGameLogicRandomValue(g_00E06668, g_00E0666C, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookArmyBreaker.cpp", 0x4E);
		found->b = TheGameLogic->m_40 + r;
		return true;
	}
	return false;
}
