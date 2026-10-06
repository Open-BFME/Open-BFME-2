// cl: /MD
// ?rva005DC8A2@Rva005DC8A2@@QAE_NXZ, retail 0x005DC8A2, 97 bytes.
// Predicate over holder from g_00DFEEF8 map lookup keyed by Player at this+0x24.
// Holder's first dword dereferenced, then index loop over bucket_count with
// rowed rva0025BFF8 getter; match requires Object+0x304 == Player+0x2ec and
// [Object+4]+0x520 == 7. Evidence: callees rowed (0x002A8F24 0x0025BFF8
// 0x002BEDAB bucket_count), callers 0x005A9AD8 0x005A9CBE pass this in ecx.
// Honest address name; owner unproven.

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
	char m_pad0[4];
	void *m_p4; // +0x4
	char m_pad1[0x304 - 8];
	int m_304; // +0x304
};

struct Inner520
{
	char m_pad[0x520];
	int m_520; // +0x520
};

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};

extern Rva002A8F24 *g_00DFEEF8;

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

class Rva005DC8A2
{
public:
	bool rva005DC8A2();
private:
	char m_pad[0x24];
	Player *m_player; // +0x24
};

bool Rva005DC8A2::rva005DC8A2()
{
	void *store = g_00DFEEF8->rva002A8F24(m_player);
	Rva0025BFF8 *holder = *(Rva0025BFF8 **)store;
	IntMap *map = (IntMap *)holder;
	for (unsigned int i = 0; i < map->bucket_count(); ++i)
	{
		Object *obj = holder->rva0025BFF8((int)i);
		if (!obj)
			continue;
		if (obj->m_304 != m_player->m_2EC)
			continue;
		if (((Inner520 *)obj->m_p4)->m_520 == 7)
			return true;
	}
	return false;
}
