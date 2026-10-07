// cl: /DNDEBUG /MD
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

struct Coord3D;
class Weapon;
class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	void setStatus(ObjectStatusTypes status, bool value);
	// Native 0x00291916, the verified position overload in ObjectFireCurrentWeapon.cpp.
	void fireCurrentWeapon(const Coord3D *position);
};

void __stdcall rva0034BFFF(Object *o)
{
	WeaponSlotType st = WEAPONSLOT_0;
	const Weapon *w = o->getCurrentWeapon(&st);
	if (w == 0)
		return;
	o->setStatus(OBJECT_STATUS_0D, true);
	o->fireCurrentWeapon(reinterpret_cast<const Coord3D *>((char *)o + 0x38));
}
