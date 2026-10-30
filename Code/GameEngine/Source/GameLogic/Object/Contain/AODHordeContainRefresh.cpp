// cl: /DNDEBUG /MD /D_CRTIMP= /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Include

class Xfer;
// stlport
#include "../../../Common/Thing/thing.h"
//
// ?refreshTrackedLargeUnit@AODHordeContain@@QAEXXZ, retail 0x0047B2AA, 81 bytes.
// Cached large-unit tracker: looks up m_trackedLargeUnit (+0x318) through
// TheGameLogic->findObjectByID (rowed 0x00049DC5); clears the ID when the
// object is gone, else copies its position (+0x38) to +0x320, sets +0x32C to
// 17.0f and +0x330 from GeometryInfo::getMaxHeightAbovePosition (rowed
// 0x006BD7C0 on the object at +0xA8). Layout from the rowed ctor 0x0047B3DB
// (vector at +0x30C, tracked ID at +0x318, position at +0x320, height pair at
// +0x32C/+0x330, factory news 0x8E0); BFME1 donor
// AODHordeContain_trackLargeUnit.cpp gives the find-clear-copy-height concept
// with 17.0f. Unblocks the 0x0047B628 caller. Identity is the AOD offsets
// plus the donor method name.

#include "../../../Common/GameLogicObjectLookupView.h"

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Object;
class GeometryInfo;


enum KindOfType { KINDOF_INVALID = -1, KINDOF_RVA_0 = 0 };

class GeometryInfo
{
public:
    float getMaxHeightAbovePosition() const;
};

class AIUpdateInterface;
class Rva003BD306Target;
struct Rva0028AC4EEntry;

class Object : public Thing
{
public:
    Drawable *getDrawable() const;
    const Rva0028AC4EEntry *rva0028AC4E() const;
    bool isKindOf(KindOfType kind) const;
    int rva0028B511() const;
    char m_pad060[0x74 - 0x60];
    int m_id; // +0x74
    char m_pad78[0xA8 - 0x78];
    GeometryInfo m_geometry;
    char m_padA9[0x258 - 0xA9];
    AIUpdateInterface *m_ai; // +0x258
    char m_pad25C[0x264 - 0x25C];
    Rva003BD306Target *m_experienceTracker;
};

#include <vector>
#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
#include "../../../Common/GameLogicObjectLookupView.h"
class Thing;
class ModuleData;
class Object;

struct Rva0047A6EDElem28 { int m_w[7]; };

struct Rva0047A6EDVec28
{
	Rva0047A6EDElem28 *m_start;
	Rva0047A6EDElem28 *m_finish;
	Rva0047A6EDElem28 *m_end;
	int size() const { return m_finish - m_start; }
};

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

struct Iface11C
{
	virtual void f11C();
	unsigned char m_pad120[0x188 - 0x120];
	Rva0047A6EDVec28 m_vec188;
	unsigned char m_pad194[0x30C - 0x194];
};

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
	virtual ~HordeContain();
	virtual void rva00470DC1();
public: void rva0047A413();
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

struct AODTrackedPosition : public Coord3D
{
    AODTrackedPosition()
    {
        Coord3D *cells = this;
        cells->x = 0.0f;
        cells->y = 0.0f;
        cells->z = 0.0f;
    }
};

struct Element16
{
	Element16();
	~Element16();
	void clear();
	float m_f[4];
};

struct Rva0047A702
{
	Rva0047A702();
	~Rva0047A702();
	float m_f[5];
	unsigned char m_b;
	unsigned char m_pad[3];
};

class AODHordeContain : public HordeContain
{
public:
	AODHordeContain(Thing *thing, const ModuleData *moduleData);
public:
	virtual ~AODHordeContain();
public:
	int rva0047A6ED() const;
public:
	void rva0047A729(const Float3 *position);
public:
	void rva0047A77E();
public:
	__declspec(dllimport) __forceinline void rva0047A413() { ((HordeContain *)this)->rva0047A413(); }
public:
	virtual void f00();
public:
	virtual void f20();
public:
	virtual void f11C();
private:
	_STL::vector<BfmeE16> m_vector;
private:
	ObjectID m_trackedLargeUnit;
private:
	int m_31C;
private:
	AODTrackedPosition m_trackedPosition;
private:
	float m_largeUnitHeightFactor;
private:
	float m_largeUnitHeight;
private:
	float m_334;
private:
	Element16 m_arrayA[0x3C];
private:
	int m_6F8;
private:
	Rva0047A702 m_arrayB[0x14];
private:
	int m_8DC;
public:
	void refreshTrackedLargeUnit();
};



extern GameLogic *TheGameLogic;


// ?refreshTrackedLargeUnit@AODHordeContain@@QAEXXZ
void AODHordeContain::refreshTrackedLargeUnit()
{
	Object *unit = TheGameLogic->findObjectByID(m_trackedLargeUnit);
	if (unit == 0)
	{
		m_trackedLargeUnit = INVALID_OBJECT_ID;
		return;
	}

	static_cast<Coord3D &>(m_trackedPosition) = unit->m_cachedPos;
	m_largeUnitHeightFactor = 17.0f;
	m_largeUnitHeight = unit->m_geometry.getMaxHeightAbovePosition();
}
