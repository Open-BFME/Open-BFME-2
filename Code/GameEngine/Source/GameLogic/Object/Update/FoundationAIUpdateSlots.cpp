// cl: /O1 /DNDEBUG /MD
//
// Two FoundationAIUpdate overrides on vtables only its matched ctor 0x004551B3
// and dtor ??1Rva00455050 install: the primary 0x00C40608 and the
// BehaviorModuleInterface vtable 0x00C40548 at +0x0C. The ctor also puts the
// interface 0x00C1A690 at +0x20 (slot 3 there is the bool getter 0x00354EB0)
// and the ObjectID at +0x28 the matched xfer saves. Names are by address.
//
// ?rva00455B67@FoundationAIUpdate@@UAEXPAVPlayer@@0@Z, retail 0x00455B67,
// 118 bytes: primary slot 9, two owner arguments (the ZH onCapture shape):
// when the +0x20 interface's slot 3 holds and the +0x28 object exists, tells
// the skirmish AI records of the old and the new owner (the pinned
// TheSkirmishAIManager lookup 0x002A8AB1 on [0x00DFEEF8]) through the pinned
// record members 0x002C6A4E and 0x002C6A3D, then moves the object to the new
// owner's +0x2EC team through the pinned 0x00298AE4.
// ?rva00455B42@FoundationAIUpdate@@UAEXH@Z, retail 0x00455B42, 37 bytes:
// +0x0C slot 46 (compiled with that subobject this); unless the +0x28 ID is
// the owner's own, passes the argument to the pinned 0x0028BAAE (stores
// Object +0x45C) of the object it names.

class ModuleData;
class Team;

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	void rva0028BAAE(int value);
	void rva00298AE4(Team *team);
private:
	unsigned char m_pad000[0x74];
	ObjectID m_id; // +0x74
};

class Player
{
public:
	Team *getDefaultTeam() const { return m_defaultTeam; }
private:
	unsigned char m_pad000[0x2EC];
	Team *m_defaultTeam; // +0x2EC
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};
extern GameLogic *TheGameLogic;

struct Rva002A8AB1Record
{
	void rva002C6A4E(Object *obj);
	void rva002C6A3D(Object *obj);
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;

template <int N> class Rva00455B42Slots : public Rva00455B42Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00455B42Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
	virtual void gap1();
	virtual void gap2();
	virtual void gap3();
	virtual void gap4();
	virtual void gap5();
	virtual void gap6();
	virtual void gap7();
	virtual void gap8();
	virtual void rva00455B67(Player *oldOwner, Player *newOwner) = 0;
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface : public Rva00455B42Slots<46>
{
public:
	virtual void rva00455B42(int value) = 0;
};

struct UpdateModuleInterface { virtual void f10(); };

class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};

class Rva00C1A690Iface
{
public:
	virtual void gap0() = 0;
	virtual void gap1() = 0;
	virtual void gap2() = 0;
	virtual bool slot3() const = 0;
};

class FoundationAIUpdate : public UpdateModule, public Rva00C1A690Iface
{
public:
	virtual void rva00455B67(Player *oldOwner, Player *newOwner);
	virtual void rva00455B42(int value);
private:
	int m_24;
	ObjectID m_28; // +0x28
	bool m_2C;
};

// ?rva00455B67@FoundationAIUpdate@@UAEXPAVPlayer@@0@Z @0x00455B67
void FoundationAIUpdate::rva00455B67(Player *oldOwner, Player *newOwner)
{
	if (!slot3())
		return;
	Object *obj = TheGameLogic->findObjectByID(m_28);
	if (!obj)
		return;
	Rva002A8AB1Record *oldRecord = g_00DFEEF8->rva002A8AB1(oldOwner);
	Rva002A8AB1Record *newRecord = g_00DFEEF8->rva002A8AB1(newOwner);
	if (oldRecord)
		oldRecord->rva002C6A4E(obj);
	if (newRecord)
		newRecord->rva002C6A3D(obj);
	obj->rva00298AE4(newOwner->getDefaultTeam());
}

// ?rva00455B42@FoundationAIUpdate@@UAEXH@Z @0x00455B42
void FoundationAIUpdate::rva00455B42(int value)
{
	if (m_28 != m_object->getID())
	{
		Object *obj = TheGameLogic->findObjectByID(m_28);
		if (obj)
			obj->rva0028BAAE(value);
	}
}
