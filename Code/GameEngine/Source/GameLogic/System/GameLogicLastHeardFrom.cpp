// cl: /O1 /DNDEBUG /MD
//
// GameLogic::lastHeardFrom, retail 0x0023CF1C, 35 bytes.
// Dedicated TU so GameLogicProcessProgress.cpp cannot see this body.
// Timeout stamp array sits at this+0x130; MAX_SLOTS is 8.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

class GameLogic
{
	char pad[0x130];
	unsigned long m_progressCompleteTimeout[8];

public:
	void lastHeardFrom(int playerId);
};

void GameLogic::lastHeardFrom(int playerId)
{
	if (playerId < 0 || playerId >= 8)
		return;
	m_progressCompleteTimeout[playerId] = timeGetTime();
}
