// cl: /MD
// ??_GPartTheHeavensUpdateModuleData@@UAEPAXI@Z @0x004ACCB1, 28B.
// Scalar deleting dtor slot 0 of vtable 0x00854E38; calls rowed ??1 at
// 0x004ACCCD plus rowed delete at 0x0002FD60.

// ??_GPartTheHeavensUpdateModuleData@@UAEPAXI@Z @0x004ACCB1
class PartTheHeavensUpdateModuleData { public: __declspec(noinline) virtual ~PartTheHeavensUpdateModuleData(); private: int m_famgen;
  friend void famgenDelete(PartTheHeavensUpdateModuleData *p); };
PartTheHeavensUpdateModuleData::~PartTheHeavensUpdateModuleData() { m_famgen = 0; }
void famgenDelete(PartTheHeavensUpdateModuleData *p) { delete p; }
