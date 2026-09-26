// cl: /O1 /DNDEBUG /MD /EHsc

// Open-BFME5: StealthUpgrade module ctor via UpgradeModule multi-inheritance.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
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
	UpgradeModule( Thing *thing, const ModuleData *moduleData );
protected:
	virtual ~UpgradeModule();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StealthUpgrade.h
class StealthUpgrade : public UpgradeModule
{
public:
	StealthUpgrade( Thing *thing, const ModuleData *moduleData );
protected:
	virtual ~StealthUpgrade();
};

// ??0StealthUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
StealthUpgrade::StealthUpgrade(
	Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}

// ??1StealthUpgrade@@MAE@XZ @0x004B530D 32B: four vptr stores at
// +0/+0xC/+0x10/+0x18 then tail-jmp to base dtor at 0x0046089D (rowed as
// ??1FireWeaponWhenDeadBehavior@@MAE@XZ; UpgradeModule twin pin, ICF fold).
// Donor ZH StealthUpgrade.cpp empty dtor; vtable 0x00857E30 slot 0 ??_G next.
StealthUpgrade::~StealthUpgrade()
{
}