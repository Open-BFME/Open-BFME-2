// cl: /O1 /MD
// ??_GSlowDeathBehaviorModuleData@@UAEPAXI@Z @0x0045E88D
// Deleting dtor slot 0 of vtable 0x842108; calls the rowed ??1 at 0x45E4A5.
class SlowDeathBehaviorModuleData { public: __declspec(noinline) virtual ~SlowDeathBehaviorModuleData(); private: int m_famgen; };
SlowDeathBehaviorModuleData::~SlowDeathBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(SlowDeathBehaviorModuleData *p) { delete p; }
