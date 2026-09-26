// cl: /O1 /MD
// ??_GRebuildHoleExposeDieModuleData@@UAEPAXI@Z @0x004869B0
// Deleting dtor slot 0 of vtable 0xC4AD40; calls the rowed ??1 at 0x4869CC.
class RebuildHoleExposeDieModuleData { public: __declspec(noinline) virtual ~RebuildHoleExposeDieModuleData(); private: int m_famgen; };
RebuildHoleExposeDieModuleData::~RebuildHoleExposeDieModuleData() { m_famgen = 0; }
void famgenDelete(RebuildHoleExposeDieModuleData *p) { delete p; }

// ??_GGrantUpgradeCreateModuleData@@UAEPAXI@Z @0x004B912F
// Deleting dtor slot 0 of vtable 0xC594E0; calls the rowed ??1 at 0x4B914B.
class GrantUpgradeCreateModuleData { public: __declspec(noinline) virtual ~GrantUpgradeCreateModuleData(); private: int m_famgen; };
GrantUpgradeCreateModuleData::~GrantUpgradeCreateModuleData() { m_famgen = 0; }
void famgenDelete(GrantUpgradeCreateModuleData *p) { delete p; }
