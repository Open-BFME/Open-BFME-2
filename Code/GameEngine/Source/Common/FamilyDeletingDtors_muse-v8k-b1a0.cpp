// cl: /MD
// Each destructor is only declared: its row's own unit defines it. The inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.
// ??_GRva003AE13C@@UAEPAXI@Z @0x003AE16E 28B
// Deleting dtor slot 0 of vtable 0x0081D2C0; calls rowed ??1Rva003AE13C@@UAE@XZ at 0x003A583E then rowed operator delete at 0x0002FD60.
class Rva003AE13C { public: explicit Rva003AE13C(int) {} virtual ~Rva003AE13C(); private: int m_famgen; };
void famgenDelete(Rva003AE13C *p) { delete p; }
Rva003AE13C *famgenNew_Rva003AE13C() { return new Rva003AE13C(0); }
