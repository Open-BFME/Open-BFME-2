// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// SpecialEnemySenseUpdate::update (0x0049A037, slot 0 of its
// UpdateModuleInterface vftable 0x00850498; the ctor 0x00499FA9 stores it and
// the vftable's name getter 0x00499F5E answers "SpecialEnemySenseUpdate").
// Looks for the closest alive enemy (relationship 1) the module data's +0x08
// object filter (0x002614EC) accepts within its +0x0C radius (BFME2's
// partition filter chain, the view AIStructureCreepTactic.cpp documents),
// then sets (found) or clears (none) model condition 258 on every object of
// the contain's slot-31 member list (slot 66), else on the object itself.
// Sleeps the data's +0x10.
class Object;
class Player;

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// vftable 0x00BFAD10, allow 0x0026119D: not effectively dead.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};

// vftable 0x00BCECF0, allow 0x002614EC: +0x08 what to compare, +0x0C a
// player, +0x10 whether a hit allows.
class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};

// vftable 0x00BFBC90, allow 0x00260EB1, getPlayerMask 0x00260E6A: the object,
// relationship flags and whether a hit allows.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *pos, float maxDist, int dc,
		Rva000421C8 *filters);	// 0x00625360
};
extern PartitionManager *ThePartitionManager;

class Rva0010CBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[20];
};

template <int N> class Rva0049A037Slots : public Rva0049A037Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0049A037Slots<0>
{
};

// A contained-objects list: STLport list<Object *> nodes (+0 next, +8 the
// object) behind its header node.
struct Rva0049A037Node
{
	Rva0049A037Node *m_next;
	Rva0049A037Node *m_prev;
	Object *m_object;
};
struct Rva0049A037List
{
	Rva0049A037Node *m_head;
};
// What slot 66 returns by value (through a hidden pointer, so not a POD).
struct Rva0049A037Items
{
	Rva0049A037Items(const Rva0049A037Items &other);
	int m_00;
	const Rva0049A037List *m_list;
};

class Rva0049A037Members : public Rva0049A037Slots<66>
{
public:
	virtual Rva0049A037Items rva0049A037Slot66() = 0;
};

class Rva0049A037Contain : public Rva0049A037Slots<31>
{
public:
	virtual Rva0049A037Members *rva0049A037Slot31() = 0;
};

class Object
{
public:
	Player *getControllingPlayer() const;	// 0x0028AFA9
	void rva0028AE6D();			// 0x0028AE6D
	const Coord3D *getPosition() const { return &m_pos; }
	unsigned char m_pad000[0x38];
	Coord3D m_pos;			// +0x38
	unsigned char m_pad044[0x10C - 0x44];
	Rva0010CBits m_conditionBits;	// +0x10C
	unsigned char m_pad15C[0x250 - 0x15C];
	Rva0049A037Contain *m_contain;	// +0x250
	Rva0049A037Contain *getContain() const { return m_contain; }
};

static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}

static __forceinline void clearModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) != 0)
	{
		object->m_conditionBits.clear(bit);
		object->rva0028AE6D();
	}
}

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	Object *getObject() const { return m_object; }
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
};

struct SpecialEnemySenseUpdateModuleData
{
	unsigned char m_pad00[0x08];
	int m_08;			// +0x08 what the 0x002614EC filter compares
	float m_0C;			// +0x0C the radius
	UpdateSleepTime m_10;		// +0x10 the delay
};

class SpecialEnemySenseUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
private:
	const SpecialEnemySenseUpdateModuleData *getSpecialEnemySenseUpdateModuleData() const
	{
		return (const SpecialEnemySenseUpdateModuleData *)m_moduleData;
	}
};

UpdateSleepTime SpecialEnemySenseUpdate::update()
{
	Object *obj = getObject();
	const SpecialEnemySenseUpdateModuleData *data = getSpecialEnemySenseUpdateModuleData();
	Object *enemy = ThePartitionManager->getClosestObject(obj->getPosition(), data->m_0C, 0,
		Rva0026119DFilter().link(&Rva002614ECFilter(&data->m_08, obj->getControllingPlayer(), true))
			->link(&Rva00260EB1Filter(obj, 1, false)));
	if (enemy) {
		Rva0049A037Members *members = obj->getContain() ? obj->getContain()->rva0049A037Slot31() : 0;
		if (members) {
			Rva0049A037Items items = members->rva0049A037Slot66();
			for (Rva0049A037Node *n = items.m_list->m_head->m_next; n != items.m_list->m_head; n = n->m_next)
				setModelConditionBit(n->m_object, 258);
		} else {
			setModelConditionBit(obj, 258);
		}
	} else {
		Rva0049A037Members *members = obj->getContain() ? obj->getContain()->rva0049A037Slot31() : 0;
		if (members) {
			Rva0049A037Items items = members->rva0049A037Slot66();
			for (Rva0049A037Node *n = items.m_list->m_head->m_next; n != items.m_list->m_head; n = n->m_next)
				clearModelConditionBit(n->m_object, 258);
		} else {
			clearModelConditionBit(obj, 258);
		}
	}
	return data->m_10;
}
