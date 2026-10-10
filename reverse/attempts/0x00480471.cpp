// ?rva00464830@SlaughterHordeContain@@UAEXPAVObject@@@Z
// partial score=0.98 date=2026-10-11
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
//
// ?isValidContainerFor@SlaughterHordeContain@@UAE_NPAVObject@@_N1@Z retail 0x00480661 114B
// Slot 38 of SlaughterHordeContain vtable 0x00848918 via row ??1SlaughterHordeContain
// Falls back to rowed HordeGarrisonContain::isValidContainerFor 0x00479E62
// Callees rowed: ObjectFilter::isValid 0x00360CED at moduleData+0xD8
// _Base_bitset<4>::_M_is_any 0x000454BA at +0xDC
// Rva00331682Holder::test 0x00331682 at Object+0x94
// Object::getControllingPlayer 0x0028AFA9 and Rva2225E0Filter::accepts 0x00362437
// Unblocks 0x0048071D. Layout from rowed ctor 0x0048034E and Horde moduledata 0x0047A251

namespace _STL
{
template<unsigned N> struct _Base_bitset;
template<> struct _Base_bitset<4>
{
	bool _M_is_any() const;
	unsigned long _M_w[4];
};
}

class Player;

class ObjectFilter
{
public:
	bool isValid() const;
private:
	int m_entryIndex;
};

class Rva00331682Holder
{
public:
	bool test(const void *other) const;
};

struct SlaughterRiderTemplateView { unsigned char m_pad000[0x115]; unsigned char m_kindOf115; };

class Object
{
public:
	Player *getControllingPlayer() const;
	void *m_vtable;
	const SlaughterRiderTemplateView *m_template;
	unsigned char m_pad08[0x94 - 0x08];
	Rva00331682Holder m_holder;
	unsigned char m_pad95[0x274 - 0x95];
	Object *m_containedBy;			// +0x274
};

struct Rva2225E0Filter : public ObjectFilter
{
	bool accepts(Object *obj, Player *player);
};

struct SlaughterHordeContainModuleData
{
	unsigned char m_pad00[0xD8];
	Rva2225E0Filter m_filter;
	_STL::_Base_bitset<4> m_bits;
};

#define SLOT08(a,b,c,d,e,f,g,h) virtual void a(); virtual void b(); virtual void c(); virtual void d(); virtual void e(); virtual void f(); virtual void g(); virtual void h();

struct Iface00
{
	SLOT08(p00,p01,p02,p03,p04,p05,p06,p07)
	SLOT08(p08,p09,p10,p11,p12,p13,p14,p15)
	virtual void p16(); virtual void p17();
	virtual void rvaPrimary48();				// +0x48
	virtual void p19();
	SLOT08(p20,p21,p22,p23,p24,p25,p26,p27)
	virtual void p28();
	virtual void rvaPrimary74(Object *obj);			// +0x74
	virtual void rvaPrimary78(Object *obj);			// +0x78
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
	virtual void g24(); virtual void g25(); virtual void g26();
	virtual void rva0050B238(Object *obj, bool flag);
	virtual void g28(); virtual void g29(); virtual void g30(); virtual void g31();
	virtual void rva00465011(Object *obj);
	virtual void g33(); virtual void g34(); virtual void g35();
	virtual void g36(); virtual void g37();
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
	virtual void rva00464830(Object *obj);
};
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0x9E0 - 0x38]; };

class GarrisonContain
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

class Rva00588B8AMember
{
public:
#define S(n) virtual void s##n();
	S(00) S(01) S(02) S(03) S(04) S(05) S(06) S(07) S(08) S(09) S(10) S(11) S(12) S(13) S(14) S(15)
	S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31)
	S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39) S(40) S(41) S(42) S(43) S(44) S(45) S(46) S(47)
	S(48) S(49) S(50) S(51) S(52) S(53) S(54) S(55) S(56) S(57) S(58) S(59) S(60) S(61) S(62) S(63)
	S(64) S(65) S(66) S(67) S(68) S(69) S(70) S(71) S(72)
#undef S
	virtual void slot124();					// +0x124
};

class Rva0047A040Base9E0
{
public:
	void *rva00588B8A(void *obj);
	void *rva00588BF3(void *contain, Object *obj);
};

class HordeGarrisonContain : public GarrisonContain, public Rva0047A040Base9E0
{
public:
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
};

class SlaughterHordeContain : public HordeGarrisonContain
{
public:
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
	virtual void rva00464830(Object *obj);
};

// ?isValidContainerFor@SlaughterHordeContain@@UAE_NPAVObject@@_N1@Z @0x00480661
bool SlaughterHordeContain::isValidContainerFor(Object *obj, bool checkCapacity, bool testPath)
{
	SlaughterHordeContainModuleData *data = (SlaughterHordeContainModuleData *)m_moduleData;
	Rva2225E0Filter *filter = &data->m_filter;
	if (filter->isValid())
	{
		_STL::_Base_bitset<4> *bits = &data->m_bits;
		if (!bits->_M_is_any() || ((Rva00331682Holder *)((char *)m_object + 0x94))->test(bits))
		{
			Player *player = m_object->getControllingPlayer();
			if (filter->accepts(obj, player))
				return true;
		}
	}
	return HordeGarrisonContain::isValidContainerFor(obj, checkCapacity, testPath);
}

// ?rva00464830@SlaughterHordeContain@@UAEXPAVObject@@@Z, retail 0x00480471, 108 bytes:
// slot 39 after the override above. HordeGarrisonContain's 0x00479D6D, except
// that a rider which starts no horde member still goes to primary slot 0x74
// only when its template has kind-of bit 0x20 at +0x115.
void SlaughterHordeContain::rva00464830(Object *obj)
{
	if (obj->m_containedBy)
		return;
	Rva00588B8AMember *member = (Rva00588B8AMember *)rva00588B8A(obj);
	if (member)
	{
		member->slot124();
		rvaPrimary74(obj);
	}
	else if (rva00588BF3(this, obj) == 0 && (obj->m_template->m_kindOf115 & 0x20))
	{
		rvaPrimary74(obj);
	}
	else
	{
		rvaPrimary78(obj);
	}
	rvaPrimary48();
}
