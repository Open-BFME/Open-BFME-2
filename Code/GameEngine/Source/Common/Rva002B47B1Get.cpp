// cl: /MD
// ?getStartingMoney@LivingWorldLogic@@QAEHXZ @0x002B47B1 18B.
// Unlock chase through global 0x00E02D6C LivingWorldCampaignManager index/array plus +0x40
// field. Caller 0x002B075A supplies TheLivingWorldLogic in ECX;
// the return is deposited as an int into Player money. Receiver is unused
// by these retail bytes. Original getter name remains unknown. Evidence: same global/index/array shape as rowed LivingWorldCampaignManager
// in Rva003B8BAALookup.cpp, caller at 0x002B075A, prev/next same dir.
struct Rva002B47B1Elem
{
	char m_pad[0x40];
	int m_startingMoney;
};
#include "../../Include/Common/LivingWorldCampaignManager.h"
// TheCampaignManager (0x00E02D6C): matched references place it at VA 0xe02d6c (retail .data initial value 0).
class Rva00E02D6C;
Rva00E02D6C *TheCampaignManager = 0;
#include "../../Include/GameLogic/LivingWorldLogic.h"

int LivingWorldLogic::getStartingMoney()
{
	LivingWorldCampaignManager *campaignManager = ((LivingWorldCampaignManager *)TheCampaignManager);
	return ((Rva002B47B1Elem *)campaignManager->field14[campaignManager->field10])->m_startingMoney;
}
