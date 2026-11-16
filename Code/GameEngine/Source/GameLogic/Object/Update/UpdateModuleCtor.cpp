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
