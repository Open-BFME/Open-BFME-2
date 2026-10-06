// cl: /MD
// ??_GRva00587F69@@UAEPAXI@Z, retail 0x00587F4D 28B.
// Deleting dtor for Rva00587F69 whose ??1 is rowed at 0x00587F69; placeholder ~ is duplicate.
class Rva00587F69 { public: __declspec(noinline) virtual ~Rva00587F69(); private: int m_famgen; friend void famgenDelete(Rva00587F69 *p); };
Rva00587F69::~Rva00587F69() { m_famgen = 0; }
void famgenDelete(Rva00587F69 *p) { delete p; }
