// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ?rva0040F87E@ArmySummarySystem@@QAEXXZ retail 0x0040F87E..0x0040FAFE 640 B.
// WorldBuilder twin 0x0108CF50 is ArmySummarySystem::Load (ArmySummary.cpp)
// at match score 1.0: gated by the TheGameLogic query 0x002034E9 it walks
// ThePlayerList and for each player with a living-world id copies the
// LivingWorldPlayer state (slot 3 reset on player+8 then 0x002AE252 then
// 0x003805BB / 0x002E6A93 / spell points / 0x002AC425) and grants every upgrade
// bit of the copied 1024-bit mask through TheUpgradeCenter and 0x002AE329 with
// TheGameLogic+0x98 cleared around it. Then with no active battle on
// TheLivingWorldLogic+0xB0 it resets each summary state at +0x2C (not 1) to 0
// else it loads each battle army summary whose 0x003F3F83 predicate is false
// through 0x0040F497 (WB ArmySummary::Load thiscall: mov esi,ecx). Retail
// has no al materialisation on any exit so the method returns void.
// Offsets and callee names are target evidence; class names are the twin's.

class GameLogic;
class PlayerList;
class LivingWorldLogic;
class UpgradeCenter;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern LivingWorldLogic *TheLivingWorldLogic;
extern UpgradeCenter *TheUpgradeCenter;

namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector;
}

class Rva002034E9Host { public: bool rva002034E9(); };

struct Rva0040F87EGameLogic { char pad00[0x98]; bool m_98; };

class Player;
class PlayerList
{
public:
	Player *getNthPlayer(int index);
	char pad00[0x14];
	int m_playerCount;
};

class Rva003805BB
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	bool rva003805BB(float value, bool flag);
	void rva002E6A93(int value);
};

class UpgradeTemplate { public: char pad00[0x38]; unsigned int m_bit; };
class Upgrade;
enum UpgradeStatusType { UPGRADE_STATUS_2 = 2 };

class Player
{
public:
	void rva002AE252();
	void rva002AC425(const _STL::vector<int, _STL::allocator<int> > &list);
	Upgrade *rva002AE329(const UpgradeTemplate *tmpl, UpgradeStatusType status, int flag);
	char pad00[8];
	Rva003805BB m_08;
	char pad0C[0x1c - 0xc];
	int m_1C;
	char pad20[4];
	int m_24;
	char pad28[0x3ac - 0x28];
	int m_livingWorldPlayerID;
};

struct BfmeFixedStorage128
{
	BfmeFixedStorage128(const BfmeFixedStorage128 &other);
	unsigned int m_bits[32];
};

class Rva00046827 { public: int rva00046827(); };
class Rva0026F0F0 { public: void *rva0026F0F0(const void *key); };

class Rva002E2903Player
{
public:
	char pad00[0x1c8];
	float m_1C8;
	char m_1CC[0x1d8 - 0x1cc];
	BfmeFixedStorage128 m_1D8;
};
class Rva004E05E9DwordField { public: int get() const; };

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

class LivingWorldPendingBattle;
class LivingWorldRegionManager
{
public:
	LivingWorldPendingBattle *rva0020E5BB(int id);
	char pad00[0xc];
	int m_activeBattleID;
};
struct Rva0040F87ELivingWorldLogic { char pad00[0xb0]; LivingWorldRegionManager *m_B0; };

struct Rva0040F87ERegion { char pad00[0x1c]; };
struct Rva0040F87EBattle { char pad00[0x18]; Rva0040F87ERegion *m_begin; Rva0040F87ERegion *m_end; };
class Rva003F468D { public: int rva003F4DAE(int region); };
class Rva003F4ABBOwner { public: void *indexedCall(int region, int army); };
class Rva003F4DCA { public: int rva003F4DCA(int region, int army); };
class LivingWorldBattle { public: int rva003F48FE(int region, int army, int unit); };

struct Rva0040F87EArmy { char pad00[0x20]; int m_id; };

class Rva003F3F83 { public: int rva003F3F83(); };

class ArmySummary
{
public:
	void Load(bool a, bool first, int id);
	char pad00[0x2c];
	int m_2C;
};
struct Rva0040F87EUnit { char pad00[0x78]; ArmySummary *m_summary; };

struct _Rva0040CA61Arg;

struct Rva0040F87EIntVector
{
	unsigned int size() const { return (unsigned int)(m_finish - m_start); }
	int operator[](unsigned int n) const { return m_start[n]; }
	int *m_start;
	int *m_finish;
};

class ArmySummarySystem
{
public:
	void rva0040F87E();
	int ComputePlayerEarnedSpellPoints(_Rva0040CA61Arg *player);
	void *rva0040D008(int key);

	char pad00[0x14];
	Rva0040F87EIntVector m_summaryIDs;
};

void ArmySummarySystem::rva0040F87E()
{
	if (!reinterpret_cast<Rva002034E9Host *>(TheGameLogic)->rva002034E9())
		return;

	for (int i = 0; i < ThePlayerList->m_playerCount; ++i) {
		Player *player = ThePlayerList->getNthPlayer(i);
		if (!player || player->m_livingWorldPlayerID == -1)
			continue;
		Rva002E2903Player *lwPlayer = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)
			->find(player->m_livingWorldPlayerID, 0);
		if (!lwPlayer)
			continue;

		bool *flag = &reinterpret_cast<Rva0040F87EGameLogic *>(TheGameLogic)->m_98;
		bool saved = *flag;
		*flag = false;

		player->m_08.slot3();
		player->rva002AE252();
		player->m_08.rva003805BB(lwPlayer->m_1C8, false);
		player->m_08.rva002E6A93(player->m_1C);
		int points = ComputePlayerEarnedSpellPoints(reinterpret_cast<_Rva0040CA61Arg *>(player));
		player->m_24 = reinterpret_cast<Rva004E05E9DwordField *>(lwPlayer)->get() + points;
		player->rva002AC425(*reinterpret_cast<const _STL::vector<int, _STL::allocator<int> > *>(lwPlayer->m_1CC));

		BfmeFixedStorage128 upgrades(lwPlayer->m_1D8);
		while (reinterpret_cast<Rva00046827 *>(&upgrades)->rva00046827() > 0) {
			UpgradeTemplate *tmpl = static_cast<UpgradeTemplate *>(
				reinterpret_cast<Rva0026F0F0 *>(TheUpgradeCenter)->rva0026F0F0(&upgrades));
			if (!tmpl)
				break;
			player->rva002AE329(tmpl, UPGRADE_STATUS_2, 0);
			unsigned int bit = tmpl->m_bit;
			upgrades.m_bits[bit >> 5] &= ~(1 << (bit & 0x1f));
		}

		reinterpret_cast<Rva0040F87EGameLogic *>(TheGameLogic)->m_98 = saved;
	}

	LivingWorldRegionManager *regions = reinterpret_cast<Rva0040F87ELivingWorldLogic *>(TheLivingWorldLogic)->m_B0;
	int battleID = regions->m_activeBattleID;
	if (battleID == 0) {
		for (unsigned int i = 0; i < m_summaryIDs.size(); ++i) {
			ArmySummary *summary = static_cast<ArmySummary *>(rva0040D008(m_summaryIDs[i]));
			if (summary && summary->m_2C != 1)
				summary->m_2C = 0;
		}
		return;
	}

	Rva0040F87EBattle *battle = reinterpret_cast<Rva0040F87EBattle *>(regions->rva0020E5BB(battleID));
	if (!battle)
		return;
	for (int r = 0; r < (int)(battle->m_end - battle->m_begin); ++r) {
		int armyCount = reinterpret_cast<Rva003F468D *>(battle)->rva003F4DAE(r);
		for (int a = 0; a < armyCount; ++a) {
			Rva0040F87EArmy *army = static_cast<Rva0040F87EArmy *>(
				reinterpret_cast<Rva003F4ABBOwner *>(battle)->indexedCall(r, a));
			int armyID = army ? army->m_id : 0;
			bool first = true;
			int unitCount = reinterpret_cast<Rva003F4DCA *>(battle)->rva003F4DCA(r, a);
			for (int u = 0; u < unitCount; ++u) {
				Rva0040F87EUnit *unit = reinterpret_cast<Rva0040F87EUnit *>(
					reinterpret_cast<LivingWorldBattle *>(battle)->rva003F48FE(r, a, u));
				ArmySummary *summary = unit->m_summary;
				if (summary && !(char)reinterpret_cast<Rva003F3F83 *>(summary)->rva003F3F83()) {
					summary->Load(true, first, armyID);
					first = false;
				}
			}
		}
	}
}
