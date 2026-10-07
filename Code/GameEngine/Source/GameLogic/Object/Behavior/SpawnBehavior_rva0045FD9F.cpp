// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva0045FD9F@SpawnBehavior@@UAEXXZ, retail 0x0045FD9F, 84 bytes.
// Identity: slot 10 of SpawnBehavior's SpawnBehaviorInterface vftable
// (0x008425AC: maySpawnSelfTaskAI, onSpawnDeath, getClosestSlave ... the rowed
// orderSlavesToGoIdle at slot 8). The interface sits at SpawnBehavior +0x20,
// so the spawn IDs (+0x4C) are at this +0x2C and the owning object (+0x08)
// at this -0x18. Every live spawn's SlavedUpdate is re-enslaved to the owner
// through onEnslave (SlavedUpdateInterface slot 1), the walk Zero Hour's
// createSpawn runs for one new spawn. The name is address-derived: Zero
// Hour's slot 10 (orderSlavesToClearDisabled) takes an argument and this
// does not.
//
// GameLogic::findObjectByID is declared as the header inline over the object
// hash map at +0xB4; MSVC calls the out-of-line copy 0x00049DC5, and only the
// inline declaration gives retail's register assignment (this in EBX).

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

enum ObjectID
{
	INVALID_ID = 0
};

class Object;
class DamageInfo;

class SlavedUpdateInterface
{
public:
	virtual ObjectID getSlaverID() const;
	virtual void onEnslave(const Object *slaver);
	virtual void onSlaverDie(const DamageInfo *info);
	virtual void onSlaverDamage(const DamageInfo *info);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

private:
	void *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
#define BMI_SLOT(n) virtual void behaviorModuleInterfaceSlot##n();
	BMI_SLOT(00) BMI_SLOT(01) BMI_SLOT(02) BMI_SLOT(03) BMI_SLOT(04) BMI_SLOT(05)
	BMI_SLOT(06) BMI_SLOT(07) BMI_SLOT(08) BMI_SLOT(09) BMI_SLOT(10) BMI_SLOT(11)
	BMI_SLOT(12) BMI_SLOT(13) BMI_SLOT(14) BMI_SLOT(15) BMI_SLOT(16) BMI_SLOT(17)
	BMI_SLOT(18) BMI_SLOT(19) BMI_SLOT(20) BMI_SLOT(21) BMI_SLOT(22) BMI_SLOT(23)
	BMI_SLOT(24) BMI_SLOT(25)
#undef BMI_SLOT
	virtual SlavedUpdateInterface *getSlavedUpdateInterface();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class Object
{
public:
	BehaviorModule **getBehaviorModules() const { return m_behaviors; }

private:
	unsigned char m_pad000[0x244];
	BehaviorModule **m_behaviors;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
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
	char m_pad000[0xB4];
	ObjectPtrHash m_objHash;
};
extern GameLogic *TheGameLogic;

// The SpawnBehaviorInterface view of SpawnBehavior (primary +0x20).
class SpawnBehavior
{
public:
	virtual void rva0045FD9F();

private:
	Object *getObject() const
	{
		return *reinterpret_cast<Object *const *>(reinterpret_cast<const unsigned char *>(this) - 0x18);
	}

	unsigned char m_pad04[0x2C - 0x04];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?rva0045FD9F@SpawnBehavior@@UAEXXZ
void SpawnBehavior::rva0045FD9F()
{
	for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		Object *currentSpawn = TheGameLogic->findObjectByID(*iter);
		if (currentSpawn)
		{
			for (BehaviorModule **update = currentSpawn->getBehaviorModules(); *update; ++update)
			{
				SlavedUpdateInterface *sdu = (*update)->getSlavedUpdateInterface();
				if (sdu != NULL)
				{
					sdu->onEnslave(getObject());
					break;
				}
			}
		}
	}
}
