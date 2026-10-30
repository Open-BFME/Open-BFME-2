// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Rva005D839BCheck RVA 0x005D839B size 168 evidence vector BfmeE8 TheGameLogic+0x40, call site 0x005D84BB.
// The random-range __FILE__ literal is the one retail pushes (0x00C76008,
// AISpellBookAssistBattle.cpp); the banked attempt carried AIStates.cpp.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct BfmeE8 { unsigned int a, b; };
// bfme link decl-only begin
// The rowed body calls the 8-byte push_back 0x00539A2E
// (stlport_vector_e8_allocate_copy.cpp); this unit's /EH copy of its
// _M_insert_overflow is not retail's 0x00057C80, so it emits neither.
namespace _STL { template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(BfmeE8 const &); }
// bfme link decl-only end

#include "../../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;
// The vector at 0x00E06654 is owned as g_Va00E06654 (Rva007B6880Thunks.cpp).
extern unsigned int g_Va00E06654;
#define g_00E06654 (*(_STL::vector<BfmeE8> *)&g_Va00E06654)
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

static bool __fastcall Rva005D839BCheck(int dummy, Rva005D839BParam *player)
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
			if (it != 0 && it->a == (unsigned int)player->m_54)
				found = it;
		}
	}
	if (found == 0)
	{
		BfmeE8 tmp;
		tmp.a = (unsigned int)player->m_54;
		tmp.b = TheGameLogic->getFrame();
		g_00E06654.push_back(tmp);
		found = &g_00E06654[g_00E06654.size() - 1];
	}
	if (found->b <= TheGameLogic->getFrame())
	{
		unsigned int delay = (unsigned int)GetGameLogicRandomValue(g_00E06650, g_00E06660, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISpellBookPowers\\AISpellBookAssistBattle.cpp", 0x4D);
		found->b = TheGameLogic->getFrame() + delay;
		return true;
	}
	return false;
}

// Native5D8443..5D84F6 is a complete179B RET4 virtual body, slot6 of
// vtable875FEC installed by the independently rowed constructor5D835A.
// The old SSE-interior boundary verdict is refuted by that entry and table.
// Constructor mode28 and native object position38/AI258 establish the views.
// The helper above is local to this file; its unused register argument then
// disappears at the call site while its own full168B remain retail-exact.
// The pure position accessor preserves the native argument evaluation order.
// Original class/method spellings remain unknown; retain address-derived names.

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

class Rva005D8317 {
public:
    virtual ~Rva005D8317();
    virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5();
    virtual bool rva005D8443(Object *source);
    char m_prefix[0x28 - 4];
    int m_mode;
};
bool Rva005D8317::rva005D8443(Object *source)
{
    bool skipStealth = m_mode == 1;
    bool skipVictim = m_mode == 0;
    Object *object = reinterpret_cast<Rva005EEA20 *>(&m_mode)->findUnitInCombat(
        source->getControllingPlayer(), skipStealth, skipVictim);
    if (object) {
        Rva005EE9CE stats;
        stats.rva005EE9CE();
        reinterpret_cast<AISpellBookBase *>(&m_mode)->getStatsInCombatRange(&stats, object, 350.0f);
        if (stats.m_08 > 0 && stats.m_04 < 0.99f &&
            Rva005D839BCheck(0, reinterpret_cast<Rva005D839BParam *>(object->getControllingPlayer()))) {
            if (m_mode == 0)
                return reinterpret_cast<Rva005EE816 *>(this)->rva005EE8DD(object->getPosition(), source);
            return reinterpret_cast<Rva005EE816 *>(this)->rva005EE8DD(
                object->m_ai->getCurrentVictim()->getPosition(), source);
        }
    }
    return false;
}
