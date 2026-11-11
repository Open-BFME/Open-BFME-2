// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// Retail 0x004906CD (RVA 0x004906CD) size 213: ArrowStorm range check then SpecialAbility base.
// Evidence: vtable slot 39 of 0x0084D5A0 (ArrowStormUpdateModuleData class); calls pinned SpecialAbilityUpdate 0x0044EDA6, rowed WeaponStore find 0x002CB8BF, WeaponTemplate min 0x002C92FA, Object dist 0x002C97E8, BfmeRanged getAttackRange pin 0x002C99C4; TheWeaponStore +0xDFEFDC; ModuleData AsciiString +0xC8 via this-0x1C; Object via this-0x18.
// Shape follows WeaponFireSpecialAbilityUpdateSlot8.cpp (same slot-8 override pattern over UpdateModule+0x04/+0x08 via second base at +0x20, same bit 0x108&4, same dist<min*min then optional range check): ArrowStorm looks up WeaponTemplate from ModuleData and uses default bonus, no -2.5.
#include "ascii_string.h"

typedef bool Bool;
typedef float Real;

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

struct Rva004906CDTemplate
{
	unsigned char m_pad000[0x108];
	unsigned char m_108;
};

class Object
{
public:
	Real rva002C97E8(const Coord3D *a, const Coord3D *b) const;
	unsigned char m_pad00[4];
	const Rva004906CDTemplate *m_template;
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos38;
};

#include "../../../../Include/GameLogic/WeaponTemplate.h"

class WeaponBonus
{
public:
	WeaponBonus()
	{
		for (int i = 0; i < 6; ++i)
			m_multiplier[i] = 1.0f;
	}
private:
	Real m_multiplier[6];
};

#include "../../../../Include/Common/BfmeRangedWeaponTemplate.h"

class WeaponStore;
extern WeaponStore *TheWeaponStore;

#include "../../../../Include/GameLogic/WeaponStore.h"

class SpecialAbilityUpdate
{
public:
	virtual Bool vslot08(int v);
};

class ArrowStormUpdate : public SpecialAbilityUpdate
{
public:
	virtual Bool vslot08(int value);
};

// The family's slot 8 spells its parameter int; this body's is a position.
Bool ArrowStormUpdate::vslot08(int value)
{
	const Coord3D *pos = (const Coord3D *)value;
	char *base = (char *)this;
	struct Mod {
		char pad[0xc8];
		AsciiString name;
	};
	Mod *mod = *(Mod **)(base - 0x1c);
	if (mod == 0) {
		return false;
	}
	if (pos == 0) {
		return SpecialAbilityUpdate::vslot08(0);
	}
	Object *obj = *(Object **)(base - 0x18);
	if (obj == 0) {
		return false;
	}
	const WeaponTemplate *wt = TheWeaponStore->findWeaponTemplate(mod->name);
	if (wt == 0) {
		return false;
	}
	Real minR = wt->getMinimumAttackRange();
	if (obj->rva002C97E8(&obj->m_pos38, pos) < minR * minR) {
		return false;
	}
	if (obj->m_template->m_108 & 4) {
		WeaponBonus bonus;
		const BfmeRangedWeaponTemplate *rwt = (const BfmeRangedWeaponTemplate *)wt;
		Real range = rwt->getAttackRange(obj, bonus, &obj->m_pos38);
		if (obj->rva002C97E8(&obj->m_pos38, pos) > range * range) {
			return false;
		}
	}
	return SpecialAbilityUpdate::vslot08((int)pos);
}
