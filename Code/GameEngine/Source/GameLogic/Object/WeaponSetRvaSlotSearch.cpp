// cl: /O1
//
// Two WeaponSet slot-search leaves (retail 0x002C73F7/37 + 0x002C741C/43).
// Both scan the six slots at +0x8 for the first entry whose state link at
// +0x4 carries the wanted flag byte (+0x133 forward, +0x132 reverse) and
// return the slot or null. /O1 selects the retail size idioms: xor-before-add
// init order, push-5/pop-reg small immediates, and the indexed reload on the
// reverse find's return (the check itself walks a lea cursor).

struct RvaWeaponSlotState
{
	char m_pad[0x132];				// +0x000..+0x132 unknown
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

// ?rva002C73F7@WeaponSet@@QBEPAURvaWeaponSlot@@XZ
RvaWeaponSlot *WeaponSet::rva002C73F7() const
{
	int i = 0;
	RvaWeaponSlot **pp = (RvaWeaponSlot **)((char *)this + 8);
	for (; i < 6; i++, pp++)
	{
		RvaWeaponSlot *slot = *pp;
		if (slot != 0 && slot->m_state->m_flag133)
			return slot;
	}
	return 0;
}

// ?rva002C741C@WeaponSet@@QBEPAURvaWeaponSlot@@XZ
RvaWeaponSlot *WeaponSet::rva002C741C() const
{
	int i = 5;
	RvaWeaponSlot **pp = (RvaWeaponSlot **)((char *)this + 0x1C);
	for (; i >= 0; i--, pp--)
	{
		RvaWeaponSlot *slot = *pp;
		if (slot != 0 && slot->m_state->m_flag132)
			return m_slots[i];
	}
	return 0;
}
