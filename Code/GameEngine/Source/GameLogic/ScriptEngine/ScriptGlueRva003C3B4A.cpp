// cl: /DNDEBUG /MD
//
// ?rva003C3B4A@Rva003BE5C9@@QAEXXZ @0x003C3B4A 51B (dump range 18).
// Sibling member of rowed 0x003BE5C9 on the same this (no ecx reload for
// the head call): runs the rowed victory emit, sets the campaign flag,
// runs the current campaign's mission-won handler through the manager
// forwarder 0x001EC981 when the manager global is set, applies
// the rowed 0x002036B4 setter, and tail-jumps the pinned 0x0021A54A
// member on the hero-manager global.
#include "../../../Include/GameLogic/Rva003BE5C9.h"

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

#include "../../../Include/GameLogic/Rva002036B4GlobalCopier.h"
class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

#include "../../../Include/GameLogic/Rva0021A54A.h"
class CreateAHeroManager;
extern CreateAHeroManager *TheCreateAHeroManager;

void Rva003BE5C9::rva003C3B4A()
{
	rva003BE5C9();
	TheCampaignManager->m_flag2D = true;
	if (TheLinearCampaignManager != 0)
		TheLinearCampaignManager->rva001EC981();
	((Rva002036B4GlobalCopier *)TheScriptEngine)->apply();
	reinterpret_cast<Rva0021A54A *>(TheCreateAHeroManager)->rva0021A54A();
}

// Native global DFDC8C is registered as TheLinearCampaignManager by22F3A1.
