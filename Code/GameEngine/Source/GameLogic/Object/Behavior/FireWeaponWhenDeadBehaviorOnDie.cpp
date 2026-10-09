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
class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80();
private:
	char m_pad[0x80];
};

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

class Thing
{
public:
	void transformPoint(const Coord3D *in, Coord3D *out);
};

class Object : public Thing
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Player *getControllingPlayer() const;
	Bool testForAnyCompletedUpgrade(const UpgradeMaskType &mask) { return ((Rva00406F9C *)&m_completedUpgrades)->rva00406F9C(&mask); }
private:
	char m_pad000[0x284];
	UpgradeMaskType m_completedUpgrades; // +0x284
};

class WeaponStore
{
public:
	void createAndFireTempWeapon(const WeaponTemplate *wt, const Object *source, const Coord3D *pos);
};

extern WeaponStore *TheWeaponStore;

class DieMuxData
{
public:
	Bool isDieApplicable(const Object *obj, const DamageInfo *damageInfo) const;
private:
	unsigned char m_pad[0x30];
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void getBody();
};

class BehaviorModule : public ObjectModule, public BehaviorModuleInterface
{
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
protected:
	Object *getObject() const { return m_object; }
	void setWakeFrame(Object *obj, UpdateSleepTime wakeDelay);
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic; // +0x18
	Int m_reserved1C; // +0x1C
};

class UpgradeMux
{
public:
	virtual Bool isUpgradeActive() const;
	virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06();
	virtual void slot07(); virtual void slot08(); virtual void slot09();
	virtual void slot10();
	virtual void getUpgradeActivationMasks(UpgradeMaskType &activation, UpgradeMaskType &conflicting) const;
protected:
	Bool m_upgradeExecuted; // +0x04
};

class DieModuleInterface
{
public:
	virtual void onDie(const DamageInfo *damageInfo) = 0;
};

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
	Bool isActiveUpgrade() const { return isUpgradeActive(); }
private:
	const FireWeaponWhenDeadBehaviorModuleData *getFireWeaponWhenDeadBehaviorModuleData() const { return (const FireWeaponWhenDeadBehaviorModuleData *)m_moduleData; }

	Rva003427DD m_damageInfo; // +0x2C
	Int m_delayCount; // +0xA8
};

void FireWeaponWhenDeadBehavior::onDie( const DamageInfo *damageInfo )
{
	const FireWeaponWhenDeadBehaviorModuleData* d = getFireWeaponWhenDeadBehaviorModuleData();
	if (m_delayCount > 0)
	{
		m_damageInfo = *(const Rva003427DD *)damageInfo;
		setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
		return;
	}
	if (!isActiveUpgrade() && !getFireWeaponWhenDeadBehaviorModuleData()->m_startsActive)
		return;
	if (!d->m_dieMuxData.isDieApplicable(getObject(), damageInfo))
		return;
	Object *obj = getObject();
	if (obj->testStatus(OBJECT_STATUS_BFME_56))
		return;
	if (!d->m_activeDuringConstruction && obj->testStatus(OBJECT_STATUS_BFME_2))
		return;
	UpgradeMaskType activation, conflicting;
	getUpgradeActivationMasks( activation, conflicting );
	Object *owner = getObject();
	if( owner->testForAnyCompletedUpgrade( conflicting ) )
		return;
	if( owner->getControllingPlayer()->testForAnyCompletedUpgrade( conflicting ) )
		return;
	if (d->m_deathWeapon)
	{
		Coord3D pos;
		getObject()->transformPoint(&d->m_weaponOffset, &pos);
		TheWeaponStore->createAndFireTempWeapon(d->m_deathWeapon, getObject(), &pos);
	}
}
