// ?rva0051BED7@Rva0051BED7@@QAE_NXZ
// partial score=0.95 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc
//
// Retail 0x0051BED7, 80 bytes: polled one-shot flag at this+0x27E. When
// set, clears it and, unless a multiplayer game with mode fields +0x114==3
// and +0x110==2 is up (setting this+0x27D then), runs the rowed free
// enabler at 0x0051B09B through a this-shaped call (aliased below) or the
// pinned 0x0051B90B otherwise. Always returns true.

class GameLogic
{
public:
	bool isInMultiplayerGame();

private:
	unsigned char m_pad[0x110];

public:
	int m_110; // game mode: 1 LAN, 5 internet (rowed isInMultiplayerGame)
	int m_114;
};

extern GameLogic *TheGameLogic;

void rva0051B90B();

class Rva0051BED7
{
public:
	bool rva0051BED7();
	void rva0051B09B();

private:
	unsigned char m_pad[0x27D];
	unsigned char m_27d;
	unsigned char m_27e;
};

// Retail passes this in ecx to the free enabler, so the method spelling
// stands in for it; the address is the rowed 0x0051B09B body.
#pragma comment(linker, "/alternatename:?rva0051B09B@Rva0051BED7@@QAEXXZ=?Rva0051B09BEnable@@YAXXZ")

bool Rva0051BED7::rva0051BED7()
{
	if (m_27e)
	{
		m_27e = false;
		GameLogic *gameLogic = TheGameLogic;
		if (!gameLogic->isInMultiplayerGame() && gameLogic->m_114 == 3)
		{
			if (gameLogic->m_110 == 2)
				m_27d = true;
			rva0051B90B();
		}
		else
			rva0051B09B();
	}
	return true;
}
