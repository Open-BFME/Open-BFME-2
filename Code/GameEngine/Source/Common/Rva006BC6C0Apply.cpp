// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

// retail global: RTS3DScene *W3DDisplay::m_3DScene (0x012F8058),
// mangled ?m_3DScene@W3DDisplay@@2PAVRTS3DScene@@A.
#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/RTS3DScene.h"

#include "../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayClass.h"

class Rva006BC6C0
{
	char m_lead[4];
	RenderObjClass *m_at4;

public:
	void apply();
};

void Rva006BC6C0::apply()
{
	W3DDisplay::m_3DScene->Add_Render_Object(m_at4);
}
