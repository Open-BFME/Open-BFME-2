// cl: /MD
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"
// AITacticSiege::sideHasIdleSiegeWeapons, retail 0x005DC8A2, 97 bytes.
// Predicate over holder from TheSkirmishAIManager map lookup keyed by Player at this+0x24.
// Holder's first dword dereferenced, then index loop over bucket_count with
// rowed rva0025BFF8 getter; match requires Object+0x304 == Player+0x2ec and
// [Object+4]+0x520 == 7. Evidence: callees rowed (0x002A8F24 0x0025BFF8
// 0x002BEDAB bucket_count), callers 0x005A9AD8 0x005A9CBE pass this in ecx.
// Named from WorldBuilder AITacticSiege::sideHasIdleSiegeWeapons (asserts in
// AITacticSiege.cpp; same 0x002A8F24 stats, bucket_count and 0x0025BFF8
// walk); both callers are the siege tactics' canRun.

class Player;
class Object;

class Player
{
public:
	char m_pad0[0x54];
	int m_playerIndex; // +0x54 (as in Rva002A8F24.cpp)
	char m_pad1[0x2EC - 0x58];
	int m_2EC; // +0x2EC
};

class Object
{
public:
	char m_pad00[0x4];
	void *m_p4;
	char m_pad08[0x38 - 8];
	Coord3D position;
	char m_pad44[0x74 - 0x44];
	ObjectID id;
	char m_pad78[0x304 - 0x78];
	int m_304;
	char m_pad308[0x438 - 0x308];
	unsigned char m_438;
};

struct Inner520
{
	char m_pad[0x520];
	int m_520; // +0x520
};

struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
	Rva002A8AB1Record*rva002A8AB1(void*);
};

extern Rva002A8F24 *TheSkirmishAIManager;

class Rva0025BFF8
{
public:
	Object *rva0025BFF8(int index);
};

namespace _STL
{
template <class T1, class T2> struct pair
{
	T1 first;
	T2 second;
};
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned int bucket_count() const;
};
}

typedef _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > > IntMap;

class Rva002C589B;
class AITacticOffensive
{
public:
	virtual ~AITacticOffensive();
	AITacticOffensive(const AsciiString &name);
protected:
	char m_pad04[0x10 - 4];
	bool m_running;
	char m_pad11[0x20 - 0x11];
	Rva002C589B *m_record;
	void *m_owner;
	char m_pad28[0x58 - 0x28];
};

class AITacticSiege : public AITacticOffensive
{
public:
	virtual ~AITacticSiege();
	AITacticSiege(const AsciiString &name);
	bool rva005DCAF4();
	class Object *rva005DCAE5();
	bool sideHasIdleSiegeWeapons();
private:
	int m_58;
};

bool AITacticSiege::sideHasIdleSiegeWeapons()
{
	void *store = TheSkirmishAIManager->rva002A8F24((Player *)m_owner);
	Rva0025BFF8 *holder = *(Rva0025BFF8 **)store;
	IntMap *map = (IntMap *)holder;
	for (unsigned int i = 0; i < map->bucket_count(); ++i)
	{
		Object *obj = holder->rva0025BFF8((int)i);
		if (!obj)
			continue;
		if (obj->m_304 != ((Player *)m_owner)->m_2EC)
			continue;
		if (((Inner520 *)obj->m_p4)->m_520 == 7)
			return true;
	}
	return false;
}
