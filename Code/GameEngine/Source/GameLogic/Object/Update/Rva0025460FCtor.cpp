// cl: /MD /GX /DNDEBUG
//
// ??0Rva0025460F@@QAE@XZ, retail 0x0025460F, 25 bytes.
// Frameless store-only ctor over the rowed Rva00253487Base base
// (0x253487): folded vtable 0x00BF2558, int 0 at +0x118 via and dword.
// Evidence: caller at 0x0025465C; neighbours AutoDeposit friend_new and
// LevelUpUpgrade ctor; same 25B pattern as RadarUpgradeModuleDataCtor
// (0x002546D2) but int at +0x118 not bool; member stored before vtable. Recipe: Radar precedent
// (flat TU-local class, explicit vtable slot, no virtuals emitted).
extern "C" const void *const __identifier("??_7WeaponSetUpgradeModuleData@@6B@")[];  // vftable 0x00BF2558

#include "../../../../Include/GameLogic/Module/Rva00253487Base.h"

class __declspec(novtable) Rva0025460F : public Rva00253487Base
{
public:
	Rva0025460F();

private:
	int m_unk118; // +0x118
};
Rva0025460F::Rva0025460F()
{
	m_unk118 = 0;
	*(unsigned int *)this = ((unsigned int)__identifier("??_7WeaponSetUpgradeModuleData@@6B@"));
}
