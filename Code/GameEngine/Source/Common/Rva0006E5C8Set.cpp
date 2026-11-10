// cl: /MD /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?rva0006E5C8@RTS3DScene@@QAEXPAVVector3@@@Z @0x0006E5C8 (61B).
// Sets shadow-manager light 0 from src then clears volumetric shadow list.
// A thiscall member of the 3D scene: every retail caller loads ecx from
// W3DDisplay::m_3DScene (VA 0x00DE1B34) before the call (0x983C2 in 0x982F9);
// the body itself never reads this, so the earlier __stdcall spelling compiled
// to the same 61 bytes.
// Evidence: shadow global 0x00DE5DFC with null guard plus callee pin @0x9A587
// setLightPosition; second global 0x00DEBCD8 with null guard plus row @0xF0912;
// callers at 0x9549A 0x955B1 0x9567F in 0x953B3 and 0x983CF in 0x982F9.

#include "../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

class W3DGameClientShadowShim
{
public:
	void setLightPosition(int lightIndex, float x, float y, float z);
};

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DVolumetricShadowManager.h"

class Gen0003AC38;
class W3DShadowManager; extern W3DShadowManager *TheW3DShadowManager;
extern class W3DVolumetricShadowManager *TheW3DVolumetricShadowManager;

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/RTS3DScene.h"

void RTS3DScene::rva0006E5C8(Vector3 *src)
{
	W3DGameClientShadowShim *shadow = (W3DGameClientShadowShim *)(*(void **)&(*(Gen0003AC38 * *)&TheW3DShadowManager));
	if (shadow == 0)
		return;
	shadow->setLightPosition(0, src->X, src->Y, src->Z);
	if (TheW3DVolumetricShadowManager != 0)
		TheW3DVolumetricShadowManager->invalidateCachedLightPositions();
}
