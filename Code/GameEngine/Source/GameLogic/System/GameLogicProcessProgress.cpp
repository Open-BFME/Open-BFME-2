// cl: /O1 /DNDEBUG /MD
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

public:
	void lastHeardFrom(int playerId);
	void processProgress(int playerId, int percentage);
};

void GameLogic::processProgress(int playerId, int percentage)
{
	if (m_loadScreen)
		m_loadScreen->processProgress(playerId, percentage);
	lastHeardFrom(playerId);
}
