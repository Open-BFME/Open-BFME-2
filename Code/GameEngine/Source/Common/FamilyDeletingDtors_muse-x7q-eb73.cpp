// cl: /O1 /MD
// ??_GGettingBuiltBehaviorModuleData@@UAEPAXI@Z @0x004534D9 28B
// Deleting dtor slot 0 of vtable 0x00840090; calls rowed ??1 at 0x00453315 then rowed operator delete at 0x0002FD60.
class GettingBuiltBehaviorModuleData { public: __declspec(noinline) virtual ~GettingBuiltBehaviorModuleData(); private: int m_famgen; };
GettingBuiltBehaviorModuleData::~GettingBuiltBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(GettingBuiltBehaviorModuleData *p) { delete p; }
// ??_GStealthUpdateModuleData@@UAEPAXI@Z @0x003759D9 28B
// Deleting dtor slot 0 of vtable 0x008184D8; calls rowed ??1 at 0x003759F5 then rowed operator delete at 0x0002FD60.
class StealthUpdateModuleData { public: __declspec(noinline) virtual ~StealthUpdateModuleData(); private: int m_famgen; };
StealthUpdateModuleData::~StealthUpdateModuleData() { m_famgen = 0; }
void famgenDelete(StealthUpdateModuleData *p) { delete p; }
// ??_GEntEnragedUpdateModuleData@@UAEPAXI@Z @0x004B2706 28B
// Deleting dtor slot 0 of vtable 0x00856980; calls rowed ??1 at 0x004B2722 then rowed operator delete at 0x0002FD60.
class EntEnragedUpdateModuleData { public: __declspec(noinline) virtual ~EntEnragedUpdateModuleData(); private: int m_famgen; };
EntEnragedUpdateModuleData::~EntEnragedUpdateModuleData() { m_famgen = 0; }
void famgenDelete(EntEnragedUpdateModuleData *p) { delete p; }
