// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva002B89E1@LivingWorldLogic@@QAE_NH@Z  0x002B89E1..0x002B8A9F (190 bytes)
// Starts the given living-world battle. WorldBuilder twin 0x00D89030
// (callgraph score 1.0): tells the battle listeners at +0x3C through the slot
// +0 vcall thunk 0x001FF3A9; calls TheAudio slot +0x190; records the region's
// +0x12C in +0xB8 (WB helper 0x00D89360 inlined); clears the mission help
// text (0x0029B17C); clears the delayed modules (0x002B7C74) and
// PrepareBattleForLoading; then by TheGameLogic's mode word +0x114 hands the
// battle to TheLAN (slot +0xA4) TheGameSpyGame (0x004FDEFF) or the region's
// PrepareSkirmishOpponents; finally SetActiveBattleID (WB name; row
// 0x0020E63F) and LivingWorld::ZoomInTo on the global's +0x8C.
#include "../../../Common/GameLogicObjectLookupView.h"

#define V4(n) virtual void v##n##a(); virtual void v##n##b(); virtual void v##n##c(); virtual void v##n##d();

class LivingWorldBattle;

class Rva002B616FListener
{
public:
	virtual void slot00(void *logic, int battle);	// +0x00
};

class Rva002B616FList
{
public:
	void forEach(void (Rva002B616FListener::*notify)(void *, int), void *arg, int value);	// 0x002B616F

private:
	unsigned char m_data[0x10];
};

class AudioManager
{
public:
	V4(0) V4(1) V4(2) V4(3) V4(4) V4(5) V4(6) V4(7) V4(8) V4(9)
	V4(10) V4(11) V4(12) V4(13) V4(14) V4(15) V4(16) V4(17) V4(18) V4(19)
	V4(20) V4(21) V4(22) V4(23) V4(24)
	virtual void slot190();	// +0x190
};
extern AudioManager *TheAudio;

class LANAPI
{
public:
	V4(0) V4(1) V4(2) V4(3) V4(4) V4(5) V4(6) V4(7) V4(8) V4(9)
	virtual void v40();
	virtual void slotA4(LivingWorldBattle *battle);	// +0xA4
};
extern LANAPI *TheLAN;

class GameSpyStagingRoom
{
public:
	void rva004FDEFF(LivingWorldBattle *battle);	// 0x004FDEFF
};
extern GameSpyStagingRoom *TheGameSpyGame;

class InGameUI;
extern InGameUI *TheInGameUI;
class Rva0029B17C
{
public:
	void rva0029B17C();	// 0x0029B17C, WB InGameUI::clearMissionHelpText
};

extern GameLogic *TheGameLogic;

class LivingWorldRegion
{
public:
	void PrepareSkirmishOpponents(LivingWorldBattle *battle);	// 0x003F34DD

	unsigned char m_pad00[0x12C];
	int m_field12C;						// +0x12C
};

class LivingWorldBattle
{
public:
	unsigned char m_pad00[0x24];
	LivingWorldRegion *m_region;				// +0x24
	unsigned char m_pad28[0x34 - 0x28];
	int m_id;						// +0x34
};

class Rva0020E5BB
{
public:
	void rva0020E63F(int battleID, int value);	// 0x0020E63F, WB LivingWorldRegionManager::SetActiveBattleID
};

class LivingWorld
{
public:
	void ZoomInTo(void *arg);				// 0x002BE8F9
};
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;

class Rva002B7C74
{
public:
	void rva002B7C74();					// 0x002B7C74
};

class LivingWorldLogic
{
public:
	bool rva002B89E1(int battle);
	void PrepareBattleForLoading(LivingWorldBattle *battle);	// 0x002B792E

	unsigned char m_pad00[0x3C];
	Rva002B616FList m_battleListeners;			// +0x3C
	unsigned char m_pad4C[0xB0 - 0x4C];
	Rva0020E5BB *m_regionManager;				// +0xB0
	unsigned char m_padB4[0xB8 - 0xB4];
	int m_fieldB8;						// +0xB8
};

bool LivingWorldLogic::rva002B89E1(int battleArg)
{
	LivingWorldBattle *battle = (LivingWorldBattle *)battleArg;
	if (battle == 0)
		return false;
	m_battleListeners.forEach(&Rva002B616FListener::slot00, this, battleArg);
	LivingWorldRegion *region = battle->m_region;
	TheAudio->slot190();
	m_fieldB8 = region->m_field12C;
	((Rva0029B17C *)TheInGameUI)->rva0029B17C();
	((Rva002B7C74 *)this)->rva002B7C74();
	PrepareBattleForLoading(battle);
	int mode = TheGameLogic->m_114;
	if (mode == 1)
		TheLAN->slotA4(battle);
	else if (mode == 2)
		TheGameSpyGame->rva004FDEFF(battle);
	else
		region->PrepareSkirmishOpponents(battle);
	m_regionManager->rva0020E63F(battle->m_id, 2);
	((LivingWorld *)g_00DFEF18)->ZoomInTo((char *)g_00DFEF18 + 0x8C);
	return true;
}
