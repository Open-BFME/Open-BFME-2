#pragma once

// FireWeaponWhenDamagedBehavior's class and module-data declarations over the
// canonical module headers, shared by every unit that defines one of its
// bodies. Not a recovered donor header.
//
// Target facts: UpdateModule is 0x20, UpgradeMux sits at +0x20 and
// DamageModuleInterface at +0x28, and the eight weapon pointers occupy
// +0x2C..+0x48 in the matched ctor (0x00482803) and dtor (0x00482551). The
// ctor copies Object+0x74 (Object::m_id) into Weapon+0x08 (Weapon::m_ownerID)
// for every allocated weapon. Retail's +0x10 interface table (0x00849594)
// names the 0x00482B24 update body in slot 0; the +0x28 damage table
// (0x00849588) names the 0x00482A69 onDamage body in slot 0. The module data
// fields (+0x118 initially active, +0x11C damage types, +0x120 damage amount,
// +0x124..+0x140 weapon templates) are the offsets the matched bodies read.

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

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
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

#include "../../../../Include/GameLogic/WeaponStore.h"
extern WeaponStore *TheWeaponStore;

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

#include "../../../../Include/GameLogic/Module/DamageModuleClass.h"

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
	virtual ~FireWeaponWhenDamagedBehavior();
	virtual UpdateSleepTime update();
	virtual void onDamage(DamageInfo *damageInfo);
	virtual NameKeyType getModuleNameKey() const;

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
public:
	// BehaviorModuleInterface table 0x00C495A0 (+0x0C): the receiver converted to the
	// class's own interface, the null-preserving casts retail folds across the module family.
	virtual DamageModuleInterface *getDamage();			// slot 4: retail 0x004523A9, the +0x28 DamageModuleInterface
	virtual UpgradeModuleInterface *getUpgrade();			// slot 10: retail 0x004543A9, the +0x20 UpgradeMux
};
