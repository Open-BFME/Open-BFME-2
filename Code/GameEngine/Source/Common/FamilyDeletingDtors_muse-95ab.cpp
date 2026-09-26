// cl: /O1 /MD
// ??_GDominateEnemySpecialPowerModuleData@@UAEPAXI@Z @0x004CCA9E 28B
// Deleting dtor slot 0 of vtable 0x0085F6F8; calls rowed ??1 at 0x004CCABA then rowed operator delete at 0x0002FD60.
class DominateEnemySpecialPowerModuleData { public: __declspec(noinline) virtual ~DominateEnemySpecialPowerModuleData(); private: int m_famgen; };
DominateEnemySpecialPowerModuleData::~DominateEnemySpecialPowerModuleData() { m_famgen = 0; }
void famgenDelete(DominateEnemySpecialPowerModuleData *p) { delete p; }
