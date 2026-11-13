// cl: /O1 /arch:SSE /G7 /MD
// ?rva002BED10@Rva002BED10@@QAEXXZ @0x002BED10 89B unlock 2 ready.
// Evidence: 7 callers; rowed HideControlBar 0x00402960; TheLivingWorldLogic TheGameLogic TheLivingWorldManager externs; rowed clear 0x0023D2D8 via GameLogic+0 clearer member; pin-only 0x0021427A; virtuals +0x28 +0x4c +0x1c +0x18 tail; prev Rva002BECCDCalls next InlineDtor.
void HideControlBar(bool b);
#include "../../Include/GameLogic/LivingWorldLogic.h"
extern LivingWorldLogic *TheLivingWorldLogic;
#include "../../Include/Common/Rva0023D2D8DwordClearer.h"
#include "GameLogicObjectLookupView.h"

// The canonical GameLogic header pads over the fields read here; they
// are reached through a view of the real TheGameLogic.
struct GameLogicFieldView
{
	Rva0023D2D8DwordClearer m_clear;
};
extern GameLogic *TheGameLogic;
#include "../../Include/GameLogic/LivingWorldManager.h"
extern LivingWorldManager *TheLivingWorldManager;
#include "../../Include/Common/Rva002BED10.h"
void Rva002BED10::rva002BED10()
{
	v10(0);
	v19(1, 1);
	v7();
	HideControlBar(true);
	if (TheLivingWorldLogic)
	{
		TheLivingWorldLogic->init();
		if (TheGameLogic)
			((GameLogicFieldView *)TheGameLogic)->m_clear.clear();
	}
	if (TheLivingWorldManager)
		TheLivingWorldManager->rva0021427A();
	v6();
}
