// ?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z
// cl: /MD
// ?rva004320B1@Rva004320B1@@QAEHPAVGameMessage@@@Z @0x004320B1 160B: switch on
// GameMessage+0x10 dispatching case 3 to a terrain pixel->world probe through
// View slot 90 (the global at 0xDFEA3C is a View*, per matched sibling
// Rva0029B4F9Init.cpp, not a standalone TacticalView) followed by three
// TheInGameUI uses -- InGameUI slot 51 (0xCC), slot 50 (0xC8) and the byte at
// 0x9B4 -- and cases 6/0x10 to Rva00431A4D then Rva00431E95. The three UI uses
// each read the global afresh; caching one read in a local costs a mov ecx,esi
// pair per use and lands 158B. Slot 51/50 and the 0x9B4 offset are fixed by
// matched sibling Rva004319F2.cpp. Copy helper 0x29AA27 is reached with the
// InGameUI pointer untouched in ecx, hence the offset-0 cast.
#include <stddef.h>

#include "../../../Libraries/Include/Lib/ICoord2D.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"

union GameMessageArgumentType
{
	int integer;
	struct Pix { int x; int y; } pixel;
};

#include "../../Include/Common/MessageStream.h"

class Rva00431A4D
{
	char m_00[4];
	unsigned char m_04;
	unsigned char m_05;
public:
	void EatNextClickMessage(GameMessage *msg);
};

class Rva00431E95
{
public:
	int HandleButtonUp(void *p);
};

#include "../../Include/GameClient/View.h"

#include "../../Include/GameClient/InGameUI.h"

struct S12_0029AA27 { int a; int b; int c; };

class Rva0029AA27At
{
public:
	void rva0029AA27(const S12_0029AA27 *src);
};
class Rva0029AA27
{
public:
	void rva0029AA27(const S12_0029AA27 *src);
};

// Retail reaches the rowed Rva0029AA27::rva0029AA27 (0x0029AA27, 24B, guarded
// 12B copy) with ecx = TheInGameUI itself, so the receiver is the UI pointer and
// the callee resolves to the rowed class rather than the offset-shim above.
struct Rva0029AA27At2 : Rva0029AA27
{
};

extern class View *TheTacticalView;
extern class InGameUI *TheInGameUI;
extern Rva0029AA27 *TheRva0029AA27;
extern void *g_ks_30f4ea;

Rva0029AA27 *TheRva0029AA27;
void *g_ks_30f4ea;

class Rva004320B1
{
	void *m_00;
	Rva00431A4D *m_04;
public:
	int rva004320B1(GameMessage *msg);
};

void Rva00431A4D::EatNextClickMessage(GameMessage *msg)
{
	if (msg->m_type == 6)
		m_04 = 1;
	else
		m_05 = 1;
}

int Rva004320B1::rva004320B1(GameMessage *msg)
{
	switch (msg->m_type)
	{
	case 3:
	{
		const GameMessageArgumentType *gameMessageArgumentType = msg->getArgument(0);
		ICoord2D pixel;
		pixel.x = gameMessageArgumentType->pixel.x;
		pixel.y = gameMessageArgumentType->pixel.y;
		Coord3D world;
		TheTacticalView->screenToTerrain(&pixel, &world, false);
		if (TheInGameUI->slot51())
			TheInGameUI->slot50(&world);
		if (TheInGameUI->m_9B4 != 0)
			((Rva0029AA27At2 *)TheInGameUI)->Rva0029AA27::rva0029AA27((const S12_0029AA27 *)&world);
		return 0;
	}
	case 6:
	case 0x10:
		m_04->EatNextClickMessage(msg);
		return ((Rva00431E95 *)this)->HandleButtonUp(msg);
	default:
		return 0;
	}
}