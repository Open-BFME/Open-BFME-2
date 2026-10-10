// cl: /O1 /EHsc /MD /arch:SSE /Ireference/shims/bfme2_ascii
//
// Armor::adjustDamage, retail 0x001D90A1 (538B, thiscall ret 0xC, x87 return).
// Identity: WorldBuilder's debug build names this body Armor::adjustDamage
// (Armor.cpp); the matched callers in ActiveBody.cpp (estimateDamage
// 0x004BDB01 and attemptDamage) call the pinned
// ?adjustDamage@Armor@@QBEMPBVDamageInfoInput@@PBVObject@@_N@Z. Zero Hour's
// ArmorTemplate::adjustDamage is only a semantic lead: BFME 2's Armor keeps the
// armor NAME (looked up through TheArmorStore, rowed 0x001D901B) and scales by
// the damaged object's state.
// Target body: healing (type 7) passes through. The object's armor set (body
// +0x254 slot 14 flags -> ThingTemplate::findArmorTemplateSet) names a second
// armor whose coefficient 27 scales everything; an armor +0x00 bonus applies
// when !flag and the damage source answers the 0x0028F44C query. Type 8 stops
// there; attribute 27 for the damage name (Object 0x0028C149) zeroes the
// damage; then the armor's own coefficient, and (type != 0) attribute 1 capped
// at TheWritableGlobalData +0xAE8, each folded as amount *= 1 - (1 - c) * factor.
// Offsets, slots and constants come from the native body; the coefficient /
// attribute meanings are donor-style readings, not proven.
#include "ascii_string.h"
#include "../../Common/GameLogicObjectLookupView.h"

typedef float Real;
typedef bool Bool;
typedef int Int;
enum DamageType { DAMAGE_TYPE_ZERO = 0 };

template <Int NUMBITS> class BitFlags
{
	unsigned int m_bits;
};
typedef BitFlags<17> ArmorSetFlags;

class DamageInfoInput
{
public:
	unsigned int m_field00;			// +0x00
	ObjectID m_sourceID;			// +0x04
	unsigned int m_field08;			// +0x08
	DamageType m_damageType;		// +0x0C
	unsigned char m_pad10[0x1C - 0x10];
	Real m_amount;				// +0x1C
};

class ArmorTemplate
{
public:
	Real getDamageCoefficient(DamageType type) const { return m_damageCoefficient[type]; }
	Real m_bonus;				// +0x00
	Real m_damageCoefficient[28];		// +0x04
};

class ArmorTemplateSet
{
public:
	unsigned int m_flags;			// +0x00
	AsciiString m_armorName;		// +0x04
};

class Rva001D901B
{
public:
	const ArmorTemplate *rva001D901B(const AsciiString &name) const;
};
class ArmorStore : public Rva001D901B
{
};
extern ArmorStore *TheArmorStore;

class ThingTemplate
{
public:
	const ArmorTemplateSet *findArmorTemplateSet(const ArmorSetFlags &flags) const;
};

class Rva001D90A1Body
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual ArmorSetFlags getArmorSetFlags() const;	// slot 14 (+0x38)
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Rva001D90A1Body *getBody() const { return m_body; }
	Bool rva0028F44C(const Object *other) const;
	// Existing rowed integer carrier ABI; native passes the local name address.
	Bool rva0028C149(Int attribute, Real *value, Int name);
private:
	unsigned char m_pad00[4];
	const ThingTemplate *m_template;	// +0x04
	unsigned char m_pad08[0x254 - 8];
	Rva001D90A1Body *m_body;		// +0x254
};

extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	unsigned char m_pad[0xAE8];
	Real m_attributeDamageCap;		// +0xAE8
};
extern GlobalData *TheWritableGlobalData;

extern const char *TheDamageNames[];

template <class T> inline const T &armorMin(const T &a, const T &b)
{
	return b < a ? b : a;
}

class Armor
{
public:
	Real adjustDamage(const DamageInfoInput *input, const Object *obj, Bool flag) const;
private:
	AsciiString m_name;
};

Real Armor::adjustDamage(const DamageInfoInput *input, const Object *obj, Bool flag) const
{
	DamageType type = input->m_damageType;
	Real amount = input->m_amount;
	if (type == 7)
		return amount;

	Real setScale = 1.0f;
	const ArmorTemplateSet *set = obj->getTemplate()->findArmorTemplateSet(obj->getBody()->getArmorSetFlags());
	if (set)
	{
		const ArmorTemplate *setArmor = TheArmorStore->rva001D901B(set->m_armorName);
		if (setArmor)
			setScale = setArmor->m_damageCoefficient[27];
	}

	Real unused;
	Real bonus = 0.0f;
	const ArmorTemplate *armor = TheArmorStore->rva001D901B(m_name);
	if (armor && !flag)
	{
		ObjectID sourceID = input->m_sourceID;
		if (sourceID && obj->rva0028F44C(TheGameLogic->findObjectByID(sourceID)))
			bonus = armor->m_bonus;
	}
	Real factor = 1.0f - bonus;
	amount *= 1.0f - (1.0f - setScale) * factor;
	if (type != 8)
	{
		Bool immune;
		{
			AsciiString name(TheDamageNames[type]);
			immune = const_cast<Object *>(obj)->rva0028C149(27, &unused, reinterpret_cast<Int>(&name));
		}
		if (immune)
			return 0.0f;

		Real coefficient;
		if (armor)
		{
			const DamageType currentType = input->m_damageType;
			coefficient = armor->getDamageCoefficient(currentType);
		}

		else
			coefficient = 1.0f;
		amount *= 1.0f - (1.0f - coefficient) * factor;
		if (type != 0)
		{
			Real attribute = 0.0f;
			{
				AsciiString name(TheDamageNames[type]);
				const_cast<Object *>(obj)->rva0028C149(1, &attribute, reinterpret_cast<Int>(&name));
			}
			amount *= 1.0f - (1.0f - (1.0f - armorMin(TheWritableGlobalData->m_attributeDamageCap, attribute))) * factor;
		}
	}
	return amount;
}
