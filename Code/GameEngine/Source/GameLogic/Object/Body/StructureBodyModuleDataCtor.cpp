// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0StructureBodyModuleData@@QAE@XZ, retail 0x00257006, 101 bytes.
// Structure-body module data: the rowed StructureBody pool key at
// 0x4C09B5, the rowed chained proc at 0x2514AF (ActiveBody base plus own
// table), the rowed behavior ctor at 0x4C0951 and the rowed ModuleData
// factory at 0x25708C (ModuleFactory registers StructureBody with it)
// prove the class; the factory sole-calls this ctor. The class derives
// from the canonical ActiveBodyModuleData (rowed ctor 0x004BF59F, virtual
// dtor 0x00256CB0), so the compiler installs retail's 31-slot table
// 0x00BF4028 (slot 7 true from ActiveBodyModuleData, the rest ModuleData's)
// after the base call; the base dtor arms the single EH state. The body is
// the SupplyTruck HealingBuffFx tail verbatim: materialized healing-default
// reference out of TheGlobalData plus inline c_str plus rowed isEmpty
// 0x1E2F plus rowed findFXList 0x1E281A into the base's +0x48 FX pointer
// (StructureBody adds no storage; the factory news ActiveBody's 0x64).

#include "../../../../Include/GameLogic/Module/ActiveBodyModuleData.h"

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../../../Include/Common/GlobalData.h"

extern class GlobalData *TheWritableGlobalData;

class FXList;
#include "../../../../Include/GameClient/FXListStore.h"

extern FXListStore *TheFXListStore;

class StructureBodyModuleData : public ActiveBodyModuleData
{
public:
	StructureBodyModuleData();
	virtual ~StructureBodyModuleData();
};

// ??0StructureBodyModuleData@@QAE@XZ @0x257006
inline StructureBodyModuleData::StructureBodyModuleData()
{
	AsciiString &healingDefault = TheWritableGlobalData->m_defaultStructureRepairBuffFxList;
	if (!reinterpret_cast<const StringBase<char> *>(&healingDefault)->isEmpty())
		field48 = TheFXListStore->findFXList(healingDefault.str());
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeStructureBodyModuleDataInlineAnchor@@YAXPAVStructureBodyModuleData@@@Z absent-from-retail
void _bfmeStructureBodyModuleDataInlineAnchor(StructureBodyModuleData *structureBodyModuleData)
{
    structureBodyModuleData->StructureBodyModuleData::StructureBodyModuleData();
}
#pragma inline_depth()
