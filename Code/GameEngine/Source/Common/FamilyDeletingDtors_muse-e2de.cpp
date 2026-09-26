// cl: /O1 /MD
// ??_GSpecialEnemySenseUpdateModuleData@@UAEPAXI@Z @0x0025523F
// Deleting dtor slot 0 of vtable 0xBF1AD8; calls the rowed ??1 at 0x25525B.
class SpecialEnemySenseUpdateModuleData { public: __declspec(noinline) virtual ~SpecialEnemySenseUpdateModuleData(); private: int m_famgen; };
SpecialEnemySenseUpdateModuleData::~SpecialEnemySenseUpdateModuleData() { m_famgen = 0; }
void famgenDelete(SpecialEnemySenseUpdateModuleData *p) { delete p; }

// ??_GPillageModuleData@@UAEPAXI@Z @0x00254FFF
// Deleting dtor slot 0 of vtable 0xBF0568; calls the rowed ??1 at 0x25501B.
class PillageModuleData { public: __declspec(noinline) virtual ~PillageModuleData(); private: int m_famgen; };
PillageModuleData::~PillageModuleData() { m_famgen = 0; }
void famgenDelete(PillageModuleData *p) { delete p; }
