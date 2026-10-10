// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva004FFB00@Rva0059CFAACallee@@QAEPAURva004FFB00Hero@@HPAH0@Z
// retail 0x004FFB00..0x004FFBB5 (181 bytes) thiscall RET 0xC.
//
// Twin of the rowed 0x00500659 (same maps and 20-byte entry layout) that keeps
// a single entry: looks up the territory key (*territory) in the int-key map
// at 0x00E04544 and the player through TheLivingWorldLogic->find(playerId 0);
// then walks the int-key map at this+4 and for every key the player DOES pass
// rva002E0BC0 on scans the entries of the vector at mapped+0x14; the
// territory's inner int map (mapped+0x0C) gives each entry's distance
// (*entry->+0x10) and the last entry at or below the best so far (start 9999)
// wins. Writes the best distance through the third argument when given and
// returns the winning entry in EAX (0 when none).
// Evidence (target): thiscall RET 0xC (ECX saved; three stack arguments);
// callees int-key _Rb_tree::_M_find 0x00388F63 (three times; the inner find
// runs twice per accepted entry) Rva002BA8F1Logic::find 0x002B51F8
// Rva002E071E::rva002E0BC0 0x002E0BC0 and _Rb_global<bool>::_M_increment
// 0x00024250. Callers 0x0059BC3A 0x0059C0E1 (rowed DefendHomeTerritory: WB
// assert closestHero != NULL) 0x0059CF06 0x0059D019 0x0059D124 0x0059D8CA
// ignore or test EAX. WorldBuilder twin 0x013001F0 (unnamed). The spelling
// is the existing pin; names are address-derived.

#include <map>
#include <vector>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern unsigned int g_Va00E04544;

class Rva002E2903Player;

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *outIndex);
};

class Rva002E071E
{
public:
	int rva002E0BC0(int id);
};

typedef _STL::map<int, int> Rva004FFB00IntMap;

struct Rva004FFB00Hero
{
	int m_id;
	char m_pad04[0xc];
	int *m_region;
};

struct Rva004FFB00Value
{
	char m_pad00[0x14];
	_STL::vector<Rva004FFB00Hero> m_entries;
};

class Rva0059CFAACallee
{
public:
	Rva004FFB00Hero *rva004FFB00(int playerId, int *territory, int *distance);
private:
	int m_00;
	_STL::map<int, Rva004FFB00Value> m_map;
};

Rva004FFB00Hero *Rva0059CFAACallee::rva004FFB00(int playerId, int *territory, int *distance)
{
	Rva004FFB00IntMap::iterator from = ((Rva004FFB00IntMap *)&g_Va00E04544)->find(*territory);
	Rva002E071E *player = (Rva002E071E *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerId, 0);
	Rva004FFB00Hero *closest = 0;
	int best = 9999;
	for (_STL::map<int, Rva004FFB00Value>::iterator it = m_map.begin(); it != m_map.end(); ++it)
	{
		if ((unsigned char)player->rva002E0BC0(it->first))
		{
			for (_STL::vector<Rva004FFB00Hero>::iterator e = it->second.m_entries.begin(); e != it->second.m_entries.end(); ++e)
			{
				int id = *e->m_region;
				Rva004FFB00IntMap *distances = (Rva004FFB00IntMap *)((char *)&from->second + 0x0C);
				if (distances->find(id)->second <= best)
				{
					best = distances->find(id)->second;
					closest = e;
				}
			}
		}
	}
	if (distance)
		*distance = best;
	return closest;
}
