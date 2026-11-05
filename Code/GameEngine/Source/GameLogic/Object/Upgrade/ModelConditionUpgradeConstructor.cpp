// cl: /DNDEBUG /MD /EHsc
// readable body of ??0ModelConditionUpgrade@@QAE@PAVThing@@PBVModuleData@@@Z: Code/GameEngine/Source/GameLogic/Object/Upgrade/ModelConditionUpgrade.cpp

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpgradeModule.h
#include "../../../../Include/GameLogic/Module/UpgradeModule.h"

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
