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

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class ScoreKeeper;

// ObjectCountMap is a 12-byte tree header. The stride is explicit in the
// indexed map accessor at 0x0039C3AC and the shape agrees with the matched
// ScoreKeeper map counter at 0x0039BEC3.
struct ObjectCountMap
{
	void *m_header;
	int m_pad04;
	int m_pad08;
};

class LivingWorldScoreKeeper
{
public:
	void rva004EE950(ScoreKeeper *rtsScoreKeeper);

private:
	unsigned char m_pad000[0x74];
	unsigned int m_scoreTotal; // +0x74, incremented by 0x0039B718
	unsigned char m_pad078[0x3C];
	ObjectCountMap m_primaryMap;   // +0xB4
	ObjectCountMap m_secondaryMap; // +0xC0
	ObjectCountMap m_indexedMap;   // +0xCC, receives twenty source maps
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

class ScoreKeeper
{
	unsigned char m_bytes[4];
};

class Rva0039B709
{
public:
	unsigned int rva0039B718();
};

class Rva0039C3AC
{
public:
	ObjectCountMap *rva0039C3AC(int index);
};

extern void __cdecl rva004EE8B8(ObjectCountMap *destination, ObjectCountMap *source);

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
	Rva002E2903Player *lwPlayer = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(m_livingWorldPlayerID, 0);
	if (lwPlayer)
		lwPlayer->getScoreKeeper()->rva004EE950(&m_scoreKeeper);
	m_accumulatedIntoLivingWorld = true;
}

// Identity (target): called on the living-world player's +0x2C8 score keeper
// with Player's +0x3BC ScoreKeeper by the matched accumulation path above.
// Layout (target): adds the rowed 0x0039B718 value at +0x74; merges source maps
// at +0x1F0 and +0x2EC into +0xB4 and +0xC0; then folds the twenty maps returned
// by 0x0039C3AC into the single map at +0xCC. The helper's exact name is kept
// address-derived at 0x004EE8B8.
void LivingWorldScoreKeeper::rva004EE950(ScoreKeeper *rtsScoreKeeper)
{
	m_scoreTotal += ((Rva0039B709 *)rtsScoreKeeper)->rva0039B718();
	rva004EE8B8(&m_primaryMap, (ObjectCountMap *)((char *)rtsScoreKeeper + 0x1F0));
	rva004EE8B8(&m_secondaryMap, (ObjectCountMap *)((char *)rtsScoreKeeper + 0x2EC));
	Rva0039C3AC *scoreMaps = (Rva0039C3AC *)rtsScoreKeeper;
	for (int i = 0; i < 20; ++i)
		rva004EE8B8(&m_indexedMap, scoreMaps->rva0039C3AC(i));
}
