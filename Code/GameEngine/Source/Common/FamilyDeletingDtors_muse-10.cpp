// cl: /MD
// Each destructor is only declared: its row's own unit defines it. The inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GRva00517397@@UAEPAXI@Z @0x0051737B 28B
// Deleting dtor calls rowed ??1Rva00517397@@UAE@XZ at 0x00517397 then rowed operator delete at 0x0002FD60.
class Rva00517397 { public: explicit Rva00517397(int) {} virtual ~Rva00517397(); private: int m_famgen;
  friend void famgenDelete(Rva00517397 *p); };
void famgenDelete(Rva00517397 *p) { delete p; }
Rva00517397 *famgenNew_Rva00517397() { return new Rva00517397(0); }

// ??_GRva002E0F1E@@UAEPAXI@Z @0x002E18A7 28B
// Deleting dtor calls rowed ??1Rva002E0F1E@@UAE@XZ at 0x002E0F1E then rowed operator delete at 0x0002FD60.
class Rva002E0F1E { public: explicit Rva002E0F1E(int) {} virtual ~Rva002E0F1E(); private: int m_famgen;
  friend void famgenDelete(Rva002E0F1E *p); };
void famgenDelete(Rva002E0F1E *p) { delete p; }
Rva002E0F1E *famgenNew_Rva002E0F1E() { return new Rva002E0F1E(0); }
