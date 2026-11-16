// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/RTS3DScene.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayClass.h"

void __stdcall bfmeGoQC(void *a)
{
	W3DDisplay::m_3DScene->slot18(a);
	W3DDisplay::m_3DScene->slot19(8);
}
