// cl: /O1 /DNDEBUG /MD /EHsc
//
// GameLogic::GetLivingWorldTacticalVictor, retail 0x0023D884 (144B), from the
// WorldBuilder lead (name, statement order, the "could not find the current
// battle" / "could not find a winner" assertions in GameLogic.cpp). Retail
// keeps only WorldBuilder's first search: for each side of the current battle
// (region manager g_009FEF10+0xB0, 0x0020E6B7) and each participant on it
// (0x003F4DAE count, 0x003F468D entry), the participant whose +0x14 player
// index resolves (0x002A7A6F) to a player the victory conditions (g_00A03138,
// vtable slot 0x38) report victorious is returned. WorldBuilder's fallback
// searches after the first assertion are absent from retail.
//
// Target facts: the battle's side table is a vector of 0x1C-byte entries at
// +0x18; the participant entry type is not established and keeps an
// address-derived name.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
struct Rva003F468DParticipant
{
	unsigned char m_pad00[0x14];
	int m_playerIndex;
};

class Player;

class PlayerList
{
public:
	Player *Rva002A7A6F(int index);
};
extern PlayerList *ThePlayerList;

class VictoryConditionsInterface
{
public:
#define VC_SLOT(n) virtual void slot##n();
	VC_SLOT(0) VC_SLOT(1) VC_SLOT(2) VC_SLOT(3) VC_SLOT(4) VC_SLOT(5) VC_SLOT(6)
	VC_SLOT(7) VC_SLOT(8) VC_SLOT(9) VC_SLOT(10) VC_SLOT(11) VC_SLOT(12) VC_SLOT(13)
#undef VC_SLOT
	virtual bool hasAchievedVictory(Player *player); // slot 0x38
};
extern struct UnknownE03138 *g_00E03138;

struct Rva0020E6B7Side
{
	unsigned char m_pad[0x1C];
};

class Rva003F468D
{
public:
	int rva003F468D(int side, int index);
	int rva003F4DAE(int side);
	int getSideCount() const { return m_sidesEnd - m_sidesBegin; }

private:
	unsigned char m_pad00[0x18];
	Rva0020E6B7Side *m_sidesBegin;
	Rva0020E6B7Side *m_sidesEnd;
};

class Rva0020E6B7RegionManager
{
public:
	Rva003F468D *rva0020E6B7();
};

class Rva0020E6B7Logic
{
public:
	Rva0020E6B7RegionManager *getRegionManager() const { return m_regionManager; }

private:
	unsigned char m_pad00[0xB0];
	Rva0020E6B7RegionManager *m_regionManager;
};

class GameLogic
{
public:
	Rva003F468DParticipant *GetLivingWorldTacticalVictor();
};

Rva003F468DParticipant *GameLogic::GetLivingWorldTacticalVictor()
{
	Rva003F468D *battle = (*(Rva0020E6B7Logic **)&TheLivingWorldLogic)->getRegionManager()->rva0020E6B7();
	if (!battle)
		return 0;
	for (int side = 0; side < battle->getSideCount(); side++) {
		int count = battle->rva003F4DAE(side);
		for (int i = 0; i < count; i++) {
			Rva003F468DParticipant *participant = (Rva003F468DParticipant *)battle->rva003F468D(side, i);
			int index = participant->m_playerIndex;
			Player *player = ThePlayerList->Rva002A7A6F(index);
			if (player != 0 && (*(VictoryConditionsInterface **)&g_00E03138)->hasAchievedVictory(player) != 0)
				return participant;
		}
	}
	return 0;
}
