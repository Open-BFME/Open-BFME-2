// cl: /O1 /MD
// ??_GDynamicPortalBehaviour@@MAEPAXI@Z @0x00460DDA 28B
// Deleting dtor slot 0 of vtable 0x008428C4; calls rowed ??1 at 0x00460C18 then rowed operator delete at 0x0002FD60.
class DynamicPortalBehaviour { protected: __declspec(noinline) virtual ~DynamicPortalBehaviour(); private: int m_famgen;
  friend void famgenDelete(DynamicPortalBehaviour *p); };
DynamicPortalBehaviour::~DynamicPortalBehaviour() { m_famgen = 0; }
void famgenDelete(DynamicPortalBehaviour *p) { delete p; }
// ??_GGen0014AE40@@UAEPAXI@Z @0x002FE6F6 28B
// Deleting dtor slot 0 of vtable 0x008071FC; calls rowed ??1 at 0x002FE0A5 then rowed operator delete at 0x0002FD60.
class Gen0014AE40 { public: __declspec(noinline) virtual ~Gen0014AE40(); private: int m_famgen; };
Gen0014AE40::~Gen0014AE40() { m_famgen = 0; }
void famgenDeleteGen(Gen0014AE40 *p) { delete p; }
