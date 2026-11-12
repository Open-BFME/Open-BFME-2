// cl: /MD
// ??_GOilSpillUpdateModuleData@@UAEPAXI@Z @0x0048C1DB 28B
// Deleting dtor slot 0 of vtable 0x00C4C2F8; calls rowed ??1 at 0x0048C191 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class OilSpillUpdateModuleData : public ModuleData { public: OilSpillUpdateModuleData(EmitVtableTag *); virtual ~OilSpillUpdateModuleData(); };
// ?<OilSpillUpdateModuleData::OilSpillUpdateModuleData> absent-from-retail
OilSpillUpdateModuleData::OilSpillUpdateModuleData(EmitVtableTag *) {}
