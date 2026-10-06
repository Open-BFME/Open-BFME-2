// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Ghidra boundary 0x004FD4D4/95. Target evidence: look up a player through
// rowed 0x002B51F8 using the first argument; read its dword at +0x34; range the
// tree at this+0x50 through rowed equal_range 0x004FCD6D; pass each node's +0x14
// value to rowed LivingWorldScenario::PlayerDefeatCondition::QueryRegionsAndNumbers
// at 0x004FCDCF; advance with rowed iterator increment 0x00024250. The owner
// type and key meaning remain unresolved. The int-valued tree spelling below
// binds the existing 4-byte equal_range body; node values are interpreted as
// condition pointers only because the target passes the loaded dword as ECX.

#include <map>
#include <vector>

class ModuleData;
class Rva002E2903Player;

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
	class PlayerDefeatCondition;
};

class LivingWorldScenario::PlayerDefeatCondition
{
public:
	void QueryRegionsAndNumbers(void *player,
		_STL::vector<const ModuleData *> *records, int *maxOut);
};

class Rva004FD4D4
{
public:
	void rva004FD4D4(int playerId,
		_STL::vector<const ModuleData *> *records, int *maxOut) const;

private:
	char m_pad00[0x50];
	_STL::multimap<int, int> m_entries;
};

void Rva004FD4D4::rva004FD4D4(int playerId,
	_STL::vector<const ModuleData *> *records, int *maxOut) const
{
	Rva002E2903Player *player =
		((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerId, 0);
	*maxOut = 0;
	int key = *(int *)((char *)player + 0x34);
	_STL::pair<_STL::multimap<int, int>::const_iterator,
		_STL::multimap<int, int>::const_iterator> range = m_entries.equal_range(key);

	for (_STL::multimap<int, int>::const_iterator it = range.first;
		it != range.second; ++it)
	{
		LivingWorldScenario::PlayerDefeatCondition *condition =
			(LivingWorldScenario::PlayerDefeatCondition *)(*it).second;
		condition->QueryRegionsAndNumbers(player, records, maxOut);
	}
}
