// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0AODHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z, retail 0x0047B3DB, 317 bytes.
// AODHordeContain behavior ctor over the pinned HordeContain intermediate base
// (0x46F543, thing plus data). The eleven compiler vptr installs (primary plus
// +0x0C/+0x10/+0x20/+0x24/+0x28/+0x2C/+0x30/+0x34/+0xFC/+0x11C, three slots
// differing from the base) are the derived automatic stores (SiegeEngineContain
// precedent); the vector at +0x30C runs through the rowed BfmeE16 _Vector_base
// (0x211E58); two ints plus six floats zero at +0x318; arrayA 0x3Cx0x10 at
// +0x338 and arrayB 0x14x0x18 at +0x6FC run through ??_L with EH states 1-2;
// ints zero at +0x6F8/+0x8DC; the body clears arrayA. Identity is the
// ModuleFactory AODHordeContain registration plus the sole raw caller
// friend_newModuleInstance 0x24BB25 (news 0x8E0). BFME1 donor
// AODHordeContainCtorThunk.cpp gives the vector plus two-array concept.
#include <vector>

class Thing;
class ModuleData;

struct Iface00 { virtual void f00(); unsigned char m_pad[8]; };
struct Iface0C { virtual void f0C(); };
struct Iface10 { virtual void f10(); unsigned char m_pad[12]; };
struct Iface20 { virtual void f20(); };
struct Iface24 { virtual void f24(); };
struct Iface28 { virtual void f28(); };
struct Iface2C { virtual void f2C(); };
struct Iface30 { virtual void f30(); };
struct Iface34 { virtual void f34(); unsigned char m_pad[0xFC - 0x38]; };
struct IfaceFC { virtual void fFC(); unsigned char m_pad[0x11C - 0x100]; };
struct Iface11C { virtual void f11C(); unsigned char m_pad[0x30C - 0x11C - 4]; };

class HordeContain
	: public Iface00
	, public Iface0C
	, public Iface10
	, public Iface20
	, public Iface24
	, public Iface28
	, public Iface2C
	, public Iface30
	, public Iface34
	, public IfaceFC
	, public Iface11C
{
public:
	HordeContain(Thing *thing, const ModuleData *moduleData);
	~HordeContain();
};

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

struct Float3
{
	Float3()
	{
		float *cells = m_f;
		cells[0] = 0.0f;
		cells[1] = 0.0f;
		cells[2] = 0.0f;
	}

	float m_f[3];
};

struct Element16
{
	Element16();
	~Element16();
	void clear();
	float m_f[4];
};

// ??0Element16@@QAE@XZ present-unmatched
Element16::Element16()
{
}

// ??1Element16@@QAE@XZ present-unmatched
Element16::~Element16()
{
}

// ?clear@Element16@@QAEXXZ present-unmatched
void Element16::clear()
{
	m_f[0] = 0.0f;
	m_f[1] = 0.0f;
	m_f[2] = 0.0f;
	m_f[3] = 0.0f;
}

struct Element24
{
	Element24();
	~Element24();
	float m_f[5];
	unsigned char m_b;
	unsigned char m_pad[3];
};

// ??0Element24@@QAE@XZ present-unmatched
Element24::Element24()
{
	m_f[0] = 0.0f;
	m_f[1] = 0.0f;
	m_f[2] = 0.0f;
	m_f[3] = 0.0f;
	m_f[4] = 0.0f;
	m_b = 0;
}

// ??1Element24@@QAE@XZ present-unmatched
Element24::~Element24()
{
}

class AODHordeContain : public HordeContain
{
public:
	AODHordeContain(Thing *thing, const ModuleData *moduleData);
	virtual void f00();
	virtual void f20();
	virtual void f11C();

private:
	_STL::vector<BfmeE16> m_vector;
	int m_318;
	int m_31C;
	Float3 m_320;
	float m_32C;
	float m_330;
	float m_334;
	Element16 m_arrayA[0x3C];
	int m_6F8;
	Element24 m_arrayB[0x14];
	int m_8DC;
};

// ?f00@AODHordeContain@@UAEXXZ present-unmatched
void AODHordeContain::f00() {}
// ?f20@AODHordeContain@@UAEXXZ present-unmatched
void AODHordeContain::f20() {}
// ?f11C@AODHordeContain@@UAEXXZ present-unmatched
void AODHordeContain::f11C() {}

// ??0AODHordeContain@@QAE@PAVThing@@PBVModuleData@@@Z
AODHordeContain::AODHordeContain(Thing *thing, const ModuleData *moduleData)
	: HordeContain(thing, moduleData)
	, m_vector()
	, m_318(0)
	, m_31C(0)
	, m_320()
	, m_32C(0.0f)
	, m_330(0.0f)
	, m_334(0.0f)
	, m_6F8(0)
	, m_8DC(0)
{
	for (int j = 0; j != 0x3C; ++j)
		m_arrayA[j].clear();
}
