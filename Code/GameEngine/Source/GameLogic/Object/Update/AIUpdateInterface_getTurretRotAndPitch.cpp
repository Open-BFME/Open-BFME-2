// cl: /DNDEBUG /MD
//
// ?getTurretRotAndPitch@AIUpdateInterface@@QBE_NW4WhichTurretType@@PAM1@Z,
// retail 0x002626FA, 54 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:747) with the BFME2 layout: m_turretAI lives at +0x20C.
// Turret angle/pitch are direct inline reads at TurretAI+0x18/+0x1C,
// matching the getWhichTurretForWeaponSlot TU.

typedef bool Bool;
typedef float Real;

enum WhichTurretType
{
	TURRET_INVALID = -1,
	TURRET_PRIMARY = 0
};

struct TurretAI
{
	char m_pad[0x18];
	Real m_angle;
	Real m_pitch;

	Real getTurretAngle() const { return m_angle; }
	Real getTurretPitch() const { return m_pitch; }
};

class AIUpdateInterface
{
	char m_pad[0x20C];
	TurretAI *m_turretAI[1];

public:
	Bool getTurretRotAndPitch(WhichTurretType tur, Real *turretAngle, Real *turretPitch) const;
};

// ?getTurretRotAndPitch@AIUpdateInterface@@QBE_NW4WhichTurretType@@PAM1@Z
Bool AIUpdateInterface::getTurretRotAndPitch(WhichTurretType tur, Real *turretAngle, Real *turretPitch) const
{
	if (m_turretAI[tur])
	{
		if (turretAngle)
		{
			*turretAngle = m_turretAI[tur]->getTurretAngle();
		}
		if (turretPitch)
		{
			*turretPitch = m_turretAI[tur]->getTurretPitch();
		}
		return true;
	}
	return false;
}
