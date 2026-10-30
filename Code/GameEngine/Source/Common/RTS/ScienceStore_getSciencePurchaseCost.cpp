// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Include/Precompiled -Ireference/open-bfme-1/game/GameEngine/Source/Common/System -Ireference/open-bfme-1/game/GameEngine/Source/Common -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ivendor
//
// ?getSciencePurchaseCost@ScienceStore@@QBEHW4ScienceType@@@Z @0x1FF3DC (86B):
// findScienceInfo (matched 0x1FF3AD) plus the BFME2 online-mode gate: the
// multiplayer predicate is called first, the mode dword (+0x110) is only read
// on the false path, and modes 2/3 (with TheRecorder::isMultiplayer for a
// replay) select the alt purchase cost at +0x2C over +0x28. The conditional
// mode load is what keeps retail's `mov esi,[esi+0x110]` coalescing and the
// load below the isInMultiplayerGame branch.
#include "ScienceStoreQueryView.h"
#include "../GameLogicObjectLookupView.h"

class RecorderClass
{
public:
	bool isMultiplayer();
};

extern GameLogic *TheGameLogic;
extern RecorderClass *TheRecorder;

// ?getSciencePurchaseCost@ScienceStore@@QBEHW4ScienceType@@@Z
int ScienceStore::getSciencePurchaseCost(ScienceType st) const
{
	const ScienceInfo *si = findScienceInfo(st);
	if (si)
	{
		GameLogic *game = TheGameLogic;
		const bool mp = game->isInMultiplayerGame();
		int mode = 0;
		if (!mp)
			mode = game->m_110;
		if (mp || mode == 2 ||
		    (mode == 3 && TheRecorder && TheRecorder->isMultiplayer()))
			return si->m_sciencePurchasePointCostMP;
		return si->m_sciencePurchasePointCost;
	}
	return 0;
}
