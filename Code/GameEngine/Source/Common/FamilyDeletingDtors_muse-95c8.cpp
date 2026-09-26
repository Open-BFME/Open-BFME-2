// cl: /O1 /MD
// ??_GFireWeaponUpdateModuleData@@UAEPAXI@Z @0x0048C098 28B
// Deleting dtor slot 0 of vtable 0x0084C110; calls rowed ??1 at 0x0048BC46 then rowed operator delete at 0x0002FD60.
class FireWeaponUpdateModuleData { public: __declspec(noinline) virtual ~FireWeaponUpdateModuleData(); private: int m_famgen; };
FireWeaponUpdateModuleData::~FireWeaponUpdateModuleData() { m_famgen = 0; }
void famgenDelete(FireWeaponUpdateModuleData *p) { delete p; }
