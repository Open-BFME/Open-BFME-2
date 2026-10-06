// cl: /MD
// ??_GRva00586D8E@@UAEPAXI@Z, retail 0x00586E35 28B.
// Deleting dtor for Rva00586D8E whose ??1 is rowed at 0x00586E51; placeholder ~ is duplicate.
class Rva00586D8E { public: __declspec(noinline) virtual ~Rva00586D8E(); private: int m_famgen; friend void famgenDelete(Rva00586D8E *p); };
Rva00586D8E::~Rva00586D8E() { m_famgen = 0; }
void famgenDelete(Rva00586D8E *p) { delete p; }
