// cl: /MD
// Each destructor is only declared: its row's own unit defines it. The inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GRva003AB9FF@@UAEPAXI@Z @0x003AE720 28B
// Deleting dtor calls rowed ??1Rva003AB9FF@@UAE@XZ at 0x003AB9FF then rowed operator delete at 0x0002FD60.
// Evidence: sibling of 0x003AE73C; retail push esi call ??1 test flag delete ret 4;
// vtable family; ??1 rowed in Rva003AB9FFDtor.cpp.
// Secondary base at +0x18: the this-adjusting deleting-destructor thunk
// (sub ecx, 0x18) at 0x003AE718 in its vtable is target evidence for it.
class Rva003AB9FFBase0 { public: virtual ~Rva003AB9FFBase0(); private: char m_unmodelled_04[0x18 - 0x04]; };
class Rva003AB9FFBase18 { public: virtual ~Rva003AB9FFBase18(); };
class Rva003AB9FF : public Rva003AB9FFBase0, public Rva003AB9FFBase18 { public: explicit Rva003AB9FF(int) {} virtual ~Rva003AB9FF(); private: int m_famgen;
  friend void famgenDelete(Rva003AB9FF *p); };
void famgenDelete(Rva003AB9FF *p) { delete p; }
Rva003AB9FF *famgenNew_Rva003AB9FF() { return new Rva003AB9FF(0); }
