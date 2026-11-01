// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// platformsdk
//
// GettingBuiltBehaviorModuleData ctor shard (retail 0x0045324E, 199 bytes).
// File-unit with GettingBuiltBehaviorModuleDataCtor.cpp (parse proc there).
//
// Retail shape: EH frame with states 5 and 6 which require 6 pre-call
// unwindables. Five are the stored members below (3 ThingRef at +8/+C/+10
// plus 2 AsciiString at +14/+18 all nulled by stores). The sixth lives in
// the ModuleData base, whose inlined constructor leaves +4 untouched.
// Its teardown restores Snapshot's table, as established by the matched dtor.
// Vtable 0xC40090 (DIR32-masked). Floats 60/30/0.25/0.5/0.75/1.0 from pool
// literals. Two AsciiString::set("") via the rowed StringBase set alias pin.
// The +0x40 member builds through the rowed Rva00360D26Member ctor at 0x003623E5
// (twin of Rva003623E5Member) and tears down through the rowed dtor at 0x00360D26.
// Bytes and ints nulled in retail order.

#include <windows.h>
#include "ascii_string.h"
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../../../Include/Common/BfmeModuleData.h"
inline ModuleData::~ModuleData() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }

class RefCountedThing
{
public:
	virtual ~RefCountedThing() {}
	long m_refCount;
};

class ThingRef
{
public:
	ThingRef() : m_ptr(0) {}
	~ThingRef()
	{
		if (m_ptr) {
			if (InterlockedDecrement(&m_ptr->m_refCount) <= 0) {
				delete m_ptr;
			}
		}
	}
private:
	RefCountedThing *m_ptr;
};

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
	Rva00360D26Member();
private:
	long m_val; // +0x00
};

class GettingBuiltBehaviorModuleData : public ModuleData
{
public:
	GettingBuiltBehaviorModuleData();
	virtual ~GettingBuiltBehaviorModuleData();
private:
	int m_pad04;
	ThingRef m_ref08;
	ThingRef m_ref0C;
	ThingRef m_ref10;
	AsciiString m_str14;
	AsciiString m_str18;
	unsigned char m_flag1C;
	float m_width20;
	float m_width24;
	int m_count28;
	unsigned char m_flag2C;
	float m_f30;
	float m_f34;
	float m_f38;
	float m_f3C;
	Rva00360D26Member m_member40;
	float m_f44;
	unsigned char m_flag48;
};

// GettingBuiltBehaviorModuleData::~GettingBuiltBehaviorModuleData: defined in GettingBuiltBehaviorModuleDataDtor.cpp (its row's unit).

// ??0GettingBuiltBehaviorModuleData@@QAE@XZ @0x0045324E
GettingBuiltBehaviorModuleData::GettingBuiltBehaviorModuleData()
	: m_ref08()
	, m_ref0C()
	, m_ref10()
	, m_str14()
	, m_str18()
	, m_width24(60.0f)
	, m_count28(0)
	, m_member40()
{
	m_f44 = 0.0f;
	m_flag48 = 0;
	m_str14.set("");
	m_str18.set("");
	m_width20 = 30.0f;
	m_f30 = 0.25f;
	m_f34 = 0.5f;
	m_f38 = 0.75f;
	m_flag2C = 0;
	m_flag1C = 0;
	m_f3C = 1.0f;
}
