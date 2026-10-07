// cl: /MD
// ??_GRva00509D4C@@UAEPAXI@Z @0x00509D30 28B calls rowed ??1Rva00509D4C@@UAE@XZ at 0x00509D4C then delete.
// Chain from 0x00509D4C same 28B scalar-deleting shape.
class Rva00509D4C { public: __declspec(noinline) virtual ~Rva00509D4C(); private: int m_famgen; };
Rva00509D4C::~Rva00509D4C() { m_famgen = 0; }
void famgenDelete(Rva00509D4C *p) { delete p; }

