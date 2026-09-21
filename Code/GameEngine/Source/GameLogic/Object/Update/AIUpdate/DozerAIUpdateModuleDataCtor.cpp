// cl: /O1 /MD /EHs-c-
// Identity: ModuleFactory registers this data class under "WeaponModeSpecialPowerUpdate" (addModule
// pairs the name with its factory); formerly misnamed DozerAIUpdate/DozerAIUpdateModuleData.
// stlport

// ??0WeaponModeSpecialPowerUpdateModuleData@@QAE@XZ, retail 0x00494D26 (58 bytes).
// Frameless ctor over the pinned AIUpdateModuleData base (0x58925D): the
// derived vtable 0x00C4EA88 is a pointer-cast body store first (Defector
// precedent for frameless plus non-empty base, so the store is a body store
// in place instead of a compiler-scheduled virtual install), then two AND
// zeros at +0x18/+0x1C, the bitset at +0x24 reset through the ledger-known
// bitset<128>::reset body (rowed at 0x24CA24, GrantUpgrade precedent), the
// count at +0x20 set to 5, and the bitset cleared via CRT memset (import
// thunk 0x6291AE). Base is 0x18 bytes per the derived offsets.

#include <bitset>
#include <string.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class AIUpdateModuleData
{
public:
	AIUpdateModuleData();
	virtual ~AIUpdateModuleData();

private:
	unsigned char m_pad[0x18 - 4];
};

class WeaponModeSpecialPowerUpdateModuleData : public AIUpdateModuleData
{
public:
	WeaponModeSpecialPowerUpdateModuleData();

private:
	int m_18;					// +0x18
	int m_1C;					// +0x1C
	int m_count;				// +0x20
	unsigned long m_bits[4];	// +0x24
};

WeaponModeSpecialPowerUpdateModuleData::WeaponModeSpecialPowerUpdateModuleData()
{
	*(unsigned int *)this = 0x00C4EA88;
	_ReadWriteBarrier();
	m_18 = 0;
	m_1C = 0;
	m_count = 5;
	((_STL::bitset<128> *)m_bits)->reset();
	memset(m_bits, 0, 0x10);
}
