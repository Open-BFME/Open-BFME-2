// cl: /MD
//
// ?rva0048B9D0@Rva0048B9D0@@QAEXPBVWeaponTemplate@@@Z @0x0048B9D0 74B
// Replaces the Weapon at +0x20: deletes the old via virtual dtor plus global
// delete, allocates a new one from TheWeaponStore with slot 0, copies the
// owner ID from owner+0x74 into weapon+8, then loads ammo from the owner.
// Evidence: packet disassembly order and offsets, callees rowed
// (allocateNewWeapon 0x0028AA81, loadAmmoNow 0x002CE1AC, delete 0x0002FD60),
// caller 0x005093C6, TheWeaponStore extern in use.

class WeaponTemplate;
class Object;
class Weapon;
enum WeaponSlotType
{
	WEAPON_SLOT_PRIMARY = 0
};

class Object
{
public:
	char m_pad00[0x74];
	int m_id; // +0x74
};

class Weapon
{
public:
	virtual ~Weapon();
	void loadAmmoNow(const Object *source);

	const void *m_template; // +4
	int m_ownerID; // +8
};

class WeaponStore
{
public:
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType wslot) const;
};

extern WeaponStore *TheWeaponStore;

class Rva0048B9D0
{
public:
	void rva0048B9D0(const WeaponTemplate *tmpl);

private:
	char m_pad00[8]; // +0..+7
	Object *m_owner; // +8
	char m_pad0C[0x14]; // +0xC..+0x1F
	Weapon *m_weapon; // +0x20
};

void Rva0048B9D0::rva0048B9D0(const WeaponTemplate *tmpl)
{
	if (tmpl == 0)
		return;
	if (m_weapon != 0)
		::delete m_weapon;
	Weapon *w = TheWeaponStore->allocateNewWeapon(tmpl, WEAPON_SLOT_PRIMARY);
	m_weapon = w;
	w->m_ownerID = m_owner->m_id;
	m_weapon->loadAmmoNow(m_owner);
}
