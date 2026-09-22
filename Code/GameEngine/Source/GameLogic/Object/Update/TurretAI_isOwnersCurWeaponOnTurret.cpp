// cl: /O1 /DNDEBUG /MD
//
// ?isOwnersCurWeaponOnTurret@TurretAI@@QBE_NXZ,
// retail 0x004D8762, 47 bytes. Dedicated TU.
// Verbatim BFME1 logic (Code/GameEngine/Source/GameLogic/AI/TurretAI.cpp:677):
// the owner's current weapon slot must be on this turret. BFME2 layout has
// the owner Object* at +0x10 (data at +8, turret index at +0xC, state machine
// at +0x14). Both callees are already rowed, so they resolve with no pins.

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

class Weapon
{
};

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
};

class TurretAI
{
	char m_pad[8];
	void *m_data;
	int m_whichTurret;
	Object *m_owner;

public:
	bool isOwnersCurWeaponOnTurret() const;
	bool isWeaponSlotOnTurret(WeaponSlotType wslot) const;
};

// ?isOwnersCurWeaponOnTurret@TurretAI@@QBE_NXZ
bool TurretAI::isOwnersCurWeaponOnTurret() const
{
	WeaponSlotType wslot;
	const Weapon *currentWeapon = m_owner->getCurrentWeapon(&wslot);
	return currentWeapon != 0 && isWeaponSlotOnTurret(wslot);
}
