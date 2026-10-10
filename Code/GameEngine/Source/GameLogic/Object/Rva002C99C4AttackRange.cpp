// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?getAttackRange@BfmeRangedWeaponTemplate@@QBEMPBVObject@@ABVWeaponBonus@@PBUCoord3D@@@Z
// @0x002C99C4 55B: ranged attack-range scaler (const thiscall, float return).
// Retail negates pos->z via SSE, forwards (obj, bonus, -z) to the pinned
// 103B sibling at 0x002C995D, then returns pinned-0x002C98E2(obj) times that
// result (x87 fmul of the live call result). Identity: callee of the landed
// BFME1-donor ?getAttackRange@Weapon@@QBEMPBVObject@@@Z (0x002C9BF8) read from
// its REL32; signature matches the existing pin. Minimal real types.

#include <math.h>

enum ObjectStatusTypes { ObjectStatusType58 = 0x3A };
class Object
{
public:
    bool testStatus(ObjectStatusTypes status) const;
    bool rva0028C149(int attribute,float *value,int argument);
};
class AI
{
public:
    static float getAdjustedVisionRangeForObject(const Object *source, int mode);
};

class WeaponBonus;
class GlobalData;
extern GlobalData *TheWritableGlobalData;

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class BfmeRangedWeaponTemplate
{
public:
	float rva002C995D(void *a, void *b, float c);
	float rva002C9217(void *bonus, float height);
	float rva002C98E2(void *a);
	float getAttackRange(Object const *obj, WeaponBonus const &bonus, Coord3D const *pos) const;
private:
	char m_pad00[0x14];
	float m_unmodifiedAttackRange;
	float m_minimumAttackRange;
	float m_dzThreshold;
	float m_dzBase;
	float m_dzScale;
	char m_pad28[0x164 - 0x28];
	float m_absDzLimit;
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

// Target002C9217..002C92B7 RET8: rowed core002C995D calls this bonus/height
// adjustment. WB0x00BB02D0 proves the same computation and accesses.
// BFME1 range-base source supplies purpose only; private field names/layout
// are structural inferences from these retail accesses. math.h float fabs
// preserves the native x87 comparison without an explicit rounding spill.
float BfmeRangedWeaponTemplate::rva002C9217(void *bonus, float dz)
{
	float range = static_cast<const float *>(bonus)[2] * m_unmodifiedAttackRange - 2.5f;
	float negDz = 0.0f - dz;
	if (negDz >= m_dzThreshold) {
		float adjust = m_dzThreshold + dz;
		adjust *= m_dzScale;
		range = m_dzBase - adjust + range;
	}
	if (m_absDzLimit > 0.0f) {
		if (fabs(dz) > m_absDzLimit)
			range = 0.0f;
	}
	if (0.0f > range)
		range = 0.0f;
	return range;
}

// Native2C98E2..2C995D RET4: both range wrappers call this scale.
// Attribute7 modifies the unit multiplier; GlobalData+1224 applies under
// status58. The volatile read of the local fixes the native multiplication
// operand order, without introducing a global or callee alias.
float BfmeRangedWeaponTemplate::rva002C98E2(void *object)

{
    Object *obj=static_cast<Object *>(object);
	float v4 = 1.0f;
	float v8 = 1.0f;
	if (obj->rva0028C149(7, &v8, 0)) {
		v4 = v8 + 1.0f;
	}
	float *mult = (float *)((char *)TheWritableGlobalData + 0x1224);
	if (*mult >= 0.0f) {
		if (obj->testStatus(ObjectStatusType58)) {
			v4 = *(volatile float *)&v4 * *mult;
		}
	}
	return v4;
}
