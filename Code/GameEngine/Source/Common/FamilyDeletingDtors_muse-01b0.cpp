// cl: /O1 /MD
// ??_GInheritUpgradeCreateModuleData@@UAEPAXI@Z @0x004B954D, 28B.
// Scalar deleting dtor slot 0 of vtable 0x00859768; calls rowed ??1 at
// 0x004B9569 plus rowed delete at 0x0002FD60.

// ??_GInheritUpgradeCreateModuleData@@UAEPAXI@Z @0x004B954D
class InheritUpgradeCreateModuleData { public: __declspec(noinline) virtual ~InheritUpgradeCreateModuleData(); private: int m_famgen;
  friend void famgenDelete(InheritUpgradeCreateModuleData *p); };
InheritUpgradeCreateModuleData::~InheritUpgradeCreateModuleData() { m_famgen = 0; }
void famgenDelete(InheritUpgradeCreateModuleData *p) { delete p; }
