// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva0009C983@Rva0009C983@@QAEXH@Z retail 0x0009C983..0x0009C9DE
// (91 bytes ret 4). When TheLivingWorldLogic exists and its mode at +0xF4
// is 0 or 4 it walks the living-world player vector at +0x8C (count taken
// once) fetching each player through Rva002BA8F1Logic::rva002B52A8
// 0x002B52A8 and colours that player's army lines with
// rva0009C814 0x0009C814 (same class; first argument forwarded). No donor
// or WorldBuilder twin; names are address-derived.
#include <vector>

typedef int Int;

class Rva002E2903Player;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(Int index);
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

struct Rva0009C983LogicView
{
	char m_pad00[0x8C];
	_STL::vector<Rva002E2903Player *> m_players; // +0x8C
	char m_pad98[0xF4 - 0x98];
	Int m_mode; // +0xF4
};

class Rva0009C983
{
public:
	void rva0009C983(Int arg);
	void rva0009C814(Int arg, Rva002E2903Player *player);
};

void Rva0009C983::rva0009C983(Int arg)
{
	Rva0009C983LogicView *logic = reinterpret_cast<Rva0009C983LogicView *>(TheLivingWorldLogic);
	if (logic == 0)
		return;
	if (logic->m_mode != 0 && logic->m_mode != 4)
		return;
	Int count = logic->m_players.size();
	for (Int i = 0; i < count; ++i)
	{
		Rva002E2903Player *player = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->rva002B52A8(i);
		if (player)
			rva0009C814(arg, player);
	}
}
