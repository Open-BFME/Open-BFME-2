// cl: /DNDEBUG /MD /GX
// ?shouldFireWeapon@FireWeaponCollide@@MAE_NXZ @0x004BB8BA 94B. Virtual slot
// 12 offset 0x30 of vtable 0x0085A0FC class of ??1FireWeaponCollide@@UAE@XZ.
// Status-mask overlap via rowed ?test@Rva00331682Holder 0x00331682 plus copy
// 0x002CF108 plus inverted-required check plus everFired at +0x18 and
// fireOnce at module +0x2C. Donor BFME1 FireWeaponCollide.cpp
// shouldFireWeapon plus ZH FireWeaponCollide.h. Follow retail order
// forbidden then required.
class Thing;
class ModuleData;

class BfmeObject872Header
{
public:
	BfmeObject872Header(const BfmeObject872Header &other);
	int m_vals[4];
};

class Rva00331682Holder
{
public:
	bool test(const void *other) const;
	int m_vals[4];
};

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

namespace _STL
{
template <unsigned _Bits>
class bitset
{
public:
	unsigned long m_words[(_Bits + 31) / 32];
};
}

class FireWeaponCollideModuleData
{
public:
	char m_pad[0x0C];
	Rva00331682Holder m_required;
	Rva00331682Holder m_forbidden;
	bool m_fireOnce;
};

struct ObjectStatusArea
{
	char m_pad[0x94];
	BfmeObject872Header m_status;
};

class FireWeaponCollide : public CollideModule
{
public:
	FireWeaponCollide(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponCollide();
protected:
	virtual bool shouldFireWeapon();
private:
	Weapon *m_collideWeapon;
	bool m_everFired;
};

bool FireWeaponCollide::shouldFireWeapon()
{
	const FireWeaponCollideModuleData *data = (const FireWeaponCollideModuleData *)m_moduleData;
	ObjectStatusArea *obj = (ObjectStatusArea *)m_object;
	BfmeObject872Header tmp(obj->m_status);
	if (data->m_forbidden.test(&tmp))
		return false;
	for (unsigned i = 0; i < 4; ++i)
		tmp.m_vals[i] = ~tmp.m_vals[i];
	if (data->m_required.test(&tmp))
		return false;
	if (m_everFired && data->m_fireOnce)
		return false;
	return true;
}
