// cl: /DNDEBUG /MD /EHsc- /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva00460175@SpawnBehavior@@QAEXH@Z, retail 0x00460175, 87 bytes.
// Unlock lane: primary-this SpawnBehavior helper called from slot-21
// 0x004604D5 via ecx-0x28 with count = m_spawnCount/3 and /2. Iterates
// m_spawnIDs at primary +0x4C, resolves each ObjectID through TheGameLogic
// (0x009FE78C) findObjectByID (rowed 0x00049DC5), skips null and
// +0x438-bit0 dead objects, issues BfmeSubBGB::bfmeDoBGB(8 0) (pinned
// 0x002984D4), counts successes in ebx and stops when count reached.
// Guards: count > m_spawnCount (+0x54) returns, m_spawnCount == 0 returns.
// Layout from SpawnBehaviorCtor 0x0045F581 (base 0x20 plus four empty
// interfaces plus UpgradeMux 8 plus ptr+3 ints, lists at +0x48/+0x4C,
// tail to 0x64) and onDelete precedent for +0x4C list iteration.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef bool Bool;

enum DamageType
{
	DAMAGE_TYPE_UNKNOWN = 8
};

enum DeathType
{
	DEATH_TYPE_UNKNOWN = 0
};

enum ObjectID
{
	INVALID_ID = 0
};

class Thing;
class ModuleData;
class ThingTemplate;

class Object
{
public:
	void kill(DamageType damageType, DeathType deathType);
	unsigned char m_pad00[0x438];
	unsigned char m_status438;
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
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
};

class SpawnBehaviorInterface
{
public:
	virtual void spawnAnchor();
};

class DieModuleInterface
{
public:
	virtual void dieAnchor();
};

class DamageModuleInterface
{
public:
	virtual void damageAnchor();
};

class SpawnExtraBase
{
public:
	virtual void extraAnchor();
};

class UpgradeMux
{
public:
	virtual void upgradeMuxAnchor();

private:
	bool m_upgradeExecuted;
};

class SpawnBehavior : public UpdateModule,
	public SpawnBehaviorInterface,
	public DieModuleInterface,
	public DamageModuleInterface,
	public SpawnExtraBase,
	public UpgradeMux
{
public:
	void rva00460175(int count);

private:
	const ThingTemplate *m_spawnTemplate;
	int m_oneShotCountdown;
	int m_framesToWait;
	int m_firstBatchCount;
	_STL::list<int> m_replacementTimes;
	_STL::list<ObjectID> m_spawnIDs;
	bool m_active;
	bool m_aggregateHealthFlag;
	bool m_initialBurstTimesInited;
	unsigned char m_pad53;
	int m_spawnCount;
};

void SpawnBehavior::rva00460175(int count)
{
	int done = 0;
	int total = m_spawnCount;
	if (count > total)
		return;
	if (total == 0)
		return;
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); )
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		++it;
		if (obj == 0)
			continue;
		if (obj->m_status438 & 1)
			continue;
		obj->kill(DAMAGE_TYPE_UNKNOWN, DEATH_TYPE_UNKNOWN);
		++done;
		if (done == count)
			break;
	}
}
