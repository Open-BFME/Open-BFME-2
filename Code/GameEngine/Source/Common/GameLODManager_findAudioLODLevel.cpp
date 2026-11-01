// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_gamelod /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/gamelod /Ireference/open-bfme-1/reference/shims/ini_noinline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc
// stlport
#include "PreRTS.h"
#include "Common/GameLOD.h"
//
// ?findAudioLODLevel@GameLODManager@@QBEHXZ @0x002026A0 20B. WorldBuilder
// GameLOD.cpp:1002 names it GameLODManager::findAudioLODLevel. Compare ints at +0x17d8
// and +0x17f0 returning 0/1. Evidence: retail mov eax [ecx+0x17d8] plus xor
// edx edx plus cmp eax [ecx+0x17f0] plus setge dl plus mov eax edx plus ret;
// same 0x17xx object as 0x00202633 (+0x176c) and 0x00202790 (+0x1770); caller
// 0x00518F1D in 0x00518D2B.

int GameLODManager::findAudioLODLevel() const
{
	return *(int *)((char *)this + 0x17d8) >= *(int *)((char *)this + 0x17f0);
}
