// cl: /DNDEBUG /MD
//
// ?setLocomotorGoalPositionOnPath@AIUpdateInterface@@UAEXXZ, retail 0x00262C13, 34 bytes.
// ?setLocomotorGoalPositionExplicit@AIUpdateInterface@@UAEXABUCoord3D@@@Z, retail 0x00262C35, 30 bytes.
// ?setLocomotorGoalOrientation@AIUpdateInterface@@UAEXM@Z, retail 0x00262C9B, 27 bytes.
// ZH donor AIUpdate.cpp verbatim locomotor goal setters for m_locomotorGoalType at +0x1FC
// and m_locomotorGoalData at +0x200.

// Coord3D: shared header/view; no private copy.
#include "../../../../../Libraries/Include/Lib/Coord3DInline.h"

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

void AIUpdateInterface::setLocomotorGoalPositionOnPath()
{
	m_field1FC = 1;
	m_field200.zero();
}

void AIUpdateInterface::setLocomotorGoalPositionExplicit(const Coord3D &newPos)
{
	m_field1FC = 2;
	m_field200 = newPos;
}

void AIUpdateInterface::setLocomotorGoalOrientation(float angle)
{
	m_field1FC = 3;
	m_field200.x = angle;
}

