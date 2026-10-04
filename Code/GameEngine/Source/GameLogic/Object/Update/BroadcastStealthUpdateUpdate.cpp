// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// BroadcastStealthUpdate::update (0x004A35C9, slot 0 of its
// UpdateModuleInterface vftable 0x00852358). After 0x004A33EE (the member
// its dtor also calls), collect the IDs of every alive object other than
// this one, relationship flag 4 to it, passing 0x002614DF and having the
// module data's +0x08 kinds within its +0x24 radius (BFME2's partition
// filter chain, the view AIStructureCreepTactic.cpp documents) into the
// +0x28 ID list; then for every listed object still alive, its stealth
// helper (Object::rva0028F4BC, switched through 0x00373D28 when its flags
// have bit 10) keeps only the data's +0x140 flags (0x002B2210). Sleeps the
// data's +0x28.
class Object;

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

// vftable 0x00BF91BC, allow 0x002611BF.
class Rva002611BFFilter : public Rva000421C8
{
public:
	Rva002611BFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
};

// vftable 0x00C07190, allow 0x002614DF: +0x08 an object.
class Rva002614DFFilter : public Rva000421C8
{
public:
	Rva002614DFFilter(const Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	const Object *m_obj;
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

// A KindOfMaskType as the mask filters copy it (0x0004543D).
class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) throw();
private:
	unsigned char m_bytes[28];
};

// vftable 0x00BC2908, allow 0x002610DE: accept what has every kind of the
// first mask and none of the second.
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};
extern unsigned char g_00DFEFA4StoragePrototype[28];

#pragma comment(linker, "/alternatename:?getPlayerMask@Rva000421C8@@UAEHXZ=?Get_File_Handle@FileClass@@UAEPAXXZ")

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BfmeWideResult
{
	Object *next() throw();	// 0x00045623
	~BfmeWideResult();	// 0x0004AA28
	void *m_value;
};

class PartitionManager
{
public:
	BfmeWideResult iterateObjectsInRange(const Coord3D *pos, float radius, int distCalc,
		Rva000421C8 *filters, int order);	// 0x00625610
};
extern PartitionManager *ThePartitionManager;

enum ObjectID
{
	INVALID_ID = 0
};

// The stealth helper Object::rva0028F4BC returns: +0x04 its data, whose
// +0x0C holds the flags.
struct Rva00373EC6Data
{
	char m_pad00[0x0C];
	unsigned m_0C;		// +0x0C
};

class Rva00373EC6
{
public:
	Rva00373EC6 *rva00373D28(Object *obj);	// 0x00373D28
	void rva002B2210(unsigned flags);	// 0x002B2210
	void *m_vtable;
	const Rva00373EC6Data *m_04;	// +0x04
};

class Object
{
public:
	Rva00373EC6 *rva0028F4BC();	// 0x0028F4BC
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_74; }
	char m_pad000[0x38];
	Coord3D m_pos;		// +0x38
	char m_pad044[0x74 - 0x44];
	ObjectID m_74;		// +0x74
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);	// 0x00049DC5
};
extern GameLogic *TheGameLogic;

// A list<ObjectID>: STLport nodes (+0 next, +8 the ID) behind the header node.
struct Rva004A35C9Node
{
	Rva004A35C9Node *m_next;
	Rva004A35C9Node *m_prev;
	ObjectID m_id;
};
class BridgeBehaviorObjectIDList
{
public:
	void push_back(const ObjectID &id);	// 0x002A1B6F
	Rva004A35C9Node *m_head;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
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
protected:
	char m_pad14[0x28 - 0x14];
};

struct BroadcastStealthUpdateModuleData
{
	unsigned char m_pad00[0x08];
	BfmeFixedStorage0004543D m_08;	// +0x08 the kinds
	float m_24;			// +0x24 the radius
	UpdateSleepTime m_28;		// +0x28 the delay
	unsigned char m_pad2C[0x140 - 0x2C];
	unsigned m_140;			// +0x140 the flags to keep
};

class BroadcastStealthUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void rva004A33EE();	// 0x004A33EE
private:
	const BroadcastStealthUpdateModuleData *getBroadcastStealthUpdateModuleData() const
	{
		return (const BroadcastStealthUpdateModuleData *)m_moduleData;
	}
	BridgeBehaviorObjectIDList m_28;	// +0x28
};

UpdateSleepTime BroadcastStealthUpdate::update()
{
	rva004A33EE();
	const BroadcastStealthUpdateModuleData *data = getBroadcastStealthUpdateModuleData();
	Object *obj = m_object;
	BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(obj->getPosition(), data->m_24, 0,
		Rva002614DFFilter(obj).link(&Rva0026119DFilter())->link(&Rva00260EB1Filter(obj, 4, false))
			->link(&Rva002611BFFilter(obj))
			->link(&Rva0004584D(data->m_08, *(BfmeFixedStorage0004543D *)g_00DFEFA4StoragePrototype)), 0);
	Object *other;
	while ((other = hits.next()) != 0)
		m_28.push_back(other->getID());
	for (Rva004A35C9Node *n = m_28.m_head->m_next; n != m_28.m_head; n = n->m_next) {
		Object *member = TheGameLogic->findObjectByID(n->m_id);
		if (!member)
			continue;
		Rva00373EC6 *stealth = member->rva0028F4BC();
		if (!stealth)
			continue;
		unsigned flags = stealth->m_04->m_0C;
		if (flags & 0x400) {
			stealth = stealth->rva00373D28(member);
			flags = stealth->m_04->m_0C;
		}
		flags -= flags & ~getBroadcastStealthUpdateModuleData()->m_140;
		stealth->rva002B2210(flags);
	}
	return getBroadcastStealthUpdateModuleData()->m_28;
}
