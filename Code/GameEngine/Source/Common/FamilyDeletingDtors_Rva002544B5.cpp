// cl: /MD
//
// ??_GRva002544B5@@UAEPAXI@Z, retail 0x00254499, 28 bytes. Deleting dtor for
// Rva002544B5: calls rowed ??1Rva002544B5 60B at 0x002544B5 then operator
// delete 0x0002FD60 on flag. Chain from 0x002544B5. Public virtual (UAE).

class Rva002544B5 { public: __declspec(noinline) virtual ~Rva002544B5(); private: int m_famgen; };
Rva002544B5::~Rva002544B5() { m_famgen = 0; }
void famgenDelete(Rva002544B5 *p) { delete p; }
