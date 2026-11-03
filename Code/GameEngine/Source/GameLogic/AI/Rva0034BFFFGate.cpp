// cl: /DNDEBUG /MD
// ?rva0034BFFF@AIChargeTargetState@@AAEXPAVObject@@@Z @0x0034BFFF 51B.
// AIChargeTargetState::update (0x0034FE6E) calls it with the state in ECX;
// the body never reads ECX, so the thiscall member compiles to the same
// ret-4 bytes the earlier stdcall spelling did.
// Weapon-state applier (single object arg): resolves the current
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
#include "../Object/object.h"

class AIChargeTargetState
{
	void rva0034BFFF(Object *o);
};

void AIChargeTargetState::rva0034BFFF(Object *object)
{
	WeaponSlotType st = WEAPONSLOT_0;
	const Weapon *weapon = object->getCurrentWeapon(&st);
	if (weapon == 0)
		return;
	object->setStatus(OBJECT_STATUS_0D, true);
	object->fireCurrentWeapon(reinterpret_cast<const Coord3D *>((char *)object + 0x38));
}
