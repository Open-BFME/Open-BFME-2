// cl: /O1 /DNDEBUG /MD
// ??0CaveContainModuleData@@QAE@XZ, retail RVA 0x00466D37 (25 bytes).
// The canonical base occupies 0x98 bytes; the CaveIndex parse entry at
// VA 0x00BEEAC8 identifies the following four-byte m_caveIndexData member.
// Retail clears that member before installing VA 0x00C43F40. Normal
// inheritance lets the compiler emit that vtable relocation and store.
#include "../../../../Include/GameLogic/Module/OpenContainModuleData.h"

#include "../../../../Include/Common/CaveContainModuleData.h"

inline CaveContainModuleData::CaveContainModuleData()
{
	m_caveIndexData = 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeCaveContainModuleDataInlineAnchor@@YAXPAVCaveContainModuleData@@@Z absent-from-retail
void _bfmeCaveContainModuleDataInlineAnchor(CaveContainModuleData *caveContainModuleData)
{
    caveContainModuleData->CaveContainModuleData::CaveContainModuleData();
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0HealContainModuleData@@QAE@XZ=??0CaveContainModuleData@@QAE@XZ")
