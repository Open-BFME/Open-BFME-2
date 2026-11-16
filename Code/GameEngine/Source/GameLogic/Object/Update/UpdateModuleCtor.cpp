// cl: /O1 /DNDEBUG /MD
//
// UpdateModule::UpdateModule, retail 0x00253390, 61 bytes. Dedicated TU so
// CreateModule.cpp cannot see this body. BehaviorModule ctor stays at 0x253330.

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

UpdateModule::UpdateModule(Thing *thing, const ModuleData *moduleData)
	: BehaviorModule(thing, moduleData),
	  m_nextCallFrameAndPhase(0),
	  m_indexInLogic(-1),
	  m_field1C(-1)
{
}

// Sole provider for the BehaviorModuleOther placeholder slot that the tables in MineshaftPortalBehaviourCtor.cpp
// and PassiveAreaEffectBehavior.cpp still hold; retail fills it with 0x000D43D0, rowed under this target's name.
#pragma comment(linker, "/alternatename:?unused@BehaviorModuleOther@@EAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
