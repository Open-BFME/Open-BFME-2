// cl: /MD
// ??_GRva002560E3@@UAEPAXI@Z @0x002560C7 28B: scalar deleting dtor calling the
// rowed ??1Rva002560E3 0x002560E3 then sized operator delete. Family block
// per §4.3 (public for UAE).

// ??_GRva002560E3@@UAEPAXI@Z @0x002560c7
class Rva002560E3 { public: __declspec(noinline) virtual ~Rva002560E3(); private: int m_famgen;
  friend void famgenDelete(Rva002560E3 *p); };
Rva002560E3::~Rva002560E3() { m_famgen = 0; }
void famgenDelete(Rva002560E3 *p) { delete p; }
