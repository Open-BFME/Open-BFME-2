// cl: /MD
// ??_GRva00414B40@@UAEPAXI@Z @0x00414B24 28B: scalar deleting dtor calling ??1Rva00414B40 at 0x00414B40.
// Same-shape sibling of ??_GRva00414932 at 0x00414AEE; needs ??1 row to exist.
class Rva00414B40 { public: __declspec(noinline) virtual ~Rva00414B40(); private: int m_famgen; };
Rva00414B40::~Rva00414B40() { m_famgen = 0; }
void famgenDelete(Rva00414B40 *p) { delete p; }
