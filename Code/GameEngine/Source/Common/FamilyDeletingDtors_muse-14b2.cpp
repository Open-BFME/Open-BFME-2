// cl: /MD
// ??_GDynamicShroudClearingRangeUpdateModuleData@@UAEPAXI@Z @0x0048B618 28B
// Deleting dtor slot 0 of vtable 0x0084BEF8; calls rowed ??1 at 0x0048B634 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class DynamicShroudClearingRangeUpdateModuleData : public ModuleData { public: DynamicShroudClearingRangeUpdateModuleData(EmitVtableTag *); virtual ~DynamicShroudClearingRangeUpdateModuleData(); };
// ?<DynamicShroudClearingRangeUpdateModuleData::DynamicShroudClearingRangeUpdateModuleData> absent-from-retail
DynamicShroudClearingRangeUpdateModuleData::DynamicShroudClearingRangeUpdateModuleData(EmitVtableTag *) {}
