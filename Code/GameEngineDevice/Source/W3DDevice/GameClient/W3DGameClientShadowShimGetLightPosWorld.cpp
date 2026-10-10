// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ?getLightPosWorld@W3DShadowManager@@QAEAAVVector3@@H@Z @0x0009A497 (13B; formerly rowed
// under the W3DGameClientShadowShim view name).
// BFME1 donor W3DShadowManager::getLightPosWorld (W3DShadow.cpp:289) moved from
// global LightPosWorld to a member at +0xC; this+12+index*12 codegen matches
// retail inc/imul/add. Evidence: shadow global 0x00DE5DFC at all 6 call sites
// (0x6E5A0 0xF1212 0xF3192 0x1074D5 0x1094E2); +0xC store in setLightPosition
// pin @0x9A587; callers use result as 3-float Vector3.

#include "vector3.h"

// Row name ?getLightPosWorld@W3DShadowManager@@ (ZH/BFME1 name; W3DProjectedShadow::update calls it with ECX = TheW3DShadowManager).
class W3DShadowManager
{
public:
	Vector3 &getLightPosWorld(int lightIndex);
private:
	unsigned char m_unk00[12];
	Vector3 m_lightPos[1];
};

Vector3 &W3DShadowManager::getLightPosWorld(int lightIndex)
{
	return m_lightPos[lightIndex];
}
