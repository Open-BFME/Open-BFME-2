// cl: /DNDEBUG /MD
//
// ?recenterTurret@AIUpdateInterface@@QAEXW4WhichTurretType@@@Z,
// retail 0x0026266C, 23 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:710) with the BFME2 layout: m_turretAI lives at +0x20C
// (single turret, MAX_TURRETS is 1). TurretAI::recenterTurret is a direct
// (non-virtual) call, resolved by pin.

typedef int Bool;

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

struct TurretAI
{
	void recenterTurret();
};

class AIUpdateInterface
{
	char m_pad[0x20C];
	TurretAI *m_turretAI[1];

public:
	void recenterTurret(WhichTurretType tur);
};

// ?recenterTurret@AIUpdateInterface@@QAEXW4WhichTurretType@@@Z
void AIUpdateInterface::recenterTurret(WhichTurretType tur)
{
	if (m_turretAI[tur])
	{
		m_turretAI[tur]->recenterTurret();
	}
}
