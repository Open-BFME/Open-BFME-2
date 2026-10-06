// cl: /O1 /MD /arch:SSE /G7
// ?rva005D7558@Rva005EE816@@QAE_NPAVObject@@@Z @0x005D7558 (102B).
// Identity (target): pin-held honest name; chain caller of rowed 0x002C6ACB;
// single caller 0x005D76CC in rva005D75BE; Rva005D7D93.cpp precedent for the
// g_00DFEEF8 record chain and hash scan for +0x120 bit 0x04.
class Object;
class Player;

struct Rva005D9F97Info
{
	char m_pad000[0x118];
	unsigned char m_118;
	char m_pad119[0x11C - 0x119];
	unsigned char m_11C;
	char m_pad11D[0x120 - 0x11D];
	unsigned char m_120;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad000[0x04];
	Rva005D9F97Info *m_04;
};

class Rva003A2BD4M08
{
public:
	char m_00;
};

struct Rva002A8AB1Record : public Rva003A2BD4M08
{
public:
	void *rva002C6ACB();
};

class Player : public Rva002A8AB1Record
{
};

class PlayerList
{
public:
	Player *rva002A8AB1(Rva003A2BD4M08 *key);
};

class Rva002A8F24 : public PlayerList
{
public:
	void *rva002A8F24(Player *player);
};

extern Rva002A8F24 *g_00DFEEF8;

namespace _STL
{
template <class T> struct hash
{
};
template <class T> struct equal_to
{
};
template <class T> class allocator
{
};
template <class A, class B> struct pair
{
	A first;
	B second;
};
template <class K, class V, class H, class E, class A> class hash_map
{
public:
	unsigned bucket_count() const;
};
}

class Rva0025BFF8 : public _STL::hash_map<int, int, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<_STL::pair<const int, int> > >
{
public:
	Object *rva0025BFF8(int index);
};

struct Rva002A8F24Result
{
	char m_pad00[8];
	Rva0025BFF8 *m_hash;
};

class Rva005EE816
{
public:
	bool rva005D7558(Object *source);
};

bool Rva005EE816::rva005D7558(Object *source)
{
	Player *controlling = source->getControllingPlayer();
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(controlling);
	void *owner = rec->rva002C6ACB();
	if (owner != 0)
	{
		Rva002A8F24Result *store = static_cast<Rva002A8F24Result *>(g_00DFEEF8->rva002A8F24(static_cast<Player *>(owner)));
		Rva0025BFF8 *hash = store->m_hash;
		unsigned count = hash->bucket_count();
		for (unsigned i = 0; i < count; ++i)
		{
			Object *obj = hash->rva0025BFF8(i);
			if (obj->m_04->m_120 & 4)
				return true;
		}
	}
	return false;
}
