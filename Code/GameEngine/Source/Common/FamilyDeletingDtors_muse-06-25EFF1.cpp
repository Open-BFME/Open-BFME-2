// cl: /MD
// ??_GRva0025EF18@@UAEPAXI@Z @0x0025EFF1, 28B.
// Scalar deleting dtor slot 0; calls rowed ??1 at 0x0025EF18 plus rowed delete at 0x0002FD60.

// ??_GRva0025EF18@@UAEPAXI@Z @0x0025EFF1 present-unmatched
class Rva0025EF18 { public: __declspec(noinline) virtual ~Rva0025EF18(); private: int m_famgen;
  friend void famgenDelete(Rva0025EF18 *p); };
Rva0025EF18::~Rva0025EF18() { m_famgen = 0; }
void famgenDelete(Rva0025EF18 *p) { delete p; }
