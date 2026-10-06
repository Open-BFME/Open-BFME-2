// cl: /DNDEBUG /MD /EHsc

// ?isInMultiplayerGame@GameLogic@@QAE_NXZ @0x42235 (23B):
// GameLogic::isInMultiplayerGame, ZH GameLogic.h:404 verbatim shape
// (m_gameMode at +0x110 is GAME_LAN(1) or GAME_INTERNET(5)). B2 carries it
// out-of-line (ZH inlines it); 43 image-wide callers including
// ScienceStore::getSciencePurchaseCost. Leaf, no pins.

class GameLogic
{
	char m_pad[0x110];
public:
	int m_gameMode;
	bool isInMultiplayerGame();
};

// ?isInMultiplayerGame@GameLogic@@QAE_NXZ
bool GameLogic::isInMultiplayerGame()
{
	return m_gameMode == 1 || m_gameMode == 5;
}
