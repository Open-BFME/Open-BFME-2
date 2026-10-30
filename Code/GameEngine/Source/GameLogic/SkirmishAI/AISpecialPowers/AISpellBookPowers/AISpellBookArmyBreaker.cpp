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
static bool __fastcall Rva005D8571Check(int dummy, Rva005D839BParam *player)
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
			if (it != 0 && it->a == (unsigned int)player->m_54)
				found = it;
		}
	}
	if (found == 0)
	{
		BfmeE8 entry;
		entry.a = (unsigned int)player->m_54;
		entry.b = TheGameLogic->getFrame();
		list.push_back(entry);
		found = &list[list.size() - 1];
	}
	if (found->b <= TheGameLogic->getFrame())
	{
		unsigned int delay = (unsigned int)GetGameLogicRandomValue(g_00E06668, g_00E0666C, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookArmyBreaker.cpp", 0x4E);
		found->b = TheGameLogic->getFrame() + delay;
		return true;
	}
	return false;
}

// Native5D8619..5D86D4 RET4 is the complete187B slot6 of vtable8760A4,
// installed by the independently rowed constructor5D8539. It is not an
// SSE instruction interior as the old boundary verdict claimed.
// The native tally tests require at least four opponents and at most half
// as many friendly units; its unsigned-to-float conversions are preserved.
// All layout and provider views are the independently verified AssistBattle
// siblings. The +28 address is the lookup receiver; no wider layout is claimed.
// Keep the existing frame-window helper file-local, with its full168B exact.

#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

class Player;
class Object;
class AIUpdateInterface {
public:
    Object *getCurrentVictim() const;
};
class Object {
public:
    Player *getControllingPlayer() const;
    const Coord3D *getPosition() const { return &m_position; }
    char m_prefix[0x38];
    Coord3D m_position;
    char m_tail[0x258 - 0x44];
    AIUpdateInterface *m_ai;
};
class Rva005EE9CE {
public:
    Rva005EE9CE *rva005EE9CE();
    unsigned int m_00;
    float m_04;
    unsigned int m_08;
    float m_0c;
};
class Rva005EEA20 {
public:
    Object *findUnitInCombat(Player *, bool, bool);
};
class AISpellBookBase {
public:
    void getStatsInCombatRange(Rva005EE9CE *, Object *, float);
};
class Rva005EE816 {
public:
    bool rva005EE8DD(const Coord3D *, Object *);
};

class Rva005D84F6 {
public:
    virtual ~Rva005D84F6();
    virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5();
    virtual bool rva005D8619(Object *source);
    char m_prefix[0x28 - 4];
    char m_lookup;
};
bool Rva005D84F6::rva005D8619(Object *source)
{
    Object *object = reinterpret_cast<Rva005EEA20 *>(&m_lookup)->findUnitInCombat(
        source->getControllingPlayer(), true, true);
    if (object) {
        Rva005EE9CE stats;
        stats.rva005EE9CE();
        reinterpret_cast<AISpellBookBase *>(&m_lookup)->getStatsInCombatRange(&stats, object, 350.0f);
        if (stats.m_08 >= 4 && stats.m_00 <= stats.m_08 * 0.5f &&
            reinterpret_cast<Rva005EE816 *>(this)->rva005EE8DD(
                object->m_ai->getCurrentVictim()->getPosition(), source) &&
            Rva005D8571Check(0, reinterpret_cast<Rva005D839BParam *>(source->getControllingPlayer())))
            return true;
    }
    return false;
}
