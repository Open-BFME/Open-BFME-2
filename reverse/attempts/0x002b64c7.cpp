// ?OnDestroyingBuilding@LivingWorldLogic@@UAEXPAVRva002B64C7Building@@@Z
// partial score=0.85 date=2026-10-07
// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// LivingWorldLogic.cpp -- LivingWorldLogic members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function and
// its callee and asserts !players.empty(); retail supplies the bytes.
//
// The dispute is settled for the first listed player, with flag 0x20 added
// to the victory flags. The element type of the player list is not proven;
// it is carried as a 32-bit value.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include <vector>
#include <map>

class LivingWorldPlayer;
class LivingWorldLogic;

// LivingWorldLogic::AutoBattleResolver (WB name), 0x28 bytes; rowed in the
// ledger under the placeholder Rva002B74DE (dtor 0x002B74DE). Its ctor
// (0x002BD40D) and Update (0x002BB7D6) are unrowed.
class Rva002B74DE
{
public:
	Rva002B74DE(LivingWorldLogic *logic, Int battle);	// 0x002BD40D
	~Rva002B74DE();						// 0x002B74DE
	Int Update();						// 0x002BB7D6, 1 when done

private:
	unsigned char m_data[0x28];
};

// m_autoBattleResolver at +0x178: an owning pointer whose reset and clear
// are rowed under placeholder names (OwnedPointerResets.cpp).
class Rva002B90B3
{
public:
	void reset(Rva002B74DE *resolver);			// 0x002B90B3
	Rva002B74DE *get() const { return m_ptr; }

private:
	Rva002B74DE *m_ptr;
};

// Player lookup by id (0x002B51F8) and the per-player upgrade marking
// (0x002E2D8D, WB LivingWorldPlayer::MarkUnitsForUpgrades) are pinned under
// placeholder names for this object and the player.
class Rva002E2903Player
{
public:
	void rva002E2D8D(void *army);				// 0x002E2D8D
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(Int playerID, UnsignedInt *index);	// 0x002B51F8
	struct Rva002B488EResult *rva002B488E(Int armyID);	// 0x002B488E, WB LivingWorldLogic::findArmy
};

struct LivingWorldUpgradeArmy
{
	unsigned char m_pad000[0x13c];
	Int m_playerID;						// +0x13C, -1 when unowned
};

// The army set reached through +0xB0 then +0x08. Retail converts it to the
// army list base at +0x2C with a NULL check, the shape of a derived-to-base
// cast, so the list is modelled as a second base.
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

// The region manager at +0xB0 (WB: GetRegionCenterPoint is called on it);
// its pending battles vector is at +0x14.
class LivingWorldRegionManager
{
public:
	Bool GetRegionCenterPoint(Int regionID, Coord2D *out);	// 0x0020F27E
	// The check of an army's move between two regions (WorldBuilder name,
	// 0x0020EC99, pinned): 0 or 1 when the move is allowed.
	Int ValidateArmyRegionEntry(struct LivingWorldArmy *army, class Rva00318C32Ret *from, class Rva00318C32Ret *to, Int a, Int b);

	unsigned char m_pad00[0x8];
	Rva002B5334ArmySet *m_armySet;				// +0x08
	unsigned char m_pad0C[0x14 - 0xc];
	_STL::vector<void *> m_field14;				// +0x14
};

// Any-of / all-of walks over this object's vectors, rowed under placeholder
// names (Rva002B4B3D.cpp, Rva002B3288.cpp).
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

// Army summary entries are reference counted through the counter at +0xAC,
// released by the rowed fastcall 0x0007DEEF; the army's summary at +0x78
// looks an entry up by id and returns it in a holder (0x0040CBD7, WB
// ArmySummary::GetEntry), NULL when absent.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);	// 0x0007DEEF

class Rva004E0632;

class ArmySummaryEntry
{
public:
	void MarkForUpgrades(const Rva004E0632 *upgrades);	// 0x0040C430
	void CancelUpgrades();					// 0x0040C45C

	// The pending move target at +0xB8 (cleared by WB's
	// CancelArmyMemberMove); an entry already moving takes no upgrades.
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

// The summary's 8-byte entry records at +0x40; the indexed getter 0x0040CB2C
// (WB ArmySummary::GetEntry, rowed under a placeholder name) yields the
// entry of record i.
struct ArmySummaryRecord
{
	Int m_entry;
	Int m_data;
};

class ArmySummary
{
public:
	ArmySummaryEntryRef GetEntry(Int entryID);		// 0x0040CBD7
	Int GetNumEntries() const { return m_recordsEnd - m_records; }

	unsigned char m_pad00[0x40];
	ArmySummaryRecord *m_records;				// +0x40
	ArmySummaryRecord *m_recordsEnd;			// +0x44
};

class Rva0040CB2CIndexedField
{
public:
	Int get(Int index) const;				// 0x0040CB2C
};

struct LivingWorldArmy
{
	unsigned char m_pad00[0x20];
	Int m_id;						// +0x20 (WB LivingWorldArmy::GetID, inlined)
	unsigned char m_pad24[0x54 - 0x24];
	Int m_ownerPlayer;					// +0x54
	unsigned char m_pad58[0x74 - 0x58];
	Bool m_field74;						// +0x74, set: left alone by EnforceArmyRegionOwnership
	unsigned char m_pad75[0x78 - 0x75];
	ArmySummary *m_summary;					// +0x78
};

// Turn listeners at +0x1C are told (old turn, new turn) through the slot +4
// virtual (vcall thunk 0x005CB260); the list's forEach (0x002B616F) and the
// per-turn cleanup at 0x002B7BFB are rowed under placeholder names
// (Rva002B55F2ListenerWalks.cpp, Rva002B7BFB.cpp).
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

// TheLivingWorldCampaignManager (0x00E02D6C, rowed lookup 0x003B8BAA); the
// end-of-turn notification at 0x003B8CAC is unrowed, unnamed in WB and pinned.
class Rva003B8BAA
{
public:
	void *rva003B8BAA();					// 0x003B8BAA, see CanDisbandArmyMember
	void rva003B8CAC();					// 0x003B8CAC
};

class Rva00E02D6C; extern Rva00E02D6C *TheCampaignManager;

// The same global as LivingWorldCampaignManager.cpp's view: its generic
// spawn army lookup (rowed 0x003B8CE0) takes the player as its second word.
class LivingWorldCampaignManager
{
public:
	void *UseGenericSpawnArmyForPlayer(Int a, Int b);	// 0x003B8CE0
};

// The generic spawn army's id at +0x4C and the player's id at +0x14, the
// pair this object's +0x13C multimap records (WB asserts
// !HasSpawnedArmyForPlayer(*army, player) before recording it).
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

// The upgrade module behind an armory's module data: the rowed const getter
// 0x004E0632 yields the object whose slot +4 tests an entry.
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

// The region: its armories through the rowed filter 0x003F28DB, its owning
// player at +0x13C.
class Rva003F287F
{
public:
	void rva003F28DB(_STL::vector<const ModuleData *> &out);	// 0x003F28DB

	unsigned char m_pad000[0x12c];
	Int m_regionID;						// +0x12C
	unsigned char m_pad130[0x13c - 0x130];
	Int m_ownerPlayer;					// +0x13C
};

// One delayed region victory (WB m_delayedRegionVictories element, 12
// bytes): the player, the region's id and the award flags. Its push_back is
// the ICF-folded 12-byte element instantiation retail calls at 0x002DF89B,
// rowed as vector<PrereqUnitRec>::push_back; the list is appended through
// that view (this unit's exception-enabled copy could not reproduce it).
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

// LivingWorldLogic's bases: a 0x10-byte primary base, then the building
// and region observer interfaces at +0x10 and +0x14 whose handlers retail
// enters with this adjusted (0x002B64C7 reads the logic at -0x10).
class Rva002B64C7Building;
class Rva002B64C7Base00
{
public:
	virtual void slot00();

private:
	unsigned char m_pad04[0x10 - 0x4];
};

class Rva002B64C7BuildingObserver
{
public:
	virtual void OnDestroyingBuilding(Rva002B64C7Building *building) = 0;
};

class Rva002BA82BRegionObserver
{
public:
	virtual void slot00() = 0;
};

class LivingWorldLogic : public Rva002B64C7Base00, public Rva002B64C7BuildingObserver, public Rva002BA82BRegionObserver
{
public:
	virtual void OnDestroyingBuilding(Rva002B64C7Building *building);

	// 0x002B6DC4: the upgrades the region's armory offers the entry.
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

private:
	void AddDelayedRegionVictory(Rva003F287F *region, Int player, UnsignedInt flags);	// 0x002B9B42
	void CheckTurnPhaseTransitions();		// 0x002BD23E
	void rva002B5B55(void *army);			// 0x002B5B55, destroys one army

	unsigned char m_pad18[0x1c - 0x18];
	Rva002B616FList m_turnListeners;		// +0x1C
	unsigned char m_pad2C[0x8c - 0x2c];
	_STL::vector<LivingWorldPlayer *> m_players;	// +0x8C
	LivingWorldPlayer *m_localPlayer;		// +0x98 (WB member name)
	unsigned char m_pad9C[0xb0 - 0x9c];
	LivingWorldRegionManager *m_field0B0;		// +0xB0, region manager
	unsigned char m_padB4[0xcc - 0xb4];
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
	unsigned char m_pad124[0x13c - 0x124];
	_STL::multimap<Int, Int> m_spawnedArmies;	// +0x13C, generic army id -> player id
	_STL::vector<DelayedRegionVictory> m_delayedRegionVictories;	// +0x148 (WB member name)
	unsigned char m_pad154[0x178 - 0x154];
	Rva002B90B3 m_autoBattleResolver;		// +0x178 (WB member name)
};

enum { TURN_PHASE_LAST_ADVANCEABLE = 6 };

// LivingWorldLogic::EndTurn, retail 0x002BD36D (WB name). From the last
// advanceable phase: run the per-turn cleanup, tell the turn listeners
// (old turn, new turn), reset the phase, copy +0x100 to +0x104, clear the two
// flags, advance the turn, notify the campaign manager and recheck phase
// transitions. The turn increment written after the field stores is what
// keeps cl from hoisting &m_turn into a register (retail addresses it off
// this, scheduled before the stores).
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

// LivingWorldLogic::AdvanceTurnPhase, retail 0x002BD3D6. WB also logs the
// refused request and the phase transition; retail keeps the logic only.
// The +0x100 value is copied to +0x104 on every advance (names unknown).
Bool LivingWorldLogic::AdvanceTurnPhase()
{
	if (!IsCurrentTurnPhaseFinished() || m_turnPhase >= TURN_PHASE_LAST_ADVANCEABLE)
		return false;
	m_turnPhase = m_turnPhase + 1;
	m_field104 = m_field100;
	CheckTurnPhaseTransitions();
	return true;
}

// LivingWorldLogic::ValidatePlayers, retail 0x002B38D2. WB logs when there
// are no players and when it falls back to the first one.
void LivingWorldLogic::ValidatePlayers()
{
	if (m_players.size() == 0)
		return;
	if (m_localPlayer == 0)
		m_localPlayer = m_players[0];
}

// LivingWorldLogic::LetAIResolveRegionAwardDispute, retail 0x002BAF5D.
void LivingWorldLogic::LetAIResolveRegionAwardDispute(Int regionID, const _STL::vector<Int> &players, UnsignedInt flags)
{
	if (players.empty())
		return;
	flags |= 0x20;
	AddDelayedRegionVictory((Rva003F287F *)regionID, players[0], flags);
}

// LivingWorldLogic::processArmyDestroyList, retail 0x002B7BBB. Destroys every
// queued army through the unrowed per-army worker, then empties the queue.
// The queue clears through the folded pointer-vector range erase (rowed as
// vector<void *>), so it is carried as one.
void LivingWorldLogic::processArmyDestroyList()
{
	for (UnsignedInt i = 0; i < m_armyDestroyList.size(); ++i)
		rva002B5B55(m_armyDestroyList[i]);
	m_armyDestroyList.clear();
}

// LivingWorldLogic::MarkTroopForUpgrades, retail 0x002B3FD3. WB asserts the
// entry is bound; retail skips an absent one.
void LivingWorldLogic::MarkTroopForUpgrades(Int entryID, LivingWorldArmy *army, const Rva004E0632 *upgrades)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return;
	entry.m_entry->MarkForUpgrades(upgrades);
}

// LivingWorldLogic::CancelTroopUpgrades, retail 0x002B4026.
void LivingWorldLogic::CancelTroopUpgrades(Int entryID, LivingWorldArmy *army)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return;
	entry.m_entry->CancelUpgrades();
}

// LivingWorldLogic::StartAutoResolveBattle, retail 0x002BD603. WB asserts no
// resolver is already bound.
void LivingWorldLogic::StartAutoResolveBattle(Int battle)
{
	m_autoBattleResolver.reset(new Rva002B74DE(this, battle));
}

// LivingWorldLogic::AutoResolveBattle, retail 0x002BD64F: resolves the whole
// battle at once, then drops the resolver.
void LivingWorldLogic::AutoResolveBattle(Int battle)
{
	m_autoBattleResolver.reset(new Rva002B74DE(this, battle));
	while (m_autoBattleResolver.get()->Update() != 1)
		;
	((Rva002B9099 *)&m_autoBattleResolver)->clear();
}

// LivingWorldLogic::AutoMarkUnitsForUpgrades, retail 0x002B5334: every owned
// army is handed to its player's upgrade marking. WB asserts the player
// exists.
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

// LivingWorldLogic::CanMoveArmyMember, retail 0x002B8F8B: an absent entry
// cannot move; otherwise the unrowed check at 0x002B8019 decides.
Bool LivingWorldLogic::CanMoveArmyMember(LivingWorldArmy *army, Int entryID, Int target)
{
	ArmySummary *summary = army->m_summary;
	ArmySummaryEntryRef entry = summary->GetEntry(entryID);
	if (entry.m_entry == 0)
		return false;
	return rva002B8019(army, entry.m_entry, target);
}

// LivingWorldLogic::IsCurrentTurnPhaseFinished, retail 0x002B5390. WB logs
// an unhandled phase; member names are unknown.
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

// AttackOrders (WB name) keeps its members at +0x08. Each member looks up
// its hero entry by the key at +0x18 (0x0031996D, unrowed and unnamed in WB),
// returned in the same reference-counted holder as army summary entries;
// the hero's rank is at +0x0C.
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

// AttackOrders::GetMaxHeroLeaderRank, retail 0x002B3A9C. WB asserts every
// member's hero entry is bound; retail skips unbound ones.
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

// LivingWorldLogic::CalcAttackingDirection, retail 0x002B4F6C: the direction
// between the centers of the last two regions of a path (both the first
// region when the path is shorter).
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

// The army summary's keyed value getter (0x0040CBB8, rowed under the
// placeholder Rva0040CB3AIndexedField): the entry for an id, NULL when absent.
class Rva0040CB3AIndexedField
{
public:
	Int get(Int index) const;				// 0x0040CBB8
};

// TheLivingWorldLogic (0x00DFEF10): its rowed int-returning check 0x002B254F,
// tested as a byte by every caller.
class Rva002B254F
{
public:
	Int rva002B254F();					// 0x002B254F
};

class LivingWorldLogic; extern LivingWorldLogic *TheLivingWorldLogic;

// TheLivingWorldCampaignManager's rowed lookup 0x003B8BAA (on g_00E02D6C
// above) returns the object
// whose slot +8 vets an army summary entry.
class Rva003B8BAAEntryVet
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual Bool vetEntry(ArmySummaryEntry *entry);		// +0x08
};

// The thing template's KindOf mask at +0x108 (WB tests bit 90 through the
// BitFlags helper 0x00045623; retail reads the word at +0x110 inline).
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

// The army member's template name (entry +0x04) against the army's own
// (+0x18), through the rowed StringBase compare 0x000069D6 (pinned view).
class Rva004525B0String
{
public:
	Int compare(const Rva004525B0String &that) const;	// 0x000069D6
};

// The target army's room for an entry: rowed 0x00319413.
class Rva0037DCA5;
class Rva003193EC
{
public:
	bool rva00319413(Rva0037DCA5 *entry);			// 0x00319413
};



// CanDisbandArmyMember, retail 0x002B3E7E (88 bytes): WB's one-argument
// overload in LivingWorldLogic.cpp (asserts at lines 8110 and 8112). Its
// entry argument arrives in EAX: cl 7.1 gives that convention to a
// file-static whose every caller is in its unit (the rowed DisbandArmy in
// Rva002B3EFA.cpp reaches it through the Rva002B3E7ECheck pin). An entry
// the campaign refuses, one already disbanded, or one whose template is
// missing or of KindOf bit 90 cannot be disbanded.
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

// CanDisbandArmyMember, retail 0x002B3ED6 (36 bytes): WB's two-argument free
// function in LivingWorldLogic.cpp, asserting the army's summary is bound.
// The summary entry for the id must exist and pass the per-entry check.
Bool CanDisbandArmyMember(LivingWorldArmy *army, Int entryID)
{
	Rva0040CB3AIndexedField *summary = (Rva0040CB3AIndexedField *)army->m_summary;
	ArmySummaryEntry *entry = (ArmySummaryEntry *)summary->get(entryID);
	return entry != 0 && CanDisbandArmyMember(entry);
}

// DisbandArmyMember, retail 0x002B3F3B (100 bytes): WB's free function in
// LivingWorldLogic.cpp. A bound entry that may be disbanded is flagged at
// +0xC4 and has its upgrades cancelled.
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

// GameMessage (Zero Hour's GameMessage.h): the argument count byte at +0x18
// and the rowed argument lookup 0x0030F4EA.
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

// WB's validateMessageArgumentIndex / validateArmy / validateArmySummaryEntryID
// helpers, which retail inlines into each message getter.
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

// getArmyFromMessage, retail 0x002B543D (58 bytes): WB's file-static in
// LivingWorldLogic.cpp (asserts msg != NULL at line 8381). The army whose id
// is the message argument, through TheLivingWorldLogic's findArmy
// (0x002B488E). Retail passes the message in ECX, cl 7.1's convention for a
// file-static whose callers are all in its unit.
static __declspec(noinline) Bool getArmyFromMessage(LivingWorldArmy **army, const GameMessage *msg, Int argIndex)
{
	if (!validateMessageArgumentIndex(msg, argIndex))
		return 0;
	Int armyID = msg->getArgument(argIndex)->integer;
	*army = (LivingWorldArmy *)((Rva002BA8F1Logic *)((Rva002B254F *)TheLivingWorldLogic))->rva002B488E(armyID);
	return *army != 0;
}

// getArmySummaryEntryIDFromMessage, retail 0x002B4108 (57 bytes): WB's
// file-static; the id must name an entry of the army's summary.
static __declspec(noinline) Bool getArmySummaryEntryIDFromMessage(Int *entryID, const GameMessage *msg, Int argIndex, LivingWorldArmy *army)
{
	if (!validateMessageArgumentIndex(msg, argIndex))
		return 0;
	*entryID = msg->getArgument(argIndex)->integer;
	return validateArmySummaryEntryID(*entryID, army);
}

// HandleUnmarkUnitForUpgradeMessage, retail 0x002B5477 (68 bytes): WB's
// handler in LivingWorldLogic.cpp: argument 0 names the army, argument 1 the
// summary entry whose upgrades TheLivingWorldLogic cancels.
void HandleUnmarkUnitForUpgradeMessage(const GameMessage *msg)
{
	LivingWorldArmy *army;
	Int entryID;
	if (getArmyFromMessage(&army, msg, 0)
		&& getArmySummaryEntryIDFromMessage(&entryID, msg, 1, army))
		((LivingWorldLogic *)((Rva002B254F *)TheLivingWorldLogic))->CancelTroopUpgrades(entryID, army);
}

// The army's region lookup 0x00318C32 (unrowed, pinned under the placeholder
// Rva00318C79Owner): NULL when the army stands in no region.
class Rva00318C32Ret;

class Rva00318C79Owner
{
public:
	Rva00318C32Ret *rva00318C32();				// 0x00318C32
};

// HandleMarkUnitForUpgradeMessage, retail 0x002B6F57 (169 bytes): WB's
// handler in LivingWorldLogic.cpp: argument 0 names an army standing in a
// region, argument 1 its summary entry, which TheLivingWorldLogic marks for
// the upgrades of the region's armory.
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

// LivingWorldLogic::GetArmoryToUpgradeTroop, retail 0x002B6DC4 (198 bytes):
// WB names it in LivingWorldLogic.cpp. The army must stand in the region and
// share its owner, and the entry must not be moving; the first of the
// region's armories whose upgrade accepts the entry is returned.
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

// LivingWorldLogic::UseGenericSpawnArmyForPlayer, retail 0x002B8660 (74
// bytes; WB name, assert line 1848). Takes the campaign's generic spawn army
// for the player and records (army id, player id); NULL without one.
Rva002B8660Army *LivingWorldLogic::UseGenericSpawnArmyForPlayer(Int a, Rva002B8660Player *player)
{
	Rva002B8660Army *army = (Rva002B8660Army *)((LivingWorldCampaignManager *)TheCampaignManager)->UseGenericSpawnArmyForPlayer(a, (Int)player);
	if (army)
		m_spawnedArmies.insert(_STL::make_pair(army->m_id, player->m_id));
	return army;
}

// LivingWorldLogic::AddDelayedRegionVictory, retail 0x002B9B42 (117 bytes;
// WB name, assert line 3613 against a region already awarded). A region is
// queued once; later awards for it are dropped.
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

// Retail 0x002B2C12 (46 bytes; WorldBuilder leaves it unnamed, its only
// callees are the army region getter and
// LivingWorldRegionManager::ValidateArmyRegionEntry): checks a move of the
// army from its region to the target army's region.
Int LivingWorldLogic::rva002B2C12(LivingWorldArmy *army, LivingWorldArmy *target)
{
	return m_field0B0->ValidateArmyRegionEntry(army, ((Rva00318C79Owner *)army)->rva00318C32(), ((Rva00318C79Owner *)target)->rva00318C32(), 0, 0);
}

// LivingWorldLogic::CanMoveArmyMember_internal, retail 0x002B6B5B (116
// bytes; WB name, assert line 7861 on the entry's previous army). An entry
// of the army's own kind stays; an entry already moving must be able to
// reach the target from the army it is moving to, otherwise from this one;
// with checkRoom the target must also take it.
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

// The armory upgrade's two troop counts (slots +0x00 and +0x08 of the
// object the rowed getter 0x004E0632 yields; the filter above is slot +0x04).
class Rva002B6E8AUpgrade
{
public:
	virtual Int count00();
	virtual void slot04();
	virtual Int count08();
};

// LivingWorldLogic::GetNumUpgradeableTroopsInRegionForPlayer, retail
// 0x002B6E8A (167 bytes; WB name). Both counts start at zero; for the
// region's owner they sum the two counts of every armory's upgrade.
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

// The player's id at +0x14 and its armies at +0x1B8 (LivingWorldPlayer.cpp's
// m_armyVec), as EnforceArmyRegionOwnership reads them.
struct Rva002B4C35Player
{
	unsigned char m_pad00[0x14];
	Int m_id;						// +0x14
	unsigned char m_pad18[0x1b8 - 0x18];
	_STL::vector<LivingWorldArmy *> m_armies;		// +0x1B8
};

// The two callees, rowed and pinned under placeholder names: the unowned
// region hand-over 0x002B388D (rowed as a BFME 1 donor's
// Refresh0023FA80Primary::scheduleNullable, on this object with
// (region, player)) and the army's eviction 0x0031912E (pinned).
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

// LivingWorldLogic::EnforceArmyRegionOwnership, retail 0x002B4C35 (184
// bytes; WB name). For every player's armies standing in a region: an
// unowned region is handed to the player, and an army in another player's
// region is moved out. Armies flagged at +0x74 are skipped.
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

// The destroyed building: its id at +0x18 and its region at +0x24; the
// rowed getter 0x004E0632 tells whether it is an armory.
class Rva002B64C7Building
{
public:
	unsigned char m_pad00[0x18];
	Int m_id;						// +0x18
	unsigned char m_pad1C[0x24 - 0x1c];
	Rva003F287F *m_region;					// +0x24
};

// The region owner's armies in the region (rowed 0x002E2504, on the player).
class Rva002E2504
{
public:
	bool rva002E2504(Rva00318C32Ret *region, _STL::vector<const ModuleData *> *out);	// 0x002E2504
};

// The pending upgrade of a summary entry: the building it was ordered from
// at +0xBC.
struct Rva002B64C7Entry
{
	unsigned char m_pad00[0xbc];
	Int m_upgradeBuilding;					// +0xBC
};

// LivingWorldLogic::OnDestroyingBuilding, retail 0x002B64C7 (240 bytes; WB
// name; entered through the building observer base at +0x10). Outside the
// first turn phase nothing happens; when an armory goes, every entry of the
// region owner's armies there that was upgrading from it cancels.
void LivingWorldLogic::OnDestroyingBuilding(Rva002B64C7Building *building)
{
	if (m_turnPhase != 0)
		return;
	if (((const Rva004E0632 *)building)->rva004E0632() == 0)
		return;
	Rva003F287F *region = building->m_region;
	if (region == 0)
		return;
	Rva002E2903Player *player = ((Rva002BA8F1Logic *)this)->find(region->m_ownerPlayer, 0);
	if (player == 0)
		return;
	_STL::vector<const ModuleData *> armies;
	((Rva002E2504 *)player)->rva002E2504((Rva00318C32Ret *)region, &armies);
	for (UnsignedInt i = 0; i < armies.size(); ++i)
	{
		LivingWorldArmy *army = (LivingWorldArmy *)armies[i];
		Int count = army->m_summary->GetNumEntries();
		for (Int j = 0; j < count; ++j)
		{
			ArmySummaryEntry *entry = (ArmySummaryEntry *)((const Rva0040CB2CIndexedField *)army->m_summary)->get(j);
			if (((Rva002B64C7Entry *)entry)->m_upgradeBuilding == building->m_id)
				entry->CancelUpgrades();
		}
	}
}
