// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ?update@FireWeaponWhenDamagedBehavior@@UAE?AW4UpdateSleepTime@@XZ @0x00482B24 149B
// UpdateModuleInterface slot 0 via vtable 0x00849594 of FireWeaponWhenDamagedBehavior; donor ZH FireWeaponWhenDamagedBehavior.cpp update.
// Evidence: slot 0 with slot 1 getDisabledTypesToProcess neighbour and +0x10 interface this giving lea ecx esi+0x10 and mov edi esi-8 and continuous weapons esi+0x2c-0x38.
class Thing;
class ModuleData;
class WeaponTemplate;
class DamageInfo;

typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_INVALID = 0,
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum WeaponStatus
{
	READY_TO_FIRE = 0,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK
};

enum BodyDamageType
{
	BODY_PRISTINE = 0,
	BODY_DAMAGED = 1,
	BODY_REALLYDAMAGED = 2,
	BODY_RUBBLE = 3
};

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual BodyDamageType getDamageState() const;
};

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	BodyModuleInterface *getBodyModule() const { return m_body; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0x254 - 0x44];
	BodyModuleInterface *m_body; // +0x254
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	Object *forceFireWeapon(const Object *source, const Coord3D *pos);
};

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

class DamageModuleInterface
{
public:
	virtual void onDamage(DamageInfo *damageInfo) = 0;
	virtual void onHealing(DamageInfo *damageInfo) = 0;
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState) = 0;
};

class FireWeaponWhenDamagedBehavior : public UpdateModule, public UpgradeMux, public DamageModuleInterface
{
public:
	FireWeaponWhenDamagedBehavior(Thing *thing, const ModuleData *moduleData);
	virtual UpdateSleepTime update();

private:
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

UpdateSleepTime FireWeaponWhenDamagedBehavior::update()
{
	if (!isUpgradeActive())
		return UPDATE_SLEEP_FOREVER;

	const Object *obj = getObject();
	BodyDamageType bdt = obj->getBodyModule()->getDamageState();

	if (bdt == BODY_RUBBLE)
	{
		if (m_continuousWeaponRubble && m_continuousWeaponRubble->getStatus() == READY_TO_FIRE)
			m_continuousWeaponRubble->forceFireWeapon(obj, obj->getPosition());
	}
	else if (bdt == BODY_REALLYDAMAGED)
	{
		if (m_continuousWeaponReallyDamaged && m_continuousWeaponReallyDamaged->getStatus() == READY_TO_FIRE)
			m_continuousWeaponReallyDamaged->forceFireWeapon(obj, obj->getPosition());
	}
	else if (bdt == BODY_DAMAGED)
	{
		if (m_continuousWeaponDamaged && m_continuousWeaponDamaged->getStatus() == READY_TO_FIRE)
			m_continuousWeaponDamaged->forceFireWeapon(obj, obj->getPosition());
	}
	else
	{
		if (m_continuousWeaponPristine && m_continuousWeaponPristine->getStatus() == READY_TO_FIRE)
			m_continuousWeaponPristine->forceFireWeapon(obj, obj->getPosition());
	}

	return UPDATE_SLEEP_NONE;
}
