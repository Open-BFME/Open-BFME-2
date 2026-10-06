// cl: /MD
// ??_GRva001EBFE5@@UAEPAXI@Z @0x001EBFC9, 28B.
// Scalar deleting dtor slot 0; calls rowed ??1 at
// 0x001EBFE5 plus rowed delete at 0x0002FD60.

class Rva001EBFE5 { public: __declspec(noinline) virtual ~Rva001EBFE5(); private: int m_famgen;
  friend void famgenDelete(Rva001EBFE5 *p); };
Rva001EBFE5::~Rva001EBFE5() { m_famgen = 0; }
void famgenDelete(Rva001EBFE5 *p) { delete p; }
