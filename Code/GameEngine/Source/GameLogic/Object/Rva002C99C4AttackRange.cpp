// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?getAttackRange@BfmeRangedWeaponTemplate@@QBEMPBVObject@@ABVWeaponBonus@@PBUCoord3D@@@Z
// @0x002C99C4 55B: ranged attack-range scaler (const thiscall, float return).
// Retail negates pos->z via SSE, forwards (obj, bonus, -z) to the pinned
// 103B sibling at 0x002C995D, then returns pinned-0x002C98E2(obj) times that
// result (x87 fmul of the live call result). Identity: callee of the landed
// BFME1-donor ?getAttackRange@Weapon@@QBEMPBVObject@@@Z (0x002C9BF8) read from
// its REL32; signature matches the existing pin. Minimal real types.

enum ObjectStatusTypes { ObjectStatusType58 = 0x3A };
class Object
{
public:
    bool testStatus(ObjectStatusTypes status) const;
};
class AI
{
public:
    static float getAdjustedVisionRangeForObject(const Object *source, int mode);
};

class WeaponBonus;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class BfmeRangedWeaponTemplate
{
public:
	float rva002C995D(void *a, void *b, float c);
	float rva002C9217(void *bonus, float height);
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

// Retail002C995D..002C99C4 RET12 ST0: nearest matched range wrapper names
// the receiver and pins this exact ABI. BFME1@9cbfb551f WeaponTemplate_
// bfmeRangeBase.cpp supplies the base-range/bonus semantic lead. BFME2's
// target adds the status58/vision-mode3 clamp; all order and scalar rounding
// follow target calls and accesses, without asserting the original core name.
float BfmeRangedWeaponTemplate::rva002C995D(void *source, void *bonus, float height)
{
    float range = rva002C9217(bonus, height);
    float scale = rva002C98E2(source);
    if (scale > 1.0f && static_cast<Object *>(source)->testStatus(ObjectStatusType58))
    {
        float vision = AI::getAdjustedVisionRangeForObject(static_cast<Object *>(source), 3);
        if (range * scale > vision)
            return vision;
    }
    return scale * range;
}
