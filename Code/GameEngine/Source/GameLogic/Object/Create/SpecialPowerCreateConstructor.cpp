// cl: /O1 /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/BehaviorModule.h"


#include "../../../../Include/Common/ModuleInterface.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateModule.h
#include "../../../../Include/GameLogic/Module/CreateModuleClass.h"

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

SpecialPowerCreate::~SpecialPowerCreate()
{
}
