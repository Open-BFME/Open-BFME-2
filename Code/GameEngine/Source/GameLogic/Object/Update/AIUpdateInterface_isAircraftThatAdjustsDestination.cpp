// cl: /DNDEBUG /MD
//
// ?isAircraftThatAdjustsDestination@AIUpdateInterface@@QBE_NXZ, retail 0x00262CBE, 52 bytes.
// ?getTreatAsAircraftForLocoDistToGoal@AIUpdateInterface@@UBE_NXZ, retail 0x00262CF2, 59 bytes.
// ZH donor AIUpdate.cpp aircraft destination and distance-to-goal methods.

#include "../../../../Include/GameLogic/LocomotorTemplate.h"

#include "../../../../Include/GameLogic/LocomotorClass.h"




#include "../../../../Include/GameLogic/Module/AIUpdate.h"

bool AIUpdateInterface::isAircraftThatAdjustsDestination() const
{
	if (vslot090())
		return true;
	Locomotor *curLocomotor = const_cast<AIUpdateInterface *>(this)->getCurLocomotor();
	if (!curLocomotor)
		return false;
	if (curLocomotor->m_template->m_appearance == 2)
		return true;
	if (curLocomotor->m_template->m_appearance == 3)
		return true;
	return false;
}

bool AIUpdateInterface::getTreatAsAircraftForLocoDistToGoal() const
{
	bool treatAsAircraft = !isDoingGroundMovement();
	if (m_pathExtraDistance > 1.0f)
		treatAsAircraft = true;
	if (m_curLocomotor && m_curLocomotor->m_template->m_appearance == 2)
		treatAsAircraft = true;
	return treatAsAircraft;
}
