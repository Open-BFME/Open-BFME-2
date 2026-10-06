// cl: /MD
// ?rva005EEB7B@Rva005EEB7B@@QAEXPAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@PAVPlayer@@@Z, retail 0x005EEB7B, 123 bytes.
// Collects ModuleData entries for objects whose current victim is controlled.
// Evidence: caller 0x005D7B65 passes this+0x28 with vector+Player; callees rowed;
// global g_00DFEEF8 map lookup then LeaField+4 range, TheGameLogic findObjectByID,
// +4 flag 0x80 at +0x108, +0x258 getCurrentVictim, getControllingPlayer flag check,
// vector<ModuleData*> push_back. Honest address name; owner unproven.

class Player;
class Object;
class ModuleData;
class AIUpdateInterface;

enum ObjectID
{
	OBJECTID_INVALID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

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

class Rva002AA245MovzxByteChaseField
{
public:
	unsigned int get() const;
	char m_lead[0x34];
	void *m_ptr;
};

struct Flag108
{
	unsigned char m_pad[0x108];
	unsigned char m_flag;
};

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	char m_pad0[4];
	Flag108 *m_p108;
	char m_pad1[0x258 - 8];
	AIUpdateInterface *m_ai;
};

namespace _STL
{

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	void push_back(const _Tp &v);
};

}

struct IdRange
{
	ObjectID *m_begin;
	ObjectID *m_end;
};

class Rva005EEB7B
{
public:
	void rva005EEB7B(_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *vec, Player *player);
};

void Rva005EEB7B::rva005EEB7B(_STL::vector<const ModuleData *, _STL::allocator<const ModuleData *> > *vec, Player *player)
{
	void *store = g_00DFEEF8->rva002A8F24(player);
	Rva005C4AD1LeaField *holder = *(Rva005C4AD1LeaField **)store;
	IdRange *range = (IdRange *)(void *)holder->get();
	ObjectID *it = range->m_begin;
	ObjectID *end = range->m_end;
	for (; it != end; ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (!obj)
			continue;
		if (obj->m_p108->m_flag & 0x80)
			continue;
		Object *victim = obj->m_ai->getCurrentVictim();
		if (!victim)
			continue;
		Player *ctrl = victim->getControllingPlayer();
		if ((unsigned char)((Rva002AA245MovzxByteChaseField *)ctrl)->get() == 0)
			continue;
		vec->push_back(*(const ModuleData **)&obj);
	}
}
