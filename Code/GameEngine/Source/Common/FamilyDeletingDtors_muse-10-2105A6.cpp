// cl: /MD
// ??_GRva002105A6@@UAEPAXI@Z @0x00210604 28B
// Deleting dtor slot 0; calls rowed ??1Rva002105A6@@UAE@XZ at 0x002105A6
// then rowed operator delete at 0x0002FD60. Evidence: chain lane after
// landing ??1; retail push esi call ??1 test flag delete ret 4.
class Rva002105A6 { public: __declspec(noinline) virtual ~Rva002105A6(); private: int m_famgen;
  friend void famgenDelete(Rva002105A6 *p); };
Rva002105A6::~Rva002105A6() { m_famgen = 0; }
void famgenDelete(Rva002105A6 *p) { delete p; }
