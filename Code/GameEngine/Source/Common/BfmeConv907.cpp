// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DScene.h
class RTS3DScene
{
public:
	virtual void bfmeSlotQC00();
	virtual void bfmeSlotQC01();
	virtual void bfmeSlotQC02();
	virtual void bfmeSlotQC03();
	virtual void bfmeSlotQC04();
	virtual void bfmeSlotQC05();
	virtual void bfmeSlotQC06();
	virtual void bfmeSlotQC07();
	virtual void bfmeSlotQC08();
	virtual void bfmeSlotQC09();
	virtual void bfmeSlotQC10();
	virtual void bfmeSlotQC11();
	virtual void bfmeSlotQC12();
	virtual void bfmeSlotQC13();
	virtual void bfmeSlotQC14();
	virtual void bfmeSlotQC15();
	virtual void bfmeSlotQC16();
	virtual void bfmeSlotQC17();
	virtual void bfmeOneQC(void *a);
	virtual void bfmeTwoQC(int f);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayClass.h"

void __stdcall bfmeGoQC(void *a)
{
	W3DDisplay::m_3DScene->bfmeOneQC(a);
	W3DDisplay::m_3DScene->bfmeTwoQC(8);
}
