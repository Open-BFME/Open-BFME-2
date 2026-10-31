// cl: /MD
//
// ?rva0048B9D0@FireWeaponUpdate@@QAEXPBVWeaponTemplate@@@Z @0x0048B9D0 74B
// FireWeaponUpdate: the sole caller (0x005093C6) fetches the module with
// findModule(nameToKey("FireWeaponUpdate")) and calls this on it (target
// fact). Donor fact: BFME 1's FireWeaponUpdate ctor sets up its m_weapon the
// same way (allocateNewWeapon, source ID, loadAmmoNow). Method name unknown.
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

class AsciiString;
class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
};

extern WeaponStore *TheWeaponStore;

class FireWeaponUpdate
{
public:
	void rva0048B9D0(const WeaponTemplate *tmpl);

private:
	char m_pad00[8]; // +0..+7
	Object *m_owner; // +8
	char m_pad0C[0x14]; // +0xC..+0x1F
	Weapon *m_weapon; // +0x20
};

void FireWeaponUpdate::rva0048B9D0(const WeaponTemplate *weaponTemplate)
{
	if (weaponTemplate == 0)
		return;
	if (m_weapon != 0)
		::delete m_weapon;
	Weapon *weapon = TheWeaponStore->allocateNewWeapon(weaponTemplate, WEAPON_SLOT_PRIMARY);
	m_weapon = weapon;
	weapon->m_ownerID = m_owner->m_id;
	m_weapon->loadAmmoNow(m_owner);
}
