// cl: /MD
// ??_GRunOffMapBehaviorModuleData@@UAEPAXI@Z @0x00255E8C 28B
// Deleting dtor slot 0 of vtable 0x007F3298; calls rowed ??1RunOffMapBehaviorModuleData@@UAE@XZ at 0x00255EA8 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class RunOffMapBehaviorModuleData : public ModuleData { public: RunOffMapBehaviorModuleData(EmitVtableTag *); virtual ~RunOffMapBehaviorModuleData(); };
// ?<RunOffMapBehaviorModuleData::RunOffMapBehaviorModuleData> absent-from-retail
RunOffMapBehaviorModuleData::RunOffMapBehaviorModuleData(EmitVtableTag *) {}