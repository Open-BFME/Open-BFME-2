// cl: /O1 /MD
// ??_GRunOffMapBehaviorModuleData@@UAEPAXI@Z @0x00255E8C 28B
// Deleting dtor slot 0 of vtable 0x007F3298; calls rowed ??1RunOffMapBehaviorModuleData@@UAE@XZ at 0x00255EA8 then rowed operator delete at 0x0002FD60.
class RunOffMapBehaviorModuleData { public: __declspec(noinline) virtual ~RunOffMapBehaviorModuleData(); private: int m_famgen; };
RunOffMapBehaviorModuleData::~RunOffMapBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(RunOffMapBehaviorModuleData *p) { delete p; }
