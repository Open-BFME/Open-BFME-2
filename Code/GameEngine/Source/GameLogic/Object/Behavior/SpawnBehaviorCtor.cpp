// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0SpawnBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0045F581, 263 bytes.
// SpawnBehavior ctor. UpdateModule base size 0x20 plus four empty interfaces
// at +0x20..+0x2C plus UpgradeMux at +0x30 size 8 plus ptr+3 ints at
// +0x38..+0x44 plus two lists at +0x48/+0x4C plus tail to 0x64 (factory
// 0x0024B405 news 0x64). Donor BFME1 SpawnBehavior.cpp:69 plus readable
// CtorThunk body. Identity is the own vtable 0xC426AC plus poolkey 0x0045F688
// with the SpawnBehavior literal plus caller friend_newModuleInstance.

#include <list>

class Thing;
class ModuleData;
class Object;
class ThingTemplate;
class AsciiString;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

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
	virtual void spawnBehaviorAnchor();
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
	virtual void spawnExtraAnchor();
};

class UpgradeMux
{
public:
	UpgradeMux();
	virtual void upgradeMuxAnchor();

private:
	bool m_upgradeExecuted;
};

struct SpawnBehaviorModuleDataView
{
	unsigned char pad00[8];
	int m_spawnNumberData;
	unsigned char pad0C[4];
	int m_initialBurst;
	bool m_isOneShotData;
	unsigned char pad15;
	bool m_aggregateHealth;
	unsigned char pad17[9];
	AsciiString *m_spawnTemplateBegin;
};

class SpawnBehavior : public UpdateModule,
	public SpawnBehaviorInterface,
	public DieModuleInterface,
	public DamageModuleInterface,
	public SpawnExtraBase,
	public UpgradeMux
{
public:
	SpawnBehavior(Thing *thing, const ModuleData *moduleData);

private:
	const ThingTemplate *m_spawnTemplate;
	int m_oneShotCountdown;
	int m_framesToWait;
	int m_firstBatchCount;
	_STL::list<int> m_replacementTimes;
	_STL::list<int> m_spawnIDs;
	bool m_active;
	bool m_aggregateHealthFlag;
	bool m_initialBurstTimesInited;
	unsigned char m_pad53;
	int m_spawnCount;
	int m_selfTaskingSpawnCount;
	int m_initialBurstCountdown;
	AsciiString *m_templateNameIterator;
};

SpawnBehavior::SpawnBehavior(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const SpawnBehaviorModuleDataView *md = (const SpawnBehaviorModuleDataView *)m_moduleData;
	m_templateNameIterator = md->m_spawnTemplateBegin;
	m_spawnTemplate = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(m_templateNameIterator);
	m_framesToWait = 0;
	m_firstBatchCount = 0;
	if (md->m_isOneShotData)
		m_oneShotCountdown = md->m_spawnNumberData;
	else
		m_oneShotCountdown = -1;
	m_active = true;
	m_replacementTimes.clear();
	m_initialBurstCountdown = md->m_initialBurst;
	m_initialBurstTimesInited = false;
	m_aggregateHealthFlag = md->m_aggregateHealth;
	m_spawnCount = -1;
	m_active = true;
	m_selfTaskingSpawnCount = 0;
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
