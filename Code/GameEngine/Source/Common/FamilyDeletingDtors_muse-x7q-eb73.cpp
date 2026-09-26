// cl: /O1 /MD
// ??_GGettingBuiltBehaviorModuleData@@UAEPAXI@Z @0x004534D9 28B
// Deleting dtor slot 0 of vtable 0x00840090; calls rowed ??1 at 0x00453315 then rowed operator delete at 0x0002FD60.
class GettingBuiltBehaviorModuleData { public: __declspec(noinline) virtual ~GettingBuiltBehaviorModuleData(); private: int m_famgen; };
GettingBuiltBehaviorModuleData::~GettingBuiltBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(GettingBuiltBehaviorModuleData *p) { delete p; }
