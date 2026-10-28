// cl: /DNDEBUG /MD
//
// HordeTransportContain's overrides in its +0x20 interface vftable 0x00C45D30
// (installed by the matched ctor 0x00477003; HordeSiegeEngineContain keeps
// them, vftable 0x00C47328). As in HordeGarrisonContainIface20.cpp, each
// forwards to a member of the empty helper (pinned Rva0047A040Base9E0
// members), which this class carries at +0x11D (the ctor builds a member
// there), and each override is named after the OpenContain implementation it
// replaces in OpenContain's +0x20 vftable 0x00C433B0; the names themselves
// are not established.
//
// ?rva00465011@HordeTransportContain@@UAEXPAVObject@@@Z, retail 0x004772B8, 25
// bytes. Slot 32: the helper member 0x00588F61 with the contain, the owner and
// the argument.
//
// ?rva004632E0@HordeTransportContain@@UAEXPAVObject@@@Z, retail 0x0047710B, 22
// bytes. Slot 61: the helper member 0x00588C4E with the contain and the
// argument.
//
// ?rva004770A6@HordeTransportContain@@UAEXPAVObject@@@Z, retail 0x004770A6, 56
// bytes. OpenContain slot 39 (pinned 0x00464830) qualified on the +0x20
// subobject via the layout-compatible OpenContain view, then the helper member
// 0x00588D99 at +0x11D, then set weapon-set flag 0x14 on the argument when its
// rowed bit-gate 0x0029091E says so. Shape follows HordeGarrisonContain slot 29
// 0x00479B7F (same two calls); the flag tail is new. Address name: class from
// the +0x20/+0x11D layout and slot shape, method identity not established.

enum WeaponSetType
{
	WEAPONSET_NONE = 0
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_26 = 0x26
};

class Object
{
public:
	bool rva0029091E(unsigned int bit) const;
	void setWeaponSetFlag(WeaponSetType wst);
	bool testStatus(ObjectStatusTypes status) const;
	unsigned char m_pad000[0x274];
	Object *m_containedBy;	// +0x274
};

// An entry the +0x11D helper keeps per contained object (rowed lookup
// 0x00588B8A); slot 73 (+0x124) tells it the object left.

class Rva00477305Owner
{
public:
	void rva00477305(Object *obj);
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
};

class Rva00468657
{
public:
	virtual void g00();
	void rva00468657(Object *obj, bool flag);
};

class Rva00588E44Contain;
class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *);
	void rva00588BA8(Object *obj, bool flag);
	Object *rva00588C4E(void *contain, const struct Coord3D *obj);
	void rva00588F61(void *contain, Object *owner, enum CommandSourceType obj);
	void rva00588D99(Object *obj);
	void rva00588E20(Object *object);
	Rva00588E44Contain *rva00588BF3(void *contain, Object *obj);
	bool rva00588D24(void *owner, Object *obj);
	void rva00588E44(void *argument);
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

class Rva004773D6Entry
{
public:
	SLOT08(e00,e01,e02,e03,e04,e05,e06,e07)
	SLOT08(e08,e09,e10,e11,e12,e13,e14,e15)
	SLOT08(e16,e17,e18,e19,e20,e21,e22,e23)
	SLOT08(e24,e25,e26,e27,e28,e29,e30,e31)
	SLOT08(e32,e33,e34,e35,e36,e37,e38,e39)
	SLOT08(e40,e41,e42,e43,e44,e45,e46,e47)
	SLOT08(e48,e49,e50,e51,e52,e53,e54,e55)
	SLOT08(e56,e57,e58,e59,e60,e61,e62,e63)
	SLOT08(e64,e65,e66,e67,e68,e69,e70,e71)
	virtual void e72();
	virtual void rva004773D6Left();	// +0x124
};

struct Iface00
{
	virtual void f00();
	SLOT08(f01,f02,f03,f04,f05,f06,f07,f08)
	SLOT08(f09,f10,f11,f12,f13,f14,f15,f16)
	virtual void f17();
	virtual void rva004773D6Refresh();	// +0x48
	const void *m_moduleData; Object *m_object;
};
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20 : public Rva00468657
{
	virtual void g01(); virtual void g02(); virtual void g03(); virtual void g04(); virtual void g05(); virtual void g06(); virtual void g07();
	SLOT08(g08,g09,g10,g11,g12,g13,g14,g15)
	SLOT08(g16,g17,g18,g19,g20,g21,g22,g23)
	virtual void g24(); virtual void g25(); virtual void g26();
	virtual void rva0050B238(Object *obj, bool flag) = 0;
	virtual void g28(); virtual void g29(); virtual void g30(); virtual void g31();
	virtual void rva00465011(Object *obj) = 0;
	virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36(); virtual void g37(); virtual void g38();
	virtual void addToContain(Object *obj) = 0;
	virtual void g40(); virtual void g41(); virtual void g42(); virtual void g43();
	SLOT08(g44,g45,g46,g47,g48,g49,g50,g51)
	SLOT08(g52,g53,g54,g55,g56,g57,g58,g59)
	virtual void g60();
	virtual void rva004632E0(Object *obj) = 0;
};
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0x11C - 0x38]; };

class TransportContain
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

struct OIface00 { virtual void f00(); const void *m_moduleData; Object *m_object; };
struct OIface0C { virtual void f0C(); };
struct OIface10 { virtual void f10(); unsigned char m_pad[12]; };
struct OIface20o
{
	SLOT08(h00,h01,h02,h03,h04,h05,h06,h07)
	SLOT08(h08,h09,h10,h11,h12,h13,h14,h15)
	SLOT08(h16,h17,h18,h19,h20,h21,h22,h23)
	SLOT08(h24,h25,h26,h27,h28,h29,h30,h31)
	SLOT08(h32,h33,h34,h35,h36,h37,h38,h39)
	virtual void addToContain(Object *obj) = 0;
};
struct OIface24 { virtual void f24(); };
struct OIface28 { virtual void f28(); };
struct OIface2C { virtual void f2C(); };
struct OIface30 { virtual void f30(); };
struct OIface34 { virtual void f34(); };

class OpenContain
	: public OIface00
	, public OIface0C
	, public OIface10
	, public OIface20o
	, public OIface24
	, public OIface28
	, public OIface2C
	, public OIface30
	, public OIface34
{
public:
	virtual void addToContain(Object *obj);
};

class HordeTransportContain : public TransportContain
{
public:
	virtual void rva0050B238(Object *obj, bool flag);
	virtual void rva00465011(Object *obj);
	virtual void rva004632E0(Object *obj);
	virtual void rva004770A6(Object *obj);
	virtual void addToContain(Object *obj);
private:
	unsigned char m_11C;
	Rva0047A040Base9E0 m_helper; // +0x11D
};

// ?rva0050B238@HordeTransportContain@@UAEXPAVObject@@_N@Z @0x00477121
void HordeTransportContain::rva0050B238(Object *obj, bool flag)
{
	m_helper.rva00588BA8(obj, flag);
	rva00468657(obj, flag);
}

// ?rva004632E0@HordeTransportContain@@UAEXPAVObject@@@Z @0x0047710B
void HordeTransportContain::rva004632E0(Object *obj)
{
	m_helper.rva00588C4E(this, (const Coord3D *)obj);
}

// ?rva00465011@HordeTransportContain@@UAEXPAVObject@@@Z @0x004772B8
void HordeTransportContain::rva00465011(Object *obj)
{
	m_helper.rva00588F61(this, m_object, (CommandSourceType)(int)obj);
}

void HordeTransportContain::rva004770A6(Object *obj)
{
	((OpenContain *)this)->OpenContain::addToContain(obj);
	m_helper.rva00588D99(obj);
	if (obj->rva0029091E(0x14))
		obj->setWeaponSetFlag((WeaponSetType)0x14);
}

// ?addToContain@HordeTransportContain@@UAEXPAVObject@@@Z, retail 0x004773D6,
// 92 bytes. Slot 39 of the +0x20 vftable (OpenContain's pinned 0x00464830 in
// its own table): for an Object no longer contained (+0x274 clear) the
// helper's entry for it is told it left (slot 73) and the object goes
// through 0x004770A6 above; without an entry an object with status 0x26 is
// handled by the rowed 0x00477305 instead. Either way the contain then
// refreshes through primary slot 18.
void HordeTransportContain::addToContain(Object *obj)
{
	if (obj->m_containedBy)
		return;
	Rva004773D6Entry *entry = (Rva004773D6Entry *)m_helper.rva00588B8A(obj);
	if (entry)
	{
		entry->rva004773D6Left();
		HordeTransportContain::rva004770A6(obj);
	}
	else if (obj->testStatus(OBJECT_STATUS_26))
		((Rva00477305Owner *)this)->rva00477305(obj);
	else
		HordeTransportContain::rva004770A6(obj);
	rva004773D6Refresh();
}
