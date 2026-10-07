// ?newOverride@WeaponStore@@QAEPAVWeaponTemplate@@PAV2@@Z
// partial score=0.93 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /EHsc
// stlport
// ?newOverride@WeaponStore@@QAEPAVWeaponTemplate@@PAV2@@Z @0x002CE063 159B.
// Identity from Weapon.cpp's WeaponStore::newOverride donor and the
// INI::parseWeaponTemplateDefinition caller at 0x002CE153. Retail additionally
// rejects chained overrides and replaces matching template entries.
#include <vector>

class WeaponTemplate
{
	unsigned char m_pad00[4];
	WeaponTemplate *m_nextTemplate;
	unsigned char m_pad08[4];
	void *m_0c;
	unsigned char m_pad10[0x150];
	unsigned char m_overrideFlag;
	unsigned char m_pad161[0x1f];

public:
	WeaponTemplate();
	WeaponTemplate &operator=(const WeaponTemplate &);
	void setNextTemplate(WeaponTemplate *next) { m_nextTemplate = next; }
	bool hasOverride() const { return m_overrideFlag != 0; }
	void setOverrideFlag() { m_overrideFlag = 1; }
	void *key() const { return m_0c; }
};

struct Rva004DFCB0Element
{
	WeaponTemplate *m_template;
	Rva004DFCB0Element(WeaponTemplate *value) : m_template(value) {}
};

class WeaponStore
{
	unsigned char m_pad00[0x0c];
	_STL::vector<Rva004DFCB0Element> m_overrides;

public:
	WeaponTemplate *newOverride(WeaponTemplate *weaponTemplate);
};

WeaponTemplate *WeaponStore::newOverride(WeaponTemplate *weaponTemplate)
{
	if (weaponTemplate == 0)
		return 0;
	if (weaponTemplate->hasOverride())
		return 0;

	WeaponTemplate *copy = new WeaponTemplate;
	*copy = *weaponTemplate;
	copy->setNextTemplate(weaponTemplate);
	copy->setOverrideFlag();

	for (Rva004DFCB0Element *it = m_overrides.begin(); it != m_overrides.end(); ++it)
	{
		if (it->m_template->key() == copy->key())
		{
			m_overrides.erase(it);
			break;
		}
	}

	m_overrides.push_back(copy);
	return copy;
}
