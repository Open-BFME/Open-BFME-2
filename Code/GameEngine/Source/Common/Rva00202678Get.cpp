// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_gamelod /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/bfme2_ascii_common /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/gamelod /Ireference/open-bfme-1/reference/shims/ini_noinline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/bfmealloc
// stlport
#include "PreRTS.h"
#include "Common/GameLOD.h"
// ?getAudioLODLevelName@GameLODManager@@QAEPBDH@Z @0x00202678 40B. WorldBuilder
// GameLOD.cpp:995 names it; the caller 0x002E53FA loads TheGameLODManager into
// ecx (the body never reads it). Indexed string getter: 0<=i<2
// returns table bfmeTabEYC[i] (0x00DB96B0), -1 returns "Unknown", else g_00BBE8E8.
// Evidence: caller 0x002E53FA passes int and uses result for StringBase::set,
// string literal 0x007D0FA4 "Unknown", table at 0x00DB96B0, default at 0x00BBE8E8.
extern const char *bfmeTabEYC[];


const char *GameLODManager::getAudioLODLevelName(int i)
{
	if (i >= 0 && i < 2)
		return bfmeTabEYC[i];
	if (i == -1)
		return "Unknown";
	return "?";
}
