// cl: /O1
//
// Two Object wrappers over the rowed WeaponSet slot searches (retail
// 0x0028AEEA/11 + 0x0028AEF5/54). The Object holds its WeaponSet at +0x330
// (its +0x8 array is the +0x338 weapon array). The 11B wrapper tail-jumps;
// the 54B wrapper stores the found slot's +0xE4 field plus its remaining
// ammo (rowed Weapon::getRemainingAmmo) through two out-params.

struct RvaWeaponSlotState
{
	char m_pad0[0xE4];				// +0x000..+0x0E4 unknown
	void *m_fieldE4;				// +0x0E4
	char m_pad1[0x132 - 0xE8];		// +0x0E8..+0x132 unknown
	bool m_flag132;					// +0x132
	bool m_flag133;					// +0x133
};

struct RvaWeaponSlot
{
	char m_pad[4];					// +0x000..+0x004 unknown
	RvaWeaponSlotState *m_state;	// +0x004
};

class WeaponSet
{
	char m_pad[8];					// +0x000..+0x008 unknown
	RvaWeaponSlot *m_slots[6];		// +0x008

public:
	RvaWeaponSlot *rva002C73F7() const;
	RvaWeaponSlot *rva002C741C() const;
};

class Weapon
{
public:
	unsigned getRemainingAmmo(bool flag) const;
};

class Object
{
	char m_pad0[0x330];				// +0x000..+0x330 unknown
	WeaponSet m_weaponSet;			// +0x330

public:
	RvaWeaponSlot *rva0028AEEA() const;
	bool rva0028AEF5(void **outPtr, unsigned *outAmmo) const;
};

// ?rva0028AEEA@Object@@QBEPAURvaWeaponSlot@@XZ
RvaWeaponSlot *Object::rva0028AEEA() const
{
	return m_weaponSet.rva002C741C();
}

// ?rva0028AEF5@Object@@QBE_NPAPAXPAI@Z present-unmatched
bool Object::rva0028AEF5(void **outPtr, unsigned *outAmmo) const
{
	RvaWeaponSlot *slot = m_weaponSet.rva002C73F7();
	if (slot != 0)
	{
		*outPtr = slot->m_state->m_fieldE4;
		*outAmmo = ((const Weapon *)slot)->getRemainingAmmo(true);
		return true;
	}
	return false;
}
