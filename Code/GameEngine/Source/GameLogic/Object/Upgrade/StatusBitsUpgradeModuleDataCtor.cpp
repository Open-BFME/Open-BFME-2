// cl: /O1 /MD /GX- /DNDEBUG
// stlport
//
// ??0StatusBitsUpgradeModuleData@@QAE@XZ, retail 0x00254775, 40 bytes.
// Frameless store-only ctor over the rowed OpenContainModuleData base
// (0x253487): folded vtable 0x00BF2558, StatusToSet reset at +0x118 and
// StatusToClear reset at +0x128 through the rowed bitset<128>::reset
// (0x24CA24; own table 0x00857984 holds exactly those two fields; the
// StatusBitsUpgrade pool key at 0x4B48F9 ends where the rowed proc begins;
// the factory at 0x25479D news 0x138 and calls this ctor). The EH ctor at
// 0x2547D1 reuses this body as its base (Transport pattern) under its own
// vtable. Recipe: GiveOrRestoreUpgradeSpecialPowerModuleDataCtor (explicit
// vtable slot, cast-to-bitset reset calls in body order).

#include <bitset>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class OpenContainModuleData
{
public:
	OpenContainModuleData();

protected:
	void *m_vtable; // +0

private:
	unsigned char m_pad[0x118 - 4];
};

class StatusBitsUpgradeModuleData : public OpenContainModuleData
{
public:
	StatusBitsUpgradeModuleData();

private:
	unsigned long m_statusToSet[4]; // +0x118
	unsigned long m_statusToClear[4]; // +0x128
};

// ??0StatusBitsUpgradeModuleData@@QAE@XZ @0x254775
StatusBitsUpgradeModuleData::StatusBitsUpgradeModuleData()
{
	m_vtable = reinterpret_cast<void *>(0x00BF2558);
	((_STL::bitset<128> *)m_statusToSet)->reset();
	((_STL::bitset<128> *)m_statusToClear)->reset();
}
