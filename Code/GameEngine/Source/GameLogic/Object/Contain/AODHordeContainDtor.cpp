// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1AODHordeContain@@UAE@XZ, retail 0x0047B563, 197 bytes.
// Slot evidence: ??_G at 0x0047B674 (ContainModuleDeletingDtors) calls here.
// Restores 11 vptrs (+0x00 +0x0C +0x10 +0x20 +0x24 +0x28 +0x2C +0x30 +0x34
// +0xFC +0x11C) then destroys vector at +0x30C (free via 0x00030830, state 0)
// plus 60 x 0x10 array at +0x338 and 20 x 0x18 array at +0x6FC through ehvec
// 0x00629110 (states 1-2, empty element dtors DIR32-masked to retail 0x4B3FD0)
// then calls pinned ??1HordeContain@@UAE@XZ at 0x0046F901. Layout from the
// rowed ctor 0x0047B3DB in AODHordeContainCtor.cpp (vector plus two-array
// concept from BFME1 AODHordeContainDestructors.cpp; BFME2 offsets +0x30C /
// +0x338 / +0x6FC, factory news 0x8E0). Identity is the ModuleFactory
// AODHordeContain registration plus the audited deleting-dtor caller.
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
struct Iface11C { virtual void f11C() = 0; unsigned char m_pad[0x30C - 0x11C - 4]; };

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
	virtual ~HordeContain();
	virtual void rva00470DC1();
};

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"

struct AODDtorElem16
{
	~AODDtorElem16();
	float m_f[4];
};

// ??1AODDtorElem16@@QAE@XZ present-unmatched
inline AODDtorElem16::~AODDtorElem16()
{
}

struct AODDtorElem24
{
	~AODDtorElem24();
	float m_f[5];
	unsigned char m_b;
	unsigned char m_pad[3];
};

// ??1AODDtorElem24@@QAE@XZ present-unmatched
inline AODDtorElem24::~AODDtorElem24()
{
}

class AODHordeContain : public HordeContain
{
public:
	virtual ~AODHordeContain();
	// Same virtual list as AODHordeContainCtor.cpp, so both units emit the same vftables.
	virtual void f00();
	virtual void f20();
	virtual void f11C();

private:
	_STL::vector<BfmeE16> m_vector;
	int m_318;
	int m_31C;
	float m_320[3];
	float m_32C;
	float m_330;
	float m_334;
	AODDtorElem16 m_arrayA[0x3C];
	int m_6F8;
	AODDtorElem24 m_arrayB[0x14];
	int m_8DC;
};

// ??1AODHordeContain@@UAE@XZ
AODHordeContain::~AODHordeContain()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
