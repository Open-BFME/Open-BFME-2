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
	m_vtable = reinterpret_cast<void *>(0x00C5F900);
	_ReadWriteBarrier();
	m_commandButton = 0;
	m_upgradeToGive = 0;
	((_STL::bitset<128> *)m_toggleFlags)->reset();
}
