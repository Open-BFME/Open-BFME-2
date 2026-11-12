// cl: /MD
// ??_GLevelGrantSpecialPowerModuleData@@UAEPAXI@Z @0x004C2C06 28B
// Deleting dtor slot 0 of vtable 0x0085C828; calls rowed ??1 at 0x004C2C22 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class LevelGrantSpecialPowerModuleData : public ModuleData { public: LevelGrantSpecialPowerModuleData(EmitVtableTag *); virtual ~LevelGrantSpecialPowerModuleData(); };
// ?<LevelGrantSpecialPowerModuleData::LevelGrantSpecialPowerModuleData> absent-from-retail
LevelGrantSpecialPowerModuleData::LevelGrantSpecialPowerModuleData(EmitVtableTag *) {}
// ??_GClearanceTestingSlowDeathBehaviorModuleData@@UAEPAXI@Z @0x00483EC5 28B
// Deleting dtor slot 0 of vtable 0x00849E98; calls rowed ??1 at 0x00483EE1 then rowed operator delete at 0x0002FD60.
class ClearanceTestingSlowDeathBehaviorModuleData { public: ClearanceTestingSlowDeathBehaviorModuleData(EmitVtableTag *); virtual ~ClearanceTestingSlowDeathBehaviorModuleData(); };
// ?<ClearanceTestingSlowDeathBehaviorModuleData::ClearanceTestingSlowDeathBehaviorModuleData> absent-from-retail
ClearanceTestingSlowDeathBehaviorModuleData::ClearanceTestingSlowDeathBehaviorModuleData(EmitVtableTag *) {}
