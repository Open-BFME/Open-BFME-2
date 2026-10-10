// cl: /MD
// Each destructor is only declared: its row's own unit defines it. The inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GAIUpdateModuleData@@UAEPAXI@Z @0x0058957E 28B
// Deleting dtor slot 0 of vtable 0x00870220; calls rowed ??1 at 0x00494BE4 then rowed operator delete at 0x0002FD60.
class AIUpdateModuleData { public: explicit AIUpdateModuleData(int) {} virtual ~AIUpdateModuleData(); private: int m_famgen; };
void famgenDelete(AIUpdateModuleData *p) { delete p; }
AIUpdateModuleData *famgenNew_AIUpdateModuleData() { return new AIUpdateModuleData(0); }

// ??_GWeaponModeSpecialPowerUpdateModuleData@@UAEPAXI@Z @0x00494D60 28B
// Deleting dtor slot 0 of vtable 0x0084EA88; calls rowed ??1 at 0x00494D7C then rowed operator delete at 0x0002FD60.
class WeaponModeSpecialPowerUpdateModuleData { public: explicit WeaponModeSpecialPowerUpdateModuleData(int) {} virtual ~WeaponModeSpecialPowerUpdateModuleData(); private: int m_famgen; };
void famgenDelete(WeaponModeSpecialPowerUpdateModuleData *p) { delete p; }
WeaponModeSpecialPowerUpdateModuleData *famgenNew_WeaponModeSpecialPowerUpdateModuleData() { return new WeaponModeSpecialPowerUpdateModuleData(0); }
