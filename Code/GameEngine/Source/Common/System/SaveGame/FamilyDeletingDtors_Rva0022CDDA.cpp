// cl: /MD
// ??_GRva0022CDDA@@UAEPAXI@Z @0x0022CDBE 28B.
// Scalar deleting dtor slot 0; calls rowed ??1 at 0x0022CDDA plus rowed delete at 0x0002FD60. Evidence: chain packet calls rowed 0x0022CDDA; ??_G shape with test byte [esp+8] 1.
// ??_GRva0022CDDA@@UAEPAXI@Z @0x0022CDBE present-unmatched
class Rva0022CDDA { public: __declspec(noinline) virtual ~Rva0022CDDA(); private: int m_famgen;
  friend void famgenDelete(Rva0022CDDA *p); };
Rva0022CDDA::~Rva0022CDDA() { m_famgen = 0; }
void famgenDelete(Rva0022CDDA *p) { delete p; }
