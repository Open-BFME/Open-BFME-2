// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?DefendHomeTerritory@LivingWorldAIArmyMover@@QAEXPAV?$vector@UBfmePod20@@V?$allocator@UBfmePod20@@@_STL@@@_STL@@HHPAVRva0059CFAACallee@@@Z
// retail 0x0059C010..0x0059C15B (331 bytes) thiscall RET 0x10; this unused.
//
// Identity (target + WorldBuilder): the WB twin at 0x014FC870 sits in
// LivingWorldAIArmyMover.cpp (assert "closestHero != NULL" line 503) with the
// same callee graph: player lookup 0x002B51F8; a region vector filled through
// rowed 0x004FD4D4 and 0x004FD533 on the active campaign's scenario
// (TheCampaignManager vector at +0x14 indexed by +0x10 then campaign +0x1C);
// per region (+0x12C id) the territory lookup 0x004FF997 then 0x00500659 (a
// vector returned by value and discarded; it reports the defender count) and
// 0x004FFB00 (closest hero plus its distance); a move record is appended
// through rowed vector<BfmePod20>::push_back 0x0059B8C6 with the next step
// from rowed 0x005009AA. Retail caller 0x0059C979 (0x0059C93C) passes its own
// ECX and four stack words. The WB name is the only identity source for the
// method; the record fields, owner views and argument names are inferred.
// Callee signatures 0x004FFB00/0x00500659 are read from their bodies: both are
// thiscall (ECX saved); 0x00500659 writes the hidden result (RET 0x10) and
// 0x004FFB00 returns its best record in EAX.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

class ModuleData;
class Rva002E2903Player;

struct BfmePod20
{
	int m_id;
	bool m_flag;
	int m_08;
	int m_0c;
	int m_step;
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class LivingWorldScenario
{
public:
	class Scenario;
};

class LivingWorldScenario::Scenario
{
public:
	void rva004FD533(int key, int unused, int *out) const;
};

class Rva004FD4D4
{
public:
	void rva004FD4D4(int playerId,
		_STL::vector<const ModuleData *> *records, int *maxOut) const;
};

struct Rva00E02D6CCampaign
{
	char m_pad00[0x1c];
	LivingWorldScenario::Scenario *m_scenario;
};

class Rva00E02D6C
{
public:
	Rva00E02D6CCampaign *getCurrentCampaign()
	{
		return m_campaignVector[m_campaignIndex];
	}

private:
	char m_pad00[0x10];
	int m_campaignIndex;
	_STL::vector<Rva00E02D6CCampaign *> m_campaignVector;
};
extern Rva00E02D6C *TheCampaignManager;

class Rva004FF997Owner
{
public:
	int rva004FF997(int id);
};

struct Rva004FFB00Hero
{
	int m_id;
	char m_pad04[0xc];
	int *m_region;
};

class Rva0059CFAACallee
{
public:
	_STL::vector<int> rva00500659(int playerId, int *territory, int *count);
	Rva004FFB00Hero *rva004FFB00(int playerId, int *territory, int *distance);
};

int rva005009AA(int from, int to);

class LivingWorldAIArmyMover
{
public:
	void DefendHomeTerritory(_STL::vector<BfmePod20> *moves, int playerId,
		int unused, Rva0059CFAACallee *armies);
};

void LivingWorldAIArmyMover::DefendHomeTerritory(_STL::vector<BfmePod20> *moves,
	int playerId, int unused, Rva0059CFAACallee *armies)
{
	Rva002E2903Player *player =
		((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerId, 0);
	int team = *(int *)((char *)player + 0x34);
	_STL::vector<const ModuleData *> regions;
	regions.clear();
	int maxA = 0;
	int maxB = 0;
	LivingWorldScenario::Scenario *scenario =
		TheCampaignManager->getCurrentCampaign()->m_scenario;
	((Rva004FD4D4 *)scenario)->rva004FD4D4(playerId, &regions, &maxA);
	scenario->rva004FD533(team, (int)&regions, &maxB);
	for (unsigned int i = 0; i < regions.size(); ++i)
	{
		int regionID = *(int *)((char *)regions[i] + 0x12c);
		int *territory = (int *)((Rva004FF997Owner *)armies)->rva004FF997(regionID);
		int defenders;
		armies->rva00500659(playerId, territory, &defenders);
		int distance;
		Rva004FFB00Hero *closestHero = armies->rva004FFB00(playerId, territory, &distance);
		if (closestHero != 0)
		{
			if (defenders < distance + 1 || defenders == 1)
			{
				int step = rva005009AA(*closestHero->m_region, *territory);
				BfmePod20 move;
				move.m_id = closestHero->m_id;
				move.m_flag = true;
				move.m_08 = 0;
				move.m_step = step;
				moves->push_back(move);
			}
		}
	}
}
