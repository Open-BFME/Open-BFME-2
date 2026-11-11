// BfmeRangedWeaponTemplate: canonical declarations for the members 3 units call through private views of it;
// each call resolves to the unit's ledger row or pin, and no unit reads its layout, which stays opaque.
#ifndef CANONICAL_BFMERANGEDWEAPONTEMPLATE_H
#define CANONICAL_BFMERANGEDWEAPONTEMPLATE_H

struct Coord3D;
class Object;
struct Rva002C92B8Record;
class WeaponBonus;

class BfmeRangedWeaponTemplate
{
public:
	float getAttackRange(const Object *source, const WeaponBonus &bonus, const Coord3D *sourcePos) const;
	float rva002C9217(void *arg, float value);
	float rva002C92B8(void *arg, const Rva002C92B8Record *from, const Rva002C92B8Record *to);
	float rva002C92DC(void *arg, const Rva002C92B8Record *rec);
	float rva002C995D(void *a, void *arr, float b);
};

#endif // CANONICAL_BFMERANGEDWEAPONTEMPLATE_H
