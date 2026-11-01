// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /MD
// platformsdk
// ?Rva0044C277Wait@@YA_NXZ @0x0044C277 79B.
// Timed GameInfo readiness poll; packet proves the calls to the target readiness
// checks, timeout reset helper, and the TheGameInfo global.

#include <windows.h>
#include "../../Include/GameNetwork/GameInfo.h"

extern GameInfo *TheGameInfo;
void Rva0044C205Reset();

bool Rva0044C277Wait()
{
	unsigned long start = timeGetTime();
	for (;;)
	{
		if (TheGameInfo == 0 || TheGameInfo->rva003FF457())
			return true;
		Rva0044C205Reset();
		if (timeGetTime() > start + 0x4E20)
			break;
	}
	for (int slot = 0; slot < 8; ++slot)
		TheGameInfo->isHeroDataReadyForSlot(slot);
	return false;
}
