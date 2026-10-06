// cl: /DNDEBUG /MD
// Built from the banked attempt reverse/attempts/0x00545239.cpp; fix: the
// scale is the compiler literal 1.15f (retail __real@3f933333 at 0x007FC15C),
// not a global, which is what keeps retail's load-local-then-mulss order.
// Rva00545239Get @0x00545239 84B. Free float getter: base rate from
// TheAI 0x009FF0F8 (+0x18 +0xC8) scaled by 1.15f when the object's
// current weapon (rowed getCurrentWeapon 0x0028AEBD twice with slot 0) has its
// +4 ByteField set (rowed get 0x002C9400). Evidence: two getCurrentWeapon calls
// with test-je, ByteField test-je, mulss plus fld return, callers 0x0054544F
// 0x005459D6, neighbours ModuleNameGetters3 and ConstIntGetters4.
class Weapon;
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
};
class Rva002C9400ByteField
{
public:
	unsigned char get() const;
};
struct AIInner
{
	char m_pad[0xC8];
	float m_rate;
};
struct AIMid
{
	char m_pad[0x18];
	AIInner *m_ptr;
};
// ?TheAI@@3PAUAIMid@@A: the global at this VA is ?TheAI@@3PAVAI@@A; this name is an alias for it.
extern AIMid * TheAI;
#pragma comment(linker, "/alternatename:?TheAI@@3PAUAIMid@@A=?TheAI@@3PAVAI@@A")

float __cdecl Rva00545239Get(void *objPtr)
{
	Object *obj = (Object *)objPtr;
	float val = TheAI->m_ptr->m_rate;
	const Weapon *w = obj->getCurrentWeapon((WeaponSlotType *)0);
	if (w) {
		const Weapon *w2 = obj->getCurrentWeapon((WeaponSlotType *)0);
		Rva002C9400ByteField *field = *(Rva002C9400ByteField **)((char *)w2 + 4);
		if (field->get())
			val *= 1.15f;
	}
	return val;
}
