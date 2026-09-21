// cl: /O1 /MD /DNDEBUG
// Identity: ModuleFactory registers this data class under "MonitorConditionUpdate" (addModule
// pairs the name with this factory); formerly misnamed ModelConditionSpecialAbilityUpdateModuleData.
// stlport

// ??0MonitorConditionUpdateModuleData@@QAE@XZ,
// retail 0x004915FD, 54 bytes. Frameless ctor over table 0xC4DA00
// (ModelConditionFlags@8, ModelConditionCommandSet@54, WeaponSetFlags@58,
// WeaponToggleCommandSet@68). Identity is the table plus the
// ModelConditionSpecialAbilityUpdate poolkey 0x490DC0 in the same cluster
// plus factory 0x24D849 news 0x6C sole caller plus proc 0x4915B5 rowed
// plus the BFME1 MonitorConditionUpdateModuleData donor.
// Shape follows Dozer precedent: pointer-cast vtable body store plus
// init-list member construction (setup hoists above the store) plus
// bitset<128> reset through the rowed 0x24CA24 plus CRT memset.

#include <bitset>
#include <string.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class Rva0042526Member
{
public:
	Rva0042526Member();

private:
	unsigned char m_pad[0x4C];
};

class MonitorConditionUpdateModuleData
{
public:
	MonitorConditionUpdateModuleData();

private:
	const void *m_vtable; // +0
	unsigned int m_unused04; // +4
	Rva0042526Member m_modelConditionFlags; // +8
	const char *m_modelConditionCommandSet; // +0x54
	unsigned long m_weaponSetFlags[4]; // +0x58
	const char *m_weaponToggleCommandSet; // +0x68
};

// ??0MonitorConditionUpdateModuleData@@QAE@XZ @0x4915FD
MonitorConditionUpdateModuleData::MonitorConditionUpdateModuleData()
	: m_vtable(reinterpret_cast<const void *>(0x00C4DA50))
	, m_modelConditionFlags()
{
	m_modelConditionCommandSet = 0;
	((_STL::bitset<128> *)m_weaponSetFlags)->reset();
	m_weaponToggleCommandSet = 0;
	memset(m_weaponSetFlags, 0, 0x10);
}
