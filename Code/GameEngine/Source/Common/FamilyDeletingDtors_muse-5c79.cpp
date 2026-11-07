// cl: /MD
// Each destructor is only declared: its row's own unit defines it. The inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// Both classes derive from the canonical ModuleData, as their constructor units declare
// AIUpdateModuleData (AIUpdateModuleDataCtor.cpp), so this unit's copies of the 31-slot
// vftables (retail 0x00C70220, 0x00C4EA88) are the retail-shaped tables instead of
// one-slot ones.
#include "../../Include/Common/ModuleData.h"

// ??_GAIUpdateModuleData@@UAEPAXI@Z @0x0058957E 28B
// Deleting dtor slot 0 of vtable 0x00870220; calls rowed ??1 at 0x00494BE4 then rowed operator delete at 0x0002FD60.
class AIUpdateModuleData : public ModuleData { public: explicit AIUpdateModuleData(int) {} virtual ~AIUpdateModuleData(); private: int m_famgen; };
void famgenDelete(AIUpdateModuleData *aIUpdateModuleData) { delete aIUpdateModuleData; }
AIUpdateModuleData *famgenNew_AIUpdateModuleData() { return new AIUpdateModuleData(0); }

// ??_GWeaponModeSpecialPowerUpdateModuleData@@UAEPAXI@Z @0x00494D60 28B
// Deleting dtor slot 0 of vtable 0x0084EA88; calls rowed ??1 at 0x00494D7C then rowed operator delete at 0x0002FD60.
class WeaponModeSpecialPowerUpdateModuleData : public AIUpdateModuleData { public: explicit WeaponModeSpecialPowerUpdateModuleData(int) : AIUpdateModuleData(0) {} virtual ~WeaponModeSpecialPowerUpdateModuleData(); private: int m_famgen; };
void famgenDelete(WeaponModeSpecialPowerUpdateModuleData *weaponModeSpecialPowerUpdateModuleData) { delete weaponModeSpecialPowerUpdateModuleData; }
WeaponModeSpecialPowerUpdateModuleData *famgenNew_WeaponModeSpecialPowerUpdateModuleData() { return new WeaponModeSpecialPowerUpdateModuleData(0); }
