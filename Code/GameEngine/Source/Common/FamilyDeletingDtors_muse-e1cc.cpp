// cl: /O1 /MD
// ??_GBloodthirstyUpdateModuleData@@UAEPAXI@Z @0x0044E315 28B
// Deleting dtor slot 0 of vtable 0x0083F160; calls rowed ??1 at 0x0044E331 then rowed operator delete at 0x0002FD60.
class BloodthirstyUpdateModuleData { public: __declspec(noinline) virtual ~BloodthirstyUpdateModuleData(); private: int m_famgen; };
BloodthirstyUpdateModuleData::~BloodthirstyUpdateModuleData() { m_famgen = 0; }
void famgenDelete(BloodthirstyUpdateModuleData *p) { delete p; }
