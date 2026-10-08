// cl: /DNDEBUG /MD /GX
//
// FireWeaponCollide.cpp: the FireWeaponCollide bodies retail links from this
// TU (tu_map approved), folded from the ctor and dtor split units, which
// shared these exact flags. One class view carries the offsets each body was
// verified against: module data +0x04, object +0x08, collide weapon +0x14,
// ever-fired +0x18; module data template +0x08; object weapon status +0x74;
// weapon deleteInstance slot 0, status +0x08.
// shouldFireWeapon stays split: declaring it virtual here changes the
// vftable this unit emits, which every other unit shares one copy of.
// The xfer unit stays split: it reaches the weapon as a Snapshot base at +0,
// which this weapon view (pool object first) cannot also express.

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
	virtual void *deleteInstance(int flags);

	unsigned char m_pad04[4];
	unsigned int m_status; // +0x08
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
	int m_weaponStatus; // +0x74
};

// Multiple-inheritance layout shared with the split xfer unit, so all units
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

// Slot 0 of both interface vftables is retail's shared `return 0` fold
// (33 C0 C3 at 0x000D43D0); the views define it inline with that body, so
// the compiled tables name a definition of their own.
class BehaviorModuleInterface
{
public:
	virtual void *behaviorSlot() { return 0; }
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class CollideModuleInterface
{
public:
	virtual void *collideSlot() { return 0; }
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
	const WeaponTemplate *m_collideWeaponTemplate; // +0x08
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

	Weapon *m_collideWeapon; // +0x14
	bool m_everFired; // +0x18
};

// ??1FireWeaponCollide@@UAE@XZ, retail 0x004BB6A7, 85 bytes (deleting dtor
// ??_G at 0x004BB806, slot 0 of vtable 0x85A0FC).
// Donor: BFME1 FireWeaponCollide.cpp dtor (delete m_collideWeapon) and Zero
// Hour FireWeaponCollide.cpp dtor. Weapon released via deleteInstance slot0
// with 0 return-fed to rowed operator delete 0x2FD60; ever-fired bool trivial.
// Base dtor folded at 0xBB68E (twin pin CollideModule). Shape follows
// FireWeaponWhenDamagedBehaviorDtor at 0x482551.
FireWeaponCollide::~FireWeaponCollide()
{
	if (m_collideWeapon != 0) {
		::operator delete(m_collideWeapon->deleteInstance(0));
	}
}

// ??0FireWeaponCollide@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x004BB79A.
// FireWeaponCollide behavior ctor over the pinned CollideModule intermediate
// base (0x4BB702, thing plus data): zeroes the collide-weapon slot, re-stores
// the primary vtable slot (the behavior vtable 0x00C5A0FC, whose slot2 is the
// name getter 0x004BB6FC pushing FireWeaponCollide) and the +0x0C/+0x10
// secondary slots, allocates the collide weapon through TheWeaponStore, and
// clears the ever-fired flag.
// Donor: BFME1 FireWeaponCollideCtorThunk.cpp (CollideModule base init,
// m_collideWeapon init, allocateNewWeapon over the module data's
// m_collideWeaponTemplate with PRIMARY_WEAPON, weapon status from the
// object, ever-fired flag). Instance factory 0x00250FAE news 0x1C.
// Scheduling: the init-list zero emits before the single EH state store,
// which emits before the three implicit vtable stores. The allocateNewWeapon
// spelling resolves to its pin at 0x0028AA81; TheWeaponStore is a TU-local
// extern (DIR32 slot patches from retail, no pin).
FireWeaponCollide::FireWeaponCollide(Thing *thing, const ModuleData *moduleData) :
	CollideModule(thing, moduleData),
	m_collideWeapon(0)
{
	m_collideWeapon = TheWeaponStore->allocateNewWeapon(
		getFireWeaponCollideModuleData()->m_collideWeaponTemplate, PRIMARY_WEAPON);
	m_collideWeapon->m_status = m_object->m_weaponStatus;
	m_everFired = false;
}
