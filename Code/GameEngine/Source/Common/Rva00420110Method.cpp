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
// neighbouring Rva0041FE86 class bytes.

class Rva00222A8BTarget
{
public:
	int invoke(void *level, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
#pragma comment(linker, "/alternatename:?TheRva00222A8BTarget@@3PAVRva00222A8BTarget@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")

class Display
{
public:
	char m_pad00[0x140];
	unsigned char m_140;
};
extern Display *TheDisplay;

class GameLogic
{
	char m_pad00[0x110];
public:
	int m_gameMode;
	bool isInMultiplayerGame();
};
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

class VictoryConditions
{
public:
	void rva00420110();
private:
	char m_pad00[0x10];
	unsigned char m_10;
	char m_pad11[0x85 - 0x11];
	unsigned char m_85;
};

void VictoryConditions::rva00420110()
{
	if ((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager) != 0 && m_10 != 0)
	{
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->invoke((void *)13, "HideEndGame", 0, 0, 0, 0, 0, 0);
		m_10 = 0;
		TheDisplay->m_140 = 1;
		if (((BfmeGlob939D *)TheGameLogic)->bfmeCall939D() != 0 && m_85 != 0)
		{
			TheTransitionHandler->setGroup(AsciiString("MPorSkirmishFadeToScoreScreen"), 0);
		}
	}
}
