// cl: /O1 /DNDEBUG /MD /EHsc

// Open-BFME5: ArmorUpgrade module dtor via UpgradeModule multi-inheritance.
// ??1ArmorUpgrade@@MAE@XZ, retail 0x004B33FD, 32 bytes: four vptr stores
// (+0x00 0x8570A0 +0x0C 0x857328 +0x10 0x857058 +0x18 0x858790, DIR32)
// then tail-jmp to the UpgradeModule base dtor (twin pin
// ??1UpgradeModule@@MAE@XZ at 0x0046089D, ICF-folded under the rowed
// ??1FireWeaponWhenDeadBehavior@@MAE@XZ there; PoisonedBehaviorDtor
// precedent). Donor is ZH ArmorUpgrade.cpp:81 (trivial dtor). Identity is
// vtable 0x8570A0 of the rowed ctor plus sole caller ??_G 0x4B3499 slot 0.

class Thing;
class ModuleData;

class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
	virtual ~BehaviorModule();

private:
	unsigned char m_data[8];
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpgradeMux
{
public:
	virtual void upgradeMuxAnchor();

private:
	bool m_upgradeExecuted;
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

class UpgradeModule : public BehaviorModule,
	public BehaviorModuleInterface,
	public UpgradeMux,
	public ModuleInterface
{
public:
	UpgradeModule(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~UpgradeModule();
};

class ArmorUpgrade : public UpgradeModule
{
public:
	ArmorUpgrade(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~ArmorUpgrade();
};

// ??1ArmorUpgrade@@MAE@XZ @0x004B33FD
ArmorUpgrade::~ArmorUpgrade()
{
}
