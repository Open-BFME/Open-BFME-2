// cl: /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
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
#include "ascii_string.h"
#include "Common/Snapshot.h"

// INI table 0x00C4A208 parses GrantUpgrade (+0x08), RemoveUpgrade (+0x0C),
// ShareUpgrades (+0x10) and LetSlaveLive (+0x11). Until the ModuleData chain
// carries its own 31-slot table, the dead +0x04 slot installs retail's
// 0x00C4A298 ahead of the strings (the ctor 0x004846C7 stores it first), and
// the dtor (0x004846FA) only restores Snapshot's 0x00BBB554, hence novtable.
extern "C" const void *const vtbl_00C4A298[];

class SlaveWatcherBehaviorModuleDataTable
{
public:
	SlaveWatcherBehaviorModuleDataTable(void *owner) { *(const void *const **)owner = vtbl_00C4A298; }

private:
	unsigned char m_unused[4];
};

class __declspec(novtable) SlaveWatcherBehaviorModuleData : public Snapshot
{
public:
	SlaveWatcherBehaviorModuleData();
	virtual ~SlaveWatcherBehaviorModuleData();

	SlaveWatcherBehaviorModuleDataTable m_table; // +0x04
	AsciiString m_grantUpgrade; // +0x08
	AsciiString m_removeUpgrade; // +0x0C
	bool m_shareUpgrades; // +0x10
	bool m_letSlaveLive; // +0x11
};

SlaveWatcherBehaviorModuleData::~SlaveWatcherBehaviorModuleData()
{
}
