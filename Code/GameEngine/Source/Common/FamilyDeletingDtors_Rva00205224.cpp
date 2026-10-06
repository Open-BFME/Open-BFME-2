// cl: /MD
// ??_GRva00205224@@UAEPAXI@Z @0x00205208 28B: scalar deleting dtor calling the
// rowed ??1Rva00205224 0x00205224 then operator delete. Family block
// per §4.3 (public for UAE).

class Rva00205224 { public: __declspec(noinline) virtual ~Rva00205224(); private: int m_famgen;
  friend void famgenDelete(Rva00205224 *p); };
Rva00205224::~Rva00205224() { m_famgen = 0; }
void famgenDelete(Rva00205224 *p) { delete p; }
