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

class Object
{
public:
	Player *getControllingPlayer() const;
	unsigned char m_pad00[0x94];
	Rva00331682Holder m_holder;
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

struct Iface00 { virtual void f00(); const void *m_moduleData; Object *m_object; };
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

class HordeGarrisonContain : public GarrisonContain
{
public:
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
};

class SlaughterHordeContain : public HordeGarrisonContain
{
public:
	virtual bool isValidContainerFor(Object *obj, bool checkCapacity, bool testPath);
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
