// cl: /O1 /MD
// ??_GAISpecialPowerUpdate@@UAEPAXI@Z @0x004B2F5F, 28B.
// Scalar deleting dtor slot 0 of vtable 0x00856E1C; calls rowed ??1 at
// 0x004B2E79 plus rowed delete at 0x0002FD60.

// ??_GAISpecialPowerUpdate@@UAEPAXI@Z @0x004B2F5F
class AISpecialPowerUpdate { public: __declspec(noinline) virtual ~AISpecialPowerUpdate(); private: int m_famgen;
  friend void famgenDelete(AISpecialPowerUpdate *p); };
AISpecialPowerUpdate::~AISpecialPowerUpdate() { m_famgen = 0; }
void famgenDelete(AISpecialPowerUpdate *p) { delete p; }
