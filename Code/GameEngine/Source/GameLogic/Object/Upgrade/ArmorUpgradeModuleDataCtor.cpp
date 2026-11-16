// cl: /MD /GX /DNDEBUG
//
// ??0ArmorUpgradeModuleData@@QAE@XZ, retail 0x00254556, 42 bytes.
// Frameless store-only ctor over the rowed Rva00253487Base base
// (0x253487): folded vtable 0x00BF2558 (shared with RadarUpgrade, Defector
// precedent for ICF-folded vtables), KillArmorUpgrade false at +0x118,
// IgnoreArmorUpgrade false at +0x119, ArmorSetFlag 3 at +0x11C (own table
// 0x00DBA870 holds exactly these three fields; all three vote one BFME1
// class in field_names; the ModuleData factory at 0x2545DB news 0x120 and
// is the sole raw caller). Recipe: ReflectDamageModuleDataCtor (flat
// TU-local class, explicit vtable slot, no virtuals emitted).

extern "C" const void *const __identifier("??_7WeaponSetUpgradeModuleData@@6B@")[];  // vftable 0x00BF2558

#include "../../../../Include/GameLogic/Module/Rva00253487Base.h"

class __declspec(novtable) ArmorUpgradeModuleData : public Rva00253487Base
{
public:
	ArmorUpgradeModuleData();

private:
	bool m_killArmorUpgrade; // +0x118
	bool m_ignoreArmorUpgrade; // +0x119
	// +0x11A..0x11B pad
	int m_armorSetFlag; // +0x11C
};

// ??0ArmorUpgradeModuleData@@QAE@XZ @0x254556
ArmorUpgradeModuleData::ArmorUpgradeModuleData()
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7WeaponSetUpgradeModuleData@@6B@"));
	m_killArmorUpgrade = false;
	m_ignoreArmorUpgrade = false;
	m_armorSetFlag = 3;
}
