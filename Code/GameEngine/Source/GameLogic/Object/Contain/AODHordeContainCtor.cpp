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
	void rva00470DC1();
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

struct Rva0047A702
{
	Rva0047A702();
	~Rva0047A702();
	float m_f[5];
	unsigned char m_b;
	unsigned char m_pad[3];
};

Rva0047A702::Rva0047A702()
{
	m_f[0] = 0.0f;
	m_f[1] = 0.0f;
	m_f[2] = 0.0f;
	m_f[3] = 0.0f;
	m_f[4] = 0.0f;
	m_b = 0;
}

// ??1Rva0047A702@@QAE@XZ present-unmatched
Rva0047A702::~Rva0047A702()
{
}

class AODHordeContain : public HordeContain
{
public:
	AODHordeContain(Thing *thing, const ModuleData *moduleData);
	void rva0047A729(const Float3 *position);
	void rva0047A77E();
	void rva0047A413();
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
	Rva0047A702 m_arrayB[0x14];
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

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f0C@Iface0C@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?f2C@Iface2C@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

// Target 0x0047A729..0x0047A77E (RET 4). The adjacent constructor proves
// the sixty 16-byte entries at +0x338 and count at +0x6F8. Each entry holds
// a three-float position followed by a copy of the owner's field at +0x44.
// The field and method keep address-derived spellings until named evidence
// identifies them. No donor method identity is asserted.
struct AODHistoryOwnerView
{
    unsigned char m_prefix[0x44];
    float m_field44;
};

void AODHordeContain::rva0047A729(const Float3 *position)
{
    int count;
    if (m_6F8 == 60)
        count = 59;
    else if ((count = m_6F8++) <= 0)
        goto insertPosition;
    Element16 *destination = m_arrayA + count;
    do
    {
        --count;
        Element16 *source = destination - 1;
        *destination = *source;
        destination = source;
    }
    while (count);
insertPosition:
    *reinterpret_cast<Float3 *>(&m_arrayA[0]) = *position;
    AODHistoryOwnerView *owner = *reinterpret_cast<AODHistoryOwnerView **>(
        reinterpret_cast<unsigned char *>(this) + 8);
    m_arrayA[0].m_f[3] = owner->m_field44;
}

// BFME1 semantic donor: AODHordeContainUpdateFormation.cpp at1399ad37.
// Native247B47A77E..47A875 has dynamic frame-rate defaults, out-of-line
// Coord3D length and a KindOf215 query instead of the donor's condition bit.
// The receiver/callee spellings retain unresolved target method identities.
class Object;
struct Rva0028AC4EEntry;
class Rva001E46E1
{
public:
    float rva001E46E1(Object *object);
    float rva001E4845(Object *object);
};
class Object
{
public:
    const Rva0028AC4EEntry *rva0028AC4E() const;
    bool rva0006F039(int kind) const;
};
class Rva0055A627Difference
{
public:
    float x, y, z;
    float length() const;
};
extern int g_Va00DBA4E4;

void AODHordeContain::rva0047A77E()
{
    float scale = 1.0f / g_Va00DBA4E4;
    float movementSpeed = scale * 100.0f;
    float movementStep = scale * 10.0f;
    Object *object = *reinterpret_cast<Object **>(
        reinterpret_cast<unsigned char *>(this) + 8);
    Rva001E46E1 *ai = reinterpret_cast<Rva001E46E1 *>(
        const_cast<Rva0028AC4EEntry *>(object->rva0028AC4E()));
    if (ai)
    {
        movementSpeed = ai->rva001E46E1(object);
        movementStep = ai->rva001E4845(object);
    }
    const Float3 *current = reinterpret_cast<const Float3 *>(
        reinterpret_cast<const unsigned char *>(object) + 0x38);
    Float3 position;
    position.m_f[0] = current->m_f[0];
    position.m_f[1] = current->m_f[1];
    position.m_f[2] = current->m_f[2];
    const Float3 *previous = reinterpret_cast<const Float3 *>(
        reinterpret_cast<const unsigned char *>(this) + 0x704);
    Rva0055A627Difference difference;
    difference.x = position.m_f[0] - previous->m_f[0];
    difference.y = position.m_f[1] - previous->m_f[1];
    difference.z = position.m_f[2] - previous->m_f[2];
    if (difference.length() > movementStep)
        rva0047A729(&position);
    rva0047A413();
    const float &speed = movementSpeed;
    if (object->rva0006F039(215))
    {
        float &tail = m_334;
        tail = tail + speed;
    }
    HordeContain::rva00470DC1();
}
