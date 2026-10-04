// cl: /O1 /arch:SSE /MD /DNDEBUG /DWIN32 /D_WINDOWS
// stlport
//
// ??0GiveOrRestoreUpgradeSpecialPowerModuleData@@QAE@XZ, retail 0x004CD0B1,
// 43 bytes. Frameless ctor over the pinned Rva0044EB54 base (0x44EB54):
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
extern "C" void vfn_00065212();
extern "C" void vfn_000B3FD0();
extern "C" void vfn_000B69A1();
extern "C" void vfn_000D43D0();
extern "C" void vfn_0047A699();
extern "C" void vfn_0047A69C();
extern "C" void vfn_004CD2CC();
extern "C" void vfn_0050B5C6();
#pragma comment(linker, "/alternatename:_vfn_00065212=?name@Rva00065212Named@@QBEPBDXZ")
#pragma comment(linker, "/alternatename:_vfn_000B3FD0=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:_vfn_000B69A1=?rva000B69A1@Rva000B69A1@@QAE?AVAsciiString@@H@Z")
#pragma comment(linker, "/alternatename:_vfn_000D43D0=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:_vfn_0047A699=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:_vfn_0047A69C=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:_vfn_004CD2CC=??_GGiveOrRestoreUpgradeSpecialPowerModuleData@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:_vfn_0050B5C6=?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")
extern "C" const void *const vtbl_00C5F900[] = {
	(const void *)&vfn_004CD2CC,
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

#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class Rva0044EB54
{
public:
	Rva0044EB54();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0xC8 - 4];
};

class GiveOrRestoreUpgradeSpecialPowerModuleData : public Rva0044EB54
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
