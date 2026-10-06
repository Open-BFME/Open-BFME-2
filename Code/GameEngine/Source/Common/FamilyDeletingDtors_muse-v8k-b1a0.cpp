// cl: /MD
// ??_GRva003AE13C@@UAEPAXI@Z @0x003AE16E 28B
// Deleting dtor slot 0 of vtable 0x0081D2C0; calls rowed ??1Rva003AE13C@@UAE@XZ at 0x003A583E then rowed operator delete at 0x0002FD60.
class Rva003AE13C { public: __declspec(noinline) virtual ~Rva003AE13C(); private: int m_famgen; };
Rva003AE13C::~Rva003AE13C() { m_famgen = 0; }
void famgenDelete(Rva003AE13C *p) { delete p; }
