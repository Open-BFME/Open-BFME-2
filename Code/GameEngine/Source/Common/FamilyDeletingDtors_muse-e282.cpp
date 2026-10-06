// cl: /MD
// ??_GRva007401F6@@UAEPAXI@Z @0x00740226, 28B.
// Scalar deleting dtor calling rowed ??1 at 0x007401F6 plus rowed delete at 0x0002FD60.
// ??_GRva007401F6@@UAEPAXI@Z @0x00740226
class Rva007401F6 { public: __declspec(noinline) virtual ~Rva007401F6(); private: int m_famgen;
  friend void famgenDelete(Rva007401F6 *p); };
Rva007401F6::~Rva007401F6() { m_famgen = 0; }
void famgenDelete(Rva007401F6 *p) { delete p; }
