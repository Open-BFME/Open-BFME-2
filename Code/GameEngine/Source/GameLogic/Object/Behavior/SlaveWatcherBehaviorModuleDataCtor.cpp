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

// Retail VA 0x00C4A298 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_004846DE();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_004846DE=??_GSlaveWatcherBehaviorModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C4A298[] = {
	(const void *)&vfn_004846DE,
	(const void *)&vfn_000B3FD0,
	(const void *)&vfn_00065212,
	(const void *)&vfn_0047A69C,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000B69A1,
	(const void *)&vfn_0047A699,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_000D43D0,
	(const void *)&vfn_0050B5C6
};

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
	m_vtable = reinterpret_cast<const void *>(((unsigned int)vtbl_00C4A298));
	m_grantUpgrade = 0;
	m_removeUpgrade = 0;
	m_shareUpgrades = false;
	m_letSlaveLive = false;
}
