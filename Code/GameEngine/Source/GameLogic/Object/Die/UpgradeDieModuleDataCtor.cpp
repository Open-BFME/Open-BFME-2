// cl: /O1 /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0UpgradeDieModuleData@@QAE@XZ, retail 0x002550ED, 22 bytes.
// Frameless ctor over the canonical DestroyDieModuleData base (rowed ctor
// 0x253510, whose 12 ctor-position callers include this body at 0x2550F0):
// base call, the compiler's store of retail's 31-slot table 0x00BF33C0
// (ModuleData's slots; DestroyDieModuleData adds none), then the compact
// and-zero of the UpgradeToRemove name word at +0x38 (the rowed
// buildFieldParse table 0x00BF0958 holds UpgradeToRemove at +0x38, and
// BFME1's UpgradeDieModuleDataCtorThunk donor models the same word as the
// AsciiString m_upgradeName data with m_data(0) inline init); writing it
// through a pointer keeps the vptr store ahead of it, as retail schedules
// it (a plain member store sinks the vptr store below). Size 0x3C
// matches the 0x255103 factory news. Class identity is the field_names vote
// (1/1: UpgradeToRemove belongs to UpgradeDieModuleData) plus the rowed
// UpgradeDie pool key (0x486B75) in this family.

#include "../../../../Include/GameLogic/Module/DestroyDieModuleData.h"

class UpgradeDieModuleData : public DestroyDieModuleData
{
public:
	UpgradeDieModuleData();
	virtual ~UpgradeDieModuleData();

private:
	int m_upgradeName; // +0x38 (AsciiString data word; BFME1 m_upgradeName)
};

// ??0UpgradeDieModuleData@@QAE@XZ @0x2550ED
inline UpgradeDieModuleData::UpgradeDieModuleData()
{
	int *upgradeName = &m_upgradeName;
	*upgradeName = 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeUpgradeDieModuleDataInlineAnchor@@YAXPAVUpgradeDieModuleData@@@Z absent-from-retail
void _bfmeUpgradeDieModuleDataInlineAnchor(UpgradeDieModuleData *upgradeDieModuleData)
{
    upgradeDieModuleData->UpgradeDieModuleData::UpgradeDieModuleData();
}
#pragma inline_depth()
