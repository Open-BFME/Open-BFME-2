// cl: /DNDEBUG /MD
//
// Object::getControllingPlayer, retail 0x0028AFA9, 18 bytes.
// Dedicated TU so Object.cpp and RadiusDecalUpdate.cpp cannot see this body.
// Null-checks team at this+0x304 then tail-calls Team::getControllingPlayer.

class Player;

#include "../../../Include/Common/TeamBFME2.h"

#include "object.h"

Player *Object::getControllingPlayer() const
{
	Team *team = m_team;
	if (team)
		return team->getControllingPlayer();
	return 0;
}
