// cl: /MD
// ??_GRva005E8AAF@@UAEPAXI@Z @0x005E8A93 28B
// Deleting dtor calls rowed ??1Rva005E8AAF@@UAE@XZ at 0x005E8AAF then rowed operator delete at 0x0002FD60.
class Rva005E8AAF { public: __declspec(noinline) virtual ~Rva005E8AAF(); private: int m_famgen;
  friend void famgenDelete(Rva005E8AAF *p); };
Rva005E8AAF::~Rva005E8AAF() { m_famgen = 0; }
void famgenDelete(Rva005E8AAF *p) { delete p; }
