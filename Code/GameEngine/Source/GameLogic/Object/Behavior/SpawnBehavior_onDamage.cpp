// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?onDamage@SpawnBehavior@@UAEXPAVDamageInfo@@@Z, retail 0x0045FDF3, 87 bytes.
// Identity: slot 0 of SpawnBehavior's DamageModuleInterface vftable at
// 0x0084259C, ahead of the empty onHealing 0x0047A69C and the rowed
// onBodyDamageStateChange 0x004604D5. Zero Hour's SpawnBehavior::onDamage
// statement for statement: every live spawn's SlavedUpdate is told through
// onSlaverDamage (SlavedUpdateInterface slot 3). The damage interface sits
// at SpawnBehavior +0x28, so the spawn IDs (+0x4C) are at this +0x24.
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

// The DamageModuleInterface view of SpawnBehavior (primary +0x28).
class SpawnBehavior
{
public:
	virtual void onDamage(DamageInfo *info);

private:
	unsigned char m_pad04[0x24 - 0x04];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?onDamage@SpawnBehavior@@UAEXPAVDamageInfo@@@Z
void SpawnBehavior::onDamage(DamageInfo *info)
{
	for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		Object *currentSpawn = TheGameLogic->findObjectByID(*iter);
		if (currentSpawn)
		{
			// Go through all my spawns and see if they have a SlavedUpdate I can tell I was hurt to
			for (BehaviorModule **update = currentSpawn->getBehaviorModules(); *update; ++update)
			{
				SlavedUpdateInterface *sdu = (*update)->getSlavedUpdateInterface();
				if (sdu != NULL)
				{
					sdu->onSlaverDamage(info);
					break;
				}
			}
		}
	}
}
