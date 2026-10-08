// cl: /O1 /arch:SSE /G7 /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native __FILE__ places the frame-window check in AISpellBookArmyBreaker.cpp.
// The AssistBattle sibling supplies the verified expression and compiler
// settings; offsets and all target-specific globals are read from retail.
#include <vector>
#include "../../../../Common/GameLogicObjectLookupView.h"

struct BfmeE8 { unsigned int a, b; };
// Use the ledger's existing exact push_back provider, rather than emitting
// a second copy of the library member in this translation unit.
namespace _STL {
template <> void vector<BfmeE8>::push_back(const BfmeE8 &value);
}
extern GameLogic *TheGameLogic;
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

// Shared partial parameter view: only the native +0x54 key is asserted.
struct Rva005D839BParam
{
    char m_pad00[0x54];
    int m_54;
};

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
		tmp.b = TheGameLogic->getFrame();
		list.push_back(tmp);
		found = &list[list.size() - 1];
	}
	if (found->b <= TheGameLogic->getFrame())
	{
		unsigned int r = (unsigned int)GetGameLogicRandomValue(g_00E06668, g_00E0666C, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookArmyBreaker.cpp", 0x4E);
		found->b = TheGameLogic->getFrame() + r;
		return true;
	}
	return false;
}
