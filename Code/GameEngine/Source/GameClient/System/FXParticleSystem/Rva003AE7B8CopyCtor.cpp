// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD -EHs-c-
// ??0Rva003ABA36@@QAE@ABV0@@Z @0x003AE7B8 285B
// Compiler-generated copy ctor of the 0x8e4-byte particle object's base:
// Rva003AF50D head (rowed 0x003AF50D, three vptr stores), the
// LightningDrawModuleInfo copy at +0x18 (rowed 0x003A7DCA, neg/sbb/and null
// guard), two 90-element tables of {int, int, float} copied by the inline
// element ctor loop, an int and three int triples. The ctor is implicit, so
// the derived 0x003AE792 copy ctor below is its emitting user. Layout views
// carry measured offsets and sizes only; element and triple meanings are open.
// -EHs-c-: retail has no unwind frame here.
// Class names follow the vtables this ctor stores: 0x00C1D520's deleting
// dtor 0x003AE73C calls the rowed ~Rva003A97E0 (0x003A97E0) and 0x00C1D55C's
// deleting dtor 0x003AE8D5 calls the rowed ~Rva003ABA36 (0x003ABA36).
class RvaSmartPtr12_3AE7B8
{
public:
	RvaSmartPtr12_3AE7B8(const RvaSmartPtr12_3AE7B8 &that);
	~RvaSmartPtr12_3AE7B8();
private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};
class ModuleInfoSecondBase_3AE7B8
{
public:
	virtual ~ModuleInfoSecondBase_3AE7B8();
};
class ModuleInfoHeadBase_3AE7B8
{
public:
	ModuleInfoHeadBase_3AE7B8(const ModuleInfoHeadBase_3AE7B8 &other)
		: m_smart(other.m_smart)
		, m_int10(other.m_int10)
	{
	}
	virtual ~ModuleInfoHeadBase_3AE7B8();
	RvaSmartPtr12_3AE7B8 m_smart;
	int m_int10;
};
class Rva003AF50D : public ModuleInfoHeadBase_3AE7B8, public ModuleInfoSecondBase_3AE7B8
{
public:
	Rva003AF50D(const Rva003AF50D &other);
	virtual ~Rva003AF50D();
};
class Rva003A97E0 : public Rva003AF50D
{
public:
	__forceinline Rva003A97E0(const Rva003A97E0 &other)
		: Rva003AF50D(other)
	{
	}
	virtual ~Rva003A97E0();
};
namespace FXParticleSystem {
class LightningDrawModuleInfo {
public:
	LightningDrawModuleInfo(const LightningDrawModuleInfo &other);
	virtual ~LightningDrawModuleInfo();
private:
	char m_pad[0x30 - 4];
};
}
struct Elem3AE7B8
{
	Elem3AE7B8(const Elem3AE7B8 &other) : a(other.a), b(other.b), c(other.c) {}
	int a;
	int b;
	float c;
};
struct Triple3AE7B8
{
	Triple3AE7B8(const Triple3AE7B8 &other) : x(other.x), y(other.y), z(other.z) {}
	int x, y, z;
};
class Rva003ABA36 : public Rva003A97E0, public FXParticleSystem::LightningDrawModuleInfo
{
public:
	virtual ~Rva003ABA36();
private:
	Elem3AE7B8 m_first[90];
	Elem3AE7B8 m_second[90];
	int m_8b8;
	Triple3AE7B8 m_8bc, m_8c8, m_8d4;
	int m_8e0;
};
class Rva005EBCC0Object : public Rva003ABA36
{
public:
	Rva005EBCC0Object(const Rva005EBCC0Object &o);
};
Rva005EBCC0Object::Rva005EBCC0Object(const Rva005EBCC0Object &o)
	: Rva003ABA36(o)
{
}
