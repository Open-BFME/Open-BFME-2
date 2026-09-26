// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??1FireWeaponWhenDamagedBehavior@@UAE@XZ, retail 0x00482551 (234 bytes).
// Behavior-side dtor completing the FireWeaponWhenDamagedBehavior file-unit
// (ctor rowed at 0x00482803 over the same model; deleting dtor at 0x00482A4D
// calls this body). Restores the five vptrs (+0 +0xC +0x10 +0x20 +0x28) then
// releases the eight Weapon slots at +0x2C..+0x48 through the virtual
// deleteInstance slot0 with 0 return-fed to the rowed operator delete at
// 0x0002FD60 then calls the pinned UpdateModule base dtor at 0x0024A797.
// Layout from the rowed ctor TU at 0x00482803 (UpdateModule 0x20 plus
// UpgradeMux at +0x20 plus DamageModuleInterface at +0x28 plus eight Weapon
// slots). Shape follows FireWeaponUpdateDtor at 0x0048BD11 (tracked-pointer
// virtual release slot0 with 0 return-fed operator delete) over the
// PoisonedBehaviorDtor MI precedent.
class Thing;
class ModuleData;
class WeaponTemplate;
class DamageInfo;

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
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

protected:
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

class FireWeaponWhenDamagedBehavior : public UpdateModule, public UpgradeMux, public DamageModuleInterface
{
public:
	FireWeaponWhenDamagedBehavior(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponWhenDamagedBehavior();

private:
	Weapon *m_reactionWeaponPristine; // +0x2C
	Weapon *m_reactionWeaponDamaged; // +0x30
	Weapon *m_reactionWeaponReallyDamaged; // +0x34
	Weapon *m_reactionWeaponRubble; // +0x38
	Weapon *m_continuousWeaponPristine; // +0x3C
	Weapon *m_continuousWeaponDamaged; // +0x40
	Weapon *m_continuousWeaponReallyDamaged; // +0x44
	Weapon *m_continuousWeaponRubble; // +0x48
};

FireWeaponWhenDamagedBehavior::~FireWeaponWhenDamagedBehavior()
{
	if (m_reactionWeaponPristine != 0) {
		::operator delete(m_reactionWeaponPristine->deleteInstance(0));
	}
	if (m_reactionWeaponDamaged != 0) {
		::operator delete(m_reactionWeaponDamaged->deleteInstance(0));
	}
	if (m_reactionWeaponReallyDamaged != 0) {
		::operator delete(m_reactionWeaponReallyDamaged->deleteInstance(0));
	}
	if (m_reactionWeaponRubble != 0) {
		::operator delete(m_reactionWeaponRubble->deleteInstance(0));
	}
	if (m_continuousWeaponPristine != 0) {
		::operator delete(m_continuousWeaponPristine->deleteInstance(0));
	}
	if (m_continuousWeaponDamaged != 0) {
		::operator delete(m_continuousWeaponDamaged->deleteInstance(0));
	}
	if (m_continuousWeaponReallyDamaged != 0) {
		::operator delete(m_continuousWeaponReallyDamaged->deleteInstance(0));
	}
	if (m_continuousWeaponRubble != 0) {
		::operator delete(m_continuousWeaponRubble->deleteInstance(0));
	}
}
