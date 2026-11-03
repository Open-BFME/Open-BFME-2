// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?notifyOf2DSampleCompletion@MilesAudioManager@@QAEXXZ @0x000514EB 16B
// Guarded decrement at +0x684. Evidence: __thiscall via ecx plus no
// stack args plus ret; lea plus test plus jbe plus dec plus store;
// WorldBuilder 0x00797440 names the method and m_numPlaying2DSamples;
// its guarded unsigned decrement at +0x684 agrees with the whole retail body.
#include "../../../GameEngineDevice/Include/MilesAudioDevice/MilesAudioManager.h"

void MilesAudioManager::notifyOf2DSampleCompletion()
{
	unsigned *p = (unsigned *)((char *)this + 0x684);
	if (*p <= 0u)
		return;
	--(*p);
}

// WorldBuilder 0x00797510 independently names the 3D completion method
// and its unsigned counter at +0x688 (MilesAudioManager.cpp:8560).
void MilesAudioManager::notifyOf3DSampleCompletion()
{
	unsigned *p = (unsigned *)((char *)this + 0x688);
	if (*p <= 0u)
		return;
	--(*p);
}
