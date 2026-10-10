// cl: /MD
// Each destructor is only declared: its row's own unit defines it. The inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GRva003A97E0@@UAEPAXI@Z @0x003AE73C 28B
// Deleting dtor calls rowed ??1Rva003A97E0@@UAE@XZ at 0x003A97E0 then rowed operator delete at 0x0002FD60.
// Evidence: dtor lane; retail push esi call ??1 test flag delete ret 4;
// vtable slot 0 of 0x0081D520 family; ??1 rowed in ParticleModuleInfoDtor.cpp.
class Rva003A97E0 { public: explicit Rva003A97E0(int) {} virtual ~Rva003A97E0(); private: int m_famgen;
  friend void famgenDelete(Rva003A97E0 *p); };
void famgenDelete(Rva003A97E0 *p) { delete p; }
Rva003A97E0 *famgenNew_Rva003A97E0() { return new Rva003A97E0(0); }
