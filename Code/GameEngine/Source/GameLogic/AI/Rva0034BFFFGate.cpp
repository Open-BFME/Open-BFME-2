// cl: /O1 /DNDEBUG /MD
// ?rva0034BFFF@@YGXPAVObject@@@Z @0x0034BFFF 51B.
// Stdcall weapon-state applier (single object arg): resolves the current
// weapon through rowed getCurrentWeapon and, when present, applies the
// rowed setStatus 0xD/1 pair plus the pinned 0x291916 hook on the +0x38
// member. The slot temp zeroes via and (not mov).
enum WeaponSlotType
{
	WEAPONSLOT_0 = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_0D = 0xD
};

class Weapon;
class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	void setStatus(ObjectStatusTypes status, int value);
	void rva00291916(void *arg);
};

void __stdcall rva0034BFFF(Object *o)
{
	WeaponSlotType st = WEAPONSLOT_0;
	const Weapon *w = o->getCurrentWeapon(&st);
	if (w == 0)
		return;
	o->setStatus(OBJECT_STATUS_0D, 1);
	o->rva00291916((void *)((char *)o + 0x38));
}
