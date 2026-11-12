// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// LivingWorldRegionManager::EnumerateCompletedBattles (WorldBuilder name, line 1588: callback over the +0x20..+0x24 battle list).
// was ?rva0020E7E8@Rva0020E7E8@@QAEXPAVRva0020E7E8Callback@@@Z, retail 0x0020E7E8,
// 43 bytes.
// Pointer scan at +0x20/+0x24 calling virtual slot 0 on arg with each
// element breaking on false. Caller at 0x00576792.

#include "../../../../GameEngine/Include/GameClient/Rva0020E7E8Callback.h"

#include "../../../../GameEngine/Include/GameLogic/LivingWorldRegionManager.h"

void LivingWorldRegionManager::EnumerateCompletedBattles(Rva0020E7E8Callback *cb)
{
	void **begin = field20;
	void **end = field24;
	for (; begin != end; ++begin) {
		void *elem = *begin;
		if (!cb->invoke(elem))
			break;
	}
}
