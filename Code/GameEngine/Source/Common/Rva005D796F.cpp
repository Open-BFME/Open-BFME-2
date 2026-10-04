// cl: /O1 /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva005D796F@Rva005D791C@@UAE_NPAVObject@@@Z @0x005D796F 154B, slot 6
// (offset 0x18) of vtable 0x00875DFC (class of rowed dtor 0x005D791C).
// For each ObjectID in the array behind rowed rva002A8F24 (via global
// g_00DFEEF8) plus rowed LeaField get 0x005C4AD1: resolve it through rowed
// GameLogic::findObjectByID via TheGameLogic; skip nulls, skip IDs already
// keys of the map<int,int> at +0x28 (rowed _M_find 0x00388F63, HordeContain
// precedent), skip when pin-only 0x005EE8DD is false; else insert the key
// into the set<int> overlaid at the same +0x28 (rowed set insert 0x000BC15D,
// horde_rank_set precedent) and return true. False when nothing inserts.
// The map and set calls address the same member per retail; the insert goes
// through a set-typed view of it.
#include <map>
#include <set>

enum ObjectID
{
	OBJECTID_FIRST = 0
};

class Player;
class Object;
struct Coord3D
{
	float x;
	float y;
	float z;
};

class PlayerList;
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_pad00[0x38];
	Coord3D m_coord38;
	unsigned char m_pad44[0x74 - 0x44];
	int m_74;
};

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};
extern Rva002A8F24 *g_00DFEEF8;

class Rva005C4AD1LeaField
{
public:
	void *get() const;
};

class Rva005EE816
{
public:
	bool rva005EE8DD(const Coord3D *a, Object *b);
};

class Rva005D791C
{
public:
	virtual ~Rva005D791C();
	virtual void gap1() = 0;
	virtual void gap2() = 0;
	virtual void gap3() = 0;
	virtual void gap4() = 0;
	virtual void gap5() = 0;
	virtual bool rva005D796F(Object *arg);
private:
	unsigned char m_pad04[0x28 - 0x04];
	_STL::map<int, int> m_map28;
};

bool Rva005D791C::rva005D796F(Object *arg)
{
	Player *player = arg->getControllingPlayer();
	void *arr = g_00DFEEF8->rva002A8F24(player);
	const Rva005C4AD1LeaField *fld = *(const Rva005C4AD1LeaField *const *)((const char *)arr + 0x0C);
	ObjectID **pp = (ObjectID **)fld->get();
	ObjectID *cur = pp[0];
	for (; cur != pp[1]; ++cur)
	{
		Object *o = TheGameLogic->findObjectByID(*cur);
		if (o == 0)
			continue;
		int key = o->m_74;
		if (m_map28.find(key) != m_map28.end())
			continue;
		if (!((Rva005EE816 *)this)->rva005EE8DD((const Coord3D *)((const char *)o + 0x38), arg))
			continue;
		((_STL::set<int> *)&m_map28)->insert(key);
		return true;
	}
	return false;
}
