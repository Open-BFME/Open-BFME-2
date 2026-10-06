// cl: /MD
// ??_GRva00382398@@UAEPAXI@Z @0x003831EB, 28B.
// Scalar deleting dtor for Rva00382398; calls rowed ??1 at 0x00382398 plus
// rowed delete at 0x0002FD60.

class Rva00382398 { public: __declspec(noinline) virtual ~Rva00382398(); private: int m_famgen;
  friend void famgenDelete(Rva00382398 *p); };
Rva00382398::~Rva00382398() { m_famgen = 0; }
void famgenDelete(Rva00382398 *p) { delete p; }
