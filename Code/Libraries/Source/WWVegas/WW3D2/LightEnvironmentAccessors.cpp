// cl: /Ireference/shims/bfme2lightenv /Ob2 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// LightEnvironmentClass's inline per-light accessors, out of line.
//
// Retail keeps eight int3-padded 23-byte bodies at 0x0011C320..0x0011C400,
// each `this + i*0x54 + k` with k = 0x14, 0x2C, 0x39, 0x48, 0x4C, 0x5C, 0x50,
// 0x3C. Against the BFME2 layout shim (leading byte, LightCount at +0x04,
// InputLights[] of 0x54-byte InputLightStruct at +0x14) those are, in address
// order, exactly the header's declaration order: Get_Light_Direction,
// Get_Light_Diffuse, isPointLight, getPointIrad, getPointOrad,
// getPointDiffuse, getPointAmbient, getPointCenter. Zero Hour's layout puts
// every member four bytes lower, which is why a ZH-header compile had placed
// getPointOrad on getPointIrad's body. No retail call reaches any of the
// eight; the identities rest on that offset/order agreement alone.
#include "lightenvironment.h"

// The accessors are header inlines; the anchor makes this unit emit its
// copies for the rows. It is not retail code.
#pragma inline_depth(0)
// ?_bfmeLightEnvironmentAccessorAnchor@@YAXPBVLightEnvironmentClass@@@Z absent-from-retail
void _bfmeLightEnvironmentAccessorAnchor(const LightEnvironmentClass *env)
{
	env->Get_Light_Direction(0);
	env->Get_Light_Diffuse(0);
	env->isPointLight(0);
	env->getPointIrad(0);
	env->getPointOrad(0);
	env->getPointDiffuse(0);
	env->getPointAmbient(0);
	env->getPointCenter(0);
}
#pragma inline_depth()
