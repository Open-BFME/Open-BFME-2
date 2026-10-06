// cl: /MD
// ??_GLevelGrantSpecialPowerModuleData@@UAEPAXI@Z @0x004C2C06 28B
// Deleting dtor slot 0 of vtable 0x0085C828; calls rowed ??1 at 0x004C2C22 then rowed operator delete at 0x0002FD60.
class LevelGrantSpecialPowerModuleData { public: __declspec(noinline) virtual ~LevelGrantSpecialPowerModuleData(); private: int m_famgen; };
LevelGrantSpecialPowerModuleData::~LevelGrantSpecialPowerModuleData() { m_famgen = 0; }
void famgenDelete(LevelGrantSpecialPowerModuleData *p) { delete p; }
// ??_GClearanceTestingSlowDeathBehaviorModuleData@@UAEPAXI@Z @0x00483EC5 28B
// Deleting dtor slot 0 of vtable 0x00849E98; calls rowed ??1 at 0x00483EE1 then rowed operator delete at 0x0002FD60.
class ClearanceTestingSlowDeathBehaviorModuleData { public: __declspec(noinline) virtual ~ClearanceTestingSlowDeathBehaviorModuleData(); private: int m_famgen; };
ClearanceTestingSlowDeathBehaviorModuleData::~ClearanceTestingSlowDeathBehaviorModuleData() { m_famgen = 0; }
void famgenDelete(ClearanceTestingSlowDeathBehaviorModuleData *p) { delete p; }
