// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/moduledata /DBFME_SNAPSHOT_NAME_SLOT
// stlport
//
// ?rva004EEE38@Rva004EF2FAPrimary@@QAEXH@Z retail 0x004EEE38..0x004EF039
// (513 bytes EH RET 4). The end-of-turn statistics collection of the
// living-world score keeper (WorldBuilder twin 0x010F1230
// LivingWorldScoreKeeper::collectEndOfTurnStats in LivingWorldScoreKeeper.cpp
// with its asserts and stat dump stripped). Called through the rowed
// interface thunk 0x004EF2FA. Target evidence:
//  - nothing when the turn equals the +0x7C last turn (then stored) or the
//    +0xF4 owner ID is -1; the owner comes from the rowed
//    Rva002BA8F1Logic::find 0x002B51F8 on TheLivingWorldLogic; the region
//    manager is its +0xB0 and the campaign that manager's +0x08;
//  - the +0x58 bool vector is resized (rowed 0x0006DB1C) to the campaign's
//    +0x5C rule count; per rule the old bit is read (rowed operator[]
//    0x0006BE1F) a non-null rule rewrites it through the rowed
//    IsRuleSatisfied 0x0020F143 and _Bit_reference::operator= 0x00066099;
//    a newly set bit appends the turn to the +0x34 list (rowed push_back
//    0x004DFCB0) and a cleared one bumps +0xF0;
//  - a per-turn stats record (vtable 0x00862A28 over Snapshot; unwind
//    state 0 runs its folded dtor 0x0049B47C) counts the campaign's +0x2C
//    regions whose +0x13C owner matches and the armies each lists through
//    the rowed 0x003F287F (a local vector; unwind state 1 its dtor) and
//    the owner's +0x1B8 entries' +0x78 eight-byte +0x40 lists; it is
//    appended to +0x28 by the rowed 0x004EE9B1.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "Common/Snapshot.h"

typedef short Short;

class ModuleData;
class Rva002E2903Player;
class Rva002E071E;

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

class LivingWorldRegionBonusRule
{
public:
	bool IsRuleSatisfied(Rva002E071E *player, float *value);
};

class Rva003F287F
{
public:
	void rva003F287F(_STL::vector<const ModuleData *> &out);

	char m_pad000[0x13C];
	int m_ownerID; // +0x13C
};

struct Rva004EEE38Campaign
{
	char m_pad00[0x2C];
	_STL::vector<Rva003F287F *> m_regions;                // +0x2C
	char m_pad38[0x5C - 0x38];
	_STL::vector<LivingWorldRegionBonusRule *> m_rules;   // +0x5C
};

struct Rva004EEE38RegionManager
{
	char m_pad00[0x08];
	Rva004EEE38Campaign *m_campaign; // +0x08
};

struct Rva004EEE38LogicView
{
	char m_pad000[0xB0];
	Rva004EEE38RegionManager *m_regionManager; // +0xB0
};

struct Rva004EEE38Pair
{
	int a;
	int b;
};

struct Rva004EEE38Army
{
	char m_pad00[0x40];
	_STL::vector<Rva004EEE38Pair> m_entries; // +0x40
};

struct Rva004EEE38Entry
{
	char m_pad00[0x78];
	Rva004EEE38Army *m_army; // +0x78
};

struct Rva004EEE38PlayerView
{
	char m_pad000[0x1B8];
	_STL::vector<Rva004EEE38Entry *> m_entries; // +0x1B8
};

class Rva004EE1A9 : public Snapshot
{
public:
	Rva004EE1A9() : m_field04(0), m_field06(0), m_field08(0) {}
	virtual ~Rva004EE1A9() {}

protected:
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);

public:
	Short m_field04;
	Short m_field06;
	Short m_field08;
};

struct Elem003AF8C0;

class Rva004EE6D0
{
public:
	void push_back(const Elem003AF8C0 &x);

private:
	void *m_start;
	void *m_finish;
	void *m_end;
};

class Rva004EF2FAPrimary
{
public:
	virtual void primarySlot();
	void rva004EEE38(int turn);

private:
	char m_pad004[0x28 - 0x04];
	Rva004EE6D0 m_perTurnStats;                     // +0x28
	_STL::vector<const ModuleData *> m_turnsGained; // +0x34
	char m_pad040[0x58 - 0x40];
	_STL::vector<bool> m_rulesHeld;                 // +0x58
	char m_pad06C[0x7C - 0x6C];
	int m_lastTurn;                                 // +0x7C
	char m_pad080[0xF0 - 0x80];
	int m_rulesLost;                                // +0xF0
	int m_ownerID;                                  // +0xF4
};

void Rva004EF2FAPrimary::rva004EEE38(int turn)
{
	if (m_lastTurn == turn)
		return;
	m_lastTurn = turn;

	if (m_ownerID == -1)
		return;

	Rva002E2903Player *owner = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(m_ownerID, 0);
	if (owner == 0)
		return;

	Rva004EEE38RegionManager *regionManager = reinterpret_cast<Rva004EEE38LogicView *>(TheLivingWorldLogic)->m_regionManager;
	if (regionManager == 0)
		return;

	Rva004EEE38Campaign *campaign = regionManager->m_campaign;
	if (campaign == 0)
		return;

	_STL::vector<LivingWorldRegionBonusRule *> &rules = campaign->m_rules;
	m_rulesHeld.resize(rules.size(), false);
	for (unsigned int i = 0; i < rules.size(); ++i)
	{
		bool wasHeld = m_rulesHeld[i];
		if (rules[i] != 0)
			m_rulesHeld[i] = rules[i]->IsRuleSatisfied(reinterpret_cast<Rva002E071E *>(owner), 0);
		if (!wasHeld)
		{
			if (m_rulesHeld[i])
				m_turnsGained.push_back(reinterpret_cast<const ModuleData *const &>(turn));
		}
		else
		{
			if (!m_rulesHeld[i])
				++m_rulesLost;
		}
	}

	{
		Rva004EE1A9 stats;
		_STL::vector<Rva003F287F *> &regions = campaign->m_regions;
		for (_STL::vector<Rva003F287F *>::iterator it = regions.begin(), end = regions.end(); it != end; ++it)
		{
			Rva003F287F *region = *it;
			if (region != 0 && region->m_ownerID == m_ownerID)
			{
				++stats.m_field04;
				_STL::vector<const ModuleData *> armies;
				region->rva003F287F(armies);
				stats.m_field08 += armies.size();
			}
		}

		_STL::vector<Rva004EEE38Entry *> &entries = reinterpret_cast<Rva004EEE38PlayerView *>(owner)->m_entries;
		for (_STL::vector<Rva004EEE38Entry *>::iterator e = entries.begin(), eEnd = entries.end(); e != eEnd; ++e)
		{
			if (*e != 0 && (*e)->m_army != 0)
				stats.m_field06 += (*e)->m_army->m_entries.size();
		}

		m_perTurnStats.push_back(reinterpret_cast<const Elem003AF8C0 &>(stats));
	}
}
