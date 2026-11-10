// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
#include "ascii_string.h"

// ?rva00420110@VictoryConditions@@QAEXXZ, retail 0x00420110, 111 bytes. HideEndGame
// plus score-screen transition: when the Apt target is present and +0x10 is
// set, invoke (void*)13 "HideEndGame" with rest 0, clear +0x10, set
// TheDisplay byte at +0x140 to 1, then when the multiplayer gate answers
// true and +0x85 is set, set the transition group to
// "MPorSkirmishFadeToScoreScreen" immediate 0.
// Target evidence: sole caller at 0x004201FA passes same this; callees are
// the rowed invoke 0x00222A8B, bfmeCall939D 0x0023C6FD, StringBase ctor
// 0x00037BA0 and setGroup 0x001DC252; layout +0x10/+0x85 matches the
// neighbouring VictoryConditions::reset class bytes.

#include "../../Include/Common/Rva00222A8BTarget.h"
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;

#include "../../Include/GameClient/Display.h"

// Display keeps its +0x140 flag protected; this unit writes it through a view
// of the real TheDisplay.
struct DisplayFlag140View
{
	char m_pad00[0x140];
	unsigned char m_140;
};

#include "GameLogicObjectLookupView.h"
class BfmeGlob939D : public GameLogic
{
public:
	char bfmeCall939D();
};
extern GameLogic *TheGameLogic;

class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler *TheTransitionHandler;

class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString groupName, bool immediate);
};

#include "../../Include/GameLogic/VictoryConditionsClass.h"

void VictoryConditions::rva00420110()
{
	if ((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager) != 0 && m_10 != 0)
	{
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke((void *)13, "HideEndGame", 0, 0, 0, 0, 0, 0);
		m_10 = 0;
		((DisplayFlag140View *)TheDisplay)->m_140 = 1;
		if (((BfmeGlob939D *)TheGameLogic)->bfmeCall939D() != 0 && m_singleAllianceRemaining != 0)
		{
			TheTransitionHandler->setGroup(AsciiString("MPorSkirmishFadeToScoreScreen"), 0);
		}
	}
}
