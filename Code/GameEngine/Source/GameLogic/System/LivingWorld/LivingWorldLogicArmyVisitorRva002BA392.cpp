// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP=
//
// The living-world army walk callback at 0x002BA392 (96 bytes, RET4; vtable
// 0x00BFE000, built inline at 0x002B29E0 and 0x002B3811), the code just
// before LivingWorldLogic's player observer 0x002BA3F2. +0x04 is the battle.
// Once the battle has a winning side, an army whose owner the winner's first
// player does not count as a friend (rowed 0x002E0BC0), that has no unflagged
// units left (rowed 0x0040CF55) and an empty name is queued for destruction
// (rowed 0x002B8A9F on TheLivingWorldLogic). Armies without the +0x75 flag
// get the rowed 0x003192B1 update. Returns true so the walk continues. Class
// and method spellings are unknown; the views follow LivingWorldLogic.cpp.

typedef int Int;
typedef bool Bool;

class ModuleData;
class ArmySummary;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

#include "string_base.h"

struct LivingWorldArmy
{
	unsigned char m_pad00[0x18];
	StringBase<char> m_name;				// +0x18
	unsigned char m_pad1C[0x54 - 0x1C];
	Int m_ownerPlayer;					// +0x54
	unsigned char m_pad58[0x75 - 0x58];
	Bool m_field75;						// +0x75
	unsigned char m_pad76[0x78 - 0x76];
	ArmySummary *m_summary;					// +0x78
};

class LivingWorldBattle
{
public:
	unsigned char m_pad00[0x38];
	Int m_side;						// +0x38, the winning side
};

// Rowed receivers under placeholder names (LivingWorldLogic.cpp views).
class Rva003F468D
{
public:
	Int rva003F468D(Int side, Int army);			// 0x003F468D
};
class Rva002E071E
{
public:
	Int rva002E0BC0(Int playerID);				// 0x002E0BC0
};
class Rva0040CF55Owner
{
public:
	Int sumUnflagged() const;				// 0x0040CF55
};
class Rva002B8A9F
{
public:
	void rva002B8A9F(ModuleData *army);			// 0x002B8A9F
};
class Rva003193EC
{
public:
	void rva003192B1();					// 0x003192B1
};

class Rva002BA392ArmyVisitor
{
public:
	virtual bool visit(LivingWorldArmy *army);

	LivingWorldBattle *m_battle;				// +0x04
};

bool Rva002BA392ArmyVisitor::visit(LivingWorldArmy *army)
{
	LivingWorldBattle *battle = m_battle;
	if (battle->m_side >= 0)
	{
		Rva002E071E *winner = (Rva002E071E *)((Rva003F468D *)battle)->rva003F468D(battle->m_side, 0);
		if (!(unsigned char)winner->rva002E0BC0(army->m_ownerPlayer))
		{
			if (!(army->m_summary && ((const Rva0040CF55Owner *)army->m_summary)->sumUnflagged())
				&& army->m_name.isEmpty())
				((Rva002B8A9F *)TheLivingWorldLogic)->rva002B8A9F((ModuleData *)army);
		}
		if (!army->m_field75)
			((Rva003193EC *)army)->rva003192B1();
	}
	return true;
}
