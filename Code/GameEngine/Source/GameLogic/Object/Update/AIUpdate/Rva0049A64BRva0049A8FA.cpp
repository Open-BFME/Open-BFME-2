// cl: /DNDEBUG /MD
//
// ?rva0049A8FA@Rva0049A64B@@UAEXHPAUCoord3D@@@Z @0x0049A8FA 65B.
// Target evidence: the only reference to this body is slot 5 of the vtable
// 0x00C50868 that the matched Rva0049A64B dtor 0x0049A64B installs at
// +0x3E4, the trailing interface base of this AIUpdate-family class (vptrs
// at +0, +0xC, +0x10, +0x20, +0x24 as the dtor stores them); the slot's name
// is not established, hence the address name. cl 7.1 compiles an override of
// a non-primary base's virtual with the base subobject's this and folds the
// adjustment into the member accesses: the Object pointer at +8 is read as
// [ecx-0x3DC]. Body: asks the object's +0x250 module (the contain slot the
// matched evaluateIsBuildingEmpty reads) for a provider through vslot +0x7C
// and, when it and the out pointer exist, copies the Coord3D that provider
// returns by value from vslot +0x1C (first argument forwarded, an int out
// parameter whose meaning is not asserted). Structural inference: the int is
// declared at function scope, which gives it its own frame slot as retail
// (declared in the if block it reuses the dead out-pointer argument slot).
class Thing;
class ModuleData;
struct Coord3D { float x, y, z; };
class Rva0049A8FAProvider
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual Coord3D rva1C(int a, int *extra) = 0; // +0x1C
};
class Rva0049A8FAContain
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void s25();
	virtual void s26();
	virtual void s27();
	virtual void s28();
	virtual void s29();
	virtual void s30();
	virtual Rva0049A8FAProvider *rva7C() = 0; // +0x7C
};
class Object
{
public:
	unsigned char m_pad000[0x250];
	Rva0049A8FAContain *m_250;
};
struct B00 { virtual void f00(); const ModuleData *m_moduleData; Object *m_object; };
struct B0C { virtual void f0C(); };
struct B10 { virtual void f10(); unsigned char m_pad[12]; };
struct B20 { virtual void f20(); };
struct B24 { virtual void f24(); unsigned char m_pad[0x3E4 - 0x28]; };
class Iface3E4
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void rva0049A8FA(int a, Coord3D *out) = 0;
};
class Rva0049A64B : public B00, public B0C, public B10, public B20, public B24, public Iface3E4
{
public:
	virtual void rva0049A8FA(int a, Coord3D *out);
};
void Rva0049A64B::rva0049A8FA(int a, Coord3D *out)
{
	int extra;
	Rva0049A8FAProvider *p = m_object->m_250->rva7C();
	if (p && out)
	{
		*out = p->rva1C(a, &extra);
	}
}
