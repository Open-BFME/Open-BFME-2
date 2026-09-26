// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??1DoCommandUpgrade@@MAE@XZ 32B @0x004B4BA1: four vptr stores at
// +0/+0x0C/+0x10/+0x18 then tail-jmp to UpgradeModule base dtor twin
// ??1UpgradeModule@@MAE@XZ at 0x0046089D ICF-folded under rowed
// ??1FireWeaponWhenDeadBehavior@@MAE@XZ. Identity via rowed ctor 0x004B4C2E
// vtable 0x00857B58 plus caller ??_G 0x004B4C5F slot 0. ArmorUpgradeDtor precedent.

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

class DoCommandUpgrade : public UpgradeModule
{
public:
	DoCommandUpgrade(Thing *thing, const ModuleData *moduleData);

protected:
	virtual ~DoCommandUpgrade();
};

DoCommandUpgrade::~DoCommandUpgrade()
{
}
