// cl: /O1 /MD
// ??_GBoneFXUpdateModuleData@@UAEPAXI@Z @0x0048785B
// Deleting dtor slot 0 of vtable 0x84B0E8; calls the rowed ??1 at 0x487877.
class BoneFXUpdateModuleData { public: __declspec(noinline) virtual ~BoneFXUpdateModuleData(); private: int m_famgen; };
BoneFXUpdateModuleData::~BoneFXUpdateModuleData() { m_famgen = 0; }
void famgenDelete(BoneFXUpdateModuleData *p) { delete p; }
