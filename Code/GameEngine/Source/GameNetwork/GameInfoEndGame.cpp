// cl: /O1 /DNDEBUG /MD /EHsc
// ?endGame@GameInfo@@QAEXXZ @0x003FF296 (9B):
// GameInfo::endGame. BFME1 GameInfo.cpp donor verbatim minus DEBUG_ASSERTCRASH
// (compiled out under /DNDEBUG): clears inGame/inProgress at +0x10/+0x11.
// Layout from GameInfoGetSlotNum (pad 0x10 then inGame): two mov byte 0 + ret.

typedef bool Bool;

class GameInfo
{
public:
	void enterGame();
	void endGame();

private:
	char m_pad[0x10];
	Bool m_inGame;      // +0x10
	Bool m_inProgress;  // +0x11
};

// ?enterGame@GameInfo@@QAEXXZ @0x003FF268 (9B): WorldBuilder names it
// GameInfo::enterGame (GameInfo.cpp, assert line 721 "Entering game at a bad
// time!", compiled out here): sets inGame, clears inProgress. Same shape in the
// BFME1 GameInfo.cpp donor.
void GameInfo::enterGame()
{
	m_inGame = true;
	m_inProgress = false;
}

void GameInfo::endGame()
{
	m_inGame = false;
	m_inProgress = false;
}
