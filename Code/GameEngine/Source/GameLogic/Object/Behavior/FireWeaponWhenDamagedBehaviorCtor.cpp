// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0FireWeaponWhenDamagedBehavior@@QAE@PAVThing@@PBVModuleData@@@Z, retail
// 0x00482803, 584 bytes. Behavior-side ctor completing the FireWeaponWhenDamaged
// file-unit (ModuleData proc/ctor/factory rowed at 0x2536E1/0x253682/0x253703;
// behavior factory rowed at 0x24C2F5 news 0x4C with the pinned 2-arg ctor).
//
// Donor: ZH FireWeaponWhenDamagedBehavior.cpp ctor (UpdateModule base, eight
// allocateNewWeapon plus reloadAmmo pairs over the module data templates,
// initially-active giveSelfUpgrade, upgrade-active plus continuous-template
// wake-frame select). BFME2 repairs: UpdateModule is 0x20 (BehaviorModule
// pair plus UpdateModuleInterface plus three ints, per UpdateModuleCtor.cpp);
// UpgradeMux member at +0x20 (vptr plus executed flag, pinned 0x4CE2A3) with
// the inline DamageModuleInterface base at +0x28 (sibling Dead ctor 0x482D80
// shows the same store-before-installs shape); eight Weapon slots at
// +0x2C..+0x48; per-weapon status copy (Weapon+0x08 from Object+0x74, per the
// landed FireWeaponCollide ctor); templates at module+0x124..+0x140;
// UPDATE_SLEEP_NONE=1 and UPDATE_SLEEP_FOREVER=0x3fffffff over setWakeFrame
// pin 0x44DF71 with the rowed UpdateModule base 0x253390.

class Thing;
class ModuleData;
class WeaponTemplate;
class DamageInfo;

#define NULL 0

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class Object
{
public:
	unsigned char m_pad[0x74];
	int m_weaponStatus;
};

class Weapon
{
public:
	void reloadAmmo(const Object *sourceObj);

	unsigned char m_pad[8];
	int m_status;
};

class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *weaponTemplate, WeaponSlotType slot) const;
};

extern WeaponStore *TheWeaponStore;

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
	void setWakeFrame(Object *obj, unsigned int frame);

private:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class UpgradeMux
{
public:
	UpgradeMux();
	virtual bool isUpgradeActive() = 0;
	void giveSelfUpgrade();

private:
	bool m_upgradeExecuted;
};

class DamageModuleInterface
{
public:
	DamageModuleInterface() {}
	virtual void onDamage(DamageInfo *damageInfo);
};

class FireWeaponWhenDamagedBehaviorModuleData
{
public:
	unsigned char m_pad[0x118];
	bool m_initiallyActive;
	unsigned char m_pad119[0x124 - 0x119];
	const WeaponTemplate *m_reactionWeaponPristine;
	const WeaponTemplate *m_reactionWeaponDamaged;
	const WeaponTemplate *m_reactionWeaponReallyDamaged;
	const WeaponTemplate *m_reactionWeaponRubble;
	const WeaponTemplate *m_continuousWeaponPristine;
	const WeaponTemplate *m_continuousWeaponDamaged;
	const WeaponTemplate *m_continuousWeaponReallyDamaged;
	const WeaponTemplate *m_continuousWeaponRubble;
};

class FireWeaponWhenDamagedBehavior : public UpdateModule, public UpgradeMux, public DamageModuleInterface
{
public:
	FireWeaponWhenDamagedBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponWhenDamagedBehavior();

private:
	const FireWeaponWhenDamagedBehaviorModuleData *getFireWeaponWhenDamagedBehaviorModuleData() const
	{
		return reinterpret_cast<const FireWeaponWhenDamagedBehaviorModuleData *>(m_moduleData);
	}

	const Object *getObject() const
	{
		return m_object;
	}

	Weapon *m_reactionWeaponPristine;
	Weapon *m_reactionWeaponDamaged;
	Weapon *m_reactionWeaponReallyDamaged;
	Weapon *m_reactionWeaponRubble;
	Weapon *m_continuousWeaponPristine;
	Weapon *m_continuousWeaponDamaged;
	Weapon *m_continuousWeaponReallyDamaged;
	Weapon *m_continuousWeaponRubble;
};

static const int UPDATE_SLEEP_NONE = 1;
static const int UPDATE_SLEEP_FOREVER = 0x3fffffff;

// ??0FireWeaponWhenDamagedBehavior@@QAE@PAVThing@@PBVModuleData@@@Z @0x00482803
FireWeaponWhenDamagedBehavior::FireWeaponWhenDamagedBehavior(Thing *thing, const ModuleData *moduleData) :
	UpdateModule(thing, moduleData),
	m_reactionWeaponPristine(0),
	m_reactionWeaponDamaged(0),
	m_reactionWeaponReallyDamaged(0),
	m_reactionWeaponRubble(0),
	m_continuousWeaponPristine(0),
	m_continuousWeaponDamaged(0),
	m_continuousWeaponReallyDamaged(0),
	m_continuousWeaponRubble(0)
{
	const FireWeaponWhenDamagedBehaviorModuleData *d = getFireWeaponWhenDamagedBehaviorModuleData();
	const Object *obj = getObject();

	if (d->m_reactionWeaponPristine)
	{
		m_reactionWeaponPristine = TheWeaponStore->allocateNewWeapon(
			d->m_reactionWeaponPristine, PRIMARY_WEAPON);
		m_reactionWeaponPristine->reloadAmmo(obj);
		m_reactionWeaponPristine->m_status = obj->m_weaponStatus;
	}
	if (d->m_reactionWeaponDamaged)
	{
		m_reactionWeaponDamaged = TheWeaponStore->allocateNewWeapon(
			d->m_reactionWeaponDamaged, PRIMARY_WEAPON);
		m_reactionWeaponDamaged->reloadAmmo(obj);
		m_reactionWeaponDamaged->m_status = obj->m_weaponStatus;
	}
	if (d->m_reactionWeaponReallyDamaged)
	{
		m_reactionWeaponReallyDamaged = TheWeaponStore->allocateNewWeapon(
			d->m_reactionWeaponReallyDamaged, PRIMARY_WEAPON);
		m_reactionWeaponReallyDamaged->reloadAmmo(obj);
		m_reactionWeaponReallyDamaged->m_status = obj->m_weaponStatus;
	}
	if (d->m_reactionWeaponRubble)
	{
		m_reactionWeaponRubble = TheWeaponStore->allocateNewWeapon(
			d->m_reactionWeaponRubble, PRIMARY_WEAPON);
		m_reactionWeaponRubble->reloadAmmo(obj);
		m_reactionWeaponRubble->m_status = obj->m_weaponStatus;
	}
	if (d->m_continuousWeaponPristine)
	{
		m_continuousWeaponPristine = TheWeaponStore->allocateNewWeapon(
			d->m_continuousWeaponPristine, PRIMARY_WEAPON);
		m_continuousWeaponPristine->reloadAmmo(obj);
		m_continuousWeaponPristine->m_status = obj->m_weaponStatus;
	}
	if (d->m_continuousWeaponDamaged)
	{
		m_continuousWeaponDamaged = TheWeaponStore->allocateNewWeapon(
			d->m_continuousWeaponDamaged, PRIMARY_WEAPON);
		m_continuousWeaponDamaged->reloadAmmo(obj);
		m_continuousWeaponDamaged->m_status = obj->m_weaponStatus;
	}
	if (d->m_continuousWeaponReallyDamaged)
	{
		m_continuousWeaponReallyDamaged = TheWeaponStore->allocateNewWeapon(
			d->m_continuousWeaponReallyDamaged, PRIMARY_WEAPON);
		m_continuousWeaponReallyDamaged->reloadAmmo(obj);
		m_continuousWeaponReallyDamaged->m_status = obj->m_weaponStatus;
	}
	if (d->m_continuousWeaponRubble)
	{
		m_continuousWeaponRubble = TheWeaponStore->allocateNewWeapon(
			d->m_continuousWeaponRubble, PRIMARY_WEAPON);
		m_continuousWeaponRubble->reloadAmmo(obj);
		m_continuousWeaponRubble->m_status = obj->m_weaponStatus;
	}

	if (d->m_initiallyActive)
	{
		giveSelfUpgrade();
	}

	UpgradeMux *upgradeMux = this;
	if (upgradeMux->isUpgradeActive() &&
		(d->m_continuousWeaponPristine != NULL ||
		d->m_continuousWeaponDamaged != NULL ||
		d->m_continuousWeaponReallyDamaged != NULL ||
		d->m_continuousWeaponRubble != NULL))
	{
		setWakeFrame(const_cast<Object *>(getObject()), UPDATE_SLEEP_NONE);
	}
	else
	{
		setWakeFrame(const_cast<Object *>(getObject()), UPDATE_SLEEP_FOREVER);
	}
}
