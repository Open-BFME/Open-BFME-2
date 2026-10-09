// cl: /MD
// ?usingMeleeAttack@HordeContain@@QAEEXZ 0x004695DA 40B (WB 0x010BF5C0 HordeContain::usingMeleeAttack: the same template flag 0x77 test, getCurrentWeapon and weapon-template byte; its assert reads getObject()) evidence: flag 0x80 at obj+4 +0x116 then current weapon null gives 1 else tail byte get callers 0x47200F 0x472247 0x47233E
enum WeaponSlotType
{
	SLOT_0 = 0
};
class Weapon;
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
struct FlagHolder
{
	unsigned char m_pad[0x116];
	unsigned char m_flags;
};
class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	char m_pad00[4];
	FlagHolder *m_04;
};
class Weapon
{
public:
	char m_pad04[4];
	Rva002C9400ByteField *m_field04;
};
class HordeContain
{
public:
	unsigned char usingMeleeAttack();
	char m_pad[8];
	Object *m_08;
};
unsigned char HordeContain::usingMeleeAttack()
{
	Object *obj = m_08;
	if ((obj->m_04->m_flags & 0x80) != 0) {
		const Weapon *weapon = obj->getCurrentWeapon(0);
		if (weapon != 0)
			return weapon->m_field04->get();
		return 1;
	}
	return 0;
}
