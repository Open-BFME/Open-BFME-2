// cl: /MD
// ??_GRva002AE627@@UAEPAXI@Z @0x002AF53E, 28B.
// Scalar deleting dtor slot 0 of vtable 0x007FDDB4; calls rowed ??1 at
// 0x002AE627 plus rowed delete at 0x0002FD60.

// ??_GRva002AE627@@UAEPAXI@Z @0x002AF53E present-unmatched
class Rva002AE627 { public: __declspec(noinline) virtual ~Rva002AE627(); private: int m_famgen;
  friend void famgenDelete(Rva002AE627 *p); };
Rva002AE627::~Rva002AE627() { m_famgen = 0; }
void famgenDelete(Rva002AE627 *p) { delete p; }
