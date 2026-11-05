// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?onDie@FireWeaponWhenDeadBehavior@@UAEXPBVDamageInfo@@@Z, retail 0x00482C4A
// (310 bytes). Zero Hour's FireWeaponWhenDeadBehavior::onDie (GeneralsMD
// GameLogic/Object/Behavior/FireWeaponWhenDeadBehavior.cpp) in its BFME 2
// form. Target evidence: the one slot of the die-interface vtable 0x00849698
// that the rowed ctor 0x00482D80 stores at +0x28, so the body runs on the
// +0x28 subobject. BFME 2 additions over Zero Hour:
//  - with the +0xA8 delay count set (ctor: module data DelayTime +0x11C)
//    the damage record is copied to +0x2C (rowed operator= 0x003427DD) and
//    the module wakes next frame (rowed setWakeFrame 0x0044DF71);
//  - StartsActive (+0x118) passes the upgrade test too;
//  - status 0x56 always blocks and status 2 blocks unless
//    ActiveDuringConstruction (+0x119);
//  - the death weapon (+0x15C) fires from WeaponOffset (+0x120) moved into
//    world space by the rowed Thing::transformPoint 0x0030A812;
//  - the controlling player is not null-checked.
// Other callees: pinned DieMuxData::isDieApplicable 0x004CE588 (+0x12C),
// rowed Object::testStatus 0x0004E536, the UpgradeMux slots 0
// (isUpgradeActive) and 11 (getUpgradeActivationMasks 0x00452460), the
// rowed mask clear 0x001EAE6F as the mask constructor, rowed mask test
// 0x00406F9C on the object (+0x284) and player (+0x13C) masks,
// getControllingPlayer 0x0028AFA9 and createAndFireTempWeapon 0x002CE904.
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

class Thing;
class ModuleData;
class DamageInfo;
class WeaponTemplate;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_BFME_2 = 2,
	OBJECT_STATUS_BFME_56 = 0x56
};

// The 0x80-byte upgrade mask: constructed through the rowed clear.
#include "../../../../Include/Common/Rva001EAE6FHelper.h"

class Rva00406F9C
{
public:
	bool rva00406F9C(const void *other);
};

struct UpgradeMaskType
{
	UpgradeMaskType() { ((Rva001EAE6FHelper *)this)->clear80(); }
	char m_bits[0x80];
};

class Player
{
public:
	Bool testForAnyCompletedUpgrade(const UpgradeMaskType &mask) { return ((Rva00406F9C *)&m_completedUpgrades)->rva00406F9C(&mask); }
private:
	char m_pad000[0x13C];
	UpgradeMaskType m_completedUpgrades; // +0x13C
};

#include "../../../Common/Thing/thing.h"

class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	Bool testForAnyCompletedUpgrade(const UpgradeMaskType &mask) { return ((Rva00406F9C *)&m_completedUpgrades)->rva00406F9C(&mask); }
private:
	char m_pad060[0x284 - 0x60];
	UpgradeMaskType m_completedUpgrades; // +0x284
};

#include "../../../../Include/GameLogic/WeaponStore.h"

extern WeaponStore *TheWeaponStore;

#include "../../../../Include/GameLogic/Module/DieMuxData.h"

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


#include "../../../../Include/GameLogic/Module/UpdateModule.h"


#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

#include "../../../../Include/GameLogic/Module/DieModuleInterface.h"

// The +0x2C damage record; its assignment is rowed at 0x003427DD.
class Rva003427DD
{
public:
	Rva003427DD &operator=(const Rva003427DD &other);
private:
	unsigned char m_data[0x7C];
};

class FireWeaponWhenDeadBehaviorModuleData
{
public:
	unsigned char m_pad00[0x118];
	Bool m_startsActive; // +0x118
	Bool m_activeDuringConstruction; // +0x119
	UnsignedInt m_delayTime; // +0x11C
	Coord3D m_weaponOffset; // +0x120
	DieMuxData m_dieMuxData; // +0x12C
	const WeaponTemplate *m_deathWeapon; // +0x15C
};

class FireWeaponWhenDeadBehavior : public UpdateModule, public UpgradeMux, public DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo);
	// WorldBuilder 0x011BB480 reaches slot 0 through the full object
	// (this-0x28, then its +0x20 UpgradeMux) rather than directly as the
	// later slot-11 call does: an inline helper of the module.
	Bool isActiveUpgrade() const { return isAlreadyUpgraded(); }
private:
	const FireWeaponWhenDeadBehaviorModuleData *getFireWeaponWhenDeadBehaviorModuleData() const { return (const FireWeaponWhenDeadBehaviorModuleData *)m_moduleData; }

	Rva003427DD m_damageInfo; // +0x2C
	Int m_delayCount; // +0xA8
};

void FireWeaponWhenDeadBehavior::onDie( const DamageInfo *damageInfo )
{
	const FireWeaponWhenDeadBehaviorModuleData* fireWeaponWhenDeadBehaviorModuleData = getFireWeaponWhenDeadBehaviorModuleData();
	if (m_delayCount > 0)
	{
		m_damageInfo = *(const Rva003427DD *)damageInfo;
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
		return;
	}
	if (!isActiveUpgrade() && !getFireWeaponWhenDeadBehaviorModuleData()->m_startsActive)
		return;
	if (!fireWeaponWhenDeadBehaviorModuleData->m_dieMuxData.isDieApplicable(getObject(), damageInfo))
		return;
	Object *obj = getObject();
	if (obj->testStatus(OBJECT_STATUS_BFME_56))
		return;
	if (!fireWeaponWhenDeadBehaviorModuleData->m_activeDuringConstruction && obj->testStatus(OBJECT_STATUS_BFME_2))
		return;
	UpgradeMaskType activation, conflicting;
	getUpgradeActivationMasks( activation, conflicting );
	Object *owner = getObject();
	if( owner->testForAnyCompletedUpgrade( conflicting ) )
		return;
	if( owner->getControllingPlayer()->testForAnyCompletedUpgrade( conflicting ) )
		return;
	if (fireWeaponWhenDeadBehaviorModuleData->m_deathWeapon)
	{
		Coord3D pos;
		getObject()->transformPoint(&fireWeaponWhenDeadBehaviorModuleData->m_weaponOffset, &pos);
		TheWeaponStore->createAndFireTempWeapon(fireWeaponWhenDeadBehaviorModuleData->m_deathWeapon, getObject(), &pos);
	}
}
