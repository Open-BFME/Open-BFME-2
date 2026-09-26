// cl: /O1 /MD
// ??_GDominateEnemySpecialPowerModuleData@@UAEPAXI@Z @0x004CCA9E 28B
// Deleting dtor slot 0 of vtable 0x0085F6F8; calls rowed ??1 at 0x004CCABA then rowed operator delete at 0x0002FD60.
class DominateEnemySpecialPowerModuleData { public: __declspec(noinline) virtual ~DominateEnemySpecialPowerModuleData(); private: int m_famgen; };
DominateEnemySpecialPowerModuleData::~DominateEnemySpecialPowerModuleData() { m_famgen = 0; }
void famgenDelete(DominateEnemySpecialPowerModuleData *p) { delete p; }

// ??_GAODCrushCollideModuleData@@UAEPAXI@Z @0x004BC06C 28B
// Deleting dtor slot 0 of vtable 0x0085A350; calls rowed ??1 at 0x004BC088 then rowed operator delete at 0x0002FD60.
class AODCrushCollideModuleData { public: __declspec(noinline) virtual ~AODCrushCollideModuleData(); private: int m_famgen; };
AODCrushCollideModuleData::~AODCrushCollideModuleData() { m_famgen = 0; }
void famgenDelete(AODCrushCollideModuleData *p) { delete p; }

// ??_GDetachableRiderUpdateModuleData@@UAEPAXI@Z @0x004AEB23 28B
// Deleting dtor slot 0 of vtable 0x00855510; calls rowed ??1 at 0x004AEB3F then rowed operator delete at 0x0002FD60.
class DetachableRiderUpdateModuleData { public: __declspec(noinline) virtual ~DetachableRiderUpdateModuleData(); private: int m_famgen; };
DetachableRiderUpdateModuleData::~DetachableRiderUpdateModuleData() { m_famgen = 0; }
void famgenDelete(DetachableRiderUpdateModuleData *p) { delete p; }
