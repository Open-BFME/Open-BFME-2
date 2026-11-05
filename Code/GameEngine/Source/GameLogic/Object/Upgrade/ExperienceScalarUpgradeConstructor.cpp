// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ExperienceScalarUpgrade module ctor via UpgradeModule multi-inheritance.

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
	UpgradeModule( Thing *thing, const ModuleData *moduleData );
protected:
	virtual ~UpgradeModule();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ExperienceScalarUpgrade.h
class ExperienceScalarUpgrade : public UpgradeModule
{
public:
	ExperienceScalarUpgrade( Thing *thing, const ModuleData *moduleData );
public:
	// retail slot 4: the rowed ?getModuleNameKey@ExperienceScalarUpgrade@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0ExperienceScalarUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z
ExperienceScalarUpgrade::ExperienceScalarUpgrade(
	Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}