// cl: /DNDEBUG /MD /EHsc
// readable body of ??0FXListDie@@: Code/GameEngine/Source/GameLogic/Object/Die/FXListDie.cpp

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
#include "../../../../Include/Common/ObjectModule.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../Include/GameLogic/Module/DieModule.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FXListDie.h
class FXListDie : public DieModule
{
public:
	FXListDie( Thing *thing, const ModuleData *moduleData );
};

FXListDie::FXListDie( Thing *thing, const ModuleData *moduleData )
	: DieModule( thing, moduleData )
{
}
