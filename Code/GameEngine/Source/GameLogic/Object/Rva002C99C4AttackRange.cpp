// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?getAttackRange@BfmeRangedWeaponTemplate@@QBEMPBVObject@@ABVWeaponBonus@@PBUCoord3D@@@Z
// @0x002C99C4 55B: ranged attack-range scaler (const thiscall, float return).
// Retail negates pos->z via SSE, forwards (obj, bonus, -z) to the pinned
// 103B sibling at 0x002C995D, then returns pinned-0x002C98E2(obj) times that
// result (x87 fmul of the live call result). Identity: callee of the landed
// BFME1-donor ?getAttackRange@Weapon@@QBEMPBVObject@@@Z (0x002C9BF8) read from
// its REL32; signature matches the existing pin. Minimal real types.

class Object;

class WeaponBonus;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class BfmeRangedWeaponTemplate
{
public:
	float rva002C995D(void *a, void *b, float c);
	float rva002C98E2(void *a);
	float getAttackRange(Object const *obj, WeaponBonus const &bonus, Coord3D const *pos) const;
};

// ?getAttackRange@BfmeRangedWeaponTemplate@@QBEMPBVObject@@ABVWeaponBonus@@PBUCoord3D@@@Z
float BfmeRangedWeaponTemplate::getAttackRange(
	Object const *obj, WeaponBonus const &bonus, Coord3D const *pos) const
{
	float f = ((BfmeRangedWeaponTemplate *)this)->rva002C995D((void *)obj, (void *)&bonus, -pos->z);
	return ((BfmeRangedWeaponTemplate *)this)->rva002C98E2((void *)obj) * f;
}
