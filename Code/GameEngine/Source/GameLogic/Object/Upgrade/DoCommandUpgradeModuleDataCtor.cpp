// cl: /O1 /MD /GX /DNDEBUG
//
// ??0DoCommandUpgradeModuleData@@QAE@XZ, retail 0x00255795, 30 bytes.
// Frameless store-only ctor over the rowed Rva00253487Base base
// (0x253487): folded vtable 0x00BF3840, GetUpgradeCommandButtonName zero at
// +0x118 plus RemoveUpgradeCommandButtonName zero at +0x11C (compact and
// forms; own table 0x00857BC4 holds exactly those two fields; the
// DoCommandUpgrade pool key at 0x4B4BF1 ends where the rowed proc begins;
// the ModuleData factory at 0x2557B5 news 0x120 and is the only raw
// caller). Recipe: AttributeModifierUpgradeModuleDataCtor (flat TU-local
// class with explicit vtable slot plus _ReadWriteBarrier pinning the
// and-stores below the vtable store).

extern "C" const void *const __identifier("??_7TooltipUpgradeModuleData@@6B@")[];  // vftable 0x00BF3840

#include "../../../../Include/GameLogic/Module/Rva00253487Base.h"

class __declspec(novtable) DoCommandUpgradeModuleData : public Rva00253487Base
{
public:
	DoCommandUpgradeModuleData();

private:
	int m_getUpgradeCommandButtonName; // +0x118
	int m_removeUpgradeCommandButtonName; // +0x11C
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ??0DoCommandUpgradeModuleData@@QAE@XZ @0x255795
inline DoCommandUpgradeModuleData::DoCommandUpgradeModuleData()
{
	*(unsigned int *)this = ((unsigned int)__identifier("??_7TooltipUpgradeModuleData@@6B@"));
	_ReadWriteBarrier();
	m_getUpgradeCommandButtonName = 0;
	m_removeUpgradeCommandButtonName = 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeDoCommandUpgradeModuleDataInlineAnchor@@YAXPAVDoCommandUpgradeModuleData@@@Z absent-from-retail
void _bfmeDoCommandUpgradeModuleDataInlineAnchor(DoCommandUpgradeModuleData *doCommandUpgradeModuleData)
{
    doCommandUpgradeModuleData->DoCommandUpgradeModuleData::DoCommandUpgradeModuleData();
}
#pragma inline_depth()
