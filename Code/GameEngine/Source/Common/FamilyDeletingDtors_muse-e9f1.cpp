// cl: /MD
// ??_GBoneFXUpdateModuleData@@UAEPAXI@Z @0x0048785B
// Deleting dtor slot 0 of vtable 0x84B0E8; calls the rowed ??1 at 0x487877.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class BoneFXUpdateModuleData : public ModuleData { public: BoneFXUpdateModuleData(EmitVtableTag *); virtual ~BoneFXUpdateModuleData(); };
// ?<BoneFXUpdateModuleData::BoneFXUpdateModuleData> absent-from-retail
BoneFXUpdateModuleData::BoneFXUpdateModuleData(EmitVtableTag *) {}
