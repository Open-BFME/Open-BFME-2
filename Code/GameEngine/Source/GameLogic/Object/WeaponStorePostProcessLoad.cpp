// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// WeaponStore::postProcessLoad @0x002CADFA 58B.
// Name: WorldBuilder (Weapon.cpp line 2074, "you must call this after
// TheThingFactory is inited"), a virtual by its vtable pairing. Retail
// bytes: with TheThingFactory set, every non-null template in the vector at
// +0x0C gets its own postProcessLoad (retail 0x002CA942, WB-named
// WeaponTemplate::postProcessLoad; kept under its ledger placeholder name).
// The retail assert is compiled out.
#include <vector>

class Rva002CA9CA
{
public:
	void rva002CA942();
};

class ThingFactory;
extern ThingFactory *TheThingFactory;

class WeaponStore
{
public:
	virtual void postProcessLoad();

private:
	char m_pad04[0x0C - 4];
	_STL::vector<Rva002CA9CA *> m_weaponTemplateVector;	// +0x0C
};

void WeaponStore::postProcessLoad()
{
	if (!TheThingFactory)
		return;
	for (unsigned int i = 0; i < m_weaponTemplateVector.size(); i++)
	{
		Rva002CA9CA *weaponTemplate = m_weaponTemplateVector[i];
		if (weaponTemplate)
			weaponTemplate->rva002CA942();
	}
}
