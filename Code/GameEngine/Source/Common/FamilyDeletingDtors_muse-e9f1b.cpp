// cl: /O1 /MD
// ??_GBoneFXUpdate@@MAEPAXI@Z @0x00487DD2
// Deleting dtor slot 0 of vtable 0x84B170; calls the rowed ??1 at 0x487ABF.
class BoneFXUpdate { protected: __declspec(noinline) virtual ~BoneFXUpdate(); private: int m_famgen; friend void famgenDelete(BoneFXUpdate *p); };
BoneFXUpdate::~BoneFXUpdate() { m_famgen = 0; }
void famgenDelete(BoneFXUpdate *p) { delete p; }
