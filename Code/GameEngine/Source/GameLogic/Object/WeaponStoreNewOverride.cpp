// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?newOverride@WeaponStore@@QAEPAVWeaponTemplate@@PAV2@@Z, retail 0x002CE063
// (159 bytes).
// Identity (target): WorldBuilder's debug Weapon.cpp:1996
// WeaponStore::newOverride calls operator new, the WeaponTemplate
// constructor (0x002CD169) and copy assignment (0x002CD67C), then the
// template vector's erase and push_back, as retail does.
// Donor (BFME 1 / Zero Hour WeaponStore::newOverride): a new template copied
// from the given one, chained to it as its next template (+0x04). BFME 2
// deltas (target): no override of an override (flag +0x160, set on the new
// one), and the store's template vector (+0x0C) swaps the entry with the
// same name key (+0x0C) for the new template. The 0x180-byte allocation
// and its constructor stand for newInstance(WeaponTemplate).
#include <vector>

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class WeaponTemplate
{
public:
	WeaponTemplate();
	WeaponTemplate &operator=(const WeaponTemplate &that);

	NameKeyType getNameKey() const { return m_nameKey; }
	bool isOverride() const { return m_isOverride; }
	void friend_setNextTemplate(WeaponTemplate *next) { m_nextTemplate = next; }
	void friend_setIsOverride() { m_isOverride = true; }

private:
	unsigned char m_pad000[0x04];
	WeaponTemplate *m_nextTemplate; // +0x04
	unsigned char m_pad008[0x0C - 0x08];
	NameKeyType m_nameKey; // +0x0C
	unsigned char m_pad010[0x160 - 0x10];
	bool m_isOverride; // +0x160
	unsigned char m_pad161[0x180 - 0x161];
};

typedef _STL::vector<WeaponTemplate *, _STL::allocator<WeaponTemplate *> > WeaponTemplateVector;

class WeaponStore
{
public:
	WeaponTemplate *newOverride(WeaponTemplate *weaponTemplate);

protected:
    WeaponTemplate *findWeaponTemplatePrivate(NameKeyType key) const;

private:
	unsigned char m_pad00[0x0C];
	WeaponTemplateVector m_weaponTemplateVector; // +0x0C
};

WeaponTemplate *WeaponStore::newOverride(WeaponTemplate *weaponTemplate)
{
	if (weaponTemplate == 0)
		return 0;
	if (weaponTemplate->isOverride())
		return 0;

	WeaponTemplate *wt = new WeaponTemplate;
	*wt = *weaponTemplate;
	wt->friend_setNextTemplate(weaponTemplate);
	wt->friend_setIsOverride();

	NameKeyType key = wt->getNameKey();
	for (WeaponTemplateVector::iterator it = m_weaponTemplateVector.begin(); it != m_weaponTemplateVector.end(); ++it)
	{
		if ((*it)->getNameKey() == key)
		{
			m_weaponTemplateVector.erase(it);
			break;
		}
	}
	m_weaponTemplateVector.push_back(wt);
	return wt;
}

// Target: retail 0x002CADBE is the complete 60-byte key search; the mapped
// WorldBuilder Weapon.cpp body indexes the vector at +0x0C and compares the
// template key at +0x0C. WeaponStore callers establish the receiver and role.
// Name, protected access and mutable return follow Zero Hour Weapon.h/source.
// Keep the genuine STLport size/index operations: a hand-written pointer range
// hoists the count and differs from retail's loop-bottom recomputation.
WeaponTemplate *WeaponStore::findWeaponTemplatePrivate(NameKeyType key) const
{
    for (int i = 0; i < m_weaponTemplateVector.size(); ++i)
        if (m_weaponTemplateVector[i]->getNameKey() == key)
            return m_weaponTemplateVector[i];
    return 0;
}
