// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva00500659@Rva0059CFAACallee@@QAE?AV?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@HPAH0@Z
// retail 0x00500659..0x00500770 (279 bytes) thiscall RET 0x10 hidden result.
//
// Looks up the territory key (*territory) in the int-key map at 0x00E04544
// and the player through TheLivingWorldLogic->find(playerId 0); then walks the
// int-key map at this+4 and for every key the player does NOT pass
// rva002E0BC0 on scans the 20-byte entries of the vector at mapped+0x14:
// the territory's inner int map (mapped+0x0C) gives each entry's distance
// (*entry->+0x10); entries at the smallest distance (start 9999) are
// collected by their +0 id. Writes the smallest distance to *count when given
// and returns the collected ids by value.
// Evidence (target): callees int-key _Rb_tree::_M_find 0x00388F63 (twice)
// Rva002BA8F1Logic::find 0x002B51F8 / Rva002E071E::rva002E0BC0 0x002E0BC0 and
// _Rb_global<bool>::_M_increment 0x00024250; global g_Va00E04544 (data
// 0x00A04544) and TheLivingWorldLogic (0x009FEF10). Twin of rowed
// 0x004FFA6E/0x004FF9DC (same maps and entry layout). WorldBuilder 0x01300340
// has the same calls and loop structure (unnamed).
// The result vector is not vector<int>: retail calls the 4-byte enum
// instantiations (erase 0x00532803 copy loop through 0x0025BF40 / push_back
// 0x002E01C6 / copy ctor 0x0054878E) while vector<int>'s own erase and
// push_back are the memmove copies at 0x00688710/0x00688940. Which enum is
// not established; ObjectID is a stand-in that carries existing ledger names
// for all three callees. Names are address-derived.

#include <map>
#include <vector>

enum ObjectID
{
	INVALID_ID = 0
};

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

typedef _STL::map<int, int> Rva00500659IntMap;

struct Rva00500659Entry
{
	ObjectID m_id;
	char m_pad04[0xc];
	int *m_territory;
};

struct Rva00500659Value
{
	char m_pad00[0x14];
	_STL::vector<Rva00500659Entry> m_entries;
};

class Rva0059CFAACallee
{
public:
	_STL::vector<ObjectID> rva00500659(int playerId, int *territory, int *count);
private:
	int m_00;
	_STL::map<int, Rva00500659Value> m_map;
};

_STL::vector<ObjectID> Rva0059CFAACallee::rva00500659(int playerId, int *territory, int *count)
{
	Rva00500659IntMap::iterator from = ((Rva00500659IntMap *)&g_Va00E04544)->find(*territory);
	Rva002E071E *player = (Rva002E071E *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerId, 0);
	_STL::map<int, Rva00500659Value>::iterator it = m_map.begin();
	int best = 9999;
	_STL::vector<ObjectID> result;
	result.clear();
	for (; it != m_map.end(); ++it)
	{
		if (!(unsigned char)player->rva002E0BC0(it->first))
		{
			for (_STL::vector<Rva00500659Entry>::iterator e = it->second.m_entries.begin(); e != it->second.m_entries.end(); ++e)
			{
				int id = *e->m_territory;
				Rva00500659IntMap *distances = (Rva00500659IntMap *)((char *)&from->second + 0x0C);
				int distance = distances->find(id)->second;
				if (distance == best)
				{
					result.push_back(e->m_id);
				}
				else if (distance < best)
				{
					best = distance;
					result.clear();
					result.push_back(e->m_id);
				}
			}
		}
	}
	if (count)
		*count = best;
	return result;
}
