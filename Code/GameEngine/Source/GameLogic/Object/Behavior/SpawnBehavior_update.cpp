// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?update@SpawnBehavior@@UAE?AW4UpdateSleepTime@@XZ, retail 0x004602F4, 481 bytes.
// Identity: slot 0 of SpawnBehavior's UpdateModuleInterface vftable 0x008425E0
// (then UpdateModule's rowed 0x00253376 and 0x0044DF8D), so `this` is the
// update interface at SpawnBehavior +0x10. Donor: BFME 1's
// SpawnBehavior::update (reference/open-bfme-1/game/GameEngine/Source/
// GameLogic/Object/Behavior/SpawnBehaviorUpdate.cpp) over Zero Hour's.
// BFME 2 deltas measured from retail:
// - the upgrade masks are 128 bytes, read inline from module data +0x5C and
//   +0xDC; the gate asks UpgradeMux (+0x30) slot 0, isAlreadyUpgraded;
// - with m_shareUpgrades (+0x171) every live spawn is given the owner's
//   completed upgrades (Object +0x284) through the rowed NotEqual 0x0045F4C2,
//   _Base_bitset<32>::_M_do_or and Object::updateUpgradeModules;
// - the update rate reloads from the frame-rate global 0x00E035C8
//   (Zero Hour's SPAWN_UPDATE_RATE, LOGICFRAMES_PER_SECOND/2);
// - a due replacement time first tries an orphan reclaim (rowed 0x0045F9D8)
//   before createSpawn;
// - stopSpawning is the virtual SpawnBehaviorInterface slot 9 (0x0045F37D,
//   m_active = false), also called for m_killSpawnsBasedOnModelConditionState
//   (+0x170).
//
// GameLogic::findObjectByID is declared as the header inline over the object
// hash map at +0xB4; MSVC calls the out-of-line copy 0x00049DC5.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1
};

namespace _STL
{
template <int N> struct _Base_bitset
{
	void _M_do_or(const _Base_bitset<N> &other);
	unsigned long _M_w[N];
};
}

// The shared 0x80-byte clear 0x001EAE6F, the out-of-line constructor of
// every 128-byte BitFlags (rowed under this address-derived name).
class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();

	unsigned long m_words[32];
};

class UpgradeMaskType : public Rva001EAE6FHelper
{
public:
	UpgradeMaskType() { clear80(); }

	Bool any() const
	{
		for (UnsignedInt i = 0; i < 32; ++i)
			if (m_words[i] != 0)
				return true;
		return false;
	}
};

bool __cdecl Rva0045F4C2NotEqual(const void *a, const void *b);

extern int g_00E035C8;

class Object
{
public:
	ObjectID getProducerID() const { return m_producerID; }
	void updateUpgradeModules();

	unsigned char m_pad000[0x78];
	ObjectID m_producerID;
	unsigned char m_pad07C[0x284 - 0x7C];
	_STL::_Base_bitset<32> m_objectUpgradesCompleted;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
	Object *findObjectByID(ObjectID id)
	{
		if (id == INVALID_ID)
			return 0;
		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;
		return (*it).second;
	}

private:
	char m_pad000[0x40];
	UnsignedInt m_frame;
	char m_pad044[0xB4 - 0x44];
	ObjectPtrHash m_objHash;
};
extern GameLogic *TheGameLogic;

class UpgradeMuxData
{
public:
	void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const
	{
		activation = m_activationMask;
		conflicting = m_conflictingMask;
	}

	UpgradeMaskType m_activationMask;
	UpgradeMaskType m_conflictingMask;
};

class SpawnBehaviorModuleData
{
public:
	unsigned char m_pad000[0x08];
	Int m_spawnNumberData;
	Int m_spawnReplaceDelayData;
	Int m_initialBurst;
	Bool m_isOneShotData;
	unsigned char m_pad015[0x5C - 0x15];
	UpgradeMuxData m_upgradeMuxData;
	unsigned char m_pad15C[0x170 - 0x15C];
	Bool m_killSpawnsBasedOnModelConditionState;
	Bool m_shareUpgrades;
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	const SpawnBehaviorModuleData *m_moduleData;
	Object *m_object;
	void *m_behaviorModuleInterface;
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;

private:
	unsigned char m_pad04[0x10 - 0x04];
};

class SpawnBehaviorInterface
{
public:
#define SBI_SLOT(n) virtual void spawnBehaviorInterfaceSlot##n();
	SBI_SLOT(00) SBI_SLOT(01) SBI_SLOT(02) SBI_SLOT(03) SBI_SLOT(04) SBI_SLOT(05)
	SBI_SLOT(06) SBI_SLOT(07) SBI_SLOT(08)
#undef SBI_SLOT
	virtual void stopSpawning();
};

class DieModuleInterface
{
public:
	virtual void onDie();
};

class DamageModuleInterface
{
public:
	virtual void onDamage();
};

class SpawnBehaviorInterface2C
{
public:
	virtual void rva0045FE4A();
};

class UpgradeMux
{
public:
	virtual Bool isAlreadyUpgraded() const;

private:
	Bool m_upgradeExecuted;
};

class SpawnBehavior : public ObjectModule,
	public UpdateModuleInterface,
	public SpawnBehaviorInterface,
	public DieModuleInterface,
	public DamageModuleInterface,
	public SpawnBehaviorInterface2C,
	public UpgradeMux
{
public:
	virtual UpdateSleepTime update();
	void computeAggregateStates();
	Bool shouldTryToSpawn();
	Bool rva0045F9D8();

private:
	Bool createSpawn();
	Object *getObject() const { return m_object; }
	const SpawnBehaviorModuleData *getSpawnBehaviorModuleData() const { return m_moduleData; }

	void *m_spawnTemplate;
	Int m_oneShotCountdown;
	Int m_framesToWait;
	Int m_firstBatchCount;
	_STL::list<Int> m_replacementTimes;
	_STL::list<ObjectID> m_spawnIDs;
	Bool m_active;
	Bool m_aggregateHealth;
	Bool m_initialBurstTimesInited;
	Int m_spawnCount;
	UnsignedInt m_selfTaskingSpawnCount;
	Int m_initialBurstCountdown;
};

// ?update@SpawnBehavior@@UAE?AW4UpdateSleepTime@@XZ
UpdateSleepTime SpawnBehavior::update()
{
	if (m_aggregateHealth)
		computeAggregateStates();

	const SpawnBehaviorModuleData *md = getSpawnBehaviorModuleData();
	UpgradeMaskType activation;
	UpgradeMaskType conflicting;
	md->m_upgradeMuxData.getUpgradeActivationMasks(activation, conflicting);
	if (activation.any() && !isAlreadyUpgraded())
		return UPDATE_SLEEP_NONE;

	if (md->m_shareUpgrades)
	{
		for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it)
		{
			Object *spawn = TheGameLogic->findObjectByID(*it);
			if (spawn && getObject())
			{
				const _STL::_Base_bitset<32> *upgrades = &getObject()->m_objectUpgradesCompleted;
				if (Rva0045F4C2NotEqual(upgrades, &spawn->m_objectUpgradesCompleted))
				{
					spawn->m_objectUpgradesCompleted._M_do_or(*upgrades);
					spawn->updateUpgradeModules();
				}
			}
		}
	}

	if (!m_initialBurstTimesInited)
	{
		m_initialBurstTimesInited = true;
		Bool runtimeProduced = getObject()->getProducerID() != INVALID_ID;
		Int burstInitCount = m_initialBurstCountdown;
		for (Int listIndex = 0; listIndex < md->m_spawnNumberData; ++listIndex)
		{
			if (md->m_initialBurst > 0)
			{
				if (runtimeProduced && burstInitCount > 0)
					--burstInitCount;
				m_replacementTimes.push_back(runtimeProduced);
			}
			else
				m_replacementTimes.push_back(listIndex);
		}
	}

	if (--m_framesToWait > 0)
		return UPDATE_SLEEP_NONE;
	m_framesToWait = g_00E035C8;

	if (shouldTryToSpawn())
	{
		for (_STL::list<Int>::iterator it = m_replacementTimes.begin(); it != m_replacementTimes.end();)
		{
			if (TheGameLogic->getFrame() > (UnsignedInt)*it)
			{
				if (rva0045F9D8())
					it = m_replacementTimes.erase(it);
				else if (createSpawn())
					it = m_replacementTimes.erase(it);
				else
					++it;
			}
			else
				++it;
		}

		if (md->m_isOneShotData && m_oneShotCountdown <= 0)
			stopSpawning();
		if (md->m_killSpawnsBasedOnModelConditionState)
			stopSpawning();
	}
	return UPDATE_SLEEP_NONE;
}
