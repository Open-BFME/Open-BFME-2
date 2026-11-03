// cl: /MD
//
// ?postInit@AIEconomyBuilder@@QAEXXZ 27B @0x005975F7: pushes Player* at +0x14
// into global TheSkirmishAIManager's rowed rva002A8F24, then passes the returned
// pointer as this into rowed addInfoReceiver with this (as ModuleData) as arg.
// Evidence: two E8 callees with row names in packet, global VA 0x00DFEEF8,
// second callee takes PBVModuleData so owner is a ModuleData; callers at
// 0x004EBFA4 0x004EBFCD. Owner identity unproven so honest address name.

class Player;
class ModuleData;

#include "../../Include/GameLogic/Rva002A8F24.h"

extern Rva002A8F24 *TheSkirmishAIManager;

#include "../../Include/GameLogic/AIStatCollector.h"

class AIEconomyBuilder
{
public:
	void postInit();
private:
	char m_pad[0x14];
	Player *m_14;
};

void AIEconomyBuilder::postInit()
{
	void *p = TheSkirmishAIManager->rva002A8F24(m_14);
	((AIStatCollector *)p)->addInfoReceiver((const ModuleData *)this);
}
