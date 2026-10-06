// cl: /DNDEBUG /MD /EHsc
// ?endGame@GameInfo@@QAEXXZ @0x003FF296 (9B):
// GameInfo::endGame. BFME1 GameInfo.cpp donor verbatim minus DEBUG_ASSERTCRASH
// (compiled out under /DNDEBUG): clears inGame/inProgress at +0x10/+0x11.
// Layout from GameInfoGetSlotNum (pad 0x10 then inGame): two mov byte 0 + ret.
//
// ?rva003FF268@GameInfo@@QAEXXZ @0x003FF268 (9B): sets inGame and clears
// inProgress. Same fields as endGame; it sits just before startGame (vtable
// slot 11, 0x003FF271) and endGame, where BFME1/ZH GameInfo.cpp place
// enterGame, but the donor's reset() call is absent here (callers such as
// GameEngine::init call vtable slot 10 just before), so the pinned address
// name stays.

typedef bool Bool;

class GameInfo
{
public:
	void rva003FF268();
	void endGame();

private:
	char m_pad[0x10];
	Bool m_inGame;      // +0x10
	Bool m_inProgress;  // +0x11
};

void GameInfo::rva003FF268()
{
	m_inGame = true;
	m_inProgress = false;
}

void GameInfo::endGame()
{
	m_inGame = false;
	m_inProgress = false;
}
