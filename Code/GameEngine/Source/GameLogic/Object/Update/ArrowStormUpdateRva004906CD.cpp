// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE
// Retail 0x004906CD (RVA 0x004906CD) size 213: ArrowStorm range check then SpecialAbility base.
// Evidence: vtable slot 39 of 0x0084D5A0 (ArrowStormUpdateModuleData class); calls pinned SpecialAbilityUpdate 0x0044EDA6, rowed WeaponStore find 0x002CB8BF, WeaponTemplate min 0x002C92FA, Object dist 0x002C97E8, BfmeRanged getAttackRange pin 0x002C99C4; TheWeaponStore +0xDFEFDC; ModuleData AsciiString +0xC8 via this-0x1C; Object via this-0x18.
// Shape follows WeaponFireSpecialAbilityUpdateSlot8.cpp (same slot-8 override pattern over UpdateModule+0x04/+0x08 via second base at +0x20, same bit 0x108&4, same dist<min*min then optional range check): ArrowStorm looks up WeaponTemplate from ModuleData and uses default bonus, no -2.5.
#include "ascii_string.h"

typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

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

class WeaponTemplate
{
public:
	Real getMinimumAttackRange() const;
};

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

class BfmeRangedWeaponTemplate : public WeaponTemplate
{
public:
	Real getAttackRange(const Object *obj, const WeaponBonus &bonus, const Coord3D *pos) const;
};

class WeaponStore;
extern WeaponStore *TheWeaponStore;

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
};

class SpecialAbilityUpdate
{
public:
	virtual Bool rva0044EDA6(int v);
};

class Rva004906CD : public SpecialAbilityUpdate
{
public:
	Bool rva004906CD(const Coord3D *pos);
};

Bool Rva004906CD::rva004906CD(const Coord3D *pos)
{
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
		return SpecialAbilityUpdate::rva0044EDA6(0);
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
	return SpecialAbilityUpdate::rva0044EDA6((int)pos);
}
