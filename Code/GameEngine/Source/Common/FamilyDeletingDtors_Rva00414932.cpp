// cl: /MD
// ??_GRva00414932@@UAEPAXI@Z @0x00414AEE 28B: scalar deleting dtor calling ??1Rva00414932 at 0x00414932.
// Same-shape sibling of ??_GVersion; needs ??1 row to exist.

class Rva00414932 { public: __declspec(noinline) virtual ~Rva00414932(); private: int m_famgen; };
Rva00414932::~Rva00414932() { m_famgen = 0; }
void famgenDelete(Rva00414932 *p) { delete p; }
