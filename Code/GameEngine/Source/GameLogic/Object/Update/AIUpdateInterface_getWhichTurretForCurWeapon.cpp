// cl: /DNDEBUG /MD
//
// ?getWhichTurretForCurWeapon@AIUpdateInterface@@QBE?AW4WhichTurretType@@XZ,
// retail 0x0026275E, 44 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:770) with the BFME2 layout: m_turretAI lives at +0x20C
// (single turret, MAX_TURRETS is 1). TurretAI::isOwnersCurWeaponOnTurret is
// a direct (non-virtual) const call, resolved by pin.

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

enum
{
	MAX_TURRETS = 1
};

struct TurretAI
{
	bool isOwnersCurWeaponOnTurret() const;
};

class AIUpdateInterface
{
	char m_pad[0x20C];
	TurretAI *m_turretAI[MAX_TURRETS];

public:
	WhichTurretType getWhichTurretForCurWeapon() const;
};

// ?getWhichTurretForCurWeapon@AIUpdateInterface@@QBE?AW4WhichTurretType@@XZ
WhichTurretType AIUpdateInterface::getWhichTurretForCurWeapon() const
{
	for (int i = 0; i < MAX_TURRETS; ++i)
	{
		if (m_turretAI[i] && m_turretAI[i]->isOwnersCurWeaponOnTurret())
		{
			return (WhichTurretType)i;
		}
	}
	return TURRET_INVALID;
}
