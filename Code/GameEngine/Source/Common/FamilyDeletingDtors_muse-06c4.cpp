// cl: /O1 /MD
// ??_GW3DProjectileStreamDrawModuleData@@UAEPAXI@Z @0x000D1354, 28B.
// Scalar deleting dtor slot 0 of vtable 0x007CDF18; calls rowed ??1 at
// 0x000D1226 plus rowed delete at 0x0002FD60.

// ??_GW3DProjectileStreamDrawModuleData@@UAEPAXI@Z @0x000D1354
class W3DProjectileStreamDrawModuleData { public: __declspec(noinline) virtual ~W3DProjectileStreamDrawModuleData(); private: int m_famgen;
  friend void famgenDelete(W3DProjectileStreamDrawModuleData *p); };
W3DProjectileStreamDrawModuleData::~W3DProjectileStreamDrawModuleData() { m_famgen = 0; }
void famgenDelete(W3DProjectileStreamDrawModuleData *p) { delete p; }
