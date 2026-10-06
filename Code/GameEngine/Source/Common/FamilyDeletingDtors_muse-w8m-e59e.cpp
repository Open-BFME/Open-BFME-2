// cl: /MD
// ??_GOilSpillUpdateModuleData@@UAEPAXI@Z @0x0048C1DB 28B
// Deleting dtor slot 0 of vtable 0x00C4C2F8; calls rowed ??1 at 0x0048C191 then rowed operator delete at 0x0002FD60.
class OilSpillUpdateModuleData { public: __declspec(noinline) virtual ~OilSpillUpdateModuleData(); private: int m_famgen; };
OilSpillUpdateModuleData::~OilSpillUpdateModuleData() { m_famgen = 0; }
void famgenDelete(OilSpillUpdateModuleData *p) { delete p; }
