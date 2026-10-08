// cl: /O1 /DNDEBUG /MD /EHsc
//
// GameLogic::LivingWorldTacticalBattleComplete, retail 0x0023D914 (309B),
// from the WorldBuilder lead (name, statement order, the battle/sideIndex/
// playerIndex/lwVictor assertions at GameLogic.cpp 8394..8436).
//
// WorldBuilder facts carried as names: ArmySummarySystem::Save (0x0040F19D,
// on the GameLogic +0x184 member with the object list), Player::
// accumulateRTSBattleStatsIntoLivingWorldScoreKeeper (0x002A9994),
// GetLivingWorldTacticalVictor (0x0023D884), sendEndSessionMsg (0x0023D29F)
// and TransitionFromLivingWorldTacticalBattle (0x0023D0CD).
//
// Target facts: every player (mask 0xFFFFF) has its stats accumulated; with a
// current battle (region manager g_009FEF10+0xB0, 0x0020E6B7) its living-world
// player (Player +0x3AC, lookup 0x002B51F8) is located on a side (0x003F4752)
// and slot (0x003F4FAA) and handed the Player +0x3BC block (0x003F470E). The
// victor's +0x14 player index (or -1) is stored at GameLogic +0x1B0 and its
// side at battle +0x38 (WorldBuilder's LivingWorldBattle::SetWinningSide,
// inlined in retail). Retail then either ends the session (singleton
// g_00DFE1C8 0x00210DC9 set and g_00DFEF18 +0x18 clear: TheGameLogic
// 0x00210C66 picks sendEndSessionMsg or g_00DFE1C8 0x00211FA8) or calls
// 0x00376E92(1, 0) and the transition. Unestablished types keep
// address-derived names.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Object;

class ArmySummarySystem
{
public:
	void Save(Object *objects);
};

class Player
{
public:
	void accumulateRTSBattleStatsIntoLivingWorldScoreKeeper();
	int getArmyID() const { return m_armyID; }
	void *getScoreKeeperBlock() { return m_scoreBlock; }

private:
	unsigned char m_pad00[0x3AC];
	int m_armyID;
	unsigned char m_pad3B0[0x3BC - 0x3B0];
	unsigned char m_scoreBlock[4];
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;

struct Rva003F468DParticipant
{
	unsigned char m_pad00[0x14];
	int m_playerIndex;
};

class LivingWorldBattle
{
public:
	int rva003F4752(void *player);
	int rva003F4FAA(int side, void *player);
	void rva003F470E(int side, int slot, void *block);
	void SetWinningSide(int side) { m_winningSide = side; }

private:
	unsigned char m_pad00[0x38];
	int m_winningSide;
};

class Rva0020E6B7RegionManager
{
public:
	LivingWorldBattle *rva0020E6B7();
};

class Rva002E2903Player;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *outIndex);
	bool rva002B3669();
	Rva0020E6B7RegionManager *getRegionManager() const { return m_regionManager; }

private:
	unsigned char m_pad00[0xB0];
	Rva0020E6B7RegionManager *m_regionManager;
};

class Rva00DFE1C8Host
{
public:
	bool rva00210DC9();
	void rva00211FA8();
};
extern Rva00DFE1C8Host *g_00DFE1C8;

class Rva002D3627Host
{
public:
	bool getFlag18() const { return m_18 != 0; }

private:
	unsigned char m_pad00[0x18];
	unsigned char m_18;
};
extern Rva002D3627Host *g_00DFEF18;

class Rva00210C66CmpBoolField
{
public:
	bool get() const;
};

class Rva0023D29F
{
public:
	void rva0023D29F();
};

class GameLogic
{
public:
	void rva0023DA4E();
	void LivingWorldTacticalBattleComplete();
	Rva003F468DParticipant *GetLivingWorldTacticalVictor();
	void rva00376E92(int a, int b);
	void TransitionFromLivingWorldTacticalBattle();

private:
	unsigned char m_pad00[0xAC];
	Object *m_objList;
	unsigned char m_padB0[0x184 - 0xB0];
	ArmySummarySystem m_armySummarySystem;
	unsigned char m_pad188[0x1B0 - 0x188];
	int m_livingWorldVictorIndex;
};
extern GameLogic *TheGameLogic;

void GameLogic::LivingWorldTacticalBattleComplete()
{
	m_armySummarySystem.Save(m_objList);
	LivingWorldBattle *battle = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager()->rva0020E6B7();
	int mask = 0xFFFFF;
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player)
			continue;
		player->accumulateRTSBattleStatsIntoLivingWorldScoreKeeper();
		void *block = player->getScoreKeeperBlock();
		if (!battle || !block)
			continue;
		Rva002E2903Player *lwPlayer = (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->find(player->getArmyID(), 0);
		if (!lwPlayer)
			continue;
		int sideIndex = battle->rva003F4752(lwPlayer);
		if (sideIndex == -1)
			continue;
		int playerIndex = battle->rva003F4FAA(sideIndex, lwPlayer);
		if (playerIndex == -1)
			continue;
		battle->rva003F470E(sideIndex, playerIndex, block);
	}
	Rva003F468DParticipant *lwVictor = GetLivingWorldTacticalVictor();
	m_livingWorldVictorIndex = lwVictor ? lwVictor->m_playerIndex : -1;
	if (battle && lwVictor)
		battle->SetWinningSide(battle->rva003F4752(lwVictor));
	if (g_00DFE1C8->rva00210DC9() && !g_00DFEF18->getFlag18()) {
		GameLogic *logic = TheGameLogic;
		if (((Rva00210C66CmpBoolField *)logic)->get())
			((Rva0023D29F *)logic)->rva0023D29F();
		else
			g_00DFE1C8->rva00211FA8();
	} else {
		rva00376E92(1, 0);
		TransitionFromLivingWorldTacticalBattle();
	}
}

// ?rva0023DA4E@GameLogic@@QAEXXZ
// Ghidra bounds 0x0023DA4E at 43 bytes. The body gates on the rowed
// 0x002B3669 query of g_009FEF10; success pushes 1 then 0 for the pinned GameLogic helper; failure tail-calls LivingWorldTacticalBattleComplete.
void GameLogic::rva0023DA4E()
{
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic) && (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B3669())
		rva00376E92(0, 1);
	else
		LivingWorldTacticalBattleComplete();
}
