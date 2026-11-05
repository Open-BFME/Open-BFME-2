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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerCreate.h
class SpecialPowerCreate : public CreateModule
{
public:
	SpecialPowerCreate( Thing *thing, const ModuleData *moduleData );
protected:
	virtual ~SpecialPowerCreate();
public:
	// retail slot 4: the rowed ?getModuleNameKey@SpecialPowerCreate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

SpecialPowerCreate::SpecialPowerCreate( Thing *thing, const ModuleData *moduleData )
	: CreateModule( thing, moduleData )
{
}

// ??1SpecialPowerCreate@@MAE@XZ present-unmatched
SpecialPowerCreate::~SpecialPowerCreate()
{
}
