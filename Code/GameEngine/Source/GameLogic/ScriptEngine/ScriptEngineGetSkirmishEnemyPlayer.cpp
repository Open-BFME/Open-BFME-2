// cl: /DNDEBUG /MD
//
// ?getSkirmishEnemyPlayer@ScriptEngine@@QAEPAVPlayer@@XZ, retail 0x00356F6E
// (65B). Identity: Zero Hour's getPlayerFromAsciiString answers
// THIS_PLAYER_ENEMY with getSkirmishEnemyPlayer, and BFME 2's player-mask
// resolver (0x00357475) calls this body on exactly that selector,
// "<This Player's Enemy>"; the shape is Zero Hour's: the current player's
// current enemy (rowed 0x002A9BBD), else the first human player in the list.
// BFME 2 drops the Generals Challenge exception and the debug crash. The
// current player is ScriptEngine+0x1A130, the player type Player+0x5C.

// The rowed getter at 0x002A9BBD keeps its address-derived spelling.
class Rva002A9BBD
{
public:
	void *rva002A9BBD();
};

class Player
{
public:
	Player *getCurrentEnemy() { return (Player *)((Rva002A9BBD *)this)->rva002A9BBD(); }
	int getPlayerType() const { return m_playerType; }

private:
	unsigned char m_pad00[0x5C];
	int m_playerType; // +0x5C
};

enum { PLAYER_HUMAN = 0 };

class PlayerList
{
public:
	int getPlayerCount() const { return m_playerCount; }
	Player *getNthPlayer(int i);

private:
	unsigned char m_pad00[0x14];
	int m_playerCount; // +0x14
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
	Player *getSkirmishEnemyPlayer();

private:
	unsigned char m_pad00[0x1A130];
	Player *m_currentPlayer; // +0x1A130
};

Player *ScriptEngine::getSkirmishEnemyPlayer()
{
	if (m_currentPlayer) {
		Player *enemy = m_currentPlayer->getCurrentEnemy();
		if (enemy == 0) {
			for (int i = 0; i < ThePlayerList->getPlayerCount(); i++) {
				enemy = ThePlayerList->getNthPlayer(i);
				if (enemy->getPlayerType() == PLAYER_HUMAN)
					return enemy;
				enemy = 0;
			}
		}
		return enemy;
	}
	return 0;
}
