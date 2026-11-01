// cl: /DNDEBUG /MD
//
// ?setTurretEnabled@AIUpdateInterface@@QAEXW4WhichTurretType@@_N@Z,
// retail 0x00262651, 27 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:701) with the BFME2 layout: m_turretAI lives at +0x20C
// (single turret, MAX_TURRETS is 1). TurretAI::setTurretEnabled is a direct
// (non-virtual) call, resolved by pin.

typedef bool Bool;

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

struct TurretAI
{
	void setTurretEnabled(Bool enabled);
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

// ?setTurretEnabled@AIUpdateInterface@@QAEXW4WhichTurretType@@_N@Z
void AIUpdateInterface::setTurretEnabled(WhichTurretType tur, Bool enabled)
{
	if (m_turretAI[tur])
	{
		m_turretAI[tur]->setTurretEnabled(enabled);
	}
}
