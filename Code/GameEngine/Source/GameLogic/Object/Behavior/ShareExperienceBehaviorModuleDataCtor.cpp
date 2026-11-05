// cl: /Ireference/shims/moduledata /GX /MD /DNDEBUG
//
// ??0ShareExperienceBehaviorModuleData@@QAE@XZ, retail 0x0047FE90, 76 bytes.
// Framed single-state EH ctor: zero floats at +8/+0xC, pool float 1.0f at
// +0x10, folded vtable 0x00C486B0, filter member at +0x14 through the
// pinned nullary filter (0x3623E5, Rva003623E5Filter spelling), unknown
// dword at +4 kept as explicit pad. Own table 0x00C48740 holds Radius/
// DropOff/Percentage/ObjectFilter; the ShareExperienceBehavior pool key at
// 0x47FE4B ends near the rowed proc; the factory at 0x24BFE5 news 0x18
// and calls this ctor as sole caller; the rowed proc at 0x47FEDC starts
// where this ctor ends. Recipe: GeometryUpgrade (virtual mid-init vtable
// placement) with the native Snapshot base teardown arming the
// single EH state. Native cleanup78B925 restores Snapshot through49B47C;
// the polymorphic base shares the derived vptr and has no this-adjust.
// The companion48B destructor independently restores the same BBB554 table.

#include "Common/Snapshot.h"
#include <new>

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();

private:
	unsigned char m_data[4];
};

class ShareExperienceBehaviorModuleDataBase
{
public:
	virtual ~ShareExperienceBehaviorModuleDataBase() { reinterpret_cast<Snapshot *>(this)->Snapshot::~Snapshot(); }
};

class ShareExperienceBehaviorModuleData : public ShareExperienceBehaviorModuleDataBase
{
public:
	ShareExperienceBehaviorModuleData();
	virtual ~ShareExperienceBehaviorModuleData();

private:
	unsigned char m_pad04[4]; // +4
	float m_radius; // +8
	float m_dropOff; // +0xC
	float m_percentage; // +0x10
	Rva003623E5Filter m_objectFilter; // +0x14
};

// ??0ShareExperienceBehaviorModuleData@@QAE@XZ @0x47FE90
inline ShareExperienceBehaviorModuleData::ShareExperienceBehaviorModuleData()
	: m_radius(0.0f), m_dropOff(0.0f), m_percentage(1.0f)
{
}

// ?constructShareExperienceBehaviorModuleDataCtor absent-from-retail
void constructShareExperienceBehaviorModuleDataCtor(void *storage)
{
    ::new (storage) ShareExperienceBehaviorModuleData;
}
