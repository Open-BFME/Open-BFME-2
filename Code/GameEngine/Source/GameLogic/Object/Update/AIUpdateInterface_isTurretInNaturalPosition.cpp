// cl: /DNDEBUG /MD
//
// ?isTurretInNaturalPosition@AIUpdateInterface@@QBE_NW4WhichTurretType@@@Z,
// retail 0x0026269C, 27 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:730) with the BFME2 layout: m_turretAI lives at +0x20C
// (single turret, MAX_TURRETS is 1). TurretAI::isTurretInNaturalPosition is
// a direct (non-virtual) const call, resolved by pin.

typedef bool Bool;

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

struct TurretAI
{
	Bool isTurretInNaturalPosition() const;
};

#include "../../../../Include/GameLogic/Module/AIUpdate.h"

// ?isTurretInNaturalPosition@AIUpdateInterface@@QBE_NW4WhichTurretType@@@Z
Bool AIUpdateInterface::isTurretInNaturalPosition(WhichTurretType tur) const
{
	if (m_turretAI[tur])
	{
		return m_turretAI[tur]->isTurretInNaturalPosition();
	}
	return false;
}
