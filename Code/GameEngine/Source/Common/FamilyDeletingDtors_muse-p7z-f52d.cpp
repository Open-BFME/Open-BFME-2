// cl: /O1 /MD
// ??_GMonitorConditionUpdateModuleData@@UAEPAXI@Z @0x004916F5 28B
// Deleting dtor slot 0 of vtable 0x0084DA50; calls rowed ??1 at 0x00491711 then rowed operator delete at 0x0002FD60.
class MonitorConditionUpdateModuleData { public: __declspec(noinline) virtual ~MonitorConditionUpdateModuleData(); private: int m_famgen; };
MonitorConditionUpdateModuleData::~MonitorConditionUpdateModuleData() { m_famgen = 0; }
void famgenDelete(MonitorConditionUpdateModuleData *p) { delete p; }
// ??_GAttachUpdateModuleData@@UAEPAXI@Z @0x00491A84 28B
// Deleting dtor slot 0 of vtable 0x0084DD18; calls rowed ??1 at 0x00491AA0 then rowed operator delete at 0x0002FD60.
class AttachUpdateModuleData { public: __declspec(noinline) virtual ~AttachUpdateModuleData(); private: int m_famgen; };
AttachUpdateModuleData::~AttachUpdateModuleData() { m_famgen = 0; }
void famgenDelete(AttachUpdateModuleData *p) { delete p; }
// ??_GPickupStuffUpdateModuleData@@UAEPAXI@Z @0x00491F5A 28B
// Deleting dtor slot 0 of vtable 0x0084DDE0; calls rowed ??1 at 0x00491F76 then rowed operator delete at 0x0002FD60.
class PickupStuffUpdateModuleData { public: __declspec(noinline) virtual ~PickupStuffUpdateModuleData(); private: int m_famgen; };
PickupStuffUpdateModuleData::~PickupStuffUpdateModuleData() { m_famgen = 0; }
void famgenDelete(PickupStuffUpdateModuleData *p) { delete p; }
