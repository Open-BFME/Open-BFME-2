// cl: /O1 /MD -D_STLP_NO_EXCEPTIONS /EHs-c-
// Identity: ModuleFactory registers this data class under "WeaponSetUpgrade" (addModule
// pairs the name with its factory); formerly misnamed HealContain/HealContainModuleData.
// stlport
//
// ??0WeaponSetUpgradeModuleData@@QAE@XZ, retail
// 0x004B57AA (36 bytes). Dedicated thunk TU: the defining class TU does
// not exist in this tree. Direct base per ZH WeaponSetUpgrade.h is
// OpenContainModuleData (pinned ctor at 0x253487); its vtable folds with
// the derived one at retail (both install 0xBF2558), so the base view
// carries virtuals only for layout. The flag word at +0x118 resets
// through the ledger-known bitset<8>::reset body (explicitly specialized
// non-inline, as retail calls it) and sets bit 3.

#include <bitset>
#include <string.h>

namespace _STL {
template<> bitset<128> &bitset<128>::reset();
}

class OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();

	unsigned char _pad[0x114];
};

class WeaponSetUpgradeModuleData : public OpenContainModuleData
{
public:
	WeaponSetUpgradeModuleData();

	// bitset<128> storage as plain words: retail constructs the member
	// trivially and calls the out-of-line reset body, and sets bit 3
	// of the first word.
	unsigned long m_flagsWord[4];
};

WeaponSetUpgradeModuleData::WeaponSetUpgradeModuleData() : OpenContainModuleData()
{
	((_STL::bitset<128> *)m_flagsWord)->reset();
	// Bit 3 set: our headers emit bitset<128>::set(3) as an out-of-line
	// call, while retail inlines it to or-dword-8; the flag spelling is
	// behavior-identical.
	m_flagsWord[0] |= 8;
}
