// cl: /O1 /MD
// ??_GReplaceSelfUpgradeModuleData@@UAEPAXI@Z @0x004B795E 28B
// Deleting dtor slot 0 of vtable 0x00858B40; calls rowed ??1ReplaceSelfUpgradeModuleData@@UAE@XZ at 0x004B797A then rowed operator delete at 0x0002FD60.
class ReplaceSelfUpgradeModuleData { public: __declspec(noinline) virtual ~ReplaceSelfUpgradeModuleData(); private: int m_famgen; };
ReplaceSelfUpgradeModuleData::~ReplaceSelfUpgradeModuleData() { m_famgen = 0; }
void famgenDelete(ReplaceSelfUpgradeModuleData *p) { delete p; }
