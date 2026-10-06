// cl: /DNDEBUG /MD
//
// ?getWhichTurretForWeaponSlot@AIUpdateInterface@@QBE?AW4WhichTurretType@@W4WeaponSlotType@@PAM1@Z,
// retail 0x0026278A, 94 bytes. Dedicated TU.
// Verbatim BFME2 logic (Code/GameEngine/Source/GameLogic/Object/Update/
// AIUpdate.cpp:784): single-turret scan (MAX_TURRETS is 1 in BFME2, retail
// compares the index against 1) over m_turretAI at +0x20C, filling the angle
// and pitch out-params from TurretAI+0x18/+0x1C. TurretAI::isWeaponSlotOnTurret
// is a direct (non-virtual) call, resolved by pin.

typedef bool Bool;
typedef float Real;

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0,
	WEAPONSLOT_COUNT = 6
};

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
	char m_pad[0x18];
	Real m_angle;
	Real m_pitch;

	Real getTurretAngle() const { return m_angle; }
	Real getTurretPitch() const { return m_pitch; }
	Bool isWeaponSlotOnTurret(WeaponSlotType wslot) const;
};

class AIUpdateInterface
{
	char m_pad[0x20C];
	TurretAI *m_turretAI[MAX_TURRETS];

public:
	WhichTurretType getWhichTurretForWeaponSlot(WeaponSlotType wslot, Real *turretAngle, Real *turretPitch) const;
};

// ?getWhichTurretForWeaponSlot@AIUpdateInterface@@QBE?AW4WhichTurretType@@W4WeaponSlotType@@PAM1@Z
WhichTurretType AIUpdateInterface::getWhichTurretForWeaponSlot(WeaponSlotType wslot, Real *turretAngle, Real *turretPitch) const
{
	for (int i = 0; i < MAX_TURRETS; ++i)
	{
		if (m_turretAI[i] && m_turretAI[i]->isWeaponSlotOnTurret(wslot))
		{
			if (turretAngle)
				*turretAngle = m_turretAI[i]->getTurretAngle();
			if (turretPitch)
				*turretPitch = m_turretAI[i]->getTurretPitch();

			return (WhichTurretType)i;
		}
	}
	return TURRET_INVALID;
}
