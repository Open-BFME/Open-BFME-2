// ?shouldTryToSpawn@SpawnBehavior@@QAE_NXZ
// partial score=0.93 date=2026-09-28
// ?shouldTryToSpawn@SpawnBehavior@@QAE_NXZ
// partial score=0.93 date=2026-09-28
// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
//
// ?shouldTryToSpawn@SpawnBehavior@@QAE_NXZ, retail 0x0045F3F8, 103 bytes.
// Slot-free __thiscall (direct E8 caller at 0x00460448 in update 0x004602F4).
// BFME1/ZH donor SpawnBehavior::shouldTryToSpawn plus BFME2 deltas: the
// neutral check is inlined as (Object+0x124>>26&1) and the tail returns
// ~dead&1 from Object+0x438 bit0 (isEffectivelyDead) instead of TRUE.
// Layout follows ctor 0x0045F581 (UpdateModule base 0x20 plus four empty
// interfaces +0x20..+0x2C plus UpgradeMux +0x30 size 8, m_active +0x50,
// ModuleData +0x04 with isOneShot +0x14, Object +0x08). stopSpawning is
// virtual slot 9 (offset 0x24) on the +0x20 secondary. testStatus 2/0x13/0x15
// are UNDER_CONSTRUCTION/SOLD/RECONSTRUCTING via rowed 0x0004E536.

class Thing;
class ModuleData;
class Object;

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNDER_CONSTRUCTION = 2,
	OBJECT_STATUS_SOLD = 0x13,
	OBJECT_STATUS_RECONSTRUCTING = 0x15
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;

	unsigned char m_pad00[0x124];
	unsigned int m_124;
	unsigned char m_pad128[0x438 - 0x128];
	unsigned char m_dead;
};

struct SpawnBehaviorModuleDataView
{
	unsigned char pad00[0x14];
	bool m_isOneShotData;
};

class BehaviorModuleBase
{
public:
	virtual void unused();
	const SpawnBehaviorModuleDataView *m_moduleData;
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
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void stopSpawning();
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
	bool shouldTryToSpawn();

private:
	unsigned char m_pad38[0x18];
	bool m_active;
};

bool SpawnBehavior::shouldTryToSpawn()
{
	if (!m_active)
		return false;
	const SpawnBehaviorModuleDataView *modData = m_moduleData;
	Object *obj = m_object;
	if (modData->m_isOneShotData && obj->testStatus(OBJECT_STATUS_RECONSTRUCTING))
	{
		stopSpawning();
		return false;
	}
	if (obj->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION) || obj->testStatus(OBJECT_STATUS_SOLD))
		return false;
	unsigned char vbit = (unsigned char)(obj->m_124 >> 26);
	if (vbit & 1)
		return false;
	unsigned char inv = ~obj->m_dead;
	unsigned char bit = inv & 1;
	return bit;
}
