// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?formatPlayerStartWaypointName@GameLogic@@QAEXPAVAsciiString@@@Z @0x24822B (77B):
// GameLogic helper that fills the starting-camera waypoint name for the local
// human slot. Retail first resolves the local slot through
// GameLogic::bfmePopulateGameReport (which also builds the session report),
// then keeps the BFME1 GameLogic.cpp:4991 shape (getSlot + isHuman guard +
// startPos+1 into Player_%d_Start). Callees getSlot/isHuman/format are rowed;
// populate is pinned until its own TU lands and supersedes the pin.
class GameInfo;
class GameSlot;
class AsciiString;

class GameLogic
{
public:
	void bfmePopulateGameReport(GameInfo *game, int *localSlot);
	void formatPlayerStartWaypointName(AsciiString *out);
};

class GameInfo
{
public:
	GameSlot *getSlot(int slot);
};

class GameSlot
{
public:
	bool isHuman() const;
	unsigned char m_pad[0x10];
	int m_startPos;
};

#include "ascii_string.h"

extern GameInfo *TheGameInfo;

// ?formatPlayerStartWaypointName@GameLogic@@QAEXPAVAsciiString@@@Z
void GameLogic::formatPlayerStartWaypointName(AsciiString *out)
{
	if (!TheGameInfo)
		return;
	int localSlot;
	bfmePopulateGameReport(TheGameInfo, &localSlot);
	GameSlot *slot = TheGameInfo->getSlot(localSlot);
	if (!slot->isHuman())
		return;
	int startPos = slot->m_startPos;
	out->format("Player_%d_Start", startPos + 1);
}
