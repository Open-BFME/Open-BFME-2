char g_00BF4028;

// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0StructureBodyModuleData@@QAE@XZ, retail 0x00257006, 101 bytes.
// Structure-body module data: the rowed StructureBody pool key at
// 0x4C09B5, the rowed chained proc at 0x2514AF (ActiveBody base plus own
// table), the rowed behavior ctor at 0x4C0951 and the rowed ModuleData
// factory at 0x25708C (ModuleFactory registers StructureBody with it)
// prove the class; the factory sole-calls this ctor. Shape follows the
// ChinookAIUpdate precedent (opaque empty ActiveBody base through the
// rowed 0x4BF59F spelling, explicit vtable first member) with the
// SupplyTruck HealingBuffFx tail verbatim: materialized healing-default
// reference out of TheGlobalData plus inline c_str plus rowed isEmpty
// 0x1E2F plus rowed findFXList 0x1E281A. The empty base carries a
// declared-only dtor so single-state EH arms with zero code (Topple
// precedent); the base leaves +0x48 alone so no zero store precedes the
// guarded fill.

#include "../../../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "../../../../Include/Common/GlobalData.h"

extern class GlobalData *TheWritableGlobalData;

class FXList;
#include "../../../../Include/GameClient/FXListStore.h"

extern FXListStore *TheFXListStore;

class ActiveBodyModuleData
{
public:
	ActiveBodyModuleData();
	virtual ~ActiveBodyModuleData(); // virtual, as rowed (0x00256CB0)
};

class __declspec(novtable) StructureBodyModuleData : public ActiveBodyModuleData
{
public:
	StructureBodyModuleData();

private:
	unsigned char m_pad[0x48 - 4]; // +4
	const FXList *m_healingBuffFx; // +0x48
};

// ??0StructureBodyModuleData@@QAE@XZ @0x257006
inline StructureBodyModuleData::StructureBodyModuleData()
{
	*(const void **)this = reinterpret_cast<const void *>((unsigned int)&g_00BF4028);
	AsciiString &healingDefault = TheWritableGlobalData->m_defaultStructureRepairBuffFxList;
	if (!reinterpret_cast<const StringBase<char> *>(&healingDefault)->isEmpty())
		m_healingBuffFx = TheFXListStore->findFXList(healingDefault.str());
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
