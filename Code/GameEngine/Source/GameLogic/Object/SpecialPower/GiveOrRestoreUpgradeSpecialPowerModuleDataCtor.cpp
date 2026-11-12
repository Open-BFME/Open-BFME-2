// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0GiveOrRestoreUpgradeSpecialPowerModuleData@@QAE@XZ, retail 0x004CD0B1,
// 43 bytes. Frameless ctor over the pinned SpecialAbilityUpdateModuleData base (0x44EB54):
// vtable literal 0x00C5F900, CommandButton 0 at +0xC8, UpgradeToGive 0 at
// +0xCC, FlagsUsedForToggle bitset reset at +0xD0 (own table 0x0085F8C0 all
// three fields; the GiveOrRestoreUpgradeSpecialPower pool key at 0x4CD14B
// sits in the same cluster). The TU-local base keeps an explicit vtable
// slot (DestroyEnvironment precedent, so no vtable is emitted) and the
// integer zeros use the compact and form under /O1; the toggle mask resets
// through the ledger-known bitset<8>::reset body (rowed at 0x24CA24,
// GrantUpgradeCreate precedent).

// Retail VA 0x00C5F900 (.rdata): a 31-slot vftable no unit emits. Defined here as
// data with retail's slot pointers, each bound to the ledger name at its
// target (tools/vftable_map.py); its installers store this table.
extern "C" void __identifier("?GetSnapshotName@ModuleData@@UBEPBDXZ")();
extern "C" void __identifier("??1Coord2D@@QAE@XZ")();
extern "C" void __identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z")();
extern "C" void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
extern "C" void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
extern "C" void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
extern "C" void __identifier("??_GGiveOrRestoreUpgradeSpecialPowerModuleData@@UAEPAXI@Z")();
extern "C" void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
extern "C" const void *const vtbl_00C5F900[] = {
	(const void *)&__identifier("??_GGiveOrRestoreUpgradeSpecialPowerModuleData@@UAEPAXI@Z"),
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
	(const void *)&__identifier("?slot14@ModuleData@@UBE?AVAsciiString@@H@Z"),
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

#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class SpecialAbilityUpdateModuleData
{
public:
	SpecialAbilityUpdateModuleData();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0xC8 - 4];
};

class GiveOrRestoreUpgradeSpecialPowerModuleData : public SpecialAbilityUpdateModuleData
{
public:
	GiveOrRestoreUpgradeSpecialPowerModuleData();

private:
	int m_commandButton; // +0xC8
	int m_upgradeToGive; // +0xCC
	unsigned long m_toggleFlags[4]; // +0xD0
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ??0GiveOrRestoreUpgradeSpecialPowerModuleData@@QAE@XZ @0x4CD0B1
GiveOrRestoreUpgradeSpecialPowerModuleData::GiveOrRestoreUpgradeSpecialPowerModuleData()
{
	m_vtable = reinterpret_cast<void *>(((unsigned int)vtbl_00C5F900));
	_ReadWriteBarrier();
	m_commandButton = 0;
	m_upgradeToGive = 0;
	((_STL::bitset<128> *)m_toggleFlags)->reset();
}
