// cl: /O1 /MD
// ??_GRunOffMapBehaviorModuleData@@UAEPAXI@Z @0x00255E8C 28B
// Deleting dtor slot 0 of vtable 0x007F3298; calls rowed ??1RunOffMapBehaviorModuleData@@UAE@XZ at 0x00255EA8 then rowed operator delete at 0x0002FD60.
class RunOffMapBehaviorModuleData { public: __declspec(noinline) virtual ~RunOffMapBehaviorModuleData(); private: int m_famgen; };
RunOffMapBehaviorModuleData::~RunOffMapBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(RunOffMapBehaviorModuleData *p) { delete p; }
// ??_GAutoDepositUpdateModuleData@@UAEPAXI@Z @0x0025528B 28B
// Deleting dtor slot 0 of vtable 0x007F1BC8; calls rowed ??1AutoDepositUpdateModuleData@@UAE@XZ at 0x002552A7 then rowed operator delete at 0x0002FD60.
class AutoDepositUpdateModuleData { public: __declspec(noinline) virtual ~AutoDepositUpdateModuleData(); private: int m_famgen; };
AutoDepositUpdateModuleData::~AutoDepositUpdateModuleData() { m_famgen = 0; }
void famgenDelete(AutoDepositUpdateModuleData *p) { delete p; }
