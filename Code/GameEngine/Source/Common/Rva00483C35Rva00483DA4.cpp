// cl: /DNDEBUG /MD
//
// ?rva00483DA4@Rva00483C35@@UAEXPAUCoord3D@@@Z @0x00483DA4 84B.
// Target evidence: the only reference to this body is slot 1 of the vtable
// 0x00C49D70 that the matched Rva00483C35 dtor 0x00483C35 installs at +0x50,
// the last interface base of this behavior class (vptrs at +0, +0xC, +0x10,
// +0x20, +0x24, +0x50 as the dtor stores them); the slot's name is not
// established, hence the address name. cl 7.1 compiles an override of a
// non-primary base's virtual with the base subobject's this and folds the
// adjustment into the member accesses: module data (+4) and object (+8) are
// read as [ecx-0x4C] and [ecx-0x48]. Body: without an object the out
// coordinate is zeroed; otherwise the module data's Coord3D at +0x1EC is
// transformed by the object (Thing::transformPoint 0x0030A812, pinned from
// this call site) into a temporary copied field by field into out (retail
// shares the z store between the two paths).
class ModuleData;
struct Coord3D { float x, y, z; };
class Thing
{
public:
	void transformPoint(const Coord3D *in, Coord3D *out);
};
struct Rva00483C35ModuleData
{
	unsigned char m_pad000[0x1EC];
	Coord3D m_1EC;
};
struct B00 { virtual void f00(); const Rva00483C35ModuleData *m_moduleData; Thing *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); unsigned char m_pad[12]; };
struct B20 { virtual void f20(); };
struct B24 { virtual void f24(); unsigned char m_pad[0x50 - 0x28]; };
class Iface50
{
public:
	virtual void s00();
	virtual void rva00483DA4(Coord3D *out) = 0;
};
class Rva00483C35 : public B00, public B0C, public B10, public B20, public B24, public Iface50
{
public:
	virtual void rva00483DA4(Coord3D *out);
};
void Rva00483C35::rva00483DA4(Coord3D *out)
{
	const Rva00483C35ModuleData *md = m_moduleData;
	Thing *obj = m_object;
	if (obj == 0)
	{
		out->x = 0.0f;
		out->y = 0.0f;
		out->z = 0.0f;
	}
	else
	{
		Coord3D tmp;
		obj->transformPoint(&md->m_1EC, &tmp);
		out->x = tmp.x;
		out->y = tmp.y;
		out->z = tmp.z;
	}
}
