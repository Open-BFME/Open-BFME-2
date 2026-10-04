// cl: /O1 /DNDEBUG /MD
// ?rva00479ADA@HordeGarrisonContain@@UAEXPAVObject@@@Z @0x00479ADA 48B
// Evidence: chain lane, calls 0x00588D24 just landed, vtable slot 30 of 0x00846570 and 0x00847740,
// callers 0x00480C6A and 0x00481442, globals none, second base +0x9E0, subobject +0x20.
class Object;

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

struct Iface00
{
	SLOT08(f00,f01,f02,f03,f04,f05,f06,f07)
	SLOT08(f08,f09,f0A,f0B,f0C,f0D,f0E,f0F)
	SLOT08(f10,f11,f12,f13,f14,f15,f16,f17)
	virtual void f18(); virtual void f19(); virtual void f1A(); virtual void f1B();
	const void *m_moduleData;
	Object *m_object;
};
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20
{
	SLOT08(g00,g01,g02,g03,g04,g05,g06,g07)
	SLOT08(g08,g09,g10,g11,g12,g13,g14,g15)
	SLOT08(g16,g17,g18,g19,g20,g21,g22,g23)
	SLOT08(g24,g25,g26,g27,g28,g29,g30,g31)
	virtual void g32(); virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36(); virtual void g37(); virtual void g38();
	virtual void rva00464830(Object *obj) = 0;
};
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0x9E0 - 0x38]; };

class OpenContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
{
public:
	virtual void rva00464830(Object *obj);
};

class GarrisonContain : public OpenContain
{
};

class Rva0047A040Base9E0
{
public:
	bool rva00588D24(void *a, Object *b);
};

class Rva00478C2C
{
public:
	void rva00478C2C(Object *obj, void *x);
};

class HordeGarrisonContain : public GarrisonContain, public Rva0047A040Base9E0
{
public:
	virtual void s1C(); // slot 28
	virtual void rva00479B7F(Object *obj); // slot 29
	virtual void rva00479ADA(Object *obj); // slot 30
};

void HordeGarrisonContain::rva00479ADA(Object *obj)
{
	Rva0047A040Base9E0 *base = (Rva0047A040Base9E0 *)((char *)this + 0x9E0);
	if (base->rva00588D24(this, obj)) {
		Rva00478C2C *bpc = (Rva00478C2C *)((char *)this + 0x20);
		bpc->rva00478C2C(obj, 0);
		f12();
	}
}
