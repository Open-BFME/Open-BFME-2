// cl: /GX /Oy- /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1StructureBodyModuleData@@UAE@XZ, retail 0x00257087, 5 bytes.
// Virtual dtor over vtable 0x007F4028 (slot 0 deleting dtor at 0x0025706B
// calls this body). Empty derived of ActiveBodyModuleData (rowed ctor at
// 0x00257006 installs vtable 0xBF4028, no extra members needing teardown)
// so the body tail-jumps to the rowed base dtor at 0x00256CB0. novtable
// suppresses the derived vptr store retail lacks.
#include "../../../../Include/GameLogic/Module/ActiveBodyModuleData.h"

class __declspec(novtable) StructureBodyModuleData : public ActiveBodyModuleData
{
public:
	virtual ~StructureBodyModuleData();
};

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline StructureBodyModuleData::~StructureBodyModuleData()
{
}

// ?bfmeAnchorStructureBodyModuleDataDtor absent-from-retail
void bfmeAnchorStructureBodyModuleDataDtor(StructureBodyModuleData *structureBodyModuleData)
{
	structureBodyModuleData->StructureBodyModuleData::~StructureBodyModuleData();
}
