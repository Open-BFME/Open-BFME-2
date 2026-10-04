// ?rva00479C35@HordeGarrisonContain@@QAEXPAUCoord3D@@0@Z
// partial score=0.9 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva00479C35@HordeGarrisonContain@@QAEXPAUCoord3D@@0@Z @0x00479C35 164B
// Evidence: leaf lane, called from 3 sites in 0x00479E62, prev 0x00479C2A next 0x00479D28,
// frameless SSE transform via m_object matrix, ret 8 with 2 args.
class Object;

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct Transform
{
	float m00;
	float m01;
	float m02;
	float tx;
	float m10;
	float m11;
	float m12;
	float ty;
	float m20;
	float m21;
	float m22;
	float tz;
};

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
	char _00[4];
};

class HordeGarrisonContain : public GarrisonContain, public Rva0047A040Base9E0
{
public:
	virtual void s1C();
	virtual void rva00479B7F(Object *obj);
	virtual void rva00479ADA(Object *obj);
	void rva00479C35(Coord3D *in, Coord3D *out);
};

class Object
{
public:
	char _00[8];
	Transform m_t;
};

// ?rva00479C35@HordeGarrisonContain@@QAEXPAUCoord3D@@0@Z present-unmatched
void HordeGarrisonContain::rva00479C35(Coord3D *in, Coord3D *out)
{
	float x = in->x;
	float y = in->y;
	float z = in->z;
	Transform *t = &m_object->m_t;
	out->x = t->m01 * y + t->m02 * z + *(const volatile float *)&t->m00 * x + t->tx;
	out->y = t->m11 * y + t->m12 * z + *(const volatile float *)&t->m10 * x + t->ty;
	out->z = t->m21 * y + t->m22 * z + *(const volatile float *)&t->m20 * x + t->tz;
}
