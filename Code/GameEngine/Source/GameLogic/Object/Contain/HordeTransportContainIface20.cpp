// cl: /O1 /DNDEBUG /MD
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

class Object
{
public:
	bool rva0029091E(unsigned int bit) const;
	void setWeaponSetFlag(WeaponSetType wst);
};

class Rva0047A040Base9E0
{
public:
	void rva00588C4E(void *contain, Object *obj);
	void rva00588F61(void *contain, Object *owner, Object *obj);
	void rva00588D99(Object *obj);
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

struct Iface00 { virtual void f00(); const void *m_moduleData; Object *m_object; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20
{
	SLOT08(g00,g01,g02,g03,g04,g05,g06,g07)
	SLOT08(g08,g09,g10,g11,g12,g13,g14,g15)
	SLOT08(g16,g17,g18,g19,g20,g21,g22,g23)
	virtual void g24(); virtual void g25(); virtual void g26(); virtual void g27();
	virtual void g28(); virtual void g29(); virtual void g30(); virtual void g31();
	virtual void rva00465011(Object *obj) = 0;
	virtual void g33(); virtual void g34(); virtual void g35();
	SLOT08(g36,g37,g38,g39,g40,g41,g42,g43)
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
	virtual void rva00464830(Object *obj) = 0;
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
	virtual void rva00464830(Object *obj);
};

class HordeTransportContain : public TransportContain
{
public:
	virtual void rva00465011(Object *obj);
	virtual void rva004632E0(Object *obj);
	virtual void rva004770A6(Object *obj);
private:
	unsigned char m_11C;
	Rva0047A040Base9E0 m_helper; // +0x11D
};

// ?rva004632E0@HordeTransportContain@@UAEXPAVObject@@@Z @0x0047710B
void HordeTransportContain::rva004632E0(Object *obj)
{
	m_helper.rva00588C4E(this, obj);
}

// ?rva00465011@HordeTransportContain@@UAEXPAVObject@@@Z @0x004772B8
void HordeTransportContain::rva00465011(Object *obj)
{
	m_helper.rva00588F61(this, m_object, obj);
}

void HordeTransportContain::rva004770A6(Object *obj)
{
	((OpenContain *)this)->OpenContain::rva00464830(obj);
	m_helper.rva00588D99(obj);
	if (obj->rva0029091E(0x14))
		obj->setWeaponSetFlag((WeaponSetType)0x14);
}
