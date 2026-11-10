// cl: /DNDEBUG /MD
//
// ?rva003BD598@Rva003BD598@@QAEXXZ @0x003BD598 72B (dump range 18).
// Thiscall clearer ending in a tail jump: clears its +0x0C byte, runs the
// pinned GameLogic 0x00376D49 member, re-enters through the pinned 0x003BBAD3
// member (retail passes this in ecx although the callee body only reads
// globals, so the rowed free-function name cannot spell the call), drops
// the current campaign's mission-won handler through the manager forwarder
// 0x001EC981 when the manager global is set, flags the
// campaign manager byte, applies the rowed 0x002036A9 imm setter, and
// tail-jumps the pinned 0x0021A54A member on the hero-manager global.
#include "../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

#include "../../../Include/Common/Rva003BBAD3.h"

class LinearCampaignManager
{
public:
	void rva001EC981();
};
extern LinearCampaignManager *TheLinearCampaignManager;

class Rva00E02D6C
{
public:
	char m_pad[0x2D];
	bool m_flag2D;
};
extern Rva00E02D6C *TheCampaignManager;

class Rva002036A9DwordImmSetter
{
public:
	void apply();
};
extern class ScriptEngine *TheScriptEngine;

class Rva0021A54A
{
public:
	void rva0021A54A();
};
extern class CreateAHeroManager *TheCreateAHeroManager;

class Rva003BD598
{
public:
	void rva003BD598();
private:
	char m_pad[0x0C];
	unsigned char m_flagC;
};

void Rva003BD598::rva003BD598()
{
	m_flagC = 0;
	TheGameLogic->rva00376D49();
	((Rva003BBAD3 *)this)->rva003BBAD3();
	if (TheLinearCampaignManager != 0)
		TheLinearCampaignManager->rva001EC981();
	TheCampaignManager->m_flag2D = true;
	(*(Rva002036A9DwordImmSetter **)&TheScriptEngine)->apply();
	(*(Rva0021A54A **)&TheCreateAHeroManager)->rva0021A54A();
}

// Native global DFDC8C is registered as TheLinearCampaignManager by22F3A1.
