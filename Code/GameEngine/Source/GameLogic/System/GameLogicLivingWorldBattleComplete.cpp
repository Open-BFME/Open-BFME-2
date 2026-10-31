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
// address-derived names; the region-manager, 0x00210DC9 and 0x00376E92
// callees are called by their rows' names (the battle through a cast of the
// row's Rva003F468D return, 0x00376E92 with its two byte flags).

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Object;

class ArmySummarySystem
{
public:
	void rva0040D280(Object*,int);
	void Save(Object *objects);
};

class Player
{
public:
	void accumulateRTSBattleStatsIntoLivingWorldScoreKeeper();
	int getArmyID() const { return livingId; }
	void *getScoreKeeperBlock() { return m_track; }

private:
	unsigned char m_pad00[0x3AC];
	int livingId;
	unsigned char m_pad3B0[0x3BC - 0x3B0];
	char m_track[0x14]; // +0x3BC
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
	void *rva003F4FBD(void*);
	int rva003F4752(void *player);
	int rva003F4FAA(int side, void *player);
	void rva003F470E(int side, int slot, void *block);
	void SetWinningSide(int side) { m_winningSide = side; }
	char m_pad00[0x38];
private:
	int m_winningSide; // +0x38
};

class Rva003F468D;

class Rva0020E6B7RegionManager
{
public:
	Rva003F468D *rva0020E6B7();
};

class Rva002E2903Player;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *outIndex);
	bool rva002B3669();
	Rva0020E6B7RegionManager *getRegionManager() const { return regions; }

private:
	unsigned char m_pad00[0xB0];
	Rva0020E6B7RegionManager *regions; // +0xB0
};

class Rva00DFE1C8Host
{
public:
	bool rva00210DC9();
	void rva00211FA8();
};
// g_00DFE1C8 is only an alias of the owned global TheLivingWorldManager (ledger names column); this unit reads the owner through its own view type.
extern class LivingWorldManager *TheLivingWorldManager;
#define g_00DFE1C8 (*(Rva00DFE1C8Host * *)&TheLivingWorldManager)

class Rva002D3627Host
{
public:
	bool getFlag18() const { return m_18 != 0; }

private:
	unsigned char m_pad00[0x18];
	unsigned char m_18;
};
class LivingWorld; extern LivingWorld *TheLivingWorld;

class Rva00210C66CmpBoolField
{
public:
	bool get() const;
};

class Rva0023D29F
{
public:
	void sendEndSessionMsg();
};

class GameLogic
{
public:
	void rva0023DA49();
	void rva0023DA4E();
	void LivingWorldTacticalBattleComplete();
	Rva003F468DParticipant *GetLivingWorldTacticalVictor();
	void clearGameData(bool a, bool b);
	void TransitionFromLivingWorldTacticalBattle();

private:
	unsigned char m_pad00[0xAC];
	Object *m_firstObject;
	unsigned char m_padB0[0x184 - 0xB0];
	ArmySummarySystem m_armySummarySystem;
	unsigned char m_pad188[0x1B0 - 0x188];
	int m_livingWorldVictorIndex;
};
extern GameLogic *TheGameLogic;

void GameLogic::LivingWorldTacticalBattleComplete()
{
	m_armySummarySystem.Save(m_firstObject);
	LivingWorldBattle *battle = (LivingWorldBattle *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->getRegionManager()->rva0020E6B7();
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
	if (g_00DFE1C8->rva00210DC9() && !((Rva002D3627Host *)TheLivingWorld)->getFlag18()) {
		GameLogic *logic = TheGameLogic;
		if (((Rva00210C66CmpBoolField *)logic)->get())
			((Rva0023D29F *)logic)->sendEndSessionMsg();
		else
			g_00DFE1C8->rva00211FA8();
	} else {
		clearGameData(true, false);
		TransitionFromLivingWorldTacticalBattle();
	}
}

// ?rva0023DA49@GameLogic@@QAEXXZ
// Retail 0x0023DA49 (5 bytes), right after LivingWorldTacticalBattleComplete:
// a tail jump into it, called on TheGameLogic from the unrowed 0x0037AB28 site.
void GameLogic::rva0023DA49()
{
	LivingWorldTacticalBattleComplete();
}

// ?rva0023DA4E@GameLogic@@QAEXXZ
// Ghidra bounds 0x0023DA4E at 43 bytes. The body gates on the rowed
// 0x002B3669 query of g_009FEF10; success pushes 1 then 0 for the pinned GameLogic helper; failure tail-calls LivingWorldTacticalBattleComplete.
void GameLogic::rva0023DA4E()
{
	if ((*(Rva002BA8F1Logic **)&TheLivingWorldLogic) && (*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->rva002B3669())
		clearGameData(false, true);
	else
		LivingWorldTacticalBattleComplete();
}
