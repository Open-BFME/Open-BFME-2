// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva004FFA6E@Rva004FFA6E@@QAE_NHHABQAURva004FFA6ESource@@@Z
// Retail 0x004FFA6E..0x004FFB00 (146 bytes).
// Looks up the source id (source->+0x14) in the int-key map at 0x00E04544
// and the player through TheLivingWorldLogic->find(playerIndex 0); then walks
// the int-key map at receiver+4 and for every key the player passes
// rva002E0BC0 on scans the 20-byte entries of the vector at mapped+0x14
// returning true as soon as the source's inner int map (mapped+0x0C) holds a
// value <= limit for an entry's id (*entry->+0x10). Returns false otherwise.
// Evidence (target): callees int-key _Rb_tree::_M_find 0x00388F63 (twice)
// Rva002BA8F1Logic::find 0x002B51F8 / Rva002E071E::rva002E0BC0 0x002E0BC0 and
// _Rb_global<bool>::_M_increment 0x00024250 are rowed; global
// g_Va00E04544 (data 0x00A04544) and TheLivingWorldLogic (0x009FEF10).
// Rva0050059A reads the same global map's mapped value with its inner map at
// +0x0C. Twin of 0x004FF9DC (which skips keys the player passes instead).
// WorldBuilder 0x012FFD00 has the same calls and loop structure (unnamed).
// Meanings and class identities are unproven; names are address-derived.

#include <map>
#include <vector>

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

typedef _STL::map<int, int> Rva004FFA6EIntMap;

struct Rva004FFA6ESource
{
	char m_pad00[0x14];
	int m_id;
};

struct Rva004FFA6EEntry
{
	char m_pad00[0x10];
	int *m_id;
};

struct Rva004FFA6EValue
{
	char m_pad00[0x14];
	_STL::vector<Rva004FFA6EEntry> m_entries;
};

class Rva004FFA6E
{
public:
	bool rva004FFA6E(int playerIndex, int limit, Rva004FFA6ESource *const &source);
private:
	int m_00;
	_STL::map<int, Rva004FFA6EValue> m_map;
};

bool Rva004FFA6E::rva004FFA6E(int playerIndex, int limit, Rva004FFA6ESource *const &source)
{
	Rva004FFA6EIntMap::iterator from = ((Rva004FFA6EIntMap *)&g_Va00E04544)->find(source->m_id);
	Rva002E071E *player = (Rva002E071E *)((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerIndex, 0);
	for (_STL::map<int, Rva004FFA6EValue>::iterator it = m_map.begin(); it != m_map.end(); ++it)
	{
		if ((unsigned char)player->rva002E0BC0(it->first))
		{
			for (_STL::vector<Rva004FFA6EEntry>::iterator e = it->second.m_entries.begin(); e != it->second.m_entries.end(); ++e)
			{
				int id = *e->m_id;
				Rva004FFA6EIntMap *distances = (Rva004FFA6EIntMap *)((char *)&from->second + 0x0C);
				if (distances->find(id)->second <= limit)
					return true;
			}
		}
	}
	return false;
}
