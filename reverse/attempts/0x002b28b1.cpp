// ?armyMoveRequest@LivingWorldLogic@@QAEXPAULivingWorldArmy@@PAVRva00318C32Ret@@PBVCoord2D@@H@Z
// partial score=0.98 date=2026-10-08
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include <vector>
#include <map>

class LivingWorldPlayer;
class LivingWorldLogic;

LivingWorldLogic *TheLivingWorldLogic = 0;

class Rva002B74DE
{
public:
	Rva002B74DE(LivingWorldLogic *logic, Int battle);	// 0x002BD40D
	~Rva002B74DE();						// 0x002B74DE
	Int Update();						// 0x002BB7D6, 1 when done

private:
	unsigned char m_data[0x28];
};

class Rva002B90B3
{
public:
	void reset(Rva002B74DE *resolver);			// 0x002B90B3
	Rva002B74DE *get() const { return m_ptr; }

private:
	Rva002B74DE *m_ptr;
};

class Rva002E2903Player
{
public:
	void rva002E2D8D(void *army);				// 0x002E2D8D
};

class AsciiString;
class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(Int playerID, UnsignedInt *index);	// 0x002B51F8
	Rva002E2903Player *find(const AsciiString &name, UnsignedInt *index);	// 0x002B6AEC
	struct Rva002B488EResult *rva002B488E(Int armyID);	// 0x002B488E, WB LivingWorldLogic::findArmy
	struct Rva002B2579Result *rva002B2579(int id);	// 0x002B2579
	struct Rva002B3740Item *rva002B2B2D();	// 0x002B2B2D
private:
	char m_pad00[0xB0];
	void *m_containerB0;	// +0xB0
	int m_padB4;
	int m_keyB8;	// +0xB8
};

struct LivingWorldUpgradeArmy
{
	unsigned char m_pad000[0x13c];
	Int m_playerID;						// +0x13C, -1 when unowned
};

struct Rva002B5334Base
{
	unsigned char m_pad00[0x2c];
};

struct Rva002B5334ArmyList
{
	_STL::vector<LivingWorldUpgradeArmy *> m_armies;
};

struct Rva002B5334ArmySet : public Rva002B5334Base, public Rva002B5334ArmyList
{
};

#include "../../../../../Libraries/Include/Lib/Coord2D.h"

class LivingWorldRegionManager
{
public:
	Bool GetRegionCenterPoint(Int regionID, Coord2D *out);	// 0x0020F27E
	Bool GetRegionCenterPoint(class Rva0020E89C *region, Coord2D *out);
	class Rva00318C32Ret *rva0020FAEA(const Coord2D *pos, class Rva00318C32Ret *hint);
	void rva0020FB8B(class LivingWorldBattle *battle);	// 0x0020FB8B, ends the battle (pinned)
	void UpdateBattleMarkers();				// 0x0020EBA0 (WorldBuilder name, pinned)
	Int ValidateArmyRegionEntry(struct LivingWorldArmy *army, class Rva00318C32Ret *from, class Rva00318C32Ret *to, Int a, Int b);

	unsigned char m_pad00[0x8];
	Rva002B5334ArmySet *m_armySet;				// +0x08
	unsigned char m_pad0C[0x14 - 0xc];
	_STL::vector<void *> m_field14;				// +0x14
private:
	class Rva0020E89C *rva0020EAF6(int key);		// 0x0020EAF6, pinned
	friend class Rva002BA8F1Logic;
};

class Rva002B4B3D
{
public:
	Bool rva002B4B3D();					// 0x002B4B3D
};

class Rva002B3288
{
public:
	Bool rva002B3288();					// 0x002B3288
};

class Rva002B9099
{
public:
	void clear();						// 0x002B9099
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);	// 0x0007DEEF

class Rva004E0632;

class ArmySummaryEntry
{
public:
	void MarkForUpgrades(const Rva004E0632 *upgrades);	// 0x0040C430
	void CancelUpgrades();					// 0x0040C45C

	Int getMoveTarget() const { return m_moveTarget; }

	unsigned char m_pad00[0xac];
	unsigned char m_padAC[0xb8 - 0xac];
	Int m_moveTarget;					// +0xB8
	unsigned char m_padBC[0xc4 - 0xbc];
	Bool m_disbanded;					// +0xC4, set by DisbandArmyMember
};

struct ArmySummaryEntryRef
{
	~ArmySummaryEntryRef()
	{
		if (m_entry)
			ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)((char *)m_entry + 0xac));
	}

	ArmySummaryEntry *m_entry;
};

class ArmySummary
{
public:
	ArmySummaryEntryRef GetEntry(Int entryID);		// 0x0040CBD7
};

struct LivingWorldArmy
{
	void initiateMove(const Coord2D &pos, class Rva00318C32Ret *target, Int flags);

	unsigned char m_pad00[0x20];
	Int m_id;						// +0x20 (WB LivingWorldArmy::GetID, inlined)
	unsigned char m_pad24[0x54 - 0x24];
	Int m_ownerPlayer;					// +0x54
	unsigned char m_pad58[0x74 - 0x58];
	Bool m_field74;						// +0x74, set: left alone by EnforceArmyRegionOwnership
	unsigned char m_pad75[0x78 - 0x75];
	ArmySummary *m_summary;					// +0x78
};

class Rva002B616FListener
{
public:
	virtual void slot00();
	virtual void onTurnChanged(void *oldTurn, int newTurn);	// +0x04
};

class Rva002B616FList
{
public:
	void forEach(void (Rva002B616FListener::*notify)(void *, int), void *arg, int value);	// 0x002B616F

private:
	unsigned char m_data[0x10];
};

class Rva002B7BFB
{
public:
	void rva002B7BFB();					// 0x002B7BFB
};

class Rva003B8BAA
{
public:
	void *rva003B8BAA();					// 0x003B8BAA, see CanDisbandArmyMember
	void rva003B8CAC();					// 0x003B8CAC
};

class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

class LivingWorldCampaignManager
{
public:
	void *UseGenericSpawnArmyForPlayer(Int a, Int b);	// 0x003B8CE0
};

struct Rva002B8660Army
{
	unsigned char m_pad00[0x4c];
	Int m_id;						// +0x4C
};

struct Rva002B8660Player
{
	unsigned char m_pad00[0x14];
	Int m_id;						// +0x14
};

class ModuleData;

class Rva004E0632Filter
{
public:
	virtual void slot00();
	virtual Bool accepts(ArmySummaryEntry *entry);		// +0x04
};

class Rva004E0632
{
public:
	Int rva004E0632() const;				// 0x004E0632
};

class Rva003F287F
{
public:
	void rva003F28DB(_STL::vector<const ModuleData *> &out);	// 0x003F28DB

	unsigned char m_pad000[0x12c];
	Int m_regionID;						// +0x12C
	unsigned char m_pad130[0x13c - 0x130];
	Int m_ownerPlayer;					// +0x13C
};

struct DelayedRegionVictory
{
	Int player;
	Int regionID;
	UnsignedInt flags;
};

struct PrereqUnitRec
{
	unsigned int m_data[3];
	~PrereqUnitRec() {}
};

class Xfer
{
public:
	class Version
	{
	public:
		Version(unsigned char current, unsigned char minimum) : m_current(current), m_minimum(minimum) {}
		unsigned char m_current;
		unsigned char m_minimum;
	};

	virtual void slot00();
	virtual Bool IsLoading() const;				// +0x04
	virtual void slot08();
	virtual Bool IsCRC() const;				// +0x0C
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual Xfer &XferRawBytes(void *data, UnsignedInt size);	// +0x24
	virtual Xfer &xferVersion(Version &value);		// +0x28
	virtual void slot2C();
	virtual Xfer &xferSnapshot(void *snapshot);		// +0x30, operator==(Snapshot &)
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual Xfer &xferInt(Int &value);			// +0x7C
};
void XferLivingWorldPlayerID(Xfer *xfer, int *playerID);	// 0x002034C4
struct Rva003EFE82Obj;
int __cdecl Rva003EFE82Get(Rva003EFE82Obj *obj, void *out);	// 0x003EFE82, "LivingWorldRegionID"
struct Rva002B24F0Obj;
int __cdecl Rva002B24F0Get(Rva002B24F0Obj *obj, void *out);	// 0x002B24F0, "LivingWorldRegionVictoryFlags"

template <class T> class StringBase
{
public:
	void set(const StringBase &that);			// 0x000366F0
	bool isEmpty() const;					// 0x00001E2F
	StringBase &operator=(const StringBase &that) { set(that); return *this; }

private:
	T *m_data;
};
struct Rva003F0F13Elem
{
	float a;
	float b;
};
struct Rva0059E647Entry;
class LivingWorldRegion
{
public:
	void GetGarrisonArmyPlacementSpot(Rva003F0F13Elem *out);	// 0x003F0F13
	void *rva003F0588();					// 0x003F0588, the free building slot
	void rva003F2A8C(Int playerID);				// 0x003F2A8C, owner change
	void rva003EFE72(void *slot, Rva0059E647Entry *buildingTemplate);	// 0x003EFE72, captured placement
	void BuildBuilding(void *slot, Rva0059E647Entry *buildingTemplate);	// 0x003F1C56

	unsigned char m_pad000[0x13c];
	Int m_ownerPlayer;					// +0x13C
};
class Rva004E3184
{
public:
	Rva004E3184(void *arg);					// 0x004E30D5
	virtual ~Rva004E3184();					// 0x004E3184

	StringBase<char> m_name;				// +0x04
	unsigned char m_pad08[0x20 - 0x8];
	Rva003F0F13Elem m_pos;					// +0x20
	unsigned char m_pad28[0x54 - 0x28];
	Bool m_flag54;						// +0x54
	unsigned char m_pad55[0x58 - 0x55];
};
struct Rva002B6A04Template
{
	unsigned char m_pad00[0x24];
	StringBase<char> m_name24;				// +0x24
	unsigned char m_pad28[0x34 - 0x28];
	StringBase<char> m_name34;				// +0x34
};
struct Rva002B6A04Player
{
	unsigned char m_pad00[0x40];
	Rva002B6A04Template *m_template;			// +0x40
};
struct Rva002B6A04Summary
{
	unsigned char m_pad00[0x64];
	StringBase<char> m_name64;				// +0x64
};
void *__stdcall Rva002B4948Find(void *player, void *region, void *arg);	// 0x002B4948

struct Rva002B2858Coord
{
	Rva002B2858Coord() {}
	Rva002B2858Coord(const Rva002B2858Coord &that) : x(that.x), y(that.y) {}
	~Rva002B2858Coord() {}
	float x;
	float y;
};

class Rva002BA82BBase00
{
public:
	virtual void slot00();

private:
	unsigned char m_pad04[0x10 - 0x4];
};

class Rva002BA82BObserver10
{
public:
	virtual void slot00();
};

class Rva002BA82BRegionObserver
{
public:
	virtual void OnRegionChangedOwnership(LivingWorldRegion *region, Int oldOwnerID, Int newOwnerID) = 0;
};

class LivingWorldLogic : public Rva002BA82BBase00, public Rva002BA82BObserver10, public Rva002BA82BRegionObserver
{
public:
	virtual void OnRegionChangedOwnership(LivingWorldRegion *region, Int oldOwnerID, Int newOwnerID);

	const Rva004E0632 *GetArmoryToUpgradeTroop(ArmySummaryEntry *entry, LivingWorldArmy *army, Rva003F287F *region);
	void ValidatePlayers();
	Bool EndTurn();
	Bool AdvanceTurnPhase();
	Bool IsCurrentTurnPhaseFinished();
	void processArmyDestroyList();
	void MarkTroopForUpgrades(Int entryID, LivingWorldArmy *army, const Rva004E0632 *upgrades);
	void CancelTroopUpgrades(Int entryID, LivingWorldArmy *army);
	void StartAutoResolveBattle(Int battle);
	void AutoResolveBattle(Int battle);
	void AutoMarkUnitsForUpgrades();
	void CalcAttackingDirection(const _STL::vector<Int> &path, Coord2D *direction);
	Bool CanMoveArmyMember(LivingWorldArmy *army, Int entryID, Int target);
	Bool rva002B8019(LivingWorldArmy *army, ArmySummaryEntry *entry, Int target);	// 0x002B8019
	void LetAIResolveRegionAwardDispute(Int regionID, const _STL::vector<Int> &players, UnsignedInt flags);
	Rva002B8660Army *UseGenericSpawnArmyForPlayer(Int a, Rva002B8660Player *player);
	Bool CanMoveArmyMember_internal(LivingWorldArmy *army, ArmySummaryEntry *entry, LivingWorldArmy *target, Bool checkRoom);
	Int rva002B2C12(LivingWorldArmy *army, LivingWorldArmy *target);
	void GetNumUpgradeableTroopsInRegionForPlayer(Rva003F287F *region, Int player, Int *countA, Int *countB);
	void EnforceArmyRegionOwnership();
	Bool rva002B27B5(LivingWorldArmy *army, Rva00318C32Ret *target);
	void rva002B26D0(LivingWorldArmy *army, Rva00318C32Ret *target, Rva002B2858Coord pos, Int flags);
	Rva002B2858Coord AdjustArmyMoveTargetPos(Rva00318C32Ret *target, const Coord2D *pos);	// 0x002B2858, pinned
	void armyMoveRequest(LivingWorldArmy *army, Rva00318C32Ret *target, const Coord2D *pos, Int flags);
	void rva002B2834(LivingWorldArmy *army, Int flags);
	void XferDelayedRegionVictories(Xfer *xfer);
	void XferPlayers(Xfer *xfer);
	void AwardOwnershipSetsToPlayers();
	LivingWorldArmy *spawnArmy(Rva004E3184 *spawn, Rva002B6A04Player *player, Bool flag);	// 0x002B65B7, pinned
	LivingWorldArmy *CreateEmptyGarrisonArmy(Rva002B6A04Player *player, LivingWorldRegion *region);
	void *rva002B4948(void *player, LivingWorldRegion *region, Int arg);	// 0x002B4948 (rowed as the stdcall Rva002B4948Find)
	void spawnBuilding(const struct Rva002B99F8Request *request);
	Bool rva002B5CBB(const struct Rva002B4C35Player *player);
	void GameLogic_tacticalBattleComplete();
	void OnBattleComplete(class LivingWorldBattle *battle);
	void rva002B9A90(Int regionID, const _STL::vector<Int> &players, UnsignedInt flags);	// 0x002B9A90
	void rva002B37FF(class LivingWorldBattle *battle);	// 0x002B37FF
	void PrepareBattleForLoading(class LivingWorldBattle *battle);

private:
	void AddDelayedRegionVictory(Rva003F287F *region, Int player, UnsignedInt flags);	// 0x002B9B42
	void CheckTurnPhaseTransitions();		// 0x002BD23E
	void rva002B5B55(void *army);			// 0x002B5B55, destroys one army

	unsigned char m_pad18[0x1c - 0x18];
	Rva002B616FList m_turnListeners;		// +0x1C
	unsigned char m_pad2C[0x3c - 0x2c];
	Rva002B616FList m_battleListeners;		// +0x3C, told (logic, battle) when a battle completes
	unsigned char m_pad4C[0x8c - 0x4c];
	_STL::vector<LivingWorldPlayer *> m_players;	// +0x8C
	LivingWorldPlayer *m_localPlayer;		// +0x98 (WB member name)
	unsigned char m_pad9C[0xb0 - 0x9c];
	LivingWorldRegionManager *m_field0B0;		// +0xB0, region manager
	unsigned char m_padB4[0xb6 - 0xb4];
	Bool m_fieldB6;					// +0xB6, set when a tactical battle completes
	unsigned char m_padB7[0xb8 - 0xb7];
	Int m_fieldB8;					// +0xB8, the battle region index, reset to -1
	unsigned char m_padBC[0xcc - 0xbc];
	_STL::vector<void *> m_fieldCC;			// +0xCC
	unsigned char m_padD8[0xf4 - 0xd8];
	Int m_turnPhase;				// +0xF4 (WB member name)
	unsigned char m_padF8[0xfc - 0xf8];
	Int m_turn;					// +0xFC
	UnsignedInt m_field100;				// +0x100
	UnsignedInt m_field104;				// +0x104
	Bool m_field108;				// +0x108
	Bool m_field109;				// +0x109
	unsigned char m_pad10A[0x10c - 0x10a];
	_STL::vector<void *> m_field10C;		// +0x10C
	_STL::vector<void *> m_armyDestroyList;		// +0x118
	unsigned char m_pad124[0x130 - 0x124];
	_STL::map<Int, class RegionAwardDispute *> m_regionAwardDisputes;	// +0x130
	_STL::multimap<Int, Int> m_spawnedArmies;	// +0x13C, generic army id -> player id
	_STL::vector<DelayedRegionVictory> m_delayedRegionVictories;	// +0x148 (WB member name)
	unsigned char m_pad154[0x178 - 0x154];
	Rva002B90B3 m_autoBattleResolver;		// +0x178 (WB member name)
};

enum { TURN_PHASE_LAST_ADVANCEABLE = 6 };

Bool LivingWorldLogic::EndTurn()
{
	if (TURN_PHASE_LAST_ADVANCEABLE == m_turnPhase)
	{
		((Rva002B7BFB *)this)->rva002B7BFB();
		Int turn = m_turn;
		m_turnListeners.forEach(&Rva002B616FListener::onTurnChanged, (void *)turn, turn + 1);
		m_turnPhase = 0;
		m_field104 = m_field100;
		m_field108 = false;
		m_field109 = false;
		m_turn++;
		((Rva003B8BAA *)TheCampaignManager)->rva003B8CAC();
		CheckTurnPhaseTransitions();
		return true;
	}
	return false;
}

Bool LivingWorldLogic::AdvanceTurnPhase()
{
	if (!IsCurrentTurnPhaseFinished() || m_turnPhase >= TURN_PHASE_LAST_ADVANCEABLE)
		return false;
	m_turnPhase = m_turnPhase + 1;
	m_field104 = m_field100;
	CheckTurnPhaseTransitions();
	return true;
}

void LivingWorldLogic::ValidatePlayers()
{
	if (m_players.size() == 0)
		return;
	if (m_localPlayer == 0)
		m_localPlayer = m_players[0];
}

void LivingWorldLogic::LetAIResolveRegionAwardDispute(Int regionID, const _STL::vector<Int> &players, UnsignedInt flags)
{
	if (players.empty())
		return;
	flags |= 0x20;
	AddDelayedRegionVictory((Rva003F287F *)regionID, players[0], flags);
}

void LivingWorldLogic::processArmyDestroyList()
{
	for (UnsignedInt i = 0; i < m_armyDestroyList.size(); ++i)
		rva002B5B55(m_armyDestroyList[i]);
	m_armyDestroyList.clear();
}

void LivingWorldLogic::MarkTroopForUpgrades(Int entryID, LivingWorldArmy *army, const Rva004E0632 *upgrades)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return;
	entry.m_entry->MarkForUpgrades(upgrades);
}

void LivingWorldLogic::CancelTroopUpgrades(Int entryID, LivingWorldArmy *army)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return;
	entry.m_entry->CancelUpgrades();
}

void LivingWorldLogic::StartAutoResolveBattle(Int battle)
{
	m_autoBattleResolver.reset(new Rva002B74DE(this, battle));
}

void LivingWorldLogic::AutoResolveBattle(Int battle)
{
	m_autoBattleResolver.reset(new Rva002B74DE(this, battle));
	while (m_autoBattleResolver.get()->Update() != 1)
		;
	((Rva002B9099 *)&m_autoBattleResolver)->clear();
}

// ?LivingWorldLogic::AutoMarkUnitsForUpgrades present-unmatched
void LivingWorldLogic::AutoMarkUnitsForUpgrades()
{
	Rva002B5334ArmyList *list = m_field0B0->m_armySet;
	for (UnsignedInt i = 0; i < list->m_armies.size(); ++i)
	{
		LivingWorldUpgradeArmy *army = list->m_armies[i];
		if (army->m_playerID != -1)
		{
			Rva002E2903Player *player = ((Rva002BA8F1Logic *)this)->find(army->m_playerID, 0);
			player->rva002E2D8D(army);
		}
	}
}

Bool LivingWorldLogic::CanMoveArmyMember(LivingWorldArmy *army, Int entryID, Int target)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return false;
	return rva002B8019(army, entry.m_entry, target);
}

Bool LivingWorldLogic::IsCurrentTurnPhaseFinished()
{
	switch (m_turnPhase)
	{
		case 0:
			return m_fieldCC.empty();
		case 1:
		case 5:
			return !((Rva002B4B3D *)this)->rva002B4B3D();
		case 2:
			return !(m_field0B0->m_field14.size() > 0);
		case 3:
			return m_field100 >= m_field104 + 1;
		case 4:
			return m_field10C.empty() || ((Rva002B3288 *)this)->rva002B3288();
		case 6:
			return true;
	}
	return false;
}

struct HeroEntryKey;

class AttackOrdersMember
{
public:
	ArmySummaryEntryRef rva0031996D(const HeroEntryKey &key);	// 0x0031996D

	unsigned char m_pad00[0x18];
	HeroEntryKey &key() { return *(HeroEntryKey *)m_key; }

private:
	unsigned char m_key[4];					// +0x18
};

template <class T> inline const T &maxOf(const T &a, const T &b)
{
	return (a < b) ? b : a;
}

class AttackOrders
{
public:
	Int GetMaxHeroLeaderRank();

private:
	unsigned char m_pad00[0x8];
	_STL::vector<AttackOrdersMember *> m_members;		// +0x08
};

Int AttackOrders::GetMaxHeroLeaderRank()
{
	Int maxRank = 0;
	for (UnsignedInt i = 0; i < m_members.size(); ++i)
	{
		AttackOrdersMember *member = m_members[i];
		ArmySummaryEntryRef heroEntry = member->rva0031996D(member->key());
		if (heroEntry.m_entry)
		{
			Int rank = *(const Int *)((const char *)heroEntry.m_entry + 0xc);
			maxRank = maxOf(maxRank, rank);
		}
	}
	return maxRank;
}

// ?LivingWorldLogic::CalcAttackingDirection present-unmatched
void LivingWorldLogic::CalcAttackingDirection(const _STL::vector<Int> &path, Coord2D *direction)
{
	Int last = path.size() - 1;
	Int previous = path.size() - 2;
	if (last < 0 || previous < 0)
	{
		last = 0;
		previous = 0;
	}
	Coord2D from, to;
	m_field0B0->GetRegionCenterPoint(path[last], &from);
	m_field0B0->GetRegionCenterPoint(path[previous], &to);
	*direction = to;
	direction->x -= from.x;
	direction->y -= from.y;
}

class Rva0040CB3AIndexedField
{
public:
	Int get(Int index) const;				// 0x0040CBB8
};

class Rva002B254F
{
public:
	Int rva002B254F();					// 0x002B254F
};

class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;

class Rva003B8BAAEntryVet
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual Bool vetEntry(ArmySummaryEntry *entry);		// +0x08
};

struct ThingTemplateKindOf
{
	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[4];				// +0x108

	Bool isKindOf(Int bit) const { return (m_kindOf[bit >> 5] >> (bit & 31)) & 1; }
};

class AsciiString;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *name);	// 0x002D06CA, TheThingFactory->findTemplate
};

extern Rva002D06CA *g_00DFF000;

class Rva004525B0String
{
public:
	Int compare(const Rva004525B0String &that) const;	// 0x000069D6
};

class Rva0037DCA5;
class Rva003193EC
{
public:
	bool rva00319413(Rva0037DCA5 *entry);			// 0x00319413
};



static Bool CanDisbandArmyMember(ArmySummaryEntry *entry)
{
	if ((unsigned char)((Rva002B254F *)TheLivingWorldLogic)->rva002B254F() != 0)
	{
		if (!((Rva003B8BAAEntryVet *)((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA())->vetEntry(entry))
			return 0;
	}
	if (entry->m_disbanded)
		return 0;
	const ThingTemplateKindOf *thing = (const ThingTemplateKindOf *)g_00DFF000->rva002D06CA((const AsciiString *)((char *)entry + 4));
	if (thing == 0)
		return 0;
	if (thing->isKindOf(90))
		return 0;
	return 1;
}

Bool CanDisbandArmyMember(LivingWorldArmy *army, Int entryID)
{
	Rva0040CB3AIndexedField *summary = (Rva0040CB3AIndexedField *)army->m_summary;
	ArmySummaryEntry *entry = (ArmySummaryEntry *)summary->get(entryID);
	return entry != 0 && CanDisbandArmyMember(entry);
}

void DisbandArmyMember(LivingWorldArmy *army, Int entryID)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	ArmySummaryEntry *bound = entry.m_entry;
	if (bound != 0 && CanDisbandArmyMember(bound))
	{
		entry.m_entry->m_disbanded = 1;
		entry.m_entry->CancelUpgrades();
	}
}

union GameMessageArgumentType
{
	Int integer;
};

class GameMessage
{
public:
	const GameMessageArgumentType *getArgument(Int argIndex) const;	// 0x0030F4EA
	UnsignedInt getArgumentCount() const { return m_argCount; }

private:
	unsigned char m_pad00[0x18];
	unsigned char m_argCount;				// +0x18
};

static inline Bool validateMessageArgumentIndex(const GameMessage *msg, Int argIndex)
{
	return argIndex >= 0 && argIndex < (Int)msg->getArgumentCount();
}

static inline Bool validateArmySummaryEntryID(Int entryID, LivingWorldArmy *army)
{
	Rva0040CB3AIndexedField *summary = (Rva0040CB3AIndexedField *)army->m_summary;
	Int entry = summary->get(entryID);
	return entry != 0;
}

static __declspec(noinline) Bool getArmyFromMessage(LivingWorldArmy **army, const GameMessage *msg, Int argIndex)
{
	if (!validateMessageArgumentIndex(msg, argIndex))
		return 0;
	Int armyID = msg->getArgument(argIndex)->integer;
	*army = (LivingWorldArmy *)((Rva002BA8F1Logic *)((Rva002B254F *)TheLivingWorldLogic))->rva002B488E(armyID);
	return *army != 0;
}

static __declspec(noinline) Bool getArmySummaryEntryIDFromMessage(Int *entryID, const GameMessage *msg, Int argIndex, LivingWorldArmy *army)
{
	if (!validateMessageArgumentIndex(msg, argIndex))
		return 0;
	*entryID = msg->getArgument(argIndex)->integer;
	return validateArmySummaryEntryID(*entryID, army);
}

void HandleUnmarkUnitForUpgradeMessage(const GameMessage *msg)
{
	LivingWorldArmy *army;
	Int entryID;
	if (getArmyFromMessage(&army, msg, 0)
		&& getArmySummaryEntryIDFromMessage(&entryID, msg, 1, army))
		((LivingWorldLogic *)((Rva002B254F *)TheLivingWorldLogic))->CancelTroopUpgrades(entryID, army);
}

class Rva00318C32Ret;

class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();				// 0x00318C32
};

void HandleMarkUnitForUpgradeMessage(const GameMessage *msg)
{
	LivingWorldArmy *army;
	if (!getArmyFromMessage(&army, msg, 0))
		return;
	Rva00318C32Ret *region = ((Rva00318C79Owner *)army)->rva00318C32();
	if (region == 0)
		return;
	Int entryID;
	if (!getArmySummaryEntryIDFromMessage(&entryID, msg, 1, army))
		return;
	ArmySummaryEntryRef entry = army->m_summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return;
	const Rva004E0632 *upgrades = ((LivingWorldLogic *)((Rva002B254F *)TheLivingWorldLogic))->GetArmoryToUpgradeTroop(entry.m_entry, army, (Rva003F287F *)region);
	if (upgrades != 0)
		((LivingWorldLogic *)((Rva002B254F *)TheLivingWorldLogic))->MarkTroopForUpgrades(entryID, army, upgrades);
}

const Rva004E0632 *LivingWorldLogic::GetArmoryToUpgradeTroop(ArmySummaryEntry *entry, LivingWorldArmy *army, Rva003F287F *region)
{
	if ((void *)((Rva00318C79Owner *)army)->rva00318C32() != (void *)region)
		return 0;
	if (army->m_ownerPlayer != region->m_ownerPlayer)
		return 0;
	if (entry->getMoveTarget() != 0)
		return 0;
	_STL::vector<const ModuleData *> armories;
	region->rva003F28DB(armories);
	for (UnsignedInt i = 0; i < armories.size(); ++i)
	{
		const Rva004E0632 *armory = (const Rva004E0632 *)armories[i];
		if (((Rva004E0632Filter *)armory->rva004E0632())->accepts(entry))
			return armory;
	}
	return 0;
}

Rva002B8660Army *LivingWorldLogic::UseGenericSpawnArmyForPlayer(Int a, Rva002B8660Player *player)
{
	Rva002B8660Army *army = (Rva002B8660Army *)((LivingWorldCampaignManager *)TheCampaignManager)->UseGenericSpawnArmyForPlayer(a, (Int)player);
	if (army)
		m_spawnedArmies.insert(_STL::make_pair(army->m_id, player->m_id));
	return army;
}

void LivingWorldLogic::AddDelayedRegionVictory(Rva003F287F *region, Int player, UnsignedInt flags)
{
	for (UnsignedInt i = 0; i < m_delayedRegionVictories.size(); ++i)
	{
		if (m_delayedRegionVictories[i].regionID == region->m_regionID)
			return;
	}
	DelayedRegionVictory victory;
	victory.player = player;
	victory.regionID = region->m_regionID;
	victory.flags = flags;
	((_STL::vector<PrereqUnitRec> *)&m_delayedRegionVictories)->push_back(*(const PrereqUnitRec *)&victory);
}

Int LivingWorldLogic::rva002B2C12(LivingWorldArmy *army, LivingWorldArmy *target)
{
	return m_field0B0->ValidateArmyRegionEntry(army, ((Rva00318C79Owner *)army)->rva00318C32(), ((Rva00318C79Owner *)target)->rva00318C32(), 0, 0);
}

Bool LivingWorldLogic::CanMoveArmyMember_internal(LivingWorldArmy *army, ArmySummaryEntry *entry, LivingWorldArmy *target, Bool checkRoom)
{
	if (((const Rva004525B0String *)((char *)entry + 4))->compare(*(const Rva004525B0String *)((char *)army + 0x18)) == 0)
		return false;
	if (entry->getMoveTarget() != 0)
	{
		if (entry->getMoveTarget() != target->m_id)
		{
			LivingWorldArmy *oldSourceArmy = (LivingWorldArmy *)((Rva002BA8F1Logic *)this)->rva002B488E(entry->getMoveTarget());
			if (oldSourceArmy == 0)
				return false;
			Int result = rva002B2C12(oldSourceArmy, target);
			Bool valid = result >= 0 && result <= 1;
			if (!valid)
				return false;
		}
	}
	else
	{
		Int result = rva002B2C12(army, target);
		Bool valid = result >= 0 && result <= 1;
		if (!valid)
			return false;
	}
	if (checkRoom && !((Rva003193EC *)target)->rva00319413((Rva0037DCA5 *)entry))
		return false;
	return true;
}

class Rva002B6E8AUpgrade
{
public:
	virtual Int count00();
	virtual void slot04();
	virtual Int count08();
};

void LivingWorldLogic::GetNumUpgradeableTroopsInRegionForPlayer(Rva003F287F *region, Int player, Int *countA, Int *countB)
{
	*countA = 0;
	*countB = 0;
	if (region->m_ownerPlayer != player)
		return;
	_STL::vector<const ModuleData *> armories;
	region->rva003F28DB(armories);
	for (UnsignedInt i = 0; i < armories.size(); ++i)
	{
		Rva002B6E8AUpgrade *upgrade = (Rva002B6E8AUpgrade *)((const Rva004E0632 *)armories[i])->rva004E0632();
		*countA += upgrade->count08();
		*countB += upgrade->count00();
	}
}

struct Rva002B4C35Player
{
	unsigned char m_pad00[0x14];
	Int m_id;						// +0x14
	unsigned char m_pad18[0x1b8 - 0x18];
	_STL::vector<LivingWorldArmy *> m_armies;		// +0x1B8
};

class Refresh0023FA80AI;
class Refresh0023FA80Object;
class Refresh0023FA80Primary
{
public:
	void scheduleNullable(Refresh0023FA80AI *ai, Refresh0023FA80Object *obj);	// 0x002B388D
};
class Rva0031912E
{
public:
	Int rva0031912E();					// 0x0031912E
};

void LivingWorldLogic::EnforceArmyRegionOwnership()
{
	for (UnsignedInt i = 0; i < m_players.size(); ++i)
	{
		Rva002B4C35Player *player = (Rva002B4C35Player *)m_players[i];
		_STL::vector<LivingWorldArmy *> &armies = player->m_armies;
		for (UnsignedInt j = 0; j < armies.size(); ++j)
		{
			LivingWorldArmy *army = armies[j];
			if (army->m_field74)
				continue;
			Rva003F287F *region = (Rva003F287F *)((Rva00318C79Owner *)army)->rva00318C32();
			if (region == 0)
				continue;
			if (region->m_ownerPlayer == -1)
				((Refresh0023FA80Primary *)this)->scheduleNullable((Refresh0023FA80AI *)region, (Refresh0023FA80Object *)player);
			else if (region->m_ownerPlayer != player->m_id)
				((Rva0031912E *)army)->rva0031912E();
		}
	}
}

class Rva002B27B5Campaign
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual Bool canArmyMoveTo(LivingWorldArmy *army, Rva00318C32Ret *target);	// +0x10
};

Bool LivingWorldLogic::rva002B27B5(LivingWorldArmy *army, Rva00318C32Ret *target)
{
	Int result = m_field0B0->ValidateArmyRegionEntry(army, ((Rva00318C79Owner *)army)->rva00318C32(), target, 0, 0);
	Bool valid = result >= 0 && result <= 1;
	if (valid)
	{
		if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0)
		{
			Rva002B27B5Campaign *campaign = (Rva002B27B5Campaign *)((Rva003B8BAA *)TheCampaignManager)->rva003B8BAA();
			return campaign->canArmyMoveTo(army, target);
		}
		return true;
	}
	return false;
}

// ?LivingWorldLogic::rva002B26D0 present-unmatched
void LivingWorldLogic::rva002B26D0(LivingWorldArmy *army, Rva00318C32Ret *target, Rva002B2858Coord pos, Int flags)
{
	if (army == 0 || target == 0)
		return;
	if (((Rva00318C79Owner *)army)->rva00318C32() == target)
		return;
	army->initiateMove(*(const Coord2D *)&pos, target, flags);
}

struct Arg54;
class Rva002B280C
{
public:
	bool rva002B280C(Arg54 *army);				// 0x002B280C
};
class Rva00319831
{
public:
	void rva00319831(Int flags);				// 0x00319831
};

void LivingWorldLogic::rva002B2834(LivingWorldArmy *army, Int flags)
{
	if (army == 0)
		return;
	if (!((Rva002B280C *)this)->rva002B280C((Arg54 *)army))
		return;
	((Rva00319831 *)army)->rva00319831(flags);
}

// ?LivingWorldLogic::armyMoveRequest present-unmatched
void LivingWorldLogic::armyMoveRequest(LivingWorldArmy *army, Rva00318C32Ret *target, const Coord2D *pos, Int flags)
{
	if (m_turnPhase != 0 && m_turnPhase != 4)
		return;
	if (((Rva00318C79Owner *)army)->rva00318C32() == 0)
	{
		rva002B26D0(army, target, AdjustArmyMoveTargetPos(target, pos), flags);
	}
	else if (rva002B27B5(army, target))
	{
		rva002B2834(army, flags);
		if (((Rva00318C79Owner *)army)->rva00318C32() != target)
			rva002B26D0(army, target, AdjustArmyMoveTargetPos(target, pos), flags);
	}
}

void LivingWorldLogic::XferDelayedRegionVictories(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	xfer->xferVersion(version);
	if (xfer->IsLoading())
	{
		Int count;
		xfer->xferInt(count);
		for (Int i = 0; i < count; ++i)
		{
			Int playerID;
			XferLivingWorldPlayerID(xfer, &playerID);
			Rva002E2903Player *player = ((Rva002BA8F1Logic *)this)->find(playerID, 0);
			Int regionID;
			Rva003EFE82Get((Rva003EFE82Obj *)xfer, &regionID);
			UnsignedInt flags = 0;
			if (version.m_minimum >= 2)
				Rva002B24F0Get((Rva002B24F0Obj *)xfer, &flags);
			if (player != 0 && regionID != -1)
			{
				DelayedRegionVictory victory;
				victory.player = (Int)player;
				victory.regionID = regionID;
				victory.flags = flags;
				((_STL::vector<PrereqUnitRec> *)&m_delayedRegionVictories)->push_back(*(const PrereqUnitRec *)&victory);
			}
		}
	}
	else
	{
		Int count = m_delayedRegionVictories.size();
		xfer->xferInt(count);
		for (Int i = 0; i < count; ++i)
		{
			Int playerID = ((Rva002B4C35Player *)m_delayedRegionVictories[i].player)->m_id;
			XferLivingWorldPlayerID(xfer, &playerID);
			Int regionID = m_delayedRegionVictories[i].regionID;
			Rva003EFE82Get((Rva003EFE82Obj *)xfer, &regionID);
			UnsignedInt flags = m_delayedRegionVictories[i].flags;
			Rva002B24F0Get((Rva002B24F0Obj *)xfer, &flags);
		}
	}
}

struct Rva002BA8F1Listener;
class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *listener);		// 0x005A0B4C
	unsigned char m_pad[0x14];
};
class Rva002E277A
{
public:
	Rva002E277A();						// 0x002E277A
	unsigned char m_pad000[0x4];
	Rva005A0B4CList m_observers;				// +0x04
	unsigned char m_pad018[0x3c8 - 0x18];
};
struct Rva002BAA3DBase18
{
	unsigned char m_pad00[0x18];
};
struct Rva002BA8F1Listener
{
	void *m_vtbl;
};
struct Rva002BAA3DLogic : public Rva002BAA3DBase18, public Rva002BA8F1Listener
{
};

void LivingWorldLogic::XferPlayers(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	xfer->xferVersion(version);
	if (xfer->IsLoading())
	{
		Int count;
		xfer->xferInt(count);
		((_STL::vector<void *> *)&m_players)->clear();
		((_STL::vector<const ModuleData *> *)&m_players)->reserve(count);
		for (Int i = 0; i < count; ++i)
		{
			Rva002E277A *player = new Rva002E277A;
			xfer->xferSnapshot(player);
			((_STL::vector<const ModuleData *> *)&m_players)->push_back(*(const ModuleData **)&player);
			player->m_observers.append((Rva002BA8F1Listener *)(Rva002BAA3DLogic *)this);
		}
		Int localPlayerID;
		xfer->XferRawBytes(&localPlayerID, 4);
		m_localPlayer = (LivingWorldPlayer *)((Rva002BA8F1Logic *)this)->find(localPlayerID, 0);
	}
	else
	{
		Int count = m_players.size();
		xfer->xferInt(count);
		for (Int i = 0; i < count; ++i)
			xfer->xferSnapshot(m_players[i]);
		if (!xfer->IsCRC())
		{
			Int id = m_localPlayer ? ((Rva002B4C35Player *)m_localPlayer)->m_id : -1;
			Int localPlayerID = id;
			xfer->XferRawBytes(&localPlayerID, 4);
		}
	}
}

class Rva002B7582Sets
{
public:
	void rva004FD699(void *baseRegion, _STL::vector<const ModuleData *> *regions);	// 0x004FD699
	void rva004FCA11(void *baseRegion, Rva002E2903Player *player);	// 0x004FCA11
};
struct Rva002B7582Campaign
{
	Rva002B7582Sets *GetOwnershipSets() const { return m_ownershipSets; }

	unsigned char m_pad00[0x1c];
	Rva002B7582Sets *m_ownershipSets;			// +0x1C
};
struct Rva002B7582CampaignManager
{
	Rva002B7582Campaign *GetCurrentCampaign() { return m_campaigns[m_campaignIndex]; }

	unsigned char m_pad00[0x10];
	Int m_campaignIndex;					// +0x10
	_STL::vector<Rva002B7582Campaign *> m_campaigns;	// +0x14
};
class Rva002104B6
{
public:
	void *rva002104B6(void *name);				// 0x002104B6
};

void LivingWorldLogic::AwardOwnershipSetsToPlayers()
{
	Rva002B7582Sets *sets = ((Rva002B7582CampaignManager *)TheCampaignManager)->GetCurrentCampaign()->GetOwnershipSets();
	if (sets == 0)
		return;
	_STL::vector<const ModuleData *> regions;
	for (UnsignedInt i = 0; i < m_players.size(); ++i)
	{
		Rva002E2903Player *player = (Rva002E2903Player *)m_players[i];
		if (player == 0)
			continue;
		void *baseRegion = ((Rva002104B6 *)m_field0B0)->rva002104B6((char *)player + 0x2c);
		if (baseRegion == 0)
			continue;
		((_STL::vector<void *> *)&regions)->clear();
		sets->rva004FD699(baseRegion, &regions);
		for (UnsignedInt j = 0; j < regions.size(); ++j)
		{
			const ModuleData *region = regions[j];
			((Refresh0023FA80Primary *)this)->scheduleNullable((Refresh0023FA80AI *)region, (Refresh0023FA80Object *)player);
		}
		sets->rva004FCA11(baseRegion, player);
	}
}

struct Rva002B2579Result;
struct Rva002B3740Item;
class Rva0020EEF4Outer
{
public:
	int rva0020EEF4(int id);
};

Rva002B2579Result *Rva002BA8F1Logic::rva002B2579(int id)
{
	if (id == 0)
		return 0;
	return (Rva002B2579Result *)((Rva0020EEF4Outer *)m_containerB0)->rva0020EEF4(id);
}

Rva002B3740Item *Rva002BA8F1Logic::rva002B2B2D()
{
	return (Rva002B3740Item *)((LivingWorldRegionManager *)m_containerB0)->rva0020EAF6(m_keyB8);
}

LivingWorldArmy *LivingWorldLogic::CreateEmptyGarrisonArmy(Rva002B6A04Player *player, LivingWorldRegion *region)
{
	LivingWorldArmy *army = (LivingWorldArmy *)rva002B4948(player, region, 0);
	if (army == 0)
	{
		Rva004E3184 spawn(0);
		spawn.m_flag54 = false;
		spawn.m_name.set(player->m_template->m_name24);
		Rva003F0F13Elem spot;
		region->GetGarrisonArmyPlacementSpot(&spot);
		spawn.m_pos = spot;
		army = spawnArmy(&spawn, player, true);
		Rva002B6A04Template *playerTemplate = player->m_template;
		Rva002B6A04Summary *summary = (Rva002B6A04Summary *)army->m_summary;
		summary->m_name64 = playerTemplate->m_name34;
	}
	return army;
}

class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *other) const;	// 0x002E071E
	Int rva002E0BC0(Int playerID);				// 0x002E0BC0
};
class Rva002B8A9F
{
public:
	void rva002B8A9F(ModuleData *army);			// 0x002B8A9F
};

void LivingWorldLogic::OnRegionChangedOwnership(LivingWorldRegion *region, Int oldOwnerID, Int newOwnerID)
{
	const Rva002E071E *newOwner = (const Rva002E071E *)((Rva002BA8F1Logic *)this)->find(newOwnerID, 0);
	if (newOwnerID != -1)
	{
		for (UnsignedInt i = 0; i < m_players.size(); ++i)
		{
			LivingWorldPlayer *player = m_players[i];
			if (newOwner->rva002E071E((const Rva002E071E *)player))
				CreateEmptyGarrisonArmy((Rva002B6A04Player *)player, region);
		}
	}
	if (oldOwnerID != -1)
	{
		if (newOwner != 0 && (unsigned char)((Rva002E071E *)newOwner)->rva002E0BC0(oldOwnerID) != 0)
			return;
		for (UnsignedInt i = 0; i < m_players.size(); ++i)
		{
			LivingWorldPlayer *player = m_players[i];
			if (newOwner != 0 && !newOwner->rva002E071E((const Rva002E071E *)player))
			{
				void *army = rva002B4948(player, region, 0);
				if (army != 0)
					((Rva002B8A9F *)this)->rva002B8A9F((ModuleData *)army);
			}
		}
	}
}

class AsciiString;
struct Rva002B99F8Request
{
	void *m_vtbl;
	unsigned char m_player[4];				// +0x04, AsciiString
	Int m_templateToken;					// +0x08
	unsigned char m_region[4];				// +0x0C, AsciiString
	Bool m_captured;					// +0x10
};

struct Rva0059E647Factory
{
	Rva0059E647Entry *Lookup(Int *token);			// 0x002B931C
};
extern Rva0059E647Factory *g_rva0059E647Factory;

void LivingWorldLogic::spawnBuilding(const Rva002B99F8Request *request)
{
	Rva002104B6 *regions = (Rva002104B6 *)TheLivingWorldLogic->m_field0B0;
	LivingWorldRegion *region = (LivingWorldRegion *)regions->rva002104B6((void *)request->m_region);
	Rva0059E647Entry *buildingTemplate = g_rva0059E647Factory->Lookup((Int *)&request->m_templateToken);
	Rva002B4C35Player *player = (Rva002B4C35Player *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(*(const AsciiString *)request->m_player, 0);
	void *slot = region->rva003F0588();
	if (slot == 0)
		return;
	if (request->m_captured)
	{
		if (region->m_ownerPlayer != player->m_id)
			region->rva003F2A8C(player->m_id);
		region->rva003EFE72(slot, buildingTemplate);
	}
	else
	{
		region->BuildBuilding(slot, buildingTemplate);
	}
}

Rva002B2858Coord LivingWorldLogic::AdjustArmyMoveTargetPos(Rva00318C32Ret *target, const Coord2D *pos)
{
	Rva002B2858Coord adjusted;
	if (m_field0B0->rva0020FAEA(pos, target) != target)
		m_field0B0->GetRegionCenterPoint((Rva0020E89C *)target, (Coord2D *)&adjusted);
	else
	{
		adjusted.x = pos->x;
		adjusted.y = pos->y;
	}
	return adjusted;
}

class RegionAwardDispute
{
public:
	Int GetResolvableBy();					// 0x004FBED6

	unsigned char m_pad00[0x1c];
	Bool m_resolved;					// +0x1C
};

Bool LivingWorldLogic::rva002B5CBB(const Rva002B4C35Player *player)
{
	_STL::map<Int, RegionAwardDispute *>::iterator it = m_regionAwardDisputes.begin();
	_STL::map<Int, RegionAwardDispute *>::iterator end = m_regionAwardDisputes.end();
	for (; it != end; ++it)
	{
		RegionAwardDispute *dispute = (*it).second;
		if (!dispute->m_resolved)
		{
			Int playerID = player->m_id;
			if (dispute->GetResolvableBy() == playerID)
				return true;
		}
	}
	return false;
}

class Rva003F468D;
class LivingWorldBattle
{
public:
	Int GetTeamNumberForSide(Int side);			// 0x003F458A
	Int rva003F48FE(Int side, Int army, Int unit);		// 0x003F48FE
	Int GetRetreatedPlayerCount(Int side);			// 0x003F46A8
	Int GetRetreatedPlayerID(Int side, Int index);		// 0x003F46C1
	Int rva003F47E6(Int side);				// 0x003F47E6
	Int rva003F459A();					// 0x003F459A, total army count (pinned)
	void *rva003F4ABB(Int side, Int army);			// 0x003F4ABB, the army object or null (pinned)
	void AddArmy(Int player, void *army);			// 0x003F6DF9 (WorldBuilder name, pinned)

	unsigned char m_pad00[0x18];
	struct Rva002BC1DASide { unsigned char m_data[0x1c]; } *m_sides;	// +0x18
	Rva002BC1DASide *m_sidesEnd;				// +0x1C
	unsigned char m_pad20[0x24 - 0x20];
	Rva003F287F *m_region;					// +0x24
	unsigned char m_pad28[0x38 - 0x28];
	Int m_side;						// +0x38, the winning side
};
class Rva003F468D
{
public:
	Int rva003F468D(Int side, Int army);			// 0x003F468D
	Int rva003F4DAE(Int side);				// 0x003F4DAE
};
class Rva003F4DCA
{
public:
	Int rva003F4DCA(Int side, Int army);			// 0x003F4DCA
};
class Rva0020E6B7RegionManager
{
public:
	LivingWorldBattle *rva0020E6B7();			// 0x0020E6B7
};
struct Rva002BC1DAArmy
{
	unsigned char m_pad00[0x34];
	Int m_team;						// +0x34
};
class Rva002BC1DAUnit
{
public:
	Bool rva003190A5();					// 0x003190A5
	void rva00319A12();					// 0x00319A12

	unsigned char m_pad00[0x18];
	StringBase<char> m_templateName;			// +0x18
};
void ConsumeGarrisonUnitsFromRTS(Rva002BC1DAUnit *unit, Rva002BC1DAArmy *army, LivingWorldBattle *battle);	// 0x002BBD52

void LivingWorldLogic::GameLogic_tacticalBattleComplete()
{
	void *region = ((Rva002BA8F1Logic *)this)->rva002B2B2D();
	m_fieldB6 = true;
	LivingWorldBattle *battle = ((Rva0020E6B7RegionManager *)m_field0B0)->rva0020E6B7();
	if (battle != 0 && battle->m_side != -1 && region != 0)
	{
		Int team = battle->GetTeamNumberForSide(battle->m_side);
		Int sideCount = battle->m_sidesEnd - battle->m_sides;
		for (Int side = 0; side < sideCount; ++side)
		{
			Int armyCount = ((Rva003F468D *)battle)->rva003F4DAE(side);
			for (Int a = 0; a < armyCount; ++a)
			{
				Rva002BC1DAArmy *army = (Rva002BC1DAArmy *)((Rva003F468D *)battle)->rva003F468D(side, a);
				Int unitCount = ((Rva003F4DCA *)battle)->rva003F4DCA(side, a);
				for (Int u = 0; u < unitCount; ++u)
				{
					Rva002BC1DAUnit *unit = (Rva002BC1DAUnit *)battle->rva003F48FE(side, a, u);
					if (army->m_team != team)
					{
						if (!unit->m_templateName.isEmpty())
						{
							if (unit->rva003190A5())
								unit->rva00319A12();
							((_STL::vector<const ModuleData *> *)&m_field10C)->push_back((const ModuleData *)unit);
						}
						else
						{
							((Rva002B8A9F *)this)->rva002B8A9F((ModuleData *)unit);
						}
					}
					else if (unit->m_templateName.isEmpty())
					{
						ConsumeGarrisonUnitsFromRTS(unit, army, battle);
					}
				}
			}
		}
		OnBattleComplete(battle);
		m_battleListeners.forEach(&Rva002B616FListener::onTurnChanged, this, (int)battle);
	}
	m_fieldB8 = -1;
}

struct Rva002BAF7EArmy
{
	unsigned char m_pad00[0x14];
	Int m_owner;						// +0x14
};
struct Rva002BAF7EWinner
{
	unsigned char m_pad00[0x34];
	Int m_team;						// +0x34
};

void LivingWorldLogic::OnBattleComplete(LivingWorldBattle *battle)
{
	m_field0B0->rva0020FB8B(battle);
	Int winner = battle->m_side;
	if (winner == -1)
		return;
	UnsignedInt flags = 0;
	Rva003F287F *region = battle->m_region;
	if (region->m_ownerPlayer != -1)
	{
		flags = 1;
		Rva002BAF7EWinner *owner = (Rva002BAF7EWinner *)((Rva002BA8F1Logic *)this)->find(region->m_ownerPlayer, 0);
		if (owner->m_team == battle->GetTeamNumberForSide(winner))
			goto done;
	}
	{
		Int sideCount = battle->m_sidesEnd - battle->m_sides;
		for (Int side = 0; side < sideCount; ++side)
		{
			if (side == battle->m_side)
				continue;
			Int i = 0;
			Int armyCount = ((Rva003F468D *)battle)->rva003F4DAE(side);
			for (; i < armyCount; ++i)
			{
				if (((Rva002BAF7EArmy *)((Rva003F468D *)battle)->rva003F468D(side, i))->m_owner == region->m_ownerPlayer)
					flags |= 2;
				else
					flags |= 4;
			}
			i = 0;
			Int retreatedCount = battle->GetRetreatedPlayerCount(side);
			for (; i < retreatedCount; ++i)
			{
				Int owner = region->m_ownerPlayer;
				if (battle->GetRetreatedPlayerID(side, i) == owner)
					flags |= 8;
				else
					flags |= 0x10;
			}
		}
		UnsignedInt winnerCount = ((Rva003F468D *)battle)->rva003F4DAE(winner);
		if ((Int)winnerCount > 1)
		{
			_STL::vector<const ModuleData *> players;
			players.reserve(winnerCount);
			for (UnsignedInt w = 0; w < winnerCount; ++w)
				players.push_back((const ModuleData *)((Rva003F468D *)battle)->rva003F468D(winner, w));
			flags |= 0x20;
			const _STL::vector<Int> &playerIDs = *(const _STL::vector<Int> *)&players;
			if (battle->rva003F47E6(winner) == 0)
			{
				Int regionID = (Int)battle->m_region;
				LetAIResolveRegionAwardDispute(regionID, playerIDs, flags);
			}
			else
			{
				Int regionID = (Int)battle->m_region;
				rva002B9A90(regionID, playerIDs, flags);
			}
		}
		else
		{
			Int army = ((Rva003F468D *)battle)->rva003F468D(winner, 0);
			AddDelayedRegionVictory(region, army, flags);
		}
	}
done:
	rva002B37FF(battle);
	m_field0B0->UpdateBattleMarkers();
}

struct Rva002B792ECampaign
{
	unsigned char m_pad00[0x38];
	Int m_spacing;						// +0x38
};
struct Rva002B792ECampaignManager
{
	Rva002B792ECampaign *GetCurrentCampaign() { return m_campaigns[m_campaignIndex]; }

	unsigned char m_pad00[0x10];
	Int m_campaignIndex;					// +0x10
	_STL::vector<Rva002B792ECampaign *> m_campaigns;	// +0x14
};
class Rva0040C985
{
public:
	void rva0040C985(Int arg);				// 0x0040C985
	void rva0040CA3A(Int offset);				// 0x0040CA3A

	unsigned char m_pad00[0x2c];
	Int m_battleState;					// +0x2C
};
struct Rva002B792EArmy
{
	unsigned char m_pad00[0x18];
	StringBase<char> m_templateName;			// +0x18
	unsigned char m_pad1C[0x78 - 0x1c];
	Rva0040C985 *m_summary;					// +0x78
};
class Rva00318BA5
{
public:
	void rva00318BA5(LivingWorldRegion *region);		// 0x00318BA5
};

void LivingWorldLogic::PrepareBattleForLoading(LivingWorldBattle *battle)
{
	_STL::vector<const ModuleData *> armies;
	armies.reserve(battle->rva003F459A());
	Int k = 0;
	for (Int side = 0; side < battle->m_sidesEnd - battle->m_sides; ++side)
	{
		for (Int a = 0; a < ((Rva003F468D *)battle)->rva003F4DAE(side); ++a, ++k)
		{
			void *army = battle->rva003F4ABB(side, a);
			if (army == 0)
			{
				Int player = ((Rva003F468D *)battle)->rva003F468D(side, a);
				army = CreateEmptyGarrisonArmy((Rva002B6A04Player *)player, (LivingWorldRegion *)battle->m_region);
				if (army != 0)
					battle->AddArmy(player, army);
			}
			armies.begin()[k] = (const ModuleData *)army;
		}
	}
	Int spacing = 0;
	if (TheCampaignManager != 0)
		spacing = ((Rva002B792ECampaignManager *)TheCampaignManager)->GetCurrentCampaign()->m_spacing;
	k = 0;
	for (Int side = 0; side < battle->m_sidesEnd - battle->m_sides; ++side)
	{
		Int armyCount = ((Rva003F468D *)battle)->rva003F4DAE(side);
		for (Int a = 0; a < armyCount; ++a, ++k)
		{
			Int engaged = 0;
			Int unitCount = ((Rva003F4DCA *)battle)->rva003F4DCA(side, a);
			Int u = 0;
			if (u < unitCount)
			{
				Int offset = 0;
				do
				{
					Rva002B792EArmy *unit = (Rva002B792EArmy *)battle->rva003F48FE(side, a, u);
					if (!unit->m_templateName.isEmpty())
					{
						if (engaged > 0 && spacing > 0)
						{
							unit->m_summary->rva0040CA3A(offset);
							Rva0040C985 *summary = unit->m_summary;
							summary->rva0040C985(0);
						}
						else
						{
							Rva0040C985 *summary = unit->m_summary;
							summary->m_battleState = 4;
							((Rva00318BA5 *)armies[k])->rva00318BA5((LivingWorldRegion *)battle->m_region);
						}
						++engaged;
						offset += spacing;
					}
					else
					{
						Rva0040C985 *summary = unit->m_summary;
						summary->m_battleState = 4;
					}
				} while (++u < unitCount);
			}
		}
	}
}
