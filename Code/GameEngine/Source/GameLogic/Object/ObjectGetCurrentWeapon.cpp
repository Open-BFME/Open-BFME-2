// cl: /O1 /DNDEBUG /MD
//
// Object::getCurrentWeapon, retail 0x0028AEBD, 45 bytes.
// Dedicated TU so Object.cpp cannot see this body.
// If the weapon-set flag at +0x358 is clear, return null; otherwise
// optionally write the slot at +0x350 and index the array at +0x338.

class Weapon;

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

class Object
{
	char pad_0[0x338];
	Weapon *m_weapon[6];
	int m_currentWeapon;
	int unused354;
	int m_weaponSetPresent;

public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
};

const Weapon *Object::getCurrentWeapon(WeaponSlotType *slot) const
{
	if (m_weaponSetPresent == 0)
		return 0;
	if (slot)
		*slot = (WeaponSlotType)m_currentWeapon;
	return m_weapon[m_currentWeapon];
}
