// cl: /Ireference/shims/bfme2_ascii /MD /Ireference/shims/moduledata
// ??1SlaveWatcherBehaviorModuleData@@UAE@XZ @0x004846FA, 63B.
// Virtual dtor slot evidence: ??_G at 0x004846DE (rowed, slot 0 of vtable
// 0x00C4A298) calls here. Destroys AsciiStrings at +0x0C then +0x08 via
// pinned 0x00036410 then restores base vtable 0x00BBB554 with trivial base
// inlined (no base call). Layout from rowed ctor 0x004846C7 (GrantUpgrade
// +0x08 RemoveUpgrade +0x0C ShareUpgrades +0x10 LetSlaveLive +0x11, factory
// news 0x14) and INI table 0x00C4A208 (GrantUpgrade RemoveUpgrade via
// parseAsciiString). Donor BFME1 SlaveWatcherBehaviorModuleDataConstructor
// dtor. SlavedUpdateModuleDataDtor precedent (novtable suppresses derived
// store).
#include "Common/Snapshot.h"

#include "ascii_string.h"

class __declspec(novtable) SlaveWatcherBehaviorModuleData : public Snapshot
{
public:
	virtual ~SlaveWatcherBehaviorModuleData();

private:
	unsigned char m_pad[0x08 - 4];
	AsciiString m_grantUpgrade; // +0x08
	AsciiString m_removeUpgrade; // +0x0C
	unsigned char m_rest[0x14 - 0x10];
};

SlaveWatcherBehaviorModuleData::~SlaveWatcherBehaviorModuleData()
{
}
