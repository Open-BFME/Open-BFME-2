// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /DNDEBUG /MD
//
// ??1RebuildHoleBehaviorModuleData@@UAE@XZ, retail 0x0048334A, 48 bytes.
// RebuildHole ModuleData dtor over the pinned base vtable 0x00BBB554: destroys
// the AsciiString at +0x10 via the folded StringBase dtor at 0x00036410,
// then restores the Snapshot base vtable. Layout from the rowed ctor
// 0x0048323E (base 0x10 plus WorkerRespawnDelay +0x08 plus HoleHealth +0x0C
// plus WorkerObjectName +0x10, factory 0x0024C433 news 0x14, vtable
// 0x00C49950) plus parse table 0x00C49A10. Shape follows
// AIUpdateModuleDataDtor (single member plus BBB554 base, no -1). Caller is
// the audited ??_G at 0x0048332E (slot 0 of vtable 0x00C49950).
#include "Common/Snapshot.h"

#include "ascii_string.h"

class __declspec(novtable) RebuildHoleBehaviorModuleData : public Snapshot
{
public:
	virtual ~RebuildHoleBehaviorModuleData();

private:
	int m_unused04;
	float m_workerRespawnDelay;
	float m_holeHealthRegen;
	AsciiString m_workerObjectName;
};

RebuildHoleBehaviorModuleData::~RebuildHoleBehaviorModuleData()
{
}
