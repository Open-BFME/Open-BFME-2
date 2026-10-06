// cl: /DNDEBUG /MD
//
// ?setTurretTargetPosition@AIUpdateInterface@@QAEXW4WhichTurretType@@PBUCoord3D@@@Z,
// retail 0x00262636, 27 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:692) with the BFME2 layout: m_turretAI lives at +0x20C
// (single turret, MAX_TURRETS is 1). TurretAI::setTurretTargetPosition is
// a direct (non-virtual) call, resolved by pin.

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct TurretAI
{
	void setTurretTargetPosition(const Coord3D *pos);
};

class AIUpdateInterface
{
	char m_pad[0x20C];
	TurretAI *m_turretAI[1];

public:
	void setTurretTargetPosition(WhichTurretType tur, const Coord3D *pos);
};

// ?setTurretTargetPosition@AIUpdateInterface@@QAEXW4WhichTurretType@@PBUCoord3D@@@Z
void AIUpdateInterface::setTurretTargetPosition(WhichTurretType tur, const Coord3D *pos)
{
	if (m_turretAI[tur])
	{
		m_turretAI[tur]->setTurretTargetPosition(pos);
	}
}
