// cl: /O1 /MD
// ??_GSiegeDeployHordeSpecialPower@@UAEPAXI@Z @0x004C64B7 28B
// Deleting dtor slot 0 of vtable 0x0085DD94; calls rowed ??1 at 0x004C63EF then rowed operator delete at 0x0002FD60.
class SiegeDeployHordeSpecialPower { public: __declspec(noinline) virtual ~SiegeDeployHordeSpecialPower(); private: int m_famgen; };
SiegeDeployHordeSpecialPower::~SiegeDeployHordeSpecialPower() { m_famgen = 0; }
void famgenDelete(SiegeDeployHordeSpecialPower *p) { delete p; }
