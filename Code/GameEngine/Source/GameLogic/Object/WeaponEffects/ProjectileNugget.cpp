// cl: /O1 /EHsc /MD /arch:SSE
// ProjectileNugget.cpp -- ProjectileNugget members recovered from
// WorldBuilder leads (reverse/wb_name_leads.csv): WB's debug build names the
// function (vtable pairing); retail supplies the bytes. The nugget first
// applies the base nugget test (0x005075D6, rowed under the placeholder
// Rva00508925), then requires its filter at +0x128 to accept the object.

typedef int Int;
typedef bool Bool;

class Object;

class Rva002CA9CA
{
public:
	Bool rva002CAA59(Int arg, const void *obj);		// 0x002CAA59
};

class Rva00508925
{
public:
	unsigned char rva005075D6(Int obj, Int arg);		// 0x005075D6
};

class ProjectileNugget : public Rva00508925
{
public:
	Bool canAffectObject(const Object *obj, Int arg);

private:
	unsigned char m_pad000[0x128];
	Rva002CA9CA *m_filter;				// +0x128
};

// ProjectileNugget::canAffectObject, retail 0x00509720.
Bool ProjectileNugget::canAffectObject(const Object *obj, Int arg)
{
	if (!rva005075D6((Int)obj, arg))
		return false;
	if (m_filter == 0)
		return false;
	return m_filter->rva002CAA59(arg, obj);
}
