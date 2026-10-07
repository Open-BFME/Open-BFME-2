// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?onDie@SpawnBehavior@@UAEXPBVDamageInfo@@@Z retail 0x0045F7B5, 199 bytes.
// Identity: SpawnBehavior's DieModuleInterface vftable slot 0x008425A8.
// BFME1 donor (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/
// Behavior/SpawnBehavior.cpp:110) with BFME2 layout repairs, modeled on the
// landed SpawnBehavior_onSpawnDeath shard. Deltas: kill takes (8,0) args,
// isEffectivelyDead inlines to a bit test at Object+0x438, getBehaviorModules
// is a direct member at Object+0x244, setProducer stores the producer ID.
//
// GameLogic::findObjectByID is declared as the header inline over the object
// hash map at +0xB4; MSVC calls the out-of-line copy 0x00049DC5, and only the
// inline declaration gives retail's register assignment (this in EBX).

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0
};

enum DamageType
{
	DAMAGE_UNRESISTABLE = 8
};

enum DeathType
{
	DEATH_NORMAL = 0
};

class Object;
class DamageInfo;

class DieMuxData
{
public:
	Bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;
};

class SlavedUpdateInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void onSlaverDie(const DamageInfo *damageInfo);
};

class BehaviorModuleFirstBase
{
public:
	virtual void firstBase00();
private:
	char m_firstPad[8];
};

class BehaviorModuleSecondBase
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual SlavedUpdateInterface *getSlavedUpdateInterface();
};

class BehaviorModule : public BehaviorModuleFirstBase, public BehaviorModuleSecondBase
{
};

class Object
{
public:
	void setProducer(Object *producer);
	void kill(DamageType damageType, DeathType deathType);
	Bool isEffectivelyDead() const { return (m_deadFlag & 1) != 0; }

public:
	unsigned char m_pad00[0x74];
	unsigned int m_id;
	unsigned int m_producerId;
	unsigned char m_pad7C[0x244 - 0x7C];
	BehaviorModule **m_behaviorModules;
	unsigned char m_pad248[0x438 - 0x248];
	unsigned char m_deadFlag;
};

class SpawnBehaviorModuleData
{
public:
	unsigned char m_pad00[0x18];
	Bool m_spawnedRequireSpawner;
	unsigned char m_pad19[0x2C - 0x19];
	DieMuxData m_dieMuxData;
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

class SpawnBehavior
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
	const SpawnBehaviorModuleData *getSpawnBehaviorModuleData() const
	{
		return *reinterpret_cast<SpawnBehaviorModuleData *const *>(
			reinterpret_cast<const unsigned char *>(this) - 0x20);
	}
	Object *getObject() const
	{
		return *reinterpret_cast<Object **>(
			reinterpret_cast<unsigned char *>(const_cast<SpawnBehavior *>(this)) - 0x1C);
	}

private:
	char m_pad[0x24];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?onDie@SpawnBehavior@@UAEXPBVDamageInfo@@@Z
void SpawnBehavior::onDie(const DamageInfo *damageInfo)
{
	const SpawnBehaviorModuleData *modData = getSpawnBehaviorModuleData();

	if (modData->m_dieMuxData.isDieApplicable(getObject(), damageInfo) == false)
		return;

	for (_STL::list<ObjectID>::iterator iter = m_spawnIDs.begin(); iter != m_spawnIDs.end(); iter++)
	{
		Object *currentSpawn = TheGameLogic->findObjectByID(*iter);
		if (currentSpawn)
		{
			for (BehaviorModule **update = currentSpawn->m_behaviorModules; *update; ++update)
			{
				SlavedUpdateInterface *sdu = (*update)->getSlavedUpdateInterface();
				if (sdu != NULL)
				{
					sdu->onSlaverDie(damageInfo);
					break;
				}
			}

			currentSpawn->setProducer(NULL);
		}
	}

	if (modData->m_spawnedRequireSpawner)
	{
		Object *obj;

		for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); )
		{
			obj = TheGameLogic->findObjectByID(*it);
			++it;

			if (obj && obj->isEffectivelyDead() == false)
				obj->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
		}
	}
}
