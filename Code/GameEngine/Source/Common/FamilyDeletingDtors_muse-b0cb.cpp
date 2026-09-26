// cl: /O1 /MD
// ??_GStatusBitsUpgradeIfEldestKindofModuleData@@UAEPAXI@Z @0x00255740 28B
// Deleting dtor slot 0 of vtable 0x00BF25D8; calls the rowed ??1 at 0x0025575C.
class StatusBitsUpgradeIfEldestKindofModuleData { public: __declspec(noinline) virtual ~StatusBitsUpgradeIfEldestKindofModuleData(); private: int m_famgen; };
StatusBitsUpgradeIfEldestKindofModuleData::~StatusBitsUpgradeIfEldestKindofModuleData() { m_famgen = 0; }
void famgenDelete(StatusBitsUpgradeIfEldestKindofModuleData *p) { delete p; }
