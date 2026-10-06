// cl: /O1 /DNDEBUG /MD
// Player::accumulateRTSBattleStatsIntoLivingWorldScoreKeeper, retail
// 0x002A9994 (62 bytes):
// ?accumulateRTSBattleStatsIntoLivingWorldScoreKeeper@Player@@QAEXXZ
// Identity (target): WorldBuilder's debug Player.cpp:744 body of this name
// calls the living-world player lookup (0x002B51F8) then 0x004EE950 on the
// living-world player's +0x2C8 score keeper with this player's +0x3BC score
// keeper, as retail does.
// Body (target): once only (flag +0x33F, set even when the player has no
// living-world counterpart), find the living-world player by this
// player's living-world id (+0x3AC) and fold the RTS score keeper into it.
class ScoreKeeper;

class LivingWorldScoreKeeper
{
public:
	void rva004EE950(ScoreKeeper *rtsScoreKeeper);
};

class Rva002E2903Player
{
public:
	LivingWorldScoreKeeper *getScoreKeeper() { return &m_scoreKeeper; }

private:
	unsigned char m_pad000[0x2C8];
	LivingWorldScoreKeeper m_scoreKeeper; // +0x2C8
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

extern Rva002BA8F1Logic *g_009FEF10;

class ScoreKeeper
{
	unsigned char m_bytes[4];
};

class Player
{
public:
	void accumulateRTSBattleStatsIntoLivingWorldScoreKeeper();

private:
	unsigned char m_pad000[0x33F];
	bool m_accumulatedIntoLivingWorld; // +0x33F
	unsigned char m_pad340[0x3AC - 0x340];
	int m_livingWorldPlayerID; // +0x3AC
	unsigned char m_pad3B0[0x3BC - 0x3B0];
	ScoreKeeper m_scoreKeeper; // +0x3BC
};

void Player::accumulateRTSBattleStatsIntoLivingWorldScoreKeeper()
{
	if (m_accumulatedIntoLivingWorld)
		return;
	Rva002E2903Player *lwPlayer = g_009FEF10->find(m_livingWorldPlayerID, 0);
	if (lwPlayer)
		lwPlayer->getScoreKeeper()->rva004EE950(&m_scoreKeeper);
	m_accumulatedIntoLivingWorld = true;
}
