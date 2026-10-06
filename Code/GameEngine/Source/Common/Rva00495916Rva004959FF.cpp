// cl: /DNDEBUG /MD
//
// Retail 0x004959FF (44 bytes): Rva00495916::rva004959FF, slot 5 of the primary
// vtable 0x00C4ED3C that the matched Rva00495916 dtor (Rva0024A797Derived.cpp)
// installs; the class keeps that row's placeholder name and three-base layout
// (module base with the ModuleData at +4 and the Object at +8, two interfaces).
// Body: set weapon set flag 0 on the Object, then lock the weapon slot named by
// the module data (+0x30 when the +0x3C flag is set, else +0x28) temporarily
// through Object::setWeaponLock 0x00290B24 (two calls in the source; retail
// merges them and pushes the slot per branch).

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};
enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};
enum WeaponLockType
{
	NOT_LOCKED = 0,
	LOCKED_TEMPORARILY = 1,
	LOCKED_PERMANENTLY = 2
};
class Object
{
public:
	void setWeaponSetFlag(WeaponSetType wst);
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
};
class ModuleData;
class Rva0024A797
{
public:
	virtual ~Rva0024A797();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class MiBase1
{
public:
	virtual void f1();
};
class Rva00495916_B2
{
public:
	virtual void f2();
};
class Rva00495916ModuleData
{
public:
	unsigned char m_pad[0x28];
	WeaponSlotType m_28; // +0x28
	unsigned char m_pad2C[0x30 - 0x2C];
	WeaponSlotType m_30; // +0x30
	unsigned char m_pad34[0x3C - 0x34];
	bool m_3C; // +0x3C
};
class Rva00495916 : public Rva0024A797, public MiBase1, public Rva00495916_B2
{
public:
	virtual void rva004959FF();
};
void Rva00495916::rva004959FF()
{
	const Rva00495916ModuleData *data = (const Rva00495916ModuleData *)m_moduleData;
	m_object->setWeaponSetFlag((WeaponSetType)0);
	if (data->m_3C)
		m_object->setWeaponLock(data->m_30, LOCKED_TEMPORARILY);
	else
		m_object->setWeaponLock(data->m_28, LOCKED_TEMPORARILY);
}
