// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// WeaponStore::postProcessLoad @0x002CADFA 58B.
// Name: WorldBuilder (Weapon.cpp line 2074, "you must call this after
// TheThingFactory is inited"), a virtual by its vtable pairing. Retail
// bytes: with TheThingFactory set, every non-null template in the vector at
// +0x0C gets its own postProcessLoad (retail 0x002CA942, WB-named
// WeaponTemplate::postProcessLoad; rowed on its address-named class view).
// The retail assert is compiled out.
#include <vector>

class WeaponBonus;
class Weapon;
class Rva001E11F8;
struct ListNode;
class Rva002CA9CA
{
private:
	friend class Weapon;
public:
	bool rva002CA9CA(int damageType, const void *weapon);
	void rva002CAA9D(int a1, const void *a2, const void *a3, const WeaponBonus &bonus);
	bool rva002CAA59(int source, const void *weapon);
	void postProcessLoad();
	void rva002CA970(int firingWeapon, int source, const void *weapon, int position);
	float getProjectileNuggetRadiusIfAlliesAffected(const void *arg);
	bool rva002CAD8B();
	void rva002CAC6E(int a, int context);
	bool getAutoReloadsClip() const { return m_128 == 0; }
	float getReal168() const { return m_168; }
	char m_pad00[0x58];
private:
	int m_58; // +0x58
	char m_pad5C[0x48];
	Rva001E11F8 *m_a4; // +0xA4
	Rva001E11F8 *m_a8; // +0xA8
	Rva001E11F8 *m_ac; // +0xAC
	Rva001E11F8 *m_b0; // +0xB0
	char m_padB4[0x4];
	Rva001E11F8 *m_b8; // +0xB8
	Rva001E11F8 *m_bc; // +0xBC
	Rva001E11F8 *m_c0; // +0xC0
	Rva001E11F8 *m_c4; // +0xC4
	char m_padC8[0x48];
	unsigned char m_110; // +0x110
	char m_pad111[0x17];
	int m_128; // +0x128
	char m_pad12C[0x4];
	float m_130; // +0x130
	char m_pad134[0x34];
	unsigned char m_168; // +0x168
	char m_pad169[0x13];
	ListNode *m_17c; // +0x17C
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
			weaponTemplate->postProcessLoad();
	}
}
