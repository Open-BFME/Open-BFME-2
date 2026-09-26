// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0FireWeaponCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x004BB79A, 106 bytes. FireWeaponCollide behavior ctor over the pinned
// CollideModule intermediate base (0x4BB702, thing plus data): zeroes the
// collide-weapon slot, re-stores the primary vtable slot (the behavior
// vtable 0x00C5A0FC, whose slot2 is the name getter 0x004BB6FC pushing
// FireWeaponCollide) and the +0x0C/+0x10 secondary slots, allocates the
// collide weapon through TheWeaponStore, and clears the ever-fired flag.
//
// Donor: BFME1 FireWeaponCollideCtorThunk.cpp (CollideModule base init,
// m_collideWeapon init, allocateNewWeapon over the module data's
// m_collideWeaponTemplate with PRIMARY_WEAPON, weapon status from the
// object, ever-fired flag). Retail offsets: module data at this+0x04,
// object at this+0x08, template at module+0x08, weapon status at
// object+0x74 and weapon+0x08, collide weapon at this+0x14, ever-fired at
// this+0x18 (instance factory 0x00250FAE news 0x1C).
//
// Scheduling: the init-list zero emits before the single EH state store,
// which emits before the three implicit vtable stores of the
// multiple-inheritance layout (+0x00/+0x0C/+0x10, named as in the dtor TU so
// DIR32 consistency holds). The allocateNewWeapon spelling
// resolves to its pin at 0x0028AA81; TheWeaponStore is a TU-local extern
// (DIR32 slot patches from retail, no pin). Class identity is the
// FireWeapon retail cluster (pool key rowed at 0x004BB755 pushing the same
// string, vtable slot2 getter, the instance factory at 0x00250FAE is the
// sole raw caller).

class Thing;
class ModuleData;
class WeaponTemplate;

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class Weapon
{
public:
	unsigned char m_pad[8];
	unsigned int m_status;
};

class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *weaponTemplate, WeaponSlotType slot) const;
};

extern WeaponStore *TheWeaponStore;

class Object
{
public:
	unsigned char m_pad[0x74];
	int m_weaponStatus;
};

// Same multiple-inheritance layout as FireWeaponCollideDtor.cpp, so both TUs
// name the three vtables alike (+0x00 ObjectModule, +0x0C
// BehaviorModuleInterface, +0x10 CollideModuleInterface).
class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class CollideModuleInterface
{
public:
	virtual void collideSlot();
};

class CollideModule : public BehaviorModule, public CollideModuleInterface
{
public:
	CollideModule(Thing *thing, const ModuleData *moduleData);
	virtual ~CollideModule();
};

class FireWeaponCollideModuleData
{
public:
	unsigned char m_pad[8];
	const WeaponTemplate *m_collideWeaponTemplate;
};

class FireWeaponCollide : public CollideModule
{
public:
	FireWeaponCollide(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponCollide();

private:
	const FireWeaponCollideModuleData *getFireWeaponCollideModuleData() const
	{
		return reinterpret_cast<const FireWeaponCollideModuleData *>(m_moduleData);
	}

	Weapon *m_collideWeapon;
	bool m_everFired;
};

// ??0FireWeaponCollide@@QAE@PAVThing@@PBVModuleData@@@Z
FireWeaponCollide::FireWeaponCollide(Thing *thing, const ModuleData *moduleData) :
	CollideModule(thing, moduleData),
	m_collideWeapon(0)
{
	m_collideWeapon = TheWeaponStore->allocateNewWeapon(
		getFireWeaponCollideModuleData()->m_collideWeaponTemplate, PRIMARY_WEAPON);
	m_collideWeapon->m_status = m_object->m_weaponStatus;
	m_everFired = false;
}
