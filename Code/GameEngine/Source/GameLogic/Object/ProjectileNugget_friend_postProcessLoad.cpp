// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?friend_postProcessLoad@ProjectileNugget@@UAEXXZ @0x005097CD 71B: resolve helper over base
// Rva00507823 slot 8 plus WeaponStore find by +0x130 name into +0x128 plus
// FX lookup by +0x134 name into +0x12c when non-empty. All callees rowed.
// A virtual: it overrides that slot 8 in vtable 0x00C646B0 (installed at
// 0x00509CC3), as its WB twin is slot 8 of WB table 0x01EC39D8.

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

class ThingTemplate;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &key);
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
	virtual void friend_postProcessLoad();

private:
	const WeaponTemplate *m_detonationWeapon; // +0x128
	const ThingTemplate *m_projectileTemplate; // +0x12C
	AsciiString m_warheadTemplateName; // +0x130
	AsciiString m_projectileTemplateName; // +0x134
};

void ProjectileNugget::friend_postProcessLoad()
{
	Rva00507823::rva00507877();
	m_detonationWeapon = TheWeaponStore->findWeaponTemplate(m_warheadTemplateName);
	if (!m_projectileTemplateName.isEmpty())
		m_projectileTemplate = TheThingFactory->findTemplate(m_projectileTemplateName);
}
