// cl: /DNDEBUG /MD
//
// ?gatherUnitBack@HordeContain@@UAEXPAVObject@@@Z, retail 0x004725D5, 75 bytes.
// Slot 38 of ??_7HordeContain 0x00C45050 (the last of the slots 34 to 38 it
// adds over OpenContain's 34; HorseHordeContain and AODHordeContain keep it).
// Erases the object's ID from the keyed tree at +0x170 (rowed erase-by-key
// rva0046EDEF), then runs the +0x20 interface's slot 39 with the object and
// its slot 93 with the owner's +0x284 block and 0. Address name: class and
// slot are proven, the method identity is not.

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	unsigned char m_pad00[0x74];
	ObjectID m_id; // +0x74
	unsigned char m_pad78[0x284 - 0x78];
	unsigned char m_284[4]; // +0x284
};

class Rva002EE9B7
{
public:
	unsigned int rva0046EDEF(const int &key);
private:
	unsigned char m_tree[0x0C];
};

struct Iface00
{
	SLOT08(f00,f01,f02,f03,f04,f05,f06,f07)
	SLOT08(f08,f09,f0A,f0B,f0C,f0D,f0E,f0F)
	SLOT08(f10,f11,f12,f13,f14,f15,f16,f17)
	SLOT08(f18,f19,f1A,f1B,f1C,f1D,f1E,f1F)
	virtual void f20(); virtual void f21();
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
	virtual void rva39(Object *obj);
	SLOT08(g40,g41,g42,g43,g44,g45,g46,g47)
	SLOT08(g48,g49,g50,g51,g52,g53,g54,g55)
	SLOT08(g56,g57,g58,g59,g60,g61,g62,g63)
	SLOT08(g64,g65,g66,g67,g68,g69,g70,g71)
	SLOT08(g72,g73,g74,g75,g76,g77,g78,g79)
	SLOT08(g80,g81,g82,g83,g84,g85,g86,g87)
	virtual void g88(); virtual void g89(); virtual void g90(); virtual void g91();
	virtual void g92();
	virtual void rva93(void *block, int flag);
};
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0x170 - 0x38]; };

class OpenContainView
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
};

class HordeContain : public OpenContainView
{
public:
	virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
	virtual void gatherUnitBack(Object *obj);
private:
	Rva002EE9B7 m_170;
};

// ?gatherUnitBack@HordeContain@@UAEXPAVObject@@@Z @0x004725D5
void HordeContain::gatherUnitBack(Object *obj)
{
	ObjectID id = obj->getID();
	m_170.rva0046EDEF(reinterpret_cast<const int &>(id));
	rva39(obj);
	rva93(m_object->m_284, 0);
}
