// ?CanMoveArmyMember_internal@LivingWorldLogic@@QAE_NPAVRva003193EC@@PAVRva0037DCA5@@0_N@Z
// partial score=0.8 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// LivingWorldLogic.cpp -- LivingWorldLogic members recovered from WorldBuilder
// leads (reverse/wb_name_leads.csv): WB's debug build names the function and
// its callee and asserts !players.empty(); retail supplies the bytes.
//
// The dispute is settled for the first listed player, with flag 0x20 added
// to the victory flags. The element type of the player list is not proven;
// it is carried as a 32-bit value.

#include "ascii_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

namespace _STL
{
	template <class T> class allocator {};

	template <class T, class A = allocator<T> > class vector
	{
	public:
		bool empty() const { return m_start == m_finish; }
		UnsignedInt size() const { return UnsignedInt(m_finish - m_start); }
		const T &operator[](UnsignedInt i) const { return m_start[i]; }
		T *begin() { return m_start; }
		T *end() { return m_finish; }
		T *erase(T *first, T *last);		// folded pointer-vector range erase 0x0031BD55
		void clear() { erase(begin(), end()); }

	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

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

// An army as CanMoveArmyMember_internal reaches it: name at +0x18, id at
// +0x20 (WB LivingWorldArmy::GetID, inlined), and the capacity check
// 0x00319413 on a summary entry; both are rowed under placeholder names.
class Rva0037DCA5
{
public:
	unsigned char m_pad00[0x4];
	AsciiString m_name;					// +0x04
	unsigned char m_pad08[0xb8 - 0x8];
	Int m_pendingArmyID;					// +0xB8
};

class Rva003193EC
{
public:
	Bool rva00319413(Rva0037DCA5 *entry);			// 0x00319413
	Int GetID() const { return m_id; }

	unsigned char m_pad00[0x18];
	AsciiString m_name;					// +0x18
	unsigned char m_pad1C[0x20 - 0x1c];
	Int m_id;						// +0x20
};

struct Rva002B488EResult;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(Int playerID, UnsignedInt *index);	// 0x002B51F8
	Rva002B488EResult *rva002B488E(Int armyID);			// 0x002B488E, WB findArmy
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

struct Rva002B5334Owner
{
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

	unsigned char m_pad00[0xac];
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
	unsigned char m_pad00[0x78];
	ArmySummary *m_summary;					// +0x78
};

class LivingWorldLogic
{
public:
	void ValidatePlayers();
	Bool AdvanceTurnPhase();
	Bool IsCurrentTurnPhaseFinished();
	void processArmyDestroyList();
	void MarkTroopForUpgrades(Int entryID, LivingWorldArmy *army, const Rva004E0632 *upgrades);
	void CancelTroopUpgrades(Int entryID, LivingWorldArmy *army);
	void StartAutoResolveBattle(Int battle);
	void AutoResolveBattle(Int battle);
	void AutoMarkUnitsForUpgrades();
	Bool CanMoveArmyMember(LivingWorldArmy *army, Int entryID, Int target);
	Bool rva002B8019(LivingWorldArmy *army, ArmySummaryEntry *entry, Int target);	// 0x002B8019
	Bool CanMoveArmyMember_internal(Rva003193EC *srcArmy, Rva0037DCA5 *entry, Rva003193EC *dstArmy, Bool checkCapacity);
	Int rva002B2C12(Rva003193EC *fromArmy, Rva003193EC *toArmy);	// 0x002B2C12
	void LetAIResolveRegionAwardDispute(Int regionID, const _STL::vector<Int> &players, UnsignedInt flags);

private:
	void AddDelayedRegionVictory(Int regionID, Int player, UnsignedInt flags);	// 0x002B9B42
	void CheckTurnPhaseTransitions();		// 0x002BD23E
	void rva002B5B55(void *army);			// 0x002B5B55, destroys one army

	unsigned char m_pad00[0x8c];
	_STL::vector<LivingWorldPlayer *> m_players;	// +0x8C
	LivingWorldPlayer *m_localPlayer;		// +0x98 (WB member name)
	unsigned char m_pad9C[0xb0 - 0x9c];
	Rva002B5334Owner *m_field0B0;			// +0xB0
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
	unsigned char m_pad124[0x178 - 0x124];
	Rva002B90B3 m_autoBattleResolver;		// +0x178 (WB member name)
};

enum { TURN_PHASE_LAST_ADVANCEABLE = 6 };

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
	AddDelayedRegionVictory(regionID, players[0], flags);
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

static inline Bool isMovableRelation(Int relation)
{
	return relation >= 0 && relation <= 1;
}

// LivingWorldLogic::CanMoveArmyMember_internal, retail 0x002B6B5B. A member
// cannot move into the army it is in; a member already pending a move is
// judged from its pending source army (WB asserts that army exists); the
// unrowed relation check 0x002B2C12 must answer 0 or 1.
Bool LivingWorldLogic::CanMoveArmyMember_internal(Rva003193EC *srcArmy, Rva0037DCA5 *entry, Rva003193EC *dstArmy, Bool checkCapacity)
{
	if (entry->m_name.compare(srcArmy->m_name) == 0)
		return false;
	if (entry->m_pendingArmyID != 0)
	{
		if (entry->m_pendingArmyID != dstArmy->GetID())
		{
			Rva003193EC *oldSourceArmy = (Rva003193EC *)((Rva002BA8F1Logic *)this)->rva002B488E(entry->m_pendingArmyID);
			if (oldSourceArmy == 0)
				return false;
			Int relation = rva002B2C12(oldSourceArmy, dstArmy);
			if (!(relation >= 0 && relation <= 1))
				return false;
		}
	}
	else
	{
		Int relation = rva002B2C12(srcArmy, dstArmy);
		if (!(relation >= 0 && relation <= 1))
			return false;
	}
	if (checkCapacity && !dstArmy->rva00319413(entry))
		return false;
	return true;
}
