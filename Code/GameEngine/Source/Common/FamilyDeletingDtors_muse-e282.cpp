// cl: /MD
// Each destructor is only declared: its row's own unit defines it. The inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GRva007401F6@@UAEPAXI@Z @0x00740226, 28B.
// Scalar deleting dtor calling rowed ??1 at 0x007401F6 plus rowed delete at 0x0002FD60.
// ??_GRva007401F6@@UAEPAXI@Z @0x00740226
class Rva007401F6 { public: explicit Rva007401F6(int) {} virtual ~Rva007401F6(); private: int m_famgen;
  friend void famgenDelete(Rva007401F6 *p); };
void famgenDelete(Rva007401F6 *p) { delete p; }
Rva007401F6 *famgenNew_Rva007401F6() { return new Rva007401F6(0); }
