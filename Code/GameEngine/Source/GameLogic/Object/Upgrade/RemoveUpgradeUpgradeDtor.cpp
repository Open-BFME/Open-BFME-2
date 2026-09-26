// cl: /O1 /DNDEBUG /MD /EHsc

// Open-BFME5: RemoveUpgradeUpgrade module dtor via UpgradeModule multi-inheritance.
// ??1RemoveUpgradeUpgrade@@MAE@XZ, retail 0x004B7F01, 32 bytes: four vptr stores
// (+0x00 0x858E20 +0x0C 0x857328 +0x10 0x858DD8 +0x18 0x858790, DIR32)
// then tail-jmp to the UpgradeModule base dtor (twin pin
// ??1UpgradeModule@@MAE@XZ at 0x0046089D, ICF-folded under the rowed
// ??1FireWeaponWhenDeadBehavior@@MAE@XZ there; ArmorUpgradeDtor
// precedent). Identity is vtable 0x858E20 of the rowed ctor at 0x004B7FA4
// plus sole caller ??_G 0x004B7FD5 slot 0.

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

class RemoveUpgradeUpgrade : public UpgradeModule
{
public:
	RemoveUpgradeUpgrade(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~RemoveUpgradeUpgrade();
};

// ??1RemoveUpgradeUpgrade@@MAE@XZ @0x004B7F01
RemoveUpgradeUpgrade::~RemoveUpgradeUpgrade()
{
}
