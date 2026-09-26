// cl: /O1 /MD
// ??_GCommandPointsUpgradeModuleData@@UAEPAXI@Z @0x0025593D 28B
// Deleting dtor slot 0 of vtable 0x007F2658; calls rowed ??1 at 0x00255959 then rowed operator delete at 0x0002FD60.
class CommandPointsUpgradeModuleData { public: __declspec(noinline) virtual ~CommandPointsUpgradeModuleData(); private: int m_famgen; };
// ??1CommandPointsUpgradeModuleData@@UAE@XZ present-unmatched
CommandPointsUpgradeModuleData::~CommandPointsUpgradeModuleData() { m_famgen = 0; }
void famgenDeleteCommandPointsUpgradeModuleData(CommandPointsUpgradeModuleData *p) { delete p; }
// ??_GRefundDieModuleData@@UAEPAXI@Z @0x0025504B 28B
// Deleting dtor slot 0 of vtable 0x007F0660; calls rowed ??1 at 0x00255067 then rowed operator delete at 0x0002FD60.
class RefundDieModuleData { public: __declspec(noinline) virtual ~RefundDieModuleData(); private: int m_famgen; };
// ??1RefundDieModuleData@@UAE@XZ present-unmatched
RefundDieModuleData::~RefundDieModuleData() { m_famgen = 0; }
void famgenDeleteRefundDieModuleData(RefundDieModuleData *p) { delete p; }
