// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/shims/bfmealloc /O1 /EHsc /MD /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_CRTIMP=
// stlport
// LivingWorldRegionManager.cpp -- region-manager members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function and the region overload it calls (0x0020EA58); retail supplies
// the bytes. The region id lookup is the rowed 0x0020EAF6 accessor.

#include <stdlib.h>
namespace _STL { void __cdecl free(void *block) throw(...); }
#define free _STL::free
#include <vector>
#include <algorithm>
#undef free

#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

// The center point is 2D: the region overload writes only x and y.
#include "../../../../../Libraries/Include/Lib/Coord2D.h"

// LivingWorldRegion: a region with its own UI popup point (+0xAB) returns
// it through the accessor 0x0020E493, rowed under a placeholder name with an
// explicit out parameter.
struct Out0020E493 : public Coord2D
{
};

class Rva0020E89C
{
public:
	unsigned char m_pad00[0xab];
	bool m_hasUiPopupPoint;				// +0xAB
	unsigned char m_padAC[0x13C - 0xAC];
	Int m_id;							// +0x13C, the region id

	// Stores the reinforcement settings (+0x158 name, +0x14C..+0x154,
	// flags +0x1A0/+0x1A1); unrowed and unnamed in WB.
	void rva003F1AB9(const AsciiString &name, Int a, Int b, Int c, Bool d, Bool e);	// 0x003F1AB9
};

class Rva0020E493
{
public:
	Out0020E493 *rva0020E493(Out0020E493 *out);	// 0x0020E493
};

class LivingWorldPendingBattle;

class PendingBattleVisitor
{
public:
	virtual bool Visit(LivingWorldPendingBattle *battle) = 0;
};

class ModuleData;
struct RegionBattleView;
struct RegionBattlePoint;
typedef _STL::vector<const ModuleData *> RegionSlots;

class LivingWorldRegionManager
{
public:
	void EnumeratePendingBattles(PendingBattleVisitor &visitor) const;
	void AddBattle(RegionBattleView *, const RegionSlots &, const RegionSlots &, const RegionBattlePoint &);
	Bool GetRegionCenterPoint(Int regionID, Coord2D *out);
	Bool GetRegionCenterPoint(Rva0020E89C *region, Coord2D *out);	// 0x0020EA58
	Bool GetRegionUiPopupPoint(Int regionID, Coord2D *out);
	void SetRegionReinforcements(Int regionID, const AsciiString &name, Int a, Int b, Int c, Bool d, Bool e);

private:
	friend class LivingWorldRegionBonusRule;
	Rva0020E89C *rva0020EAF6(Int regionID);				// 0x0020EAF6

	unsigned char m_pad00[0x14];
	LivingWorldPendingBattle **m_pendingBattlesStart;		// +0x14
	LivingWorldPendingBattle **m_pendingBattlesFinish;		// +0x18
};

// LivingWorldRegionManager::GetRegionCenterPoint, retail 0x0020F27E.
// ?LivingWorldRegionManager::GetRegionCenterPoint present-unmatched
Bool LivingWorldRegionManager::GetRegionCenterPoint(Int regionID, Coord2D *out)
{
	Rva0020E89C *region = rva0020EAF6(regionID);
	if (region == 0)
		return false;
	return GetRegionCenterPoint(region, out);
}

// LivingWorldRegionManager::EnumeratePendingBattles, retail 0x0020E7BD: visit
// each pending battle until the visitor declines.
void LivingWorldRegionManager::EnumeratePendingBattles(PendingBattleVisitor &visitor) const
{
	LivingWorldPendingBattle **end = m_pendingBattlesFinish;
	for (LivingWorldPendingBattle **it = m_pendingBattlesStart; it != end; ++it)
	{
		LivingWorldPendingBattle *battle = *it;
		if (!visitor.Visit(battle))
			break;
	}
}

// LivingWorldRegionManager::GetRegionUiPopupPoint, retail 0x0020F2A2: the
// region's own popup point when it has one, else its center. WB asserts the
// region exists.
// ?LivingWorldRegionManager::GetRegionUiPopupPoint present-unmatched
Bool LivingWorldRegionManager::GetRegionUiPopupPoint(Int regionID, Coord2D *out)
{
	Rva0020E89C *region = rva0020EAF6(regionID);
	if (region == 0)
		return false;
	if (region->m_hasUiPopupPoint)
	{
		Out0020E493 point;
		*out = *((Rva0020E493 *)region)->rva0020E493(&point);
		return true;
	}
	return GetRegionCenterPoint(regionID, out);
}

// LivingWorldRegionManager::SetRegionReinforcements, retail 0x0020EEC8:
// forwards the settings to the region when it exists (WB logs otherwise).
// ?LivingWorldRegionManager::SetRegionReinforcements present-unmatched
void LivingWorldRegionManager::SetRegionReinforcements(Int regionID, const AsciiString &name, Int a, Int b, Int c, Bool d, Bool e)
{
	Rva0020E89C *region = rva0020EAF6(regionID);
	if (region)
		region->rva003F1AB9(name, a, b, c, d, e);
}

// LivingWorldRegionBonusRule::ParseINI, retail 0x00210AB8: the field-parse
// proc of the region manager's "ConcurrentRegionBonus" entry (retail table
// 0x00BE41E0, offset 0). WorldBuilder names it (WB 0x00B53BB0,
// LivingWorldRegionManager.cpp:220, "A ConcurrentRegionBonus was created
// without any regions in the rule!"). It builds a 0x58-byte rule (rowed ctor
// 0x00210973 under its placeholder name, taking the next rule id), parses it
// with the rule's field table, and hands it to the manager through rowed
// 0x0020F77C, or deletes it when its region list (+0x20) is empty. The rule
// has no vftable (the ctor stores the id at +0), so the delete calls the dtor
// 0x002105A6 directly, as WB does. The id counter and the parse table are
// named here from their roles; retail keeps only their addresses.
struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);	// 0x0002DE78
};

class ObjectCreationNugget;

class Rva002105A6;
class Rva002E2285;
class LivingWorldRegionBonusRule;

// The AsciiString-keyed hash table family (Rva000427195Dtor.cpp and its
// insert units): the instantiations' identical clear() bodies fold to the
// one the ledger rows at 0x003A2A41 on the family placeholder.
struct Rva000427195
{
	void rva003A2A41();										// 0x003A2A41
};

// The table's bucket vector: freed (null-guarded) by the table's dtor after
// clear(), as in Rva000427195Dtor.cpp.
struct Rva0021030EBuckets
{
	~Rva0021030EBuckets()
	{
		if (m_begin)
			_STL::free(m_begin);
	}

	void **m_begin;
	void **m_end;
	void **m_storageEnd;
};

// The +0x38 member: this holder's instantiation of that table (the family's
// layout: an unused word, the bucket vector at +4, the count at +0x10). Its
// destructor is its own copy at 0x0021030E of the family's clear-then-free
// body (0x001FDEDB and its other copies): each copy carries its own EH
// handler, so /OPT:ICF keeps them apart. The class is named for that address.
struct Rva0021030E
{
	~Rva0021030E();
	void *m_unused00;
	Rva0021030EBuckets m_buckets;
	unsigned int m_numElements;
};

// The +0x4C object, deleted through its rowed non-virtual dtor 0x003EF728.
class Rva003EF728
{
public:
	~Rva003EF728();
};

// The +0x2C entries are reached only through their virtual destructor.
class Rva00210830Entry
{
public:
	virtual ~Rva00210830Entry();
};

// The rules' holder (the INI block that owns ConcurrentRegionBonus at +0x5C,
// RegionConqueredSound at +0x50 and RegionEffectsManagerName at +0x54, field
// table 0x00BE41C0). Its dtor is pinned under the placeholder of its deleting
// dtor 0x002109F8; the layout is the dtor's (four strings, three vectors, the
// hash table, the owned +0x4C object, two strings); the +0x20 vector's
// element type is unproven.
class Rva002109F8
{
public:
	~Rva002109F8();

protected:
	AsciiString m_str00;									// +0x00
	AsciiString m_str04;									// +0x04
	AsciiString m_str08;									// +0x08
	AsciiString m_str0C;									// +0x0C
	unsigned char m_pad10[0x20 - 0x10];
	_STL::vector<Int> m_vec20;								// +0x20
	_STL::vector<void *> m_entries;							// +0x2C
	Rva0021030E m_table;									// +0x38
	Rva003EF728 *m_owned;									// +0x4C
	AsciiString m_regionConqueredSound;						// +0x50
	AsciiString m_regionEffectsManagerName;					// +0x54
	unsigned char m_pad58[0x5C - 0x58];
	_STL::vector<LivingWorldRegionBonusRule *> m_rules;		// +0x5C
};

// The same holder under the placeholder of its rowed rule-list append (whose
// parameter the ledger spells ObjectCreationNugget).
class Rva0020F77C : public Rva002109F8
{
public:
	void rva0020F77C(ObjectCreationNugget *rule);			// 0x0020F77C
	void rva0020F34E(void *owner, Rva002E2285 *player);
};

// The rule's region names (+0x20, a vector<AsciiString> per the ctor and
// dtor rows); only its emptiness is read here.
struct RegionBonusRuleRegionList
{
	AsciiString *m_start;
	AsciiString *m_finish;
	AsciiString *m_endOfStorage;

	Bool empty() const { return m_start == m_finish; }
};

// The ids of those regions (+0x2C), resolved when the rule is parsed.
struct RegionBonusRuleRegionIDList
{
	Int *m_start;
	Int *m_finish;
	Int *m_endOfStorage;

	unsigned int size() const { return m_finish - m_start; }
	Int operator[](unsigned int i) const { return m_start[i]; }
};

#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"

// A rule's bonus block (+0x04): a Snapshot with six ints, copied by the rowed
// 0x0020E449 and scaled by the rowed 0x0020E27B; a copy dies inline, leaving
// only the Snapshot vptr store.
class Rva0020E449 : public Snapshot
{
public:
	Rva0020E449(const Rva0020E449 &other);	// 0x0020E449
	virtual ~Rva0020E449() {}
	void rva0020E27B(float scale);			// 0x0020E27B

protected:
	virtual void loadPostProcess(void);
	virtual const char *GetSnapshotName(void) const;
	virtual void xfer(Xfer *xfer);

private:
	Int m_values[6];						// +0x04..+0x18
};

class Rva002105A6
{
public:
	Rva002105A6(Int id);					// 0x00210973
	~Rva002105A6();							// 0x002105A6

	Int m_id;								// +0x00
	Rva0020E449 m_bonus;					// +0x04
	RegionBonusRuleRegionList m_regions;	// +0x20
	RegionBonusRuleRegionIDList m_regionIDs;	// +0x2C
	unsigned char m_pad38[0x58 - 0x38];
};

// The player the rule is tested for, rowed under 0x002E0BC0's placeholder
// owner: the region-owner test there and the player id at +0x14.
class Rva002E071E
{
public:
	bool rva002E071E(const Rva002E071E *) const;
	int rva002E0BC0(Int regionID);			// 0x002E0BC0

	unsigned char m_pad00[0x14];
	Int m_id;								// +0x14
};

// The same player under the placeholder owner of its bonus accumulator
// 0x002E2285, which takes the rule's id word and the scaled bonus.
class Rva002E2285 : public Rva002E071E
{
public:
	void rva002E2285(Int *ruleID, const Rva0020E449 &bonus);	// 0x002E2285
};

class Rva003F287F;
class LivingWorldLogic
{
    friend class Rva0020FDDFHost;
private:
    void AddDelayedRegionVictory(Rva003F287F *, int, unsigned int);
public:
    void LetAIResolveRegionAwardDispute(int, const _STL::vector<int> &, unsigned int);
    void rva002B9A90(int, const _STL::vector<int> &, unsigned int);
	unsigned char m_pad00[0xB0];
	LivingWorldRegionManager *m_regionManager;	// +0xB0
};
extern LivingWorldLogic *TheLivingWorldLogic;

// The rule is the record built above; its ctor and dtor are rowed under the
// record's placeholder name.
class LivingWorldRegionBonusRule : public Rva002105A6
{
public:
	static void ParseINI(INI *ini, void *instance, void *store, const void *userData);
	Bool IsRuleSatisfied(Rva002E071E *player, float *fraction);

private:
	static Int getNextRuleID() { return ++s_ruleCount; }

	static Int s_ruleCount;
	static const FieldParse s_fieldParseTable[];
};

void LivingWorldRegionBonusRule::ParseINI(INI *ini, void *instance, void *store, const void *userData)
{
	Rva002105A6 *rule = new Rva002105A6(getNextRuleID());
	ini->initFromINI(rule, s_fieldParseTable);
	if (!rule->m_regions.empty())
	{
		if (instance)
			((Rva0020F77C *)instance)->rva0020F77C((ObjectCreationNugget *)rule);
	}
	else
	{
		delete rule;
	}
}

// LivingWorldRegionBonusRule::IsRuleSatisfied, retail 0x0020F143 (WB
// 0x00B547A0, LivingWorldRegionManager.cpp:465 names it): false for a rule
// with no regions or when one of its regions is missing (WB asserts) or fails
// the player's rowed test 0x002E0BC0; else true when the player holds at
// least one, with the held fraction stored through the optional pointer.
Bool LivingWorldRegionBonusRule::IsRuleSatisfied(Rva002E071E *player, float *fraction)
{
	if (m_regionIDs.size() == 0)
		return false;

	Int held = 0;
	for (unsigned int i = 0; i < m_regionIDs.size(); ++i)
	{
		Rva0020E89C *region = TheLivingWorldLogic->m_regionManager->rva0020EAF6(m_regionIDs[i]);
		if (region == 0)
			return false;
		const Int &regionID = region->m_id;
		if (!(unsigned char)player->rva002E0BC0(regionID))
			return false;
		if (player->m_id == regionID)
			++held;
	}

	if (held == 0)
		return false;
	if (fraction)
		*fraction = (float)held / (float)m_regionIDs.size();
	return true;
}

// Rva0020F77C::rva0020F34E, retail 0x0020F34E (WB 0x00B53D70, unnamed, in
// LivingWorldRegionManager.cpp between ParseINI and IsRuleSatisfied): every
// rule the player satisfies adds its bonus, scaled by the satisfied fraction,
// to the player. The first argument is unused; its caller passes the object
// whose +8 is this holder.
void Rva0020F77C::rva0020F34E(void *owner, Rva002E2285 *player)
{
	for (unsigned int i = 0; i < m_rules.size(); ++i)
	{
		LivingWorldRegionBonusRule *rule = m_rules[i];
		float fraction = 1.0f;
		if (rule->IsRuleSatisfied(player, &fraction))
		{
			Rva0020E449 bonus(rule->m_bonus);
			bonus.rva0020E27B(fraction);
			player->rva002E2285(&rule->m_id, bonus);
		}
	}
}

// Rva002109F8::~Rva002109F8, retail 0x00210830 (WB 0x00B53690, unnamed, in
// LivingWorldRegionManager.cpp): destroys the +0x2C entries through their
// virtual dtor and the global delete and clears the vector, deletes the owned
// +0x4C object and every rule (non-virtual dtor 0x002105A6), then the members
// unwind in reverse order.
Rva002109F8::~Rva002109F8()
{
	for (unsigned int i = 0; i < m_entries.size(); ++i)
		::delete (Rva00210830Entry *)m_entries[i];
	m_entries.clear();

	delete m_owned;

	for (unsigned int j = 0; j < m_rules.size(); ++j)
		delete m_rules[j];
}

// Rva0021030E::~Rva0021030E, retail 0x0021030E: the holder's +0x38 table
// clears its nodes through the family's folded clear (0x003A2A41), then its
// bucket vector frees the bucket array (null-guarded, C++-linkage free at
// 0x00030830); the bucket member is live (EH state 0) across the clear.
Rva0021030E::~Rva0021030E()
{
	reinterpret_cast<Rva000427195 *>(this)->rva003A2A41();
}

// Native210B38..210C17 RET0; WB B54E00 is the region-manager destructor.
// Its primary Snapshot table has four slots; the +4 observer base has two
// turn callbacks and no virtual destructor. The three pointer vectors are
// at +14, +20 and +34; +34 owns the campaign records destroyed above.
// Preserve the existing address-derived destructor owner rather than infer
// names for the observer interface or the remaining primary-slot methods.
class CreateAHeroData;
class Rva002B7250
{
public:
	void rva002B7250(CreateAHeroData *observer);
};
struct RegionLogicObserverPrefix
{
	unsigned char m_pad00[0x1C];
	Rva002B7250 m_observers;
};
class Rva0020FB41Outer
{
public:
	void rva0020F685();
};
class RegionTurnObserverView
{
public:
	virtual void BeginTurn(int, int) = 0;
	virtual void EndTurn(int, int) = 0;
	~RegionTurnObserverView() {}
};
class Rva00210B38 : public Snapshot, public RegionTurnObserverView
{
public:
	virtual ~Rva00210B38();
protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName(void) const;
	virtual void xfer(Xfer *);
	virtual void BeginTurn(int, int);
	virtual void EndTurn(int, int);
private:
	void *m_campaign08;
	int m_key0C, m_key10;
	_STL::vector<void *> m_pending;
	_STL::vector<void *> m_completed;
	unsigned char m_pad2C[8];
	_STL::vector<void *> m_campaigns;
};

Rva00210B38::~Rva00210B38()
{
	for (unsigned int i = 0; i < m_campaigns.size(); ++i)
		delete static_cast<Rva002109F8 *>(m_campaigns[i]);
	m_campaigns.clear();
	reinterpret_cast<Rva0020FB41Outer *>(this)->rva0020F685();
	// The holder at singleton+1C removes the +4 observer subobject. Its
	// existing ABI spells the opaque argument CreateAHeroData; this call
	// establishes its address, not that unrelated class identity.
	reinterpret_cast<RegionLogicObserverPrefix *>(TheLivingWorldLogic)->m_observers.rva002B7250(reinterpret_cast<CreateAHeroData *>(
		static_cast<RegionTurnObserverView *>(this)));
}


// WB B583A0 names CheckForBattles; retail20FDDF..2100E6 is the entire775B
// RET0 body. Region+164 contains army IDs; army+78/+2C marks participation,
// player+44 distinguishes human control and region+13C is its owner ID.
// The two local pointer containers use the already-owned ModuleData vector
// ABI as opaque word storage. This does not identify armies or players as
// ModuleData. Typed pointer locals preserve native lifetime/evaluation order.
// The existing delayed-victory ABI spells its player word int; preserve the
// pointer bits here, as both native images pass the player object itself.
class Rva002E2903Player { public: char pad00[0x44]; int field44; };
class Rva003F02E4 { public: bool rva003F0336(const Rva002E071E *); };
class Rva003F287F;
struct Rva002B488EResult;
class Rva002BA8F1Logic
{
public:
    Rva002B488EResult *rva002B488E(int);
    Rva002E2903Player *find(int, unsigned int *);
};
struct RegionArmyState { char pad00[0x2C]; int field2C; };
struct RegionArmyView { char pad00[0x54]; int owner54; char pad58[0x20]; RegionArmyState *state78; };
struct RegionBattleView
{
    char pad00[0x13C];
    int owner13C;
    int getOwner() const { return owner13C; }
    char pad140[0x24];
    _STL::vector<int> armies164;
};
struct RegionCampaignView { char pad00[0x2C]; _STL::vector<RegionBattleView *> regions; };
struct RegionBattlePoint { float x,y; };
class RegionSlotsAccess : public RegionSlots { public: Rva002E071E *get(unsigned int index) const { return reinterpret_cast<Rva002E071E *>(const_cast<ModuleData *>((*this)[index])); } };
class Rva002B2702B0 { public: bool rva0020EA58(void *, float *); };
class Rva0020FDDFHost
{
public:
    void rva0020FDDF();
private:
    char pad00[8];
    RegionCampaignView *campaign08;
};

void Rva0020FDDFHost::rva0020FDDF()
{
    _STL::vector<RegionBattleView *> *regions=&campaign08->regions;
    RegionSlots armies;
    RegionSlots players;
    for (unsigned int i=0; i<regions->size(); ++i) {
        RegionBattleView *region=(*regions)[i];
        _STL::vector<int> *ids=&region->armies164;
        if (ids->empty()) continue;
        reinterpret_cast<_STL::vector<void *> *>(&players)->clear();
        reinterpret_cast<_STL::vector<void *> *>(&armies)->clear();
        for (unsigned int j=0; j<ids->size(); ++j) {
            RegionArmyView *army=reinterpret_cast<RegionArmyView *>(reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->rva002B488E((*ids)[j]));
            if (army) {
                army->state78->field2C=1;
                armies.push_back(reinterpret_cast<const ModuleData *const &>(army));
                int owner=army->owner54;
                Rva002E2903Player *player=reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(owner,0);
                if (player) {
                    if (_STL::find(reinterpret_cast<int *>(players.begin()),reinterpret_cast<int *>(players.end()),reinterpret_cast<const int &>(player))==reinterpret_cast<int *>(players.end()))
                        players.push_back(reinterpret_cast<const ModuleData *const &>(player));
                }
            }
        }
        if (players.size()==0) continue;
        if (players.size()==1) {
            Rva002E071E *player=reinterpret_cast<Rva002E071E *>(const_cast<ModuleData *>(players[0]));
            if (region->owner13C==-1) {
                TheLivingWorldLogic->AddDelayedRegionVictory(reinterpret_cast<Rva003F287F *>(region),reinterpret_cast<int>(player),0);
            } else if (!(unsigned char)player->rva002E0BC0(region->getOwner())) {
                if (reinterpret_cast<Rva003F02E4 *>(region)->rva003F0336(player)) {
                    Rva002E2903Player *owner=reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(region->getOwner(),0);
                    if (owner) {
                        players.push_back(reinterpret_cast<const ModuleData *const &>(owner));
                        RegionBattlePoint point;
                        reinterpret_cast<Rva002B2702B0 *>(this)->rva0020EA58(region,&point.x);
                        reinterpret_cast<LivingWorldRegionManager *>(this)->AddBattle(region,armies,players,point);
                    }
                } else {
                    TheLivingWorldLogic->AddDelayedRegionVictory(reinterpret_cast<Rva003F287F *>(region),reinterpret_cast<int>(player),1);
                }
            }
        } else if (players.size()>=2) {
            bool hostile=false;
            for (unsigned int k=1; k<players.size(); ++k) {
                const Rva002E071E *other=reinterpret_cast<const Rva002E071E *>(players[k]);
                Rva002E071E *first=reinterpret_cast<Rva002E071E *>(const_cast<ModuleData *>(players[0]));
                if (!first->rva002E071E(other)) {
                    hostile=true; break;
                }
            }
            if (!hostile && reinterpret_cast<Rva003F02E4 *>(region)->rva003F0336(reinterpret_cast<const Rva002E071E *>(players[0]))) {
                Rva002E2903Player *owner=reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(region->getOwner(),0);
                if (owner) {
                    players.push_back(reinterpret_cast<const ModuleData *const &>(owner)); hostile=true;
                }
            }
            if (hostile) {
                RegionBattlePoint point;
                reinterpret_cast<Rva002B2702B0 *>(this)->rva0020EA58(region,&point.x);
                reinterpret_cast<LivingWorldRegionManager *>(this)->AddBattle(region,armies,players,point);
            } else if (region->owner13C==-1 || !(unsigned char)reinterpret_cast<const RegionSlotsAccess *>(&players)->get(0)->rva002E0BC0(region->getOwner())) {
                bool human=false;
                for (unsigned int n=0; n<players.size(); ++n) {
                    if (reinterpret_cast<const Rva002E2903Player *>(players[n])->field44==0) { human=true; break; }
                }
                if (human) {
                    unsigned int flags=0x20;
                    if (region->owner13C!=-1) flags=0x21;
                    TheLivingWorldLogic->rva002B9A90(reinterpret_cast<int>(region),reinterpret_cast<const _STL::vector<int> &>(players),flags);
                } else {
                    unsigned int flags=0x20;
                    if (region->owner13C!=-1) flags=0x21;
                    TheLivingWorldLogic->LetAIResolveRegionAwardDispute(reinterpret_cast<int>(region),reinterpret_cast<const _STL::vector<int> &>(players),flags);
                }
            }
        }
    }
}
