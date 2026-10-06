// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?setPlayerType@Player@@QAEXW4PlayerType@@_N@Z @0x002A9A18 180B:
// Player::setPlayerType after the BFME1/Zero Hour donor. BFME2 also creates
// the AI for a non-computer slot when skirmish is set and the global at
// 0x00DFEEF8 has its +0x860 flag, and allocates with plain operator new
// (0x0002FDA0): AISkirmishPlayer (0xA0 bytes, ctor 0x004EF3A3) or AIPlayer
// (0x78 bytes, ctor 0x004F04FC). The old AI is destroyed through vtable slot
// 0 with flag 0 followed by operator delete 0x0002FD60. Player layout:
// m_playerType +0x5C, m_ai +0x2DC. TheAI 0x00DFF0F8: AI data +0x18,
// m_forceSkirmishAI +0x65.

class Player;

class AIPlayer
{
public:
	AIPlayer(Player *p);
	virtual ~AIPlayer();
private:
	char m_pad[0x78 - 4];
};

class AISkirmishPlayer : public AIPlayer
{
public:
	AISkirmishPlayer(Player *p);
	virtual ~AISkirmishPlayer();
private:
	char m_pad[0xA0 - 0x78];
};

struct Rva002A9A18AIData
{
	char m_pad[0x65];
	bool m_forceSkirmishAI;
};

struct Rva002A9A18AI
{
	const Rva002A9A18AIData *getAiData() const { return m_aiData; }
	char m_pad[0x18];
	Rva002A9A18AIData *m_aiData;
};
extern Rva002A9A18AI *g_00DFF0F8;

struct Rva002A9A18Global
{
	char m_pad[0x860];
	bool m_860;
};
extern Rva002A9A18Global *g_00DFEEF8;

enum PlayerType
{
	PLAYER_HUMAN,
	PLAYER_COMPUTER
};

class Player
{
public:
	void setPlayerType(PlayerType t, bool skirmish);
private:
	char m_pad00[0x5C];
	PlayerType m_playerType;
	char m_pad60[0x2DC - 0x60];
	AIPlayer *m_ai;
};

void Player::setPlayerType(PlayerType t, bool skirmish)
{
	m_playerType = t;

	if (m_ai)
	{
		::delete m_ai;
	}
	m_ai = 0;

	if (t == PLAYER_COMPUTER || (skirmish && g_00DFEEF8->m_860))
	{
		if (skirmish || g_00DFF0F8->getAiData()->m_forceSkirmishAI) {
			m_ai = new AISkirmishPlayer(this);
		} else {
			m_ai = new AIPlayer(this);
		}
	}
}
