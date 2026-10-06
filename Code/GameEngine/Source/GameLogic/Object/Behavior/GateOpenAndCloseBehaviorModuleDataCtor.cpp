// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0GateOpenAndCloseBehaviorModuleData@@QAE@XZ, retail 0x00498E2E, 280 bytes.
// GateOpenAndClose data ctor over INI table 0x00BF19F8 (OpenByDefault at +8
// ResetTime at +0xC PercentOpen at +0x10 Proxy at +0x14 Repel at +0x18
// GeometryForOpen at +0x2C GeometryForClosed at +0x38; factory 0x253F1F news
// 0x4C sole caller plus GateProxy base 0x24E359). Donor is BFME1
// GateOpenAndCloseBehaviorModuleData ctor thunk. Layout from rowed dtor
// 0x00498D46 (AsciiString at +0x14 four ref holders at +0x1C..+0x28 vectors at
// +0x2C/+0x38) plus snap ints at +0x44/+0x48 from global 0x00DCB4CC.
// Empty Snapshot base with declared dtor arms EH 0 plus proxy plus four refs
// plus two vectors arm 1-7 so temps arm 8-9-10 matching retail 7-8-9-10.
// Recipe is ProductionSpeedBonus plus SpecialPowerModuleData ref-holder idiom.

// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <vector>

#include "ascii_string.h"

extern const void *const g_00BBB554[];
extern int g_00DCB4CC;
// g_00DCB4CC: matched references place it at VA 0xdcb4cc (retail .data initial value -1).
int g_00DCB4CC = -1;

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class GateRefHolder
{
public:
	GateRefHolder() : m_ptr(0) {}
	~GateRefHolder() { if (m_ptr) m_ptr->Release_Ref(); }

private:
	OpaqueRefCounted *m_ptr;
};

class Snapshot
{
public:
	Snapshot() {}
	~Snapshot()
	{
		*(const void **)this = g_00BBB554;
	}
};

class GateOpenAndCloseBehaviorModuleData : public Snapshot
{
public:
	GateOpenAndCloseBehaviorModuleData();
	virtual ~GateOpenAndCloseBehaviorModuleData();

private:
	int m_unused04; // +4 untouched padding
	bool m_openByDefault; // +8
	unsigned char m_pad09[3];
	int m_resetTime; // +0xC
	int m_percentOpen; // +0x10
	AsciiString m_proxy; // +0x14
	bool m_repel; // +0x18
	unsigned char m_pad19[3];
	GateRefHolder m_ref1C; // +0x1C
	GateRefHolder m_ref20; // +0x20
	GateRefHolder m_ref24; // +0x24
	GateRefHolder m_ref28; // +0x28
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_geometryForOpen; // +0x2C
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > m_geometryForClosed; // +0x38
	int m_snap44; // +0x44
	int m_snap48; // +0x48
};

// ??0GateOpenAndCloseBehaviorModuleData@@QAE@XZ @0x00498E2E
GateOpenAndCloseBehaviorModuleData::GateOpenAndCloseBehaviorModuleData()
	: Snapshot()
	, m_proxy()
	, m_ref1C()
	, m_ref20()
	, m_ref24()
	, m_ref28()
{
	m_openByDefault = false;
	m_resetTime = 50;
	m_percentOpen = 50;
	m_proxy.clear();
	m_repel = true;
	AsciiString openLeft("OpenLeft");
	AsciiString openRight("OpenRight");
	AsciiString closed("Closed");
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > &vecOpen = m_geometryForOpen;
	vecOpen.erase(vecOpen.begin(), vecOpen.end());
	vecOpen.push_back(openLeft);
	vecOpen.push_back(openRight);
	_STL::vector<AsciiString, _STL::allocator<AsciiString> > &vecClosed = m_geometryForClosed;
	vecClosed.erase(vecClosed.begin(), vecClosed.end());
	vecClosed.push_back(closed);
	int snap = g_00DCB4CC;
	m_snap44 = snap;
	m_snap48 = snap;
}
