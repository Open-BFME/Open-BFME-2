// cl: /MD
// ??_GRva003AF50D@@UAEPAXI@Z @0x003AE492 28B
// Deleting dtor slot 0 of vtable 0x0081D420; calls rowed ??1Rva003AF50D@@UAE@XZ at 0x003A983C then rowed operator delete at 0x0002FD60.
class Rva003AF50D { public: __declspec(noinline) virtual ~Rva003AF50D(); private: int m_famgen; };
Rva003AF50D::~Rva003AF50D() { m_famgen = 0; }
void famgenDelete(Rva003AF50D *p) { delete p; }
