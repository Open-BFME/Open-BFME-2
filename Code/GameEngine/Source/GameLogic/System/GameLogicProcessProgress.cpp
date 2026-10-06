// cl: /DNDEBUG /MD
//
// GameLogic::processProgress, retail 0x0023D740, 46 bytes.
// Dedicated TU so ConnectionManager.cpp cannot see this body.
// Forwards to LoadScreen at this+0x120 virtual slot 0x10 then lastHeardFrom.

class LoadScreen
{
public:
#define V(n) virtual void r##n() = 0;
	V(0) V(1) V(2) V(3)
#undef V
	virtual void processProgress(int playerId, int percentage) = 0;
};

class GameLogic
{
	char pad[0x120];
	LoadScreen *m_loadScreen;
	char pad124[4];
	unsigned char m_heardFlags[8];

public:
	void lastHeardFrom(int playerId);
	void processProgress(int playerId, int percentage);
	void rva0023D76E(int playerId);
};

void GameLogic::processProgress(int playerId, int percentage)
{
	if (m_loadScreen)
		m_loadScreen->processProgress(playerId, percentage);
	lastHeardFrom(playerId);
}
// ?rva0023D76E@GameLogic@@QAEXH@Z @0x0023D76E 37B: range-checks slot 0-7, tests byte at this+0x128, sets it and calls lastHeardFrom row 0x0023CF1C. Byte array sits just before timeout array at +0x130 proven by sibling lastHeardFrom TU. Callers at 0x004D0352 and 0x004D3095.
void GameLogic::rva0023D76E(int playerId)
{
	if (playerId < 0 || playerId >= 8)
		return;
	if (m_heardFlags[playerId] == 1)
		return;
	m_heardFlags[playerId] = 1;
	lastHeardFrom(playerId);
}
