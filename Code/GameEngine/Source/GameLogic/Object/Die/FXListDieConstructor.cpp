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
#include "../../../../Include/Common/FXListDie.h"

FXListDie::FXListDie( Thing *thing, const ModuleData *moduleData )
	: DieModule( thing, moduleData )
{
}

// ??1FXListDie@@UAE@XZ @0x00486579 (25B): restores the three vptrs the
// constructor installs (0x0084AD04 at +0, 0x0084A650 at +0xC, 0x0084AD00 at
// +0x10) and tail-jumps to ~DieModule. Slot 0 of FXListDie's own vftable
// 0x0084AD04 is the scalar deleting destructor 0x00486607, which calls this
// body.
FXListDie::~FXListDie()
{
}
