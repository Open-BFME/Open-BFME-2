// cl: /O1 /MD
// ??_GGiveOrRestoreUpgradeSpecialPower@@UAEPAXI@Z @0x004CD332, 28B.
// Deleting dtor slot 0 of vtable 0x0085FA40; calls rowed ??1GiveOrRestoreUpgradeSpecialPower@@UAE@XZ at 0x004CD166 then rowed operator delete at 0x0002FD60.
class GiveOrRestoreUpgradeSpecialPower { public: __declspec(noinline) virtual ~GiveOrRestoreUpgradeSpecialPower(); private: int m_famgen; };
GiveOrRestoreUpgradeSpecialPower::~GiveOrRestoreUpgradeSpecialPower() { m_famgen = 0; }
void famgenDelete(GiveOrRestoreUpgradeSpecialPower *p) { delete p; }
