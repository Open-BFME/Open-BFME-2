// cl: /O1 /DNDEBUG /MD /GX /arch:SSE
//
// ??0WeaponFireSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z,
// retail 0x00492708, 170 bytes. Behavior-side ctor completing the
// WeaponFireSpecialAbilityUpdate file-unit (behavior instance factory
// rowed at 0x24DB1B news 0x8C with this pinned 2-arg ctor as its sole
// caller; poolkey rowed at 0x492685; name getter rowed at 0x4925D5;
// ModuleData proc 0x24DB00 plus ModuleData factory 0x24DB56 plus
// ModuleData ctor 0x4926CA all rowed).
//
// Shape follows the FireWeaponCollide behavior ctor over a pinned opaque
// Rva0044EF5E intermediate base (0x44EF5E, thing plus data): copy the
// module-data weapon name at +0xC8 into a stack AsciiString (rowed copy
// at 0x365F0), look it up through TheWeaponStore (rowed findWeaponTemplate
// at 0x2CB8BF over the TU-local extern, DIR32 slot patches from retail,
// no pin), allocate it on a hit (pinned allocateNewWeapon at 0x28AA81),
// arm it through the opaque weapon method at 0x2CE1AC (fresh Rva pin,
// do-not-name), then explicitly destroy the temp (rowed AsciiString fold
// at 0x36410). The primary vtable slot plus the +0x0C/+0x10/+0x20
// secondary slots re-store through pointer casts (Defector precedent:
// no virtuals declared, so the stores land in body order with identical
// mov bytes). /GX for the EH prologue plus the three state stores
// (and-early for the base, byte-mid for the temp, byte-late reset around
// the explicit destruction); the declared-only base dtor arms them with
// no emitted code. Row supersedes the ctor pin.

class Thing;
class ModuleData;
class Object;
class WeaponTemplate;
class Weapon;

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
	Weapon *allocateNewWeapon(const WeaponTemplate *weaponTemplate, WeaponSlotType slot) const;
};

extern WeaponStore *TheWeaponStore;

class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	~Rva0044EF5E();

protected:
	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x88 - 0x0C];
};

class WeaponFireModuleData
{
public:
	unsigned char m_pad[0xC8];
	AsciiString m_weaponName;
};

class WeaponFireSpecialAbilityUpdate : public Rva0044EF5E
{
public:
	WeaponFireSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData);

private:
	const WeaponFireModuleData *getWeaponFireModuleData() const
	{
		return reinterpret_cast<const WeaponFireModuleData *>(m_moduleData);
	}

	Weapon *m_weapon;
};

// ?Rva002CE1AC@Weapon@@QAEXPAVObject@@@Z @0x002CE1AC
class Weapon
{
public:
	void Rva002CE1AC(Object *object);

	unsigned char m_pad[8];
	unsigned int m_status;
};

// ??0WeaponFireSpecialAbilityUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x492708
WeaponFireSpecialAbilityUpdate::WeaponFireSpecialAbilityUpdate(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	*(const void **)this = (const void *)0x00C4E090;
	*(const void **)((char *)this + 0x0C) = (const void *)0x00C4D640;
	*(const void **)((char *)this + 0x10) = (const void *)0x00C4E080;
	*(const void **)((char *)this + 0x20) = (const void *)0x00C4E05C;
	m_weapon = 0;
	AsciiString weaponName(getWeaponFireModuleData()->m_weaponName);
	const WeaponTemplate *templ = TheWeaponStore->findWeaponTemplate(weaponName);
	if (templ != 0)
	{
		m_weapon = TheWeaponStore->allocateNewWeapon(templ, PRIMARY_WEAPON);
		m_weapon->m_status = 0;
		m_weapon->Rva002CE1AC(m_object);
	}
}
