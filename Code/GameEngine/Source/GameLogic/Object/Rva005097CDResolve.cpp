// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?friend_postProcessLoad@ProjectileNugget@@QAEXXZ @0x005097CD 71B: resolve helper over base
// Rva00507823 slot 8 plus WeaponStore find by +0x130 name into +0x128 plus
// FX lookup by +0x134 name into +0x12c when non-empty. All callees rowed.

#include "ascii_string.h"


class WeaponTemplate
{
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
};

extern WeaponStore *TheWeaponStore;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

class Rva00507823
{
public:
	virtual ~Rva00507823();
	Rva00507823();
	virtual void rva00507877();

private:
	char m_pad[0x128 - 4];
};

class ProjectileNugget : public Rva00507823
{
public:
	void friend_postProcessLoad();

private:
	const WeaponTemplate *m_128;
	void *m_12C;
	AsciiString m_130;
	AsciiString m_134;
};

void ProjectileNugget::friend_postProcessLoad()
{
	Rva00507823::rva00507877();
	m_128 = TheWeaponStore->findWeaponTemplate(m_130);
	if (!m_134.isEmpty())
		m_12C = ((Rva002D06CA *)TheThingFactory)->rva002D06CA(&m_134);
}
