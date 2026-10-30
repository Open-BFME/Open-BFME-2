// cl: /O1 /EHsc /MD /arch:SSE
// ProjectileNugget.cpp -- ProjectileNugget members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function (vtable pairing); retail supplies the bytes. The nugget first
// applies the base nugget test (0x005075D6, rowed under the placeholder
// Rva00508925), then requires its +0x128 detonation weapon (filled from
// WeaponStore::findWeaponTemplate by friend_postProcessLoad 0x005097CD) to
// accept the object through 0x002CAA59, a method on that weapon template
// still rowed under the placeholder Rva002CA9CA.

typedef int Int;
typedef bool Bool;

class Object;
class WeaponTemplate;

class Rva002CA9CA
{
public:
	Bool rva002CAA59(Int arg, const void *obj);		// 0x002CAA59
};

// LINK: 0x005075D6 is rowed as Rva00507823::rva005075D6(const void *, Object *) (Rva005075D6TargetFilter.cpp).
class Rva00507823
{
public:
	unsigned char rva005075D6(const void *obj, Object *arg);		// 0x005075D6
};

class ProjectileNugget : public Rva00507823
{
public:
	Bool canAffectObject(const Object *obj, Int arg);

private:
	unsigned char m_pad000[0x128];
	const WeaponTemplate *m_detonationWeapon;	// +0x128
};

// ProjectileNugget::canAffectObject, retail 0x00509720.
Bool ProjectileNugget::canAffectObject(const Object *obj, Int arg)
{
	if (!rva005075D6((const void *)obj, (Object *)arg))
		return false;
	const WeaponTemplate *weapon = m_detonationWeapon;
	if (weapon == 0)
		return false;
	return ((Rva002CA9CA *)weapon)->rva002CAA59(arg, obj);
}
