// cl: /O1 /MD
// ??_GDoCommandUpgradeModuleData@@UAEPAXI@Z @0x00256283 28B
// Deleting dtor slot 0 of vtable 0x007F3840; calls rowed ??1 at 0x00256222 then rowed operator delete at 0x0002FD60.
class DoCommandUpgradeModuleData { public: __declspec(noinline) virtual ~DoCommandUpgradeModuleData(); private: int m_famgen; };
// ??1DoCommandUpgradeModuleData@@UAE@XZ present-unmatched
DoCommandUpgradeModuleData::~DoCommandUpgradeModuleData() { m_famgen = 0; }
void famgenDeleteDoCommandUpgradeModuleData(DoCommandUpgradeModuleData *p) { delete p; }
