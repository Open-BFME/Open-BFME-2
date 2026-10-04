// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?validateArmorAndDamageFX@ActiveBody@@QBEXXZ, retail 0x004BE1AE (156B).
// Zero Hour ActiveBody::validateArmorAndDamageFX: look up the template's armor
// set for the current armor-set flags and, when it differs from the cached
// one, refresh the cached armor and damage FX.
// BFME 2 differences (target evidence): an ArmorTemplateSet names its armor
// (AsciiString at set +0x04) instead of pointing at an ArmorTemplate, so the
// "has an armor" test is that name's out-of-line StringBase<char>::isEmpty
// (0x00001E2F), TheArmorStore's makeArmor (0x001D9001) builds the Armor from
// the name, and Armor is the one-string object whose assignment is the
// AsciiString set (0x000366F0) and whose clear assigns
// AsciiString::TheEmptyString. The lookup is the ThingTemplate armor-set
// finder 0x0033DCB8 (its own callers include this body; rowed under an
// address name). Members: armor-set flags +0xF0, armor set +0xF4, armor
// +0xF8, damage FX +0xFC (mutable: the method is const). The template is
// Thing +0x04 of the module's Object (+0x08).

#include "ascii_string.h"

template <int NUMBITS> class BitFlags
{
	unsigned int m_bits[(NUMBITS + 31) / 32];
};
typedef BitFlags<17> ArmorSetFlags;

class DamageFX;

class ArmorTemplateSet
{
public:
	const AsciiString &getArmorTemplateName() const { return m_armorName; }
	const DamageFX *getDamageFX() const { return m_fx; }

private:
	ArmorSetFlags m_types;		// +0x00
	AsciiString m_armorName;	// +0x04
	const DamageFX *m_fx;		// +0x08
};

class Armor
{
public:
	void clear() { m_templateName = AsciiString::TheEmptyString; }

private:
	AsciiString m_templateName;
};

class ArmorStore
{
public:
	Armor makeArmor(const AsciiString &name) const;	// 0x001D9001
};
extern ArmorStore *TheArmorStore;

class ThingTemplate
{
public:
	const ArmorTemplateSet *findArmorTemplateSet(const ArmorSetFlags &t) const;	// 0x0033DCB8
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }

private:
	void *m_vptr;
	const ThingTemplate *m_template;	// +0x04
};

class ActiveBody
{
public:
	void validateArmorAndDamageFX() const;

private:
	const Object *getObject() const { return m_object; }

	void *m_vptr;					// +0x00
	void *m_moduleData;				// +0x04
	const Object *m_object;				// +0x08
	char m_pad0C[0xF0 - 0x0C];
	ArmorSetFlags m_curArmorSetFlags;		// +0xF0
	mutable const ArmorTemplateSet *m_curArmorSet;	// +0xF4
	mutable Armor m_curArmor;			// +0xF8
	mutable const DamageFX *m_curDamageFX;		// +0xFC
};

void ActiveBody::validateArmorAndDamageFX() const
{
	const ArmorTemplateSet *set = getObject()->getTemplate()->findArmorTemplateSet(m_curArmorSetFlags);
	if (set && set != m_curArmorSet)
	{
		const AsciiString &armorName = set->getArmorTemplateName();
		if (!((const StringBase<char> &)armorName).isEmpty())
		{
			m_curArmor = TheArmorStore->makeArmor(armorName);
		}
		else
		{
			m_curArmor.clear();
		}
		m_curDamageFX = set->getDamageFX();
		m_curArmorSet = set;
	}
}
