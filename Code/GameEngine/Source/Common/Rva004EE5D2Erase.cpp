// cl: /MD /Ireference/shims/moduledata
// stlport
//
// ?rva004EE5D2@LivingWorldScoreKeeper@@QAEXXZ @0x004EE5D2 195B
// Removes 8 embedded entries via rowed ?rva002B7250@Rva002B7250@@QAEXPAVCreateAHeroData@@@Z:
// 4 from Rva002BA8F1Logic members, 3 from globals, 1 from member pointer.
// Evidence: packet disassembly order and offsets, callers 0x004EE695/0x004EE78A.
// +0x04..+0x20 are LivingWorldScoreKeeper's eight observer bases after
// Snapshot (hence the this-null checks) and +0xF8 its once-only flag.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class CreateAHeroData
{
public:
	int m_x;
};

class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *v);
};

class Rva002BA8F1Logic;

Rva002B7250 g_00E04424;
extern Rva002B7250 g_registryAtE02E88;
Rva002B7250 g_00E044F0;

class BfmeSelectionState
{
public:
	bool isSelectionLocked()const;
};

#include <time.h>

#include "../../Include/Common/LivingWorldScoreKeeper.h"

void LivingWorldScoreKeeper::rva004EE5D2()
{
	((Rva002B7250 *)((char *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic) + 0x1c))->rva002B7250((CreateAHeroData *)static_cast<LivingWorldPhaseObserver *>(this));
	((Rva002B7250 *)((char *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic) + 0x2c))->rva002B7250((CreateAHeroData *)static_cast<LivingWorldAutoResolveEventObserver *>(this));
	((Rva002B7250 *)((char *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic) + 0x3c))->rva002B7250((CreateAHeroData *)static_cast<LivingWorldRTSEventObserver *>(this));
	((Rva002B7250 *)((char *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic) + 0x4c))->rva002B7250((CreateAHeroData *)static_cast<LivingWorldLogicObserver *>(this));
	g_00E04424.rva002B7250((CreateAHeroData *)static_cast<LivingWorldBuildingObserver *>(this));
	g_registryAtE02E88.rva002B7250((CreateAHeroData *)static_cast<LivingWorldRegionObserver *>(this));
	g_00E044F0.rva002B7250((CreateAHeroData *)static_cast<LivingWorldBuildingNuggetSpawnArmyObserver *>(this));
	((Rva002B7250 *)m_player)->rva002B7250((CreateAHeroData *)static_cast<LivingWorldPlayerObserver *>(this));
}



void LivingWorldScoreKeeper::rva004EE78A()
{
	if (m_F8 != 0)
		return;
	m_F8 = 1;
	return rva004EE5D2();
}
