// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??1FireWeaponCollide@@UAE@XZ, retail 0x004BB6A7, 85 bytes. Collide-side
// dtor completing the FireWeaponCollide file-unit (ctor rowed at 0xBB79A,
// pool key at 0xBB755, deleting dtor unclaimed at 0xBB806 slot 0 of vtable
// 0x85A0FC).
//
// Donor: BFME1 FireWeaponCollide.cpp dtor (delete m_collideWeapon) and Zero
// Hour FireWeaponCollide.cpp dtor. BFME2 layout from ctor TU: CollideModule
// base 0x14 (vtable 0x85A0FC primary plus +0x0C/+0x10 secondaries), weapon
// at +0x14 via deleteInstance slot0 with 0 return-fed to rowed operator
// delete 0x2FD60, ever-fired bool at +0x18 trivial. Base dtor folded at
// 0xBB68E (twin pin CollideModule). Shape follows FireWeaponWhenDamaged
//BehaviorDtor at 0x482551 (tracked-pointer virtual release slot0 with 0).

class Thing;
class ModuleData;

class Weapon
{
public:
	virtual void *deleteInstance(int flags);
};

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	const ModuleData *m_moduleData;
	void *m_object;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorSlot();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
public:
	virtual ~BehaviorModule() {}
};

class CollideModuleInterface
{
public:
	virtual void collideSlot();
};

class CollideModule : public BehaviorModule, public CollideModuleInterface
{
public:
	virtual ~CollideModule();
};

class FireWeaponCollide : public CollideModule
{
public:
	FireWeaponCollide(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponCollide();

private:
	Weapon *m_collideWeapon;
	bool m_everFired;
};

// ??1FireWeaponCollide@@UAE@XZ
FireWeaponCollide::~FireWeaponCollide()
{
	if (m_collideWeapon != 0) {
		::operator delete(m_collideWeapon->deleteInstance(0));
	}
}
