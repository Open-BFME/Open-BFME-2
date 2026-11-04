// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ?update@FireWeaponWhenDamagedBehavior@@UAE?AW4UpdateSleepTime@@XZ @0x00482B24 149B
// UpdateModuleInterface slot 0 via vtable 0x00849594 of FireWeaponWhenDamagedBehavior; donor ZH FireWeaponWhenDamagedBehavior.cpp update.
// Evidence: slot 0 with slot 1 getDisabledTypesToProcess neighbour and +0x10 interface this giving lea ecx esi+0x10 and mov edi esi-8 and continuous weapons esi+0x2c-0x38.
// ?onDamage@FireWeaponWhenDamagedBehavior@@UAEXPAVDamageInfo@@@Z @0x00482A69 187B
// DamageModuleInterface slot 0 via vtable 0x00849588 of FireWeaponWhenDamagedBehavior; donor ZH FireWeaponWhenDamagedBehavior.cpp onDamage.
// Evidence: slot 0 and UpgradeMux active check and damage type bit test moduleData+0x11C with DamageInfo+0x10 and amount comiss moduleData+0x120 vs DamageInfo+0x70 and reaction weapons.
class Thing;
class ModuleData;
class WeaponTemplate;

#include "../../../../Include/GameLogic/Damage.h"

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

#include "../../../../Include/GameLogic/Module/BodyModule.h"

#include "../object.h"

#include "../../../../Include/GameLogic/Weapon.h"

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

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

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
	unsigned char m_pad00[0x118];
	bool m_initiallyActive; // +0x118
	unsigned char m_pad119[0x11C - 0x119];
	int m_damageTypes; // +0x11C
	float m_damageAmount; // +0x120
	const WeaponTemplate *m_reactionWeaponPristine; // +0x124
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
	virtual UpdateSleepTime update();
	virtual void onDamage(DamageInfo *damageInfo);

private:
	bool isUpgradeActive() const
	{
		return isAlreadyUpgraded();
	}

	const Object *getObject() const
	{
		return m_object;
	}

	const FireWeaponWhenDamagedBehaviorModuleData *getFireWeaponWhenDamagedBehaviorModuleData() const
	{
		return reinterpret_cast<const FireWeaponWhenDamagedBehaviorModuleData *>(m_moduleData);
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

void FireWeaponWhenDamagedBehavior::onDamage(DamageInfo *damageInfo)
{
	if (!isUpgradeActive())
		return;

	const FireWeaponWhenDamagedBehaviorModuleData *fireWeaponWhenDamagedBehaviorModuleData = getFireWeaponWhenDamagedBehaviorModuleData();

	if ((fireWeaponWhenDamagedBehaviorModuleData->m_damageTypes & (1 << (damageInfo->m_damageType - 1))) == 0)
		return;

	if (damageInfo->m_actualDamageDealt < fireWeaponWhenDamagedBehaviorModuleData->m_damageAmount)
		return;

	const Object *obj = getObject();
	BodyDamageType bdt = obj->getBodyModule()->getDamageState();

	if (bdt == BODY_RUBBLE)
	{
		if (m_reactionWeaponRubble && m_reactionWeaponRubble->getStatus() == READY_TO_FIRE)
			m_reactionWeaponRubble->forceFireWeapon(obj, obj->getPosition());
	}
	else if (bdt == BODY_REALLYDAMAGED)
	{
		if (m_reactionWeaponReallyDamaged && m_reactionWeaponReallyDamaged->getStatus() == READY_TO_FIRE)
			m_reactionWeaponReallyDamaged->forceFireWeapon(obj, obj->getPosition());
	}
	else if (bdt == BODY_DAMAGED)
	{
		if (m_reactionWeaponDamaged && m_reactionWeaponDamaged->getStatus() == READY_TO_FIRE)
			m_reactionWeaponDamaged->forceFireWeapon(obj, obj->getPosition());
	}
	else
	{
		if (m_reactionWeaponPristine && m_reactionWeaponPristine->getStatus() == READY_TO_FIRE)
			m_reactionWeaponPristine->forceFireWeapon(obj, obj->getPosition());
	}
}
