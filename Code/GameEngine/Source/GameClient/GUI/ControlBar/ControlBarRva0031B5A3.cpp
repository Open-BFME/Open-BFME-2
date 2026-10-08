// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva0031B5A3@ControlBar@@QAEXPBVPlayer@@@Z @0x0031B5A3 106B ControlBar arrow group refresh for local player.
// Evidence: isLocalPlayer rowed 0x002A9D89; money via ThePlayerList 0x009FEEE8 plus 0x10 plus 0x24 vs +0x27C; TheTransitionHandler 0x00DFDC14 null plus TheInGameUI 0x009FEDF0 bytes 0x15 0x16; ControlBarArrow literal via rowed StringBase ctor 0x00037BA0 plus setGroup rowed 0x001DC252; sets +0x278 and +0x28; callers 0x002A9F95 0x002A9FED 0x002A9FFE; neighbours share /O1.
#include "ascii_string.h"

class Player
{
public:
	bool isLocalPlayer() const;
};

struct MoneyInner
{
	char m_pad00[0x24];
	int m_money;
};

class PlayerList
{
public:
	char m_pad00[0x10];
	MoneyInner *m_p0010;
};

extern PlayerList *ThePlayerList;

class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler *TheTransitionHandler;

class InGameUI
{
public:
	char m_pad00[0x15];
	unsigned char m_15;
	unsigned char m_16;
};

extern InGameUI *TheInGameUI;

class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString groupName, bool immediate);
};

class ControlBar
{
public:
	void rva0031B5A3(const Player *player);
private:
	char m_pad00[0x28];
	unsigned char m_0028;
	char m_pad29[0x270 - 0x29];
	const void *m_p0270;
	const void *m_p0274;
	unsigned char m_0278;
	char m_pad279[0x27c - 0x279];
	int m_027C;
};

void ControlBar::rva0031B5A3(const Player *player)
{
	if (!player->isLocalPlayer())
		return;
	{
		int money = ThePlayerList->m_p0010->m_money;
		if (m_027C > money)
			goto done;
	}
	if (TheTransitionHandler == 0)
		goto done;
	if (TheInGameUI->m_15 == 0)
		goto done;
	if (TheInGameUI->m_16 == 0)
		goto done;
	TheTransitionHandler->setGroup(AsciiString("ControlBarArrow"), 0);
done:
	m_0278 = 1;
	m_0028 = 1;
}
