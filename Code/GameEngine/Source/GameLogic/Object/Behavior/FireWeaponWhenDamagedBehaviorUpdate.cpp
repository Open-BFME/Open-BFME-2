// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ?update@FireWeaponWhenDamagedBehavior@@UAE?AW4UpdateSleepTime@@XZ @0x00482B24 149B
// UpdateModuleInterface slot 0 via vtable 0x00849594 of FireWeaponWhenDamagedBehavior; donor ZH FireWeaponWhenDamagedBehavior.cpp update.
// Evidence: slot 0 with slot 1 getDisabledTypesToProcess neighbour and +0x10 interface this giving lea ecx esi+0x10 and mov edi esi-8 and continuous weapons esi+0x2c-0x38.
// ?onDamage@FireWeaponWhenDamagedBehavior@@UAEXPAVDamageInfo@@@Z @0x00482A69 187B
// DamageModuleInterface slot 0 via vtable 0x00849588 of FireWeaponWhenDamagedBehavior; donor ZH FireWeaponWhenDamagedBehavior.cpp onDamage.
// Evidence: slot 0 and UpgradeMux active check and damage type bit test moduleData+0x11C with DamageInfo+0x10 and amount comiss moduleData+0x120 vs DamageInfo+0x70 and reaction weapons.
#include "FireWeaponWhenDamagedView.h"

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
