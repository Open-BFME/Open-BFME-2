// cl: /O1 /DNDEBUG /MD /Oi /arch:SSE
//
// ??0ProjectileStreamUpdate@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x0033EE25, 86 bytes. Behavior-side ctor completing the
// ProjectileStreamUpdate file-unit (cullFrontOfList 56B at 0x33F033 and
// considerDying 37B at 0x33F06B placed from the ZH donor TU; behavior
// factory rowed at 0x24FC59 with this pinned 2-arg ctor).
//
// Shape: frameless single-base ctor over the rowed UpdateModule base
// 0x253390 (base-class layout mirrors UpdateModuleCtor.cpp exactly: MI
// chain plus wake/index/reserved members, so the derived stores land at
// +0x20/+0x70; the three vtable installs at +0/+0xC/+0x10 are implicit,
// in base-init order, resolving to this TU's COMDAT vtables which are
// DIR32-masked in comparison). The ZH donor ctor is followed for the body
// with one BFME2 repair: the INVALID_ID loop over the 20-strong ID array
// is a memset (W3DDebrisDraw precedent: extern-C memset plus /Oi inlines
// to push-imm/pop-ecx plus rep stosd, no call, zero new pins), then the
// donor assignment order (owning/nextFree/firstValid/target plus inline
// targetPosition.zero(), whose address-take emits the lea-plus-movss
// triple per the MissileUpdate precedent). Factory news fits the +0x8C
// tail. Zero new pins (base resolves via its row).

class Thing;
class ModuleData;

class BehaviorModuleBase
{
	virtual void unused();
	int a;
	int b;
};

class BehaviorModuleOther
{
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
	virtual void update();
};

typedef int ObjectID;
typedef int Int;

enum
{
	INVALID_ID = 0,
	MAX_PROJECTILE_STREAM = 20
};

struct Coord3D
{
	void zero() { m_x = 0.0f; m_y = 0.0f; m_z = 0.0f; }
	float m_x;
	float m_y;
	float m_z;
};

extern "C" void *memset(void *, int, unsigned int);

class ProjectileStreamUpdate : public UpdateModule
{
public:
	ProjectileStreamUpdate(Thing *thing, const ModuleData *moduleData);

private:
	ObjectID m_projectileIDs[MAX_PROJECTILE_STREAM]; // +0x20
	Int m_nextFreeIndex; // +0x70
	Int m_firstValidIndex; // +0x74
	ObjectID m_owningObject; // +0x78
	ObjectID m_targetObject; // +0x7C
	Coord3D m_targetPosition; // +0x80
};

// ??0ProjectileStreamUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0033EE25
ProjectileStreamUpdate::ProjectileStreamUpdate(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	memset(m_projectileIDs, 0, sizeof(m_projectileIDs));
	m_owningObject = INVALID_ID;
	m_nextFreeIndex = 0;
	m_firstValidIndex = 0;
	m_targetObject = INVALID_ID;
	m_targetPosition.zero();
}
