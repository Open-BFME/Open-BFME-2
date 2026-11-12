// cl: /MD
// ??_GDominateEnemySpecialPowerModuleData@@UAEPAXI@Z @0x004CCA9E 28B
// Deleting dtor slot 0 of vtable 0x0085F6F8; calls rowed ??1 at 0x004CCABA then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class DominateEnemySpecialPowerModuleData : public ModuleData { public: DominateEnemySpecialPowerModuleData(EmitVtableTag *); virtual ~DominateEnemySpecialPowerModuleData(); };
// ?<DominateEnemySpecialPowerModuleData::DominateEnemySpecialPowerModuleData> absent-from-retail
DominateEnemySpecialPowerModuleData::DominateEnemySpecialPowerModuleData(EmitVtableTag *) {}

// ??_GAODCrushCollideModuleData@@UAEPAXI@Z @0x004BC06C 28B
// Deleting dtor slot 0 of vtable 0x0085A350; calls rowed ??1 at 0x004BC088 then rowed operator delete at 0x0002FD60.
class AODCrushCollideModuleData : public ModuleData { public: AODCrushCollideModuleData(EmitVtableTag *); virtual ~AODCrushCollideModuleData(); };
// ?<AODCrushCollideModuleData::AODCrushCollideModuleData> absent-from-retail
AODCrushCollideModuleData::AODCrushCollideModuleData(EmitVtableTag *) {}
