// cl: /MD
// ?rva005D896F@Rva005D898A@@QAE_NPAVObject@@@Z @0x005D896F 27B.
// Helper over Object::getCurrentWeapon (rowed at 0x0028AEBD) and the rowed
// byte getter at 0x002C9400. Retail takes Object* from [esp+4], calls
// getCurrentWeapon with null slot, reads Weapon+4 as a pointer to the
// byte-field holder, calls its get, then returns !byte via neg al / sbb eax
// eax / inc eax. Its one caller, Rva005D898A::rva005D898A (0x005D898A,
// GapBodiesS3H.cpp), loads ecx with its own this and tests al: a bool member
// of that class that ignores this. No donor.

class Weapon;
enum WeaponSlotType;
#include "../GameLogic/Object/object.h"
class Weapon
{
public:
	char m_pad[4];
	class Rva002C9400ByteField *m_04;
};
#include "../../Include/Common/Rva002C9400ByteField.h"

class Rva005D898A
{
public:
	bool rva005D896F(Object *obj);
};

bool Rva005D898A::rva005D896F(Object *obj)
{
	const Weapon *weapon = obj->getCurrentWeapon((WeaponSlotType *)0);
	unsigned char b = weapon->m_04->get();
	return !b;
}
