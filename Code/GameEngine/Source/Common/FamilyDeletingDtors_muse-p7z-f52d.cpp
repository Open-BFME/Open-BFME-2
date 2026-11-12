// cl: /MD
// ??_GMonitorConditionUpdateModuleData@@UAEPAXI@Z @0x004916F5 28B
// Deleting dtor slot 0 of vtable 0x0084DA50; calls rowed ??1 at 0x00491711 then rowed operator delete at 0x0002FD60.
struct EmitVtableTag;

// Retail's tables hold ModuleData's 30 inherited slots after the deleting destructor.
#include "../../Include/Common/ModuleData.h"

class MonitorConditionUpdateModuleData { public: MonitorConditionUpdateModuleData(EmitVtableTag *); virtual ~MonitorConditionUpdateModuleData(); };
// ?<MonitorConditionUpdateModuleData::MonitorConditionUpdateModuleData> absent-from-retail
MonitorConditionUpdateModuleData::MonitorConditionUpdateModuleData(EmitVtableTag *) {}
// ??_GAttachUpdateModuleData@@UAEPAXI@Z @0x00491A84 28B
// Deleting dtor slot 0 of vtable 0x0084DD18; calls rowed ??1 at 0x00491AA0 then rowed operator delete at 0x0002FD60.
class AttachUpdateModuleData : public ModuleData { public: AttachUpdateModuleData(EmitVtableTag *); virtual ~AttachUpdateModuleData(); };
// ?<AttachUpdateModuleData::AttachUpdateModuleData> absent-from-retail
AttachUpdateModuleData::AttachUpdateModuleData(EmitVtableTag *) {}
// ??_GPickupStuffUpdateModuleData@@UAEPAXI@Z @0x00491F5A 28B
// Deleting dtor slot 0 of vtable 0x0084DDE0; calls rowed ??1 at 0x00491F76 then rowed operator delete at 0x0002FD60.
class PickupStuffUpdateModuleData { public: PickupStuffUpdateModuleData(EmitVtableTag *); virtual ~PickupStuffUpdateModuleData(); };
// ?<PickupStuffUpdateModuleData::PickupStuffUpdateModuleData> absent-from-retail
PickupStuffUpdateModuleData::PickupStuffUpdateModuleData(EmitVtableTag *) {}
