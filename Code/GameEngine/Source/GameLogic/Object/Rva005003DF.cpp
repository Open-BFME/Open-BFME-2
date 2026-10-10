// cl: /O1 /arch:SSE /G7 /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// ?rva005003DF@Rva005003DF@@QBEHHABHPAH@Z
// stlport
// NEAR: register-save/allocation mismatch only; retail keeps the player
// index i in edi and the hoisted inner-map pointer in ebx, this source swaps them.
//
// ?rva005003DF@Rva005003DF@@QBEHHABHPAH@Z, retail 0x005003DF (235 bytes).
// Nearest-entry search over the int multimap at this+0x10 (the receiver of
// the rowed const equal_range wrapper 0x005003C7 keeps its tree there too).
// The key passed by reference is looked up in the int-key map at 0x00E04544
// (the rowed rva0050059A/rva00500606 read the same global: each mapped value
// holds an int-to-int map at +0x0C). For every LivingWorld player (vector
// +0x8C of TheLivingWorldLogic; rowed rva002B52A8 by index; player id
// +0x14) that the pinned rva002E0BC0 on the player found by the rowed
// find(id 0) 0x002B51F8 rejects: each multimap entry under that player id
// reads its value's entry in that inner map and keeps the smallest (start
// 9999). Writes the smallest to the optional out pointer and returns the
// best entry's mapped value. One caller 0x0059CB05 (Ghidra 0x0059C93C).
// WorldBuilder twin 0x01300540 (callgraph evidence).

#include <map>
#include <vector>

typedef _STL::map<int, int> Rva005003DFIntMap;
typedef _STL::multimap<int, int> Rva005003DFIntMultiMap;

struct Rva005003DFDistances
{
	char m_pad00[0x0C];
	Rva005003DFIntMap m_distances; // +0x0C
};

extern unsigned int g_Va00E04544;

class Rva002E0BC0Helper
{
public:
	unsigned char rva002E0BC0(int id);
};

class Rva002E2903Player
{
public:
	char m_pad00[0x14];
	int m_id; // +0x14
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
	Rva002E2903Player *rva002B52A8(int index);
};

class LivingWorldLogic
{
public:
	int getNumPlayers() const { return m_players.size(); }
	char m_pad00[0x8C];
	_STL::vector<Rva002E2903Player *> m_players; // +0x8C
};

extern LivingWorldLogic *TheLivingWorldLogic;

class Rva005003DF
{
public:
	int rva005003DF(int playerId, const int &key, int *outBest) const;
private:
	char m_pad00[0x10];
	Rva005003DFIntMultiMap m_entries; // +0x10
};

int Rva005003DF::rva005003DF(int playerId, const int &key, int *outBest) const
{
	Rva005003DFIntMap::iterator found = ((Rva005003DFIntMap *)&g_Va00E04544)->find(key);
	int best = 9999;
	Rva005003DFIntMultiMap::const_iterator bestIt;
	for (int i = 0; i < TheLivingWorldLogic->getNumPlayers(); ++i)
	{
		int id = ((Rva002BA8F1Logic *)TheLivingWorldLogic)->rva002B52A8(i)->m_id;
		Rva002E0BC0Helper *player = (Rva002E0BC0Helper *)((Rva002BA8F1Logic *)(TheLivingWorldLogic?TheLivingWorldLogic:TheLivingWorldLogic))->find(playerId, 0);
		if (!player->rva002E0BC0(id))
		{
			_STL::pair<Rva005003DFIntMultiMap::const_iterator, Rva005003DFIntMultiMap::const_iterator> range = m_entries.equal_range(id);
			for (Rva005003DFIntMultiMap::const_iterator it = range.first; it != range.second; ++it)
			{
				int distance = ((Rva005003DFDistances *)&found->second)->m_distances.find(it->second)->second;
				if (distance < best)
				{
					best = distance;
					bestIt = it;
				}
			}
		}
	}
	if (outBest)
		*outBest = best;
	return bestIt->second;
}
