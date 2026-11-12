// cl: /MD
// ??_GRadiateFearUpdateModuleData@@UAEPAXI@Z @0x0049C1D2 28B
// Deleting dtor slot 0 of vtable 0x00850FF0; calls rowed ??1 at 0x0049C1EE then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class RadiateFearUpdateModuleData : public ModuleData { public: RadiateFearUpdateModuleData(EmitVtableTag *); virtual ~RadiateFearUpdateModuleData(); };
// ?<RadiateFearUpdateModuleData::RadiateFearUpdateModuleData> absent-from-retail
RadiateFearUpdateModuleData::RadiateFearUpdateModuleData(EmitVtableTag *) {}
