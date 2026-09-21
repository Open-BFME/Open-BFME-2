// cl: /O1 /arch:SSE /MD /DNDEBUG
//
// ??0SlaveWatcherBehaviorModuleData@@QAE@XZ, retail 0x004846C7,
// 22 bytes. Frameless store-only ctor over table 0xC4A208
// (GrantUpgrade@8, RemoveUpgrade@C, ShareUpgrades@10, LetSlaveLive@11).
// Identity is the table (BFME1 SlaveWatcherBehaviorModuleDataConstructor
// donor carries GrantUpgrade@8/RemoveUpgrade@C at identical offsets;
// BFME2 extends with ShareUpgrades/LetSlaveLive bytes) plus the rowed
// poolkey 0x48462E (SlaveWatcherBehavior) in the same cluster plus
// factory 0x24C660 news 0x14 sole caller plus proc 0x4845BA rowed.
// Shape follows ReflectDamage trivial-ctor precedent: flat TU-local class
// with explicit void*m_vtable (no virtuals, no vtable emission) plus
// plain-data members; body assignments in retail order. Strings are 4B
// zeroed slots, modeled as const char* (BattlePlan precedent). Vtable
// 0x00C4A298 is unique image-wide (single installing site).

class SlaveWatcherBehaviorModuleData
{
public:
	SlaveWatcherBehaviorModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	const char *m_grantUpgrade; // +8
	const char *m_removeUpgrade; // +0xC
	bool m_shareUpgrades; // +0x10
	bool m_letSlaveLive; // +0x11
};

// ??0SlaveWatcherBehaviorModuleData@@QAE@XZ @0x4846C7
SlaveWatcherBehaviorModuleData::SlaveWatcherBehaviorModuleData()
{
	m_vtable = reinterpret_cast<const void *>(0x00C4A298);
	m_grantUpgrade = 0;
	m_removeUpgrade = 0;
	m_shareUpgrades = false;
	m_letSlaveLive = false;
}
