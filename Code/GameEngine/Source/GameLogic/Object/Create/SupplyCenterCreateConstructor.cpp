// cl: /O1 /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h
class CreateModule : public BehaviorModule, public ModuleInterface
{
public:
	CreateModule( Thing *thing, const ModuleData *moduleData );
protected:
	virtual ~CreateModule();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterCreate.h
class SupplyCenterCreate : public CreateModule
{
public:
	SupplyCenterCreate( Thing *thing, const ModuleData *moduleData );
protected:
	virtual ~SupplyCenterCreate();
public:
	// retail slot 4: the rowed ?getModuleNameKey@SupplyCenterCreate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

SupplyCenterCreate::SupplyCenterCreate( Thing *thing, const ModuleData *moduleData )
	: CreateModule( thing, moduleData )
{
}

// ??1SupplyCenterCreate@@MAE@XZ present-unmatched
SupplyCenterCreate::~SupplyCenterCreate()
{
}
