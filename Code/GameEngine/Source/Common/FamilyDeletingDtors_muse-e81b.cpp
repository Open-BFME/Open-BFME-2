// cl: /O1 /MD
// ??_GRainOfFireUpdate@@UAEPAXI@Z @0x004AC5D9, 28B.
// Scalar deleting dtor slot 0 of vtable 0x00854C74; calls rowed ??1 at
// 0x004AC24D plus rowed delete at 0x0002FD60.

// ??_GRainOfFireUpdate@@UAEPAXI@Z @0x004AC5D9
class RainOfFireUpdate { public: __declspec(noinline) virtual ~RainOfFireUpdate(); private: int m_famgen;
  friend void famgenDelete(RainOfFireUpdate *p); };
RainOfFireUpdate::~RainOfFireUpdate() { m_famgen = 0; }
void famgenDelete(RainOfFireUpdate *p) { delete p; }
