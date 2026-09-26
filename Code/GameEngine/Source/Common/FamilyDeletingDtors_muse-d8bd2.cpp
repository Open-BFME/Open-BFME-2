// cl: /O1 /MD
// ??_GFlammableUpdate@@UAEPAXI@Z @0x0048C8DD 28B
// Deleting dtor slot 0 of vtable 0x0084C3D4; calls rowed ??1 at 0x0048C724 then rowed operator delete at 0x0002FD60.
class FlammableUpdate { public: __declspec(noinline) virtual ~FlammableUpdate(); private: int m_famgen; };
FlammableUpdate::~FlammableUpdate() { m_famgen = 0; }
void famgenDelete(FlammableUpdate *p) { delete p; }
