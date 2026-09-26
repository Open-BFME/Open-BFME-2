// cl: /O1 /MD
// ??_GGiveOrRestoreUpgradeSpecialPowerModuleData@@UAEPAXI@Z @0x004CD2CC 28B
// Deleting dtor slot 0 of vtable 0x0085F900; calls rowed ??1GiveOrRestoreUpgradeSpecialPowerModuleData@@UAE@XZ at 0x004CD2E8 then rowed operator delete at 0x0002FD60.
class GiveOrRestoreUpgradeSpecialPowerModuleData { public: __declspec(noinline) virtual ~GiveOrRestoreUpgradeSpecialPowerModuleData(); private: int m_famgen; };
GiveOrRestoreUpgradeSpecialPowerModuleData::~GiveOrRestoreUpgradeSpecialPowerModuleData() { m_famgen = 0; }
void famgenDelete(GiveOrRestoreUpgradeSpecialPowerModuleData *p) { delete p; }
