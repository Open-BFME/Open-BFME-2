// cl: /MD C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
//
// ?rva0006E5A0@RTS3DScene@@QAEXPAVVector3@@@Z @0x0006E5A0 (40B).
// Copies shadow-manager light 0 into dest via the landed getLightPosWorld.
// A thiscall member of the 3D scene: the retail caller loads ecx from
// W3DDisplay::m_3DScene (VA 0x00DE1B34) before the call (0x95658 in
// 0x953B3); the body never reads this, so the earlier __stdcall spelling
// compiled to the same 40 bytes.
// Evidence: shadow global 0x00DE5DFC with null guard; callee row @0x9A497;
// caller 0x95665 passes [ebx+0xE0]; member-wise Vector3 copy.

#include "../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

// Row name ?getLightPosWorld@W3DShadowManager@@ (ZH/BFME1 name; W3DProjectedShadow::update calls it with ECX = TheW3DShadowManager).
class W3DShadowManager
{
public:
	Vector3 &getLightPosWorld(int lightIndex);
};

class Gen0003AC38;
class W3DShadowManager; extern W3DShadowManager *TheW3DShadowManager;

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/RTS3DScene.h"

void RTS3DScene::rva0006E5A0(Vector3 *dest)
{
	W3DShadowManager *shadow = (W3DShadowManager *)(*(void **)&(*(Gen0003AC38 * *)&TheW3DShadowManager));
	if (!shadow)
		return;
	Vector3 &src = shadow->getLightPosWorld(0);
	dest->X = src.X;
	dest->Y = src.Y;
	dest->Z = src.Z;
}
