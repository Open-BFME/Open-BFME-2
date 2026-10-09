// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /arch:SSE
// LivingWorldRegionManager.cpp -- region-manager members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function and the region overload it calls (0x0020EA58); retail supplies
// the bytes. The region id lookup is the rowed 0x0020EAF6 accessor.

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

class LivingWorldRegionManager
{
public:
	void EnumeratePendingBattles(PendingBattleVisitor &visitor) const;
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

// The manager's rule-list append, rowed with an ObjectCreationNugget parameter.
class Rva0020F77C
{
public:
	void rva0020F77C(ObjectCreationNugget *rule);			// 0x0020F77C
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

class Rva002105A6
{
public:
	Rva002105A6(Int id);					// 0x00210973
	~Rva002105A6();							// 0x002105A6

	Int m_id;								// +0x00
	unsigned char m_pad04[0x20 - 0x04];
	RegionBonusRuleRegionList m_regions;	// +0x20
	RegionBonusRuleRegionIDList m_regionIDs;	// +0x2C
	unsigned char m_pad38[0x58 - 0x38];
};

// The player the rule is tested for, rowed under 0x002E0BC0's placeholder
// owner: the region-owner test there and the player id at +0x14.
class Rva002E071E
{
public:
	int rva002E0BC0(Int regionID);			// 0x002E0BC0

	unsigned char m_pad00[0x14];
	Int m_id;								// +0x14
};

class LivingWorldLogic
{
public:
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
