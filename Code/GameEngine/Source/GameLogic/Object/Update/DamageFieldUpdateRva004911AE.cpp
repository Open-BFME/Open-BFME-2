// cl: /DNDEBUG /MD /GX- /Oy-
//
// ?rva004911AE@DamageFieldUpdate@@QAEXPAVObject@@@Z @0x004911AE 126B: fires
// the Weapon at +0x20 at the Object arg, or when that slot is null walks
// the victim list at +0x24 using TheGameLogic frame at +0x40 and per-entry
// Weapon/status/flag at +0/+4/+8. Same class as the neighbouring
// DamageFieldUpdate dtor 0x0049122C; callees are rowed getStatus 0x002CCFC7
// and Weapon::forceFireWeapon 0x002CE7A4. Caller at 0x004914AA proves a
// thiscall void(Object*) method; honest DamageFieldUpdate naming.
enum WeaponStatus
{
	READY_TO_FIRE,
	OUT_OF_AMMO,
	BETWEEN_FIRING_SHOTS,
	RELOADING_CLIP,
	PRE_ATTACK,
	WEAPON_STATUS_5
};

class Object
{
public:
	char m_pad[0x38];
	struct { float x, y, z; } m_position;
	char m_pad44[0x30];
	int m_id;
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	Object *forceFireWeapon(const Object *source, const Object *target);
};

class GameLogic
{
public:
	char m_pad00[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

struct DamageEntry
{
	Weapon *m_weapon00;
	unsigned int m_frame04;
	unsigned char m_flag08;
};

struct DamageNode
{
	DamageNode *m_next00;
	DamageNode *m_prev04;
	DamageEntry *m_entry08;
};

class FireWeaponUpdate
{
public:
	virtual ~FireWeaponUpdate();

protected:
	char m_pad04[0x08 - 4];
	Object *m_obj08;
	char m_pad0C[0x20 - 0x0C];
	Weapon *m_weapon20;
	DamageNode *m_list24;
	char m_pad28[0x2C - 0x28];
};

class DamageFieldUpdate : public FireWeaponUpdate
{
public:
	DamageFieldUpdate(void *thing, const void *moduleData);
	virtual ~DamageFieldUpdate();

	void rva004911AE(Object *other);
};

void DamageFieldUpdate::rva004911AE(Object *other)
{
	if (other == 0)
		return;
	if (m_weapon20 != 0)
	{
		if (m_weapon20->getStatus() != READY_TO_FIRE)
			return;
		m_weapon20->forceFireWeapon(m_obj08, other);
		return;
	}
	unsigned int frame = TheGameLogic->m_frame;
	for (DamageNode *node = m_list24->m_next00; node != m_list24; node = node->m_next00)
	{
		DamageEntry *entry = node->m_entry08;
		if (frame <= entry->m_frame04)
			continue;
		if (entry->m_weapon00->getStatus() != READY_TO_FIRE)
			continue;
		entry->m_weapon00->forceFireWeapon(m_obj08, other);
		if (entry->m_flag08 == 0)
			continue;
		entry->m_frame04 = (unsigned int)-1;
	}
}
