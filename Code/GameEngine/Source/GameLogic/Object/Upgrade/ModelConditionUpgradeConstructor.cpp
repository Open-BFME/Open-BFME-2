// cl: /DNDEBUG /MD /EHsc
// readable body of ??0ModelConditionUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Upgrade/ModelConditionUpgrade.cpp

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ModelConditionUpgrade.h
class ModelConditionUpgrade : public UpgradeModule
{
public:
	ModelConditionUpgrade( Thing *thing, const ModuleData *moduleData );
public:
	// retail slot 4: the rowed ?getModuleNameKey@ModelConditionUpgrade@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

ModelConditionUpgrade::ModelConditionUpgrade( Thing *thing, const ModuleData *moduleData )
	: UpgradeModule( thing, moduleData )
{
}
