// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/moduledata /Ireference/shims/bfme2_ascii
//
// LivingWorldLogic::loadPostProcess, native 2BC5D3..2BC653 (128 B,
// ret 0). Identity: the WB debug body at va 0xd89ef0 (callgraph match 2.0)
// reproduces this exact statement order; the receiver is an observer
// subobject at +0xC of the object it resets, whose members are
// m_player8C (+0x8C, per the setLocal argument), m_regionA4 (+0xA4, pointer
// with a virtual at vslot 1), m_bd (+0xBD guard) and m_dc (+0xDC tail guard).
// The reset target is the same object Rva002BA8F1Logic::setLocal
// (0x002B38F7) and Rva002B296F::rva002B296F (0x002B296F) are called on, so
// its own offsets are reached through (char *)this: player +0x98 =
// this+0x8C, region manager +0xB0 = this+0xA4, BfmeSelectionState flags
// +0xB4/+0xB5 (rowed isSelectionLocked 0x0042253A), phase byte +0xE8 =
// this+0xDC. Every call is a landed row: 0x002BC39D Rva002BBBE7 list clear
// on the g_Va00E04544 global object, 0x005020CC BuildRegionDistances,
// 0x002B38F7 setLocal, 0x0042253A isSelectionLocked, 0x002B296F phase
// refresh. The Snapshot name slot identifies LivingWorldLogic; the globals
// are the ledger's own (TheCampaignManager 0x00A02D6C, g_00DFE1C8 0x009FE1C8,
// g_00DFEF18 0x009FEF18, g_Va00E04544 0x00A04544).

class Rva002E2903Player;
class Rva002BA8F1Logic;
class BfmeSelectionState;
class Rva002B296F;

// The member object at +0xC of TheCampaignManager that carries a vtable.
class Rva00E02D6CSub0C
{
public:
	virtual void slot00();
	virtual void slot04();
};

class Rva00E02D6C
{
public:
	char m_pad00[0xC];
	Rva00E02D6CSub0C m_sub0C;	// +0x0C
};

extern Rva00E02D6C *TheCampaignManager;	// 0x00A02D6C datum

// The member object at +0xC of the g_00DFE1C8 host.
class Rva00DFE1C8HostSub0C
{
public:
	virtual void slot00();
	virtual void slot04();
};

class Rva00DFE1C8Host
{
public:
	char m_pad00[0xC];
	Rva00DFE1C8HostSub0C m_sub0C;	// +0x0C
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;	// 0x009FE1C8

// The host whose vslot 0x28 takes one int (pushed 0).
class Rva002D3627Host
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28(int value);
};

class LivingWorld; extern LivingWorld *TheLivingWorld;	// 0x009FEF18 pin

// The 0x00A04544 global object (16 B, owned by Rva007B6880Thunks.cpp).
extern unsigned int g_Va00E04544;

class Rva002BBBE7
{
public:
	void rva002BC39D();	// 0x002BC39D, 41 B
};

void Rva005020CCBuildRegionDistances();	// 0x005020CC, 447 B

#include "../../../../Include/GameLogic/Rva002BA8F1Logic.h"

#include "../../../../Include/Common/BfmeSelectionState.h"

#include "../../../../Include/Common/Rva002B296F.h"

// The region manager pointer read at this+0xA4 (the reset target's +0xB0).
class Rva002BC5D3RegionMgr
{
public:
	virtual void slot00();
	virtual void slot04();
};

// The Snapshot override receives the secondary subobject at +0xC.
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
#include "../../../../../Libraries/Source/subsystem/SubsystemInterface.h"
class LivingWorldLogic : public SubsystemInterface, public Snapshot
{
public:
	virtual void loadPostProcess();

private:
	char m_pad10[0x98 - 0x10];
	Rva002E2903Player *m_player8C;		// +0x8C
	char m_pad90[0xA4 - 0x90];
	Rva002BC5D3RegionMgr *m_regionA4;	// +0xA4
	char m_padA8[0xBD - 0xA8];
	unsigned char m_bd;			// +0xBD
	char m_padBE[0xDC - 0xBE];
	unsigned char m_dc;			// +0xDC
};

void LivingWorldLogic::loadPostProcess()
{
	if (m_bd != 0)
	{
		TheCampaignManager->m_sub0C.slot04();
		m_regionA4->slot04();
		((Rva00DFE1C8Host *)TheLivingWorldManager)->m_sub0C.slot04();
		((Rva002BBBE7 *)&g_Va00E04544)->rva002BC39D();
		Rva005020CCBuildRegionDistances();

		Rva002BA8F1Logic *logic = (Rva002BA8F1Logic *)((char *)this);
		logic->setLocal(m_player8C);

		if (!((BfmeSelectionState *)logic)->isSelectionLocked())
			((Rva002D3627Host *)TheLivingWorld)->slot28(0);

		if (m_dc != 0)
			((Rva002B296F *)logic)->rva002B296F();
	}
}
