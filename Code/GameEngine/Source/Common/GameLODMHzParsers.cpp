// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/reference/shims/ini /Ireference/open-bfme-1/reference/shims/gamelod /Ireference/open-bfme-1/reference/shims/ini_noinline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

// stlport
// Donor: BFME 1 GameLOD.cpp at 10af19f44a89ab7ecc23195bb9a842ceafbc02c9.
// Retail INI registration 0x00DB9744 pairs "ReallyLowMHz" with 0x00601E56;
// its complete [0x00201E56..0x00201E81) body parses an int and writes +0x17EC
// only when TheGameLODManager at 0x00DFE144 is nonnull. Field offset is a
// target fact; the donor supplies the parser's purpose and shared declarations.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/GameLOD.h"

void parseReallyLowMHz(INI *ini)
{
    Int mhz;
    INI::parseInt(ini, NULL, &mhz, NULL);
    if (TheGameLODManager)
        *reinterpret_cast<Int *>(reinterpret_cast<char *>(TheGameLODManager) + 0x17EC) = mhz;
}

// Retail registration 0x00DB9750 pairs "AudioLowMHz" with 0x00601E81.
// Its complete 43B body stores to +0x17F0, immediately after ReallyLowMHz.
void parseAudioLowMHz(INI *ini)
{
    Int mhz;
    INI::parseInt(ini, NULL, &mhz, NULL);
    if (TheGameLODManager)
        *reinterpret_cast<Int *>(reinterpret_cast<char *>(TheGameLODManager) + 0x17F0) = mhz;
}
