// cl: /DNDEBUG /MD /GX /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
//
// ??0SlaveWatcherBehaviorModuleData@@QAE@XZ, retail 0x004846C7,
// 22 bytes. Frameless store-only ctor over table 0xC4A208
// (GrantUpgrade@8, RemoveUpgrade@C, ShareUpgrades@10, LetSlaveLive@11).
// Identity is the table (BFME1 SlaveWatcherBehaviorModuleDataConstructor
// donor carries GrantUpgrade@8/RemoveUpgrade@C at identical offsets;
// BFME2 extends with ShareUpgrades/LetSlaveLive bytes) plus the rowed
// poolkey 0x48462E (SlaveWatcherBehavior) in the same cluster plus
// factory 0x24C660 news 0x14 sole caller plus proc 0x4845BA rowed.
// The class view is the one SlaveWatcherBehavior.cpp declares: the novtable
// Snapshot-derived data with AsciiString members, whose +0x04 member stores
// vtable 0x00C4A298 (unique image-wide, single installing site) before the
// strings construct.

// Retail VA 0x00C4A298 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
extern "C" void __identifier("??1Coord2D@@QAE@XZ")();
extern "C" void __identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")();
extern "C" void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
extern "C" void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
extern "C" void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
extern "C" void __identifier("??_GSlaveWatcherBehaviorModuleData@@UAEPAXI@Z")();
extern "C" void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
extern "C" const void *const vtbl_00C4A298[] = {
	(const void *)&__identifier("??_GSlaveWatcherBehaviorModuleData@@UAEPAXI@Z"),
	(const void *)&__identifier("??1Coord2D@@QAE@XZ"),
	(const void *)&__identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ"),
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z"),
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"),
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
};

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

// ??0SlaveWatcherBehaviorModuleData@@QAE@XZ @0x4846C7
SlaveWatcherBehaviorModuleData::SlaveWatcherBehaviorModuleData()
	: m_table(this)
{
	m_shareUpgrades = false;
	m_letSlaveLive = false;
}
