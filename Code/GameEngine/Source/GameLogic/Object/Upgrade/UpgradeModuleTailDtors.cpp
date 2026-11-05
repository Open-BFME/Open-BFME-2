// cl: /DNDEBUG /MD /EHsc
//
// Upgrade module dtors with the StealthUpgrade shape (StealthUpgrade.cpp,
// matched 0x004B530D): four compiler vptr restores at +0/+0xC/+0x10/+0x18,
// then a tail jmp to the UpgradeModule dtor 0x0046089D.
//
// ??1LocomotorSetUpgrade@@MAE@XZ @0x004B3EA0 32B: audited ??_G 0x004B3F3C;
//   slot 4 -> 0x004B3EC6 uses class-name string "LocomotorSetUpgrade".
// ??1AllowBannerSpawnUpgrade@@MAE@XZ @0x004B84EA 32B: audited ??_G 0x004B85B8;
//   slot 4 -> 0x004B8520 uses class-name string "AllowBannerSpawnUpgrade".
// Protected access (MAE) follows the StealthUpgrade precedent and the ZH
// memory-pool glue; the access specifier is not target evidence.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


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

class UpgradeModule : public BehaviorModule, public UpgradeMux, public ModuleInterface
{
public:
protected:
	virtual ~UpgradeModule();
};

class LocomotorSetUpgrade : public UpgradeModule
{
protected:
	virtual ~LocomotorSetUpgrade();
public:
	// retail slot 4: the rowed ?getModuleNameKey@LocomotorSetUpgrade@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

LocomotorSetUpgrade::~LocomotorSetUpgrade()
{
}

class AllowBannerSpawnUpgrade : public UpgradeModule
{
protected:
	virtual ~AllowBannerSpawnUpgrade();
public:
	// retail slot 4: the rowed ?getModuleNameKey@AllowBannerSpawnUpgrade@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

AllowBannerSpawnUpgrade::~AllowBannerSpawnUpgrade()
{
}
