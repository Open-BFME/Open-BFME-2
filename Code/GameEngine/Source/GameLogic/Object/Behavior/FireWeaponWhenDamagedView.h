#pragma once

// Scoped union of the existing BFME 2 ctor/dtor declarations, not a recovered
// donor header. UpdateModule is 0x20, UpgradeMux is at +0x20, DamageModuleInterface
// at +0x28, and the eight weapon pointers at +0x2C..+0x48 in both matched bodies.
// Weapon's existing ctor status access is +0x08; the dtor dispatches slot zero.

class Thing;

class ModuleData;

class WeaponTemplate;

class DamageInfo;

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
	virtual void *deleteInstance(int flags);
	void reloadAmmo(const Object *sourceObj);

	unsigned char m_pad[4]; // vptr + padding keeps the ctor's status at +0x08
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

enum UpdateSleepTime {};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);

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

enum BodyDamageType {};

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(DamageInfo *damageInfo) = 0;
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState) = 0;
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
	// Retail's +0x10 interface table (0x00849594) names the existing
	// 0x00482B24 update body, as in FireWeaponWhenDamagedBehaviorUpdate.cpp.
	virtual UpdateSleepTime update();

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
