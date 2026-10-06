// cl: /MD
// ?Rva005D896FGet@@YGHPAVObject@@@Z @0x005D896F 27B.
// Free stdcall helper over Object::getCurrentWeapon (rowed at 0x0028AEBD)
// and the rowed byte getter at 0x002C9400. Retail takes Object* from
// [esp+4], calls getCurrentWeapon with null slot, reads Weapon+4 as a
// pointer to the byte-field holder, calls its get, then returns !byte via
// neg al / sbb eax eax / inc eax. Caller at 0x005D89B5. No donor.

class Weapon;
enum WeaponSlotType;
class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
};
class Weapon
{
public:
	char m_pad[4];
	class Rva002C9400ByteField *m_04;
};
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};

int __stdcall Rva005D896FGet(Object *obj)
{
	const Weapon *w = obj->getCurrentWeapon((WeaponSlotType *)0);
	unsigned char b = w->m_04->get();
	return !b;
}
