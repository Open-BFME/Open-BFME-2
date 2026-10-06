// cl: /MD
// ?rva00542BE2@Rva00542BE2@@QAE_NPBVObject@@@Z @0x00542BE2 55B
// Evidence: chain packet; callees rowed getCurrentWeapon 0x0028AEBD and isWithinAttackRange 0x002CB933; owner at +0xc and single Object arg feed isWithinAttackRange with 0.0f and 1; no caller or vtable so honest address name.
class Object;
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
class Weapon
{
public:
	bool isWithinAttackRange(const Object *source, const Object *target, float extra, int flag) const;
};
class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
};
class Rva00542BE2
{
public:
	bool rva00542BE2(const Object *target);
	char m_pad[0xc];
	Object *m_owner;
};
bool Rva00542BE2::rva00542BE2(const Object *target)
{
	if (m_owner->getCurrentWeapon((WeaponSlotType *)0) == 0)
		return true;
	return m_owner->getCurrentWeapon((WeaponSlotType *)0)->isWithinAttackRange(m_owner, target, 0.0f, 1);
}
