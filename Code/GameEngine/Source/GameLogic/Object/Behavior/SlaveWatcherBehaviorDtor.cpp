// cl: /DNDEBUG /MD /GX
//
// ??1SlaveWatcherBehavior@@UAE@XZ, retail 0x00484739,
// 112 bytes. Behavior-side dtor restoring the three MI vptrs (+0 0xC4A264
// plus +0x0C 0x7EFF90 plus +0x10 0xC4A258) then conditionally releasing the
// watched slave: when the ModuleData at +0x04 is null or its LetSlaveLive
// byte at +0x11 is clear and the slave ID at +0x20 is set, it resolves the
// slave through TheGameLogic (0x9FE78C) findObjectByID (rowed 0x49DC5) and
// kills it with (0, 13) through the rowed 0x2984D4 kill, then calls the
// UpdateModule base dtor (pinned 0x24A797). Layout follows the ctor TU
// 0x4845CB (UpdateModule base size 0x20 plus m_20 plus 0x80 pad, factory
// 0x24C625 news 0xA4). Identity is the own vtable 0xC4A448 plus slot 0
// deleting dtor 0x4848CA calling this body. BFME1 donor
// SlaveWatcherBehaviorDestructors.cpp proves the find-plus-kill shape.

class Thing;

class SlaveWatcherBehaviorModuleData
{
public:
	unsigned char m_pad[0x10];
	bool m_updateSlave; // +0x10
	bool m_letSlaveLive; // +0x11
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum DamageType
{
	DAMAGE_NORMAL = 0
};

enum DeathType
{
	DEATH_SLAVE_WATCHER_RELEASE = 13
};

namespace _STL
{
template <int N> struct _Base_bitset
{
public:
	unsigned int m_bits;
	void _M_do_or(const _Base_bitset<N> &other);
};
}

class SlaveWatcherBits : public _STL::_Base_bitset<32>
{
private:
	unsigned char m_pad[0x7C];
};

class Object
{
public:
	void kill(DamageType type, DeathType death);
	void updateUpgradeModules();
	unsigned char m_pad00[0x284];
	SlaveWatcherBits m_upgradeBits;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class BehaviorModuleBase
{
public:
	virtual void unused();
	const SlaveWatcherBehaviorModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleOther
{
public:
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const void *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_UNREADY = 1
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *object, UpdateSleepTime sleepTime);
	unsigned int m_nextCallFrameAndPhase; // +0x14
	int m_indexInLogic; // +0x18
	int m_reserved1C; // +0x1C
};

class SlaveWatcherBehavior : public UpdateModule
{
public:
	SlaveWatcherBehavior(Thing *thing, const void *moduleData);
	virtual ~SlaveWatcherBehavior();
	void rva00484869(int id);

private:
	int m_slaveID; // +0x20
	SlaveWatcherBits m_upgradeBits; // +0x24
};

// ??1SlaveWatcherBehavior@@UAE@XZ @0x00484739
SlaveWatcherBehavior::~SlaveWatcherBehavior()
{
	if (!m_moduleData || !m_moduleData->m_letSlaveLive)
	{
		if (m_slaveID != 0)
		{
			Object *slave = TheGameLogic->findObjectByID((ObjectID)m_slaveID);
			if (slave)
				slave->kill(DAMAGE_NORMAL, DEATH_SLAVE_WATCHER_RELEASE);
		}
	}
}

// ?rva00484869@SlaveWatcherBehavior@@QAEXH@Z @0x00484869: adjacent destructor rows and shared +0x20 slave ID identify the class; method name remains address-derived.
void SlaveWatcherBehavior::rva00484869(int id)
{
	m_slaveID = id;
	if (m_moduleData->m_updateSlave)
	{
		Object *slave = TheGameLogic->findObjectByID((ObjectID)id);
		if (slave)
		{
			m_upgradeBits = m_object->m_upgradeBits;
			slave->m_upgradeBits._M_do_or(m_upgradeBits);
			slave->updateUpgradeModules();
		}
	}
	setWakeFrame(m_object, UPDATE_SLEEP_UNREADY);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
