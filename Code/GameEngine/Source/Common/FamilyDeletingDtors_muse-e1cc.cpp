// cl: /MD
// ??_GBloodthirstyUpdateModuleData@@UAEPAXI@Z @0x0044E315 28B
// Deleting dtor slot 0 of vtable 0x0083F160; calls rowed ??1 at 0x0044E331 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class BloodthirstyUpdateModuleData : public ModuleData { public: BloodthirstyUpdateModuleData(EmitVtableTag *); virtual ~BloodthirstyUpdateModuleData(); };
// ?<BloodthirstyUpdateModuleData::BloodthirstyUpdateModuleData> absent-from-retail
BloodthirstyUpdateModuleData::BloodthirstyUpdateModuleData(EmitVtableTag *) {}
