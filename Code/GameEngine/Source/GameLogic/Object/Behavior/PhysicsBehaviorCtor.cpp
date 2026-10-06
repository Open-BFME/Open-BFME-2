// cl: /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// PhysicsBehavior constructor @0x3907A6 (182B). Identity: the sole raw caller
// is the rowed PhysicsBehavior instance factory 0x24E73C. Retail: UpdateModule
// base (rowed 0x253390), the three vtables, an empty BfmeE16 vector at +0x20
// (rowed _Vector_base 0x211E58; the state-1 unwind funclet destroys this+0x20),
// then body zeroing in retail store order, the module-data byte at +0x58
// copied to +0x5D, and setWakeFrame(m_object, UPDATE_SLEEP_FOREVER) through
// the rowed 0x44DF71.
//
// The two float triples at +0x2C and +0x38 are Coord3D::zero() calls, as in
// the Zero Hour ctor's m_accel.zero()/m_vel.zero(): stores made through the
// inlined member pointer keep the m_moduleData/m_object loads below them, which
// is what the earlier attempts' _ReadWriteBarrier tried to force and what put
// the EH state-1 store back just before the call. Layout honest-address only.

#include <vector>

struct BfmeE16
{
	unsigned char m_pad[16];
};

struct Coord3D
{
	float x;
	float y;
	float z;
	void zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
};

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class Thing;
class ModuleData;
class Object;

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class PhysicsBehaviorModuleData
{
public:
	unsigned char m_pad[0x58];
	unsigned char m_bfme58;
};

class PhysicsBehavior : public UpdateModule
{
public:
	PhysicsBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~PhysicsBehavior();
private:
	_STL::vector<BfmeE16> m_elements;
	Coord3D m_bfme2C;
	Coord3D m_bfme38;
	float m_bfme44;
	float m_bfme48;
	int m_bfme4C;
	int m_bfme50;
	int m_bfme54;
	int m_bfme58;
	bool m_bfme5C;
	unsigned char m_bfme5D;
	bool m_bfme5E;
	bool m_bfme5F;
	int m_bfme60;
	int m_bfme64;
};

// ??0PhysicsBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x003907A6
PhysicsBehavior::PhysicsBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData)
{
	m_bfme44 = 0.0f;
	m_bfme48 = 0.0f;
	m_bfme4C = 0;
	m_bfme50 = 0;
	m_bfme54 = 0;
	m_bfme58 = 0;
	m_bfme5C = false;
	m_bfme5E = false;
	m_bfme5F = false;
	m_bfme60 = 0;
	m_bfme64 = 0;
	m_bfme2C.zero();
	m_bfme38.zero();
	m_bfme5D = reinterpret_cast<const PhysicsBehaviorModuleData *>(m_moduleData)->m_bfme58;
	setWakeFrame(m_object, UPDATE_SLEEP_FOREVER);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?behaviorModuleOtherAnchor@BehaviorModuleOther@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
