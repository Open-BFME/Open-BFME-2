// cl: /O1 /MD /GX /DNDEBUG
//
// ??0RadarUpgradeModuleData@@QAE@XZ, retail 0x002546D2, 25 bytes.
// Frameless store-only ctor over the rowed Rva00253487Base base
// (0x253487): folded vtable 0x00BF2558, DisableProof false at +0x118 (own
// table 0x008578D0 holds exactly DisableProof at +0x118; the RadarUpgrade
// pool key at 0x4B4727 ends where the rowed proc begins; the ModuleData
// factory at 0x254741 news 0x11C and is one of two raw callers). The second
// raw caller is the KillLocomotorUpgrade factory at 0x25470D (proc 0x2546EB
// with the single-field KillLocomotorUpgrade table at +0x118): the two
// single-bool@118 ctors are ICF-folded to this one address, and this row
// proves the body while the KillLocomotor side shares the fold (Defector
// precedent). Recipe: ReflectDamageModuleDataCtor (flat TU-local class,
// explicit vtable slot, no virtuals emitted).

extern "C" const void *const __identifier("??_7WeaponSetUpgradeModuleData@@6B@")[];  // vftable 0x00BF2558

#include "../../../../Include/GameLogic/Module/Rva00253487Base.h"

class __declspec(novtable) RadarUpgradeModuleData : public Rva00253487Base
{
public:
	RadarUpgradeModuleData();

private:
	bool m_disableProof; // +0x118
};

// ??0RadarUpgradeModuleData@@QAE@XZ @0x2546D2
inline RadarUpgradeModuleData::RadarUpgradeModuleData()
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7WeaponSetUpgradeModuleData@@6B@"));
	m_disableProof = false;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRadarUpgradeModuleDataInlineAnchor@@YAXPAVRadarUpgradeModuleData@@@Z absent-from-retail
void _bfmeRadarUpgradeModuleDataInlineAnchor(RadarUpgradeModuleData *radarUpgradeModuleData)
{
    radarUpgradeModuleData->RadarUpgradeModuleData::RadarUpgradeModuleData();
}
#pragma inline_depth()
