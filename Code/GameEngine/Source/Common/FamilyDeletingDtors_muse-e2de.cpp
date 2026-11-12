// cl: /MD
// ??_GSpecialEnemySenseUpdateModuleData@@UAEPAXI@Z @0x0025523F
// Deleting dtor slot 0 of vtable 0xBF1AD8; calls the rowed ??1 at 0x25525B.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class SpecialEnemySenseUpdateModuleData { public: SpecialEnemySenseUpdateModuleData(EmitVtableTag *); virtual ~SpecialEnemySenseUpdateModuleData(); };
// ?<SpecialEnemySenseUpdateModuleData::SpecialEnemySenseUpdateModuleData> absent-from-retail
SpecialEnemySenseUpdateModuleData::SpecialEnemySenseUpdateModuleData(EmitVtableTag *) {}

// ??_GPillageModuleData@@UAEPAXI@Z @0x00254FFF
// Deleting dtor slot 0 of vtable 0xBF0568; calls the rowed ??1 at 0x25501B.
class PillageModuleData : public ModuleData { public: PillageModuleData(EmitVtableTag *); virtual ~PillageModuleData(); };
// ?<PillageModuleData::PillageModuleData> absent-from-retail
PillageModuleData::PillageModuleData(EmitVtableTag *) {}
